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
#include "../CMS_lumi.C"
#include "TStyle.h"
#include "TPaveStats.h"
#include "TText.h"
#include "TCut.h"
#include "TChain.h"
#include "THStack.h"


int xlo = 1;
int xhi = 4;
int nbin = 8;
int canvas_width = 1800;
int canvas_height = 700;

TPaveLabel* makeLabel(const std::string&,float ,float ,float ,float );


const char *dir = "figures";

#define PI 3.141592653589
double getError(double A, double eA, double B, double eB);
void getEfficiency(TH1F *&, TH1F *&, double *, double *);

void make_hist(TH1F *&, Color_t , int );

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



void prepare_canvas(TCanvas *canvas){
  float T = 0.08;
  float B = 0.14;
  float L = 0.14;
  float R = 0.04;
  
  canvas->SetFillColor(0);
  canvas->SetBorderMode(0);
  canvas->SetFrameFillStyle(0);
  canvas->SetFrameBorderMode(0);
  canvas->SetLeftMargin( L );
  canvas->SetRightMargin( R );
  canvas->SetTopMargin( T );
  canvas->SetBottomMargin( B );
  canvas->SetTickx(0);
  canvas->SetTicky(0);
}

vector<TPad*> get_pads(){
  
  vector<TPad*> pads;
  
  double left_margin = 0.18;
  double right_margin = 0.1;
  
  auto pad_0 = new TPad("pad_0", "pad_0", 0.0, 0.25, 0.33, 1.00);
  pad_0->SetLeftMargin(left_margin);
  pad_0->SetBottomMargin(0);
  pad_0->SetRightMargin(right_margin);
  
  auto pad_1 = new TPad("pad_1", "pad_1", 0.0, 0.00, 0.33, 0.25);
  pad_1->SetLeftMargin(left_margin);
  pad_1->SetTopMargin(0);
  pad_1->SetBottomMargin(0.3);
  pad_1->SetRightMargin(right_margin);
  
  auto pad_2 = new TPad("pad_2", "pad_2", 0.33, 0.25, 0.66, 1.0);
  pad_2->SetLeftMargin(left_margin);
  pad_2->SetBottomMargin(0);
  pad_2->SetRightMargin(right_margin);
  
  auto pad_3 = new TPad("pad_3", "pad_3", 0.33, 0.00, 0.66, 0.25);
  pad_3->SetLeftMargin(left_margin);
  pad_3->SetTopMargin(0);
  pad_3->SetBottomMargin(0.3);
  pad_3->SetRightMargin(right_margin);
  
  auto pad_4 = new TPad("pad_4", "pad_4", 0.66, 0.25, 1.00, 1.0);
  pad_4->SetLeftMargin(left_margin);
  pad_4->SetBottomMargin(0);
  pad_4->SetRightMargin(right_margin);
  
  auto pad_5 = new TPad("pad_5", "pad_5", 0.66, 0.00, 1.00, 0.25);
  pad_5->SetLeftMargin(left_margin);
  pad_5->SetTopMargin(0);
  pad_5->SetBottomMargin(0.3);
  pad_5->SetRightMargin(right_margin);
  
  pads.push_back(pad_0);
  pads.push_back(pad_1);
  pads.push_back(pad_2);
  pads.push_back(pad_3);
  pads.push_back(pad_4);
  pads.push_back(pad_5);
  
  return pads;
}

TH1F* get_ratio(TH1F *hist_num, TH1F* hist_den){
  auto hist_ratio = (TH1F*)hist_num->Clone();
  hist_ratio->Divide(hist_den);
  
  hist_ratio->SetMinimum(0.5);
  hist_ratio->SetMaximum(1.5);
  
  hist_ratio->GetXaxis()->SetTitleFont(43);
  hist_ratio->GetXaxis()->SetTitleSize(20);
  hist_ratio->GetXaxis()->SetTitleOffset(4);
  hist_ratio->GetXaxis()->SetLabelFont(43);
  hist_ratio->GetXaxis()->SetLabelSize(20);
  
  hist_ratio->GetYaxis()->SetTitle("Ratio Data/MC");
  hist_ratio->GetYaxis()->SetTitleFont(43);
  hist_ratio->GetYaxis()->SetTitleSize(20);
  hist_ratio->GetYaxis()->SetTitleOffset(2);
  hist_ratio->GetYaxis()->SetLabelFont(43);
  hist_ratio->GetYaxis()->SetLabelSize(20);
  hist_ratio->GetYaxis()->SetNdivisions(5);
  
  hist_ratio->SetFillColorAlpha(kRed, 0.0);
  
  
  
  return hist_ratio;
}

