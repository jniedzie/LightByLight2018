//  Event.cpp
//
//  Created by Jeremi Niedziela on 22/07/2019.

#include "Event.hpp"
#include "PhysObjectProcessor.hpp"

Event::Event()
{

}

Event::~Event()
{

}

void Event::Reset()
{
  genParticles.clear();
  photons.clear();
  goodPhotons.clear();
  caloTowers.clear();
  generalTracks.clear();
  electrons.clear();
  goodElectrons.clear();
  L1EGs.clear();
  
  goodPhotonsReady = false;
  goodElectronsReady = false;
}

bool Event::HasSingleEG3Trigger() const
{
  return triggersLbL.at("HLT_HIUPC_SingleEG3_NotMBHF2AND_v1");
}

bool Event::HasSingleEG5Trigger() const
{
  return triggersLbL.at("HLT_HIUPC_SingleEG5_NotMBHF2AND_v1");
}

bool Event::HasDoubleEG2Trigger() const
{
  return triggersLbL.at("HLT_HIUPC_DoubleEG2_NotMBHF2AND_v1");
}

bool Event::HasSingleEG3noHFvetoTrigger() const
{
  return triggersLbL.at("HLT_HIUPC_SingleEG3_BptxAND_SinglePixelTrack_MaxPixelTrack_v1");
}

vector<shared_ptr<PhysObject>> Event::GetGoodGenPhotons() const
{
  vector<shared_ptr<PhysObject>> goodGenPhotons;
  
  for(int iGenPhoton=0; iGenPhoton<nGenParticles; iGenPhoton++){
    auto genPhoton = genParticles[iGenPhoton];
    
    if(genPhoton->GetPID() != 22) continue;
    if(fabs(genPhoton->GetEta()) > config.params("maxEta")) continue;
    if(genPhoton->GetEt() < config.params("minEt")) continue;
    
    goodGenPhotons.push_back(genPhoton);
  }
  
  return goodGenPhotons;
}

vector<shared_ptr<PhysObject>> Event::GetGoodPhotons()
{
  if(goodPhotonsReady) return goodPhotons;
  
  goodPhotons.clear();
  
  for(int iPhoton=0; iPhoton<nPhotons; iPhoton++){
    auto photon = photons[iPhoton];
    
    // Check Et
    if(photon->GetEt() < config.params("photonMinEt")) continue;
    
    // Check eta & phi (remove noisy region >2.3, remove cracks between EB and EE, remove HEM issue region)
    double absEta = fabs(photon->GetEta());
    if(absEta > config.params("photonMaxEta")) continue;
    if(absEta > config.params("ecalCrackMin") && absEta < config.params("ecalCrackMax")) continue;
    if(photon->GetEta() < -minEtaEE &&
       photon->GetPhi() > config.params("ecalHEMmin") &&
       photon->GetPhi() < config.params("ecalHEMmax")) continue;
    
    // Check η shower shape
    if((absEta < maxEtaEB) && (photon->GetEtaWidth() > config.params("photonMaxEtaWidthBarrel"))) continue;
    else if((absEta < maxEtaEE) && (photon->GetEtaWidth() > config.params("photonMaxEtaWidthEndcap"))) continue;
    
    // Check H/E
    if((absEta < maxEtaEB) && (photon->GetHoverE() > config.params("photonMaxHoverEbarrel"))) continue;
    else if((absEta < maxEtaEE) && (photon->GetHoverE() > config.params("photonMaxHoverEendcap"))) continue;
    
    goodPhotons.push_back(photon);
  }
  goodPhotonsReady = true;
  return goodPhotons;
}

