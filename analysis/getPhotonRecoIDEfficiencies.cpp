//  getPhotonRecoIDEfficiencies
//
//  Created by Ruchi Chudasama on 01/03/2021
//
//  Calculates photon reco +ID efficiencies in MC and data, as defined in the Analysis Note

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"
#include "EventDisplay.hpp"
#include "Logger.hpp"

const double eleMass = 0.000511;
Double_t getDPHI( Double_t phi1, Double_t phi2);
Double_t getDETA(Double_t eta1, Double_t eta2);
double acop(double dphi) {
   return 1.-fabs(TVector2::Phi_mpi_pi(dphi))/TMath::Pi(); 
};

int run;
int ls;
int evtnb;
float swissCross;
float etaWidth;
float HoE;
int ok_photon;
int ok_ID;
int ok_etaWidth;
int ok_swissCross;
int ok_HoE;
int tag_charge;
int nTag;
float tag_Et;
float tag_SCEt;
float tag_SCEta;
float tag_SCPhi;
float tag_pt;
float tag_eta;
float tag_phi;
int pass_EG3;
int pass_EG5;
float tag_L1Et_passEG3;
float tag_L1Eta_passEG3;
float tag_L1Et_passEG5;
float tag_L1Eta_passEG5;
int nPho_notag;
float phoEt_notag;
float phoEta_notag;
float phoPhi_notag;
float phoAco_notag;
float phoSCEt_notag;
float phoSCEta_notag;
float phoSCPhi_notag;
float phoSCAco_notag;

int ok_probeTrk;
int nprobeTrk;
float probetkPt, probetkEta, probetkPhi, probeTkMinDphi, probetkAco; int probetkCharge; float probetkMinDpt, probetkMinDet;
float probetkvx; float probetkvy; float probetkvz; float probetkd0; float probetkdxy; float probetkdz; float probetkdxyError; 
float probetkdzError; int probetkValidHits; int probetkMissHits;  float diffPt_probetkEleGamma, diffEt_probetkEleGamma;
float diffSCPt_probetkEleGamma, diffSCEt_probetkEleGamma;

