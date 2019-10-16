//  getEfficienciesData
//
//  Created by Jeremi Niedziela on 24/07/2019.
//
//  Calculates QED efficiencies in MC and data, as defined in the Analysis Note

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"

string configPath = "configs/efficiencies.md";
string outputPath = "results/efficienciesQED_test.root";

// Only those datasets will be analyzed
const vector<EDataset> datasetsToAnalyze = {
  kData ,
//  kMCqedSC,
//  kMCqedSL
};

// Select which efficiencies to calculate
bool doRecoEfficiency    = true;
bool doTriggerEfficiency = false;
bool doCHEefficiency     = false;
bool doNEEefficiency     = false;

// Names of efficiency histograms to create and save
vector<string> histParams = {
  "reco_id_eff", "trigger_eff", "trigger_HFveto_eff", "charged_exclusivity_eff", "neutral_exclusivity_eff",
};


map<string, int> matched;
map<string, float> acoplanarity;
map<string, float> SCEt;
map<string, float> absEta;

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
  
  // Check if the electron is also matched with one of the L1 EG objects
  bool foundMatchingL1EG = false;
  for(auto &L1EG : event.GetL1EGs()){
    if(physObjectProcessor.GetDeltaR(*electron, *L1EG) < 0.3){
      foundMatchingL1EG = true;
      break;
    }
  }
  if(!foundMatchingL1EG) return;
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
                            map<string, TTree*> &trees,
                            map<string, TH1D*> &cutThroughHists,
                            string datasetName)
{
  string name = "trigger_eff"+datasetName;
  int cutLevel = 0;
  cutThroughHists[name]->Fill(cutLevel++);
  
  // Check trigger
  if(!event.HasSingleEG3Trigger()) return;
  cutThroughHists[name]->Fill(cutLevel++);
  
  // Neutral exclusivity
  if(event.HasAdditionalTowers()) return;
  cutThroughHists[name]->Fill(cutLevel++);
  
  // Preselect events with exactly two electrons
  auto goodElectrons = event.GetGoodElectrons();
  if(goodElectrons.size() != 2) return;
  cutThroughHists[name]->Fill(cutLevel++);
  
  // Charged exclusivity
  if(event.GetNchargedTracks() != 2) return;
  cutThroughHists[name]->Fill(cutLevel++);
  
  // Tag and probe
  auto electron1 = goodElectrons[0];
  auto electron2 = goodElectrons[1];
  
  shared_ptr<PhysObject> tag = nullptr;
  shared_ptr<PhysObject> passingProbe = nullptr;
  shared_ptr<PhysObject> failedProbe = nullptr;
  
  // Replace by L1 EG !!!
  for(auto &tower : event.GetCaloTowers()){
    if(tag && passingProbe) break;
    
    double deltaR1 = physObjectProcessor.GetDeltaR(*electron1, *tower);
    double deltaR2 = physObjectProcessor.GetDeltaR(*electron2, *tower);
    
    if(deltaR1 < 1.0){
      if(!tag && tower->GetEt() > 3.0) tag = electron1;
      else if(tower->GetEt() > 2.0) passingProbe = electron1;
    }
    
    if(deltaR2 < 1.0){
      if(!tag && tower->GetEt() > 3.0) tag = electron2;
      else if(tower->GetEt() > 2.0) passingProbe = electron2;
    }
  }
  
  if(!tag) return;
  cutThroughHists[name]->Fill(cutLevel++);
  
  acoplanarity.at(datasetName) = physObjectProcessor.GetAcoplanarity(*electron1, *electron2);
  
  if(passingProbe){
    matched.at(datasetName) = 1;
    SCEt.at(datasetName) = passingProbe->GetPt();
    //  SCEt.at(datasetName) = probe->GetEtSC();
    absEta.at(datasetName) = fabs(passingProbe->GetEta());
    
  }
  else{
    if(tag == electron1) failedProbe = electron2;
    else                 failedProbe = electron1;
    
    matched.at(datasetName) = 0;
    SCEt.at(datasetName) = failedProbe->GetPt();
    //  SCEt.at(datasetName) = probe->GetEtSC();
    absEta.at(datasetName) = fabs(failedProbe->GetEta());
    
  }
  trees.at(datasetName)->Fill();
}

