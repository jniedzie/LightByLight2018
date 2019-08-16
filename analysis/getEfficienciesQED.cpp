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
string outputPath = "results/efficienciesQED_test.root";

vector<EDataset> datasetsToAnalyze = { kData , kMCqedSC, kMCqedSL };

bool doRecoEfficiency    = true;
bool doTriggerEfficiency = false;
bool doCHEefficiency     = false;
bool doNEEefficiency     = false;

vector<string> histParams = {
  "reco_id_eff", "trigger_eff", "charged_exclusivity_eff", "neutral_exclusivity_eff",
};

/// Counts number of events passing tag and probe criteria for reco+ID efficiency
void CheckRecoEfficiency(Event &event,
                         map<string, pair<int, int>> &nEvents,
                         map<string, TH1D*> &hists,
                         map<string, TH1D*> &cutThroughHists,
                         string datasetName)
{
  string name = "reco_id_eff"+datasetName;
  int cutLevel = 0;
  cutThroughHists[name]->Fill(cutLevel++);
  
  // Check trigger
  if(!event.HasSingleEG3Trigger()) return;
  cutThroughHists[name]->Fill(cutLevel++);
  
  auto goodElectrons = event.GetGoodElectrons();
  
  // Preselect events with one electron and one extra track not reconstructed as an electron
  if(goodElectrons.size() != 1 || event.GetNgeneralTracks() != 2) return;
  cutThroughHists[name]->Fill(cutLevel++);
  
  // Get objects
  auto electron   = goodElectrons[0];
  auto track1     = event.GetGeneralTrack(0);
  auto track2     = event.GetGeneralTrack(1);
  
  // Check electron cuts
  cutThroughHists[name]->Fill(cutLevel++);
      
  // Check if there is exactly one track matching electron
  double deltaR1 = physObjectProcessor.GetDeltaR(*electron, *track1);
  double deltaR2 = physObjectProcessor.GetDeltaR(*electron, *track2);
  
  shared_ptr<PhysObject> matchingTrack = nullptr;
  shared_ptr<PhysObject> bremTrack     = nullptr;
  
  if(deltaR1 < 0.3 && deltaR2 > 0.3){
    matchingTrack = track1;
    bremTrack     = track2;
  }
  if(deltaR1 > 0.3 && deltaR2 < 0.3){
    matchingTrack = track2;
    bremTrack     = track1;
  }
      
  if(!matchingTrack) return;
  cutThroughHists[name]->Fill(cutLevel++);
        
        // Make sure that tracks have opposite charges and that brem track has low momentum
  if(bremTrack->GetCharge() == electron->GetCharge() || bremTrack->GetPt() > 2.0) return;
  cutThroughHists[name]->Fill(cutLevel++);
          
  // Count this event as a tag
  hists[name+"_den"]->Fill(1);
  nEvents[name].first++;
          
  // Check that there's exactly one photon passing ID cuts
  if(event.GetGoodPhotons().size() == 1){
    cutThroughHists[name]->Fill(cutLevel++);
            
    // Count this event as a probe
    hists[name+"_num"]->Fill(1);
    nEvents[name].second++;
  }
}

/// Counts number of events passing tag and probe criteria for trigger efficiency
void CheckTriggerEfficiency(Event &event,
                            map<string, pair<int, int>> &nEvents,
                            map<string, TH1D*> &hists,
                            map<string, TH1D*> &cutThroughHists,
                            string datasetName)
{
  string name = "trigger_eff"+datasetName;
  
  if(!event.HasSingleEG3Trigger()) return;
  cutThroughHists[name]->Fill(1);
  
  auto goodElectrons = event.GetGoodElectrons();
  
  if(goodElectrons.size() != 2) return;
  cutThroughHists[name]->Fill(2);
  
  if(event.HasAdditionalTowers()) return;
  cutThroughHists[name]->Fill(3);
        
  if(event.GetNchargedTracks() != 2) return;
  cutThroughHists[name]->Fill(4);
    
  auto electron1 = goodElectrons[0];
  auto electron2 = goodElectrons[1];
  
  shared_ptr<PhysObject> tag;
  shared_ptr<PhysObject> probe;
  
  for(auto &tower : event.GetCaloTowers()){
    if(tower->GetEt() < 5.0) continue;
    
    double deltaR1 = physObjectProcessor.GetDeltaR(*electron1, *tower);
    double deltaR2 = physObjectProcessor.GetDeltaR(*electron2, *tower);
    
    if(deltaR1 < 0.1 && electron2->GetEt() > 2.0){
      tag   = electron1;
      probe = electron2;
      break;
    }
    
    if(deltaR2 < 0.1 && electron1->GetEt() > 2.0){
      tag   = electron2;
      probe = electron1;
      break;
    }
  }
  
  if(!tag) return;
  cutThroughHists[name]->Fill(4);

}

