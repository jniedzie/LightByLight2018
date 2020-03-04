//  prepareAcoplanarityPlots.cpp
//
//  Created by Jeremi Niedziela on 31/07/2019.

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"
#include "EventDisplay.hpp"

string configPath = "configs/efficiencies.md";
string outputPath = "results/basicPlots_test_new.root";

bool saveCalosFailingNEE = true;
bool saveTriphotonHists = true;
bool checkTriggers = false;

int nThreePhotonEvents = 0;

// Only those datasets will be analyzed
const vector<EDataset> datasetsToAnalyze = {
//  kData,
  //  kData_SingleEG3,
  //  kData_recoEff,
  //  kData_triggerEff,
  //  kData_HFveto,
  //  kData_exclusivity,
  kData_LbLsignal,
//  kData_QEDsignal,
//    kMCqedSC,
  //  kMCqedSC_SingleEG3,
  //  kMCqedSC_recoEff,
  //  kMCqedSC_triggerEff,
  //  kMCqedSC_HFveto,
  //  kMCqedSC_exclusivity,
//  kMCqedSC_LbLsignal,
  kMCqedSC_QEDsignal,
  //  kMCqedSL,
    kMClbl,
    kMCcep
};

vector<string> suffixes = {
  "all", "low_aco", "high_aco",
  "good", "good_low_aco", "good_high_aco", "good_all", "two_photons", "good_two_photons"
};

vector<tuple<string, int, double, double>> histParams = {
  // title                   nBins min   max
  {"lbl_acoplanarity"       , 200 , 0   , 1.0   },
  {"lbl_photon_et"          , 100 , 0   , 100.0 },
  {"lbl_photon_eta"         , 6   ,-2.4 , 2.4   },
  {"lbl_photon_phi"         , 8   ,-4.0 , 4.0   },
  {"lbl_diphoton_mass"      , 80  , 0   , 200.0 },
  {"lbl_diphoton_rapidity"  , 6   ,-2.4 , 2.4   },
  {"lbl_diphoton_pt"        , 50  , 0   , 10.0  },
  {"lbl_triphoton_mass"     , 800 , 0   , 200.0 },
  {"lbl_triphoton_rapidity" , 24  ,-2.4 , 2.4   },
  {"lbl_triphoton_pt"       , 500 , 0   , 100.0 },
  {"lbl_cut_flow"           , 15  , 0   , 15    },
  {"lbl_nee_failing"        , 15  , 0   , 15    },
  {"lbl_HFp"                , 200 , 0   , 20    },
  {"lbl_HFm"                , 200 , 0   , 20    },
  {"lbl_HFp_leading_tower"  , 200 , 0   , 20    },
  {"lbl_HFm_leading_tower"  , 200 , 0   , 20    },
  
  {"qed_acoplanarity"       , 500 , 0   , 1.0   },
  {"qed_electron_pt"        , 400 , 0   , 200.0 },
  {"qed_electron_eta"       , 24  ,-2.4 , 2.4   },
  {"qed_electron_phi"       , 20  ,-4.0 , 4.0   },
  {"qed_dielectron_mass"    , 200 , 0   , 200.0 },
  {"qed_dielectron_rapidity", 30  ,-3.0 , 3.0   },
  {"qed_dielectron_pt"      , 100 , 0   , 10.0  },
  {"qed_cut_flow"           , 15  , 0   , 15    },
  {"qed_electron_cutflow"   , 15  , 0   , 15    },
  {"qed_HFp"                , 200 , 0   , 20    },
  {"qed_HFm"                , 200 , 0   , 20    },
  {"qed_HFp_leading_tower"  , 200 , 0   , 20    },
  {"qed_HFm_leading_tower"  , 200 , 0   , 20    },
  
  {"samesign_dielectron_mass"       , 200 , 0   , 200.0 },
  {"samesign_dielectron_rapidity"   , 30  ,-3.0 , 3.0   },
  {"samesign_dielectron_pt"         , 100 , 0   , 10.0  },
  
  {"nTracks"                , 100 , 0   , 100   },
  {"track_pt"               , 5000, 0   , 100   },
  {"track_eta"              , 100 ,-3.5 , 3.5   },
  {"track_phi"              , 100 ,-3.5 , 3.5   },
  {"track_missing_hits"     , 50  , 0   , 50    },
  {"track_valid_hits"       , 50  , 0   , 50    },
  {"track_purity"           , 10  , 0   , 10    },
  {"track_charge"           , 4   ,-2   , 2     },
  {"track_chi2"             , 1000, 0   , 100   },
  {"track_dxy"              ,10000,-150 , 150   },
  {"track_dz"               ,10000,-500 , 500   },
  {"track_dxy_over_sigma"   , 1000, 0   , 100   },
  {"track_dz_over_sigma"    , 1000, 0   , 100   },
  
  {"track_vx"               , 1000,-150 , 150   },
  {"track_vy"               , 1000,-150 , 150   },
  {"track_vz"               , 1000,-500 , 500   },
  
  {"tracks_cut_flow"        , 15  , 0   , 15    },
};

