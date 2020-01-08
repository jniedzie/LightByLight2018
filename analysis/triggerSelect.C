#include "TTree.h"
#include "TFile.h"

#include <iostream>

using namespace std;

const char *triggerName = "HLT_HIUPC_SingleEG3_NotMBHF2AND_v1";

//string inPath = "/eos/cms/store/group/phys_heavyions/rchudasa/lbyl_2018/data_ntuples/HIForward/ntuples_data_new/200105_192027/0000/";
//string inFileName = inPath + "data_HiForestAOD_1-100.root";

string outPath = "/eos/cms/store/group/phys_diffraction/lbyl_2018/data_withSingleEG3/ntuples/";
//string outFileName = outPath + "data_HiForestAOD_withSingleEG3_test.root";

//const char* inFileName  = "ntuples_mc_qed_sc_withL1_merged.root";
//const char* inFileName  = "ntuples_mc_qed_sc_withL1_test.root";
//const char* outFileName = "ntuples_mc_qed_withSingleEG3.root";
//const char* outFileName = "ntuples_mc_qed_withSingleEG3_test.root";

string getNthLine(const string& filename, int N)
{
  ifstream in(filename.c_str());
  string s;
  for(int i=0; i<N; i++) getline(in, s);
  getline(in,s);
  return s;
}

void triggerSelect(int fileNumber)
{
  string inFileName = getNthLine("input_list.txt", fileNumber);
  string outFileName = outPath + "data_HiForestAOD_withSingleEG3_" + to_string(fileNumber) + ".root";
  
  cout<<"Input file: "<<inFileName<<endl;
  cout<<"Output file: "<<outFileName<<endl;
  
  cout<<"Starting conversion"<<endl;
  TFile *inFile       = TFile::Open(inFileName.c_str());
  TTree *inTreeHLT    = (TTree*)inFile->Get("hltanalysis/HltTree");
  TTree *inTreeL1     = (TTree*)inFile->Get("l1object/L1UpgradeFlatTree");
  TTree *inTreeEvent  = (TTree*)inFile->Get("ggHiNtuplizer/EventTree");
  cout<<"Trees opened"<<endl;
  int hasTrigger;
  inTreeHLT->SetBranchAddress(triggerName, &hasTrigger);
  
  int nWithTrigger = 0;
  
  TFile *outFile = new TFile(outFileName.c_str(), "recreate");
  outFile->cd();
  
  TDirectory *dirHLT    = outFile->mkdir("hltanalysis");
  TDirectory *dirL1     = outFile->mkdir("l1object");
  TDirectory *dirEvent  = outFile->mkdir("ggHiNtuplizer");
  
  cout<<"Cloning trees"<<endl;
  TTree *outTreeHLT   = inTreeHLT->CloneTree(0);
  TTree *outTreeL1    = inTreeL1->CloneTree(0);
  TTree *outTreeEvent = inTreeEvent->CloneTree(0);
  cout<<"Resetting trees"<<endl;
  outTreeHLT->Reset();
  outTreeL1->Reset();
  outTreeEvent->Reset();
  cout<<"Processing events"<<endl;
  
  for(int iEvent=0; iEvent<inTreeHLT->GetEntries(); iEvent++){
    if(iEvent%10000==0) cout<<"Processed events: "<<iEvent<<endl;
    
    inTreeHLT->GetEntry(iEvent);
    inTreeL1->GetEntry(iEvent);
    inTreeEvent->GetEntry(iEvent);
    
    if(hasTrigger){
      nWithTrigger++;
      outTreeHLT->Fill();
      outTreeL1->Fill();
      outTreeEvent->Fill();
    }
  }
  
  cout<<nWithTrigger<<"/"<<inTreeHLT->GetEntries()<<endl;
  
  dirHLT->cd();
  outTreeHLT->Write();
  dirL1->cd();
  outTreeL1->Write();
  dirEvent->cd();
  outTreeEvent->Write();
  
  outFile->Close();
}
