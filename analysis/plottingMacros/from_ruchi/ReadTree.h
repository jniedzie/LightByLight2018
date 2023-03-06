//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jun 27 15:55:03 2022 by ROOT version 6.20/04
// from TTree output_tree/
// found on file: data_cosThetaStar.root
//////////////////////////////////////////////////////////

#ifndef ReadTree_h
#define ReadTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class ReadTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           run;
   Int_t           ls;
   Int_t           evtnb;
   Int_t           nPho;
   Float_t         phoEt_1;
   Float_t         phoEta_1;
   Float_t         phoPhi_1;
   Float_t         phoSCEt_1;
   Float_t         phoSCEta_1;
   Float_t         phoSCPhi_1;
   Float_t         phoEtaWidth_1;
   Float_t         phoHoverE_1;
   Float_t         phoEnergyTop_1;
   Float_t         phoEnergyBottom_1;
   Float_t         phoEnergyLeft_1;
   Float_t         phoEnergyRight_1;
   Float_t         phoEnergyCrysMax_1;
   Float_t         phoSwissCross_1;
   Float_t         phoSeedTime_1;
   Float_t         phoSigmaIEta_1;
   Float_t         phoEt_2;
   Float_t         phoEta_2;
   Float_t         phoPhi_2;
   Float_t         phoSCEt_2;
   Float_t         phoSCEta_2;
   Float_t         phoSCPhi_2;
   Float_t         phoEtaWidth_2;
   Float_t         phoHoverE_2;
   Float_t         phoEnergyTop_2;
   Float_t         phoEnergyBottom_2;
   Float_t         phoEnergyLeft_2;
   Float_t         phoEnergyRight_2;
   Float_t         phoEnergyCrysMax_2;
   Float_t         phoSwissCross_2;
   Float_t         phoSeedTime_2;
   Float_t         phoSigmaIEta_2;
   Float_t         vSum_M;
   Float_t         vSum_Energy;
   Float_t         vSum_Pt;
   Float_t         vSum_Eta;
   Float_t         vSum_Phi;
   Float_t         vSum_Rapidity;
   Float_t         pho_dpt;
   Float_t         pho_deta;
   Float_t         pho_dphi;
   Float_t         pho_acop;
   Int_t           ok_neuexcl;
   Float_t         zdc_energy_pos;
   Float_t         zdc_energy_neg;
   Int_t           ok_zdcexcl_1n_pos;
   Int_t           ok_zdcexcl_1n_neg;
   Int_t           ok_zdcexcl_3n_pos;
   Int_t           ok_zdcexcl_3n_neg;
   Int_t           ok_zdcexcl_4n_pos;
   Int_t           ok_zdcexcl_4n_neg;
   Int_t           ok_zdcexcl_5n_pos;
   Int_t           ok_zdcexcl_5n_neg;
   Int_t           ok_zdcexcl;
   Int_t           ok_castorexcl;
   Int_t           ok_chexcl;
   Int_t           ok_chexcl_tracks;
   Int_t           ok_chexcl_electrons;
   Int_t           ok_chexcl_muons;
   Int_t           ok_chexcl_goodtracks;
   Int_t           ok_chexcl_goodelectrons;
   Float_t         SFweight_reco[16];
   Float_t         SFweight_trig[16];
   Int_t           nPixelCluster;
   Int_t           nPixelRecHits;
   Int_t           nTracks;
   Float_t         costhetastar;
   Float_t         cos_photon_pair_helicity0;
   Float_t         cos_photon_pair_helicity1;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_ls;   //!
   TBranch        *b_evtnb;   //!
   TBranch        *b_nPho;   //!
   TBranch        *b_phoEt_1;   //!
   TBranch        *b_phoEta_1;   //!
   TBranch        *b_phoPhi_1;   //!
   TBranch        *b_phoSCEt_1;   //!
   TBranch        *b_phoSCEta_1;   //!
   TBranch        *b_phoSCPhi_1;   //!
   TBranch        *b_phoEtaWidth_1;   //!
   TBranch        *b_phoHoverE_1;   //!
   TBranch        *b_phoEnergyTop_1;   //!
   TBranch        *b_phoEnergyBottom_1;   //!
   TBranch        *b_phoEnergyLeft_1;   //!
   TBranch        *b_phoEnergyRight_1;   //!
   TBranch        *b_phoEnergyCrysMax_1;   //!
   TBranch        *b_phoSwissCross_1;   //!
   TBranch        *b_phoSeedTime_1;   //!
   TBranch        *b_phoSigmaIEta_1;   //!
   TBranch        *b_phoEt_2;   //!
   TBranch        *b_phoEta_2;   //!
   TBranch        *b_phoPhi_2;   //!
   TBranch        *b_phoSCEt_2;   //!
   TBranch        *b_phoSCEta_2;   //!
   TBranch        *b_phoSCPhi_2;   //!
   TBranch        *b_phoEtaWidth_2;   //!
   TBranch        *b_phoHoverE_2;   //!
   TBranch        *b_phoEnergyTop_2;   //!
   TBranch        *b_phoEnergyBottom_2;   //!
   TBranch        *b_phoEnergyLeft_2;   //!
   TBranch        *b_phoEnergyRight_2;   //!
   TBranch        *b_phoEnergyCrysMax_2;   //!
   TBranch        *b_phoSwissCross_2;   //!
   TBranch        *b_phoSeedTime_2;   //!
   TBranch        *b_phoSigmaIEta_2;   //!
   TBranch        *b_vSum_diPho_M;   //!
   TBranch        *b_vSum_diPho_Energy;   //!
   TBranch        *b_vSum_diPho_Pt;   //!
   TBranch        *b_vSum_diPho_Eta;   //!
   TBranch        *b_vSum_diPho_Phi;   //!
   TBranch        *b_vSum_diPho_Rapidity;   //!
   TBranch        *b_pho_dpt;   //!
   TBranch        *b_pho_deta;   //!
   TBranch        *b_pho_dphi;   //!
   TBranch        *b_pho_acop;   //!
   TBranch        *b_ok_neuexcl;   //!
   TBranch        *b_zdc_energy_pos;   //!
   TBranch        *b_zdc_energy_neg;   //!
   TBranch        *b_ok_zdcexcl_1n_pos;   //!
   TBranch        *b_ok_zdcexcl_1n_neg;   //!
   TBranch        *b_ok_zdcexcl_3n_pos;   //!
   TBranch        *b_ok_zdcexcl_3n_neg;   //!
   TBranch        *b_ok_zdcexcl_4n_pos;   //!
   TBranch        *b_ok_zdcexcl_4n_neg;   //!
   TBranch        *b_ok_zdcexcl_5n_pos;   //!
   TBranch        *b_ok_zdcexcl_5n_neg;   //!
   TBranch        *b_ok_zdcexcl;   //!
   TBranch        *b_ok_castorexcl;   //!
   TBranch        *b_ok_chexcl;   //!
   TBranch        *b_ok_chexcl_tracks;   //!
   TBranch        *b_ok_chexcl_electrons;   //!
   TBranch        *b_ok_chexcl_muons;   //!
   TBranch        *b_ok_chexcl_goodtracks;   //!
   TBranch        *b_ok_chexcl_goodelectrons;   //!
   TBranch        *b_SFweight_reco;   //!
   TBranch        *b_SFweight_trig;   //!
   TBranch        *b_nPixelCluster;   //!
   TBranch        *b_nPixelRecHits;   //!
   TBranch        *b_nTracks;   //!
   TBranch        *b_costhetastar;   //!
   TBranch        *b_cos_photon_pair_helicity0;   //!
   TBranch        *b_cos_photon_pair_helicity1;   //!

   ReadTree(TTree *tree=0);
   virtual ~ReadTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ReadTree_cxx