/// Counts number of events passing tag and probe criteria for charged exclusivity efficiency
void CheckCHEefficiency(Event &event,
                        map<string, pair<int, int>> &nEvents,
                        map<string, TH1D*> &hists,
                        map<string, TH1D*> &cutThroughHists,
                        string datasetName)
{
  string name = "charged_exclusivity_eff"+datasetName;
  int cutLevel = 0;
  
  if(!event.HasLbLTrigger()) return;
  cutThroughHists[name]->Fill(cutLevel++); // 0
  
  auto goodElectrons = event.GetGoodElectrons();
  if(goodElectrons.size() < 2) return;
  cutThroughHists[name]->Fill(cutLevel++); // 1
      
  int nPositiveElectrons = 0;
  int nNegativeElectrons = 0;
  
  for(auto &electron : goodElectrons){
    if(electron->GetCharge() > 0) nPositiveElectrons++;
    if(electron->GetCharge() < 0) nNegativeElectrons++;
  }
      
  if(nPositiveElectrons < 1 || nNegativeElectrons < 1) return;
  cutThroughHists[name]->Fill(cutLevel++); // 2
  hists[name+"_den"]->Fill(1);
  nEvents[name].first++;
        
  if(event.GetNchargedTracks() == 2){
    cutThroughHists[name]->Fill(cutLevel++); // 3
    hists[name+"_num"]->Fill(1);
    nEvents[name].second++;
  }
}

/// Counts number of events passing tag and probe criteria for neutral exclusivity efficiency
void CheckNEEefficiency(Event &event,
                        map<string, pair<int, int>> &nEvents,
                        map<string, TH1D*> &hists,
                        map<string, TH1D*> &cutThroughHists,
                        string datasetName)
{
  string name = "neutral_exclusivity_eff"+datasetName;
  int cutLevel = 0;
  
  if(!event.HasLbLTrigger()) return;
  cutThroughHists[name]->Fill(cutLevel++); // 0
  
  // Check that there are exaclty two electrons
  auto goodElectrons = event.GetGoodElectrons();
  if(goodElectrons.size() != 2) return;
  cutThroughHists[name]->Fill(cutLevel++); // 1
  
  auto electron1 = goodElectrons[0];
  auto electron2 = goodElectrons[1];
  
  // Check if electrons have opposite charges
  // Check number of missing hits and H/E
  if(electron1->GetCharge() == electron2->GetCharge()) return;
  cutThroughHists[name]->Fill(cutLevel++); // 2
  
  if(electron1->GetNmissingHits() == 0  || electron2->GetNmissingHits() == 0) return;
  cutThroughHists[name]->Fill(cutLevel++); // 3
  
  if(electron1->GetHoverE() < 0.02      || electron2->GetHoverE() < 0.02) return;
  cutThroughHists[name]->Fill(cutLevel++); // 4
  
  TLorentzVector dielectron = physObjectProcessor.GetObjectsSum(*electron1, *electron2);
        
  // Check dielectron properties
  if(dielectron.M() < 5.0 || dielectron.Pt() > 1.0 || fabs(dielectron.Eta()) > 2.4) return;
  cutThroughHists[name]->Fill(cutLevel++); // 5
          
          
  // ...
  // missing: |η(SC)| < 2.4 except |η(SC)| ∈ [1.4442, 1.566]
  // missing: iso(rel,Ecal)< 0.3, iso(rel,Hcal)< 0.2, iso(rel,trk)< 0.05
  
  hists[name+"_den"]->Fill(1);
  nEvents[name].first++;
  
  if(event.GetNchargedTracks() == 2){
    cutThroughHists[name]->Fill(cutLevel++); // 6
    hists[name+"_num"]->Fill(1);
    nEvents[name].second++;
  }
}