void fillTriphotonHists(Event &event, const map<string, TH1D*> &hists, string datasetName, bool saveEventDisplays=false)
{
  auto photons = event.GetPhysObjects(kGoodPhoton);
  PhysObjects isolatedPhotons;
  
  for(int i=0; i<photons.size(); i++){
    bool hasNerbyPhotons = false;
    for(int j=0; j<photons.size(); j++){
      if(i==j) continue;
      
      double deltaR = physObjectProcessor.GetDeltaR(*photons[i], *photons[j]);
      
      if(deltaR < 0.3){
        hasNerbyPhotons = true;
        break;
      }
    }
    if(!hasNerbyPhotons) isolatedPhotons.push_back(photons[i]);
  }
  
  if(isolatedPhotons.size() == 3){
    nThreePhotonEvents++;
    TLorentzVector triphoton = physObjectProcessor.GetTriphoton(*isolatedPhotons[0],
                                                                *isolatedPhotons[1],
                                                                *isolatedPhotons[2]);
    
    hists.at("lbl_triphoton_mass_all_"+datasetName)->Fill(triphoton.M());
    hists.at("lbl_triphoton_rapidity_all_"+datasetName)->Fill(triphoton.Rapidity());
    hists.at("lbl_triphoton_pt_all_"+datasetName)->Fill(triphoton.Pt());
    
    if(saveEventDisplays){
      PhysObjects emptyVector;
      saveEventDisplay(emptyVector, emptyVector, emptyVector, isolatedPhotons, emptyVector,
                       "~/Desktop/lbl_triphoton_event_displays_"+datasetName+"/");
    }
  }
}

void fillPhotonHists(Event &event, const map<string, TH1D*> &hists, string datasetName, string suffix="")
{
  if(suffix != "") suffix += "_";
  for(auto photon : event.GetPhysObjects(kGoodPhoton)){
    hists.at("lbl_photon_et_" +suffix+datasetName)->Fill(photon->GetEt());
    hists.at("lbl_photon_eta_"+suffix+datasetName)->Fill(photon->GetEta());
    hists.at("lbl_photon_phi_"+suffix+datasetName)->Fill(photon->GetPhi());
  }
}

void fillDiphotonHists(Event &event, const map<string, TH1D*> &hists, string datasetName, string suffix="")
{
  TLorentzVector diphoton = physObjectProcessor.GetDiphoton(*event.GetPhysObjects(kGoodPhoton)[0],
                                                            *event.GetPhysObjects(kGoodPhoton)[1]);
  if(suffix != "") suffix += "_";
  hists.at("lbl_diphoton_mass_"     +suffix+datasetName)->Fill(diphoton.M());
  hists.at("lbl_diphoton_rapidity_" +suffix+datasetName)->Fill(diphoton.Rapidity());
  hists.at("lbl_diphoton_pt_"       +suffix+datasetName)->Fill(diphoton.Pt());
}

