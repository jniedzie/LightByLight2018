//  prepareShowerShapePlots.cpp
//
//  Created by Jeremi Niedziela on 30/07/2019.

#include "Helpers.hpp"
#include "Event.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"
#include "Logger.hpp"
#include <fstream>


/*int run;
int ls;
int evtnb;
float photon_Et;
float photon_Eta;
float photon_Phi;
float photon_SCEt;
float photon_SCEta;
float photon_SCPhi;
float photon_SwissCross;
float photon_EtaWidth;
float photon_HoverE;
float photon_Sigmaetaeta;
float photon_SeedTime;
int ok_neuexcl;
int ok_zdcexcl;
int ok_chexcl;
*/

/// initialise tree
/*void InitTree(TTree *tr) {
  tr->Branch("run",       &run,         "run/I");
  tr->Branch("ls",        &ls,          "ls/I");
  tr->Branch("evtnb",     &evtnb,       "evtnb/I");
  tr->Branch("photon_Et",           &photon_Et,           "photon_Et/F");
  tr->Branch("photon_Eta",          &photon_Eta,          "photon_Eta/F");
  tr->Branch("photon_Phi",          &photon_Phi,          "photon_Phi/F");
  tr->Branch("photon_SCEt",         &photon_SCEt,         "photon_SCEt/F");
  tr->Branch("photon_SCEta",        &photon_SCEta,        "photon_SCEta/F");
  tr->Branch("photon_SCPhi",        &photon_SCPhi,        "photon_SCPhi/F");
  tr->Branch("photon_SwissCross",   &photon_SwissCross,   "photon_SwissCross/F");
  tr->Branch("photon_EtaWidth",     &photon_EtaWidth,     "photon_EtaWidth/F");
  tr->Branch("photon_HoverE",       &photon_HoverE,       "photon_HoverE/F");
  tr->Branch("photon_Sigmaetaeta",&photon_Sigmaetaeta,"photon_Sigmaetaeta/F");
  tr->Branch("photon_SeedTime",     &photon_SeedTime,     "photon_SeedTime/F");
  tr->Branch("ok_neuexcl",          &ok_neuexcl,          "ok_neuexcl/I");
  tr->Branch("ok_zdcexcl",          &ok_zdcexcl,          "ok_zdcexcl/I");
  tr->Branch("ok_chexcl",           &ok_chexcl,           "ok_chexcl/I");
}

// reset all variables
void ResetVars() {
  run =-999;
  ls=-999;
  evtnb =-999;
  photon_Et = -999;
  photon_Eta = -999;
  photon_Phi = -999;
  photon_SCEt = -999;
  photon_SCEta = -999;
  photon_SCPhi = -999;
  photon_SwissCross = -999;
  photon_EtaWidth = -999;
  photon_HoverE = -999;
  photon_Sigmaetaeta = -999;
  photon_SeedTime = -999;
  ok_neuexcl = -999;
  ok_zdcexcl = -999;
  ok_chexcl  = -999;
}*/
 

vector<tuple<string, int, double, double>> histParams = {
  // title               nBins min   max
  {"eEB"               , 100 , 0.  , 5.},
  {"eEE"               , 100 , 0.  , 10.},
  {"eHE"               , 100 , 0.  , 5.},
  {"eHB"               , 100 , 0.  , 5.},
  {"eHFp"              , 100 , 0.  , 10.},
  {"eHFm"              , 100 , 0.  , 10.},

  {"eEB_leadingTower"               , 100 , 0.  , 5.},
  {"eEE_leadingTower"               , 100 , 0.  , 10.},
  {"eHE_leadingTower"               , 100 , 0.  , 5.},
  {"eHB_leadingTower"               , 100 , 0.  , 5.},
  {"eHFp_leadingTower"              , 100 , 0.  , 10.},
  {"eHFm_leadingTower"              , 100 , 0.  , 10.},

};