/// initialise tree
void InitTree(TTree *tr) {
  tr->Branch("run",&run,"run/I");
  tr->Branch("ls",&ls,"ls/I");
  tr->Branch("evtnb",&evtnb,"evtnb/I");
  tr->Branch("nTag",   &nTag,   "nTag/I");
  tr->Branch("tag_charge",&tag_charge,"tag_charge/I");
  tr->Branch("tag_Et",&tag_Et,"tag_Et/F");
  tr->Branch("tag_SCEt",&tag_SCEt,"tag_SCEt/F");
  tr->Branch("tag_SCEta",&tag_SCEta,"tag_SCEta/F");
  tr->Branch("tag_SCPhi",&tag_SCPhi,"tag_SCPhi/F");
  tr->Branch("tag_pt",&tag_pt,"tag_pt/F");
  tr->Branch("tag_eta",&tag_eta,"tag_eta/F");
  tr->Branch("tag_phi",&tag_phi,"tag_phi/F");
  tr->Branch("pass_EG3",&pass_EG3,"pass_EG3/I");
  tr->Branch("pass_EG5",&pass_EG5,"pass_EG5/I");
  tr->Branch("tag_L1Et_passEG3",&tag_L1Et_passEG3,"tag_L1Et_passEG3/F");
  tr->Branch("tag_L1Eta_passEG3",&tag_L1Eta_passEG3,"tag_L1Eta_passEG3/F");
  tr->Branch("tag_L1Et_passEG5",&tag_L1Et_passEG5,"tag_L1Et_passEG5/F");
  tr->Branch("tag_L1Eta_passEG5",&tag_L1Eta_passEG5,"tag_L1Eta_passEG5/F");
  tr->Branch("swissCross",&swissCross,"swissCross/F");
  tr->Branch("etaWidth",&etaWidth,"etaWidth/F");
  tr->Branch("HoE",&HoE,"HoE/F");
  tr->Branch("ok_photon",&ok_photon,"ok_photon/I");
  tr->Branch("ok_ID",&ok_ID,"ok_ID/I");
  tr->Branch("ok_etaWidth",&ok_etaWidth,"ok_etaWidth/I");
  tr->Branch("ok_swissCross",&ok_swissCross,"ok_swissCross/I");
  tr->Branch("ok_HoE",&ok_HoE,"ok_HoE/I");
  tr->Branch("nPho_notag",   &nPho_notag,   "nPho_notag/I");
  tr->Branch("phoEt_notag",&phoEt_notag,"phoEt_notag/F");
  tr->Branch("phoEta_notag",&phoEta_notag,"phoEta_notag/F");
  tr->Branch("phoPhi_notag",&phoPhi_notag,"phoPhi_notag/F");
  tr->Branch("phoAco_notag",&phoAco_notag,"phoAco_notag/F");
  tr->Branch("phoSCEt_notag",&phoSCEt_notag,"phoSCEt_notag/F");
  tr->Branch("phoSCEta_notag",&phoSCEta_notag,"phoSCEta_notag/F");
  tr->Branch("phoSCPhi_notag",&phoSCPhi_notag,"phoSCPhi_notag/F");
  tr->Branch("phoSCAco_notag",&phoSCAco_notag,"phoSCAco_notag/F");
  tr->Branch("ok_probeTrk",&ok_probeTrk,"ok_probeTrk/I");
  tr->Branch("nprobeTrk",   &nprobeTrk,   "nprobeTrk/I");
  tr->Branch("probetkCharge",&probetkCharge,"probetkCharge/I");
  tr->Branch("probetkPt",&probetkPt,"probetkPt/F");
  tr->Branch("probetkEta",&probetkEta,"probetkEta/F");
  tr->Branch("probetkPhi",&probetkPhi,"probetkPhi/F");
  tr->Branch("probetkMinDpt",&probetkMinDpt,"probetkMinDpt/F");
  tr->Branch("probetkMinDet",&probetkMinDet,"probetkMinDet/F");
  tr->Branch("diffPt_probetkEleGamma",&diffPt_probetkEleGamma,"diffPt_probetkEleGamma/F");
  tr->Branch("diffEt_probetkEleGamma",&diffEt_probetkEleGamma,"diffEt_probetkEleGamma/F");

  tr->Branch("diffSCPt_probetkEleGamma",&diffSCPt_probetkEleGamma,"diffSCPt_probetkEleGamma/F");
  tr->Branch("diffSCEt_probetkEleGamma",&diffSCEt_probetkEleGamma,"diffSCEt_probetkEleGamma/F");

  tr->Branch("probetkAco",&probetkAco,"probetkAco/F");
  tr->Branch("probetkvx",&probetkvx,"probetkvx/F");
  tr->Branch("probetkvy",&probetkvy,"probetkvy/F");
  tr->Branch("probetkvz",&probetkvz,"probetkvz/F");
  tr->Branch("probetkd0",&probetkd0,"probetkd0/F");
  tr->Branch("probetkdxy",&probetkdxy,"probetkdxy/F");
  tr->Branch("probetkdz",&probetkdz,"probetkdz/F");
  tr->Branch("probetkdxyError",&probetkdxyError,"probetkdxyError/F");
  tr->Branch("probetkdzError",&probetkdzError,"probetkdzError/F");
  tr->Branch("probetkValidHits",&probetkValidHits,"probetkValidHits/I");
  tr->Branch("probetkMissHits",&probetkMissHits,"probetkMissHits/I");
}

// reset event variables
void ResetEventVars() {
  run   = -999;
  ls    = -999;
  evtnb = -999;
}

// reset tag variables
void ResetTagVars() {
  nTag=0;
  pass_EG3   = -999;
  pass_EG5   = -999;
  tag_charge = -999;
  tag_Et     = -999;
  tag_SCEt   = -999;
  tag_SCEta  = -999;
  tag_SCPhi  = -999;
  tag_pt     = -999;
  tag_eta    = -999;
  tag_phi    = -999;
  tag_L1Et_passEG3  = -999;
  tag_L1Eta_passEG3 = -999;
  tag_L1Et_passEG5  = -999;
  tag_L1Eta_passEG5 = -999;
}

// reset passing probe variables
void ResetPassingProbeVars() {
   swissCross     = -999;
   etaWidth       = -999;
   HoE            = -999;
   ok_photon      = -999;
   ok_ID          = -999;
   ok_etaWidth    = -999;
   ok_swissCross  = -999;
   ok_HoE         = -999;
   nPho_notag     = 0;
   phoEt_notag    = -999;
   phoEta_notag   = -999;
   phoPhi_notag   = 999;
   phoAco_notag   = 999;
   phoSCEt_notag  = -999;
   phoSCEta_notag = -999;
   phoSCPhi_notag = 999;
   phoSCAco_notag = 999;
}