void CheckTriggerHFvetoEfficiency(Event &event,
                                  map<string, pair<int, int>> &nEvents,
                                  map<string, TH1D*> &hists,
                                  map<string, TH1D*> &cutThroughHists,
                                  string datasetName)
{
  string name = "trigger_HFveto_eff"+datasetName;
  int cutLevel = 0;
  cutThroughHists[name]->Fill(cutLevel++);
  
  // Check trigger with no HF veto
  if(!event.HasSingleEG3noHFvetoTrigger()) return;
  cutThroughHists[name]->Fill(cutLevel++);
  
  // Neutral exclusivity
  if(event.HasAdditionalTowers()) return;
  cutThroughHists[name]->Fill(cutLevel++);
  
  // Preselect events with exactly two electrons
  auto goodElectrons = event.GetGoodElectrons();
  if(goodElectrons.size() != 2) return;
  cutThroughHists[name]->Fill(cutLevel++);
  
  // Opposite charges
  auto electron1 = goodElectrons[0];
  auto electron2 = goodElectrons[1];
  if(electron1->GetCharge() == electron2->GetCharge()) return;
  cutThroughHists[name]->Fill(cutLevel++);
  
  // Charged exclusivity
  if(event.GetNchargedTracks() != 2) return;
  cutThroughHists[name]->Fill(cutLevel++);
  
  // Check if there are two electrons matched with L1 objects
  vector<shared_ptr<PhysObject>> matchedElectrons;
  
  // Replace by L1 EG !!!
  for(auto &tower : event.GetCaloTowers()){
    if(matchedElectrons.size() == 2) break;
    if(tower->GetEt() < 2.0) continue;
    
    double deltaR1 = physObjectProcessor.GetDeltaR(*electron1, *tower);
    double deltaR2 = physObjectProcessor.GetDeltaR(*electron2, *tower);
    
    if(deltaR1 < 1.0) matchedElectrons.push_back(electron1);
    if(deltaR2 < 1.0) matchedElectrons.push_back(electron2);
  }
  
  if(matchedElectrons.size() != 2) return;
  cutThroughHists[name]->Fill(cutLevel++);
  
  nEvents[name].first++;
  hists[name+"_den"]->Fill(1);
  
  // Check if it also has double EG2 trigger
  if(!event.HasDoubleEG2Trigger()) return;
  
  nEvents[name].second++;
  hists[name+"_num"]->Fill(1);
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
  cutThroughHists[name]->Fill(cutLevel++);
  
  if(!event.HasDoubleEG2Trigger()) return;
  cutThroughHists[name]->Fill(cutLevel++);
  
  // Check that there are exaclty two electrons
  auto goodElectrons = event.GetGoodElectrons();
  if(goodElectrons.size() != 2) return;
  cutThroughHists[name]->Fill(cutLevel++);
  
  auto electron1 = goodElectrons[0];
  auto electron2 = goodElectrons[1];
  
  // Check dielectron properties
  if(electron1->GetCharge() == electron2->GetCharge()) return;
  cutThroughHists[name]->Fill(cutLevel++);

  TLorentzVector dielectron = physObjectProcessor.GetObjectsSum(*electron1, *electron2);
  if(dielectron.M() < 5.0 || dielectron.Pt() > 1.0 || fabs(dielectron.Eta()) > 2.3) return;
  cutThroughHists[name]->Fill(cutLevel++);
  hists[name+"_den"]->Fill(1);
  nEvents[name].first++;
  
  // Charged exclusivity
  if(event.GetNchargedTracks() != 2) return;
  cutThroughHists[name]->Fill(cutLevel++);
  hists[name+"_num"]->Fill(1);
  nEvents[name].second++;
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
  cutThroughHists[name]->Fill(cutLevel++);
  
  if(!event.HasDoubleEG2Trigger()) return;
  cutThroughHists[name]->Fill(cutLevel++);
  
  // Check that there are exaclty two electrons
  auto goodElectrons = event.GetGoodElectrons();
  if(goodElectrons.size() != 2) return;
  cutThroughHists[name]->Fill(cutLevel++);
  
  auto electron1 = goodElectrons[0];
  auto electron2 = goodElectrons[1];
  
  // Opposite charges
  if(electron1->GetCharge() == electron2->GetCharge()) return;
  cutThroughHists[name]->Fill(cutLevel++);
  
  // Check dielectron properties
  TLorentzVector dielectron = physObjectProcessor.GetObjectsSum(*electron1, *electron2);
  if(dielectron.M() < 5.0 || dielectron.Pt() > 1.0 || fabs(dielectron.Eta()) > 2.4) return;
  cutThroughHists[name]->Fill(cutLevel++);
  
  // Charged exclusivity
  if(event.GetNchargedTracks() != 2) return;
  cutThroughHists[name]->Fill(cutLevel++);
  hists[name+"_den"]->Fill(1);
  nEvents[name].first++;
  
  // Neutral exclusivity
  if(event.HasAdditionalTowers()) return;
  cutThroughHists[name]->Fill(cutLevel++);
  hists[name+"_num"]->Fill(1);
  nEvents[name].second++;
}

