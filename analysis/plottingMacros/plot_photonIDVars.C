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

const int nfile = 5;
const char *sample[nfile]={"Data","QEDSC","QEDSL","LbLSC", "CEPSC"};

const char *dir = "figures";

#define PI 3.141592653589

void make_hist(TH1D *&, Color_t , int, int);
void drawText(const char *text, float xp, float yp, int size){
  TLatex *tex = new TLatex(xp,yp,text);
  tex->SetTextFont(43);
  tex->SetTextSize(size);
  tex->SetTextColor(kRed);
  tex->SetLineWidth(1);
  tex->SetNDC();
  tex->Draw();
}


bool outside_HEM(Double_t SCEta, Double_t SCPhi){
  if(SCEta < -1.34 && SCEta > -3 && SCPhi > -1.65 && SCPhi < -0.85) return false;
  return true;
}

bool outside_crack(Double_t SCEta){
  //if(abs(SCEta) > 1.4442 && abs(SCEta) < 1.566) return false;
  //if(abs(SCEta) > 1.1942 && abs(SCEta) < 1.816) return false;
  if(abs(SCEta) > 1.3942 && abs(SCEta) < 1.616) return false;
  return true;
}

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
using namespace std;


TCanvas* PlotHistsAndRatio(TCanvas* , TH1D* , TH1D*, TH1D* , TH1D*, TH1D*,  double , double , double , double , bool, const char *, double); 

const double wt[nfile] = {1, lumiNormSC, norm_exgg, norm_cep};

