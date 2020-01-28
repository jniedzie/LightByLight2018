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
//  kData,
//  kData_SingleEG3,
  kData_recoEff,
//  kData_triggerEff,
//  kData_HFveto,
//  kData_exclusivity,
//  kData_LbLsignal,
//  kData_QEDsignal,
//  kMCqedSC,
//  kMCqedSC_SingleEG3,
  kMCqedSC_recoEff,
//  kMCqedSC_triggerEff,
//  kMCqedSC_HFveto,
//  kMCqedSC_exclusivity,
//  kMCqedSC_signal,
//  kMCqedSL
};

// Select which efficiencies to calculate
bool doRecoEfficiency    = true;
bool doTriggerEfficiency = false;
bool doHFvetoEfficiency  = false;
bool doCHEefficiency     = false;
bool doNEEefficiency     = false;

// Names of efficiency histograms to create and save
vector<string> histParams = {
  // reco+ID efficiency histograms
  "reco_id_eff_cut_through",
  "reco_id_eff_num",
  "reco_id_eff_den",
  "reco_id_eff_vs_pt_num",
  "reco_id_eff_vs_pt_den",
  "reco_id_eff_vs_eta_num",
  "reco_id_eff_vs_eta_den",
  "ele_acoplanarity",
  "brem_track_pt",
  "failingPhotonEt",
  "failingPhotonEta",
  "failingPhotonHEbarrel",
  "failingPhotonHEendcap",
  "failingPhotonSigmaBarrel",
  "failingPhotonSigmaEndcap",
  "delta_pt_tracks",
  "delta_phi_electron_photon",
  
  // trigger efficiency histograms
  "trigger_eff_cut_through",
  "trigger_HFveto_eff_cut_through",
  "trigger_HFveto_eff_num",
  "trigger_HFveto_eff_den",
  
  // exclusivity efficiency histograms
  "charged_exclusivity_eff_cut_through",
  "charged_exclusivity_eff_num",
  "charged_exclusivity_eff_den",
  "dielectron_mass",
  
  "neutral_exclusivity_eff_cut_through",
  "neutral_exclusivity_eff_num",
  "neutral_exclusivity_eff_den",
};


map<string, int> matched;
map<string, float> acoplanarity;
map<string, float> SCEt;
map<string, float> absEta;