// reset probe variables
void ResetProbeVars() {
   ok_probeTrk       = -999;
   nprobeTrk         = 0;
   probetkPt         = -999;
   probetkEta        = -999; 
   probetkPhi        = -999;
   probeTkMinDphi    = 999;
   probetkAco        = 999;
   probetkMinDpt     = 999.;
   probetkMinDet     = 999.;
   diffPt_probetkEleGamma   = 999.;
   diffEt_probetkEleGamma   = 999.;
   diffSCPt_probetkEleGamma   = 999.;
   diffSCEt_probetkEleGamma   = 999.;
   probetkvx         = 999.; 
   probetkvy         = 999.;
   probetkvz         = 999.;
   probetkd0         = 999.;
   probetkdxy        = 999.; 
   probetkdz         = 999.;
   probetkdxyError   = 999.; 
   probetkdzError    = 999.;
   probetkValidHits  = 999.; 
   probetkMissHits   = 999.;
}

/// trigger matching
shared_ptr<PhysObject> TriggerMatch(PhysObject obj, PhysObjects l1objs, double etmin, double absetamax, double dRmax=0.5) {
  shared_ptr<PhysObject> ans = 0;
  double minDR = dRmax;
  
  for (auto &L1EG : l1objs) {
    if (L1EG->GetEt() < etmin) continue;
    if (fabs(L1EG->GetEta()) > absetamax) continue;
    
    double deltaR = physObjectProcessor.GetDeltaR_SC(obj, *L1EG);
    if (deltaR < minDR) {
      minDR = deltaR;
      ans = static_pointer_cast<PhysObject>(L1EG);
    }
  }
  
  return ans;
}

/// track-ele matching
shared_ptr<PhysObject> EleMatch(PhysObject obj, PhysObjects electrons, double dRmax=0.1, double dptRelMax=0.2) {
  shared_ptr<PhysObject> ans = 0;
  double minDR = dRmax;
  
  for (auto& ele : electrons) {
    double deltaR = physObjectProcessor.GetDeltaR(obj, *ele);
    double dptRel = fabs((obj.GetPt() / ele->GetPt()) - 1.);
    if (deltaR < minDR && dptRel < dptRelMax) {
      minDR = deltaR;
      ans = static_pointer_cast<PhysObject>(ele);
    }
  }
  
  return ans;
}