void plot_photonIDVars(){
  
  //gROOT->LoadMacro("CMS_lumi.C");
  bool outOfFrame    = false;
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);

  TFile *outf= new TFile("histos.root","recreate");  
  TChain *phoID[nfile];

  for (int i=0; i<nfile; i++){
    phoID[i] = new TChain("photonIDVars_tree");
    phoID[i]->Add(Form("%sAll_photonID_plots.root",sample[i]));
   cout << "file " << phoID[i] << endl;
  }

  const TCut barrel_cut =  "photon_Et > 0 && abs(photon_SCEta)<1.446 ";
  const TCut endcap_cut =  "photon_Et > 0 && abs(photon_SCEta)>1.446 && abs(photon_SCEta)< 2.1";

  TH1D* hpho_pt_barrel[nfile], * hpho_eta_barrel[nfile],  * hpho_phi_barrel[nfile];
  TH1D *hpho_hovere_barrel[nfile], *hpho_etawidth_barrel[nfile], *hpho_swisscross_barrel[nfile], *hpho_seedTime_barrel[nfile], *hpho_sigmaIetaIeta_barrel[nfile];
  TH1D* hpho_pt_endcap[nfile], * hpho_eta_endcap[nfile],  * hpho_phi_endcap[nfile];
  TH1D *hpho_hovere_endcap[nfile], *hpho_etawidth_endcap[nfile], *hpho_swisscross_endcap[nfile], *hpho_seedTime_endcap[nfile], *hpho_sigmaIetaIeta_endcap[nfile];
  
  for (int i=0; i<nfile; i++){
    
    hpho_pt_barrel[i]   = new TH1D(Form("hpho_pt_barrel%d",i),"",20,0,20);
    hpho_eta_barrel[i]  = new TH1D(Form("hpho_eta_barrel%d",i),"",100,-2.4,2.4);
    hpho_phi_barrel[i]  = new TH1D(Form("hpho_phi_barrel%d",i),"",100,-PI,PI);
    hpho_hovere_barrel[i]       = new TH1D(Form("hpho_hovere_barrel%d",i),"H/E",60,0,0.6);
    hpho_etawidth_barrel[i]     = new TH1D(Form("hpho_etawidth_barrel%d",i),"#eta width",60,0,0.08);
    hpho_swisscross_barrel[i]   = new TH1D(Form("hpho_swisscross_barrel%d",i),"1 - E4/E",55,0.0,1.1);
    hpho_seedTime_barrel[i]     = new TH1D(Form("hpho_seedTime_barrel%d",i),"abs(seed time) (ns)",50,0,25);
    hpho_sigmaIetaIeta_barrel[i]= new TH1D(Form("hpho_sigmaIetaIeta_barrel%d",i),"#sigma i#eta i#eta",60,0,0.08);

    hpho_pt_endcap[i]   = new TH1D(Form("hpho_pt_endcap%d",i),"",20,0,20);
    hpho_eta_endcap[i]  = new TH1D(Form("hpho_eta_endcap%d",i),"",100,-2.4,2.4);
    hpho_phi_endcap[i]  = new TH1D(Form("hpho_phi_endcap%d",i),"",100,-PI,PI);
    hpho_hovere_endcap[i]       = new TH1D(Form("hpho_hovere_endcap%d",i),"H/E",60,0,0.6);
    hpho_etawidth_endcap[i]     = new TH1D(Form("hpho_etawidth_endcap%d",i),"#eta width",60,0,0.08);
    hpho_swisscross_endcap[i]   = new TH1D(Form("hpho_swisscross_endcap%d",i),"1 - E4/E",55,0.0,1.1);
    hpho_seedTime_endcap[i]     = new TH1D(Form("hpho_seedTime_endcap%d",i),"abs(seed time) (ns)",50,0,25);
    hpho_sigmaIetaIeta_endcap[i]= new TH1D(Form("hpho_sigmaIetaIeta_endcap%d",i),"#sigma i#eta i#eta",60,0,0.08);

    phoID[i]->Project(hpho_pt_barrel[i]->GetName(),             "photon_Et",               barrel_cut);
    phoID[i]->Project(hpho_eta_barrel[i]->GetName(),            "photon_Eta",              barrel_cut);
    phoID[i]->Project(hpho_phi_barrel[i]->GetName(),            "photon_Phi",              barrel_cut);
    phoID[i]->Project(hpho_hovere_barrel[i]->GetName(),         "photon_HoverE",           barrel_cut);
    phoID[i]->Project(hpho_etawidth_barrel[i]->GetName(),       "photon_EtaWidth",         barrel_cut);
    phoID[i]->Project(hpho_swisscross_barrel[i]->GetName(),     "photon_SwissCross",       barrel_cut);
    phoID[i]->Project(hpho_seedTime_barrel[i]->GetName(),       "abs(photon_SeedTime)",    barrel_cut);
    phoID[i]->Project(hpho_sigmaIetaIeta_barrel[i]->GetName(),  "photon_SigmaIEtaIEta",    barrel_cut);

    phoID[i]->Project(hpho_pt_endcap[i]->GetName(),             "photon_Et",               endcap_cut);
    phoID[i]->Project(hpho_eta_endcap[i]->GetName(),            "photon_Eta",              endcap_cut);
    phoID[i]->Project(hpho_phi_endcap[i]->GetName(),            "photon_Phi",              endcap_cut);
    phoID[i]->Project(hpho_hovere_endcap[i]->GetName(),         "photon_HoverE",           endcap_cut);
    phoID[i]->Project(hpho_etawidth_endcap[i]->GetName(),       "photon_EtaWidth",         endcap_cut);
    phoID[i]->Project(hpho_swisscross_endcap[i]->GetName(),     "photon_SwissCross",       endcap_cut);
    phoID[i]->Project(hpho_seedTime_endcap[i]->GetName(),       "abs(photon_SeedTime)",    endcap_cut);
    phoID[i]->Project(hpho_sigmaIetaIeta_endcap[i]->GetName(),  "photon_SigmaIEtaIEta",    endcap_cut);
  } // for 4 files
  

 
  TCanvas* c1 = new TCanvas("Photon_HoverE_barrel","H/E",254,411,639,592);
  //                canvas, data,              QED SC,                 QED SL,               Lbyl,                   CEP,            xmin, xmax, ymin, ymax, drawlog, threshold text, 
  // xval threshold
  PlotHistsAndRatio(c1, hpho_hovere_barrel[0], hpho_hovere_barrel[1], hpho_hovere_barrel[2], hpho_hovere_barrel[3], hpho_hovere_barrel[4], 
                    0.045960,2.0,0.0001,2.0,1, "0.045960", 0.22);

  TCanvas* c2 = new TCanvas("Photon_HoverE_endcap","H/E",254,411,639,592);
  PlotHistsAndRatio(c2, hpho_hovere_endcap[0], hpho_hovere_endcap[1], hpho_hovere_endcap[2], hpho_hovere_endcap[3], hpho_hovere_endcap[4],
                    0.059000,2.0,0.0001,2.0,1, "0.059000", 0.23);

  
  TCanvas* c3 = new TCanvas("Photon_etaWidth_barrel","#eta width",254,411,639,592);
  PlotHistsAndRatio(c3, hpho_etawidth_barrel[0], hpho_etawidth_barrel[1], hpho_etawidth_barrel[2], hpho_etawidth_barrel[3], hpho_etawidth_barrel[4], 
                    0.0106,2.0,0.0001,1.0,1, "0.0106", 0.25);

  TCanvas* c4 = new TCanvas("Photon_etaWidth_endcap","#eta width",254,411,639,592);
  PlotHistsAndRatio(c4, hpho_etawidth_endcap[0], hpho_etawidth_endcap[1], hpho_etawidth_endcap[2], hpho_etawidth_endcap[3], hpho_etawidth_endcap[4], 
                    0.0272,2.0,0.0001,1.0,1, "0.0272", 0.45);

  TCanvas* c5 = new TCanvas("Photon_swisscross_barrel","swiss cross",254,411,639,592);
  PlotHistsAndRatio(c5, hpho_swisscross_barrel[0], hpho_swisscross_barrel[1], hpho_swisscross_barrel[2], hpho_swisscross_barrel[3], hpho_swisscross_barrel[4], 
	            0.95,1.2,0.0001,0.2,0, "0.95", 0.9);

  TCanvas* c6 = new TCanvas("Photon_swisscross_endcap","swiss cross",254,411,639,592);
  PlotHistsAndRatio(c6, hpho_swisscross_endcap[0], hpho_swisscross_endcap[1], hpho_swisscross_endcap[2], hpho_swisscross_endcap[3], hpho_swisscross_endcap[4], 
                    0.95,1.2,0.0001,0.2,0, "0.95", 0.9);

  TCanvas* c7 = new TCanvas("Photon_seedTime_barrel","seed time barrel",254,411,639,592);
  PlotHistsAndRatio(c7, hpho_seedTime_barrel[0], hpho_seedTime_barrel[1], hpho_seedTime_barrel[2], hpho_seedTime_barrel[3], hpho_seedTime_barrel[4], 
                    3.0,2.0,0.0001,1.0,1, "3.0", 0.25);

  TCanvas* c8 = new TCanvas("Photon_seedTime_endcap","seed time endcap",254,411,639,592);
  PlotHistsAndRatio(c8, hpho_seedTime_endcap[0], hpho_seedTime_endcap[1], hpho_seedTime_endcap[2], hpho_seedTime_endcap[3], hpho_seedTime_endcap[4], 
                    3.0,2.0,0.0001,1.0,1, "3.0", 0.25);

  TCanvas* c9 = new TCanvas("Photon_sigmaIetaIeta_barrel","sigmaIetaIeta barrel",254,411,639,592);
  PlotHistsAndRatio(c9, hpho_sigmaIetaIeta_barrel[0], hpho_sigmaIetaIeta_barrel[1], hpho_sigmaIetaIeta_barrel[2], hpho_sigmaIetaIeta_barrel[3], hpho_sigmaIetaIeta_barrel[4],
                     0.02,2.0,0.0001,1.0,1, "0.02", 0.25);

  TCanvas* c10 = new TCanvas("Photon_sigmaIetaIeta_endcap","sigmaIetaIeta endcap",254,411,639,592);
  PlotHistsAndRatio(c10, hpho_sigmaIetaIeta_endcap[0], hpho_sigmaIetaIeta_endcap[1], hpho_sigmaIetaIeta_endcap[2], hpho_sigmaIetaIeta_endcap[3], hpho_sigmaIetaIeta_endcap[4],
                    0.06,2.0,0.0001,1.0,1, "0.06", 0.8);

 /* TCanvas* c11 = new TCanvas("Photon_pt_barrel","#eta width",254,411,639,592);
  PlotHistsAndRatio(c11, hpho_pt_barrel[0], hpho_pt_barrel[1], hpho_pt_barrel[2], hpho_pt_barrel[3], hpho_pt_barrel[4], 
                    0.0106,2.0,0.0001,1.0,1, "0.0106", 0.25);

  TCanvas* c12 = new TCanvas("Photon_pt_endcap","#eta width",254,411,639,592);
  PlotHistsAndRatio(c12, hpho_pt_endcap[0], hpho_pt_endcap[1], hpho_pt_endcap[2], hpho_pt_endcap[3], hpho_pt_endcap[4], 
                    0.0272,2.0,0.0001,1.0,1, "0.0272", 0.45);*/
 
}