vector<shared_ptr<PhysObject>> Event::GetGoodElectrons(TH1D *cutFlowHist)
{
  if(goodElectronsReady) return goodElectrons;
  
  goodElectrons.clear();
  
  for(auto electron : electrons){
    int cutFlowIndex=0;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++);
    
    // Check pt
    if(electron->GetPt() < config.params("electronMinPt")) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++);
    
    // Check eta
    double eta = fabs(electron->GetEtaSC());
    if(eta > config.params("ecalCrackMin") &&
       eta < config.params("ecalCrackMax"))   continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++);
    
    if(eta >= config.params("electronMaxEta")) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++);
    
    // Check for HEM issue
    if(electron->GetEtaSC() < -minEtaEE &&
       electron->GetPhiSC() > config.params("ecalHEMmin") &&
       electron->GetPhiSC() < config.params("ecalHEMmax")) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++);
    
    // Check n missing hits
    if(electron->GetNmissingHits() > config.params("electronMaxNmissingHits")) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++);
    
    string subdet = "";
    if((eta < maxEtaEB)) subdet = "Barrel";
    else if((eta < maxEtaEE)) subdet = "Endcap";
    
    // Check H/E
    if(electron->GetHoverE() >= config.params("electronMaxHoverE_"+subdet)) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++);
    
    // Check Δη at vertex
    if(electron->GetDetaSeed() >= config.params("electronMaxDetaSeed"+subdet)) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++);
    
    // Check isolation
    if(electron->GetChargedIso() >= config.params("electronMaxChargedIso"+subdet)) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++);
    
    if(electron->GetPhotonIso()  >= config.params("electronMaxPhotonIso"+subdet))  continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++);
    
    if(electron->GetNeutralIso() >= config.params("electronMaxNeutralIso"+subdet)) continue;
    if(cutFlowHist) cutFlowHist->Fill(cutFlowIndex++);

    goodElectrons.push_back(electron);
  }
  goodElectronsReady = true;
  return goodElectrons;
}

double Event::GetDiphotonInvMass()
{
  if(GetGoodPhotons().size() !=2 ) return -1;
  
  TLorentzVector pho1, pho2;
  
  pho1.SetPtEtaPhiE(GetGoodPhotons()[0]->GetEt(),
                    GetGoodPhotons()[0]->GetEta(),
                    GetGoodPhotons()[0]->GetPhi(),
                    GetGoodPhotons()[0]->GetEnergy());
  
  pho2.SetPtEtaPhiE(GetGoodPhotons()[1]->GetEt(),
                    GetGoodPhotons()[1]->GetEta(),
                    GetGoodPhotons()[1]->GetPhi(),
                    GetGoodPhotons()[1]->GetEnergy());
  
  TLorentzVector diphoton = pho1+pho2;
  
  return diphoton.M();
}

bool Event::DiphotonPtAboveThreshold()
{
  GetGoodPhotons();
  
  if(GetGoodPhotons().size() != 2) return true;
  
  double pt_1 = GetGoodPhotons()[0]->GetEt();
  double pt_2 = GetGoodPhotons()[1]->GetEt();
  double deltaPhi = GetGoodPhotons()[0]->GetPhi() - GetGoodPhotons()[1]->GetPhi();
  
  double pairPt = sqrt(pt_1*pt_1 + pt_2*pt_2 + 2*pt_1*pt_2*cos(deltaPhi));
  if(pairPt > config.params("diphotonMaxPt")) return true;
  
  return false;
}

bool Event::HasAdditionalTowers(bool checkHF, ECaloType *failingCalo)
{
  for(int iTower=0; iTower<nCaloTowers; iTower++){
    auto tower = caloTowers[iTower];
    
    if(physObjectProcessor.IsInCrackOrHEM(*tower)) continue;
    
    ECaloType subdetHad = tower->GetTowerSubdetHad();
    
    // Check HF exclusivity
    if(checkHF && (subdetHad==kHFp || subdetHad==kHFm)){
      if(tower->GetEnergy() > config.params("noiseThreshold"+caloName.at(subdetHad))){
        if(failingCalo) *failingCalo = subdetHad;
        return true;
      }
    }

    // Check HB and HE exclusivity
    if(subdetHad==kHB || subdetHad==kHE){
      if(tower->GetEnergyHad() > config.params("noiseThreshold"+caloName.at(subdetHad))){
        if(failingCalo) *failingCalo = subdetHad;
        return true;
      }
    }
    
    // Check EB and EE exclusivity
    ECaloType subdetEm = tower->GetTowerSubdetEm();
    
    if(subdetEm == kEE && fabs(tower->GetEta()) > config.params("maxEtaEEtower")) continue;
    
    if(IsOverlappingWithGoodPhoton(*tower)) continue;
    if(IsOverlappingWithGoodElectron(*tower)) continue;
    
    double threshold = GetEmThresholdForTower(*tower);
    
    if((tower->GetEnergyEm() > threshold) &&
       (checkHF || (subdetEm!=kHFp && subdetEm!=kHFm))){
      if(failingCalo) *failingCalo = subdetEm;
      return true;
    }
      
  }
  return false;
}

