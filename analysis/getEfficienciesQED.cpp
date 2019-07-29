//  getEfficienciesData
//
//  Created by Jeremi Niedziela on 24/07/2019.
//
//  Calculates data driven efficiencies, as defined in the Analysis Note

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"

string configPath = "configs/efficiencies.md";

bool doRecoEfficiency = true;
bool doCHEefficiency = true;
bool doNEEefficiency = true;

vector<string> histParams = {
  "reco_id_eff", "charged_exclusivity_eff", "neutral_exclusivity_eff",
};

map<string, pair<int, int>> nEvents; ///< N events passing tag/probe criteria
map<string, TH1D*> cutThroughHists;
map<string, TH1D*> hists;

/// Counts number of events passing tag and probe criteria for reco+ID efficiency
void CheckRecoEfficiency(Event &event)
{
  // Preselect events with one electron and one extra track not reconstructed as an electron
  if(event.HasSingleEG5Trigger() &&
     event.GetNelectrons() == 1 &&
     event.GetNgeneralTracks() == 2){
    
    cutThroughHists["reco_id_eff_den"]->Fill(1);
    
    // Get objects of interest
    auto electron = event.GetElectron(0);
    auto track1   = event.GetGeneralTrack(0);
    auto track2   = event.GetGeneralTrack(1);
    
    // Check electron cuts
    if(electron->GetPt() > 3.0 && fabs(electron->GetEta()) < 2.4){
      cutThroughHists["reco_id_eff_den"]->Fill(2);
      
      // Check if there is exactly one track matching electron
      double deltaR1 = physObjectProcessor.GetDeltaR(*electron, *track1);
      double deltaR2 = physObjectProcessor.GetDeltaR(*electron, *track2);
      
      shared_ptr<PhysObject> matchingTrack = nullptr;
      shared_ptr<PhysObject> bremTrack     = nullptr;
      
      if(deltaR1 < 0.3 && deltaR2 > 0.3){
        matchingTrack                      = track1;
        bremTrack                          = track2;
      }
      if(deltaR1 > 0.3 && deltaR2 < 0.3){
        matchingTrack                      = track2;
        bremTrack                          = track1;
      }
      
      if(matchingTrack){
        cutThroughHists["reco_id_eff_den"]->Fill(3);
        
        // Make sure that tracks have opposite charges and that brem track has low momentum
        if(bremTrack->GetCharge() != electron->GetCharge() && bremTrack->GetPt() < 2.0){
          cutThroughHists["reco_id_eff_den"]->Fill(4);
          
          // Count this event as a tag
          hists["reco_id_eff_den"]->Fill(1);
          nEvents["reco_id_eff"].first++;
          
          // Check that there's exactly one photon and has high enough momentum
          if(event.GetGoodPhotonSCs().size() == 1){
            cutThroughHists["reco_id_eff_den"]->Fill(5);
            
            // Count this event as a probe
            hists["reco_id_eff_num"]->Fill(1);
            nEvents["reco_id_eff"].second++;
          }
        }
      }
    }
  }
}

/// Counts number of events passing tag and probe criteria for charged exclusivity efficiency
void CheckCHEefficiency(const Event &event)
{
  if(event.HasLbLTrigger()){
    cutThroughHists["charged_exclusivity_eff"]->Fill(1);
    auto goodElectrons = event.GetGoodElectrons();
    
    if(goodElectrons.size() >= 2){
      
      int nPositiveElectrons = 0;
      int nNegativeElectrons = 0;
      
      for(auto &electron : goodElectrons){
        if(electron->GetCharge() > 0) nPositiveElectrons++;
        if(electron->GetCharge() < 0) nNegativeElectrons++;
      }
      
      if(nPositiveElectrons > 0 && nNegativeElectrons > 0){
        cutThroughHists["charged_exclusivity_eff"]->Fill(2);
        hists["charged_exclusivity_eff_den"]->Fill(1);
        nEvents["charged_exclusivity_eff"].first++;
        
        if(event.GetNchargedTracks() == 2){
          cutThroughHists["charged_exclusivity_eff"]->Fill(3);
          hists["charged_exclusivity_eff_num"]->Fill(1);
          nEvents["charged_exclusivity_eff"].second++;
        }
      }
    }
  }
}