/// Counts number of events passing tag and probe criteria for reco+ID efficiency
void CheckRecoEfficiency(Event &event, map<string, TH1D*> &hists, string datasetName)
{
  string cutThouthName = "reco_id_eff_cut_through_"+datasetName;
  int cutLevel = 0;
  hists[cutThouthName]->Fill(cutLevel++); // 0
  
  // Check trigger
  if(!event.HasSingleEG3Trigger()) return;
  hists[cutThouthName]->Fill(cutLevel++); // 1
  
  // Preselect events with exactly two tracks
  if(event.GetNgeneralTracks() != 2) return;
  hists[cutThouthName]->Fill(cutLevel++); // 2
  
  // Make sure that tracks have opposite charges and that brem track has low momentum
  auto track1 = event.GetGeneralTrack(0);
  auto track2 = event.GetGeneralTrack(1);
  if(track1->GetCharge() == track2->GetCharge()) return;
  hists[cutThouthName]->Fill(cutLevel++); // 3
  
  double estimatedPhotonEt = fabs(track1->GetPt()-track2->GetPt());
//  if(estimatedPhotonEt < 2.0) return;
  hists[cutThouthName]->Fill(cutLevel++); // 4
  
  // Check if there is one good electron matched with L1EG
  vector<shared_ptr<PhysObject>> goodMatchedElectrons;
  auto goodElectrons = event.GetGoodElectrons();
  
  for(auto electron : goodElectrons){
    if(electron->GetPt() < 5.0) continue;
    
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
  hists[cutThouthName]->Fill(cutLevel++); // 5
  
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
  hists[cutThouthName]->Fill(cutLevel++); // 6
  
  if(fabs(bremTrack->GetPt() - matchingTrack->GetPt()) > 4) return;
  
  // Check separation between brem track and photon:
//  if(fabs(2*bremTrack->GetPt()-matchingTrack->GetPt()) < 2.0) return;
  
//  if(bremTrack->GetPt() < 2.0) return;
  hists[cutThouthName]->Fill(cutLevel++); // 7
  
  // Count this event as a tag
  hists["reco_id_eff_den_"+datasetName]->Fill(1);
  hists["reco_id_eff_vs_pt_den_"+datasetName]->Fill(estimatedPhotonEt);
  hists["reco_id_eff_vs_eta_den_"+datasetName]->Fill(fabs(matchingTracks[0]->GetEta()));
  hists["ele_acoplanarity_"+datasetName]->Fill(physObjectProcessor.GetAcoplanarity(*matchingTrack, *bremTrack));
  hists["brem_track_pt_"+datasetName]->Fill(bremTrack->GetPt());
  hists["delta_pt_tracks_"+datasetName]->Fill(fabs(bremTrack->GetPt() - matchingTrack->GetPt()));
  
//   Count number of photons that are far from good, matched electrons
  auto photons = event.GetGoodPhotons();
//  auto photons = event.GetPhotons();
  int nBremPhotons = 0;
  
  for(auto photon : photons){
    if(physObjectProcessor.GetDeltaR_SC(*theElectron, *photon) > 0.3){
      nBremPhotons++;
      hists["delta_phi_electron_photon_"+datasetName]->Fill(fabs(theElectron->GetCharge()*theElectron->GetPhi() - photon->GetPhi()));
    }
  }
  
  // Check that there's exactly one photon passing ID cuts
  if(nBremPhotons > 0){
    hists[cutThouthName]->Fill(cutLevel++); // 8
    
    // Count this event as a probe
    hists["reco_id_eff_num_"+datasetName]->Fill(1);
    hists["reco_id_eff_vs_pt_num_"+datasetName]->Fill(estimatedPhotonEt);
    hists["reco_id_eff_vs_eta_num_"+datasetName]->Fill(fabs(matchingTracks[0]->GetEta()));
  }
  else{
    auto allPhotons = event.GetPhotons();
//    saveEventDisplay(matchingTracks, bremTracks, goodMatchedElectrons, photons, allPhotons, "~/Desktop/lbl_event_displays_"+datasetName+"/");
    
    for(auto photon : allPhotons){
      if(find(photons.begin(), photons.end(), photon) != photons.end()) continue; // this was a good photon
      if(physObjectProcessor.GetDeltaR_SC(*theElectron, *photon) < 0.3) continue; // this one it matched with electron
      
      double eta = fabs(photon->GetEta());
      
      hists["failingPhotonEt_"+datasetName]->Fill(photon->GetEt());
      hists["failingPhotonEta_"+datasetName]->Fill(eta);
      
      if(eta < maxEtaEB){
        hists["failingPhotonSigmaBarrel_"+datasetName]->Fill(photon->GetEtaWidth());
        hists["failingPhotonHEbarrel_"+datasetName]->Fill(photon->GetHoverE());
      }
      else{
        hists["failingPhotonSigmaEndcap_"+datasetName]->Fill(photon->GetEtaWidth());
        hists["failingPhotonHEendcap_"+datasetName]->Fill(photon->GetHoverE());
      }
    }
  }
}

/// Counts number of events passing tag and probe criteria for trigger efficiency
void CheckTriggerEfficiency(Event &event, map<string, TTree*> &trees, map<string, TH1D*> &hists, string datasetName)
{
  string cutThouthName = "trigger_eff_cut_through_"+datasetName;
  int cutLevel = 0;
  hists[cutThouthName]->Fill(cutLevel++); // 0
  
  // Check trigger
  if(!event.HasSingleEG3Trigger()) return;
  hists[cutThouthName]->Fill(cutLevel++); // 1
  
  // Neutral exclusivity
  if(event.HasAdditionalTowers()) return;
  hists[cutThouthName]->Fill(cutLevel++); // 2
  
  // Preselect events with exactly two electrons
  auto goodElectrons = event.GetGoodElectrons();
  if(goodElectrons.size() != 2) return;
  hists[cutThouthName]->Fill(cutLevel++); // 3
  
  // Charged exclusivity
  if(event.GetNchargedTracks() != 2) return;
  hists[cutThouthName]->Fill(cutLevel++); // 4
  
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
      if(!tag && L1EG->GetEt() > 5.0) tag = electron1;
      else if(L1EG->GetEt() > 2.0) passingProbe = electron1;
    }
    
    if(deltaR2 < 1.0){
      if(!tag && L1EG->GetEt() > 5.0) tag = electron2;
      else if(L1EG->GetEt() > 2.0) passingProbe = electron2;
    }
  }
  
  if(!tag) return;
  hists[cutThouthName]->Fill(cutLevel++); // 5
  
  acoplanarity.at(datasetName) = physObjectProcessor.GetAcoplanarity(*electron1, *electron2);
  
  if(passingProbe){
    matched.at(datasetName) = 1;
    SCEt.at(datasetName) = passingProbe->GetPt();
    absEta.at(datasetName) = fabs(passingProbe->GetEta());
  }
  else{
    if(tag == electron1) failedProbe = electron2;
    else                 failedProbe = electron1;
    
    matched.at(datasetName) = 0;
    SCEt.at(datasetName) = failedProbe->GetPt();
    absEta.at(datasetName) = fabs(failedProbe->GetEta());
  }
  trees.at(datasetName)->Fill();
}

