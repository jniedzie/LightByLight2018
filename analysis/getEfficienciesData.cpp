//  getEfficienciesData
//
//  Created by Jeremi Niedziela on 24/07/2019.
//
//  Calculates data driven efficiencies, as defined in the Analysis Note

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "ConfigManager.hpp"

string configPath = "configs/efficiencies.md";

void PrintEfficiency(double num, double den)
{
  cout<<(double)num/den<<"\t#pm "<<sqrt(1./num+1./den)*(double)num/den<<endl;
}

vector<string> histParams = {
  "reco_id_eff"
};

int main(int argc, char* argv[])
{
  if(argc != 1 && argc != 3){
    cout<<"This app requires 0 or 2 parameters."<<endl;
    cout<<"./getEfficienciesData inputPath outputPath"<<endl;
    exit(0);
  }
  
  unique_ptr<EventProcessor> eventProcessor;
  if(argc == 3) eventProcessor = unique_ptr<EventProcessor>(new EventProcessor(argv[1]));
  else          eventProcessor = unique_ptr<EventProcessor>(new EventProcessor(kData));
  
  config = ConfigManager(configPath);
  
  // Prepare counters and histograms
  int nTagEvents     = 0;
  int nPassingEvents = 0;
  
  float bins[] = { 0, 2, 3, 4, 5, 6, 8, 10, 13, 20 };
  map<string, TH1D*> hists;
  for(auto name : histParams){
    hists[name]         = new TH1D( name.c_str()        ,  name.c_str()        , 9, bins);
    hists[name+"_num"]  = new TH1D((name+"_num").c_str(), (name+"_num").c_str(), 9, bins);
    hists[name+"_den"]  = new TH1D((name+"_den").c_str(), (name+"_den").c_str(), 9, bins);
    hists[name+"_num"]->Sumw2();
    hists[name+"_den"]->Sumw2();
  }
  
  // Loop over events
  int iEvent;
  for(iEvent=0; iEvent<eventProcessor->GetNevents(); iEvent++){
    if(iEvent%10000 == 0) cout<<"Processing event "<<iEvent<<endl;
    if(iEvent >= config.params["maxEvents"]) break;
    
    auto event = eventProcessor->GetEvent(iEvent);
    
    // Preselect events with one photon, one electron and one extra track not reconstructed as an electron
    if(event->HasSingleEG3Trigger() &&
       event->GetNgeneralTracks() == 2 &&
       event->GetNelectrons() == 1){
      
      cout<<"Found good event"<<endl;
      
      auto electron = event->GetElectron(0);
      
      // Find matching track
      auto track1 = event->GetGeneralTrack(0);
      auto track2 = event->GetGeneralTrack(1);
      
      double deltaR1 = sqrt(pow(electron->GetEta()-track1->GetEta(), 2) +
                            pow(electron->GetPhi()-track1->GetPhi(), 2));
      
      double deltaR2 = sqrt(pow(electron->GetEta()-track2->GetEta(), 2) +
                            pow(electron->GetPhi()-track2->GetPhi(), 2));
      
      shared_ptr<PhysObject> matchingTrack = nullptr;
      shared_ptr<PhysObject> bremTrack = nullptr;
      
      if(deltaR1 < 0.3 && deltaR2 > 0.3){
        matchingTrack = track1;
        bremTrack     = track2;
      }
      if(deltaR1 > 0.3 && deltaR2 < 0.3){
        matchingTrack = track2;
        bremTrack     = track1;
      }
      
      if(!matchingTrack){
        cout<<"Both track or no track match the electron"<<endl;
      }
      else{
        cout<<"There's one track matching electron"<<endl;
        if(electron->GetPt() > 3.0 && fabs(electron->GetEta())<2.4){
          cout<<"Electron passes cuts"<<endl;
          
          if(bremTrack->GetCharge() == -electron->GetCharge()){
            cout<<"Have opposite charges"<<endl;
            
            if(bremTrack->GetPt() < 2.0){
              cout<<"Found an event matching all \"tag\" criteria"<<endl;
              hists["reco_id_eff_den"]->Fill(1);
              nTagEvents++;
              
              if(event->GetNphotonSCs() == 1){
                if(event->GetPhotonSC(0)->GetPt() > 2.0){
                  cout<<"and it has one photon"<<endl;
                  hists["reco_id_eff_num"]->Fill(1);
                  nPassingEvents++;
                }
              }
            }
          }
        }
      }

    }
  }
  
  // Print the results
  cout<<"\n\n------------------------------------------------------------------------"<<endl;
  cout<<"N event analyzed: "<<iEvent<<endl;
  cout<<"N tags: "<<nTagEvents<<endl;
  cout<<"N passing: "<<nPassingEvents<<endl;
  
  cout<<"Reco+ID efficiency: "; PrintEfficiency(nPassingEvents, nTagEvents);
  
  cout<<"------------------------------------------------------------------------\n\n"<<endl;
  
  // Save histograms
  TFile *outFile = new TFile(argc==3 ? argv[2]  : "results/efficienciesData.root", "recreate");
  outFile->cd();
  
  for(auto name : histParams){
    hists[name]->Divide(hists[name+"_num"], hists[name+"_den"], 1, 1, "B");
    hists[name]->Write();
    hists[name+"_num"]->Write();
    hists[name+"_den"]->Write();
  }
  
  outFile->Close();
  
  return 0;
}