void fillElectronHists(Event &event, const map<string, TH1D*> &hists, string datasetName, string suffix="")
{
  if(suffix != "") suffix += "_";
  for(auto electron : event.GetPhysObjects(kGoodMatchedElectron)){
    hists.at("qed_electron_pt_" +suffix+datasetName)->Fill(electron->GetPt());
    hists.at("qed_electron_eta_"+suffix+datasetName)->Fill(electron->GetEta());
    hists.at("qed_electron_phi_"+suffix+datasetName)->Fill(electron->GetPhi());
  }
}

void fillDielectronHists(Event &event, const map<string, TH1D*> &hists, string datasetName, string sample, string suffix="")
{
  if(suffix != "") suffix += "_";
  
  TLorentzVector dielectron = physObjectProcessor.GetDielectron(*event.GetPhysObjects(kGoodMatchedElectron)[0],
                                                                *event.GetPhysObjects(kGoodMatchedElectron)[1]);
  
  hists.at(sample+"_dielectron_mass_"     +suffix+datasetName)->Fill(dielectron.M());
  hists.at(sample+"_dielectron_rapidity_" +suffix+datasetName)->Fill(dielectron.Rapidity());
  hists.at(sample+"_dielectron_pt_"       +suffix+datasetName)->Fill(dielectron.Pt());
  
}

void fillHFnoiseHists(Event &event, const map<string, TH1D*> &hists, string datasetName, string sample, string suffix="")
{
  if(suffix != "") suffix += "_";
  
  event.SortCaloTowersByEnergy();
  bool leadingHFpFilled = false;
  bool leadingHFmFilled = false;
  
  for(auto tower : event.GetPhysObjects(kCaloTower)){
    
    if(tower->GetEta() > minEtaHF && tower->GetEta() < maxEtaHF){
      hists.at(sample+"_HFp_"+suffix+datasetName)->Fill(tower->GetEnergy());
      
      if(!leadingHFpFilled){
        hists.at(sample+"_HFp_leading_tower_"+suffix+datasetName)->Fill(tower->GetEnergy());
        leadingHFpFilled = true;
      }
    }
    if(tower->GetEta() > -maxEtaHF && tower->GetEta() < -minEtaHF){
      hists.at(sample+"_HFm_"+suffix+datasetName)->Fill(tower->GetEnergy());
      if(!leadingHFmFilled){
        hists.at(sample+"_HFm_leading_tower_"+suffix+datasetName)->Fill(tower->GetEnergy());
        leadingHFmFilled = true;
      }
    }
  }
}