ReadTree::ReadTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("data_cosThetaStar.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("data_cosThetaStar.root");
      }
      f->GetObject("output_tree",tree);

   }
   Init(tree);
}

ReadTree::~ReadTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ReadTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ReadTree::LoadTree(Long64_t entry)
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

void ReadTree::Init(TTree *tree)
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

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("ls", &ls, &b_ls);
   fChain->SetBranchAddress("evtnb", &evtnb, &b_evtnb);
   fChain->SetBranchAddress("nPho", &nPho, &b_nPho);
   fChain->SetBranchAddress("phoEt_1", &phoEt_1, &b_phoEt_1);
   fChain->SetBranchAddress("phoEta_1", &phoEta_1, &b_phoEta_1);
   fChain->SetBranchAddress("phoPhi_1", &phoPhi_1, &b_phoPhi_1);
   fChain->SetBranchAddress("phoSCEt_1", &phoSCEt_1, &b_phoSCEt_1);
   fChain->SetBranchAddress("phoSCEta_1", &phoSCEta_1, &b_phoSCEta_1);
   fChain->SetBranchAddress("phoSCPhi_1", &phoSCPhi_1, &b_phoSCPhi_1);
   fChain->SetBranchAddress("phoEtaWidth_1", &phoEtaWidth_1, &b_phoEtaWidth_1);
   fChain->SetBranchAddress("phoHoverE_1", &phoHoverE_1, &b_phoHoverE_1);
   fChain->SetBranchAddress("phoEnergyTop_1", &phoEnergyTop_1, &b_phoEnergyTop_1);
   fChain->SetBranchAddress("phoEnergyBottom_1", &phoEnergyBottom_1, &b_phoEnergyBottom_1);
   fChain->SetBranchAddress("phoEnergyLeft_1", &phoEnergyLeft_1, &b_phoEnergyLeft_1);
   fChain->SetBranchAddress("phoEnergyRight_1", &phoEnergyRight_1, &b_phoEnergyRight_1);
   fChain->SetBranchAddress("phoEnergyCrysMax_1", &phoEnergyCrysMax_1, &b_phoEnergyCrysMax_1);
   fChain->SetBranchAddress("phoSwissCross_1", &phoSwissCross_1, &b_phoSwissCross_1);
   fChain->SetBranchAddress("phoSeedTime_1", &phoSeedTime_1, &b_phoSeedTime_1);
   fChain->SetBranchAddress("phoSigmaIEta_1", &phoSigmaIEta_1, &b_phoSigmaIEta_1);
   fChain->SetBranchAddress("phoEt_2", &phoEt_2, &b_phoEt_2);
   fChain->SetBranchAddress("phoEta_2", &phoEta_2, &b_phoEta_2);
   fChain->SetBranchAddress("phoPhi_2", &phoPhi_2, &b_phoPhi_2);
   fChain->SetBranchAddress("phoSCEt_2", &phoSCEt_2, &b_phoSCEt_2);
   fChain->SetBranchAddress("phoSCEta_2", &phoSCEta_2, &b_phoSCEta_2);
   fChain->SetBranchAddress("phoSCPhi_2", &phoSCPhi_2, &b_phoSCPhi_2);
   fChain->SetBranchAddress("phoEtaWidth_2", &phoEtaWidth_2, &b_phoEtaWidth_2);
   fChain->SetBranchAddress("phoHoverE_2", &phoHoverE_2, &b_phoHoverE_2);
   fChain->SetBranchAddress("phoEnergyTop_2", &phoEnergyTop_2, &b_phoEnergyTop_2);
   fChain->SetBranchAddress("phoEnergyBottom_2", &phoEnergyBottom_2, &b_phoEnergyBottom_2);
   fChain->SetBranchAddress("phoEnergyLeft_2", &phoEnergyLeft_2, &b_phoEnergyLeft_2);
   fChain->SetBranchAddress("phoEnergyRight_2", &phoEnergyRight_2, &b_phoEnergyRight_2);
   fChain->SetBranchAddress("phoEnergyCrysMax_2", &phoEnergyCrysMax_2, &b_phoEnergyCrysMax_2);
   fChain->SetBranchAddress("phoSwissCross_2", &phoSwissCross_2, &b_phoSwissCross_2);
   fChain->SetBranchAddress("phoSeedTime_2", &phoSeedTime_2, &b_phoSeedTime_2);
   fChain->SetBranchAddress("phoSigmaIEta_2", &phoSigmaIEta_2, &b_phoSigmaIEta_2);
   fChain->SetBranchAddress("vSum_M", &vSum_M, &b_vSum_diPho_M);
   fChain->SetBranchAddress("vSum_Energy", &vSum_Energy, &b_vSum_diPho_Energy);
   fChain->SetBranchAddress("vSum_Pt", &vSum_Pt, &b_vSum_diPho_Pt);
   fChain->SetBranchAddress("vSum_Eta", &vSum_Eta, &b_vSum_diPho_Eta);
   fChain->SetBranchAddress("vSum_Phi", &vSum_Phi, &b_vSum_diPho_Phi);
   fChain->SetBranchAddress("vSum_Rapidity", &vSum_Rapidity, &b_vSum_diPho_Rapidity);
   fChain->SetBranchAddress("pho_dpt", &pho_dpt, &b_pho_dpt);
   fChain->SetBranchAddress("pho_deta", &pho_deta, &b_pho_deta);
   fChain->SetBranchAddress("pho_dphi", &pho_dphi, &b_pho_dphi);
   fChain->SetBranchAddress("pho_acop", &pho_acop, &b_pho_acop);
   fChain->SetBranchAddress("ok_neuexcl", &ok_neuexcl, &b_ok_neuexcl);
   fChain->SetBranchAddress("zdc_energy_pos", &zdc_energy_pos, &b_zdc_energy_pos);
   fChain->SetBranchAddress("zdc_energy_neg", &zdc_energy_neg, &b_zdc_energy_neg);
   fChain->SetBranchAddress("ok_zdcexcl_1n_pos", &ok_zdcexcl_1n_pos, &b_ok_zdcexcl_1n_pos);
   fChain->SetBranchAddress("ok_zdcexcl_1n_neg", &ok_zdcexcl_1n_neg, &b_ok_zdcexcl_1n_neg);
   fChain->SetBranchAddress("ok_zdcexcl_3n_pos", &ok_zdcexcl_3n_pos, &b_ok_zdcexcl_3n_pos);
   fChain->SetBranchAddress("ok_zdcexcl_3n_neg", &ok_zdcexcl_3n_neg, &b_ok_zdcexcl_3n_neg);
   fChain->SetBranchAddress("ok_zdcexcl_4n_pos", &ok_zdcexcl_4n_pos, &b_ok_zdcexcl_4n_pos);
   fChain->SetBranchAddress("ok_zdcexcl_4n_neg", &ok_zdcexcl_4n_neg, &b_ok_zdcexcl_4n_neg);
   fChain->SetBranchAddress("ok_zdcexcl_5n_pos", &ok_zdcexcl_5n_pos, &b_ok_zdcexcl_5n_pos);
   fChain->SetBranchAddress("ok_zdcexcl_5n_neg", &ok_zdcexcl_5n_neg, &b_ok_zdcexcl_5n_neg);
   fChain->SetBranchAddress("ok_zdcexcl", &ok_zdcexcl, &b_ok_zdcexcl);
   fChain->SetBranchAddress("ok_castorexcl", &ok_castorexcl, &b_ok_castorexcl);
   fChain->SetBranchAddress("ok_chexcl", &ok_chexcl, &b_ok_chexcl);
   fChain->SetBranchAddress("ok_chexcl_tracks", &ok_chexcl_tracks, &b_ok_chexcl_tracks);
   fChain->SetBranchAddress("ok_chexcl_electrons", &ok_chexcl_electrons, &b_ok_chexcl_electrons);
   fChain->SetBranchAddress("ok_chexcl_muons", &ok_chexcl_muons, &b_ok_chexcl_muons);
   fChain->SetBranchAddress("ok_chexcl_goodtracks", &ok_chexcl_goodtracks, &b_ok_chexcl_goodtracks);
   fChain->SetBranchAddress("ok_chexcl_goodelectrons", &ok_chexcl_goodelectrons, &b_ok_chexcl_goodelectrons);
   fChain->SetBranchAddress("SFweight_reco", SFweight_reco, &b_SFweight_reco);
   fChain->SetBranchAddress("SFweight_trig", SFweight_trig, &b_SFweight_trig);
   fChain->SetBranchAddress("nPixelCluster", &nPixelCluster, &b_nPixelCluster);
   fChain->SetBranchAddress("nPixelRecHits", &nPixelRecHits, &b_nPixelRecHits);
   fChain->SetBranchAddress("nTracks", &nTracks, &b_nTracks);
   fChain->SetBranchAddress("costhetastar", &costhetastar, &b_costhetastar);
   fChain->SetBranchAddress("cos_photon_pair_helicity0", &cos_photon_pair_helicity0, &b_cos_photon_pair_helicity0);
   fChain->SetBranchAddress("cos_photon_pair_helicity1", &cos_photon_pair_helicity1, &b_cos_photon_pair_helicity1);
   Notify();
}

Bool_t ReadTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ReadTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ReadTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ReadTree_cxx