void plot_photonID(){
 
  //gROOT->LoadMacro("CMS_lumi.C");
  bool outOfFrame    = false;
  TH1::SetDefaultSumw2();
   gStyle->SetOptStat(0);

  //TFile *outf= new TFile("histos.root","recreate");  

  TChain *data = new TChain("tnpQED/fitter_tree");
  data->Add("efficienciesQED_Data_singleEG3_photonEt2_13Feb2024.root");
  TChain *qed = new TChain("tnpQED/fitter_tree");
  qed->Add("efficienciesQED_MC_singleEG3_photonEt2_13Feb2024.root");


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
  TH1F* efficiency_barrel_pT = new TH1F("",";p_{T}^{e} - p_{T}^{tk} ~ E_{T}^{#gamma} (GeV);Efficiency",5,bins);

  //
  TH1F* numerator_endcap_pT = new TH1F("",";p_{T}^{e} - p_{T}^{tk} ~ E_{T}^{#gamma};Numerator",5,bins);
  TH1F* denominator_endcap_pT = new TH1F("",";p_{T}^{e} - p_{T}^{tk} ~ E_{T}^{#gamma};Denominator",5,bins);
  TH1F* efficiency_endcap_pT = new TH1F("",";p_{T}^{e} - p_{T}^{tk} ~ E_{T}^{#gamma} (GeV);Efficiency",5,bins);

  //
  TH1F* numerator_eta = new TH1F("",";#eta^{e};Numerator",12,0,2.4);
  TH1F* denominator_eta = new TH1F("",";#eta^{e};Denominator",12,0,2.4);
  TH1F* efficiency_eta = new TH1F("",";#eta^{e};Efficiency",12,0,2.4);

  // qed histograms
  TH1F* qed_numerator_barrel_pT = new TH1F("",";p_{T}^{e} - p_{T}^{tk} ~ E_{T}^{#gamma};Numerator",5,bins);
  TH1F* qed_denominator_barrel_pT = new TH1F("",";p_{T}^{e} - p_{T}^{tk} ~ E_{T}^{#gamma};Denominator",5,bins);
  TH1F* qed_efficiency_barrel_pT = new TH1F("",";p_{T}^{e} - p_{T}^{tk} ~ E_{T}^{#gamma} (GeV);Efficiency",5,bins);

  //
  TH1F* qed_numerator_endcap_pT = new TH1F("",";p_{T}^{e} - p_{T}^{tk} ~ E_{T}^{#gamma};Numerator",5,bins);
  TH1F* qed_denominator_endcap_pT = new TH1F("",";p_{T}^{e} - p_{T}^{tk} ~ E_{T}^{#gamma};Denominator",5,bins);
  TH1F* qed_efficiency_endcap_pT = new TH1F("",";p_{T}^{e} - p_{T}^{tk} ~ E_{T}^{#gamma} (GeV);Efficiency",5,bins);

  //
  TH1F* qed_numerator_eta = new TH1F("",";#eta^{e};Numerator",12,0,2.4);
  TH1F* qed_denominator_eta = new TH1F("",";#eta^{e};Denominator",12,0,2.4);
  TH1F* qed_efficiency_eta = new TH1F("",";#eta^{e};Efficiency",12,0,2.4);

  // Loop over data events
  for(int i = 0; i < data->GetEntriesFast(); i++){
    data->GetEntry(i);

    TLorentzVector electron, track, photon;
    electron.SetPtEtaPhiM(tag_pt,tag_eta,tag_phi,0.005);
    track.SetPtEtaPhiM(probetkPt,probetkEta,probetkPhi,0.005);
    photon = electron-track;
    
    //if(pass_EG3 && probetkAco < 0.2 && ok_probeTrk && nPho_notag == 1 && probetkMinDpt>2.0 ){
    if(pass_EG3 && probetkAco < 0.01 && probetkPt >0.65 && ok_probeTrk && probetkMinDpt>2.0 && probetkMinDpt<20 && probetkValidHits >5 && fabs(photon.Eta())<2.2 && fabs(probetkEta) <= 2.2 && nPho_notag==1 && ok_photon==1 && phoEt_notag>2.0 ){
       if(fabs(probetkEta) < 1.5){      
        denominator_barrel_pT->Fill(probetkMinDpt);
        denominator_eta->Fill(fabs(probetkEta));
        if(ok_ID == 1 ){
          numerator_barrel_pT->Fill(probetkMinDpt);
          numerator_eta->Fill(fabs(probetkEta));
        }
      }
      //else if(fabs(probetkEta) > 1.5){
      else if(fabs(probetkEta) > 1.5 && fabs(probetkEta) <= 2.2 ){
        if (fabs(probetkEta) > 2.2) cout << "Eta:" << probetkEta << endl;
        denominator_endcap_pT->Fill(probetkMinDpt);
        denominator_eta->Fill(fabs(probetkEta));
        if(ok_ID == 1 ){
          numerator_endcap_pT->Fill(probetkMinDpt);
          numerator_eta->Fill(fabs(probetkEta));
        }
      }
    }
  }

  // Loop over qed events
  for(int i = 0; i < qed->GetEntriesFast(); i++){
    qed->GetEntry(i);

    TLorentzVector electron, track, photon;
    electron.SetPtEtaPhiM(tag_pt,tag_eta,tag_phi,0.005);
    track.SetPtEtaPhiM(probetkPt,probetkEta,probetkPhi,0.005);
    photon = electron-track;
    
    //if(qed_pass_EG3 && qed_probetkAco < 0.2 && qed_ok_probeTrk  && qed_nPho_notag == 1 && qed_probetkMinDpt>2.0 ){
    if(qed_pass_EG3 && qed_probetkAco < 0.01 && qed_probetkPt >0.65 && qed_ok_probeTrk  && qed_probetkMinDpt>2.0 && qed_probetkMinDpt<20.0 &&  qed_probetkValidHits>5 && fabs(photon.Eta())<2.2 && fabs(qed_probetkEta) <= 2.2 && qed_nPho_notag==1 && qed_ok_photon==1 && qed_phoEt_notag>2.0 ){    
      if(fabs(qed_probetkEta) < 1.5){    

        qed_denominator_barrel_pT->Fill(qed_probetkMinDpt);
        qed_denominator_eta->Fill(qed_probetkEta);

        if(qed_ok_ID == 1){
          qed_numerator_barrel_pT->Fill(qed_probetkMinDpt);
          qed_numerator_eta->Fill(qed_probetkEta);      
        }
      }
      //else if(fabs(qed_probetkEta) > 1.5){
      else if(fabs(qed_probetkEta) > 1.5 && fabs(qed_probetkEta) <= 2.2){
        qed_denominator_endcap_pT->Fill(qed_probetkMinDpt);
        qed_denominator_eta->Fill(qed_probetkEta);

        if(qed_ok_ID == 1 ){
          qed_numerator_endcap_pT->Fill(qed_probetkMinDpt);
          qed_numerator_eta->Fill(qed_probetkEta);
        }
      }
    }
  }

  TLegend *leg1=new TLegend(0.65,0.2080679,0.9971347,0.407091);
  leg1->SetFillColor(0);
  leg1->SetBorderSize(0);
  leg1->SetFillStyle(0);
  leg1->SetTextFont(43);
  leg1->SetTextSize(24);
  leg1->AddEntry(efficiency_barrel_pT,"Data","pl");
  leg1->AddEntry(qed_efficiency_barrel_pT,"MC","pl");

   TCanvas* canvas = new TCanvas("canvas","canvas", 50, 50, canvas_width, canvas_height);
//  prepare_canvas(canvas);
  
  vector<TPad*> pads = get_pads();
  
  //TCanvas *c1 = new TCanvas("c1", "c1",67,87,700,491);
  //TCanvas* c1 = new TCanvas();
  canvas->cd();
  pads[0]->Draw();
  pads[0]->cd();
  pads[0]->SetGridx();
  pads[0]->SetGridy();
  //pads[0]->SetLogy();
  
  //gPad->SetGridx();
  //gPad->SetGridy();
  efficiency_barrel_pT->Divide(numerator_barrel_pT, denominator_barrel_pT, 1, 1, "B");
  efficiency_barrel_pT->SetMarkerColor(kBlue+1);
  efficiency_barrel_pT->SetMarkerStyle(20);
  efficiency_barrel_pT->SetMarkerSize(1);
  efficiency_barrel_pT->SetLineColor(kBlue+1);
  efficiency_barrel_pT->GetYaxis()->SetRangeUser(0.0,1.0);
  efficiency_barrel_pT->Draw("pe");

  qed_efficiency_barrel_pT->Divide(qed_numerator_barrel_pT, qed_denominator_barrel_pT, 1, 1, "B");
  qed_efficiency_barrel_pT->SetMarkerColor(2);
  qed_efficiency_barrel_pT->SetMarkerStyle(20);
  qed_efficiency_barrel_pT->SetMarkerSize(1);
  qed_efficiency_barrel_pT->SetLineColor(2);
  qed_efficiency_barrel_pT->Draw("pesame");
  leg1->Draw();
  std::string regionLabelStr = "|#eta^{SC}| < 1.44" ;
  auto labelRegion = makeLabel(regionLabelStr,0.70,0.40,0.77,0.47);
  labelRegion->Draw();
  //CMS_lumi( c1, 104, 0,lumi_PbPb2018 );
  
  
  canvas->cd();
  pads[1]->Draw();
  pads[1]->cd();  
  pads[1]->SetGridx();
  pads[1]->SetGridy();
  TH1F *hist_pt_ratio = get_ratio(efficiency_barrel_pT, qed_efficiency_barrel_pT);
  //auto hist_pt_ratio_syst = get_stat_uncertainty_hist(hist_pt_ratio);
  
  hist_pt_ratio->Draw("pex0");
  //hist_pt_ratio_syst->Draw("e2same");
  
  //hist_pt_ratio->GetXaxis()->SetRangeUser(0, 0.3);
  
  //c1->SaveAs("checks_figures/photonEfficiency_pt2p5/photonIDEff_barrel_pT.png");
  //c1->SaveAs("checks_figures/photonEfficiency_pt2p5/photonIDEff_barrel_pT.pdf");

 /* TCanvas *c2 = new TCanvas("c2", "c2",67,87,700,491);
  //TCanvas* c1 = new TCanvas();
  gPad->SetGridx();
  gPad->SetGridy();*/
  canvas->cd();
  pads[2]->Draw();
  pads[2]->cd();
  pads[2]->SetGridx();
  pads[2]->SetGridy();
  efficiency_endcap_pT->Divide(numerator_endcap_pT, denominator_endcap_pT, 1, 1, "B");
  efficiency_endcap_pT->SetMarkerColor(kBlue+1);
  efficiency_endcap_pT->SetMarkerStyle(20);
  efficiency_endcap_pT->SetMarkerSize(1);
  efficiency_endcap_pT->SetLineColor(kBlue+1);
  efficiency_endcap_pT->GetYaxis()->SetRangeUser(0.0,1.0);
  efficiency_endcap_pT->Draw("p e");

  qed_efficiency_endcap_pT->Divide(qed_numerator_endcap_pT, qed_denominator_endcap_pT, 1, 1, "B");
  qed_efficiency_endcap_pT->SetMarkerColor(2);
  qed_efficiency_endcap_pT->SetMarkerStyle(20);
  qed_efficiency_endcap_pT->SetMarkerSize(1);
  qed_efficiency_endcap_pT->SetLineColor(2);
  qed_efficiency_endcap_pT->Draw("p e same");
  leg1->Draw();
  std::string regionLabelStr2 = "1.56 < |#eta^{SC}| < 2.2";
  auto labelRegion2 = makeLabel(regionLabelStr2,0.70,0.40,0.77,0.47);
      labelRegion2->Draw();
      
  canvas->cd();
  pads[3]->Draw();
  pads[3]->cd();  
  pads[3]->SetGridx();
  pads[3]->SetGridy();
  TH1F *hist_pt_ratio_en = get_ratio(efficiency_endcap_pT, qed_efficiency_endcap_pT);
  //auto hist_pt_ratio_syst = get_stat_uncertainty_hist(hist_pt_ratio);
  
  hist_pt_ratio_en->Draw("pex0");
  //CMS_lumi( c2, 104, 0,lumi_PbPb2018 );
  //c2->SaveAs("checks_figures/photonEfficiency_pt2p5/photonIDEff_endcap_pT.png");
  //c2->SaveAs("checks_figures/photonEfficiency_pt2p5/photonIDEff_endcap_pT.pdf");


  //TCanvas *c3 = new TCanvas("c3", "c3",67,87,700,491);
  //TCanvas* c1 = new TCanvas();
  //gPad->SetGridx();
  //gPad->SetGridy();
  canvas->cd();
  pads[4]->Draw();
  pads[4]->cd();
  pads[4]->SetGridx();
  pads[4]->SetGridy();
  efficiency_eta->Divide(numerator_eta, denominator_eta, 1, 1, "B");
  efficiency_eta->SetMarkerColor(kBlue+1);
  efficiency_eta->SetMarkerStyle(20);
  efficiency_eta->SetMarkerSize(1);
  efficiency_eta->SetLineColor(kBlue+1);
  efficiency_eta->GetYaxis()->SetRangeUser(0.0,1.0);
  efficiency_eta->Draw("p e");

  qed_efficiency_eta->Divide(qed_numerator_eta, qed_denominator_eta, 1, 1, "B");
  qed_efficiency_eta->SetMarkerColor(2);
  qed_efficiency_eta->SetMarkerStyle(20);
  qed_efficiency_eta->SetMarkerSize(1);
  qed_efficiency_eta->SetLineColor(2);
  qed_efficiency_eta->Draw("p e same");
  leg1->Draw();
  //CMS_lumi( c3, 104, 0,lumi_PbPb2018 );
  //c3->SaveAs("checks_figures/photonEfficiency_pt2p5/photonIDEff_eta.png");
  //c3->SaveAs("checks_figures/photonEfficiency_pt2p5/photonIDEff_eta.pdf");

  canvas->cd();
  pads[5]->Draw();
  pads[5]->cd();  
  pads[5]->SetGridx();
  pads[5]->SetGridy();
  TH1F *hist_eta_ratio = get_ratio(efficiency_eta, qed_efficiency_eta);
  hist_eta_ratio->Draw("pex0");
  
  canvas->SaveAs("checks_figures/photonEfficiency_pt2p0/photonIDEff_all.png");
  canvas->SaveAs("checks_figures/photonEfficiency_pt2p0/photonIDEff_all.pdf");
      
  double eff, err;
  cout << "*****Data ******" << endl;; 
  cout << "pt barrel efficiency = "; 
  getEfficiency(numerator_barrel_pT, denominator_barrel_pT, &eff, &err);
  cout << "pt endcap efficiency = "; 
  getEfficiency(numerator_endcap_pT, denominator_endcap_pT, &eff, &err);
  cout << "Eta efficiency = "; 
  getEfficiency(numerator_eta, denominator_eta, &eff, &err);


 // double eff, err;
  cout << "*****MC ******" << endl;; 
  cout << "pt barrel efficiency = "; 
  getEfficiency(qed_numerator_barrel_pT, qed_denominator_barrel_pT, &eff, &err);
  cout << "pt endcap efficiency = "; 
  getEfficiency(qed_numerator_endcap_pT, qed_denominator_endcap_pT, &eff, &err);
  cout << "Eta efficiency = "; 
  getEfficiency(qed_numerator_eta, qed_denominator_eta, &eff, &err);


}