void fillTracksHists(Event &event, const map<string, TH1D*> &hists, string datasetName, string suffix="")
{
  if(suffix != "") suffix += "_";
  
  PhysObjects tracksLowPt, tracksHighPt;
  
  hists.at("nTracks_"+suffix+datasetName)->Fill(event.GetPhysObjects(kGeneralTrack).size());
  
  for(auto track : event.GetPhysObjects(kGeneralTrack)){
    double trackPt = track->GetPt();
    hists.at("track_pt_"+suffix+datasetName)->Fill(trackPt);
    hists.at("track_eta_"+suffix+datasetName)->Fill(track->GetEta());
    hists.at("track_phi_"+suffix+datasetName)->Fill(track->GetPhi());
    
    hists.at("track_missing_hits_"  + suffix + datasetName)->Fill(track->GetNmissingHits());
    hists.at("track_valid_hits_"    + suffix + datasetName)->Fill(track->GetNvalidHits());
    hists.at("track_purity_"        + suffix + datasetName)->Fill(track->GetPurity());
    hists.at("track_charge_"        + suffix + datasetName)->Fill(track->GetCharge());
    hists.at("track_chi2_"          + suffix + datasetName)->Fill(track->GetChi2());
    hists.at("track_dxy_"           + suffix + datasetName)->Fill(track->GetDxy());
    hists.at("track_dz_"            + suffix + datasetName)->Fill(track->GetDz());
    hists.at("track_dxy_over_sigma_"+ suffix + datasetName)->Fill(fabs(track->GetDxy()/track->GetDxyErr()));
    hists.at("track_dz_over_sigma_" + suffix + datasetName)->Fill(fabs(track->GetDz()/track->GetDzErr()));
    hists.at("track_vx_"            + suffix + datasetName)->Fill(track->GetVertexX());
    hists.at("track_vy_"            + suffix + datasetName)->Fill(track->GetVertexY());
    hists.at("track_vz_"            + suffix + datasetName)->Fill(track->GetVertexZ());
    
    if(trackPt < 0.1) tracksLowPt.push_back(track);
    else              tracksHighPt.push_back(track);
  }
  
  hists.at("nTracks_good_"+suffix+datasetName)->Fill(event.GetPhysObjects(kGoodGeneralTrack).size());
  
  for(auto track : event.GetPhysObjects(kGoodGeneralTrack)){
    hists.at("track_pt_good_"+suffix+datasetName)->Fill(track->GetPt());
    hists.at("track_eta_good_"+suffix+datasetName)->Fill(track->GetEta());
    hists.at("track_phi_good_"+suffix+datasetName)->Fill(track->GetPhi());
  }
}

void fillLbLHistograms(Event &event, const map<string, TH1D*> &hists, string datasetName)
{
  int cutThrough=0;
  hists.at("lbl_cut_flow_all_"+datasetName)->Fill(cutThrough++); // 0
  
  if(checkTriggers && !event.HasDoubleEG2Trigger()) return;
  hists.at("lbl_cut_flow_all_"+datasetName)->Fill(cutThrough++); // 1
  
  if(event.GetPhysObjects(kGoodGeneralTrack).size() != 0) return;
  hists.at("lbl_cut_flow_all_"+datasetName)->Fill(cutThrough++); // 2
  
  if(saveCalosFailingNEE){
    map<ECaloType, bool> failingCalo;
    bool failedNEE = event.HasAdditionalTowers(failingCalo);
    for(ECaloType caloType : calotypes){
      if(failingCalo[caloType]) hists.at("lbl_nee_failing_all_"+datasetName)->Fill(caloType);
    }
    if(failedNEE) return;
  }
  else{
    if(event.HasAdditionalTowers()) return;
  }
  hists.at("lbl_cut_flow_all_"+datasetName)->Fill(cutThrough++); // 3
  
  if(saveTriphotonHists) fillTriphotonHists(event, hists, datasetName);
  
  if(event.GetPhysObjects(kGoodPhoton).size() != 2) return;
  hists.at("lbl_cut_flow_all_"+datasetName)->Fill(cutThrough++); // 4
  
  TLorentzVector diphoton = physObjectProcessor.GetDiphoton(*event.GetPhysObjects(kGoodPhoton)[0],
                                                            *event.GetPhysObjects(kGoodPhoton)[1]);
  
  if(diphoton.M() < config.params("diphotonMinMass")) return;
  hists.at("lbl_cut_flow_all_"+datasetName)->Fill(cutThrough++); // 5
  
  if(diphoton.Pt() > config.params("diphotonMaxPt")) return;
  hists.at("lbl_cut_flow_all_"+datasetName)->Fill(cutThrough++); // 6
  
  if(fabs(diphoton.Rapidity()) > config.params("diphotonMaxRapidity")) return;
  hists.at("lbl_cut_flow_all_"+datasetName)->Fill(cutThrough++); // 7
  
  double aco = physObjectProcessor.GetAcoplanarity(*event.GetPhysObjects(kGoodPhoton)[0],
                                                   *event.GetPhysObjects(kGoodPhoton)[1]);
  hists.at("lbl_acoplanarity_all_"+datasetName)->Fill(aco);
  
  string suffix;
  if(aco > 0.01){
    suffix = "high_aco";
  }
  else{
    suffix = "low_aco";
    hists.at("lbl_cut_flow_all_"+datasetName)->Fill(cutThrough++); // 8
  }
  
  fillPhotonHists(  event, hists, datasetName, suffix);
  fillPhotonHists(  event, hists, datasetName, "all");
  fillDiphotonHists(event, hists, datasetName, suffix);
  fillDiphotonHists(event, hists, datasetName, "all");
  fillHFnoiseHists( event, hists, datasetName, "lbl", suffix);
  fillHFnoiseHists( event, hists, datasetName, "lbl", "all");
}

