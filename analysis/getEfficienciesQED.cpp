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
#include "Logger.hpp"


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
  
  // electron reco+ID efficiency
  "electron_reco_id_eff_cut_through",
  "electron_reco_id_eff_num",
  "electron_reco_id_eff_den",
  "electron_reco_id_eff_acoplanarity_num",
  "electron_reco_id_eff_acoplanarity_den",
  
  "electron_reco_id_eff_vs_pt_num",
  "electron_reco_id_eff_vs_pt_den",
  "electron_reco_id_eff_vs_eta_num",
  "electron_reco_id_eff_vs_eta_den",
 
  "electron_reco_id_eff_n_good_electrons",
  "electron_reco_id_eff_n_good_matched_electrons",
  
  "failed_electron_reco_id_eff_vs_pt",
  "failed_electron_reco_id_eff_vs_eta",
  
  // trigger efficiency histograms
  "trigger_eff_cut_through",
  "trigger_HFveto_eff_cut_through",
  "trigger_HFveto_eff_num",
  "trigger_HFveto_eff_den",
  "trigger_HFveto_eff_vs_dielectron_mass_num",
  "trigger_HFveto_eff_vs_dielectron_mass_den",
  "trigger_HFveto_eff_vs_dielectron_rapidity_num",
  "trigger_HFveto_eff_vs_dielectron_rapidity_den",
  "trigger_HFveto_eff_vs_dielectron_pt_num",
  "trigger_HFveto_eff_vs_dielectron_pt_den",
  "trigger_HFveto_eff_vs_acoplanarity_num",
  "trigger_HFveto_eff_vs_acoplanarity_den",
  
  // exclusivity efficiency histograms
  "charged_exclusivity_eff_cut_through",
  "charged_exclusivity_eff_num",
  "charged_exclusivity_eff_den",
  "dielectron_mass",
  "charged_exclusivity_eff_vs_dielectron_mass_num",
  "charged_exclusivity_eff_vs_dielectron_mass_den",
  "charged_exclusivity_eff_vs_dielectron_rapidity_num",
  "charged_exclusivity_eff_vs_dielectron_rapidity_den",
  "charged_exclusivity_eff_vs_dielectron_pt_num",
  "charged_exclusivity_eff_vs_dielectron_pt_den",
  
  
  "neutral_exclusivity_eff_cut_through",
  "neutral_exclusivity_eff_num",
  "neutral_exclusivity_eff_den",
  "neutral_exclusivity_eff_vs_dielectron_mass_num",
  "neutral_exclusivity_eff_vs_dielectron_mass_den",
  "neutral_exclusivity_eff_vs_dielectron_rapidity_num",
  "neutral_exclusivity_eff_vs_dielectron_rapidity_den",
  "neutral_exclusivity_eff_vs_dielectron_pt_num",
  "neutral_exclusivity_eff_vs_dielectron_pt_den",
};

map<string, int> matched;
map<string, float> acoplanarity;
map<string, float> SCEt;
map<string, float> absEta;

Double_t getDPHI( Double_t phi1, Double_t phi2);
Double_t getDETA(Double_t eta1, Double_t eta2);

