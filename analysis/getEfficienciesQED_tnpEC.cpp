//  getEfficienciesData
//
//  Created by Emilien Chapon on 26/10/2020
//
//  Calculates QED efficiencies in MC and data, as defined in the Analysis Note

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"
#include "EventDisplay.hpp"
#include "Logger.hpp"

int run;
int ls;
int evtnb;
float pt;
float eta;
float abseta;
float phi;
float ele_pt;
float ele_eta;
float ele_phi;
float ele_DR;
int NMissHits;
float deta_vtx;
float chiso;
float neuiso;
float phoiso;
float HoE;
float L1Et;
float L1eta;
float L1phi;
float L1DR;
float SCEt;
float SCeta;
float SCphi;
float Ntrk;
float HFE;
int ok_elematch;
int ok_ID;
int ok_deta_vtx;
int ok_NMissHits;
int ok_chiso;
int ok_neuiso;
int ok_phoiso;
int ok_HoE;
int ok_trg2;
int ok_trg3;
int ok_trg5;
int ok_chexcl;
int ok_neuexcl;
int ok_HFveto;
float tag_pt;
float tag_eta;
float tag_phi;
int pass_EG3;
int pass_EG5;
float tag_L1Et_passEG3;
float tag_L1Eta_passEG3;
float tag_L1Et_passEG5;
float tag_L1Eta_passEG5;
float pair_pt;
float pair_eta;
float pair_phi;
float pair_y;
float pair_mass;
float pair_acop;


/// initialise tree
void InitTree(TTree *tr) {
   tr->Branch("run",&run,"run/I");
   tr->Branch("ls",&ls,"ls/I");
   tr->Branch("evtnb",&evtnb,"evtnb/I");
   tr->Branch("pt",&pt,"pt/F");
   tr->Branch("eta",&eta,"eta/F");
   tr->Branch("abseta",&abseta,"abseta/F");
   tr->Branch("phi",&phi,"phi/F");
   tr->Branch("ele_pt",&ele_pt,"ele_pt/F");
   tr->Branch("ele_eta",&ele_eta,"ele_eta/F");
   tr->Branch("ele_phi",&ele_phi,"ele_phi/F");
   tr->Branch("ele_DR",&ele_DR,"ele_DR/F");
   tr->Branch("NMissHits",&NMissHits,"NMissHits/I");
   tr->Branch("deta_vtx",&deta_vtx,"deta_vtx/F");
   tr->Branch("chiso",&chiso,"chiso/F");
   tr->Branch("neuiso",&neuiso,"neuiso/F");
   tr->Branch("phoiso",&phoiso,"phoiso/F");
   tr->Branch("HoE",&HoE,"HoE/F");
   tr->Branch("L1Et",&L1Et,"L1Et/F");
   tr->Branch("L1eta",&L1eta,"L1eta/F");
   tr->Branch("L1phi",&L1phi,"L1phi/F");
   tr->Branch("L1DR",&L1DR,"L1DR/F");
   tr->Branch("SCEt",&SCEt,"SCEt/F");
   tr->Branch("SCeta",&SCeta,"SCeta/F");
   tr->Branch("SCphi",&SCphi,"SCphi/F");
   tr->Branch("Ntrk",&Ntrk,"Ntrk/F");
   tr->Branch("HFE",&HFE,"HFE/F");
   tr->Branch("ok_elematch",&ok_elematch,"ok_elematch/I");
   tr->Branch("ok_ID",&ok_ID,"ok_ID/I");
   tr->Branch("ok_deta_vtx",&ok_deta_vtx,"ok_deta_vtx/I");
   tr->Branch("ok_NMissHits",&ok_NMissHits,"ok_NMissHits/I");
   tr->Branch("ok_chiso",&ok_chiso,"ok_chiso/I");
   tr->Branch("ok_neuiso",&ok_neuiso,"ok_neuiso/I");
   tr->Branch("ok_phoiso",&ok_phoiso,"ok_phoiso/I");
   tr->Branch("ok_HoE",&ok_HoE,"ok_HoE/I");
   tr->Branch("ok_trg2",&ok_trg2,"ok_trg2/I");
   tr->Branch("ok_trg3",&ok_trg3,"ok_trg3/I");
   tr->Branch("ok_trg5",&ok_trg5,"ok_trg5/I");
   tr->Branch("ok_chexcl",&ok_chexcl,"ok_chexcl/I");
   tr->Branch("ok_neuexcl",&ok_neuexcl,"ok_neuexcl/I");
   tr->Branch("ok_HFveto",&ok_HFveto,"ok_HFveto/I");
   tr->Branch("tag_pt",&tag_pt,"tag_pt/F");
   tr->Branch("tag_eta",&tag_eta,"tag_eta/F");
   tr->Branch("tag_phi",&tag_phi,"tag_phi/F");
   tr->Branch("pass_EG3",&pass_EG3,"pass_EG3/I");
   tr->Branch("pass_EG5",&pass_EG5,"pass_EG5/I");
   tr->Branch("tag_L1Et_passEG3",&tag_L1Et_passEG3,"tag_L1Et_passEG3/F");
   tr->Branch("tag_L1Eta_passEG3",&tag_L1Eta_passEG3,"tag_L1Eta_passEG3/F");
   tr->Branch("tag_L1Et_passEG5",&tag_L1Et_passEG5,"tag_L1Et_passEG5/F");
   tr->Branch("tag_L1Eta_passEG5",&tag_L1Eta_passEG5,"tag_L1Eta_passEG5/F");
   tr->Branch("pair_pt",&pair_pt,"pair_pt/F");
   tr->Branch("pair_eta",&pair_eta,"pair_eta/F");
   tr->Branch("pair_phi",&pair_phi,"pair_phi/F");
   tr->Branch("pair_y",&pair_y,"pair_y/F");
   tr->Branch("pair_mass",&pair_mass,"pair_mass/F");
   tr->Branch("pair_acop",&pair_acop,"pair_acop/F");
}