void fillCHEhistograms(Event &event, const map<string, TH1D*> &hists, string datasetName)
{
  if(checkTriggers && !event.HasDoubleEG2Trigger()) return;
  if(event.HasAdditionalTowers()) return;
  
  fillTracksHists(event, hists, datasetName, "all");
  
  auto photons = event.GetPhysObjects(kGoodPhoton);
  if(photons.size() != 2) return;

  TLorentzVector diphoton = physObjectProcessor.GetDiphoton(*photons[0], *photons[1]);
  if(diphoton.M()  < config.params("diphotonMinMass")) return;
  if(diphoton.Pt() > config.params("diphotonMaxPt")) return;
  
  fillTracksHists(event, hists, datasetName, "two_photons");
  
  double aco = physObjectProcessor.GetAcoplanarity(*photons[0], *photons[1]);
  fillTracksHists(event, hists, datasetName, aco > config.params("diphotonMaxAco") ? "high_aco" : "low_aco");
}

void fillQEDHistograms(Event &event, const map<string, TH1D*> &hists, string datasetName)
{
  int cutThrough=0;
  hists.at("qed_cut_flow_all_"+datasetName)->Fill(cutThrough++); // 0
    
  if(checkTriggers && !event.HasDoubleEG2Trigger()) return;
  hists.at("qed_cut_flow_all_"+datasetName)->Fill(cutThrough++); // 1
  
  if(event.HasAdditionalTowers()) return;
  hists.at("qed_cut_flow_all_"+datasetName)->Fill(cutThrough++); // 2
  
  if(event.GetPhysObjects(kGoodGeneralTrack).size() != 2) return;
  hists.at("qed_cut_flow_all_"+datasetName)->Fill(cutThrough++); // 3
  
  if(event.GetPhysObjects(kGoodMatchedElectron).size() != 2) return;
  hists.at("qed_cut_flow_all_"+datasetName)->Fill(cutThrough++); // 4
  
  if(event.GetPhysObjects(kGoodMatchedElectron)[0]->GetCharge() ==
     event.GetPhysObjects(kGoodMatchedElectron)[1]->GetCharge()){
    fillDielectronHists(event, hists, datasetName, "samesign", "all");
    return;
  }
  hists.at("qed_cut_flow_all_"+datasetName)->Fill(cutThrough++); // 5
  
  TLorentzVector dielectron = physObjectProcessor.GetDielectron(*event.GetPhysObjects(kGoodMatchedElectron)[0],
                                                                *event.GetPhysObjects(kGoodMatchedElectron)[1]);
  
  if(dielectron.M() < config.params("dielectronMinMass")) return;
  hists.at("qed_cut_flow_all_"+datasetName)->Fill(cutThrough++); // 6
  
  if(dielectron.Pt() > config.params("dielectronMaxPt")) return;
  hists.at("qed_cut_flow_all_"+datasetName)->Fill(cutThrough++); // 7
  
  if(fabs(dielectron.Rapidity()) > config.params("dielectronMaxRapidity")) return;
  hists.at("qed_cut_flow_all_"+datasetName)->Fill(cutThrough++); // 8
  
  double aco = physObjectProcessor.GetAcoplanarity(*event.GetPhysObjects(kGoodMatchedElectron)[0],
                                                   *event.GetPhysObjects(kGoodMatchedElectron)[1]);
  
  hists.at("qed_acoplanarity_all_"+datasetName)->Fill(aco);
  
  fillElectronHists(  event, hists, datasetName, "all");
  fillDielectronHists(event, hists, datasetName, "qed", "all");
  fillHFnoiseHists(   event, hists, datasetName, "qed", "all");
}