int main(int argc, char* argv[])
{
  if(argc != 1 && argc != 6){
    cout<<"This app requires 0 or 5 parameters."<<endl;
    cout<<"./getEfficienciesData configPath inputPathData inputPathQED_SC inputPathQED_SL outputPath"<<endl;
    exit(0);
  }
  
  map<EDataset, string> inputPaths;
  
  if(argc == 6){
    configPath           = argv[1];
    inputPaths[kData]    = argv[2];
    inputPaths[kMCqedSC] = argv[3];
    inputPaths[kMCqedSL] = argv[4];
    outputPath           = argv[5];
  }
  config = ConfigManager(configPath);
  
  float bins[] = { 0, 2, 3, 4, 5, 6, 8, 10, 13, 20 };
  
  map<string, pair<int, int>> nEvents; ///< N events passing tag/probe criteria
  map<string, TH1D*> cutThroughHists;
  map<string, TH1D*> hists;
  
  TFile *outFile = new TFile(outputPath.c_str(), "recreate");
  
  for(EDataset dataset : datasetsToAnalyze){
    
    string name = datasetName.at(dataset);
    
    for(auto histName : histParams){
      string title = histName+name;
      
      hists[title]         = new TH1D( title.c_str()        ,  title.c_str()        , 9, bins);
      hists[title+"_num"]  = new TH1D((title+"_num").c_str(), (title+"_num").c_str(), 9, bins);
      hists[title+"_den"]  = new TH1D((title+"_den").c_str(), (title+"_den").c_str(), 9, bins);
      hists[title+"_num"]->Sumw2();
      hists[title+"_den"]->Sumw2();
      
      cutThroughHists[title] = new TH1D(("cut_through_"+title).c_str(), ("cut_through_"+title).c_str(), 10, 0, 10);
      nEvents[title] = make_pair(0, 0);
    }
    
    
    unique_ptr<EventProcessor> events;
    if(argc == 6){
      events = unique_ptr<EventProcessor>(new EventProcessor(inputPaths[dataset]));
    }
    else{
      events = unique_ptr<EventProcessor>(new EventProcessor(dataset));
    }

    // Loop over events
    for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
      if(iEvent%10000 == 0) cout<<"Processing event "<<iEvent<<endl;
      if(iEvent >= config.params("maxEvents")) break;
      
      auto event = events->GetEvent(iEvent);
      
      if(doRecoEfficiency)      CheckRecoEfficiency(*event, nEvents, hists, cutThroughHists, name);
      if(doTriggerEfficiency)   CheckTriggerEfficiency(*event, nEvents, hists, cutThroughHists, name);
      if(doCHEefficiency)       CheckCHEefficiency(*event, nEvents, hists, cutThroughHists, name);
      if(doNEEefficiency)       CheckNEEefficiency(*event, nEvents, hists, cutThroughHists, name);
    }
  
    // Print the results and save histograms
    cout<<"\n\n------------------------------------------------------------------------"<<endl;

    outFile->cd();
  
    for(auto histName : histParams){
      string title = histName+name;
      
      hists[title]->Divide(hists[title+"_num"], hists[title+"_den"], 1, 1, "B");
      hists[title]->Write();
      hists[title+"_num"]->Write();
      hists[title+"_den"]->Write();
      cutThroughHists[title]->Write();
      
      cout<<"N tags, probes "<<title<<": "<<nEvents[title].first<<", "<<nEvents[title].second<<endl;
      cout<<title<<" efficiency: "; PrintEfficiency(nEvents[title].second, nEvents[title].first);
    }
    cout<<"------------------------------------------------------------------------\n\n"<<endl;
  }
  outFile->Close();

  return 0;
}

