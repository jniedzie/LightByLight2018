//  getRecoIDEfficienciesQED_MC
//
//  Created by Ruchi Chudasama on 18/11/2020
//
//  Calculates QED Reco and ID efficiencies in MC driven way

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"
#include "EventDisplay.hpp"
#include "Logger.hpp"

int run;
int ls;
int evtnb;

float gen_elePt;
float gen_eleEta;
float gen_elePhi;

float  reco_elePt;
float  reco_eleEta;
float  reco_elePhi;
float  reco_eleEoverP;
float  reco_eleHoverE;
float  reco_eleMissHits;
float  reco_eledEtaAtVtx;
float  reco_eleSCEn;
float  reco_elePFChIso;
float  reco_elePFPhoIso;
float  reco_elePFNeuIso; 

float gen_elePt_reco_events;
float gen_eleEta_reco_events;
int ok_elematch;

void InitGenTree(TTree *genTree) {
  
  genTree->Branch("run",&run,"run/I");
  genTree->Branch("ls",&ls,"ls/I");
  genTree->Branch("evtnb",&evtnb,"evtnb/I");
  
  genTree->Branch("gen_elePt", &gen_elePt, "gen_elePt/F");
  genTree->Branch("gen_eleEta", &gen_eleEta, "gen_eleEta/F");
  genTree->Branch("gen_elePhi", &gen_elePhi, "gen_elePhi/F");
}

void InitTree(TTree *tree) {
  tree->Branch("reco_elePt", &reco_elePt, "reco_elePt/F");
  tree->Branch("reco_eleEta", &reco_eleEta, "reco_eleEta/F");
  tree->Branch("reco_elePhi", &reco_elePhi, "reco_elePhi/F");
  
  tree->Branch("reco_eleHoverE", &reco_eleHoverE, "reco_eleHoverE/F");
  tree->Branch("reco_eleMissHits", &reco_eleMissHits, "reco_eleMissHits/F");
  tree->Branch("reco_eledEtaAtVtx", &reco_eledEtaAtVtx, "reco_eledEtaAtVtx/F");
  tree->Branch("reco_eleSCEn", &reco_eleSCEn, "reco_eleSCEn/F");
  tree->Branch("reco_elePFChIso", &reco_elePFChIso, "reco_elePFChIso/F");
  tree->Branch("reco_elePFPhoIso", &reco_elePFPhoIso, "reco_elePFPhoIso/F");
  tree->Branch("reco_elePFNeuIso", &reco_elePFNeuIso, "reco_elePFNeuIso/F");
  tree->Branch("gen_elePt_reco_events", &gen_elePt_reco_events, "gen_elePt_reco_events/F");
  tree->Branch("gen_eleEta_reco_events", &gen_eleEta_reco_events, "gen_eleEta_reco_events/F");
  tree->Branch("ok_elematch",&ok_elematch,"ok_elematch/I");
}

// reset event variables
void ResetEventVars() {
  run = 0;
  ls = 0;
  evtnb = 0;
}


// reset Gen electron variables
void ResetRecoEleVars() {
  reco_elePt = -999;
  reco_eleEta = -999;
  reco_elePhi = -999;
  reco_eleEoverP = -999;
  reco_eleHoverE = -999;
  reco_eleMissHits = -999;
  reco_eledEtaAtVtx = -999;
  reco_eleSCEn = -999;
  reco_elePFChIso = -999;
  reco_elePFPhoIso = -999;
  reco_elePFNeuIso = -999; 
  ok_elematch = -999;
}


// reset Reco electron variables
void ResetGenEleVars() {
  gen_elePt = -999;
  gen_eleEta = -999;
  gen_elePhi = -999;
  gen_elePt_reco_events = -999;
  gen_eleEta_reco_events = -999;
  
}

