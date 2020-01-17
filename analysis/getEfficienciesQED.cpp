//  getEfficienciesData
//
//  Created by Jeremi Niedziela on 24/07/2019.
//
//  Calculates QED efficiencies in MC and data, as defined in the Analysis Note

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"
#include "EventDisplay.hpp"

string configPath = "configs/efficiencies.md";
//string configPath = "/afs/cern.ch/work/j/jniedzie/private/LightByLight2018/analysis/configs/efficiencies.md";
string outputPath = "results/efficienciesQED_test.root";

// Only those datasets will be analyzed
const vector<EDataset> datasetsToAnalyze = {
  kData,
//  kMCqedSC_SingleEG3,
  kMCqedSC_recoEff,
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
  "reco_id_eff", "reco_id_eff_vs_pt", "reco_id_eff_vs_eta",
  "trigger_eff", "trigger_HFveto_eff", "charged_exclusivity_eff", "neutral_exclusivity_eff",
  "ele_acoplanarity", "brem_track_pt"
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
                         map<string, TH1D*> &monitorHists,
                         string datasetName)
{
  string name = "reco_id_eff"+datasetName;
  int cutLevel = 0;
  cutThroughHists[name]->Fill(cutLevel++); // 0
  
  // Check trigger
  if(!event.HasSingleEG3Trigger()) return;
  cutThroughHists[name]->Fill(cutLevel++); // 1
  
  // Preselect events with exactly two tracks
  if(event.GetNgeneralTracks() != 2) return;
  cutThroughHists[name]->Fill(cutLevel++); // 2
  
  // Make sure that tracks have opposite charges and that brem track has low momentum
  auto track1 = event.GetGeneralTrack(0);
  auto track2 = event.GetGeneralTrack(1);
  if(track1->GetCharge() == track2->GetCharge()) return;
  cutThroughHists[name]->Fill(cutLevel++); // 3
  
  double estimatedPhotonEt = fabs(track1->GetPt()-track2->GetPt());
//  if(estimatedPhotonEt < 2.0) return;
  cutThroughHists[name]->Fill(cutLevel++); // 4
  
  // Check if there is one good electron matched with L1EG
  vector<shared_ptr<PhysObject>> goodMatchedElectrons;
  auto goodElectrons = event.GetGoodElectrons();
  
  for(auto electron : goodElectrons){
    for(auto &L1EG : event.GetL1EGs()){
      if(L1EG->GetEt() < 5.0) continue;
      
      if(physObjectProcessor.GetDeltaR_SC(*electron, *L1EG) < 0.3){
        goodMatchedElectrons.push_back(electron);
        break;
      }
    }
  }
  
  if(goodMatchedElectrons.size() != 1) return;
  auto theElectron = goodMatchedElectrons[0];
  cutThroughHists[name]->Fill(cutLevel++); // 5
  
  // Find tracks that match electrons
  vector<shared_ptr<PhysObject>> matchingTracks;
  vector<shared_ptr<PhysObject>> bremTracks;
  
  for(auto track : event.GetGeneralTracks()){
    if(physObjectProcessor.GetDeltaR(*theElectron, *track) < 0.3) matchingTracks.push_back(track);
    else                                                          bremTracks.push_back(track);
  }
  
  // Check that only one track matches the electron
  if(matchingTracks.size() != 1 || bremTracks.size() != 1) return;
  auto matchingTrack  = matchingTracks[0];
  auto bremTrack      = bremTracks[0];
  cutThroughHists[name]->Fill(cutLevel++); // 6
  
  // Check separation between brem track and photon:
//  if(fabs(2*bremTrack->GetPt()-matchingTrack->GetPt()) < 2.0) return;
  
  if(bremTrack->GetPt() < 2.0) return;
  cutThroughHists[name]->Fill(cutLevel++); // 7
  
  // Count this event as a tag
  hists[name+"_den"]->Fill(1);
  hists["reco_id_eff_vs_pt"+datasetName+"_den"]->Fill(estimatedPhotonEt);
  hists["reco_id_eff_vs_eta"+datasetName+"_den"]->Fill(fabs(matchingTracks[0]->GetEta()));
  nEvents[name].first++;
  
  hists["ele_acoplanarity"+datasetName+"_den"]->Fill(physObjectProcessor.GetAcoplanarity(*matchingTrack, *bremTrack));
  hists["brem_track_pt"+datasetName+"_den"]->Fill(bremTrack->GetPt());
  
//   Count number of photons that are far from good, matched electrons
  auto photons = event.GetGoodPhotons();
//  auto photons = event.GetPhotons();
  int nBremPhotons = 0;
  
  for(auto photon : photons){
    if(physObjectProcessor.GetDeltaR_SC(*theElectron, *photon) > 0.3) nBremPhotons++;
  }
  
  // Check that there's exactly one photon passing ID cuts
  if(nBremPhotons > 0){
    cutThroughHists[name]->Fill(cutLevel++); // 8
    
    // Count this event as a probe
    hists[name+"_num"]->Fill(1);
    hists["reco_id_eff_vs_pt"+datasetName+"_num"]->Fill(estimatedPhotonEt);
    hists["reco_id_eff_vs_eta"+datasetName+"_num"]->Fill(fabs(matchingTracks[0]->GetEta()));
    nEvents[name].second++;
  }
  else{
    auto allPhotons = event.GetPhotons();
//    saveEventDisplay(matchingTracks, bremTracks, goodMatchedElectrons, photons, allPhotons, "~/Desktop/lbl_event_displays_"+datasetName+"/");
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
  cutThroughHists[name]->Fill(cutLevel++); // 0
  
  // Check trigger
  if(!event.HasSingleEG3Trigger()) return;
  cutThroughHists[name]->Fill(cutLevel++); // 1
  
  // Neutral exclusivity
  if(event.HasAdditionalTowers()) return;
  cutThroughHists[name]->Fill(cutLevel++); // 2
  
  // Preselect events with exactly two electrons
  auto goodElectrons = event.GetGoodElectrons();
  if(goodElectrons.size() != 2) return;
  cutThroughHists[name]->Fill(cutLevel++); // 3
  
  // Charged exclusivity
  if(event.GetNchargedTracks() != 2) return;
  cutThroughHists[name]->Fill(cutLevel++); // 4
  
  // Tag and probe
  auto electron1 = goodElectrons[0];
  auto electron2 = goodElectrons[1];
  
  shared_ptr<PhysObject> tag = nullptr;
  shared_ptr<PhysObject> passingProbe = nullptr;
  shared_ptr<PhysObject> failedProbe = nullptr;
  
  for(auto &L1EG : event.GetL1EGs()){
    if(tag && passingProbe) break;
    
    double deltaR1 = physObjectProcessor.GetDeltaR_SC(*electron1, *L1EG);
    double deltaR2 = physObjectProcessor.GetDeltaR_SC(*electron2, *L1EG);
    
    if(deltaR1 < 1.0){
      if(!tag && L1EG->GetEt() > 3.0) tag = electron1;
      else if(L1EG->GetEt() > 2.0) passingProbe = electron1;
    }
    
    if(deltaR2 < 1.0){
      if(!tag && L1EG->GetEt() > 3.0) tag = electron2;
      else if(L1EG->GetEt() > 2.0) passingProbe = electron2;
    }
  }
  
  if(!tag) return;
  cutThroughHists[name]->Fill(cutLevel++); // 5
  
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
  cutThroughHists[name]->Fill(cutLevel++); // 0
  
  // Check trigger with no HF veto
  if(!event.HasSingleEG3noHFvetoTrigger()) return;
  cutThroughHists[name]->Fill(cutLevel++); // 1
  
  // Neutral exclusivity
  if(event.HasAdditionalTowers()) return;
  cutThroughHists[name]->Fill(cutLevel++); // 2
  
  // Preselect events with exactly two electrons
  auto goodElectrons = event.GetGoodElectrons();
  if(goodElectrons.size() != 2) return;
  cutThroughHists[name]->Fill(cutLevel++); // 3
  
  // Opposite charges
  auto electron1 = goodElectrons[0];
  auto electron2 = goodElectrons[1];
  if(electron1->GetCharge() == electron2->GetCharge()) return;
  cutThroughHists[name]->Fill(cutLevel++); // 4
  
  // Charged exclusivity
  if(event.GetNchargedTracks() != 2) return;
  cutThroughHists[name]->Fill(cutLevel++); // 5
  
  // Check if there are two electrons matched with L1 objects
  vector<shared_ptr<PhysObject>> matchedElectrons;
  
  // Check matching with L1 objects
  for(auto &L1EG : event.GetL1EGs()){
    if(matchedElectrons.size() == 2) break;
    if(L1EG->GetEt() < 2.0) continue;
    
    double deltaR1 = physObjectProcessor.GetDeltaR(*electron1, *L1EG);
    double deltaR2 = physObjectProcessor.GetDeltaR(*electron2, *L1EG);
    
    if(deltaR1 < 1.0) matchedElectrons.push_back(electron1);
    if(deltaR2 < 1.0) matchedElectrons.push_back(electron2);
  }
  
  if(matchedElectrons.size() != 2) return;
  cutThroughHists[name]->Fill(cutLevel++); // 6
  
  nEvents[name].first++;
  hists[name+"_den"]->Fill(1);
  
  // Check if it also has double EG2 trigger
  if(!event.HasDoubleEG2Trigger()) return;
  cutThroughHists[name]->Fill(cutLevel++); // 7
  
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
  cutThroughHists[name]->Fill(cutLevel++); // 0
  
  if(!event.HasDoubleEG2Trigger()) return;
  cutThroughHists[name]->Fill(cutLevel++); // 1
  
  // Check that there are exaclty two electrons
  auto goodElectrons = event.GetGoodElectrons();
  if(goodElectrons.size() != 2) return;
  cutThroughHists[name]->Fill(cutLevel++); // 2
  
  auto electron1 = goodElectrons[0];
  auto electron2 = goodElectrons[1];
  
  // Check dielectron properties
  if(electron1->GetCharge() == electron2->GetCharge()) return;
  cutThroughHists[name]->Fill(cutLevel++); // 3
  
  TLorentzVector dielectron = physObjectProcessor.GetObjectsSum(*electron1, *electron2);
  if(dielectron.M() < 5.0 || dielectron.Pt() > 1.0 || fabs(dielectron.Eta()) > 2.3) return;
  cutThroughHists[name]->Fill(cutLevel++); // 4
  hists[name+"_den"]->Fill(1);
  nEvents[name].first++;
  
  // Charged exclusivity
  if(event.GetNchargedTracks() != 2) return;
  cutThroughHists[name]->Fill(cutLevel++); // 5
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
  cutThroughHists[name]->Fill(cutLevel++); // 0
  
  if(!event.HasDoubleEG2Trigger()) return;
  cutThroughHists[name]->Fill(cutLevel++); // 1
  
  // Check that there are exaclty two electrons
  auto goodElectrons = event.GetGoodElectrons();
  if(goodElectrons.size() != 2) return;
  cutThroughHists[name]->Fill(cutLevel++); // 2
  
  auto electron1 = goodElectrons[0];
  auto electron2 = goodElectrons[1];
  
  // Opposite charges
  if(electron1->GetCharge() == electron2->GetCharge()) return;
  cutThroughHists[name]->Fill(cutLevel++); // 3
  
  // Check dielectron properties
  TLorentzVector dielectron = physObjectProcessor.GetObjectsSum(*electron1, *electron2);
  if(dielectron.M() < 5.0 || dielectron.Pt() > 1.0 || fabs(dielectron.Eta()) > 2.4) return;
  cutThroughHists[name]->Fill(cutLevel++); // 4
  
  // Charged exclusivity
  if(event.GetNchargedTracks() != 2) return;
  cutThroughHists[name]->Fill(cutLevel++); // 5
  hists[name+"_den"]->Fill(1);
  nEvents[name].first++;
  
  // Neutral exclusivity
  if(event.HasAdditionalTowers()) return;
  cutThroughHists[name]->Fill(cutLevel++); // 6
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
                          map<string, TH1D*> &monitorHists,
                          map<string, pair<int, int>> &nEvents,
                          const string &name)
{
  
  
  for(auto histName : histParams){
    string title = histName+name;
    
    vector<float> bins;
    
    if(histName.find("vs_pt") != string::npos){
      bins  = { 0, 2, 4, 6, 8, 20 };
    }
    else if(histName.find("vs_eta") != string::npos){
      bins  = { 0.5, 1.0, 1.5, 2.0 , 2.5 };
    }
    else if(histName.find("acoplanarity") != string::npos){
      bins  = { 0, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10 };
    }
    else if(histName.find("brem_track_pt") != string::npos){
      bins  = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20 };
    }
    else{
      bins = { 0, 2, 3, 4, 5, 6, 8, 10, 13, 20 };
    }
    
    float *binsArray = &bins[0];
    int nBins = (int)bins.size()-1;
    
    hists[title]         = new TH1D( title.c_str()        ,  title.c_str()        , nBins, binsArray);
    hists[title+"_num"]  = new TH1D((title+"_num").c_str(), (title+"_num").c_str(), nBins, binsArray);
    hists[title+"_den"]  = new TH1D((title+"_den").c_str(), (title+"_den").c_str(), nBins, binsArray);
    
    hists[title+"_num"]->Sumw2();
    hists[title+"_den"]->Sumw2();
    
    cutThroughHists[title] = new TH1D(("cut_through_"+title).c_str(), ("cut_through_"+title).c_str(), 10, 0, 10);
    
    monitorHists[title+"_nPhotons"] = new TH1D(("nPhotons_"+title).c_str(), ("nPhotons_"+title).c_str(), 10, 0, 10);
    monitorHists[title+"_photonsDeta"] = new TH1D(("photonsDeta_"+title).c_str(), ("photonsDeta_"+title).c_str(), 20, 0, 5);
    monitorHists[title+"_photonsDphi"] = new TH1D(("photonsDphi_"+title).c_str(), ("photonsDphi_"+title).c_str(), 20, 0, 7);
    
    nEvents[title] = make_pair(0, 0);
  }
}

