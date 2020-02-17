//  prepareAcoplanarityPlots.cpp
//
//  Created by Jeremi Niedziela on 31/07/2019.

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"
#include "EventDisplay.hpp"

string configPath = "configs/efficiencies.md";
string outputPath = "results/basicPlots_test.root";

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
  //  kMCqedSC,
  //  kMCqedSC_SingleEG3,
  //  kMCqedSC_recoEff,
  //  kMCqedSC_triggerEff,
  //  kMCqedSC_HFveto,
  //  kMCqedSC_exclusivity,
//  kMCqedSC_LbLsignal,
//  kMCqedSC_QEDsignal,
  //  kMCqedSL,
  //  kMClbl,
  //  kMCcep
};

vector<tuple<string, int, double, double>> histParams = {
  // title                   nBins min   max
  {"lbl_acoplanarity"       , 20  , 0   , 0.1   },
  {"lbl_photon_et"          , 10  , 0   , 10.0  },
  {"lbl_photon_eta"         , 6   ,-2.4 , 2.4   },
  {"lbl_photon_phi"         , 8   , -4.0, 4.0   },
  {"lbl_diphoton_mass"      , 8   , 0   , 20.0  },
  {"lbl_diphoton_rapidity"  , 6   ,-2.4 , 2.4   },
  {"lbl_diphoton_pt"        , 5   , 0   , 1.0   },
  
  {"lbl_triphoton_mass"     , 800 , 0   , 200.0  },
  {"lbl_triphoton_rapidity" , 24  ,-2.4 , 2.4   },
  {"lbl_triphoton_pt"       , 500 , 0   , 100.0   },
  
  {"lbl_cut_through"        , 15  , 0   , 15    },
  
  {"qed_acoplanarity"       , 30  , 0   , 0.06  },
  {"qed_electron_pt"        , 40  , 0   , 20.0  },
  {"qed_electron_eta"       , 23  , -2.3, 2.3   },
  {"qed_electron_phi"       , 20  , -4.0, 4.0   },
  {"qed_dielectron_mass"    , 200 , 0   , 200.0 },
  {"qed_dielectron_rapidity", 30  ,-3.0 , 3.0   },
  {"qed_dielectron_pt"      , 20  , 0   , 2.0   },
  {"qed_cut_through"        , 15  , 0   , 15    },
  {"qed_electron_cutflow"   , 15  , 0   , 15    },
  
  {"qed_HFp"                , 200 , 0   , 20    },
  {"qed_HFm"                , 200 , 0   , 20    },
  {"qed_HFp_leading_tower"  , 200 , 0   , 20    },
  {"qed_HFm_leading_tower"  , 200 , 0   , 20    },
  
  {"qed_acoplanarity_no_cuts"       , 30  , 0   , 0.06  },
  {"qed_electron_pt_no_cuts"        , 40  , 0   , 20.0  },
  {"qed_electron_eta_no_cuts"       , 23  , -2.3, 2.3   },
  {"qed_electron_phi_no_cuts"       , 20  , -4.0, 4.0   },
  {"qed_dielectron_mass_no_cuts"    , 1000 , 0   , 200.0 },
  {"qed_dielectron_mass_low_no_cuts", 2400 , 0   , 12.0 },
  {"qed_dielectron_rapidity_no_cuts", 30  ,-3.0 , 3.0   },
  {"qed_dielectron_pt_no_cuts"      , 20  , 0   , 2.0   },
  
  {"qed_aco_HF_gt_5"        , 30  , 0   , 0.06   },
  {"qed_aco_HF_gt_10"       , 30  , 0   , 0.06   },
  {"qed_aco_HF_gt_15"       , 30  , 0   , 0.06   },
  
  {"qed_HFp_no_cuts"                , 200 , 0   , 20    },
  {"qed_HFm_no_cuts"                , 200 , 0   , 20    },
  {"qed_HFp_leading_tower_no_cuts"  , 200 , 0   , 20    },
  {"qed_HFm_leading_tower_no_cuts"  , 200 , 0   , 20    },
  
  {"nTracks"                , 100 , 0   , 100   },
  {"nTracks_withDoubleEG2"  , 100 , 0   , 100   },
  {"tracks_cut_through"     , 10  , 0   , 10    },
  {"nTracks_pt_geq_100_MeV" , 100 , 0   , 100   },
  {"nTracks_pt_lt_100_MeV"  , 100 , 0   , 100   },
  {"track_pt"               , 500 , 0   , 5     },
};

