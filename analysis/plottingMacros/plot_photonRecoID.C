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

void plot_photonRecoID(){
 
  //gROOT->LoadMacro("CMS_lumi.C");
  bool outOfFrame    = false;
  TH1::SetDefaultSumw2();
   gStyle->SetOptStat(0);

  //TFile *outf= new TFile("histos.root","recreate");  

  TChain *data = new TChain("tnpQED/fitter_tree");
  data->Add("/afs/cern.ch/user/o/osuranyi/eos/lbyl_2018/efficienciesQED/efficiencies_data.root");
  TChain *qed = new TChain("tnpQED/fitter_tree");
  qed->Add("/afs/cern.ch/user/o/osuranyi/eos/lbyl_2018/efficienciesQED/efficiencies_qed.root");


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
  float phoEtBarrel_notag;
  float phoEtEndcap_notag;
  float phoEta_notag;
  float phoPhi_notag;
  float phoAco_notag;
  float phoSCEt_notag;
  float phoSCEtBarrel_notag;
  float phoSCEtEndcap_notag;
  float phoSCEta_notag;
  float phoSCPhi_notag;
  float phoSCAco_notag;

  int ok_probeTrk;
  int nprobeTrk;
  float probetkPt, probetkEta, probetkPhi, probeTkMinDphi, probetkAco; int probetkCharge; float probetkMinDpt, probetkMinDet;
  float probetkvx; float probetkvy; float probetkvz; float probetkd0; float probetkdxy; float probetkdz; float probetkdxyError; 
  float probetkdzError; int probetkValidHits; int probetkMissHits;  float diffPt_probetkEleGamma, diffEt_probetkEleGamma;
  float diffSCPt_probetkEleGamma, diffSCEt_probetkEleGamma;

  // qed variables
  int qed_run;
  int qed_ls;
  int qed_evtnb;
  float qed_swissCross;
  float qed_etaWidth;
  float qed_HoE;
  int qed_ok_photon;
  int qed_ok_ID;
  int qed_ok_etaWidth;
  int qed_ok_swissCross;
  int qed_ok_HoE;
  int qed_tag_charge;
  int qed_nTag;
  float qed_tag_Et;
  float qed_tag_SCEt;
  float qed_tag_SCEta;
  float qed_tag_SCPhi;
  float qed_tag_pt;
  float qed_tag_eta;
  float qed_tag_phi;
  int qed_pass_EG3;
  int qed_pass_EG5;
  float qed_tag_L1Et_passEG3;
  float qed_tag_L1Eta_passEG3;
  float qed_tag_L1Et_passEG5;
  float qed_tag_L1Eta_passEG5;
  int qed_nPho_notag;
  float qed_phoEt_notag;
  float qed_phoEtBarrel_notag;
  float qed_phoEtEndcap_notag;
  float qed_phoEta_notag;
  float qed_phoPhi_notag;
  float qed_phoAco_notag;
  float qed_phoSCEt_notag;
  float qed_phoSCEtBarrel_notag;
  float qed_phoSCEtEndcap_notag;
  float qed_phoSCEta_notag;
  float qed_phoSCPhi_notag;
  float qed_phoSCAco_notag;

  int qed_ok_probeTrk;
  int qed_nprobeTrk;
  float qed_probetkPt, qed_probetkEta, qed_probetkPhi, qed_probeTkMinDphi, qed_probetkAco; int qed_probetkCharge; float qed_probetkMinDpt, qed_probetkMinDet;
  float qed_probetkvx; float qed_probetkvy; float qed_probetkvz; float qed_probetkd0; float qed_probetkdxy; float qed_probetkdz; float qed_probetkdxyError; 
  float qed_probetkdzError; int qed_probetkValidHits; int qed_probetkMissHits;  float qed_diffPt_probetkEleGamma, qed_diffEt_probetkEleGamma;
  float qed_diffSCPt_probetkEleGamma, qed_diffSCEt_probetkEleGamma;





  data->SetBranchAddress("run",&run);
  data->SetBranchAddress("ls",&ls);
  data->SetBranchAddress("evtnb",&evtnb);
  data->SetBranchAddress("nTag",   &nTag);
  data->SetBranchAddress("tag_charge",&tag_charge);
  data->SetBranchAddress("tag_Et",&tag_Et);
  data->SetBranchAddress("tag_SCEt",&tag_SCEt);
  data->SetBranchAddress("tag_SCEta",&tag_SCEta);
  data->SetBranchAddress("tag_SCPhi",&tag_SCPhi);
  data->SetBranchAddress("tag_pt",&tag_pt);
  data->SetBranchAddress("tag_eta",&tag_eta);
  data->SetBranchAddress("tag_phi",&tag_phi);
  data->SetBranchAddress("pass_EG3",&pass_EG3);
  data->SetBranchAddress("pass_EG5",&pass_EG5);
  data->SetBranchAddress("tag_L1Et_passEG3",&tag_L1Et_passEG3);
  data->SetBranchAddress("tag_L1Eta_passEG3",&tag_L1Eta_passEG3);
  data->SetBranchAddress("tag_L1Et_passEG5",&tag_L1Et_passEG5);
  data->SetBranchAddress("tag_L1Eta_passEG5",&tag_L1Eta_passEG5);
  data->SetBranchAddress("swissCross",&swissCross);
  data->SetBranchAddress("etaWidth",&etaWidth);
  data->SetBranchAddress("HoE",&HoE);
  data->SetBranchAddress("ok_photon",&ok_photon);
  data->SetBranchAddress("ok_ID",&ok_ID);
  data->SetBranchAddress("ok_etaWidth",&ok_etaWidth);
  data->SetBranchAddress("ok_swissCross",&ok_swissCross);
  data->SetBranchAddress("ok_HoE",&ok_HoE);
  data->SetBranchAddress("nPho_notag",   &nPho_notag);
  data->SetBranchAddress("phoEt_notag",&phoEt_notag);
  data->SetBranchAddress("phoEta_notag",&phoEta_notag);
  data->SetBranchAddress("phoPhi_notag",&phoPhi_notag);
  data->SetBranchAddress("phoAco_notag",&phoAco_notag);
  data->SetBranchAddress("phoSCEt_notag",&phoSCEt_notag);
  data->SetBranchAddress("phoSCEtBarrel_notag",&phoSCEtBarrel_notag);
  data->SetBranchAddress("phoSCEtEndcap_notag",&phoSCEtEndcap_notag);
  data->SetBranchAddress("phoSCEta_notag",&phoSCEta_notag);
  data->SetBranchAddress("phoSCPhi_notag",&phoSCPhi_notag);
  data->SetBranchAddress("phoSCAco_notag",&phoSCAco_notag);
  data->SetBranchAddress("ok_probeTrk",&ok_probeTrk);
  data->SetBranchAddress("nprobeTrk",   &nprobeTrk);
  data->SetBranchAddress("probetkCharge",&probetkCharge);
  data->SetBranchAddress("probetkPt",&probetkPt);
  data->SetBranchAddress("probetkEta",&probetkEta);
  data->SetBranchAddress("probetkPhi",&probetkPhi);
  data->SetBranchAddress("probetkMinDpt",&probetkMinDpt);
  data->SetBranchAddress("probetkMinDet",&probetkMinDet);
  data->SetBranchAddress("diffPt_probetkEleGamma",&diffPt_probetkEleGamma);
  data->SetBranchAddress("diffEt_probetkEleGamma",&diffEt_probetkEleGamma);

  data->SetBranchAddress("diffSCPt_probetkEleGamma",&diffSCPt_probetkEleGamma);
  data->SetBranchAddress("diffSCEt_probetkEleGamma",&diffSCEt_probetkEleGamma);

  data->SetBranchAddress("probetkAco",&probetkAco);
  data->SetBranchAddress("probetkvx",&probetkvx);
  data->SetBranchAddress("probetkvy",&probetkvy);
  data->SetBranchAddress("probetkvz",&probetkvz);
  data->SetBranchAddress("probetkd0",&probetkd0);
  data->SetBranchAddress("probetkdxy",&probetkdxy);
  data->SetBranchAddress("probetkdz",&probetkdz);
  data->SetBranchAddress("probetkdxyError",&probetkdxyError);
  data->SetBranchAddress("probetkdzError",&probetkdzError);
  data->SetBranchAddress("probetkValidHits",&probetkValidHits);
  data->SetBranchAddress("probetkMissHits",&probetkMissHits);

  // qed branch addresses

  qed->SetBranchAddress("run",&qed_run);
  qed->SetBranchAddress("ls",&qed_ls);
  qed->SetBranchAddress("evtnb",&qed_evtnb);
  qed->SetBranchAddress("nTag",   &qed_nTag);
  qed->SetBranchAddress("tag_charge",&qed_tag_charge);
  qed->SetBranchAddress("tag_Et",&qed_tag_Et);
  qed->SetBranchAddress("tag_SCEt",&qed_tag_SCEt);
  qed->SetBranchAddress("tag_SCEta",&qed_tag_SCEta);
  qed->SetBranchAddress("tag_SCPhi",&qed_tag_SCPhi);
  qed->SetBranchAddress("tag_pt",&qed_tag_pt);
  qed->SetBranchAddress("tag_eta",&qed_tag_eta);
  qed->SetBranchAddress("tag_phi",&qed_tag_phi);
  qed->SetBranchAddress("pass_EG3",&qed_pass_EG3);
  qed->SetBranchAddress("pass_EG5",&qed_pass_EG5);
  qed->SetBranchAddress("tag_L1Et_passEG3",&qed_tag_L1Et_passEG3);
  qed->SetBranchAddress("tag_L1Eta_passEG3",&qed_tag_L1Eta_passEG3);
  qed->SetBranchAddress("tag_L1Et_passEG5",&qed_tag_L1Et_passEG5);
  qed->SetBranchAddress("tag_L1Eta_passEG5",&qed_tag_L1Eta_passEG5);
  qed->SetBranchAddress("swissCross",&qed_swissCross);
  qed->SetBranchAddress("etaWidth",&qed_etaWidth);
  qed->SetBranchAddress("HoE",&qed_HoE);
  qed->SetBranchAddress("ok_photon",&qed_ok_photon);
  qed->SetBranchAddress("ok_ID",&qed_ok_ID);
  qed->SetBranchAddress("ok_etaWidth",&qed_ok_etaWidth);
  qed->SetBranchAddress("ok_swissCross",&qed_ok_swissCross);
  qed->SetBranchAddress("ok_HoE",&qed_ok_HoE);
  qed->SetBranchAddress("nPho_notag",   &qed_nPho_notag);
  qed->SetBranchAddress("phoEt_notag",&qed_phoEt_notag);
  qed->SetBranchAddress("phoEta_notag",&qed_phoEta_notag);
  qed->SetBranchAddress("phoPhi_notag",&qed_phoPhi_notag);
  qed->SetBranchAddress("phoAco_notag",&qed_phoAco_notag);
  qed->SetBranchAddress("phoSCEt_notag",&qed_phoSCEt_notag);
  qed->SetBranchAddress("phoSCEtBarrel_notag",&qed_phoSCEtBarrel_notag);
  qed->SetBranchAddress("phoSCEtEndcap_notag",&qed_phoSCEtEndcap_notag);
  qed->SetBranchAddress("phoSCEta_notag",&qed_phoSCEta_notag);
  qed->SetBranchAddress("phoSCPhi_notag",&qed_phoSCPhi_notag);
  qed->SetBranchAddress("phoSCAco_notag",&qed_phoSCAco_notag);
  qed->SetBranchAddress("ok_probeTrk",&qed_ok_probeTrk);
  qed->SetBranchAddress("nprobeTrk",   &qed_nprobeTrk);
  qed->SetBranchAddress("probetkCharge",&qed_probetkCharge);
  qed->SetBranchAddress("probetkPt",&qed_probetkPt);
  qed->SetBranchAddress("probetkEta",&qed_probetkEta);
  qed->SetBranchAddress("probetkPhi",&qed_probetkPhi);
  qed->SetBranchAddress("probetkMinDpt",&qed_probetkMinDpt);
  qed->SetBranchAddress("probetkMinDet",&qed_probetkMinDet);
  qed->SetBranchAddress("diffPt_probetkEleGamma",&qed_diffPt_probetkEleGamma);
  qed->SetBranchAddress("diffEt_probetkEleGamma",&qed_diffEt_probetkEleGamma);

  qed->SetBranchAddress("diffSCPt_probetkEleGamma",&qed_diffSCPt_probetkEleGamma);
  qed->SetBranchAddress("diffSCEt_probetkEleGamma",&qed_diffSCEt_probetkEleGamma);

  qed->SetBranchAddress("probetkAco",&qed_probetkAco);
  qed->SetBranchAddress("probetkvx",&qed_probetkvx);
  qed->SetBranchAddress("probetkvy",&qed_probetkvy);
  qed->SetBranchAddress("probetkvz",&qed_probetkvz);
  qed->SetBranchAddress("probetkd0",&qed_probetkd0);
  qed->SetBranchAddress("probetkdxy",&qed_probetkdxy);
  qed->SetBranchAddress("probetkdz",&qed_probetkdz);
  qed->SetBranchAddress("probetkdxyError",&qed_probetkdxyError);
  qed->SetBranchAddress("probetkdzError",&qed_probetkdzError);
  qed->SetBranchAddress("probetkValidHits",&qed_probetkValidHits);
  qed->SetBranchAddress("probetkMissHits",&qed_probetkMissHits);



  // Create histograms
  double bins[6] = {0.0,2.0, 4.0, 6.0, 8.0, 20.0};
  TH1F* numerator_barrel_pT = new TH1F("",";p_{T}^{e} - p_{T}^{tk} ~ E_{T}^{#gamma};Numerator",5,bins);
  TH1F* denominator_barrel_pT = new TH1F("",";p_{T}^{e} - p_{T}^{tk} ~ E_{T}^{#gamma};Denominator",5,bins);
  TH1F* efficiency_barrel_pT = new TH1F("",";p_{T}^{e} - p_{T}^{tk} ~ E_{T}^{#gamma};Efficiency",5,bins);

  //
  TH1F* numerator_endcap_pT = new TH1F("",";p_{T}^{e} - p_{T}^{tk} ~ E_{T}^{#gamma};Numerator",5,bins);
  TH1F* denominator_endcap_pT = new TH1F("",";p_{T}^{e} - p_{T}^{tk} ~ E_{T}^{#gamma};Denominator",5,bins);
  TH1F* efficiency_endcap_pT = new TH1F("",";p_{T}^{e} - p_{T}^{tk} ~ E_{T}^{#gamma};Efficiency",5,bins);

  //
  TH1F* numerator_eta = new TH1F("",";#eta^{e};Numerator",10,0,2.4);
  TH1F* denominator_eta = new TH1F("",";#eta^{e};Denominator",10,0,2.4);
  TH1F* efficiency_eta = new TH1F("",";#eta^{e};Efficiency",10,0,2.4);

  // qed histograms
  TH1F* qed_numerator_barrel_pT = new TH1F("",";p_{T}^{e} - p_{T}^{tk} ~ E_{T}^{#gamma};Numerator",5,bins);
  TH1F* qed_denominator_barrel_pT = new TH1F("",";p_{T}^{e} - p_{T}^{tk} ~ E_{T}^{#gamma};Denominator",5,bins);
  TH1F* qed_efficiency_barrel_pT = new TH1F("",";p_{T}^{e} - p_{T}^{tk} ~ E_{T}^{#gamma};Efficiency",5,bins);

  //
  TH1F* qed_numerator_endcap_pT = new TH1F("",";p_{T}^{e} - p_{T}^{tk} ~ E_{T}^{#gamma};Numerator",5,bins);
  TH1F* qed_denominator_endcap_pT = new TH1F("",";p_{T}^{e} - p_{T}^{tk} ~ E_{T}^{#gamma};Denominator",5,bins);
  TH1F* qed_efficiency_endcap_pT = new TH1F("",";p_{T}^{e} - p_{T}^{tk} ~ E_{T}^{#gamma};Efficiency",5,bins);

  //
  TH1F* qed_numerator_eta = new TH1F("",";#eta^{e};Numerator",10,0,2.4);
  TH1F* qed_denominator_eta = new TH1F("",";#eta^{e};Denominator",10,0,2.4);
  TH1F* qed_efficiency_eta = new TH1F("",";#eta^{e};Efficiency",10,0,2.4);

  // Loop over data events
  for(int i = 0; i < data->GetEntriesFast(); i++){
    data->GetEntry(i);

    if(pass_EG5 && probetkAco < 0.2 && ok_probeTrk && nPho_notag == 1){
      if(fabs(probetkEta) < 1.5){
        denominator_barrel_pT->Fill(probetkMinDpt);
        denominator_eta->Fill(fabs(probetkEta));
        if(ok_photon == 1 && ok_etaWidth == 1 && ok_HoE == 1){
          numerator_barrel_pT->Fill(probetkMinDpt);
          numerator_eta->Fill(fabs(probetkEta));
        }
      }
      else if(fabs(probetkEta) > 1.5){
        denominator_endcap_pT->Fill(probetkMinDpt);
        denominator_eta->Fill(fabs(probetkEta));
        if(ok_photon == 1 && ok_etaWidth == 1 && ok_HoE == 1){
          numerator_endcap_pT->Fill(probetkMinDpt);
          numerator_eta->Fill(fabs(probetkEta));
        }
      }
    }
  }

  // Loop over qed events
  for(int i = 0; i < qed->GetEntriesFast(); i++){
    qed->GetEntry(i);

    if(qed_pass_EG5 && qed_probetkAco < 0.2 && qed_ok_probeTrk && qed_nPho_notag == 1){
      
      if(fabs(qed_probetkEta) < 1.5){
        qed_denominator_barrel_pT->Fill(qed_probetkMinDpt);
        qed_denominator_eta->Fill(qed_probetkEta);

        if(qed_ok_photon == 1 && qed_ok_etaWidth == 1 && qed_ok_HoE == 1){
          qed_numerator_barrel_pT->Fill(qed_probetkMinDpt);
          qed_numerator_eta->Fill(qed_probetkEta);      
        }
      }
      else if(fabs(qed_probetkEta) > 1.5){
        qed_denominator_endcap_pT->Fill(qed_probetkMinDpt);
        qed_denominator_eta->Fill(qed_probetkEta);

        if(qed_ok_photon == 1 && qed_ok_etaWidth == 1 && qed_ok_HoE == 1){
          qed_numerator_endcap_pT->Fill(qed_probetkMinDpt);
          qed_numerator_eta->Fill(qed_probetkEta);
        }
      }
    }
  }


  TCanvas* c1 = new TCanvas();

  efficiency_barrel_pT->Divide(numerator_barrel_pT, denominator_barrel_pT, 1, 1, "B");
  efficiency_barrel_pT->SetMarkerColor(1);
  efficiency_barrel_pT->SetMarkerStyle(20);
  efficiency_barrel_pT->SetMarkerSize(1);
  efficiency_barrel_pT->SetLineColor(1);
  efficiency_barrel_pT->GetYaxis()->SetRangeUser(0.0,1.0);
  efficiency_barrel_pT->Draw("p e");

  qed_efficiency_barrel_pT->Divide(qed_numerator_barrel_pT, qed_denominator_barrel_pT, 1, 1, "B");
  qed_efficiency_barrel_pT->SetMarkerColor(2);
  qed_efficiency_barrel_pT->SetMarkerStyle(20);
  qed_efficiency_barrel_pT->SetMarkerSize(1);
  qed_efficiency_barrel_pT->SetLineColor(2);
  qed_efficiency_barrel_pT->Draw("p e same");

  c1->SaveAs("figures/photonEfficiency/efficiency_barrel_pT.png");

  efficiency_endcap_pT->Divide(numerator_endcap_pT, denominator_endcap_pT, 1, 1, "B");
  efficiency_endcap_pT->SetMarkerColor(1);
  efficiency_endcap_pT->SetMarkerStyle(20);
  efficiency_endcap_pT->SetMarkerSize(1);
  efficiency_endcap_pT->SetLineColor(1);
  efficiency_endcap_pT->GetYaxis()->SetRangeUser(0.0,1.0);
  efficiency_endcap_pT->Draw("p e");

  qed_efficiency_endcap_pT->Divide(qed_numerator_endcap_pT, qed_denominator_endcap_pT, 1, 1, "B");
  qed_efficiency_endcap_pT->SetMarkerColor(2);
  qed_efficiency_endcap_pT->SetMarkerStyle(20);
  qed_efficiency_endcap_pT->SetMarkerSize(1);
  qed_efficiency_endcap_pT->SetLineColor(2);
  qed_efficiency_endcap_pT->Draw("p e same");

  c1->SaveAs("figures/photonEfficiency/efficiency_endcap_pT.png");

  efficiency_eta->Divide(numerator_eta, denominator_eta, 1, 1, "B");
  efficiency_eta->SetMarkerColor(1);
  efficiency_eta->SetMarkerStyle(20);
  efficiency_eta->SetMarkerSize(1);
  efficiency_eta->SetLineColor(1);
  efficiency_eta->GetYaxis()->SetRangeUser(0.0,1.0);
  efficiency_eta->Draw("p e");

  qed_efficiency_eta->Divide(qed_numerator_eta, qed_denominator_eta, 1, 1, "B");
  qed_efficiency_eta->SetMarkerColor(2);
  qed_efficiency_eta->SetMarkerStyle(20);
  qed_efficiency_eta->SetMarkerSize(1);
  qed_efficiency_eta->SetLineColor(2);
  qed_efficiency_eta->Draw("p e same");

  c1->SaveAs("figures/photonEfficiency/efficiency_eta.png");


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