/// Counts number of events passing tag and probe criteria for neutral exclusivity efficiency
void CheckNEEefficiency(const Event &event)
{
  if(event.HasLbLTrigger()){
    
    auto goodElectrons = event.GetGoodElectrons();
    
    if(goodElectrons.size() == 2){
      cutThroughHists["neutral_exclusivity_eff"]->Fill(1);
      
      auto electron1 = goodElectrons[0];
      auto electron2 = goodElectrons[1];
      
      if(electron1->GetCharge() != electron2->GetCharge() &&
         electron1->GetNmissingHits() == 0  && electron2->GetNmissingHits() == 0 &&
         electron1->GetHoverE() < 0.02      && electron2->GetHoverE() < 0.02
         ){
        cutThroughHists["neutral_exclusivity_eff"]->Fill(2);
        TLorentzVector dielectron = physObjectProcessor.GetObjectsSum(*electron1, *electron2);
        
        if(dielectron.M() > 5.0 && dielectron.Pt() < 1.0 && fabs(dielectron.Eta()) < 2.4){
          cutThroughHists["neutral_exclusivity_eff"]->Fill(3);
          hists["neutral_exclusivity_eff_den"]->Fill(1);
          nEvents["neutral_exclusivity_eff"].first++;
          
          if(event.GetNchargedTracks() == 2){
            cutThroughHists["neutral_exclusivity_eff"]->Fill(4);
            hists["neutral_exclusivity_eff_num"]->Fill(1);
            nEvents["neutral_exclusivity_eff"].second++;
          }
        }
      }
    }
  }
}

int main(int argc, char* argv[])
{
  if(argc != 1 && argc != 4){
    cout<<"This app requires 0 or 2 parameters."<<endl;
    cout<<"./getEfficienciesData configPath inputPath outputPath"<<endl;
    exit(0);
  }
  
  unique_ptr<EventProcessor> eventProcessor;
  if(argc == 4){
    eventProcessor = unique_ptr<EventProcessor>(new EventProcessor(argv[2]));
    configPath = argv[1];
  }
  else{
    eventProcessor = unique_ptr<EventProcessor>(new EventProcessor(kData));
  }
  
  config = ConfigManager(configPath);
  
  // Prepare counters and histograms
  float bins[] = { 0, 2, 3, 4, 5, 6, 8, 10, 13, 20 };
  
  for(auto name : histParams){
    hists[name]         = new TH1D( name.c_str()        ,  name.c_str()        , 9, bins);
    hists[name+"_num"]  = new TH1D((name+"_num").c_str(), (name+"_num").c_str(), 9, bins);
    hists[name+"_den"]  = new TH1D((name+"_den").c_str(), (name+"_den").c_str(), 9, bins);
    hists[name+"_num"]->Sumw2();
    hists[name+"_den"]->Sumw2();
    
    cutThroughHists[name] = new TH1D(("cut_through_"+name).c_str(), ("cut_through_"+name).c_str(), 10, 0, 10);
    nEvents[name] = make_pair(0, 0);
  }
  
  // Loop over events
  for(int iEvent=0; iEvent<eventProcessor->GetNevents(); iEvent++){
    if(iEvent%10000 == 0) cout<<"Processing event "<<iEvent<<endl;
    if(iEvent >= config.params["maxEvents"]) break;
    
    auto event = eventProcessor->GetEvent(iEvent);
    
    if(doRecoEfficiency)  CheckRecoEfficiency(*event);
    if(doCHEefficiency)   CheckCHEefficiency(*event);
    if(doNEEefficiency)   CheckNEEefficiency(*event);
  }
  
  // Print the results and save histograms
  cout<<"\n\n------------------------------------------------------------------------"<<endl;

  TFile *outFile = new TFile(argc==4 ? argv[3]  : "results/efficienciesQED.root", "recreate");
  outFile->cd();
  
  for(auto name : histParams){
    hists[name]->Divide(hists[name+"_num"], hists[name+"_den"], 1, 1, "B");
    hists[name]->Write();
    hists[name+"_num"]->Write();
    hists[name+"_den"]->Write();
    cutThroughHists[name]->Write();
    
    cout<<"N tags, probes "<<name<<": "<<nEvents[name].first<<", "<<nEvents[name].second<<endl;
    cout<<name<<" efficiency: "; PrintEfficiency(nEvents[name].second, nEvents[name].first);
  }
  
  outFile->Close();
  
  cout<<"------------------------------------------------------------------------\n\n"<<endl;
  
  return 0;
}