void fillNEEcutFlowHist(TH1D *hist, int &cutFlow, ECaloType failingCalo)
{
  // in this order: HB, HE, HFp, HFm, EB, EE
  
  if(failingCalo != kHB){
    hist->Fill(cutFlow);
  }
  cutFlow++;
  if(failingCalo != kHB && failingCalo != kHE){
    hist->Fill(cutFlow);
  }
  cutFlow++;
  if(failingCalo != kHB && failingCalo != kHE && failingCalo != kHFp){
    hist->Fill(cutFlow);
  }
  cutFlow++;
  if(failingCalo != kHB && failingCalo != kHE && failingCalo != kHFp && failingCalo != kHFm){
    hist->Fill(cutFlow);
    cutFlow++;
  }
  if(failingCalo != kHB && failingCalo != kHE && failingCalo != kHFp && failingCalo != kHFm && failingCalo != kEB){
    hist->Fill(cutFlow);
  }
  cutFlow++;
  if(failingCalo != kHB && failingCalo != kHE && failingCalo != kHFp && failingCalo != kHFm && failingCalo != kEB && failingCalo != kEE){
    hist->Fill(cutFlow);
  }
  cutFlow++;
}

void fillLbLHistograms(Event &event, const map<string, TH1D*> &hists, string datasetName)
{
  int cutThrough=0;
  hists.at("lbl_cut_through_"+datasetName)->Fill(cutThrough++); // 0
  
//  if(!event.HasDoubleEG2Trigger()) return;
  hists.at("lbl_cut_through_"+datasetName)->Fill(cutThrough++); // 1
  
  if(event.GetNchargedTracks() != 0) return;
  hists.at("lbl_cut_through_"+datasetName)->Fill(cutThrough++); // 2
  
  bool checkHF = true;
  ECaloType failingCalo = nCaloTypes;
  bool failedNEE = event.HasAdditionalTowers(checkHF, &failingCalo);
  fillNEEcutFlowHist(hists.at("lbl_cut_through_"+datasetName), cutThrough, failingCalo); // 3 - 8
  if(failedNEE) return;
  
  
  auto photons = event.GetGoodPhotons();
  
//  vector<shared_ptr<PhysObject>> isolatedPhotons;
//
//  for(int i=0; i<photons.size(); i++){
//
//
//    bool hasNerbyPhotons = false;
//    for(int j=0; j<photons.size(); j++){
//      if(i==j) continue;
//
//      double deltaR = physObjectProcessor.GetDeltaR(*photons[i], *photons[j]);
////      double deltaPhi = fabs(photons[i]->GetPhi()-photons[j]->GetPhi());
//
//      if(deltaR < 0.3){
//        hasNerbyPhotons = true;
//        break;
//      }
//    }
//    if(!hasNerbyPhotons) isolatedPhotons.push_back(photons[i]);
//  }
//
//  if(isolatedPhotons.size() == 3){
//    nThreePhotonEvents++;
//    TLorentzVector triphoton = physObjectProcessor.GetTriphoton(*isolatedPhotons[0],
//                                                                *isolatedPhotons[1],
//                                                                *isolatedPhotons[2]);
//
//    hists.at("lbl_triphoton_mass_"+datasetName)->Fill(triphoton.M());
//    hists.at("lbl_triphoton_rapidity_"+datasetName)->Fill(triphoton.Rapidity());
//    hists.at("lbl_triphoton_pt_"+datasetName)->Fill(triphoton.Pt());
//
//    vector<shared_ptr<PhysObject>> emptyVector;
//
////    saveEventDisplay(emptyVector, emptyVector, emptyVector, isolatedPhotons, emptyVector, "~/Desktop/lbl_triphoton_event_displays_"+datasetName+"/");
//  }
  
  if(photons.size() != 2) return;
  hists.at("lbl_cut_through_"+datasetName)->Fill(cutThrough++); // 9
  
  TLorentzVector diphoton = physObjectProcessor.GetDiphoton(*photons[0], *photons[1]);
  
  if(diphoton.M() < 5.0) return;
  hists.at("lbl_cut_through_"+datasetName)->Fill(cutThrough++); // 10
  
  if(diphoton.Pt() > 1.0) return;
  hists.at("lbl_cut_through_"+datasetName)->Fill(cutThrough++); // 11
  
  //  if(fabs(diphoton.Rapidity()) > 2.4) return;
  hists.at("lbl_cut_through_"+datasetName)->Fill(cutThrough++); // 12
  
  double aco = physObjectProcessor.GetAcoplanarity(*photons[0], *photons[1]);
  hists.at("lbl_acoplanarity_"+datasetName)->Fill(aco);
  
  if(aco > 0.01) return;
  hists.at("lbl_cut_through_"+datasetName)->Fill(cutThrough++); // 13
  
  hists.at("lbl_photon_et_"+datasetName)->Fill(photons[0]->GetEt());
  hists.at("lbl_photon_et_"+datasetName)->Fill(photons[1]->GetEt());
  hists.at("lbl_photon_eta_"+datasetName)->Fill(photons[0]->GetEta());
  hists.at("lbl_photon_eta_"+datasetName)->Fill(photons[1]->GetEta());
  hists.at("lbl_photon_phi_"+datasetName)->Fill(photons[0]->GetPhi());
  hists.at("lbl_photon_phi_"+datasetName)->Fill(photons[1]->GetPhi());
  hists.at("lbl_diphoton_mass_"+datasetName)->Fill(diphoton.M());
  hists.at("lbl_diphoton_rapidity_"+datasetName)->Fill(diphoton.Rapidity());
  hists.at("lbl_diphoton_pt_"+datasetName)->Fill(diphoton.Pt());
  
}

