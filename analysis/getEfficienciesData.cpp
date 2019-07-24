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

int main()
{
  config = ConfigManager(configPath);
  unique_ptr<EventProcessor> eventProcessor(new EventProcessor(kData));
  
  // Prepare counters and histograms
  int nGenEvents                               = 0;
  int nEventsPassingAll                        = 0;
  
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
    
    // Here we get gen and reco photons that pass acceptance (c_ACC) criteria
    auto goodGenPhotons  = event->GetGoodGenPhotons();
    auto photonSCpassing = event->GetGoodPhotonSCs();
    
    // Check properties of this event
    bool hasTwoGoodGenPhotons     = false;
    
    
    // Increment counters of different types of events
    if(hasTwoGoodGenPhotons){
      nGenEvents++;
      hists["reco_id_eff_den"]->Fill(goodGenPhotons.front()->GetEt());
    }
    
  }
  
  // Print the results
  cout<<"\n\n------------------------------------------------------------------------"<<endl;
  cout<<"N event analyzed: "<<iEvent<<endl;
  cout<<"N gen events within limits: "<<nGenEvents<<endl;
  cout<<"N events passing all selections: "<<nEventsPassingAll<<endl;
  
  cout<<"Reco+ID efficiency: "; PrintEfficiency(nEventsPassingAll, nGenEvents);
  
  cout<<"------------------------------------------------------------------------\n\n"<<endl;
  
  // Save histograms
  TFile *outFile = new TFile("results/efficienciesData.root", "recreate");
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

