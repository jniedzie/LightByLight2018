//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Nov 21 18:04:00 2017 by ROOT version 6.04/02
// from TTree PixelTree/Tree of Pixel Hits
// found on file: /eos/cms/store/group/phys_diffraction/diphoton/aug_reco_data_check_for_lumi/hiforest2/00/hiforest_0.root
//////////////////////////////////////////////////////////

#ifndef pixelTreeReaderData_h
#define pixelTreeReaderData_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class pixelTreeReaderData {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           nEv;
   Int_t           nLumi;
   Int_t           nBX;
   Int_t           nRun;
   Float_t         beamSpotX;
   Float_t         beamSpotY;
   Float_t         beamSpotZ;
   Int_t           nhits1;
   Int_t           nhits2;
   Int_t           nhits3;
   Int_t           nhits4;
   Int_t           nhits5;
   Int_t           ntrks;
   Int_t           ntrksCut;
   Int_t           mult;
   Int_t           nv;
   Float_t         vx[2];   //[nv]
   Float_t         vy[2];   //[nv]
   Float_t         vz[2];   //[nv]
   Float_t         eta1[21542];   //[nhits1]
   Float_t         phi1[21542];   //[nhits1]
   Float_t         r1[21542];   //[nhits1]
   Float_t         cs1[21542];   //[nhits1]
   Float_t         ch1[21542];   //[nhits1]
   Float_t         eta2[27319];   //[nhits2]
   Float_t         phi2[27319];   //[nhits2]
   Float_t         r2[27319];   //[nhits2]
   Float_t         cs2[27319];   //[nhits2]
   Float_t         ch2[27319];   //[nhits2]
   Float_t         eta3[15916];   //[nhits3]
   Float_t         phi3[15916];   //[nhits3]
   Float_t         r3[15916];   //[nhits3]
   Float_t         cs3[15916];   //[nhits3]
   Float_t         ch3[15916];   //[nhits3]
   Float_t         eta4[24157];   //[nhits4]
   Float_t         phi4[24157];   //[nhits4]
   Float_t         r4[24157];   //[nhits4]
   Float_t         cs4[24157];   //[nhits4]
   Float_t         ch4[24157];   //[nhits4]
   Float_t         eta5[23969];   //[nhits5]
   Float_t         phi5[23969];   //[nhits5]
   Float_t         r5[23969];   //[nhits5]
   Float_t         cs5[23969];   //[nhits5]
   Float_t         ch5[23969];   //[nhits5]

   // List of branches
   TBranch        *b_nEv;   //!
   TBranch        *b_nLumi;   //!
   TBranch        *b_nBX;   //!
   TBranch        *b_nRun;   //!
   TBranch        *b_beamSpotX;   //!
   TBranch        *b_beamSpotY;   //!
   TBranch        *b_beamSpotZ;   //!
   TBranch        *b_nhits1;   //!
   TBranch        *b_nhits2;   //!
   TBranch        *b_nhits3;   //!
   TBranch        *b_nhits4;   //!
   TBranch        *b_nhits5;   //!
   TBranch        *b_ntrks;   //!
   TBranch        *b_ntrksCut;   //!
   TBranch        *b_mult;   //!
   TBranch        *b_nv;   //!
   TBranch        *b_vx;   //!
   TBranch        *b_vy;   //!
   TBranch        *b_vz;   //!
   TBranch        *b_eta1;   //!
   TBranch        *b_phi1;   //!
   TBranch        *b_r1;   //!
   TBranch        *b_cs1;   //!
   TBranch        *b_ch1;   //!
   TBranch        *b_eta2;   //!
   TBranch        *b_phi2;   //!
   TBranch        *b_r2;   //!
   TBranch        *b_cs2;   //!
   TBranch        *b_ch2;   //!
   TBranch        *b_eta3;   //!
   TBranch        *b_phi3;   //!
   TBranch        *b_r3;   //!
   TBranch        *b_cs3;   //!
   TBranch        *b_ch3;   //!
   TBranch        *b_eta4;   //!
   TBranch        *b_phi4;   //!
   TBranch        *b_r4;   //!
   TBranch        *b_cs4;   //!
   TBranch        *b_ch4;   //!
   TBranch        *b_eta5;   //!
   TBranch        *b_phi5;   //!
   TBranch        *b_r5;   //!
   TBranch        *b_cs5;   //!
   TBranch        *b_ch5;   //!

   pixelTreeReaderData(TTree *tree=0);
   virtual ~pixelTreeReaderData();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef pixelTreeReaderData_cxx