/// Checks that number of arguments provided is correct and sets corresponding variables
void ReadInputArguments(int argc, char* argv[],
                        string &configPath, string &inputPath, string &outputPath, string &sampleName)
{
  if(argc != 5){
    Log(1)<<"This app requires 4 parameters:\n";
    Log(1)<<"./getRecoIDEfficienciesQED_MC configPath inputPath outputPath datasetName[Data|QED_SC|QED_SL|LbL|CEP]\n";
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
  outFile->mkdir("RecoIDQED");
  outFile->cd("RecoIDQED");
  TTree *genTree = new TTree("gen_tree","");
  TTree *tree = new TTree("reco_tree","");
  
  InitTree(tree);
  InitGenTree(genTree);
  
  auto events = make_unique<EventProcessor>(inputPath, dataset);
  int count_gen = 0; int count_reco = 0; int count_gen_reco_matched = 0; int tree_filled=0;   
  
  // Loop over events
  //for(int iEvent=100; iEvent < 200; iEvent++){
  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
    if(iEvent%1000 == 0) Log(0)<<"Processing event "<<iEvent<<"\n";
    if(iEvent >= config.params("maxEvents")) break;
    
    auto event = events->GetEvent(iEvent);
    
    ResetEventVars();
    ResetGenEleVars();	
    ResetRecoEleVars();	
    
    run = event->GetRunNumber();
    ls = event->GetLumiSection();
    evtnb = event->GetEventNumber();
    
    auto genElectrons  = event->GetPhysObjects(EPhysObjType::kGoodGenElectron);
    auto recoElectrons = event->GetPhysObjects(EPhysObjType::kElectronInAcceptance);
    
    for(auto gen : genElectrons ){  
      ResetGenEleVars();
      count_gen ++;
      Log(1)<< iEvent << " Coming in gen loop: et:" << gen->GetEt() << "  Eta:" << gen->GetEta() << " Phi:"<< gen->GetPhi();
      Log(1) << "  ele matched: " << ok_elematch << "  gen ele size:" << genElectrons.size() << "\n";  
      gen_elePt  = gen->GetEt();
      gen_eleEta = gen->GetEta();
      gen_elePhi = gen->GetPhi();
      genTree->Fill();
    }


    for(auto reco : recoElectrons ){  
      if(recoElectrons.size()>0)Log(1)<< iEvent << " Coming in reco loop " << recoElectrons.size() << "\n";  
      ResetRecoEleVars();
      count_reco ++; 

      for(auto gen : genElectrons ){  
	ResetGenEleVars();	

	Log(1)<< iEvent << " Coming in gen loop: et:" << gen->GetEt() << "Eta:" << gen->GetEta() << " Phi:"<< gen->GetPhi() ;  
	Log(1) << "  ele matched: " << ok_elematch << "\n";  
	double deltaR = sqrt(pow(gen->GetEta() - reco->GetEta(), 2)+
			     pow(gen->GetPhi() - reco->GetPhi(), 2));    
        bool gen_reco_match = deltaR < 0.3;

        if(gen_reco_match) { count_gen_reco_matched++;
	  ok_elematch = 1;       
	  Log(1)<< iEvent << " Coming in gen-reco macthed loop: et:" << reco->GetPt() << "Eta:" << reco->GetEta() << " Phi:"<< reco->GetPhi() << "  ele matched: " << ok_elematch << "\n" ; 
                 
	  reco_elePt        = reco->GetPt(); 
	  reco_eleEta       = reco->GetEta(); 
	  reco_elePhi       = reco->GetPhi(); 
	  
	  reco_eleHoverE    = reco->GetHoverE();
	  reco_eleMissHits  = reco->GetNmissingHits();
	  reco_eledEtaAtVtx = reco->GetDetaSeed();
	  
	  reco_elePFChIso   = reco->GetChargedIso();
	  reco_elePFPhoIso  = reco->GetPhotonIso();
	  reco_elePFNeuIso  = reco->GetNeutralIso();
	  
	  gen_elePt_reco_events = gen->GetPt(); 
	  gen_eleEta_reco_events = gen->GetEta(); 
	} // reco-gen matching
       } // gen loop
       

    tree->Fill(); Log(1) << "filled the tree" << "\n"; tree_filled++;
    Log(1)<< iEvent << " filled tree with gen et:" << gen_elePt << "Eta:" << gen_eleEta << " Phi:"<< gen_elePhi << "  ele matched: " << ok_elematch << "\n" ;  
    Log(1)<< iEvent << " filled tree with reco et:" << reco_elePt << "Eta:" << reco_eleEta << " Phi:"<< reco_elePhi << "  ele matched: " << ok_elematch << "\n" << "\n";  

      } // reco electron

  }//nentry    
 
  Log(1)<< " Number of gen electrons: " << count_gen << "\n";
  Log(1)<< " Number of reco electrons: " << count_reco << "\n";
  Log(1)<< " Number of gen-reco matched electrons: " << count_gen_reco_matched << "\n";
  Log(1)<< " Tree filled " << tree_filled << "number of times " << "\n";
 
  outFile->Write();
  outFile->Close();
  
  return 0;
  
  
}


