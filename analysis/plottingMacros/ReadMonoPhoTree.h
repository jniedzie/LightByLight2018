//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Sep 13 09:17:33 2021 by ROOT version 6.20/06
// from TTree monoPhoton_tree/
// found on file: merged_anomalous_data.root
//////////////////////////////////////////////////////////

#ifndef ReadMonoPhoTree_h
#define ReadMonoPhoTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

class ReadMonoPhoTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           run;
   Int_t           ls;
   Int_t           evtnb;
   Int_t           mono_nPho;
   Float_t         monoPhoEt;
   Float_t         monoPhoEta;
   Float_t         monoPhoPhi;
   Float_t         monoPhoSCEt;
   Float_t         monoPhoSCEta;
   Float_t         monoPhoSCPhi;
   Int_t           monoPhook_zdcexcl;
   Float_t         monoPhoEtaWidth;
   Float_t         monoPhoHoverE;
   Float_t         monoPhoEnergyTop;
   Float_t         monoPhoEnergyBottom;
   Float_t         monoPhoEnergyLeft;
   Float_t         monoPhoEnergyRight;
   Float_t         monoPhoEnergyCrysMax;
   Float_t         monoPhoSeedTime;
   Float_t         monoPhoSigmaIEta;
   Float_t         leadingEmEnergy_EB;
   Float_t         leadingEmEnergy_EE;
   Float_t         leadingHadEnergy_HB;
   Float_t         leadingHadEnergy_HE;
   Float_t         leadingHadEnergy_HF_Plus;
   Float_t         leadingHadEnergy_HF_Minus;
   Int_t           mono_nL1Pho;
   vector<float>   *monoPhoL1Et;
   vector<float>   *monoPhoL1Eta;
   vector<float>   *monoPhoL1Phi;
   vector<float>   *monoPhoL1deta;
   vector<float>   *monoPhoL1dphi;
   vector<float>   *monoPhoL1dr;
   Int_t           monoPho_nPixelCluster;
   Int_t           monoPho_nPixelRecHits;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_ls;   //!
   TBranch        *b_evtnb;   //!
   TBranch        *b_mono_nPho;   //!
   TBranch        *b_monoPhoEt;   //!
   TBranch        *b_monoPhoEta;   //!
   TBranch        *b_monoPhoPhi;   //!
   TBranch        *b_monoPhoSCEt;   //!
   TBranch        *b_monoPhoSCEta;   //!
   TBranch        *b_monoPhoSCPhi;   //!
   TBranch        *b_monoPhook_zdcexcl;   //!
   TBranch        *b_monoPhoEtaWidth;   //!
   TBranch        *b_monoPhoHoverE;   //!
   TBranch        *b_monoPhoEnergyTop;   //!
   TBranch        *b_monoPhoEnergyBottom;   //!
   TBranch        *b_monoPhoEnergyLeft;   //!
   TBranch        *b_monoPhoEnergyRight;   //!
   TBranch        *b_monoPhoEnergyCrysMax;   //!
   TBranch        *b_monoPhoSeedTime;   //!
   TBranch        *b_monoPhoSigmaIEta;   //!
   TBranch        *b_leadingEmEnergy_EB;   //!
   TBranch        *b_leadingEmEnergy_EE;   //!
   TBranch        *b_leadingHadEnergy_HB;   //!
   TBranch        *b_leadingHadEnergy_HE;   //!
   TBranch        *b_leadingHadEnergy_HF_Plus;   //!
   TBranch        *b_leadingHadEnergy_HF_Minus;   //!
   TBranch        *b_mono_nL1Pho;   //!
   TBranch        *b_monoPhoL1Et;   //!
   TBranch        *b_monoPhoL1Eta;   //!
   TBranch        *b_monoPhoL1Phi;   //!
   TBranch        *b_monoPhoL1deta;   //!
   TBranch        *b_monoPhoL1dphi;   //!
   TBranch        *b_monoPhoL1dr;   //!
   TBranch        *b_monoPho_nPixelCluster;   //!
   TBranch        *b_monoPho_nPixelRecHits;   //!

   ReadMonoPhoTree(TTree *tree=0);
   virtual ~ReadMonoPhoTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ReadMonoPhoTree_cxx
ReadMonoPhoTree::ReadMonoPhoTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("merged_anomalous_data.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("merged_anomalous_data.root");
      }
      f->GetObject("monoPhoton_tree",tree);

   }
   Init(tree);
}

ReadMonoPhoTree::~ReadMonoPhoTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ReadMonoPhoTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ReadMonoPhoTree::LoadTree(Long64_t entry)
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

void ReadMonoPhoTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   monoPhoL1Et = 0;
   monoPhoL1Eta = 0;
   monoPhoL1Phi = 0;
   monoPhoL1deta = 0;
   monoPhoL1dphi = 0;
   monoPhoL1dr = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("ls", &ls, &b_ls);
   fChain->SetBranchAddress("evtnb", &evtnb, &b_evtnb);
   fChain->SetBranchAddress("mono_nPho", &mono_nPho, &b_mono_nPho);
   fChain->SetBranchAddress("monoPhoEt", &monoPhoEt, &b_monoPhoEt);
   fChain->SetBranchAddress("monoPhoEta", &monoPhoEta, &b_monoPhoEta);
   fChain->SetBranchAddress("monoPhoPhi", &monoPhoPhi, &b_monoPhoPhi);
   fChain->SetBranchAddress("monoPhoSCEt", &monoPhoSCEt, &b_monoPhoSCEt);
   fChain->SetBranchAddress("monoPhoSCEta", &monoPhoSCEta, &b_monoPhoSCEta);
   fChain->SetBranchAddress("monoPhoSCPhi", &monoPhoSCPhi, &b_monoPhoSCPhi);
   fChain->SetBranchAddress("monoPhook_zdcexcl", &monoPhook_zdcexcl, &b_monoPhook_zdcexcl);
   fChain->SetBranchAddress("monoPhoEtaWidth", &monoPhoEtaWidth, &b_monoPhoEtaWidth);
   fChain->SetBranchAddress("monoPhoHoverE", &monoPhoHoverE, &b_monoPhoHoverE);
   fChain->SetBranchAddress("monoPhoEnergyTop", &monoPhoEnergyTop, &b_monoPhoEnergyTop);
   fChain->SetBranchAddress("monoPhoEnergyBottom", &monoPhoEnergyBottom, &b_monoPhoEnergyBottom);
   fChain->SetBranchAddress("monoPhoEnergyLeft", &monoPhoEnergyLeft, &b_monoPhoEnergyLeft);
   fChain->SetBranchAddress("monoPhoEnergyRight", &monoPhoEnergyRight, &b_monoPhoEnergyRight);
   fChain->SetBranchAddress("monoPhoEnergyCrysMax", &monoPhoEnergyCrysMax, &b_monoPhoEnergyCrysMax);
   fChain->SetBranchAddress("monoPhoSeedTime", &monoPhoSeedTime, &b_monoPhoSeedTime);
   fChain->SetBranchAddress("monoPhoSigmaIEta", &monoPhoSigmaIEta, &b_monoPhoSigmaIEta);
   fChain->SetBranchAddress("leadingEmEnergy_EB", &leadingEmEnergy_EB, &b_leadingEmEnergy_EB);
   fChain->SetBranchAddress("leadingEmEnergy_EE", &leadingEmEnergy_EE, &b_leadingEmEnergy_EE);
   fChain->SetBranchAddress("leadingHadEnergy_HB", &leadingHadEnergy_HB, &b_leadingHadEnergy_HB);
   fChain->SetBranchAddress("leadingHadEnergy_HE", &leadingHadEnergy_HE, &b_leadingHadEnergy_HE);
   fChain->SetBranchAddress("leadingHadEnergy_HF_Plus", &leadingHadEnergy_HF_Plus, &b_leadingHadEnergy_HF_Plus);
   fChain->SetBranchAddress("leadingHadEnergy_HF_Minus", &leadingHadEnergy_HF_Minus, &b_leadingHadEnergy_HF_Minus);
   fChain->SetBranchAddress("mono_nL1Pho", &mono_nL1Pho, &b_mono_nL1Pho);
   fChain->SetBranchAddress("monoPhoL1Et", &monoPhoL1Et, &b_monoPhoL1Et);
   fChain->SetBranchAddress("monoPhoL1Eta", &monoPhoL1Eta, &b_monoPhoL1Eta);
   fChain->SetBranchAddress("monoPhoL1Phi", &monoPhoL1Phi, &b_monoPhoL1Phi);
   fChain->SetBranchAddress("monoPhoL1deta", &monoPhoL1deta, &b_monoPhoL1deta);
   fChain->SetBranchAddress("monoPhoL1dphi", &monoPhoL1dphi, &b_monoPhoL1dphi);
   fChain->SetBranchAddress("monoPhoL1dr", &monoPhoL1dr, &b_monoPhoL1dr);
   fChain->SetBranchAddress("monoPho_nPixelCluster", &monoPho_nPixelCluster, &b_monoPho_nPixelCluster);
   fChain->SetBranchAddress("monoPho_nPixelRecHits", &monoPho_nPixelRecHits, &b_monoPho_nPixelRecHits);
   Notify();
}

Bool_t ReadMonoPhoTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ReadMonoPhoTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ReadMonoPhoTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ReadMonoPhoTree_cxx