/// Creates output trigger tree that will store information about matching, acoplanarity etc.
void InitializeTriggerTrees(map<string, TTree*> &triggerTrees, const string &name)
{
  triggerTrees[name] = new TTree("tree","");
  matched[name]      = 0;
  acoplanarity[name] = -1.0;
  SCEt[name]         = -1.0;
  absEta[name]       = -1.0;
  triggerTrees[name]->Branch("matched",       &matched[name]      , "matched/I"       );
  triggerTrees[name]->Branch("acoplanarity",  &acoplanarity[name] , "acoplanarity/F"  );
  triggerTrees[name]->Branch("SCEt",          &SCEt[name]         , "SCEt/F"          );
  triggerTrees[name]->Branch("abseta",        &absEta[name]       , "abseta/F"        );
}

/// Creates histograms, cut through and event counters for given dataset name, for each
/// histogram specified in `histParams` vector.
void InitializeHistograms(map<string, TH1D*> &hists,
                          map<string, TH1D*> &cutThroughHists,
                          map<string, pair<int, int>> &nEvents,
                          const string &name)
{
  float bins[] = { 0, 2, 3, 4, 5, 6, 8, 10, 13, 20 };
  
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
}

/// Prints the results and saves histograms to file
void PrintAndSaveResults(TFile *outFile,
                         map<string, TH1D*> &hists,
                         const map<string, TH1D*> &cutThroughHists,
                         const map<string, pair<int, int>> &nEvents,
                         const map<string, TTree*> &triggerTrees,
                         const string &name)
{
  cout<<"\n\n------------------------------------------------------------------------"<<endl;
  outFile->cd();
  
  for(auto histName : histParams){
    string title = histName+name;
    
    hists[title]->Divide(hists[title+"_num"], hists[title+"_den"], 1, 1, "B");
    hists[title]->Write();
    hists[title+"_num"]->Write();
    hists[title+"_den"]->Write();
    cutThroughHists.at(title)->Write();
    
    cout<<"N tags, probes "<<title<<": "<<nEvents.at(title).first<<", "<<nEvents.at(title).second<<endl;
    cout<<title<<" efficiency: "; PrintEfficiency(nEvents.at(title).second, nEvents.at(title).first);
  }
  
  outFile->cd(("triggerTree_"+name).c_str());
  triggerTrees.at(name)->Write();
  
  cout<<"------------------------------------------------------------------------\n\n"<<endl;
}

/// Checks that number of arguments provided is correct and sets corresponding variables
void ReadInputArguments(int argc, char* argv[], map<EDataset, string> &inputPaths)
{
  if(argc != 1 && argc != 6){
    cout<<"This app requires 0 or 5 parameters."<<endl;
    cout<<"./getEfficienciesData configPath inputPathData inputPathQED_SC inputPathQED_SL outputPath"<<endl;
    exit(0);
  }
  if(argc == 6){
    configPath           = argv[1];
    inputPaths[kData]    = argv[2];
    inputPaths[kMCqedSC] = argv[3];
    inputPaths[kMCqedSL] = argv[4];
    outputPath           = argv[5];
  }
}

/// Application starting point
int main(int argc, char* argv[])
{
  config = ConfigManager(configPath);
  
  map<EDataset, string> inputPaths;
  ReadInputArguments(argc, argv, inputPaths);
  
  map<string, pair<int, int>> nEvents; ///< N events passing tag/probe criteria
  map<string, TH1D*> cutThroughHists;
  map<string, TH1D*> hists;
  map<string, TTree*> triggerTrees;
  
  TFile *outFile = new TFile(outputPath.c_str(), "recreate");
  
  // Loop over all required datasets
  for(EDataset dataset : datasetsToAnalyze){
    string name = datasetName.at(dataset);
    outFile->mkdir(("triggerTree_"+name).c_str());
    
    InitializeTriggerTrees(triggerTrees, name);
    InitializeHistograms(hists, cutThroughHists, nEvents, name);
    
    unique_ptr<EventProcessor> events;
    if(argc == 6) events = unique_ptr<EventProcessor>(new EventProcessor(inputPaths[dataset]));
    else          events = unique_ptr<EventProcessor>(new EventProcessor(dataset));

    // Loop over events
    for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
      if(iEvent%10000 == 0) cout<<"Processing event "<<iEvent<<endl;
      if(iEvent >= config.params("maxEvents")) break;
      
      auto event = events->GetEvent(iEvent);
      
      if(doRecoEfficiency)      CheckRecoEfficiency(*event, nEvents, hists, cutThroughHists, name);
      if(doTriggerEfficiency){
        CheckTriggerEfficiency(*event, triggerTrees, cutThroughHists, name);
        CheckTriggerHFvetoEfficiency(*event, nEvents, hists, cutThroughHists, name);
      }
      if(doCHEefficiency)       CheckCHEefficiency(*event, nEvents, hists, cutThroughHists, name);
      if(doNEEefficiency)       CheckNEEefficiency(*event, nEvents, hists, cutThroughHists, name);
    }
  
    PrintAndSaveResults(outFile, hists, cutThroughHists, nEvents, triggerTrees, name);
  }
  outFile->Close();

  return 0;
}