/// Creates histograms, cut through and event counters for given dataset name, for each
/// histogram specified in `histParams` vector.
void InitializeHistograms(map<string, TH1D*> &hists, string datasetType, string suffix="")
{
  if(suffix != "") suffix = "_" + suffix;
  
  for(auto &[histName, nBins, min, max] : histParams){
    string title = histName + suffix + "_" + datasetType;
    if(hists.find(title) != hists.end()) continue;
    hists[title] = new TH1D(title.c_str(), title.c_str(), nBins, min, max);
  }
}

int main(int argc, char* argv[])
{
  if(argc != 1 && argc != 5){
    cout<<"This app requires 0 or 4 parameters."<<endl;
    cout<<"./prepareBasicPlots configPath inputPath outputPath datasetName[Data|QED_SC|QED_SL|LbL|CEP]"<<endl;
    exit(0);
  }
  string inputPath = "";
  string sampleName = "";
  
  if(argc == 5){
    configPath = argv[1];
    inputPath  = argv[2];
    outputPath = argv[3];
    sampleName = argv[4];
  }
  config = ConfigManager(configPath);
  
  map<string, TH1D*> hists;
  
  TFile *outFile = new TFile(outputPath.c_str(), "recreate");
  
  
  
  if(inputPath==""){
    for(auto dataset : datasetsToAnalyze){
      for(string suffix : suffixes){
        InitializeHistograms(hists, datasetName.at(dataset), suffix);
      }
    }
    
    for(auto dataset : datasetsToAnalyze){
      string name = datasetName.at(dataset);
      
      cout<<"Creating "<<name<<" plots"<<endl;
      
      auto events = make_unique<EventProcessor>(inFileNames.at(dataset));
      
      for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
        if(iEvent%1000 == 0) cout<<"Processing event "<<iEvent<<endl;
        if(iEvent >= config.params("maxEvents")) break;
        
        auto event = events->GetEvent(iEvent);

        event->GetPhysObjects(kGoodElectron, hists.at("qed_electron_cutflow_all_"+name));
        event->GetPhysObjects(kGoodGeneralTrack, hists.at("tracks_cut_flow_all_"+name));
        
        fillLbLHistograms(*event, hists, name);
        fillCHEhistograms(*event, hists, name);
        fillQEDHistograms(*event, hists, name);
      }
      
      outFile->cd();
      for(auto &[histName, hist] : hists){
        if(histName.find(name) != string::npos) hist->Write();
      }
    }
  }
  else{
    auto events = make_unique<EventProcessor>(inputPath);
    
    for(string suffix : suffixes){
      InitializeHistograms(hists, sampleName, suffix);
    }
    
    for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
      if(iEvent%1000 == 0) cout<<"Processing event "<<iEvent<<endl;
      if(iEvent >= config.params("maxEvents")) break;
      
      auto event = events->GetEvent(iEvent);
      
      // run this here just to save electron cut flow hist
      event->GetPhysObjects(kGoodElectron, hists.at("qed_electron_cutflow_all_"+sampleName));
      event->GetPhysObjects(kGoodGeneralTrack, hists.at("tracks_cut_flow_all_"+sampleName));
      
      fillLbLHistograms(*event, hists, sampleName);
      fillCHEhistograms(*event, hists, sampleName);
      fillQEDHistograms(*event, hists, sampleName);
    }
    
    outFile->cd();
    for(auto &[histName, hist] : hists) hist->Write();
  }

  cout<<"N events with 3 photons: "<<nThreePhotonEvents<<endl;
  
  outFile->Close();
  
}