void fillTracksHistograms(Event &event, const map<string, TH1D*> &hists, string datasetName)
{
  int nTracks = event.GetNgeneralTracks();
  hists.at("nTracks_"+datasetName)->Fill(nTracks);
  
  hists.at("tracks_cut_through_"+datasetName)->Fill(0); // has Double EG2 trigger
  
  if(event.HasDoubleEG2Trigger()){
    hists.at("nTracks_withDoubleEG2_"+datasetName)->Fill(nTracks);
    
    hists.at("tracks_cut_through_"+datasetName)->Fill(1); // has Double EG2 trigger
    
    if(nTracks==0) hists.at("tracks_cut_through_"+datasetName)->Fill(2); // has Double EG2 trigger and no tracks
  }
  
  if(nTracks==0) hists.at("tracks_cut_through_"+datasetName)->Fill(3); // has no tracks
  
  
  for(int iTrack=0; iTrack<nTracks; iTrack++){
    double trackPt = event.GetGeneralTrack(iTrack)->GetPt();
    hists.at("track_pt_"+datasetName)->Fill(trackPt);
    
    int iBin = nTracks+1;
    if(trackPt < 0.1){
      hists.at("nTracks_pt_lt_100_MeV_"+datasetName)->SetBinContent(iBin, hists.at("nTracks_pt_lt_100_MeV_"+datasetName)->GetBinContent(iBin)+1);
    }
    else{
      hists.at("nTracks_pt_geq_100_MeV_"+datasetName)->SetBinContent(iBin, hists.at("nTracks_pt_geq_100_MeV_"+datasetName)->GetBinContent(iBin)+1);
    }
  }
}

