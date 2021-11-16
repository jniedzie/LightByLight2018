#include <iostream>
#include <fstream>
#include <sstream>
#include <TFile.h>
#include <TDirectory.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TROOT.h>
#include "CMS_lumi.C"
#include "TStyle.h"
#include "TPaveStats.h"
#include "TText.h"
#include "TCut.h"
#include "TChain.h"
#include "THStack.h"

int xlo = 1;
int xhi = 4;
int nbin = 8;




const char *dir = "figures";

#define PI 3.141592653589

void make_hist(TH1D *&, Color_t , int );

const double luminosity       = 1635.123139823; // μb^-1
const double nEventsGeneratedSL = 63957000; // older number with less files 63398400; //starlight
const double xsecGeneratedSL    = 7920; // μb, starlight

const double nEventsGeneratedSC = 67536400; // older number with less files 67262800 superchic 
const double xsecGeneratedSC    = 8827.220; // μb
const double purity = 0.96; 
double scaleFactorsSC = 0.84 *  // NEE
                        0.96 *      // CHE
                        pow(0.98, 2)* // electron reco+ID
                        0.83 *      // HF veto
                        0.99;       // L1 EG trigger

double scaleFactorsSL = 0.84 *  // NEE
                        0.96 *      // CHE
                        pow(0.99, 2)* // electron reco+ID
                        0.83 *      // HF veto
                        0.99;       // L1 EG trigger

double lumiNormSC = xsecGeneratedSC*luminosity*purity*scaleFactorsSC/nEventsGeneratedSC;
double lumiNormSL = xsecGeneratedSL*luminosity*purity*scaleFactorsSL/nEventsGeneratedSL;


const double xsecGeneratedLbL    = 2.59; // μb
const double nEventsGeneratedLbL = 466000; 
double norm_exgg = xsecGeneratedLbL*luminosity/nEventsGeneratedLbL; 


const double xsecGeneratedCEP    = 0.0058; // μb
const double nEventsGeneratedCEP = 668000; 
double norm_cep  = xsecGeneratedCEP*luminosity/nEventsGeneratedCEP; 