vector<tuple<string, int, double, double, int, double, double>> histParams2D = {
  // title         nBinsX minX   maxX   nBinsY minY  maxY
  {"eEB_eta" , 100 , -1.5 , 1.5 , 100 , 0 , 5.0 },
  {"eEE_eta" , 100 , -3.0 , 3.0 , 100 , 0 , 10.0 },
  {"eHB_eta" , 100 , -1.5 , 1.5 , 100 , 0 , 5.0 },
  {"eHE_eta" , 100 , -3.0 , 3.0 , 100 , 0 , 5.0 },
  {"eHF_eta" , 100 , -5.2 , 5.2 , 100 , 0 , 10.0 },

  {"eEB_eta_phi" , 100 , -1.5 , 1.5 , 75 , -3.15 , 3.15 },
  {"eEE_eta_phi" , 100 , -3.0 , 3.0 , 75 , -3.15 , 3.15 },
  {"eHB_eta_phi" , 100 , -1.5 , 1.5 , 75 , -3.15 , 3.15 },
  {"eHE_eta_phi" , 100 , -3.0 , 3.0 , 75 , -3.15 , 3.15 },
  {"eHF_eta_phi" , 100 , -5.2 , 5.2 , 75 , -3.15 , 3.15 },

  {"eEB_eta_leadingTower" , 100 , -1.5 , 1.5 , 100 , 0 , 5.0 },
  {"eEE_eta_leadingTower" , 100 , -3.0 , 3.0 , 100 , 0 , 10.0 },
  {"eHB_eta_leadingTower" , 100 , -1.5 , 1.5 , 100 , 0 , 5.0 },
  {"eHE_eta_leadingTower" , 100 , -3.0 , 3.0 , 100 , 0 , 5.0 },
  {"eHF_eta_leadingTower" , 100 , -5.2 , 5.2 , 100 , 0 , 10.0 },

  {"eEB_eta_phi_leadingTower" , 100 , -1.5 , 1.5 , 75 , -3.15 , 3.15 },
  {"eEE_eta_phi_leadingTower" , 100 , -3.0 , 3.0 , 75 , -3.15 , 3.15 },
  {"eHB_eta_phi_leadingTower" , 100 , -1.5 , 1.5 , 75 , -3.15 , 3.15 },
  {"eHE_eta_phi_leadingTower" , 100 , -3.0 , 3.0 , 75 , -3.15 , 3.15 },
  {"eHF_eta_phi_leadingTower" , 100 , -5.2 , 5.2 , 75 , -3.15 , 3.15 },


  {"eEB_ieta" , 90 , -45 , 45 , 100 , 0 , 5.0 },
  {"eEE_ieta" , 90 , -45 , 45 , 100 , 0 , 10.0 },
  {"eHB_ieta" , 90 , -45 , 45 , 100 , 0 , 5.0 },
  {"eHE_ieta" , 90 , -45 , 45 , 100 , 0 , 5.0 },
  {"eHF_ieta" , 90 , -45 , 45 , 100 , 0 , 10.0 },

  {"eEB_ieta_iphi" , 90 , -45 , 45 , 75 , 0 , 75 },
  {"eEE_ieta_iphi" , 90 , -45 , 45 , 75 , 0 , 75 },
  {"eHB_ieta_iphi" , 90 , -45 , 45 , 75 , 0 , 75 },
  {"eHE_ieta_iphi" , 90 , -45 , 45 , 75 , 0 , 75 },
  {"eHF_ieta_iphi" , 90 , -45 , 45 , 75 , 0 , 75 },

  {"eEB_ieta_leadingTower" , 90 , -45 , 45 , 100 , 0 , 5.0 },
  {"eEE_ieta_leadingTower" , 90 , -45 , 45 , 100 , 0 , 10.0 },
  {"eHB_ieta_leadingTower" , 90 , -45 , 45 , 100 , 0 , 5.0 },
  {"eHE_ieta_leadingTower" , 90 , -45 , 45 , 100 , 0 , 5.0 },
  {"eHF_ieta_leadingTower" , 90 , -45 , 45 , 100 , 0 , 10.0 },

  {"eEB_ieta_iphi_leadingTower" , 90 , -45 , 45 , 75 , 0 , 75 },
  {"eEE_ieta_iphi_leadingTower" , 90 , -45 , 45 , 75 , 0 , 75 },
  {"eHB_ieta_iphi_leadingTower" , 90 , -45 , 45 , 75 , 0 , 75 },
  {"eHE_ieta_iphi_leadingTower" , 90 , -45 , 45 , 75 , 0 , 75 },
  {"eHF_ieta_iphi_leadingTower" , 90 , -45 , 45 , 75 , 0 , 75 },

};

