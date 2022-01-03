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

void make_hist(TH1D *&, const char *, const char *, int, float, Color_t, int, int) ;
const char *dir  = "fig_UnfoldingSC";
void printBinCont(TH1D *hist);

void draw_unfold(int method =1)
{

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
  //TFile *f1= new TFile(Form("unfolding_QEDSL_histograms_%s.root",MethID1),"r");  
  cout<<"   "<<f1->GetName()<<endl; 


   
   
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


  TH1D *hMuMu_invmass_gen          = (TH1D*)f1->Get("hGenInvmass_xSec");
  TH1D *hMuMu_invmass_recomc       = (TH1D*)f1->Get("hRecoMCInvmass_xSec");
  TH1D *hMuMu_invmass_recodata     = (TH1D*)f1->Get("hRecoDataInvmass_xSec");
  TH1D *hMuMu_invmass_unfodata     = (TH1D*)f1->Get("hUnfoDataInvmass_xSec");
  TH1D *hMuMu_invmass_unfomc       = (TH1D*)f1->Get("hUnfoMCInvmass_xSec");

  
  

 
  cout<<"ok"<<endl; 

  TLegend *leg1=new TLegend(0.60,0.72,0.90,0.9);
  leg1->SetFillColor(0);
  leg1->SetBorderSize(0);
  leg1->SetFillStyle(0);
  leg1->SetTextFont(43);
  leg1->SetTextSize(24);
  leg1->AddEntry(hMuMu_pt_unfomc,MethID1,"pl");
  leg1->AddEntry(hMuMu_pt_gen,"Gen Superchic ","pl");
  leg1->AddEntry(hMuMu_pt_recomc,"Reco MC Superchic","pl");

  TLegend *leg2=new TLegend(0.60,0.68,0.90,0.9);
  leg2->SetFillColor(0);
  leg2->SetBorderSize(0);
  leg2->SetFillStyle(0);
  leg2->SetTextFont(43);
  leg2->SetTextSize(24);
  leg2->AddEntry(hMuMu_pt_unfodata,MethID1,"pl");
  leg2->AddEntry(hMuMu_pt_gen,"Gen Superchic","pl");
  leg2->AddEntry(hMuMu_pt_recomc,"Reco MC Superchic","pl");
  leg2->AddEntry(hMuMu_pt_recodata,"Reco Data","pl");


   
  int W = 600;
  int H = 500;
  
  float T = 0.08;
  float B = 0.14; 
  float L = 0.14;
  float R = 0.04;

  TCanvas* c1 = new TCanvas("c1","dielectron pT",50,50,W,H);
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
  c1->cd();
  gPad->SetLogy();
  hMuMu_pt_unfomc->SetMaximum(2*pow(10.,4.));
  hMuMu_pt_unfomc->SetMinimum(5*pow(10.,-2.));
  make_hist(hMuMu_pt_unfomc,"dielectron p_{T} (GeV/c)","d#sigma/dp_{T} (#mub/GeV/c)",20,1.0,kRed,1,1);
  hMuMu_pt_unfomc->Draw("p");
  make_hist(hMuMu_pt_gen,"dielectron p_{T} (GeV/c)","d#sigma/dp_{T} (#mub/GeV/c)",20,1.0,kGreen,1,2);
  hMuMu_pt_gen->Draw("histsame");

  make_hist(hMuMu_pt_recomc,"dielectron p_{T} (GeV/c)","d#sigma/dp_{T} (#mub/GeV/c)",20,1.0,kBlue,1,2);
  hMuMu_pt_recomc->Draw("histsame");
  
  //CMS_lumi( c1, 1, 10 );
  leg1->Draw();
  c1->Print(Form("./%s/closure_pt_%s.gif",dir,MethID1));
  c1->Print(Form("./%s/closure_pt_%s.pdf",dir,MethID1));
  

  TCanvas* c2 = new TCanvas("c2","dielectron pT",50,50,W,H);
  c2->SetFillColor(0);
  c2->SetBorderMode(0);
  c2->SetFrameFillStyle(0);
  c2->SetFrameBorderMode(0);
  c2->SetLeftMargin( L );
  c2->SetRightMargin( R );
  c2->SetTopMargin( T );
  c2->SetBottomMargin( B );
  c2->SetTickx(0);
  c2->SetTicky(0);
  c2->cd();
   //gPad->SetLogy();
  //hMuMu_pt_unfodata->SetMaximum(60);
  //hMuMu_pt_unfodata->SetMinimum(0);
  gPad->SetLogy();
  hMuMu_pt_unfodata->SetMaximum(2*pow(10.,4.));
  hMuMu_pt_unfodata->SetMinimum(5*pow(10.,-2.));
  make_hist(hMuMu_pt_unfodata,"dielectron p_{T} (GeV/c)","d#sigma/dp_{T} (#mub/GeV/c)",20,1.0,kRed,1,2);
  hMuMu_pt_unfodata->Draw("p");
  hMuMu_pt_gen->Draw("histsame");
  hMuMu_pt_recomc->Draw("ehistsame");
  make_hist(hMuMu_pt_recodata,"dielectron p_{T} (GeV/c)","d#sigma/dp_{T} (#mub/GeV/c)",22,1.0,kBlack,1,2);
  hMuMu_pt_recodata->Draw("ehistsame");
  
  //CMS_lumi( c2, 1, 10 );
  leg2->Draw();
  c2->Print(Form("./%s/data_pt_%s.gif",dir,MethID1));
  c2->Print(Form("./%s/data_pt_%s.pdf",dir,MethID1));


  TCanvas* c3 = new TCanvas("c3","dielectron rapidity",50,50,W,H);
  c3->SetFillColor(0);
  c3->SetBorderMode(0);
  c3->SetFrameFillStyle(0);
  c3->SetFrameBorderMode(0);
  c3->SetLeftMargin( L );
  c3->SetRightMargin( R );
  c3->SetTopMargin( T );
  c3->SetBottomMargin( B );
  c3->SetTickx(0);
  c3->SetTicky(0);
  c3->cd();
  
  hMuMu_rapidity_unfomc->SetMaximum(100);
  hMuMu_rapidity_unfomc->SetMinimum(0);
  //hMuMu_rapidity_unfomc->GetXaxis()->SetRangeUser(0,1.0); 
  make_hist(hMuMu_rapidity_unfomc,"dielectron y","d#sigma/dy (#mub)",20,1.0,kRed,1,1);
  hMuMu_rapidity_unfomc->Draw("p");
  make_hist(hMuMu_rapidity_gen,"dielectron y","d#sigma/dy (#mub)",20,1.0,kGreen,1,2);
  hMuMu_rapidity_gen->Draw("histsame");

  make_hist(hMuMu_rapidity_recomc,"dielectron y","d#sigma/dy (#mub)",20,1.0,kBlue,1,2);
  hMuMu_rapidity_recomc->Draw("histsame");
  
  //CMS_lumi( c3, 1, 10 );
  leg1->Draw();
  c3->Print(Form("./%s/closure_rapidity_%s.gif",dir,MethID1));
  c3->Print(Form("./%s/closure_rapidity_%s.pdf",dir,MethID1));


  TCanvas* c4 = new TCanvas("c4","dielectron rap",50,50,W,H);
  c4->SetFillColor(0);
  c4->SetBorderMode(0);
  c4->SetFrameFillStyle(0);
  c4->SetFrameBorderMode(0);
  c4->SetLeftMargin( L );
  c4->SetRightMargin( R );
  c4->SetTopMargin( T );
  c4->SetBottomMargin( B );
  c4->SetTickx(0);
  c4->SetTicky(0);
  c4->cd();
  
  hMuMu_rapidity_unfodata->SetMaximum(100);
  hMuMu_rapidity_unfodata->SetMinimum(0);
  make_hist(hMuMu_rapidity_unfodata,"dielectron y","d#sigma/dy (#mub)",20,1.0,kRed,1,2);
  hMuMu_rapidity_unfodata->Draw("p");
  hMuMu_rapidity_gen->Draw("histsame");
  hMuMu_rapidity_recomc->Draw("ehistsame");
  make_hist(hMuMu_rapidity_recodata,"dielectron y","d#sigma/dy (#mub)",22,1.0,kBlack,1,2);
  hMuMu_rapidity_recodata->Draw("ehistsame");
  
  //CMS_lumi( c4, 1, 10 );
  leg2->Draw();
  c4->Print(Form("./%s/data_rapidity_%s.gif",dir,MethID1));
  c4->Print(Form("./%s/data_rapidity_%s.pdf",dir,MethID1));
 



  //invmass
 TCanvas* c5 = new TCanvas("c5","dielectron invmass",50,50,W,H);
  c5->SetFillColor(0);
  c5->SetBorderMode(0);
  c5->SetFrameFillStyle(0);
  c5->SetFrameBorderMode(0);
  c5->SetLeftMargin( L );
  c5->SetRightMargin( R );
  c5->SetTopMargin( T );
  c5->SetBottomMargin( B );
  c5->SetTickx(0);
  c5->SetTicky(0);
  c5->cd();
  gPad->SetLogy(); 
  hMuMu_invmass_unfomc->SetMaximum(100);
  hMuMu_invmass_unfomc->SetMinimum(0.001);
  //hMuMu_invmass_unfomc->GetXaxis()->SetRangeUser(0,1.0); 
  make_hist(hMuMu_invmass_unfomc,"dielectron Invmass","d#sigma/dm (#mub/Gev)",20,1.0,kRed,1,1);
  hMuMu_invmass_unfomc->Draw("p");
  make_hist(hMuMu_invmass_gen,"dielectron Invmass","d#sigma/dm (#mub/Gev)",20,1.0,kGreen,1,2);
  hMuMu_invmass_gen->Draw("histsame");

  make_hist(hMuMu_invmass_recomc,"dielectron Invmass","d#sigma/dm (#mub/Gev)",20,1.0,kBlue,1,2);
  hMuMu_invmass_recomc->Draw("histsame");
  
  //CMS_lumi( c5, 1, 10 );
  leg1->Draw();
  c5->Print(Form("./%s/closure_invmass_%s.gif",dir,MethID1));
  c5->Print(Form("./%s/closure_invmass_%s.pdf",dir,MethID1));



  TCanvas* c6 = new TCanvas("c6","dielectron invmass",50,50,W,H);
  c6->SetFillColor(0);
  c6->SetBorderMode(0);
  c6->SetFrameFillStyle(0);
  c6->SetFrameBorderMode(0);
  c6->SetLeftMargin( L );
  c6->SetRightMargin( R );
  c6->SetTopMargin( T );
  c6->SetBottomMargin( B );
  c6->SetTickx(0);
  c6->SetTicky(0);
  c6->cd();
   gPad->SetLogy();
  hMuMu_invmass_unfodata->SetMaximum(100);
  hMuMu_invmass_unfodata->SetMinimum(0.001);
  make_hist(hMuMu_invmass_unfodata,"dielectron Invmass","d#sigma/dm (#mub/Gev)",20,1.0,kRed,1,2);
  hMuMu_invmass_unfodata->Draw("p");
  hMuMu_invmass_gen->Draw("histsame");
  hMuMu_invmass_recomc->Draw("ehistsame");
  make_hist(hMuMu_invmass_recodata,"dielectron Invmass","d#sigma/dm (#mub/Gev)",22,1.0,kBlack,1,2);
  hMuMu_invmass_recodata->Draw("ehistsame");
  
  //CMS_lumi( c6, 1, 10 );
  leg2->Draw();
  c5->Print(Form("./%s/data_invmass_%s.gif",dir,MethID1));
  c5->Print(Form("./%s/data_invmass_%s.pdf",dir,MethID1));

  //printBinCont(hMuMu_pt_unfodata);
  //printBinCont(hMuMu_rapidity_unfodata);
  //printBinCont(hMuMu_invmass_unfodata);
 
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
  tex->SetTextColor(kBlack);
  tex->SetLineWidth(1);
  tex->SetNDC();
  tex->Draw();
}

void make_hist(TH1D *& hist, const char *xtitle, const char *ytitle, int kstyle, float ksize, Color_t kcolor, int lstyle, int lwidth){
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
  hist->GetYaxis()->SetTitle(ytitle); 
  hist->GetXaxis()->SetTitle(xtitle);
  hist->SetLineStyle(lstyle);
  hist->SetLineWidth(lwidth);
 
}
