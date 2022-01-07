#include <iostream>
#include <fstream>
#include <sstream>
#include "TROOT.h"
#include "TStyle.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TAxis.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TText.h"
#include "TLorentzVector.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TAxis.h"
#include "TH1.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH1I.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TMath.h"
#include "TVector3.h"
#include "TString.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TSystem.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TLegend.h>
#include <TMath.h>
#include <TPad.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

double syst_uncertainty = 0.26;
double syst_uncertainty_mc = 0.10;

void make_hist(TH1D *&, string, string, int, float, Color_t, int, int) ;
TH1D* get_stat_uncertainty_hist(TH1D *input_hist, double uncertainty = syst_uncertainty);
void printBinCont(TH1D *hist);
void prepare_canvas(TCanvas *canvas);

int mc_gen_color = kBlue;
int data_unfold_color = kRed;
int mc_reco_color = kBlack;
int data_reco_color = kOrange+1;

void draw_unfold(int method =1)
{
  
  //  gStyle->SetErrorX(0);
  
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  TH1::SetDefaultSumw2();
  //gStyle->SetPadLeftMargin(0.01);
  gStyle->SetPadRightMargin(0.005);
  
  
  char MethID1[100];
  if(method==1)
  {
    
    sprintf(MethID1,"Bayes_unfo");
  }
  if(method==2)
  {
    sprintf(MethID1,"Svd_unfo ");
  }
  if(method==3)
  {
    sprintf(MethID1,"BinByBin_unfo");
  }
  
  TFile *f1= new TFile(Form("unfolding_histograms_%s.root",MethID1),"r");
  cout<<"   "<<f1->GetName()<<endl;
  
  
  TFile *f2= new TFile(Form("unfolding_histograms_invmass_%s.root",MethID1),"r");
  cout<<"   "<<f2->GetName()<<endl;
  
  TH1D *hMuMu_pt_gen          = (TH1D*)f1->Get("hGenPt_xSec");
  TH1D *hMuMu_pt_recomc       = (TH1D*)f1->Get("hRecoMCPt_xSec");
  TH1D *hMuMu_pt_recodata     = (TH1D*)f1->Get("hRecoDataPt_xSec");
  TH1D *hMuMu_pt_unfodata     = (TH1D*)f1->Get("hUnfoDataPt_xSec");
  TH1D *hMuMu_pt_unfomc       = (TH1D*)f1->Get("hUnfoMCPt_xSec");
  
  TH1D *hMuMu_rapidity_gen          = (TH1D*)f1->Get("hGenRap_xSec");
  TH1D *hMuMu_rapidity_recomc       = (TH1D*)f1->Get("hRecoMCRap_xSec");
  TH1D *hMuMu_rapidity_recodata     = (TH1D*)f1->Get("hRecoDataRap_xSec");
  TH1D *hMuMu_rapidity_unfodata     = (TH1D*)f1->Get("hUnfoDataRap_xSec");
  TH1D *hMuMu_rapidity_unfomc       = (TH1D*)f1->Get("hUnfoMCRap_xSec");
  
  
  TH1D *hMuMu_invmass_gen          = (TH1D*)f2->Get("hGenInvmass_xSec");
  TH1D *hMuMu_invmass_recomc       = (TH1D*)f2->Get("hRecoMCInvmass_xSec");
  TH1D *hMuMu_invmass_recodata     = (TH1D*)f2->Get("hRecoDataInvmass_xSec");
  TH1D *hMuMu_invmass_unfodata     = (TH1D*)f2->Get("hUnfoDataInvmass_xSec");
  TH1D *hMuMu_invmass_unfomc       = (TH1D*)f2->Get("hUnfoMCInvmass_xSec");
  
  cout<<"ok"<<endl;
  
  TLegend *leg1=new TLegend(0.30,0.72,0.90,0.9);
  leg1->SetFillColor(0);
  leg1->SetBorderSize(0);
  leg1->SetFillStyle(0);
  leg1->SetTextFont(43);
  leg1->SetTextSize(24);
  leg1->AddEntry(hMuMu_pt_unfomc,"Unfolded MC (Bayes)","pl");
  leg1->AddEntry(hMuMu_pt_gen, "Gen-level MC (Superchic)","pl");
  leg1->AddEntry(hMuMu_pt_recomc, "Reconstructed MC (Superchic)", "pl");
  
  
  TLegend *leg2=new TLegend(0.30,0.68,0.90,0.9);
  leg2->SetFillColor(0);
  leg2->SetBorderSize(0);
  leg2->SetFillStyle(0);
  leg2->SetTextFont(43);
  leg2->SetTextSize(24);
  
  leg2->AddEntry(hMuMu_pt_recodata,"Reconstructed data","pl");
  leg2->AddEntry(hMuMu_pt_unfodata,"Unfolded data (Bayes)","pl");
  leg2->AddEntry(hMuMu_pt_recomc, "Reconstructed MC (Superchic)", "pl");
  leg2->AddEntry(hMuMu_pt_gen, "Gen-level MC (Superchic)", "pl");
  
  int W = 600;
  int H = 500;
  
  // pT
  TCanvas* c1 = new TCanvas("c1","Dimuon pT",50,50,W,H);
  prepare_canvas(c1);
  c1->cd();
  gPad->SetLogy();
  
  
  string x_title = "p_{T}^{#gamma#gamma} (GeV)";
  string y_title = "d#sigma_{#gamma#gamma}/dp_{T}^{#gamma#gamma} (nb / 0.2 GeV)";
  
  cout<<"pt bin width:" <<hMuMu_pt_unfodata->GetXaxis()->GetBinWidth(1)<<endl;
  
  make_hist(hMuMu_pt_unfomc,x_title,y_title,20,1.0,data_unfold_color,1,1);
  
  make_hist(hMuMu_pt_gen,x_title,y_title,20,1.0,mc_gen_color,1,2);
  auto hMuMu_pt_gen_syst = get_stat_uncertainty_hist(hMuMu_pt_gen, syst_uncertainty_mc);
  
  hMuMu_pt_gen_syst->SetMaximum(2*pow(10.,3.));
  hMuMu_pt_gen_syst->SetMinimum(5*pow(10.,-2.));
  
  hMuMu_pt_gen_syst->Draw("e2");
  hMuMu_pt_gen->Draw("histsamex0");
  hMuMu_pt_unfomc->Draw("psame");
  make_hist(hMuMu_pt_recomc,x_title,y_title,20,1.0,mc_reco_color,1,2);
  hMuMu_pt_recomc->Draw("ehistsamex0");
  
  //CMS_lumi( c1, 1, 10 );
  leg1->Draw();
  c1->Print(Form("./fig/closure_pt_%s.pdf",MethID1));
  
  
  TCanvas* c2 = new TCanvas("c2","Dimuon pT",50,50,W,H);
  prepare_canvas(c2);
  c2->cd();
  //gPad->SetLogy();
  //hMuMu_pt_unfodata->SetMaximum(60);
  //hMuMu_pt_unfodata->SetMinimum(0);
  gPad->SetLogy();
  
  hMuMu_pt_unfodata->SetMaximum(2*pow(10.,3.));
  hMuMu_pt_unfodata->SetMinimum(5*pow(10.,-2.));
  
  make_hist(hMuMu_pt_unfodata,x_title,y_title,20,1.0,data_unfold_color,1,2);
  auto hMuMu_pt_unfodata_syst = get_stat_uncertainty_hist(hMuMu_pt_unfodata);
  hMuMu_pt_unfodata_syst->Draw("e2");
  
  hMuMu_pt_unfodata->Draw("psameex0");
  hMuMu_pt_gen->Draw("histsamex0");
  hMuMu_pt_gen_syst->Draw("e2same");
  hMuMu_pt_recomc->Draw("ehistsamex0");

  make_hist(hMuMu_pt_recodata,x_title,y_title,22,1.0,data_reco_color,1,2);
  hMuMu_pt_recodata->Draw("ehistsamex0");
  
  //CMS_lumi( c2, 1, 10 );
  leg2->Draw();
  c2->Print(Form("./fig/data_pt_%s.pdf",MethID1));
  
  // Rapidity
  TCanvas* c3 = new TCanvas("c3","Dimuon rapidity",50,50,W,H);
  prepare_canvas(c3);
  c3->cd();
  
  x_title = "|y_{#gamma#gamma}|";
  y_title = "d#sigma_{#gamma#gamma}/dy_{#gamma#gamma} (nb)";
  
  
  //hMuMu_rapidity_unfomc->GetXaxis()->SetRangeUser(0,1.0);
  make_hist(hMuMu_rapidity_unfomc,x_title,y_title,20,1.0,data_unfold_color,1,1);
  
  make_hist(hMuMu_rapidity_gen,x_title,y_title,20,1.0,mc_gen_color,1,2);
  auto hMuMu_rapidity_gen_syst = get_stat_uncertainty_hist(hMuMu_rapidity_gen, syst_uncertainty_mc);
  
  hMuMu_rapidity_gen_syst->SetMaximum(100);
  hMuMu_rapidity_gen_syst->SetMinimum(0);
  
  hMuMu_rapidity_gen_syst->Draw("e2");
  hMuMu_rapidity_gen->Draw("histsame");
  hMuMu_rapidity_unfomc->Draw("psame");
  make_hist(hMuMu_rapidity_recomc,x_title,y_title,20,1.0,mc_reco_color,1,2);
  hMuMu_rapidity_recomc->Draw("ehistsamex0");
  
  //CMS_lumi( c3, 1, 10 );
//  leg1->Draw();
  c3->Print(Form("./fig/closure_rapidity_%s.pdf",MethID1));
  
  TCanvas* c4 = new TCanvas("c4","Dimuon rap",50,50,W,H);
  prepare_canvas(c4);
  c4->cd();
  
  hMuMu_rapidity_unfodata->SetMaximum(100);
  hMuMu_rapidity_unfodata->SetMinimum(0);
  make_hist(hMuMu_rapidity_unfodata,x_title,y_title,20,1.0,data_unfold_color,1,2);
  auto hMuMu_rapidity_unfodata_syst = get_stat_uncertainty_hist(hMuMu_rapidity_unfodata);
  hMuMu_rapidity_unfodata_syst->Draw("e2");
  
  hMuMu_rapidity_unfodata->Draw("psameex0");
  hMuMu_rapidity_gen->Draw("histsamex0");
  hMuMu_rapidity_gen_syst->Draw("e2same");
  hMuMu_rapidity_recomc->Draw("ehistsamex0");
  make_hist(hMuMu_rapidity_recodata,x_title,y_title,22,1.0,data_reco_color,1,2);
  hMuMu_rapidity_recodata->Draw("ehistsamex0");
  
  //CMS_lumi( c4, 1, 10 );
//  leg2->Draw();
  c4->Print(Form("./fig/data_rapidity_%s.pdf",MethID1));
  
  
  
  
  //invmass
  TCanvas* c5 = new TCanvas("c5","Dimuon invmass",50,50,W,H);
  prepare_canvas(c5);
  c5->cd();
  
  x_title = "m_{#gamma#gamma} (GeV)";
  y_title = "d#sigma_{#gamma#gamma}/dm_{#gamma#gamma} (nb / 2 GeV)";
  
  cout<<"m_inv bin width:" <<hMuMu_invmass_unfodata->GetXaxis()->GetBinWidth(1)<<endl;
  
  make_hist(hMuMu_invmass_unfomc,x_title,y_title,20,1.0,data_unfold_color,1,1);
  make_hist(hMuMu_invmass_gen,x_title,y_title,20,1.0,mc_gen_color,1,2);
  
  hMuMu_invmass_gen->SetMaximum(50);
  hMuMu_invmass_gen->SetMinimum(0);
  hMuMu_invmass_gen->Draw("histsame");
  auto hMuMu_invmass_gen_syst = get_stat_uncertainty_hist(hMuMu_invmass_gen, syst_uncertainty_mc);
  hMuMu_invmass_gen_syst->Draw("e2same");
  
  make_hist(hMuMu_invmass_recomc,x_title,y_title,20,1.0,mc_reco_color,1,2);
  hMuMu_invmass_recomc->Draw("ehistsamex0");
  hMuMu_invmass_unfomc->Draw("psamex0");
  
  //CMS_lumi( c5, 1, 10 );
//  leg1->Draw();
  c5->Print(Form("./fig/closure_invmass_%s.pdf",MethID1));
  
  TCanvas* c6 = new TCanvas("c6","Dimuon rap",50,50,W,H);
  prepare_canvas(c6);
  c6->cd();
  
  hMuMu_invmass_unfodata->SetMaximum(50);
  hMuMu_invmass_unfodata->SetMinimum(0);
  make_hist(hMuMu_invmass_unfodata,x_title,y_title,20,1.0,data_unfold_color,1,2);
  auto hMuMu_invmass_unfodata_syst = get_stat_uncertainty_hist(hMuMu_invmass_unfodata);
  hMuMu_invmass_unfodata_syst->Draw("e2");
  
  hMuMu_invmass_unfodata->Draw("psameex0");
  hMuMu_invmass_gen->Draw("histsamex0");
  hMuMu_invmass_gen_syst->Draw("e2same");
  hMuMu_invmass_recomc->Draw("ehistsamex0");
  make_hist(hMuMu_invmass_recodata,x_title,y_title,22,1.0,data_reco_color,1,2);
  hMuMu_invmass_recodata->Draw("ehistsamex0");
  
  //CMS_lumi( c6, 1, 10 );
//  leg2->Draw();
  c6->Print(Form("./fig/data_invmass_%s.pdf",MethID1));
  
  printBinCont(hMuMu_pt_unfodata);
  printBinCont(hMuMu_rapidity_unfodata);
  printBinCont(hMuMu_invmass_unfodata);
  
}