double getSwisscross(shared_ptr<PhysObject> photon)
{
  double E4 = photon->GetEnergyCrystalTop() +
  photon->GetEnergyCrystalBottom() +
  photon->GetEnergyCrystalLeft() +
  photon->GetEnergyCrystalRight();
  
  double swissCross = 1 - (E4/photon->GetEnergyCrystalMax());
  
  if(E4 < 0){
    Log(1)<<"WARNING -- swiss cross cannot be calculated. The event will pass this selection automatically!!\n";
    swissCross = -999999;
  }
  
  return swissCross;
}

int eta2ieta(double eta);
int phi2iphi(double phi, int ieta);

void fillHistograms(const unique_ptr<EventProcessor> &events,
                    const map<string, TH1D*> &hists,
                    const map<string, TH2D*> &hists2D,
                    string datasetName)
{
  int nTwoGoodPho = 0;
  int selected = 0;
  int all = 0;

  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
    if(iEvent%10000==0) Log(0)<<"Processing event "<<iEvent<<"\n";
    if(iEvent >= config.params("maxEvents")) break;
    all++;

    auto event = events->GetEvent(iEvent);

    //if(event->GetPhysObjects(EPhysObjType::kGoodPhoton).size() != 2 ) continue;
    //nTwoGoodPho++;

    double leadingTowerEB = -1, leadingTowerEEp = -1, leadingTowerEEm = -1;
    double leadingTowerHB = -1, leadingTowerHEp = -1, leadingTowerHEm = -1;
    double leadingTowerHFp = -1, leadingTowerHFm = -1;

    double leadingTowerEB_eta, leadingTowerEEp_eta, leadingTowerEEm_eta;
    double leadingTowerHB_eta, leadingTowerHEp_eta, leadingTowerHEm_eta;
    double leadingTowerHFp_eta, leadingTowerHFm_eta;
 
    double leadingTowerEB_phi, leadingTowerEEp_phi, leadingTowerEEm_phi;
    double leadingTowerHB_phi, leadingTowerHEp_phi, leadingTowerHEm_phi;
    double leadingTowerHFp_phi, leadingTowerHFm_phi;

    for(auto tower : event->GetPhysObjects(EPhysObjType::kCaloTower)){
      ECaloType subdetHad = tower->GetTowerSubdetHad();
      ECaloType subdetEm = tower->GetTowerSubdetEm();

      int ieta = eta2ieta(tower->GetEta());
      int iphi = phi2iphi(tower->GetPhi(),ieta);

      if(subdetEm==kEB){
        hists.at("eEB"+datasetName)->Fill(tower->GetEnergyEm());
        hists2D.at("eEB_eta"+datasetName)->Fill(tower->GetEta(),tower->GetEnergyEm());
        hists2D.at("eEB_eta_phi"+datasetName)->Fill(tower->GetEta(),tower->GetPhi(),tower->GetEnergyEm());

        hists2D.at("eEB_ieta"+datasetName)->Fill(ieta,tower->GetEnergyEm());
        hists2D.at("eEB_ieta_iphi"+datasetName)->Fill(ieta,iphi,tower->GetEnergyEm());


        if(tower->GetEnergyEm() > leadingTowerEB){
          //if(event->IsOverlappingWithGoodPhoton(*tower)) continue;
          leadingTowerEB = tower->GetEnergyEm();
          leadingTowerEB_eta = tower->GetEta();
          leadingTowerEB_phi = tower->GetPhi();
        }
      }
      if(subdetEm==kEE){
        hists.at("eEE"+datasetName)->Fill(tower->GetEnergyEm());
        hists2D.at("eEE_eta"+datasetName)->Fill(tower->GetEta(),tower->GetEnergyEm());
        hists2D.at("eEE_eta_phi"+datasetName)->Fill(tower->GetEta(),tower->GetPhi(),tower->GetEnergyEm());

        hists2D.at("eEE_ieta"+datasetName)->Fill(ieta,tower->GetEnergyEm());
        hists2D.at("eEE_ieta_iphi"+datasetName)->Fill(ieta,iphi,tower->GetEnergyEm());

        if(tower->GetEta() > 0 && tower->GetEnergyEm() > leadingTowerEEp){ // && ieta != 27 && ieta != 28 && ieta != 29){// && !(ieta == 28 && iphi == 9) && !(ieta == 28 && iphi == 27) && !(ieta == 28 && iphi == 45) && !(ieta == 28 && iphi == 63)){ //&& ieta != 27 && ieta != 28 && ieta != 29){
          //if(event->IsOverlappingWithGoodPhoton(*tower)) continue;
          leadingTowerEEp = tower->GetEnergyEm();
          leadingTowerEEp_eta = tower->GetEta();
          leadingTowerEEp_phi = tower->GetPhi();
        }
        if(tower->GetEta() < 0 && tower->GetEnergyEm() > leadingTowerEEm){ //&& ieta != -27 && ieta != -28 && ieta != -29){ //&& !(ieta == -28 && iphi == 9) && !(ieta == -28 && iphi == 27) && !(ieta == -28 && iphi == 45) && !(ieta == -28 && iphi == 63)){ //&& ieta != -27 && ieta != -28 && ieta != -29){
          //if(event->IsOverlappingWithGoodPhoton(*tower)) continue;
          leadingTowerEEm = tower->GetEnergyEm();
          leadingTowerEEm_eta = tower->GetEta();
          leadingTowerEEm_phi = tower->GetPhi();
        }
      }
      if(subdetHad==kHB){
        hists.at("eHB"+datasetName)->Fill(tower->GetEnergyHad());
        hists2D.at("eHB_eta"+datasetName)->Fill(tower->GetEta(),tower->GetEnergyHad());
        hists2D.at("eHB_eta_phi"+datasetName)->Fill(tower->GetEta(),tower->GetPhi(),tower->GetEnergyHad());

        hists2D.at("eHB_ieta"+datasetName)->Fill(ieta,tower->GetEnergyHad());
        hists2D.at("eHB_ieta_iphi"+datasetName)->Fill(ieta,iphi,tower->GetEnergyHad());

        if(tower->GetEnergyHad() > leadingTowerHB){
          leadingTowerHB = tower->GetEnergyHad();
          leadingTowerHB_eta = tower->GetEta();
          leadingTowerHB_phi = tower->GetPhi();      
        }
      }
      if(subdetHad==kHE){
        hists.at("eHE"+datasetName)->Fill(tower->GetEnergyHad());
        hists2D.at("eHE_eta"+datasetName)->Fill(tower->GetEta(),tower->GetEnergyHad());
        hists2D.at("eHE_eta_phi"+datasetName)->Fill(tower->GetEta(),tower->GetPhi(),tower->GetEnergyHad());  

        hists2D.at("eHE_ieta"+datasetName)->Fill(ieta,tower->GetEnergyHad());
        hists2D.at("eHE_ieta_iphi"+datasetName)->Fill(ieta,iphi,tower->GetEnergyHad());  


        if(tower->GetEta() > 0 && tower->GetEnergyHad() > leadingTowerHEp){// && ieta != 16){
          leadingTowerHEp = tower->GetEnergyHad();
          leadingTowerHEp_eta = tower->GetEta();
          leadingTowerHEp_phi = tower->GetPhi();       
        }
        if(tower->GetEta() < 0 && tower->GetEnergyHad() > leadingTowerHEm){// && ieta != -16){
          leadingTowerHEm = tower->GetEnergyHad();
          leadingTowerHEm_eta = tower->GetEta();
          leadingTowerHEm_phi = tower->GetPhi();      
        }
      }
      if(subdetHad==kHFp){
        hists.at("eHFp"+datasetName)->Fill(tower->GetEnergy()); 
        hists2D.at("eHF_eta"+datasetName)->Fill(tower->GetEta(),tower->GetEnergy());
        hists2D.at("eHF_eta_phi"+datasetName)->Fill(tower->GetEta(),tower->GetPhi(),tower->GetEnergy());  

        hists2D.at("eHF_ieta"+datasetName)->Fill(ieta,tower->GetEnergy());
        hists2D.at("eHF_ieta_iphi"+datasetName)->Fill(ieta,iphi,tower->GetEnergy());  


        if(tower->GetEnergy() > leadingTowerHFp){ //&& ieta != 29 && ieta != 30){
          leadingTowerHFp = tower->GetEnergyHad();
          leadingTowerHFp_eta = tower->GetEta();
          leadingTowerHFp_phi = tower->GetPhi();       
        }
    
      }
      if(subdetHad==kHFm){
        hists.at("eHFm"+datasetName)->Fill(tower->GetEnergy());
        hists2D.at("eHF_eta"+datasetName)->Fill(tower->GetEta(),tower->GetEnergy());
        hists2D.at("eHF_eta_phi"+datasetName)->Fill(tower->GetEta(),tower->GetPhi(),tower->GetEnergy());  

        hists2D.at("eHF_ieta"+datasetName)->Fill(ieta,tower->GetEnergy());
        hists2D.at("eHF_ieta_iphi"+datasetName)->Fill(ieta,iphi,tower->GetEnergy());  

        if(tower->GetEnergy() > leadingTowerHFm){// && ieta != -29 && ieta != -30){
          leadingTowerHFm = tower->GetEnergy();
          leadingTowerHFm_eta = tower->GetEta();
          leadingTowerHFm_phi = tower->GetPhi();       
        }
      }
    
    }

    int leadingTowerEB_ieta = eta2ieta(leadingTowerEB_eta);
    int leadingTowerEEp_ieta = eta2ieta(leadingTowerEEp_eta);
    int leadingTowerEEm_ieta = eta2ieta(leadingTowerEEm_eta);
    int leadingTowerHB_ieta = eta2ieta(leadingTowerHB_eta);
    int leadingTowerHEp_ieta = eta2ieta(leadingTowerHEp_eta);
    int leadingTowerHEm_ieta = eta2ieta(leadingTowerHEm_eta);
    int leadingTowerHFp_ieta = eta2ieta(leadingTowerHFp_eta);
    int leadingTowerHFm_ieta = eta2ieta(leadingTowerHFm_eta);

    int leadingTowerEB_iphi = phi2iphi(leadingTowerEB_phi,leadingTowerEB_ieta);
    int leadingTowerEEp_iphi = phi2iphi(leadingTowerEEp_phi,leadingTowerEEp_ieta);
    int leadingTowerEEm_iphi = phi2iphi(leadingTowerEEm_phi,leadingTowerEEm_ieta);
    int leadingTowerHB_iphi = phi2iphi(leadingTowerHB_phi,leadingTowerHB_ieta);
    int leadingTowerHEp_iphi = phi2iphi(leadingTowerHEp_phi,leadingTowerHEp_ieta);
    int leadingTowerHEm_iphi = phi2iphi(leadingTowerHEm_phi,leadingTowerHEm_ieta);
    int leadingTowerHFp_iphi = phi2iphi(leadingTowerHFp_phi,leadingTowerHFp_ieta);
    int leadingTowerHFm_iphi = phi2iphi(leadingTowerHFm_phi,leadingTowerHFm_ieta);

    hists.at("eEB_leadingTower"+datasetName)->Fill(leadingTowerEB);
    hists2D.at("eEB_eta_leadingTower"+datasetName)->Fill(leadingTowerEB_eta,leadingTowerEB);
    hists2D.at("eEB_eta_phi_leadingTower"+datasetName)->Fill(leadingTowerEB_eta,leadingTowerEB_phi);

    hists.at("eEE_leadingTower"+datasetName)->Fill(leadingTowerEEp);
    hists2D.at("eEE_eta_leadingTower"+datasetName)->Fill(leadingTowerEEp_eta,leadingTowerEEp);
    hists2D.at("eEE_eta_phi_leadingTower"+datasetName)->Fill(leadingTowerEEp_eta,leadingTowerEEp_phi);

    hists.at("eEE_leadingTower"+datasetName)->Fill(leadingTowerEEm);
    hists2D.at("eEE_eta_leadingTower"+datasetName)->Fill(leadingTowerEEm_eta,leadingTowerEEm);
    hists2D.at("eEE_eta_phi_leadingTower"+datasetName)->Fill(leadingTowerEEm_eta,leadingTowerEEm_phi);

    hists.at("eHB_leadingTower"+datasetName)->Fill(leadingTowerHB);
    hists2D.at("eHB_eta_leadingTower"+datasetName)->Fill(leadingTowerHB_eta,leadingTowerHB);
    hists2D.at("eHB_eta_phi_leadingTower"+datasetName)->Fill(leadingTowerHB_eta,leadingTowerHB_phi);

    hists.at("eHE_leadingTower"+datasetName)->Fill(leadingTowerHEp);
    hists2D.at("eHE_eta_leadingTower"+datasetName)->Fill(leadingTowerHEp_eta,leadingTowerHEp);
    hists2D.at("eHE_eta_phi_leadingTower"+datasetName)->Fill(leadingTowerHEp_eta,leadingTowerHEp_phi);

    hists.at("eHE_leadingTower"+datasetName)->Fill(leadingTowerHEm);
    hists2D.at("eHE_eta_leadingTower"+datasetName)->Fill(leadingTowerHEm_eta,leadingTowerHEm);
    hists2D.at("eHE_eta_phi_leadingTower"+datasetName)->Fill(leadingTowerHEm_eta,leadingTowerHEm_phi);

    hists.at("eHFp_leadingTower"+datasetName)->Fill(leadingTowerHFp);
    hists2D.at("eHF_eta_leadingTower"+datasetName)->Fill(leadingTowerHFp_eta,leadingTowerHFp);
    hists2D.at("eHF_eta_phi_leadingTower"+datasetName)->Fill(leadingTowerHFp_eta,leadingTowerHFp_phi);

    hists.at("eHFm_leadingTower"+datasetName)->Fill(leadingTowerHFm);
    hists2D.at("eHF_eta_leadingTower"+datasetName)->Fill(leadingTowerHFm_eta,leadingTowerHFm);
    hists2D.at("eHF_eta_phi_leadingTower"+datasetName)->Fill(leadingTowerHFm_eta,leadingTowerHFm_phi);


    hists2D.at("eEB_ieta_leadingTower"+datasetName)->Fill(leadingTowerEB_ieta,leadingTowerEB);
    hists2D.at("eEB_ieta_iphi_leadingTower"+datasetName)->Fill(leadingTowerEB_ieta,leadingTowerEB_iphi);

    hists2D.at("eEE_ieta_leadingTower"+datasetName)->Fill(leadingTowerEEp_ieta,leadingTowerEEp);
    hists2D.at("eEE_ieta_iphi_leadingTower"+datasetName)->Fill(leadingTowerEEp_ieta,leadingTowerEEp_iphi);

    hists2D.at("eEE_ieta_leadingTower"+datasetName)->Fill(leadingTowerEEm_ieta,leadingTowerEEm);
    hists2D.at("eEE_ieta_iphi_leadingTower"+datasetName)->Fill(leadingTowerEEm_ieta,leadingTowerEEm_iphi);

    hists2D.at("eHB_ieta_leadingTower"+datasetName)->Fill(leadingTowerHB_ieta,leadingTowerHB);
    hists2D.at("eHB_ieta_iphi_leadingTower"+datasetName)->Fill(leadingTowerHB_ieta,leadingTowerHB_iphi);

    hists2D.at("eHE_ieta_leadingTower"+datasetName)->Fill(leadingTowerHEp_ieta,leadingTowerHEp);
    hists2D.at("eHE_ieta_iphi_leadingTower"+datasetName)->Fill(leadingTowerHEp_ieta,leadingTowerHEp_iphi);

    hists2D.at("eHE_ieta_leadingTower"+datasetName)->Fill(leadingTowerHEm_ieta,leadingTowerHEm);
    hists2D.at("eHE_ieta_iphi_leadingTower"+datasetName)->Fill(leadingTowerHEm_ieta,leadingTowerHEm_iphi);

    hists2D.at("eHF_ieta_leadingTower"+datasetName)->Fill(leadingTowerHFp_ieta,leadingTowerHFp);
    hists2D.at("eHF_ieta_iphi_leadingTower"+datasetName)->Fill(leadingTowerHFp_ieta,leadingTowerHFp_iphi);

    hists2D.at("eHF_ieta_leadingTower"+datasetName)->Fill(leadingTowerHFm_ieta,leadingTowerHFm);
    hists2D.at("eHF_ieta_iphi_leadingTower"+datasetName)->Fill(leadingTowerHFm_ieta,leadingTowerHFm_iphi);

    if(!event->HasAdditionalTowers())
      selected++;

  }//event

    Log(0) << ((double)selected)/all << "\n";
    //Log(0) << ((double)selected)/nTwoGoodPho << "\n";

} // fill histogram