/// Counts number of events passing tag and probe criteria for reco+ID efficiency
void CheckRecoEfficiency(Event &event, map<string, TH1D*> &hists, string datasetName)
{
  string cutThouthName = "reco_id_eff_cut_through_"+datasetName;
  int cutLevel = 0;
  hists[cutThouthName]->Fill(cutLevel++); // 0
  
  // Check trigger
  if(!event.HasTrigger(kSingleEG3noHF)) return;
  hists[cutThouthName]->Fill(cutLevel++); // 1
  
  // Preselect events with exactly two tracks
  if(event.GetPhysObjects(EPhysObjType::kGeneralTrack).size() != 2) return;
  hists[cutThouthName]->Fill(cutLevel++); // 2
  
  // Make sure that tracks have opposite charges and that brem track has low momentum
  auto track1 = event.GetPhysObjects(EPhysObjType::kGeneralTrack)[0];
  auto track2 = event.GetPhysObjects(EPhysObjType::kGeneralTrack)[1];
  if(track1->GetCharge() == track2->GetCharge()) return;
  hists[cutThouthName]->Fill(cutLevel++); // 3
  
  double estimatedPhotonEt = fabs(track1->GetPt()-track2->GetPt());
//  if(estimatedPhotonEt < 2.0) return;
  hists[cutThouthName]->Fill(cutLevel++); // 4
  
  // Check if there is one good electron matched with L1EG
  PhysObjects goodMatchedElectrons;
  auto goodElectrons = event.GetPhysObjects(EPhysObjType::kGoodElectron);
  
  for(auto electron : goodElectrons){
    if(electron->GetPt() < 3.0) continue;
    
    for(auto &L1EG : event.GetPhysObjects(EPhysObjType::kL1EG)){
      if(L1EG->GetEt() < 3.0) continue;
      
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
  PhysObjects matchingTracks;
  PhysObjects bremTracks;
  
  for(auto track : event.GetPhysObjects(EPhysObjType::kGeneralTrack)){
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
  auto photons = event.GetPhysObjects(EPhysObjType::kGoodPhoton);
//  auto photons = event.GetPhysObjects(EPhysObjType::kPhoton);
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
    auto allPhotons = event.GetPhysObjects(EPhysObjType::kPhoton);
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

/// Counts number of events passing tag and probe criteria for reco+ID efficiency
void CheckElectronRecoEfficiency(Event &event, map<string, TH1D*> &hists, string datasetName)
{
  string cutThouthName = "electron_reco_id_eff_cut_through_"+datasetName;
  int cutLevel = 0;
  hists[cutThouthName]->Fill(cutLevel++); // 0
  
  // Check trigger
  if(!event.HasTrigger(kSingleEG3noHF)) return;
  hists[cutThouthName]->Fill(cutLevel++); // 1
  
  // Preselect events with one or two electrons
  PhysObjects goodMatchedElectrons  = event.GetPhysObjects(EPhysObjType::kGoodMatchedElectron);
  PhysObjects goodElectrons         = event.GetPhysObjects(EPhysObjType::kGoodElectron);
  
  hists["electron_reco_id_eff_n_good_electrons_"+datasetName]->Fill(goodElectrons.size());
  hists["electron_reco_id_eff_n_good_matched_electrons_"+datasetName]->Fill(goodMatchedElectrons.size());
  
  if(goodElectrons.size() != 1 && goodElectrons.size() != 2) return;
  hists[cutThouthName]->Fill(cutLevel++); // 2
  
  if(goodMatchedElectrons.size() != 1 && goodMatchedElectrons.size() != 2) return;
  hists[cutThouthName]->Fill(cutLevel++); // 3
  
  
  auto electronTag = goodMatchedElectrons[0];
  shared_ptr<PhysObject> trackTag = nullptr;
  PhysObjects goodGeneralTracks = event.GetPhysObjects(EPhysObjType::kGoodGeneralTrack);
  PhysObjects probeTracks;
  
  // Find track matched to the tag and put other tracks in a separate collection
  for(auto track : goodGeneralTracks){
    if(track->GetPt() < 2.0) continue;
    bool matched = physObjectProcessor.GetDeltaR(*electronTag, *track) < config.params("maxDeltaR");
    if(matched) trackTag = track;
    else        probeTracks.push_back(track);
  }
  
  // make sure that tag electon is matched with a track > 2 GeV
  if(!trackTag) return;
  hists[cutThouthName]->Fill(cutLevel++); // 4

  // Check that there are some tracks left
  if(probeTracks.size() != 1) return;
  hists[cutThouthName]->Fill(cutLevel++); // 5

  auto dielectron = physObjectProcessor.GetDielectron(*trackTag, *probeTracks[0]);
  
//  if(dielectron.Pt() > 2.0 || dielectron.M() < 4.0) return;
  hists[cutThouthName]->Fill(cutLevel++); // 6
  
  hists["electron_reco_id_eff_den_"+datasetName]->Fill(1);
  hists["electron_reco_id_eff_vs_pt_den_"+datasetName]->Fill(electronTag->GetPt());
  hists["electron_reco_id_eff_vs_eta_den_"+datasetName]->Fill(electronTag->GetEta());
  
  // Check that there is a second electron
  
  if(goodElectrons.size() != 2){
    hists["failed_electron_reco_id_eff_vs_pt_"+datasetName]->Fill(electronTag->GetPt());
    hists["failed_electron_reco_id_eff_vs_eta_"+datasetName]->Fill(electronTag->GetEta());
    return;
  }
  
  
  shared_ptr<PhysObject> electronProbe;
  
  for(auto electron : goodElectrons){
    if(electron != electronTag) electronProbe = electron;
  }
  
  bool probeMatched = false;
  
  for(auto track : probeTracks){
    bool matched = physObjectProcessor.GetDeltaR(*electronProbe, *track) < config.params("maxDeltaR");
    if(matched){
      probeMatched = true;
      break;
    }
  }
  
  if(!probeMatched){
    hists["failed_electron_reco_id_eff_vs_pt_"+datasetName]->Fill(electronTag->GetPt());
    hists["failed_electron_reco_id_eff_vs_eta_"+datasetName]->Fill(electronTag->GetEta());
    return;
  }
  hists[cutThouthName]->Fill(cutLevel++); // 7
    
  hists["electron_reco_id_eff_num_"+datasetName]->Fill(1);
  hists["electron_reco_id_eff_vs_pt_num_"+datasetName]->Fill(electronTag->GetPt());
  hists["electron_reco_id_eff_vs_eta_num_"+datasetName]->Fill(electronTag->GetEta());
}

/// Counts number of events passing tag and probe criteria for trigger efficiency
void CheckTriggerEfficiency(Event &event, map<string, TTree*> &trees, map<string, TH1D*> &hists, string datasetName)
{
  string cutThouthName = "trigger_eff_cut_through_"+datasetName;
  int cutLevel = 0;
  hists[cutThouthName]->Fill(cutLevel++); // 0
  
  // Check trigger
  
  // has EG3
  //    if(!event.HasTrigger(kSingleEG3noHF)) return;
  //    double threshold = 3.0;
  
  // has EG5
  //  if(!event.HasTrigger(kSingleEG5noHF)) return;
  //  double threshold = 5.0;
  
  // has only EG3
  //  if(!event.HasTrigger(kSingleEG3noHF) || event.HasTrigger(kSingleEG5noHF)) return;
  //  double threshold = 3.0;
  
  // has only EG5
  //  if(event.HasTrigger(kSingleEG3noHF) || !event.HasTrigger(kSingleEG5noHF)) return;
  //  double threshold = 5.0;
  
  // has either of the triggers
  if(!event.HasTrigger(kSingleEG3noHF) && !event.HasTrigger(kSingleEG5noHF)) return;
  double threshold = 3.0;
  if(event.HasTrigger(kSingleEG3noHF)) threshold = 3.0;
  if(event.HasTrigger(kSingleEG5noHF)) threshold = 5.0;
  
  //  if(!event.HasTrigger(kSingleEG3noHF)) return;
  //  if(!event.HasTrigger(kSingleEG5noHF)) return;
  hists[cutThouthName]->Fill(cutLevel++); // 1
  
  // Neutral exclusivity
  if(event.HasAdditionalTowers()) return;
  hists[cutThouthName]->Fill(cutLevel++); // 2
  
  // Preselect events with exactly two electrons
  auto goodElectrons = event.GetPhysObjects(EPhysObjType::kGoodElectron);
  if(goodElectrons.size() != 2) return;
  hists[cutThouthName]->Fill(cutLevel++); // 3
  
  // Charged exclusivity
  if(event.GetPhysObjects(EPhysObjType::kGoodGeneralTrack).size() != 2) return;
  hists[cutThouthName]->Fill(cutLevel++); // 4
  
  // Tag and probe
  auto electron1 = goodElectrons[0];
  auto electron2 = goodElectrons[1];
  
  shared_ptr<PhysObject> tag = nullptr;
  shared_ptr<PhysObject> passingProbe = nullptr;
  shared_ptr<PhysObject> failedProbe = nullptr;
  
  for(auto &L1EG : event.GetPhysObjects(EPhysObjType::kL1EG)){
    if(tag && passingProbe) break;
    
    double deltaR1 = physObjectProcessor.GetDeltaR_SC(*electron1, *L1EG);
    double deltaR2 = physObjectProcessor.GetDeltaR_SC(*electron2, *L1EG);
    
    if(deltaR1 < 1.0){
      if(!tag && L1EG->GetEt() > threshold) tag = electron1;
      else if(L1EG->GetEt() > 2.0) passingProbe = electron1;
    }
    
    if(deltaR2 < 1.0){
      if(!tag && L1EG->GetEt() > threshold) tag = electron2;
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
  if(!event.HasTrigger(kSingleEG3singleTrack) && !event.HasTrigger(kSingleEG5singleTrack) ) return;
  hists[cutThouthName]->Fill(cutLevel++); // 1
  
  // Neutral exclusivity
  if(event.HasAdditionalTowers()) return;
  hists[cutThouthName]->Fill(cutLevel++); // 2
  
  // Preselect events with exactly two electrons
  auto goodElectrons = event.GetPhysObjects(EPhysObjType::kGoodElectron);
  if(goodElectrons.size() != 2) return;
  hists[cutThouthName]->Fill(cutLevel++); // 3
  
  // Opposite charges
  auto electron1 = goodElectrons[0];
  auto electron2 = goodElectrons[1];
  if(electron1->GetCharge() == electron2->GetCharge()) return;
  hists[cutThouthName]->Fill(cutLevel++); // 4
  
  // very tight charged exclusivity
  //if(event.GetPhysObjects(EPhysObjType::kGoodGeneralTrack).size() != 2) return;
  //hists[cutThouthName]->Fill(cutLevel++); // 5
  
  // Charged exclusivity: remove extra track outside electron cone
  auto genTracks = event.GetPhysObjects(EPhysObjType::kGoodGeneralTrack);
  int nextratracks =0;
  for (auto trk : genTracks) {
    if (getDPHI(trk->GetPhi(), electron1->GetPhi())<0.7 && getDETA(trk->GetEta(), electron1->GetEta())<0.15) continue;
    if (getDPHI(trk->GetPhi(), electron2->GetPhi())<0.7 && getDETA(trk->GetEta(), electron2->GetEta())<0.15) continue;
    nextratracks++;
  }
  if(nextratracks!=0) return;
  hists[cutThouthName]->Fill(cutLevel++); // 5
  
  // Check if there are two electrons matched with L1 objects
  PhysObjects matchedElectrons;
  
  // Check matching with L1 objects
  for(auto &L1EG : event.GetPhysObjects(EPhysObjType::kL1EG)){
    if(matchedElectrons.size() == 2) break;
    if(L1EG->GetEt() < 2.0) continue;
    
    double deltaR1 = physObjectProcessor.GetDeltaR_SC(*electron1, *L1EG);
    double deltaR2 = physObjectProcessor.GetDeltaR_SC(*electron2, *L1EG);
    
    if(deltaR1 < 1.0) matchedElectrons.push_back(electron1);
    if(deltaR2 < 1.0) matchedElectrons.push_back(electron2);
  }
  
  if(matchedElectrons.size() != 2) return;
  hists[cutThouthName]->Fill(cutLevel++); // 6

  TLorentzVector dielectron = physObjectProcessor.GetDielectron(*matchedElectrons[0], *matchedElectrons[1]);
  if(dielectron.M() < 5.0) return;
  hists[cutThouthName]->Fill(cutLevel++); // 7
  
  if(dielectron.Pt() > 1.0) return;
  hists[cutThouthName]->Fill(cutLevel++); // 8
  
  if(fabs(dielectron.Rapidity()) > 2.4) return;
  hists[cutThouthName]->Fill(cutLevel++); // 9

  hists["trigger_HFveto_eff_den_"+datasetName]->Fill(1);
  hists["trigger_HFveto_eff_vs_dielectron_mass_den_"+datasetName]->Fill(dielectron.M());
  hists["trigger_HFveto_eff_vs_dielectron_rapidity_den_"+datasetName]->Fill(dielectron.Rapidity());
  hists["trigger_HFveto_eff_vs_dielectron_pt_den_"+datasetName]->Fill(dielectron.Pt());
  hists["trigger_HFveto_eff_vs_acoplanarity_den_"+datasetName]->Fill(physObjectProcessor.GetAcoplanarity(*matchedElectrons[0], *matchedElectrons[1]));

  
  // Check if it also has double EG2 trigger
  if(!event.HasTrigger(kDoubleEG2noHF)) return;
  hists[cutThouthName]->Fill(cutLevel++); // 10
  hists["trigger_HFveto_eff_num_"+datasetName]->Fill(1);
  hists["trigger_HFveto_eff_vs_dielectron_mass_num_"+datasetName]->Fill(dielectron.M());
  hists["trigger_HFveto_eff_vs_dielectron_rapidity_num_"+datasetName]->Fill(dielectron.Rapidity());
  hists["trigger_HFveto_eff_vs_dielectron_pt_num_"+datasetName]->Fill(dielectron.Pt());
  hists["trigger_HFveto_eff_vs_acoplanarity_num_"+datasetName]->Fill(physObjectProcessor.GetAcoplanarity(*matchedElectrons[0], *matchedElectrons[1]));
}

/// Counts number of events passing tag and probe criteria for charged exclusivity efficiency
void CheckCHEefficiency(Event &event, map<string, TH1D*> &hists, string datasetName)
{
  string cutThouthName = "charged_exclusivity_eff_cut_through_"+datasetName;
  int cutLevel = 0;
  hists[cutThouthName]->Fill(cutLevel++); // 0
  
  if(!event.HasTrigger(kDoubleEG2noHF)) return;
  hists[cutThouthName]->Fill(cutLevel++); // 1
  
  // Check that there are exaclty two electrons
  auto goodElectrons = event.GetPhysObjects(EPhysObjType::kGoodElectron);
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
  
  if(fabs(dielectron.Rapidity()) > 2.4) return;
  hists[cutThouthName]->Fill(cutLevel++); // 6
  
  hists["charged_exclusivity_eff_den_"+datasetName]->Fill(1);
  hists["charged_exclusivity_eff_vs_dielectron_mass_den_"+datasetName]->Fill(dielectron.M());
  hists["charged_exclusivity_eff_vs_dielectron_rapidity_den_"+datasetName]->Fill(dielectron.Rapidity());
  hists["charged_exclusivity_eff_vs_dielectron_pt_den_"+datasetName]->Fill(dielectron.Pt());
  
  // very tight charged exclusivity
  //if(event.GetPhysObjects(EPhysObjType::kGoodGeneralTrack).size() != 2) return;
  //hists[cutThouthName]->Fill(cutLevel++); // 5
  
  // Charged exclusivity: remove extra track outside electron cone
  auto genTracks = event.GetPhysObjects(EPhysObjType::kGoodGeneralTrack);
  int nextratracks =0;
  for (auto trk : genTracks) {
    if (getDPHI(trk->GetPhi(), electron1->GetPhi())<0.7 && getDETA(trk->GetEta(), electron1->GetEta())<0.15) continue;
    if (getDPHI(trk->GetPhi(), electron2->GetPhi())<0.7 && getDETA(trk->GetEta(), electron2->GetEta())<0.15) continue;
    nextratracks++;
  }
  if(nextratracks!=0) return;
  hists[cutThouthName]->Fill(cutLevel++); // 5
  hists["charged_exclusivity_eff_num_"+datasetName]->Fill(1);
  hists["charged_exclusivity_eff_vs_dielectron_mass_num_"+datasetName]->Fill(dielectron.M());
  hists["charged_exclusivity_eff_vs_dielectron_rapidity_num_"+datasetName]->Fill(dielectron.Rapidity());
  hists["charged_exclusivity_eff_vs_dielectron_pt_num_"+datasetName]->Fill(dielectron.Pt());
}

/// Counts number of events passing tag and probe criteria for neutral exclusivity efficiency
void CheckNEEefficiency(Event &event, map<string, TH1D*> &hists, string datasetName)
{
  string cutThouthName = "neutral_exclusivity_eff_cut_through_"+datasetName;
  int cutLevel = 0;
  hists[cutThouthName]->Fill(cutLevel++); // 0
  
  if(!event.HasTrigger(kDoubleEG2noHF)) return;
  hists[cutThouthName]->Fill(cutLevel++); // 1
  
  // Check that there are exaclty two electrons
  auto goodElectrons = event.GetPhysObjects(EPhysObjType::kGoodElectron);
  if(goodElectrons.size() != 2) return;
  hists[cutThouthName]->Fill(cutLevel++); // 2
  
  auto electron1 = goodElectrons[0];
  auto electron2 = goodElectrons[1];
  
  // Opposite charges
  if(electron1->GetCharge() == electron2->GetCharge()) return;
  hists[cutThouthName]->Fill(cutLevel++); // 3
  
  // Check dielectron properties
  TLorentzVector dielectron = physObjectProcessor.GetDielectron(*electron1, *electron2);
  if(dielectron.M() < 5.0 || dielectron.Pt() > 1.0 || fabs(dielectron.Rapidity()) > 2.4) return;
  hists[cutThouthName]->Fill(cutLevel++); // 4
  
  // very tight charged exclusivity
  //if(event.GetPhysObjects(EPhysObjType::kGoodGeneralTrack).size() != 2) return;
  //hists[cutThouthName]->Fill(cutLevel++); // 5
  
  // Charged exclusivity: remove extra track outside electron cone
  auto genTracks = event.GetPhysObjects(EPhysObjType::kGoodGeneralTrack);
  int nextratracks =0;
  for (auto trk : genTracks) {
    if (getDPHI(trk->GetPhi(), electron1->GetPhi())<0.7 && getDETA(trk->GetEta(), electron1->GetEta())<0.15) continue;
    if (getDPHI(trk->GetPhi(), electron2->GetPhi())<0.7 && getDETA(trk->GetEta(), electron2->GetEta())<0.15) continue;
    nextratracks++;
  }
  if(nextratracks!=0) return;
  hists[cutThouthName]->Fill(cutLevel++); // 5
  hists["neutral_exclusivity_eff_den_"+datasetName]->Fill(1);
  hists["neutral_exclusivity_eff_vs_dielectron_mass_den_"+datasetName]->Fill(dielectron.M());
  hists["neutral_exclusivity_eff_vs_dielectron_rapidity_den_"+datasetName]->Fill(dielectron.Rapidity());
  hists["neutral_exclusivity_eff_vs_dielectron_pt_den_"+datasetName]->Fill(dielectron.Pt());
  
  
  // Neutral exclusivity
  if(event.HasAdditionalTowers()) return;
  hists[cutThouthName]->Fill(cutLevel++); // 6
  hists["neutral_exclusivity_eff_num_"+datasetName]->Fill(1);
  hists["neutral_exclusivity_eff_vs_dielectron_mass_num_"+datasetName]->Fill(dielectron.M());
  hists["neutral_exclusivity_eff_vs_dielectron_rapidity_num_"+datasetName]->Fill(dielectron.Rapidity());
  hists["neutral_exclusivity_eff_vs_dielectron_pt_num_"+datasetName]->Fill(dielectron.Pt());
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
    
    if(histName.find("vs_pt") != string::npos ||
       histName.find("vs_dielectron_pt") != string::npos){
      bins  = { 0, 2, 4, 6, 8, 20 , 40, 100};
      hists[title] = new TH1D(title.c_str(), title.c_str(), (int)bins.size()-1, (float*)&bins[0]);
    }
    else if(histName.find("vs_eta") != string::npos ||
            histName.find("vs_dielectron_rapidity") != string::npos){
      hists[title] = new TH1D(title.c_str(), title.c_str(), 10, 0.0, 5.0);
    }
    else if(histName.find("vs_dielectron_mass") != string::npos){
      hists[title] = new TH1D(title.c_str(), title.c_str(), 40, 0, 20);
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
      hists[title] = new TH1D(title.c_str(), title.c_str(), 50, 0, 0.1);
    }
    else if(histName.find("brem_track_pt") != string::npos){
      hists[title] = new TH1D(title.c_str(), title.c_str(), 30, 0, 10);
    }
    else if(histName.find("cut_through") != string::npos){
      hists[title] = new TH1D(title.c_str(), title.c_str(), 20, 0, 20);
    }
    else if(histName == "dielectron_mass"){
      hists[title] = new TH1D(title.c_str(), title.c_str(), 50, 0, 20);
    }
    else if(histName.find("_n_") != string::npos){
      hists[title] = new TH1D(title.c_str(), title.c_str(), 20, 0, 20);
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
  Log(0)<<"\n\n------------------------------------------------------------------------\n";
  outFile->cd();
  
  for(auto histName : histParams){
    if(!config.params("doRecoEfficiency")    && histName.find("reco_id_eff") != string::npos)              continue;
    if(!config.params("doHFvetoEfficiency")  && histName.find("trigger_HFveto_eff") != string::npos)       continue;
    //if(!config.params("doTriggerEfficiency") && histName.find("trigger") != string::npos)                  continue;
    if(!config.params("doCHEefficiency")     && histName.find("charged_exclusivity_eff") != string::npos)  continue;
    if(!config.params("doNEEefficiency")     && histName.find("neutral_exclusivity_eff") != string::npos)  continue;
    if(!config.params("doElectronRecoEfficiency") && histName.find("electron_reco_id_eff") != string::npos)              continue;
    
    string title = histName + "_" + datasetType;
    hists[title]->Write();
  }
  
  int nTag=0, nProbe=0;
  
  if(config.params("doRecoEfficiency")){
    nTag    = hists["reco_id_eff_den_"+datasetType]->GetBinContent(1);
    nProbe  = hists["reco_id_eff_num_"+datasetType]->GetBinContent(1);
    Log(0)<<"Reco N tags, probes "<<datasetType<<": "<<nTag<<", "<<nProbe<<"\n";
    Log(0)<<" efficiency: "; PrintEfficiency(nProbe, nTag);
  }
  if(config.params("doHFvetoEfficiency")){
    nTag    = hists["trigger_HFveto_eff_den_"+datasetType]->GetBinContent(1);
    nProbe  = hists["trigger_HFveto_eff_num_"+datasetType]->GetBinContent(1);
    Log(0)<<"HF veto N tags, probes "<<datasetType<<": "<<nTag<<", "<<nProbe<<"\n";
    Log(0)<<" efficiency: "; PrintEfficiency(nProbe, nTag);
  }
  if(config.params("doCHEefficiency")){
    nTag    = hists["charged_exclusivity_eff_den_"+datasetType]->GetBinContent(1);
    nProbe  = hists["charged_exclusivity_eff_num_"+datasetType]->GetBinContent(1);
    Log(0)<<"Charged exclusivity N tags, probes "<<datasetType<<": "<<nTag<<", "<<nProbe<<"\n";
    Log(0)<<" efficiency: "; PrintEfficiency(nProbe, nTag);
  }
  if(config.params("doNEEefficiency")){
    nTag    = hists["neutral_exclusivity_eff_den_"+datasetType]->GetBinContent(1);
    nProbe  = hists["neutral_exclusivity_eff_num_"+datasetType]->GetBinContent(1);
    Log(0)<<"Neutral N tags, probes "<<datasetType<<": "<<nTag<<", "<<nProbe<<"\n";
    Log(0)<<" efficiency: "; PrintEfficiency(nProbe, nTag);
  }
  if(config.params("doElectronRecoEfficiency")){
    nTag    = hists["electron_reco_id_eff_den_"+datasetType]->GetBinContent(1);
    nProbe  = hists["electron_reco_id_eff_num_"+datasetType]->GetBinContent(1);
    Log(0)<<"Electron reco N tags, probes "<<datasetType<<": "<<nTag<<", "<<nProbe<<"\n";
    Log(0)<<" efficiency: "; PrintEfficiency(nProbe, nTag);
  }
  
  
  outFile->cd(("triggerTree_"+datasetType).c_str());
  triggerTrees.at(datasetType)->Write();
  
  Log(0)<<"------------------------------------------------------------------------\n\n\n";
}

/// Checks that number of arguments provided is correct and sets corresponding variables
void ReadInputArguments(int argc, char* argv[],
                        string &configPath, string &inputPath, string &outputPath, string &sampleName)
{
  if(argc != 5){
    Log(0)<<"This app requires 4 parameters:\n";
    Log(0)<<"./getEfficienciesQED configPath inputPath outputPath datasetName[Data|QED_SC|QED_SL|LbL|CEP]\n";
    exit(0);
  }

  configPath = argv[1];
  inputPath  = argv[2];
  outputPath = argv[3];
  sampleName = argv[4];
}

/// Application starting point
int main(int argc, char* argv[])
{
  string configPath, inputPath, outputPath, sampleName;
  ReadInputArguments(argc, argv, configPath, inputPath, outputPath, sampleName);

  config = ConfigManager(configPath);
  EDataset dataset = datasetForName.at(sampleName);
  
  map<string, TH1D*> hists;
  InitializeHistograms(hists, sampleName);
  
  map<string, TTree*> triggerTrees;
  InitializeTriggerTrees(triggerTrees, sampleName);
  
  TFile *outFile = new TFile(outputPath.c_str(), "recreate");
  outFile->mkdir(("triggerTree_"+sampleName).c_str());
  
  auto events = make_unique<EventProcessor>(inputPath, dataset);
  
  // Loop over events
  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
    if(iEvent%1000 == 0) Log(0)<<"Processing event "<<iEvent<<"\n";
    if(iEvent >= config.params("maxEvents")) break;
    
    auto event = events->GetEvent(iEvent);
    
    if(config.params("doRecoEfficiency"))         CheckRecoEfficiency(*event, hists, sampleName);
    if(config.params("doTriggerEfficiency"))      CheckTriggerEfficiency(*event, triggerTrees, hists, sampleName);
    if(config.params("doHFvetoEfficiency"))       CheckTriggerHFvetoEfficiency(*event, hists, sampleName);
    if(config.params("doCHEefficiency"))          CheckCHEefficiency(*event, hists, sampleName);
    if(config.params("doNEEefficiency"))          CheckNEEefficiency(*event, hists, sampleName);
    if(config.params("doElectronRecoEfficiency")) CheckElectronRecoEfficiency(*event, hists, sampleName);
  }
  
  PrintAndSaveResults(outFile, hists, triggerTrees, sampleName);

  outFile->Close();
  
  return 0;
}

Double_t getDPHI( Double_t phi1, Double_t phi2) {
  Double_t dphi = phi1 - phi2;
  
  if ( dphi > 3.141592653589 )
    dphi = dphi - 2. * 3.141592653589;
  if ( dphi <= -3.141592653589 )
    dphi = dphi + 2. * 3.141592653589;
  
  if ( TMath::Abs(dphi) > 3.141592653589 ) {
    cout << " commonUtility::getDPHI error!!! dphi is bigger than 3.141592653589 " << endl;
  }
  
  return TMath::Abs(dphi);
  //return dphi;
}

Double_t getDETA(Double_t eta1, Double_t eta2){
  return TMath::Abs(eta1 - eta2);
}