void CheckTriggerHFvetoEfficiency(Event &event, map<string, TH1D*> &hists, string datasetName)
{
  string cutThouthName = "trigger_HFveto_eff_cut_through_"+datasetName;
  int cutLevel = 0;
  hists[cutThouthName]->Fill(cutLevel++); // 0
  
  // Check trigger with no HF veto
  if(!event.HasSingleEG3noHFvetoTrigger()) return;
  hists[cutThouthName]->Fill(cutLevel++); // 1
  
  // Neutral exclusivity
  if(event.HasAdditionalTowers()) return;
  hists[cutThouthName]->Fill(cutLevel++); // 2
  
  // Preselect events with exactly two electrons
  auto goodElectrons = event.GetGoodElectrons();
  if(goodElectrons.size() != 2) return;
  hists[cutThouthName]->Fill(cutLevel++); // 3
  
  // Opposite charges
  auto electron1 = goodElectrons[0];
  auto electron2 = goodElectrons[1];
  if(electron1->GetCharge() == electron2->GetCharge()) return;
  hists[cutThouthName]->Fill(cutLevel++); // 4
  
  // Charged exclusivity
  if(event.GetNchargedTracks() != 2) return;
  hists[cutThouthName]->Fill(cutLevel++); // 5
  
  // Check if there are two electrons matched with L1 objects
  vector<shared_ptr<PhysObject>> matchedElectrons;
  
  // Check matching with L1 objects
  for(auto &L1EG : event.GetL1EGs()){
    if(matchedElectrons.size() == 2) break;
    if(L1EG->GetEt() < 2.0) continue;
    
    double deltaR1 = physObjectProcessor.GetDeltaR_SC(*electron1, *L1EG);
    double deltaR2 = physObjectProcessor.GetDeltaR_SC(*electron2, *L1EG);
    
    if(deltaR1 < 1.0) matchedElectrons.push_back(electron1);
    if(deltaR2 < 1.0) matchedElectrons.push_back(electron2);
  }
  
  if(matchedElectrons.size() != 2) return;
  hists[cutThouthName]->Fill(cutLevel++); // 6
  hists["trigger_HFveto_eff_den_"+datasetName]->Fill(1);
  
  // Check if it also has double EG2 trigger
  if(!event.HasDoubleEG2Trigger()) return;
  hists[cutThouthName]->Fill(cutLevel++); // 7
  hists["trigger_HFveto_eff_num_"+datasetName]->Fill(1);
}

/// Counts number of events passing tag and probe criteria for charged exclusivity efficiency
void CheckCHEefficiency(Event &event, map<string, TH1D*> &hists, string datasetName)
{
  string cutThouthName = "charged_exclusivity_eff_cut_through_"+datasetName;
  int cutLevel = 0;
  hists[cutThouthName]->Fill(cutLevel++); // 0
  
  if(!event.HasDoubleEG2Trigger()) return;
  hists[cutThouthName]->Fill(cutLevel++); // 1
  
  // Check that there are exaclty two electrons
  auto goodElectrons = event.GetGoodElectrons();
  if(goodElectrons.size() != 2) return;
  hists[cutThouthName]->Fill(cutLevel++); // 2
  
  auto electron1 = goodElectrons[0];
  auto electron2 = goodElectrons[1];
  
  // Check dielectron properties
  if(electron1->GetCharge() == electron2->GetCharge()) return;
  hists[cutThouthName]->Fill(cutLevel++); // 3
  
  TLorentzVector dielectron = physObjectProcessor.GetDielectron(*electron1, *electron2);
  hists["dielectron_mass_"+datasetName]->Fill(dielectron.M());
  
  if(dielectron.M() < 5.0) return;
  hists[cutThouthName]->Fill(cutLevel++); // 4
  
  if(dielectron.Pt() > 1.0) return;
  hists[cutThouthName]->Fill(cutLevel++); // 5
  
  if(fabs(dielectron.Eta()) > 2.3) return;
  hists[cutThouthName]->Fill(cutLevel++); // 6
  
  
  hists["charged_exclusivity_eff_den_"+datasetName]->Fill(1);
  
  // Charged exclusivity
  if(event.GetNchargedTracks() != 2) return;
  hists[cutThouthName]->Fill(cutLevel++); // 5
  hists["charged_exclusivity_eff_num_"+datasetName]->Fill(1);
}