map<string, TH1D*> init1Dhists(string name)
{
  map<string, TH1D*> hists;
  for(auto params : histParams){
    string title = get<0>(params)+name;
    hists[title] = new TH1D(title.c_str(), title.c_str(), get<1>(params), get<2>(params), get<3>(params));
  }
  return hists;
}

map<string, TH2D*> init2Dhists(string name)
{
  map<string, TH2D*> hists;
  
  for(auto params : histParams2D){
    string title = get<0>(params)+name;
    hists[title] = new TH2D(title.c_str(), title.c_str(),
                            get<1>(params), get<2>(params), get<3>(params),
                            get<4>(params), get<5>(params), get<6>(params));
  }
  return hists;
}

int main(int argc, char* argv[])
{
  if(argc != 5){
    Log(0)<<"This app requires 4 parameters.\n";
    Log(0)<<"./getEfficienciesData configPath sampleName inputPath outputPath\n";
    exit(0);
  }
  
  // read input arguments
  string configPath  = argv[1];
  string sampleName  = argv[2];
  string inputPath   = argv[3];
  string outputPath  = argv[4];
  
  // create config manager
  config = ConfigManager(configPath);
  EDataset dataset;
  
  // load events from input file
  if(sampleName == "Data")          dataset = kData;
  else if(sampleName == "QED_SC")   dataset = kMCqedSC;
  else if(sampleName == "QED_SL")   dataset = kMCqedSL;
  else if(sampleName == "LbL")      dataset = kMClbl;
  else if(sampleName == "CEP")      dataset = kMCcep;
  else{
    Log(0)<<"Unrecognised sample name: "<<sampleName<<"!!\n";
    exit(0);
  }
  
  auto events = make_unique<EventProcessor>(inputPath, dataset);
  
  TFile *outFile = TFile::Open(outputPath.c_str(), "recreate");
  //TTree *photonIDVars = new TTree("photonIDVars_tree","");
  //InitTree(photonIDVars);

  // fill histograms
  map<string, TH1D*> hists = init1Dhists(sampleName);
  map<string, TH2D*> hists2D = init2Dhists(sampleName);
  fillHistograms(events, hists, hists2D, sampleName);
  
  // save output files
  //TFile *outFile = new TFile(outputPath.c_str(), "recreate");
  outFile->cd();
  outFile->Write();
  for(auto hist : hists)    hist.second->Write();
  for(auto hist : hists2D)  hist.second->Write();
  outFile->Close();
}