bool Event::HasChargedTracks() const
{
  if(nElectrons != 0) return true;
  
  for(int iTrack=0; iTrack<nGeneralTracks; iTrack++){
    auto track = generalTracks[iTrack];
    if(track->GetPt() > config.params("trackMinPt")) return true;
  }
  return false;
}

int Event::GetNchargedTracks() const
{
  int nTracks=0;
  
  for(int iTrack=0; iTrack<nGeneralTracks; iTrack++){
    if(generalTracks[iTrack]->GetPt() > config.params("trackMinPt")) nTracks++;
  }
  return nTracks;
}

void Event::SortCaloTowersByEnergy()
{
  sort(caloTowers.begin(), caloTowers.end(), PhysObjectProcessor::CompareByEnergy());
}


bool Event::IsOverlappingWithGoodPhoton(const PhysObject &tower)
{
  bool overlapsWithPhoton = false;
  
  ECaloType subdet = tower.GetTowerSubdetEm();
  double maxDeltaEta = (subdet == kEB ) ? config.params("maxDeltaEtaEB") : config.params("maxDeltaEtaEE");
  double maxDeltaPhi = (subdet == kEB ) ? config.params("maxDeltaPhiEB") : config.params("maxDeltaPhiEE");
  
  for(int iPhoton=0; iPhoton<GetGoodPhotons().size(); iPhoton++){
    auto photon = GetGoodPhotons()[iPhoton];
    
    double deltaEta = fabs(photon->GetEta() - tower.GetEta());
    double deltaPhi = fabs(photon->GetPhi() - tower.GetPhi());
    
    if(deltaEta < maxDeltaEta && deltaPhi < maxDeltaPhi){
      overlapsWithPhoton = true;
      break;
    }
  }
  return overlapsWithPhoton;
}

bool Event::IsOverlappingWithGoodElectron(const PhysObject &tower)
{
  bool overlapsWithElectron = false;
  
  ECaloType subdet = tower.GetTowerSubdetEm();
  double maxDeltaEta = (subdet == kEB ) ? config.params("maxDeltaEtaEB") : config.params("maxDeltaEtaEE");
  double maxDeltaPhi = (subdet == kEB ) ? config.params("maxDeltaPhiEB") : config.params("maxDeltaPhiEE");
  
  for(auto electron : GetGoodElectrons()){
    double deltaEta = fabs(electron->GetEta() - tower.GetEta());
    double deltaPhi = fabs(electron->GetPhi() - tower.GetPhi());
    
    if(deltaEta < maxDeltaEta && deltaPhi < maxDeltaPhi){
      overlapsWithElectron = true;
      break;
    }
  }
  return overlapsWithElectron;
}

double Event::GetEmThresholdForTower(const PhysObject &tower)
{
  double threshold = -1;
  
  ECaloType subdet = tower.GetTowerSubdetEm();
  
  if(subdet==kEE && config.params("doNoiseEEetaDependant")){
    double etaStep = config.params("noiseEEetaStep");
    double etaMin = config.params("noiseEEetaMin");
    double etaMax = config.params("noiseEEetaMax");
    
    double towerEta = fabs(tower.GetEta());
    
    if(towerEta < etaMin || towerEta > etaMax) threshold = 99999;
    
    for(double eta=etaMin; eta<etaMax; eta += etaStep){
      if(towerEta > eta && towerEta < eta+etaStep){
        threshold = config.params("noiseThresholdEE_"+to_string_with_precision(eta, 1));
      }
    }
  }
  else{
    threshold = config.params("noiseThreshold"+caloName.at(subdet));
  }
  if(threshold < 0) cout<<"ERROR - could not find threshold for thower !!"<<endl;
  return threshold;
}