TCanvas* PlotHistsAndRatio(TCanvas* c1, TH1D* hdata, TH1D* hqedsc, TH1D* hqedsl, TH1D* hlbylsc, TH1D* hcepsc, double lxmin, double lxmax, double lymin, double lymax, bool drawLog, const char *tex2, double thresh_xval){
  
  int W = 700;
  int H = 600;
  float T = 0.08;
  float B = 0.14; 
  float L = 0.14;
  float R = 0.04;

  
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetFrameFillStyle(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin( L );
  c1->SetRightMargin( R );
  c1->SetTopMargin( T );
  c1->SetBottomMargin( B );
  c1->SetTickx(0);
  c1->SetTicky(0);
  c1->cd(1);
  if(drawLog)gPad->SetLogy();
  make_hist(hdata, kBlack,    21 ,1);
  make_hist(hqedsc, kRed,      21, 1);
  make_hist(hqedsl, kOrange+2, 21, 1);
  make_hist(hlbylsc, kBlue, 21 ,1);
  make_hist(hcepsc, kGreen,  21,2);
  hdata->GetYaxis()->SetRangeUser(lymin,lymax);
  hdata->Draw("hist");
  hqedsc->Draw("histsame");
  hqedsl->Draw("histsame");
  hlbylsc->Draw("histsame");
  hcepsc->Draw("histsame");
  
  TLegend *leg2=new TLegend(0.55,0.60,0.98,0.90);
  leg2->SetFillColor(0);
  leg2->SetBorderSize(0);
  leg2->SetFillStyle(0);
  leg2->SetTextFont(43);
  leg2->SetTextSize(24);
  leg2->AddEntry(hdata,"Data ","pl");
  leg2->AddEntry(hqedsc,"QED SC","pl");
  leg2->AddEntry(hqedsl,"QED SL","pl");
  leg2->AddEntry(hlbylsc, "LbyL","pl");
  leg2->AddEntry(hcepsc, "CEP","pl");
  
  leg2->Draw();

  
  //double xmin = hmc->GetXaxis()->GetXmin();
  //double xmax = hmc->GetXaxis()->GetXmax();


  TLine *l1 = new TLine(lxmin,lymin,lxmin,lymax);
  l1->SetLineColor(kRed);
  l1->Draw();
  drawText(tex2,thresh_xval,0.80,22);
   


  TString cName=c1->GetName();
  cName+=".png";
  c1->SaveAs(cName);
  TString c2Name=c1->GetName();
  c2Name+=".pdf";
  c1->SaveAs(c2Name);
  return c1;
}


void make_hist(TH1D *& hist, Color_t kcolor, int kstyle, int lstyle){
  // For the axis labels:
  hist->SetLabelColor(1, "XYZ");
  hist->SetLabelFont(42, "XYZ");
  hist->SetLabelOffset(0.007, "XYZ");
  hist->SetLabelSize(0.05, "XYZ");
  hist->SetLineColor(kcolor); 
  hist->SetLineStyle(lstyle); 
  hist->SetLineWidth(2); 
  hist->SetMarkerColor(kcolor);
  hist->SetMarkerSize(1.0);
  //hist->SetFillColorAlpha(kcolor,0.3);
  hist->SetMarkerStyle(kstyle);
  hist->Scale(1./hist->Integral());
  hist->GetXaxis()->SetTitle(hist->GetTitle());  
  hist->GetYaxis()->SetTitle("1/events");  
  
 
}