void fillQEDHistograms(Event &event, const map<string, TH1D*> &hists, string datasetName)
{
  // Add all necessary selection criteria here
  // ...
  int cutThrough=0;
  hists.at("qed_cut_through_"+datasetName)->Fill(cutThrough++); // 0
  
  // Put this in the beginning, as good electrons won't be re-computed again later on
  auto goodElectrons = event.GetGoodElectrons(hists.at("qed_electron_cutflow_"+datasetName));
  
  auto track1 = event.GetGeneralTrack(0);
  auto track2 = event.GetGeneralTrack(1);
  
  TLorentzVector ditrack = physObjectProcessor.GetDielectron(*track1, *track2);
  double trackAco = physObjectProcessor.GetAcoplanarity(*track1, *track2);
  
  hists.at("qed_acoplanarity_no_cuts_"+datasetName)->Fill(trackAco);
  hists.at("qed_electron_pt_no_cuts_"+datasetName)->Fill(track1->GetPt());
  hists.at("qed_electron_pt_no_cuts_"+datasetName)->Fill(track2->GetPt());
  hists.at("qed_electron_eta_no_cuts_"+datasetName)->Fill(track1->GetEta());
  hists.at("qed_electron_eta_no_cuts_"+datasetName)->Fill(track2->GetEta());
  hists.at("qed_electron_phi_no_cuts_"+datasetName)->Fill(track1->GetPhi());
  hists.at("qed_electron_phi_no_cuts_"+datasetName)->Fill(track2->GetPhi());
  hists.at("qed_dielectron_mass_no_cuts_"+datasetName)->Fill(ditrack.M());
  hists.at("qed_dielectron_mass_low_no_cuts_"+datasetName)->Fill(ditrack.M());
  hists.at("qed_dielectron_rapidity_no_cuts_"+datasetName)->Fill(ditrack.Rapidity());
  hists.at("qed_dielectron_pt_no_cuts_"+datasetName)->Fill(ditrack.Pt());
  
  event.SortCaloTowersByEnergy();
  bool leadingHFpFilled = false;
  bool leadingHFmFilled = false;
  for(auto tower : event.GetCaloTowers()){
    
    if(tower->GetEta() > minEtaHF && tower->GetEta() < maxEtaHF){
      hists.at("qed_HFp_no_cuts_"+datasetName)->Fill(tower->GetEnergy());
      
      if(!leadingHFpFilled){
        hists.at("qed_HFp_leading_tower_no_cuts_"+datasetName)->Fill(tower->GetEnergy());
        leadingHFpFilled = true;
      }
    }
    if(tower->GetEta() > -maxEtaHF && tower->GetEta() < -minEtaHF){
      hists.at("qed_HFm_no_cuts_"+datasetName)->Fill(tower->GetEnergy());
      if(!leadingHFmFilled){
        hists.at("qed_HFm_leading_tower_no_cuts_"+datasetName)->Fill(tower->GetEnergy());
        leadingHFmFilled = true;
      }
    }
  }
  
//  if(!event.HasDoubleEG2Trigger()) return;
  hists.at("qed_cut_through_"+datasetName)->Fill(cutThrough++); // 1
  
  bool checkHF = false;
  ECaloType failingCalo = nCaloTypes;
  bool failedNEE = event.HasAdditionalTowers(checkHF, &failingCalo);
  fillNEEcutFlowHist(hists.at("qed_cut_through_"+datasetName), cutThrough, failingCalo); // 2-7
  if(failedNEE) return;
  
  if(event.GetNchargedTracks() != 2) return;
  hists.at("qed_cut_through_"+datasetName)->Fill(cutThrough++); // 8
  
  vector<shared_ptr<PhysObject>> goodMatchedElectrons;
  
  for(auto electron : goodElectrons){
    for(auto &L1EG : event.GetL1EGs()){
      if(L1EG->GetEt() < 2.0) continue;
      
      if(physObjectProcessor.GetDeltaR_SC(*electron, *L1EG) < 0.3){
        goodMatchedElectrons.push_back(electron);
        break;
      }
    }
  }
  
  if(goodMatchedElectrons.size() != 2) return;
  hists.at("qed_cut_through_"+datasetName)->Fill(cutThrough++); // 9
  
  auto electron1 = goodMatchedElectrons[0];
  auto electron2 = goodMatchedElectrons[1];
  
  TLorentzVector dielectron = physObjectProcessor.GetDielectron(*electron1, *electron2);
  double aco = physObjectProcessor.GetAcoplanarity(*electron1, *electron2);
  
  // add QED specific cuts here:
  if(dielectron.M() < 5.0) return;
  hists.at("qed_cut_through_"+datasetName)->Fill(cutThrough++); // 10
  
  if(dielectron.Pt() > 1.0) return;
  hists.at("qed_cut_through_"+datasetName)->Fill(cutThrough++); // 11
  
  if(fabs(dielectron.Rapidity()) > 2.4) return;
  hists.at("qed_cut_through_"+datasetName)->Fill(cutThrough++); // 12
  
  hists.at("qed_acoplanarity_"+datasetName)->Fill(aco);
  hists.at("qed_electron_pt_"+datasetName)->Fill(electron1->GetPt());
  hists.at("qed_electron_pt_"+datasetName)->Fill(electron2->GetPt());
  hists.at("qed_electron_eta_"+datasetName)->Fill(electron1->GetEta());
  hists.at("qed_electron_eta_"+datasetName)->Fill(electron2->GetEta());
  hists.at("qed_electron_phi_"+datasetName)->Fill(electron1->GetPhi());
  hists.at("qed_electron_phi_"+datasetName)->Fill(electron2->GetPhi());
  
  
  hists.at("qed_dielectron_mass_"+datasetName)->Fill(dielectron.M());
  hists.at("qed_dielectron_rapidity_"+datasetName)->Fill(dielectron.Rapidity());
  hists.at("qed_dielectron_pt_"+datasetName)->Fill(dielectron.Pt());
  
  leadingHFpFilled = false;
  leadingHFmFilled = false;
  double leadingHFenergy = -1;
  
  for(auto tower : event.GetCaloTowers()){
    
    if(tower->GetEta() > minEtaHF && tower->GetEta() < maxEtaHF){
      hists.at("qed_HFp_"+datasetName)->Fill(tower->GetEnergy());
      
      if(!leadingHFpFilled){
        hists.at("qed_HFp_leading_tower_"+datasetName)->Fill(tower->GetEnergy());
        if(tower->GetEnergy() > leadingHFenergy) leadingHFenergy = tower->GetEnergy();
        leadingHFpFilled = true;
      }
    }
    if(tower->GetEta() > -maxEtaHF && tower->GetEta() < -minEtaHF){
      hists.at("qed_HFm_"+datasetName)->Fill(tower->GetEnergy());
      if(!leadingHFmFilled){
        hists.at("qed_HFm_leading_tower_"+datasetName)->Fill(tower->GetEnergy());
        if(tower->GetEnergy() > leadingHFenergy) leadingHFenergy = tower->GetEnergy();
        leadingHFmFilled = true;
      }
    }
  }
  
  if(leadingHFenergy >  5.0) hists.at("qed_aco_HF_gt_5_"+datasetName)->Fill(aco);
  if(leadingHFenergy > 10.0) hists.at("qed_aco_HF_gt_10_"+datasetName)->Fill(aco);
  if(leadingHFenergy > 15.0) hists.at("qed_aco_HF_gt_15_"+datasetName)->Fill(aco);
}