void printBinCont(TH1D *hist){
  
  double bincont = 0;
  
  for (int i=1; i<=hist->GetNbinsX(); i++) {
    
    cout << "******bin:" << i << " " << hist->GetBinContent(i) << "+/-" <<  hist->GetBinError(i) << endl;
    bincont +=  hist->GetBinContent(i);
    
  }
  cout << "Total bincontent:" << bincont << endl;
}


void drawText(const char *text, float xp, float yp, int size){
  TLatex *tex = new TLatex(xp,yp,text);
  tex->SetTextFont(43);
  tex->SetTextSize(size);
  tex->SetTextColor(data_reco_color);
  tex->SetLineWidth(1);
  tex->SetNDC();
  tex->Draw();
}

void make_hist(TH1D *& hist, string xtitle, string ytitle, int kstyle, float ksize, Color_t kcolor, int lstyle, int lwidth){
  // For the axis labels:
  hist->SetLabelColor(1, "XYZ");
  hist->SetLabelFont(42, "XYZ");
  hist->SetLabelOffset(0.007, "XYZ");
  hist->SetLabelSize(0.05, "XYZ");
  
  // For the axis titles:
  hist->SetTitleFont(42, "XYZ");
  hist->SetTitleSize(0.06, "XYZ");
  hist->GetXaxis()->SetTitleOffset(0.9);
  hist->GetYaxis()->SetTitleOffset(1.0);
  hist->SetMarkerColor(kcolor);
  hist->SetLineColor(kcolor);
  hist->SetMarkerStyle(kstyle);
  hist->SetMarkerSize(ksize);
  hist->GetYaxis()->SetTitle(ytitle.c_str());
  hist->GetXaxis()->SetTitle(xtitle.c_str());
  hist->SetLineStyle(lstyle);
  hist->SetLineWidth(lwidth);
}

TH1D* get_stat_uncertainty_hist(TH1D *input_hist, double uncertainty = syst_uncertainty){
  
  TH1D *output_hist = (TH1D*)input_hist->Clone();
  
  for(int iBin=1; iBin<=output_hist->GetNbinsX(); iBin++){
    double value = output_hist->GetBinContent(iBin);
    output_hist->SetBinError(iBin, uncertainty * value);
  }
  
  output_hist->SetFillColorAlpha(input_hist->GetLineColor(), 0.2);
  return output_hist;
}

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