/// track/photon unmatched to tag electron
shared_ptr<PhysObject> UnMatched(PhysObject obj, PhysObjects electrons, double dRmax=0.3) {
  shared_ptr<PhysObject> ans = 0;
  double minDR = dRmax;
  
  for (auto& ele : electrons) {
    double deltaR = physObjectProcessor.GetDeltaR(obj, *ele);
    if (deltaR < minDR) continue;
    ans = static_pointer_cast<PhysObject>(ele);
  }
  return ans;
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
  
  TFile *outFile = TFile::Open(outputPath.c_str(), "recreate");
  outFile->mkdir("tnpQED");
  outFile->cd("tnpQED");
  TTree *tr = new TTree("fitter_tree","");
  InitTree(tr);
  
  auto events = make_unique<EventProcessor>(inputPath, dataset);
  
  int tag_loop = 0; int probeTrk_loop = 0; int photon_loop = 0;
  
  int cnt[10] = {0};
  
  // Loop over events
  //for(int iEvent=0; iEvent<10000; iEvent++){
  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
    if(iEvent%1000 == 0) Log(0)<<"Processing event "<<iEvent<<"\n";
    if(iEvent >= config.params("maxEvents")) break;
    
    auto event = events->GetEvent(iEvent);
    
    // Check trigger
    if(!event->HasTrigger(kSingleEG3noHF) && !event->HasTrigger(kSingleEG5noHF)) continue;
    
    ResetEventVars();
    run = event->GetRunNumber();
    ls = event->GetLumiSection();
    evtnb = event->GetEventNumber();
    
    
    auto L1EGs = event->GetPhysObjects(EPhysObjType::kL1EG);
    auto goodElectrons = event->GetPhysObjects(EPhysObjType::kGoodElectron);
    auto genTracks     = event->GetPhysObjects(EPhysObjType::kGoodGeneralTrack);
    auto goodPhoton    = event->GetPhysObjects(EPhysObjType::kPhotonInAcceptance);
    
    if(goodElectrons.size()!=1) continue;
    cnt[1]++;
    if(goodPhoton.size()>2) continue;
    cnt[2]++;
    if(genTracks.size()!=2) continue;
    cnt[3]++;
   
    auto track1 = genTracks[0];
    auto track2 = genTracks[1];
    if(track1->GetCharge() == track2->GetCharge()) continue;
    cnt[4]++; 
    // find the tag electron
    PhysObjects goodMatchedElectrons;
    
    int ntag=0;
    // loop on tags (good electrons with additional cuts)
    for (auto tag : goodElectrons) {
      // trigger matching
      auto matchedL1EG3 = TriggerMatch(*tag, L1EGs, 3, 5);
      auto matchedL1EG5 = TriggerMatch(*tag, L1EGs, 5, 5);
      if (!matchedL1EG3 && !matchedL1EG5) continue;
      //ResetTagVars();
      if(matchedL1EG3){
	pass_EG3 = 1;
	Log(1) << "matched EG3:"<< pass_EG3 << "\n";
	tag_L1Et_passEG3   = matchedL1EG3->GetEt();
	tag_L1Eta_passEG3  = matchedL1EG3->GetEta();
      }
      if(matchedL1EG5){
	pass_EG5 = 1;
	Log(1) << "matched EG5:"<< pass_EG5 << "\n";
	tag_L1Et_passEG5   = matchedL1EG5->GetEt();
	tag_L1Eta_passEG5  = matchedL1EG5->GetEta();
      }
      if(matchedL1EG3 || matchedL1EG5){
	goodMatchedElectrons.push_back(tag);
      }
    } // electron loop
    
    if(goodMatchedElectrons.size() != 1) continue;
    auto theTag = goodMatchedElectrons[0];
    cnt[5]++;
    
    tag_charge = theTag->GetCharge();
    //tag_Et     = theTag->GetEnergy();
    tag_Et     = theTag->GetEnergy()*sin(2.*atan(exp(-theTag->GetEtaSC()))); 
    tag_pt     = theTag->GetPt();
    tag_eta    = theTag->GetEta();
    tag_phi    = theTag->GetPhi();
    tag_SCEt   = theTag->GetEnergySC()*sin(2.*atan(exp(-theTag->GetEtaSC()))); 
    tag_SCEta  = theTag->GetEtaSC();
    tag_SCPhi  = theTag->GetPhiSC();
    
    Log(1) << iEvent <<  "\n" ;
    Log(1) << iEvent << "Tag pt:" << tag_pt << "  eta:" <<  tag_eta << "  phi:" << tag_phi << "  energy:" << tag_Et;
    Log(1) << "  SC energy:" << theTag->GetEnergySC()  << "\n" ;
    
    
    ResetPassingProbeVars();
    // ignore photons close to this tag electron, or that fail ID cuts
    for (auto photon : goodPhoton) {
      
      double deta = getDETA(theTag->GetEta(), photon->GetEtaSC());
      double dphi = getDPHI(theTag->GetPhi(), photon->GetPhiSC());
      
      double deltaR = physObjectProcessor.GetDeltaR_SC(*photon, *theTag);	
      auto unmathched_photon = UnMatched(*photon, goodElectrons);
      //if(unmathched_photon){
      if (deta<0.15 && dphi<0.7) continue;
      photon_loop++;
      ok_photon = 1;
      nPho_notag++;
      phoEt_notag    = photon->GetEnergy()*sin(2.*atan(exp(-photon->GetEta())));
      phoEta_notag   = photon->GetEta();
      phoPhi_notag   = photon->GetPhi();
      phoAco_notag   = acop(theTag->GetPhi() - phoPhi_notag);
      phoSCEt_notag  = photon->GetEnergySC()*sin(2.*atan(exp(-photon->GetEtaSC()))); 
      phoSCEta_notag = photon->GetEtaSC();
      phoSCPhi_notag = photon->GetPhiSC();
      phoSCAco_notag = acop(theTag->GetPhi() - phoSCPhi_notag);
      //Log(0) << iEvent << "  photon event:" << photon_loop << "  photon pt:" << phoSCEt_notag << "   eta:" << phoSCEta_notag << "   phi:" << phoSCPhi_notag << "   deltaR:"<< deltaR << "  ok"<<  ok_photon << "\n" ;
      
      // ID parameters
      etaWidth   = photon->GetEtaWidth();
      HoE        = photon->GetHoverE();
      double E4  = photon->GetEnergyCrystalTop() + photon->GetEnergyCrystalBottom() + 
	photon->GetEnergyCrystalLeft() + photon->GetEnergyCrystalRight();
      swissCross = E4/photon->GetEnergyCrystalMax();
      
      ok_swissCross = (swissCross > config.params("photonMinSwissCross"));
      if (fabs(phoSCEta_notag) < 1.5) { // barrel
	ok_etaWidth = (etaWidth < config.params("photonMaxEtaWidthBarrel"));
	ok_HoE      = (HoE < config.params("photonMaxHoverEbarrel"));
      }
      else { // endcap
	ok_etaWidth = (etaWidth < config.params("photonMaxEtaWidthEndcap"));
	ok_HoE      = (HoE < config.params("photonMaxHoverEendcap"));
      }
      if (ok_swissCross && ok_etaWidth && ok_HoE) ok_ID = 1;
    } // photon loop
    
    // there should be max 1 photon unmatched to the tag
    if (nPho_notag>1) continue;
    cnt[6]++;
    
    // find the track not matched to the electron tag or the photon. there should be only 1
    ResetProbeVars();   
    for (auto probe : genTracks) {
      
      if (probe->GetPt() >3) continue;
      double deta = getDETA(theTag->GetEta(), probe->GetEta());
      double dphi = getDPHI(theTag->GetPhi(), probe->GetPhi());
      
      auto unmathched_track = UnMatched(*probe, goodElectrons);
      if (deta<0.15 && dphi<0.7) continue;
      ok_probeTrk = 1; probeTrk_loop++; nprobeTrk++;
 
      double dpt = fabs(tag_pt-probe->GetPt());
      double det = fabs(tag_Et-probe->GetPt());
     
      double dpt_tkEleGamma = fabs((tag_pt-probe->GetPt())-phoEt_notag);
      double det_tkEleGamma = fabs((tag_Et-probe->GetPt())-phoEt_notag);

      double dSCpt_tkEleGamma = fabs((tag_pt-probe->GetPt())-phoSCEt_notag);
      double dSCet_tkEleGamma = fabs((tag_Et-probe->GetPt())-phoSCEt_notag);
      
      if (det<probetkMinDet) {
	probetkMinDpt    = dpt;
	probetkMinDet    = det;
	diffPt_probetkEleGamma  = dpt_tkEleGamma;
	diffEt_probetkEleGamma  = det_tkEleGamma;
	diffSCPt_probetkEleGamma  = dSCpt_tkEleGamma;
	diffSCEt_probetkEleGamma  = dSCet_tkEleGamma;

	probetkCharge    = probe->GetCharge();   
	probetkPt        = probe->GetPt();
	probetkEta       = probe->GetEta();
	probetkPhi       = probe->GetPhi();
	probetkAco       = acop(theTag->GetPhi()-probetkPhi);
	probetkvx        = probe->GetVertexX();  
	probetkvy        = probe->GetVertexY();  
	probetkvz        = probe->GetVertexZ();  
	probetkd0        = probe->GetD0();  
	probetkdxy       = probe->GetDxy();  
	probetkdz        = probe->GetDz();  
	probetkdxyError  = probe->GetDxyErr();  
	probetkdzError   = probe->GetDzErr();  
	probetkValidHits = probe->GetNvalidHits();  
	probetkMissHits  = probe->GetNmissingHits();  
	Log(1) << iEvent << "  probe loop:" << probeTrk_loop << "  probe pt:" <<probetkPt << "   eta:" << probetkEta << "   phi:" << probetkPhi << "\n" ;
      }
    } 
    if (probetkMinDpt>990) continue;
    cnt[7]++;
    
    if(nprobeTrk >1) continue;   
    cnt[8]++;
    
    // the tag and track +- back to back
    if (acop(theTag->GetPhi() - probetkPhi)>0.5) continue;
    cnt[9]++;
    
    tr->Fill(); 
  } // event loop
  
  Log(0) << "Events in tag loop:"    << tag_loop      << "\n" ;
  Log(0) << "Events in probe loop: " << probeTrk_loop << "\n";
  Log(0) << "Events in photon loop:" << photon_loop   << "\n";
  
  
  outFile->Write();
  outFile->Close();

  for (int i=0; i<10; i++) cout << i << ": " << cnt[i] << "; ";
  cout << endl;
  
  return 0;
}

Double_t getDPHI( Double_t phi1, Double_t phi2) {
  return fabs(TVector2::Phi_mpi_pi(phi1-phi2));
}

Double_t getDETA(Double_t eta1, Double_t eta2){
  return TMath::Abs(eta1 - eta2);
}