/// Creates histograms, cut through and event counters for given dataset name, for each
/// histogram specified in `histParams` vector.
void InitializeHistograms(map<string, TH1D*> &hists, const string &datasetType)
{
  for(auto &[histName, nBins, min, max] : histParams){
    string title = histName + "_" + datasetType;
    if(hists.find(title) != hists.end()) continue;
    hists[title] = new TH1D(title.c_str(), title.c_str(), nBins, min, max);
  }
}

int main(int argc, char* argv[])
{
  if(argc != 1 && argc != 5){
    cout<<"This app requires 0 or 4 parameters."<<endl;
    cout<<"./prepareBasicPlots configPath inputPath outputPath isMC"<<endl;
    exit(0);
  }
  string inputPath = "";
  bool isMC = false;
  
  if(argc == 5){
    configPath = argv[1];
    inputPath  = argv[2];
    outputPath = argv[3];
    isMC       = atoi(argv[4]);
  }
  config = ConfigManager(configPath);
  
  map<string, TH1D*> hists;
  
  TFile *outFile = new TFile(outputPath.c_str(), "recreate");
  
  for(auto dataset : datasetsToAnalyze){
    InitializeHistograms(hists, datasetName.at(dataset));
  }
  
  if(inputPath==""){
    
    for(auto dataset : datasetsToAnalyze){
      string name = datasetName.at(dataset);
      
      cout<<"Creating "<<name<<" plots"<<endl;
      
      auto events = make_unique<EventProcessor>(inFileNames.at(dataset));
      
      for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
        if(iEvent%1000 == 0) cout<<"Processing event "<<iEvent<<endl;
        if(iEvent >= config.params("maxEvents")) break;
        
        auto event = events->GetEvent(iEvent);
        
        if(dataset == kData_LbLsignal || dataset == kMCqedSC_LbLsignal) fillLbLHistograms(*event, hists, name);
        if(dataset == kData_QEDsignal || dataset == kMCqedSC_QEDsignal) fillQEDHistograms(*event, hists, name);
        if(dataset == kData){
          fillLbLHistograms(*event, hists, name);
          fillTracksHistograms(*event, hists, name);
          fillQEDHistograms(*event, hists, name);
        }
      }
      
      outFile->cd();
      for(auto &[histName, hist] : hists){
        if(histName.find(name) != string::npos) hist->Write();
      }
    }
  }
  else{
    auto events = make_unique<EventProcessor>(inputPath);
    
    string name = isMC ? datasetName.at(kMCqedSC) : datasetName.at(kData);
    
    for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
      if(iEvent%1000 == 0) cout<<"Processing event "<<iEvent<<endl;
      if(iEvent >= config.params("maxEvents")) break;
      
      auto event = events->GetEvent(iEvent);
      
      fillLbLHistograms(*event, hists, name);
      fillTracksHistograms(*event, hists, name);
      fillQEDHistograms(*event, hists, name);
    }
    
    outFile->cd();
    for(auto &[histName, hist] : hists) hist->Write();
  }

  cout<<"N events with 3 photons: "<<nThreePhotonEvents<<endl;
  
  outFile->Close();
  
}