void make_hist(TH1F *& hist, Color_t kcolor, int kstyle){
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

void getEfficiency(TH1F *& hnum, TH1F *& hden, double *efficiency, double *error){
  double numError, denError;
  double int_num = hnum->IntegralAndError(1,hnum->GetNbinsX(),numError);
  double int_den = hden->IntegralAndError(1,hden->GetNbinsX(),denError);
  double int_num_err = numError;
  double int_den_err = denError;
  *efficiency = int_num/int_den;
  *error = getError(int_num,int_num_err,int_den,int_den_err);
  //cout <<"Num: " << int_num << endl;
  //cout <<"Den: " << int_den << endl;
  std::cout << *efficiency  << " +/- " << *error <<  endl;  
}

//Ratio Error
double getError(double A, double eA, double B, double eB){
  double f=A/B;
  double fA=eA/A;
  double fB=eB/B;
  double eR=  f*sqrt( (fA*fA + fB*fB )) ;
  return eR;
}

TPaveLabel* makeLabel(const std::string& labelTxt,float x1,float y1,float x2,float y2)
{
  TPaveLabel* label = new TPaveLabel(x1,y1,x2,y2,
				     labelTxt.c_str(),"brNDC");
  label->SetBorderSize(0);
  label->SetTextFont(42);
  label->SetFillStyle(0);
  label->SetTextAlign(12);
  label->SetTextSize(0.657895);
  return label;
}