pixelTreeReaderData::pixelTreeReaderData(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/group/phys_diffraction/diphoton/aug_reco_data_check_for_lumi/hiforest2/00/hiforest_0.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/eos/cms/store/group/phys_diffraction/diphoton/aug_reco_data_check_for_lumi/hiforest2/00/hiforest_0.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/eos/cms/store/group/phys_diffraction/diphoton/aug_reco_data_check_for_lumi/hiforest2/00/hiforest_0.root:/pixel");
      dir->GetObject("PixelTree",tree);

   }
   Init(tree);
}

pixelTreeReaderData::~pixelTreeReaderData()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t pixelTreeReaderData::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t pixelTreeReaderData::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void pixelTreeReaderData::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("nEv", &nEv, &b_nEv);
   fChain->SetBranchAddress("nLumi", &nLumi, &b_nLumi);
   fChain->SetBranchAddress("nBX", &nBX, &b_nBX);
   fChain->SetBranchAddress("nRun", &nRun, &b_nRun);
   fChain->SetBranchAddress("beamSpotX", &beamSpotX, &b_beamSpotX);
   fChain->SetBranchAddress("beamSpotY", &beamSpotY, &b_beamSpotY);
   fChain->SetBranchAddress("beamSpotZ", &beamSpotZ, &b_beamSpotZ);
   fChain->SetBranchAddress("nhits1", &nhits1, &b_nhits1);
   fChain->SetBranchAddress("nhits2", &nhits2, &b_nhits2);
   fChain->SetBranchAddress("nhits3", &nhits3, &b_nhits3);
   fChain->SetBranchAddress("nhits4", &nhits4, &b_nhits4);
   fChain->SetBranchAddress("nhits5", &nhits5, &b_nhits5);
   fChain->SetBranchAddress("ntrks", &ntrks, &b_ntrks);
   fChain->SetBranchAddress("ntrksCut", &ntrksCut, &b_ntrksCut);
   fChain->SetBranchAddress("mult", &mult, &b_mult);
   fChain->SetBranchAddress("nv", &nv, &b_nv);
   fChain->SetBranchAddress("vx", vx, &b_vx);
   fChain->SetBranchAddress("vy", vy, &b_vy);
   fChain->SetBranchAddress("vz", vz, &b_vz);
   fChain->SetBranchAddress("eta1", eta1, &b_eta1);
   fChain->SetBranchAddress("phi1", phi1, &b_phi1);
   fChain->SetBranchAddress("r1", r1, &b_r1);
   fChain->SetBranchAddress("cs1", cs1, &b_cs1);
   fChain->SetBranchAddress("ch1", ch1, &b_ch1);
   fChain->SetBranchAddress("eta2", eta2, &b_eta2);
   fChain->SetBranchAddress("phi2", phi2, &b_phi2);
   fChain->SetBranchAddress("r2", r2, &b_r2);
   fChain->SetBranchAddress("cs2", cs2, &b_cs2);
   fChain->SetBranchAddress("ch2", ch2, &b_ch2);
   fChain->SetBranchAddress("eta3", eta3, &b_eta3);
   fChain->SetBranchAddress("phi3", phi3, &b_phi3);
   fChain->SetBranchAddress("r3", r3, &b_r3);
   fChain->SetBranchAddress("cs3", cs3, &b_cs3);
   fChain->SetBranchAddress("ch3", ch3, &b_ch3);
   fChain->SetBranchAddress("eta4", eta4, &b_eta4);
   fChain->SetBranchAddress("phi4", phi4, &b_phi4);
   fChain->SetBranchAddress("r4", r4, &b_r4);
   fChain->SetBranchAddress("cs4", cs4, &b_cs4);
   fChain->SetBranchAddress("ch4", ch4, &b_ch4);
   fChain->SetBranchAddress("eta5", eta5, &b_eta5);
   fChain->SetBranchAddress("phi5", phi5, &b_phi5);
   fChain->SetBranchAddress("r5", r5, &b_r5);
   fChain->SetBranchAddress("cs5", cs5, &b_cs5);
   fChain->SetBranchAddress("ch5", ch5, &b_ch5);
   Notify();
}

Bool_t pixelTreeReaderData::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void pixelTreeReaderData::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t pixelTreeReaderData::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef pixelTreeReaderData_cxx