/// Counts number of events passing tag and probe criteria for neutral exclusivity efficiency
void CheckNEEefficiency(Event &event, map<string, TH1D*> &hists, string datasetName)
{
  string cutThouthName = "neutral_exclusivity_eff_cut_through_"+datasetName;
  int cutLevel = 0;
  hists[cutThouthName]->Fill(cutLevel++); // 0
  
  if(!event.HasDoubleEG2Trigger()) return;
  hists[cutThouthName]->Fill(cutLevel++); // 1
  
  // Check that there are exaclty two electrons
  auto goodElectrons = event.GetGoodElectrons();
  if(goodElectrons.size() != 2) return;
  hists[cutThouthName]->Fill(cutLevel++); // 2
  
  auto electron1 = goodElectrons[0];
  auto electron2 = goodElectrons[1];
  
  // Opposite charges
  if(electron1->GetCharge() == electron2->GetCharge()) return;
  hists[cutThouthName]->Fill(cutLevel++); // 3
  
  // Check dielectron properties
  TLorentzVector dielectron = physObjectProcessor.GetDielectron(*electron1, *electron2);
  if(dielectron.M() < 5.0 || dielectron.Pt() > 1.0 || fabs(dielectron.Eta()) > 2.3) return;
  hists[cutThouthName]->Fill(cutLevel++); // 4
  
  // Charged exclusivity
  if(event.GetNchargedTracks() != 2) return;
  hists[cutThouthName]->Fill(cutLevel++); // 5
  hists["neutral_exclusivity_eff_den_"+datasetName]->Fill(1);

  // Neutral exclusivity
  if(event.HasAdditionalTowers()) return;
  hists[cutThouthName]->Fill(cutLevel++); // 6
  hists["neutral_exclusivity_eff_num_"+datasetName]->Fill(1);
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
void InitializeHistograms(map<string, TH1D*> &hists, const string &datasetType)
{
  for(auto histName : histParams){
    string title = histName + "_" + datasetType;
    vector<float> bins;
    
    if(histName.find("vs_pt") != string::npos){
      bins  = { 0, 2, 4, 6, 8, 20 };
      hists[title] = new TH1D(title.c_str(), title.c_str(), (int)bins.size()-1, (float*)&bins[0]);
    }
    else if(histName.find("vs_eta") != string::npos){
      hists[title] = new TH1D(title.c_str(), title.c_str(), 5, 0.0, 2.5);
    }
    else if(histName == "failingPhotonEt"){
      hists[title] = new TH1D(title.c_str(), title.c_str(), 20, 0, 20);
    }
    else if(histName == "failingPhotonEta"){
      hists[title] = new TH1D(title.c_str(), title.c_str(), 20, 0, 5.0);
    }
    else if(histName == "failingPhotonHEbarrel"){
      hists[title] = new TH1D(title.c_str(), title.c_str(), 50, 0, 0.5);
    }
    else if(histName == "failingPhotonHEendcap"){
      hists[title] = new TH1D(title.c_str(), title.c_str(), 50, 0, 0.5);
    }
    else if(histName == "failingPhotonSigmaBarrel"){
      hists[title] = new TH1D(title.c_str(), title.c_str(), 50, 0, 0.2);
    }
    else if(histName == "failingPhotonSigmaEndcap"){
      hists[title] = new TH1D(title.c_str(), title.c_str(), 50, 0, 0.2);
    }
    else if(histName == "delta_pt_tracks"){
      hists[title] = new TH1D(title.c_str(), title.c_str(), 20, 0, 10);
    }
    else if(histName == "delta_phi_electron_photon"){
      hists[title] = new TH1D(title.c_str(), title.c_str(), 100, 0, 2*TMath::Pi());
    }
    else if(histName.find("acoplanarity") != string::npos){
      hists[title] = new TH1D(title.c_str(), title.c_str(), 10, 0, 0.1);
    }
    else if(histName.find("brem_track_pt") != string::npos){
      hists[title] = new TH1D(title.c_str(), title.c_str(), 30, 0, 10);
    }
    else if(histName.find("cut_through") != string::npos){
      hists[title] = new TH1D(title.c_str(), title.c_str(), 20, 0, 20);
    }
    else if(histName.find("dielectron_mass") != string::npos){
      hists[title] = new TH1D(title.c_str(), title.c_str(), 50, 0, 20);
    }
    else{
      bins = { 0, 2, 3, 4, 5, 6, 8, 10, 13, 20 };
      hists[title] = new TH1D(title.c_str(), title.c_str(), (int)bins.size()-1, (float*)&bins[0]);
    }
    
    hists[title]->Sumw2();
  }
}

/// Prints the results and saves histograms to file
void PrintAndSaveResults(TFile *outFile, map<string, TH1D*> &hists,
                         const map<string, TTree*> &triggerTrees, const string &datasetType)
{
  cout<<"\n\n------------------------------------------------------------------------"<<endl;
  outFile->cd();
  
  for(auto histName : histParams){
    if(!doRecoEfficiency    && histName.find("reco_id_eff") != string::npos)              continue;
    if(!doTriggerEfficiency && histName.find("trigger") != string::npos)                  continue;
    if(!doCHEefficiency     && histName.find("charged_exclusivity_eff") != string::npos)  continue;
    if(!doNEEefficiency     && histName.find("neutral_exclusivity_eff") != string::npos)  continue;
    
    string title = histName + "_" + datasetType;
    hists[title]->Write();
  }
  
  int nTag=0, nProbe=0;
  
  if(doRecoEfficiency){
    nTag    = hists["reco_id_eff_den_"+datasetType]->GetBinContent(1);
    nProbe  = hists["reco_id_eff_num_"+datasetType]->GetBinContent(1);
    cout<<"Reco N tags, probes "<<datasetType<<": "<<nTag<<", "<<nProbe<<endl;
    cout<<" efficiency: "; PrintEfficiency(nProbe, nTag);
  }
  if(doHFvetoEfficiency){
    nTag    = hists["trigger_HFveto_eff_den_"+datasetType]->GetBinContent(1);
    nProbe  = hists["trigger_HFveto_eff_num_"+datasetType]->GetBinContent(1);
    cout<<"HF veto N tags, probes "<<datasetType<<": "<<nTag<<", "<<nProbe<<endl;
    cout<<" efficiency: "; PrintEfficiency(nProbe, nTag);
  }
  if(doCHEefficiency){
    nTag    = hists["charged_exclusivity_eff_den_"+datasetType]->GetBinContent(1);
    nProbe  = hists["charged_exclusivity_eff_num_"+datasetType]->GetBinContent(1);
    cout<<"Charged exclusivity N tags, probes "<<datasetType<<": "<<nTag<<", "<<nProbe<<endl;
    cout<<" efficiency: "; PrintEfficiency(nProbe, nTag);
  }
  if(doNEEefficiency){
    nTag    = hists["neutral_exclusivity_eff_den_"+datasetType]->GetBinContent(1);
    nProbe  = hists["neutral_exclusivity_eff_num_"+datasetType]->GetBinContent(1);
    cout<<"Neutral N tags, probes "<<datasetType<<": "<<nTag<<", "<<nProbe<<endl;
    cout<<" efficiency: "; PrintEfficiency(nProbe, nTag);
  }
  
  
  outFile->cd(("triggerTree_"+datasetType).c_str());
  triggerTrees.at(datasetType)->Write();
  
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
  map<EDataset, string> inputPaths;
  ReadInputArguments(argc, argv, inputPaths);
  config = ConfigManager(configPath);
  
  map<string, TH1D*> hists;
  map<string, TTree*> triggerTrees;
  
  TFile *outFile = new TFile(outputPath.c_str(), "recreate");
  
  // Loop over all required datasets
  for(EDataset dataset : datasetsToAnalyze){
    string name = datasetName.at(dataset);
    outFile->mkdir(("triggerTree_"+name).c_str());
    
    InitializeTriggerTrees(triggerTrees, name);
    InitializeHistograms(hists, name);
    
    auto events = make_unique<EventProcessor>(argc == 6 ? inputPaths[dataset] : inFileNames.at(dataset));
    
    // Loop over events
    for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
      if(iEvent%1000 == 0) cout<<"Processing event "<<iEvent<<endl;
      if(iEvent >= config.params("maxEvents")) break;
      
      auto event = events->GetEvent(iEvent);
      
      if(doRecoEfficiency)    CheckRecoEfficiency(*event, hists, name);
      if(doTriggerEfficiency) CheckTriggerEfficiency(*event, triggerTrees, hists, name);
      if(doHFvetoEfficiency)  CheckTriggerHFvetoEfficiency(*event, hists, name);
      if(doCHEefficiency)     CheckCHEefficiency(*event, hists, name);
      if(doNEEefficiency)     CheckNEEefficiency(*event, hists, name);
    }
    
    PrintAndSaveResults(outFile, hists, triggerTrees, name);
  }
  outFile->Close();
  
  return 0;
}