/// Prints the results and saves histograms to file
void PrintAndSaveResults(TFile *outFile,
                         map<string, TH1D*> &hists,
                         const map<string, TH1D*> &cutThroughHists,
                         const map<string, TH1D*> &monitorHists,
                         const map<string, pair<int, int>> &nEvents,
                         const map<string, TTree*> &triggerTrees,
                         const string &name)
{
  cout<<"\n\n------------------------------------------------------------------------"<<endl;
  outFile->cd();
  
  for(auto histName : histParams){
    if(histName == "reco_id_eff" || histName == "reco_id_eff_vs_pt" || histName == "reco_id_eff_vs_eta"){
      if(!doRecoEfficiency) continue;
    }
    if(histName == "trigger_eff" || histName == "trigger_HFveto_eff"){
      if(!doTriggerEfficiency) continue;
    }
    if(histName == "charged_exclusivity_eff"){
      if(!doCHEefficiency) continue;
    }
    if(histName == "neutral_exclusivity_eff"){
      if(!doNEEefficiency) continue;
    }
    
    string title = histName+name;
    
    hists[title]->Divide(hists[title+"_num"], hists[title+"_den"], 1, 1, "B");
    hists[title]->Write();
    hists[title+"_num"]->Write();
    hists[title+"_den"]->Write();
    cutThroughHists.at(title)->Write();
    
    cout<<"N tags, probes "<<title<<": "<<nEvents.at(title).first<<", "<<nEvents.at(title).second<<endl;
    cout<<title<<" efficiency: "; PrintEfficiency(nEvents.at(title).second, nEvents.at(title).first);
  }
  
  for(auto &[name, hist] : monitorHists){
    hist->Write();
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
  map<string, TH1D*> monitorHists;
  map<string, TTree*> triggerTrees;
  
  TFile *outFile = new TFile(outputPath.c_str(), "recreate");
  
  // Loop over all required datasets
  for(EDataset dataset : datasetsToAnalyze){
    string name = datasetName.at(dataset);
    outFile->mkdir(("triggerTree_"+name).c_str());
    
    InitializeTriggerTrees(triggerTrees, name);
    InitializeHistograms(hists, cutThroughHists, monitorHists, nEvents, name);
    
    auto events = make_unique<EventProcessor>(argc == 6 ? inputPaths[dataset] : inFileNames.at(dataset));
    
    // Loop over events
    for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
      if(iEvent%1000 == 0) cout<<"Processing event "<<iEvent<<endl;
      if(iEvent >= config.params("maxEvents")) break;
      
      auto event = events->GetEvent(iEvent);
      
      if(doRecoEfficiency)      CheckRecoEfficiency(*event, nEvents, hists, cutThroughHists, monitorHists, name);
      if(doTriggerEfficiency){
        CheckTriggerEfficiency(*event, triggerTrees, cutThroughHists, name);
        CheckTriggerHFvetoEfficiency(*event, nEvents, hists, cutThroughHists, name);
      }
      if(doCHEefficiency)       CheckCHEefficiency(*event, nEvents, hists, cutThroughHists, name);
      if(doNEEefficiency)       CheckNEEefficiency(*event, nEvents, hists, cutThroughHists, name);
    }
    
    PrintAndSaveResults(outFile, hists, cutThroughHists, monitorHists, nEvents, triggerTrees, name);
  }
  outFile->Close();
  
  return 0;
}

