//  prepareAcoplanarityPlots.cpp
//
//  Created by Jeremi Niedziela on 31/07/2019.

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"
#include "EventDisplay.hpp"
#include "Logger.hpp"

string configPath = "configs/preparePlots_default.md";
string outputPath = "results/basicPlots_test.root";

bool saveCalosFailingNEE = true;
bool saveTriphotonHists = true;
bool checkTriggers = false;

int nThreePhotonEvents = 0;

// Only those datasets will be analyzed
const vector<EDataset> datasetsToAnalyze = {
  kData,
  //  kData_SingleEG3,
  //  kData_recoEff,
  //  kData_triggerEff,
  //  kData_HFveto,
  //  kData_exclusivity,
//  kData_LbLsignal,
//  kData_QEDsignal,
//    kMCqedSC,
  //  kMCqedSC_SingleEG3,
  //  kMCqedSC_recoEff,
  //  kMCqedSC_triggerEff,
  //  kMCqedSC_HFveto,
  //  kMCqedSC_exclusivity,
//  kMCqedSC_LbLsignal,
//  kMCqedSC_QEDsignal,
  //  kMCqedSL,
//    kMClbl,
//    kMCcep
};

vector<string> suffixes = {
  "all", "low_aco", "high_aco", "pass_qed", "pass_lbl",  "good_pass_qed", "good_pass_lbl",
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
  {"lbl_EB_leading_tower"   , 200 , 0   , 20    },
  {"lbl_EE_leading_tower"   , 200 , 0   , 20    },
  {"lbl_HB_leading_tower"   , 200 , 0   , 20    },
  {"lbl_HE_leading_tower"   , 200 , 0   , 20    },
  {"lbl_HFp_leading_tower"  , 200 , 0   , 20    },
  {"lbl_HFm_leading_tower"  , 200 , 0   , 20    },
  {"lbl_n_all_photons"      , 100 , 0   , 100   },
  {"lbl_n_all_calo_towers"  , 100 , 0   , 100   },
  {"lbl_n_all_L1EG"         , 100 , 0   , 100   },
  {"lbl_zdc_energy"         , 1000, 0   , 50000 },
  {"lbl_n_zdc"              , 100 , 0   , 100   },
  {"lbl_bad_photon_et"      , 100 , 0   , 100.0 },
  {"lbl_bad_photon_eta"     , 6   ,-2.4 , 2.4   },
  {"lbl_bad_photon_phi"     , 8   ,-4.0 , 4.0   },
  {"lbl_n_pixel_tracks"     , 100 , 0   , 100   },
  {"lbl_zdc_sum_energy"     , 20000, 0   , 1000000 },
  {"lbl_zdc_sum_energy_pos" , 20000, 0   , 1000000 },
  {"lbl_zdc_sum_energy_neg" , 20000, 0   , 1000000 },
  
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
  {"qed_EB_leading_tower"   , 200 , 0   , 20    },
  {"qed_EE_leading_tower"   , 200 , 0   , 20    },
  {"qed_HB_leading_tower"   , 200 , 0   , 20    },
  {"qed_HE_leading_tower"   , 200 , 0   , 20    },
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
  {"track_dxy"              ,300000,-15  , 15    },
  {"track_dz"               ,100000,-50  , 50    },
  {"track_dxy_over_sigma"   , 1000, 0   , 100   },
  {"track_dz_over_sigma"    , 1000, 0   , 100   },
  
  {"track_dxy_from_bs"      ,300000,-15  , 15    },
  {"track_dz_from_bs"       ,100000,-50  , 50    },
  
  {"track_dxy_1_track"      ,300000,-15  , 15    },
  {"track_dxy_2_track"      ,300000,-15  , 15    },
  {"track_dxy_3_track"      ,300000,-15  , 15    },
  {"track_dxy_ge4_track"    ,300000,-15  , 15    },
  
  {"track_dz_1_track"       ,100000,-50  , 50    },
  {"track_dz_2_track"       ,100000,-50  , 50    },
  {"track_dz_3_track"       ,100000,-50  , 50    },
  {"track_dz_ge4_track"     ,100000,-50  , 50    },

  {"track_vx"               ,300000,-15  , 15    },
  {"track_vy"               ,300000,-15  , 15    },
  {"track_vz"               ,300000,-50  , 50    },
  
  {"tracks_cut_flow"        , 15  , 0   , 15    },
  
  {"nDisplacedTracks"       , 2000, 0   , 2000  },
  {"nDedxHits"              , 2000, 0   , 2000  },
  {"nPixelClusters"         , 2000, 0   , 2000  },
  {"nPixelRecHits"          , 2000, 0   , 2000  },
  
  {"zdc_sum_energy_pos"     , 20000, 0   , 1000000 },
  {"zdc_sum_energy_neg"     , 20000, 0   , 1000000 },
  
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

void fillNobjectsHists(Event &event, const map<string, TH1D*> &hists, string datasetName, string suffix="")
{
  if(suffix != "") suffix += "_";
  
  hists.at("lbl_n_all_photons_"+suffix+datasetName)->Fill(event.GetPhysObjects(kPhoton).size());
  hists.at("lbl_n_all_calo_towers_"+suffix+datasetName)->Fill(event.GetPhysObjects(kCaloTower).size());
  hists.at("lbl_n_all_L1EG_"+suffix+datasetName)->Fill(event.GetPhysObjects(kL1EG).size());
  hists.at("lbl_n_pixel_tracks_"+suffix+datasetName)->Fill(event.GetPhysObjects(kPixelTrack).size());
  hists.at("lbl_n_zdc_"+suffix+datasetName)->Fill(event.GetPhysObjects(kZDC).size());
}

void fillPhotonHists(Event &event, const map<string, TH1D*> &hists, string datasetName, string suffix="")
{
  if(suffix != "") suffix += "_";
  for(auto photon : event.GetPhysObjects(kGoodPhoton)){
    hists.at("lbl_photon_et_" +suffix+datasetName)->Fill(photon->GetEt());
    hists.at("lbl_photon_eta_"+suffix+datasetName)->Fill(photon->GetEta());
    hists.at("lbl_photon_phi_"+suffix+datasetName)->Fill(photon->GetPhi());
  }
  double zdcEnergySum = 0;
  double zdcEnergySumPos = 0;
  double zdcEnergySumNeg = 0;
  
  for(auto zdc : event.GetPhysObjects(kZDC)){
    hists.at("lbl_zdc_energy_"+suffix+datasetName)->Fill(zdc->GetEnergy());
    zdcEnergySum += zdc->GetEnergy();
    
    if(zdc->GetZside() > 0) zdcEnergySumPos += zdc->GetEnergy();
    else                    zdcEnergySumNeg += zdc->GetEnergy();
  }
  hists.at("lbl_zdc_sum_energy_"+suffix+datasetName)->Fill(zdcEnergySum);
  hists.at("lbl_zdc_sum_energy_pos_"+suffix+datasetName)->Fill(zdcEnergySumPos);
  hists.at("lbl_zdc_sum_energy_neg_"+suffix+datasetName)->Fill(zdcEnergySumNeg);
  
  auto goodPhotons = event.GetPhysObjects(kGoodPhoton);
  
  for(auto photon : event.GetPhysObjects(kPhoton)){
    if(find(goodPhotons.begin(), goodPhotons.end(), photon) != goodPhotons.end()) continue;
    
    hists.at("lbl_bad_photon_et_" +suffix+datasetName)->Fill(photon->GetEt());
    hists.at("lbl_bad_photon_eta_"+suffix+datasetName)->Fill(photon->GetEta());
    hists.at("lbl_bad_photon_phi_"+suffix+datasetName)->Fill(photon->GetPhi());
  }
}

void fillZDCHists(Event &event, const map<string, TH1D*> &hists, string datasetName, string suffix="")
{
  if(suffix != "") suffix += "_";
  
  double zdcEnergySumPos = 0;
  double zdcEnergySumNeg = 0;
  
  for(auto zdc : event.GetPhysObjects(kZDC)){
    if(zdc->GetZside() > 0) zdcEnergySumPos += zdc->GetEnergy();
    else                    zdcEnergySumNeg += zdc->GetEnergy();
  }
  
  hists.at("zdc_sum_energy_pos_"+suffix+datasetName)->Fill(zdcEnergySumPos);
  hists.at("zdc_sum_energy_neg_"+suffix+datasetName)->Fill(zdcEnergySumNeg);
  
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

void fillNoiseHists(Event &event, const map<string, TH1D*> &hists, string datasetName, string sample, string suffix="")
{
  if(suffix != "") suffix += "_";
  
  event.SortCaloTowersByEnergy();
  
  map<ECaloType, bool> leadingFilled;
  for(auto calo : calotypes) leadingFilled[calo] = false;
  
  PhysObjects towers = event.GetPhysObjects(kCaloTower);
  
  for(auto tower : towers){
    
    ECaloType subdetHad = tower->GetTowerSubdetHad();
    ECaloType subdetEm = tower->GetTowerSubdetEm();
    
    if(subdetEm==kEB){
      if(   !event.IsOverlappingWithGoodPhoton(*tower)
         && !event.IsOverlappingWithGoodElectron(*tower)){
        if(!leadingFilled[kEB]){
          hists.at(sample+"_EB_leading_tower_"+suffix+datasetName)->Fill(tower->GetEnergyEm());
          leadingFilled[kEB] = true;
        }
      }
    }
    if(subdetEm==kEE){
      if(fabs(tower->GetEta()) < config.params("maxEtaEEtower")
         && !event.IsOverlappingWithGoodPhoton(*tower)
         && !event.IsOverlappingWithGoodElectron(*tower)
         && !physObjectProcessor.IsInHEM(*tower)){
        if(!leadingFilled[kEE]){
          hists.at(sample+"_EE_leading_tower_"+suffix+datasetName)->Fill(tower->GetEnergyEm());
          leadingFilled[kEE] = true;
        }
      }
    }
    if(subdetHad==kHB){
      if(!leadingFilled[kHB]){
        hists.at(sample+"_HB_leading_tower_"+suffix+datasetName)->Fill(tower->GetEnergyHad());
        leadingFilled[kHB] = true;
      }
    }
    if(subdetHad==kHE){
      if(!leadingFilled[kHE]){
        hists.at(sample+"_HE_leading_tower_"+suffix+datasetName)->Fill(tower->GetEnergyHad());
        leadingFilled[kHE] = true;
      }
    }
    if(subdetHad==kHFp){
      hists.at(sample+"_HFp_"+suffix+datasetName)->Fill(tower->GetEnergy());
      
      if(!leadingFilled[kHFp]){
        hists.at(sample+"_HFp_leading_tower_"+suffix+datasetName)->Fill(tower->GetEnergy());
        leadingFilled[kHFp] = true;
      }
    }
    if(subdetHad==kHFm){
      hists.at(sample+"_HFm_"+suffix+datasetName)->Fill(tower->GetEnergy());
      if(!leadingFilled[kHFm]){
        hists.at(sample+"_HFm_leading_tower_"+suffix+datasetName)->Fill(tower->GetEnergy());
        leadingFilled[kHFm] = true;
      }
    }
  }
}

void fillTracksHists(Event &event, const map<string, TH1D*> &hists, EDataset dataset, string suffix="")
{
  string name = datasetName.at(dataset);
  if(suffix != "") suffix += "_";
  
  PhysObjects tracksLowPt, tracksHighPt;
  
  int nTracks = (int)event.GetPhysObjects(kGeneralTrack).size();
  
  hists.at("nTracks_"+suffix+name)->Fill(nTracks);
  
  hists.at("nDisplacedTracks_"+suffix+name)->Fill(event.GetNdisplacedTracks());
  hists.at("nDedxHits_"+suffix+name)->Fill(event.GetNdedxHits());
  hists.at("nPixelClusters_"+suffix+name)->Fill(event.GetNpixelClusters());
  hists.at("nPixelRecHits_"+suffix+name)->Fill(event.GetNpixelRecHits());
  
  for(auto track : event.GetPhysObjects(kGeneralTrack)){
    double trackPt = track->GetPt();
    hists.at("track_pt_"+suffix+name)->Fill(trackPt);
    hists.at("track_eta_"+suffix+name)->Fill(track->GetEta());
    hists.at("track_phi_"+suffix+name)->Fill(track->GetPhi());
    
    hists.at("track_missing_hits_"  + suffix + name)->Fill(track->GetNmissingHits());
    hists.at("track_valid_hits_"    + suffix + name)->Fill(track->GetNvalidHits());
    hists.at("track_purity_"        + suffix + name)->Fill(track->GetPurity());
    hists.at("track_charge_"        + suffix + name)->Fill(track->GetCharge());
    hists.at("track_chi2_"          + suffix + name)->Fill(track->GetChi2());
    hists.at("track_dxy_"           + suffix + name)->Fill(track->GetDxy());
    
    hists.at("track_dxy_from_bs_"   + suffix + name)->Fill(track->GetXYdistanceFromBeamSpot(dataset));
    hists.at("track_dz_from_bs_"    + suffix + name)->Fill(track->GetZdistanceFromBeamSpot(dataset));
    
    if(nTracks==1){
      hists.at("track_dxy_1_track_" + suffix + name)->Fill(track->GetDxy());
      hists.at("track_dz_1_track_"  + suffix + name)->Fill(track->GetDz());
    }
    if(nTracks==2){
      hists.at("track_dxy_2_track_" + suffix + name)->Fill(track->GetDxy());
      hists.at("track_dz_2_track_"  + suffix + name)->Fill(track->GetDz());
    }
    if(nTracks==3){
      hists.at("track_dxy_3_track_" + suffix + name)->Fill(track->GetDxy());
      hists.at("track_dz_3_track_"  + suffix + name)->Fill(track->GetDz());
    }
    if(nTracks>=4){
      hists.at("track_dxy_ge4_track_" + suffix + name)->Fill(track->GetDxy());
      hists.at("track_dz_ge4_track_"  + suffix + name)->Fill(track->GetDz());
    }
    
    hists.at("track_dz_"            + suffix + name)->Fill(track->GetDz());
    hists.at("track_dxy_over_sigma_"+ suffix + name)->Fill(fabs(track->GetDxy()/track->GetDxyErr()));
    hists.at("track_dz_over_sigma_" + suffix + name)->Fill(fabs(track->GetDz()/track->GetDzErr()));
    hists.at("track_vx_"            + suffix + name)->Fill(track->GetVertexX());
    hists.at("track_vy_"            + suffix + name)->Fill(track->GetVertexY());
    hists.at("track_vz_"            + suffix + name)->Fill(track->GetVertexZ());
    
    if(trackPt < 0.1) tracksLowPt.push_back(track);
    else              tracksHighPt.push_back(track);
  }
  
  hists.at("nTracks_good_"+suffix+name)->Fill(event.GetPhysObjects(kGoodGeneralTrack).size());
  
  for(auto track : event.GetPhysObjects(kGoodGeneralTrack)){
    hists.at("track_pt_good_"+suffix+name)->Fill(track->GetPt());
    hists.at("track_eta_good_"+suffix+name)->Fill(track->GetEta());
    hists.at("track_phi_good_"+suffix+name)->Fill(track->GetPhi());
  }
}

void fillLbLHistograms(Event &event, const map<string, TH1D*> &hists, EDataset dataset)
{
  string name = datasetName.at(dataset);
  
  int cutThrough=0;
  hists.at("lbl_cut_flow_all_"+name)->Fill(cutThrough++); // 0
  
  if(checkTriggers && !event.HasTrigger(kDoubleEG2noHF)) return;
  hists.at("lbl_cut_flow_all_"+name)->Fill(cutThrough++); // 1
  
  if(event.GetPhysObjects(kGoodGeneralTrack).size() > config.params("maxNtracks")) return;
  hists.at("lbl_cut_flow_all_"+name)->Fill(cutThrough++); // 2
  
  if(event.GetPhysObjects(kPixelTrack).size() > config.params("maxNpixelTracks")) return;
  hists.at("lbl_cut_flow_all_"+name)->Fill(cutThrough++); // 3
  
  if(event.GetNpixelRecHits() > config.params("maxNpixelRecHits")) return;
  hists.at("lbl_cut_flow_all_"+name)->Fill(cutThrough++); // 4
  
   double zdcEnergySum = 0;
   double zdcEnergySumPos = 0;
   double zdcEnergySumNeg = 0;
   
   for(auto zdc : event.GetPhysObjects(kZDC)){
     zdcEnergySum += zdc->GetEnergy();
     
     if(zdc->GetZside() > 0) zdcEnergySumPos += zdc->GetEnergy();
     else                    zdcEnergySumNeg += zdc->GetEnergy();
   }
  
  if(zdcEnergySum > config.params("maxTotalZDCenergy")) return;
  if(zdcEnergySumPos > config.params("maxTotalZDCenergyPerSide") &&
     zdcEnergySumNeg > config.params("maxTotalZDCenergyPerSide")) return;
  
  hists.at("lbl_cut_flow_all_"+name)->Fill(cutThrough++); // 5
  
  if(saveCalosFailingNEE){
    map<ECaloType, bool> failingCalo;
    bool failedNEE = event.HasAdditionalTowers(failingCalo);
    for(ECaloType caloType : calotypes){
      if(failingCalo[caloType]) hists.at("lbl_nee_failing_all_"+name)->Fill(caloType);
    }
    if(failedNEE) return;
  }
  else{
    if(event.HasAdditionalTowers()) return;
  }
  hists.at("lbl_cut_flow_all_"+name)->Fill(cutThrough++); // 6
  
  if(saveTriphotonHists) fillTriphotonHists(event, hists, name);
  
  if(event.GetPhysObjects(kGoodPhoton).size() != 2) return;
  hists.at("lbl_cut_flow_all_"+name)->Fill(cutThrough++); // 7
  
  TLorentzVector diphoton = physObjectProcessor.GetDiphoton(*event.GetPhysObjects(kGoodPhoton)[0],
                                                            *event.GetPhysObjects(kGoodPhoton)[1]);
  
  if(diphoton.M() < config.params("diphotonMinMass")) return;
  hists.at("lbl_cut_flow_all_"+name)->Fill(cutThrough++); // 8
  
  if(diphoton.Pt() > config.params("diphotonMaxPt")) return;
  hists.at("lbl_cut_flow_all_"+name)->Fill(cutThrough++); // 9
  
  if(fabs(diphoton.Rapidity()) > config.params("diphotonMaxRapidity")) return;
  hists.at("lbl_cut_flow_all_"+name)->Fill(cutThrough++); // 10
  
  double aco = physObjectProcessor.GetAcoplanarity(*event.GetPhysObjects(kGoodPhoton)[0],
                                                   *event.GetPhysObjects(kGoodPhoton)[1]);
  hists.at("lbl_acoplanarity_all_"+name)->Fill(aco);
  
  string suffix;
  if(aco > 0.01){
    suffix = "high_aco";
  }
  else{
    suffix = "low_aco";
    hists.at("lbl_cut_flow_all_"+name)->Fill(cutThrough++); // 11
  }
  
  fillNobjectsHists(  event, hists, name, suffix);
  fillNobjectsHists(  event, hists, name, "all");
  fillPhotonHists(  event, hists, name, suffix);
  fillPhotonHists(  event, hists, name, "all");
  fillDiphotonHists(event, hists, name, suffix);
  fillDiphotonHists(event, hists, name, "all");
  fillNoiseHists(   event, hists, name, "lbl", suffix);
  fillNoiseHists(   event, hists, name, "lbl", "all");
  fillTracksHists(  event, hists, dataset, "pass_lbl");

  // we found a good event!! cool, dump it to the log
  Log(2) << "PASSING! Run=" << event.GetRunNumber() << " LS=" << event.GetLumiSection() << " Evt=" << event.GetEventNumber() << " aco=" << aco << "\n";
}

void fillCHEhistograms(Event &event, const map<string, TH1D*> &hists, EDataset dataset)
{
  if(checkTriggers && !event.HasTrigger(kDoubleEG2noHF)) return;
  if(event.HasAdditionalTowers()) return;
  
  fillTracksHists(event, hists, dataset, "all");
  
  auto photons = event.GetPhysObjects(kGoodPhoton);
  if(photons.size() != 2) return;

  TLorentzVector diphoton = physObjectProcessor.GetDiphoton(*photons[0], *photons[1]);
  if(diphoton.M()  < config.params("diphotonMinMass")) return;
  if(diphoton.Pt() > config.params("diphotonMaxPt")) return;
  
  fillTracksHists(event, hists, dataset, "two_photons");
  
  double aco = physObjectProcessor.GetAcoplanarity(*photons[0], *photons[1]);
  fillTracksHists(event, hists, dataset, aco > config.params("diphotonMaxAco") ? "high_aco" : "low_aco");
}

void fillQEDHistograms(Event &event, const map<string, TH1D*> &hists, EDataset dataset)
{
  string name = datasetName.at(dataset);
  
  int cutThrough=0;
  hists.at("qed_cut_flow_all_"+name)->Fill(cutThrough++); // 0
    
  if(checkTriggers && !event.HasTrigger(kDoubleEG2noHF)) return;
  hists.at("qed_cut_flow_all_"+name)->Fill(cutThrough++); // 1
  
  if(event.HasAdditionalTowers()) return;
  hists.at("qed_cut_flow_all_"+name)->Fill(cutThrough++); // 2
  
  if(event.GetPhysObjects(kGoodGeneralTrack).size() != 2) return;
  hists.at("qed_cut_flow_all_"+name)->Fill(cutThrough++); // 3
  
  if(event.GetPhysObjects(kGoodMatchedElectron).size() != 2) return;
  hists.at("qed_cut_flow_all_"+name)->Fill(cutThrough++); // 4
  
  if(event.GetPhysObjects(kGoodMatchedElectron)[0]->GetCharge() ==
     event.GetPhysObjects(kGoodMatchedElectron)[1]->GetCharge()){
    fillDielectronHists(event, hists, name, "samesign", "all");
    return;
  }
  hists.at("qed_cut_flow_all_"+name)->Fill(cutThrough++); // 5
  
  TLorentzVector dielectron = physObjectProcessor.GetDielectron(*event.GetPhysObjects(kGoodMatchedElectron)[0],
                                                                *event.GetPhysObjects(kGoodMatchedElectron)[1]);
  
  if(dielectron.M() < config.params("dielectronMinMass")) return;
  hists.at("qed_cut_flow_all_"+name)->Fill(cutThrough++); // 6
  
  if(dielectron.Pt() > config.params("dielectronMaxPt")) return;
  hists.at("qed_cut_flow_all_"+name)->Fill(cutThrough++); // 7
  
  if(fabs(dielectron.Rapidity()) > config.params("dielectronMaxRapidity")) return;
  hists.at("qed_cut_flow_all_"+name)->Fill(cutThrough++); // 8
  
  double aco = physObjectProcessor.GetAcoplanarity(*event.GetPhysObjects(kGoodMatchedElectron)[0],
                                                   *event.GetPhysObjects(kGoodMatchedElectron)[1]);
  
  hists.at("qed_acoplanarity_all_"+name)->Fill(aco);
  
  fillElectronHists(  event, hists, name, "all");
  fillDielectronHists(event, hists, name, "qed", "all");
  fillNoiseHists(     event, hists, name, "qed", "all");
  fillTracksHists(    event, hists, dataset, "pass_qed");
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
    Log(0)<<"This app requires 0 or 4 parameters.\n";
    Log(0)<<"./prepareBasicPlots configPath inputPath outputPath datasetName[Data|QED_SC|QED_SL|LbL|CEP]\n";
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
      
      Log(0)<<"Creating "<<name<<" plots\n";
      
      auto events = make_unique<EventProcessor>(inFileNames.at(dataset), dataset);
      
      for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
        if(iEvent%1000 == 0)  Log(1)<<"Processing event "<<iEvent<<"\n";
        if(iEvent%10000 == 0) Log(0)<<"Processing event "<<iEvent<<"\n";
        if(iEvent >= config.params("maxEvents")) break;
        
        auto event = events->GetEvent(iEvent);

        event->GetPhysObjects(kGoodElectron, hists.at("qed_electron_cutflow_all_"+name));
        event->GetPhysObjects(kGoodGeneralTrack, hists.at("tracks_cut_flow_all_"+name));
        
        fillLbLHistograms(*event, hists, dataset);
        fillCHEhistograms(*event, hists, dataset);
        fillQEDHistograms(*event, hists, dataset);
        fillZDCHists(*event, hists, datasetName.at(dataset), "all");
      }
      
      outFile->cd();
      for(auto &[histName, hist] : hists){
        if(histName.find(name) != string::npos) hist->Write();
      }
    }
  }
  else{
    EDataset dataset = nDatasets;
       
    if(sampleName == "Data")    dataset = kData;
    if(sampleName == "QED_SC")  dataset = kMCqedSC;
    if(sampleName == "QED_SL")  dataset = kMCqedSL;
    if(sampleName == "LbL")     dataset = kMClbl;
    if(sampleName == "CEP")     dataset = kMCcep;
       
    
    auto events = make_unique<EventProcessor>(inputPath, dataset);
    
    for(string suffix : suffixes){
      InitializeHistograms(hists, sampleName, suffix);
    }
    
   
    if(dataset == nDatasets){
      Log(0)<<"ERROR -- unknown dataset name provided: "<<sampleName<<"\n";
      exit(0);
    }
    
    for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
      if(iEvent%1000 == 0)  Log(1)<<"Processing event "<<iEvent<<"\n";
      if(iEvent%10000 == 0) Log(0)<<"Processing event "<<iEvent<<"\n";
      if(iEvent >= config.params("maxEvents")) break;
      
      auto event = events->GetEvent(iEvent);
      
      // run this here just to save electron cut flow hist
      event->GetPhysObjects(kGoodElectron, hists.at("qed_electron_cutflow_all_"+sampleName));
      event->GetPhysObjects(kGoodGeneralTrack, hists.at("tracks_cut_flow_all_"+sampleName));
      
      fillLbLHistograms(*event, hists, dataset);
      fillCHEhistograms(*event, hists, dataset);
      fillQEDHistograms(*event, hists, dataset);
      fillZDCHists(*event, hists, sampleName, "all");
    }
    
    outFile->cd();
    for(auto &[histName, hist] : hists) hist->Write();
  }

  Log(0)<<"N events with 3 photons: "<<nThreePhotonEvents<<"\n";
  
  outFile->Close();
  
}