void plot_background(){
 
  //gROOT->LoadMacro("CMS_lumi.C");
  bool outOfFrame    = false;
  TH1::SetDefaultSumw2();
   gStyle->SetOptStat(0);



  TFile *outf= new TFile("histos.root","recreate");  

  TChain *data = new TChain("output_tree");
  data->Add("/eos/cms/store/group/phys_heavyions/osuranyi/lbyl_2018/diphoton/diphoton_data9.root");

  cout << "norm Exgg " << norm_exgg << endl;

 // const TCut excl = " ngenTrk==0 && nEle==0 ";


 // const TCut calocut = "leadingEmEnergy_EB< 0.55 && leadingEmEnergy_EE < 3.16 && leadingHadEnergy_HB < 2.0 && leadingHadEnergy_HE < 3.0 && leadingHadEnergy_HF_Plus < 4.85 && leadingHadEnergy_HF_Minus < 4.12 ";

   const TCut no_addittional_tower  = " ok_neuexcl==1 ";
   const TCut no_trk  = "ok_chexcl_goodtracks == 1"; //&& ok_chexcl_muons == 1"; //" ok_chexcl==1";
   const TCut apply_cut =  "vSum_M > 5 && vSum_Pt<2 && pho_acop<0.01" && no_trk && no_addittional_tower;
   //const TCut apply_cut =  "vSum_M > 5 && vSum_Pt<1" && no_trk && no_addittional_tower;

  const TCut aco_cut   = "vSum_M > 5 && vSum_Pt<2" && no_trk && no_addittional_tower;



  float  phoEtaWidth_1;
  float  phoHoverE_1;
  float  phoEnergyTop_1;
  float  phoEnergyBottom_1;
  float  phoEnergyLeft_1;
  float  phoEnergyRight_1;
  float  phoEnergyCrysMax_1;
  float  phoSwissCross_1;
  float  phoSeedTime_1;
  float  phoSigmaIEta_1;

  float  phoEtaWidth_2;
  float  phoHoverE_2;
  float  phoEnergyTop_2;
  float  phoEnergyBottom_2;
  float  phoEnergyLeft_2;
  float  phoEnergyRight_2;
  float  phoEnergyCrysMax_2;
  float  phoSwissCross_2;
  float  phoSeedTime_2;
  float  phoSigmaIEta_2;

  float vSum_diPho_M;
  float vSum_diPho_Energy;
  float vSum_diPho_Pt;
  float vSum_diPho_Eta;
  float vSum_diPho_Phi;
  float vSum_diPho_Rapidity;
  float pho_dpt;
  float pho_deta;
  float pho_dphi;
  float pho_acop;

  int ok_neuexcl;
  int ok_zdcexcl;
  int ok_chexcl;
  int ok_chexcl_tracks;
  int ok_chexcl_electrons;
  int ok_chexcl_muons;
  int ok_chexcl_goodtracks;
  int ok_chexcl_goodelectrons;

/*   data->SetBranchAddress("phoEt_1",             &phoEt_1);
  data->SetBranchAddress("phoEta_1",            &phoEta_1);
  data->SetBranchAddress("phoPhi_1",            &phoPhi_1);
  data->SetBranchAddress("phoSCEt_1",           &phoSCEt_1);
  data->SetBranchAddress("phoSCEta_1",          &phoSCEta_1);
  data->SetBranchAddress("phoSCPhi_1",          &phoSCPhi_1);*/
  data->SetBranchAddress("phoEtaWidth_1",       &phoEtaWidth_1);
  data->SetBranchAddress("phoHoverE_1",         &phoHoverE_1);
  data->SetBranchAddress("phoSwissCross_1",     &phoSwissCross_1);
  data->SetBranchAddress("phoSeedTime_1",       &phoSeedTime_1);
  data->SetBranchAddress("phoSigmaIEta_1",      &phoSigmaIEta_1);


 
/*  data->SetBranchAddress("phoEt_2",             &phoEt_2,       "phoEt_2/F");
  data->SetBranchAddress("phoEta_2",            &phoEta_2,      "phoEta_2/F");
  data->SetBranchAddress("phoPhi_2",            &phoPhi_2,      "phoPhi_2/F");
  data->SetBranchAddress("phoSCEt_2",           &phoSCEt_2,     "phoSCEt_2/F");
  data->SetBranchAddress("phoSCEta_2",          &phoSCEta_2,    "phoSCEta_2/F");
  data->SetBranchAddress("phoSCPhi_2",          &phoSCPhi_2,    "phoSCPhi_2/F");*/
  data->SetBranchAddress("phoEtaWidth_2",       &phoEtaWidth_2);
  data->SetBranchAddress("phoHoverE_2",         &phoHoverE_2);
  data->SetBranchAddress("phoSwissCross_2",     &phoSwissCross_2);
  data->SetBranchAddress("phoSeedTime_2",       &phoSeedTime_2);
  data->SetBranchAddress("phoSigmaIEta_2",      &phoSigmaIEta_2);
  
  data->SetBranchAddress("vSum_M",              &vSum_diPho_M);
  data->SetBranchAddress("vSum_Energy",         &vSum_diPho_Energy);
  data->SetBranchAddress("vSum_Pt",             &vSum_diPho_Pt);
  data->SetBranchAddress("vSum_Eta",            &vSum_diPho_Eta);
  data->SetBranchAddress("vSum_Phi",            &vSum_diPho_Phi);
  data->SetBranchAddress("vSum_Rapidity",       &vSum_diPho_Rapidity);
  data->SetBranchAddress("pho_dpt",             &pho_dpt);
  data->SetBranchAddress("pho_deta",            &pho_deta);
  data->SetBranchAddress("pho_dphi",            &pho_dphi);
  data->SetBranchAddress("pho_acop",            &pho_acop);
 
  data->SetBranchAddress("ok_neuexcl",          &ok_neuexcl);
  data->SetBranchAddress("ok_zdcexcl",          &ok_zdcexcl);
  data->SetBranchAddress("ok_chexcl",           &ok_chexcl);
  data->SetBranchAddress("ok_chexcl_tracks",           &ok_chexcl_tracks);
  data->SetBranchAddress("ok_chexcl_electrons",           &ok_chexcl_electrons);
  data->SetBranchAddress("ok_chexcl_muons",           &ok_chexcl_muons);
  data->SetBranchAddress("ok_chexcl_goodtracks",           &ok_chexcl_goodtracks);
  data->SetBranchAddress("ok_chexcl_goodelectrons",           &ok_chexcl_goodelectrons);

  TH1F* signal_EtaWidth = new TH1F("",";#eta width;Entries",50,0.0,0.025);
  TH1F* signal_HoverE = new TH1F("",";H/E;Entries",50,0.0,0.5);
  TH1F* signal_SwissCross = new TH1F("",";1-E4/E;Entries",50,0.0,1.05);
  TH1F* signal_SeedTime = new TH1F("",";Seed time;Entries",50,0.0,15.0);
  TH1F* signal_SigmaIEta = new TH1F("",";#sigma i#etai#eta;Entries",50,0.0,0.08);

  TH1F* background_EtaWidth = new TH1F("",";#eta width;Entries",50,0.0,0.025);
  TH1F* background_HoverE = new TH1F("",";H/E;Entries",50,0.0,0.5);
  TH1F* background_SwissCross = new TH1F("",";1-E4/E;Entries",50,0.0,1.05);
  TH1F* background_SeedTime = new TH1F("",";Seed time;Entries",50,0.0,15.0);
  TH1F* background_SigmaIEta = new TH1F("",";#sigma i#etai#eta;Entries",50,0.0,0.08);


  for(int i = 0; i < data->GetEntriesFast(); i++){
    data->GetEntry(i);

    if(ok_neuexcl && ok_chexcl_goodtracks && vSum_diPho_M > 5.0 && vSum_diPho_Pt < 1.0){
      if(pho_acop < 0.01){
        signal_EtaWidth->Fill(phoEtaWidth_1);
        signal_EtaWidth->Fill(phoEtaWidth_2);

        signal_HoverE->Fill(phoHoverE_1);
        signal_HoverE->Fill(phoHoverE_2);

        signal_SwissCross->Fill(phoSwissCross_1);
        signal_SwissCross->Fill(phoSwissCross_2);

        signal_SeedTime->Fill(phoSeedTime_1);
        signal_SeedTime->Fill(phoSeedTime_2);

        signal_SigmaIEta->Fill(phoSigmaIEta_1);
        signal_SigmaIEta->Fill(phoSigmaIEta_2);
      }
      else if(pho_acop > 0.01){
        background_EtaWidth->Fill(phoEtaWidth_1);
        background_EtaWidth->Fill(phoEtaWidth_2);

        background_HoverE->Fill(phoHoverE_1);
        background_HoverE->Fill(phoHoverE_2);

        background_SwissCross->Fill(phoSwissCross_1);
        background_SwissCross->Fill(phoSwissCross_2);

        background_SeedTime->Fill(phoSeedTime_1);
        background_SeedTime->Fill(phoSeedTime_2);

        background_SigmaIEta->Fill(phoSigmaIEta_1);
        background_SigmaIEta->Fill(phoSigmaIEta_2);
      }


    }

  }

  TCanvas* c1 = new TCanvas();

  signal_EtaWidth->Scale(1.0/signal_EtaWidth->Integral());
  signal_HoverE->Scale(1.0/signal_HoverE->Integral());
  signal_SwissCross->Scale(1.0/signal_SwissCross->Integral());
  signal_SeedTime->Scale(1.0/signal_SeedTime->Integral());
  signal_SigmaIEta->Scale(1.0/signal_SigmaIEta->Integral());

  background_EtaWidth->Scale(1.0/background_EtaWidth->Integral());
  background_HoverE->Scale(1.0/background_HoverE->Integral());
  background_SwissCross->Scale(1.0/background_SwissCross->Integral());
  background_SeedTime->Scale(1.0/background_SeedTime->Integral());
  background_SigmaIEta->Scale(1.0/background_SigmaIEta->Integral());

  signal_EtaWidth->SetLineColor(2);
  signal_HoverE->SetLineColor(2);
  signal_SwissCross->SetLineColor(2);
  signal_SeedTime->SetLineColor(2);
  signal_SigmaIEta->SetLineColor(2);

  background_EtaWidth->Draw("hist e");
  signal_EtaWidth->Draw("hist e same");
  c1->SaveAs("figures/photonID/EtaWidth.png");

  background_HoverE->Draw("hist e");
  signal_HoverE->Draw("hist e same");
  c1->SaveAs("figures/photonID/HoverE.png");

  background_SwissCross->Draw("hist e");
  signal_SwissCross->Draw("hist e same");
  c1->SaveAs("figures/photonID/SwissCross.png");

  background_SeedTime->Draw("hist e");
  signal_SeedTime->Draw("hist e same");
  c1->SaveAs("figures/photonID/SeedTime.png");

  background_SigmaIEta->Draw("hist e");
  signal_SigmaIEta->Draw("hist e same");
  c1->SaveAs("figures/photonID/SigmaIEta.png");

}

void make_hist(TH1D *& hist, Color_t kcolor, int kstyle){
  // For the axis labels:
  hist->SetLabelColor(1, "XYZ");
  hist->SetLabelFont(42, "XYZ");
  hist->SetLabelOffset(0.007, "XYZ");
  hist->SetLabelSize(0.05, "XYZ");
 
  hist->SetMarkerColor(kcolor);
  hist->SetMarkerSize(1.5);
  hist->SetFillColor(kcolor);
  hist->SetMarkerStyle(kstyle);
  
  //hist->SetTitle("");
}