// reset event variables
void ResetEventVars() {
   run = 0;
   ls = 0;
   evtnb = 0;
   Ntrk = 0;
   HFE = 0;
   ok_chexcl = 0;
   ok_neuexcl = 0;
   ok_HFveto = 0;
}

// reset tag variables
void ResetTagVars() {
   pass_EG3 = 0;
   pass_EG5 = 0;
   tag_pt = 0;
   tag_eta = 0;
   tag_phi = 0;
   tag_L1Et_passEG3 = 0;
   tag_L1Eta_passEG3 = 0;
   tag_L1Et_passEG5 = 0;
   tag_L1Eta_passEG5 = 0;
}

// reset probe variables
void ResetProbeVars() {
   pt = 0;
   eta = 0;
   abseta = 0;
   phi = 0;
   ele_pt = 0;
   ele_eta = 0;
   ele_phi = 0;
   ele_DR = 0;
   NMissHits = 0;
   deta_vtx = 0;
   chiso = 0;
   neuiso = 0;
   phoiso = 0;
   HoE = 0;
   L1Et = 0;
   L1eta = 0;
   L1phi = 0;
   L1DR = 0;
   SCEt = 0;
   SCeta = 0;
   SCphi = 0;
   ok_elematch = 0;
   ok_ID = 0;
   ok_deta_vtx = 0;
   ok_NMissHits = 0;
   ok_chiso = 0;
   ok_neuiso = 0;
   ok_phoiso = 0;
   ok_HoE = 0;
   ok_trg2 = 0;
   ok_trg3 = 0;
   ok_trg5 = 0;
   pair_pt = 0;
   pair_eta = 0;
   pair_phi = 0;
   pair_y = 0;
   pair_mass = 0;
   pair_acop = 0;
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
  
  int tag_loop = 0; int tag_cuts = 0; int probe_loop = 0; int probe_cuts =0; int matched_ele =0; 
  
  // Loop over events
  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
  //for(int iEvent=0; iEvent<200; iEvent++){
    if(iEvent%1000 == 0) Log(0)<<"Processing event "<<iEvent<<"\n";
    if(iEvent >= config.params("maxEvents")) break;

    auto event = events->GetEvent(iEvent);

    // Check trigger
    //if(!event->HasTrigger(kSingleEG3noHF) && !event->HasTrigger(kSingleEG5noHF)) continue;
    //if(!event->HasTrigger(kSingleEG3noHF)) continue;
    if(!event->HasTrigger(kSingleEG5noHF)) continue;

    ResetEventVars();
    run = event->GetRunNumber();
    ls = event->GetLumiSection();
    evtnb = event->GetEventNumber();

    // event variables
    ok_neuexcl = event->HasAdditionalTowers();
    Ntrk = event->GetPhysObjects(EPhysObjType::kGoodGeneralTrack).size();
    ok_chexcl = (Ntrk==2);

    auto L1EGs = event->GetPhysObjects(EPhysObjType::kL1EG);

    auto goodElectrons = event->GetPhysObjects(EPhysObjType::kGoodElectron);
    auto genTracks = event->GetPhysObjects(EPhysObjType::kGoodGeneralTrack);
    //auto allElectrons = event->GetPhysObjects(EPhysObjType::kElectron);
    auto allElectrons = event->GetPhysObjects(EPhysObjType::kElectronInAcceptance);

    if(allElectrons.size()>2) continue;
    if(goodElectrons.size()>2) continue;
    if(genTracks.size()>10) continue;

    // loop on tags (good electrons with additional cuts)
    for (auto tag : goodElectrons) {
       // trigger matching
       auto matchedL1EG3 = TriggerMatch(*tag, L1EGs, 3, 5);
       auto matchedL1EG5 = TriggerMatch(*tag, L1EGs, 5, 5);
       if (!matchedL1EG3 && !matchedL1EG5) continue;
       //if (!matchedL1EG5) continue;
       //if (!TriggerMatch(*tag, L1EGs, 3, 5)) continue;
       ResetTagVars();
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
       tag_pt = tag->GetPt();
       tag_eta = tag->GetEta();
       tag_phi = tag->GetPhi();
       tag_loop++;
     
       if (tag_pt < config.params("electronMinPt") || fabs(tag_eta) > config.params("electronMaxEta")) continue;
       tag_cuts++;

       // loop on probes (general tracks)
       for (auto probe : genTracks) {
         // only look at opposite sign events (also excludes cases when tag==probe)

          if(tag->GetCharge() == probe->GetCharge()) continue;
          ResetProbeVars(); probe_loop++;
          pt = probe->GetPt();
          eta = probe->GetEta();
          abseta = fabs(eta);
          phi = probe->GetPhi();

          // basic cuts
          if (pt < config.params("electronMinPt") || fabs(eta) > config.params("electronMaxEta")) continue;
          probe_cuts++;

          // reco
          auto matchedEle = EleMatch(*probe, allElectrons);
          if (matchedEle) {
             ok_elematch = 1; matched_ele++;
             ele_pt = matchedEle->GetPt();
             ele_eta = matchedEle->GetEta();
             ele_phi = matchedEle->GetPhi();
             ele_DR = physObjectProcessor.GetDeltaR(*probe,*matchedEle);
             SCEt =  matchedEle->GetEnergySC()*sin(2.*atan(exp(-matchedEle->GetEtaSC()))); 
             SCeta = matchedEle->GetEtaSC();
             SCphi = matchedEle->GetPhiSC();

             // ID
             deta_vtx = matchedEle->GetDetaSeed();
             NMissHits = matchedEle->GetNmissingHits();
             chiso = matchedEle->GetChargedIso();
             neuiso = matchedEle->GetNeutralIso();
             phoiso = matchedEle->GetPhotonIso();
             HoE = matchedEle->GetHoverE();

             ok_NMissHits = (NMissHits <= config.params("electronMaxNmissingHits"));
             if (fabs(ele_eta) < 1.5) { // barrel
                ok_deta_vtx = (deta_vtx < config.params("electronMaxDetaSeedBarrel"));
                ok_chiso = (chiso < config.params("electronMaxChargedIsoBarrel"));
                ok_neuiso = (neuiso < config.params("electronMaxNeutralIsoBarrel"));
                ok_phoiso = (phoiso < config.params("electronMaxPhotonIsoBarrel"));
                ok_HoE = (HoE < config.params("electronMaxHoverE_Barrel"));
             } else { // endcap
                ok_deta_vtx = (deta_vtx < config.params("electronMaxDetaSeedEndcap"));
                ok_chiso = (chiso < config.params("electronMaxChargedIsoEndcap"));
                ok_neuiso = (neuiso < config.params("electronMaxNeutralIsoEndcap"));
                ok_phoiso = (phoiso < config.params("electronMaxPhotonIsoEndcap"));
                ok_HoE = (HoE < config.params("electronMaxHoverE_Endcap"));
             }
             if (ok_NMissHits && ok_deta_vtx 
                   // && ok_chiso && ok_neuiso && ok_phoiso 
                   && ok_HoE) ok_ID = 1;

             // trigger
             auto matchedL1EG2 = TriggerMatch(*matchedEle, L1EGs, 2, 5);
             if (matchedL1EG2) {
                L1Et = matchedL1EG2->GetEt();
                L1eta = matchedL1EG2->GetEta();
                L1phi = matchedL1EG2->GetPhi();
                L1DR = physObjectProcessor.GetDeltaR(*matchedEle, *matchedL1EG2);
                ok_trg2 = 1;
                ok_trg3 = (L1Et > 3);
                ok_trg5 = (L1Et > 5);
             }
          } // if matchedEle

          // compute pair quantities
          TLorentzVector thepair = physObjectProcessor.GetDielectron(*tag, *probe);
          pair_pt = thepair.Pt();
          pair_eta = thepair.Eta();
          pair_y = thepair.Rapidity();
          pair_phi = thepair.Phi();
          pair_mass = thepair.M();
          pair_acop = physObjectProcessor.GetAcoplanarity(*tag, *probe);
    
          tr->Fill(); 
       } // probe track loop
    } // tag electron loop
  } // event loop

  Log(0) << "Events in tag loop:" << tag_loop << "\n" ;
  Log(0) << "Events after pt and eta cut of tag loop:" << tag_cuts << "\n";
  Log(0) << "Events in probe loop: " << probe_loop << "\n";
  Log(0) << "Events after cuts on probe:" << probe_cuts << "\n";
  Log(0) << "Matched electrons and tracks:" << matched_ele << "\n";

 
  outFile->Write();
  outFile->Close();
  
  return 0;
}
