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
#include "ReadQEDTree.C"
#include "ReadGenTree.C"
#include "TStyle.h"
#include "TPaveStats.h"
#include "TText.h"
#include "THStack.h"
#include "TCut.h"
#include "TAxis.h"
#include "TChain.h"

const int nSample = 3;
const char *sample[nSample]={"Data","QED_SC","QED_SL"};

void make_canvas(TCanvas *&);
void make_canvas_ratio(TCanvas *&);
void make_hist(TH1D *&, Color_t , int );
void make_hist_ratio(TH1D *&,Color_t, int) ;

//const double luminosity       = 1635.123139823; // μb^-1
const double luminosity       = 1639.207543; // μb^-1
const double nEventsGeneratedSL = 66750000; // older number with less files 63398400; //starlight
const double xsecGeneratedSL    = 7920; // μb, starlight

const double nEventsGeneratedSC = 67810000; // older number with less files 67262800 superchic 
const double xsecGeneratedSC    = 8827.220; // μb
const double purity = 0.96; 
double scaleFactorsSC = 0.85 *  // NEE    31.12.2021
                        0.93 *      // CHE  31.12.2021
                        pow(0.976, 2)* // electron reco+ID 31.12.2021
                        0.866 *      // HF veto
                       1.008;       // L1 EG trigger

double scaleFactorsSL = 0.85 *  // NEE    21.12.2021
  0.93 *      // CHE  31.12.2021
  pow(0.976, 2)* // electron reco+ID 31.12.2021
  0.866 *      // HF veto
  1.008;       // L1 EG trigger



double lumiNormSC = xsecGeneratedSC*luminosity*scaleFactorsSC/nEventsGeneratedSC;
double lumiNormSL = xsecGeneratedSL*luminosity*scaleFactorsSL/nEventsGeneratedSL;

const double wt[nSample] = {1, lumiNormSC, lumiNormSL};
float getAcoBinSF(float acop);


void drawText(const char *text, float xp, float yp, int size){
  TLatex *tex = new TLatex(xp,yp,text);
  tex->SetTextFont(43);
  tex->SetTextSize(size);
  tex->SetTextColor(kMagenta);
  tex->SetLineWidth(1);
  tex->SetNDC();
  tex->Draw();
}

TCanvas* PlotHistsAndRatio(TCanvas* , TH1D* , TH1D*, TH1D*, double , double , double , double , double , double , const char *, bool); 
void scaleDataAcoBins(){
 
  //gROOT->LoadMacro("CMS_lumi.C");
  bool outOfFrame    = false;
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);

  TFile *outf= new TFile("output_dataSF.root","recreate");  

  TChain *qed[nSample];

  TH1D* hele_pt[nSample], *hele_eta[nSample], *hele_phi[nSample], *hele_pt2[nSample], *hele_eta2[nSample], *hele_phi2[nSample]; 
  TH1D* hdiele_pt[nSample], *hdiele_Rapidity[nSample], *hInvmass[nSample], *hAcoplanarity[nSample] ; TH1F *hSF[nSample]; 

  TH1D* hdiele_GenPt[2], *hdiele_GenRapidity[2], *hGenInvmass[2];
  TH2D* hdiele_GenRecoPt[2], *hdiele_GenRecoRapidity[2], *hGenRecoInvmass[2];

  for (int i = 0; i < 2; i++){
    hdiele_GenPt[i]         = new TH1D(Form("hdiele_GenPt%s", sample[i+1]),"",40,0,2);
    hdiele_GenRapidity[i]   = new TH1D(Form("hdiele_GenRapidity%s",sample[i+1]),"",24,-2.4,2.4);
    hGenInvmass[i]          = new TH1D(Form("hGenInvmass%s",sample[i+1]),"",50,0,100);

    hdiele_GenRecoPt[i]         = new TH2D(Form("hdiele_GenRecoPt%s", sample[i+1]),"",40,0,2,40,0,2);
    hdiele_GenRecoRapidity[i]   = new TH2D(Form("hdiele_GenRecoRapidity%s",sample[i+1]),"",24,-2.4,2.4,24,-2.4,2.4);
    hGenRecoInvmass[i]          = new TH2D(Form("hGenRecoInvmass%s",sample[i+1]),"",50,0,100,50,0,100);

   }


  for (int i = 0; i < nSample; i++){
    qed[i] = new TChain("output_tree");
    qed[i]->Add(Form("%s_eta2p2_GenInfo.root",sample[i]));
    //if(i!=1)qed[i]->Add(Form("%s_eta2p2_GenInfo.root",sample[i]));
    //if(i==1)qed[i]->Add("QEDSC_genInfo_properChExcl.root");

    hele_pt[i]    = new TH1D(Form("hele_pt%s", sample[i]),"",50,0,50);
    hele_eta[i]   = new TH1D(Form("hele_eta%s",sample[i]),"",24,-2.4,2.4);
    hele_phi[i]   = new TH1D(Form("hele_phi%s",sample[i]),"",16,-4,4);

    hele_pt2[i]    = new TH1D(Form("hele_pt2%s", sample[i]),"",50,0,50);
    hele_eta2[i]   = new TH1D(Form("hele_eta2%s",sample[i]),"",24,-2.4,2.4);
    hele_phi2[i]   = new TH1D(Form("hele_phi2%s",sample[i]),"",16,-4,4);
 
    hdiele_pt[i]    = new TH1D(Form("hdiele_pt%s", sample[i]),"",40,0,2);
    hdiele_Rapidity[i]   = new TH1D(Form("hdiele_Rapidity%s",sample[i]),"",24,-2.4,2.4);
    hInvmass[i]   = new TH1D(Form("hInvmass%s",sample[i]),"",50,0,100);
    hAcoplanarity[i]   = new TH1D(Form("hAcoplanarity%s",sample[i]),"",50,0,0.1);

    hSF[i]   = new TH1F(Form("hSF%s",sample[i]),"",100,0,1.0);

    cout << "file " << qed[i]->GetEntries()  << endl;
    ReadQEDTree  qedR(qed[i]);
    qedR.fChain->SetBranchStatus("*",1);


    if (qedR.fChain == 0) return;
  
    Long64_t nentries = qedR.fChain->GetEntriesFast();
    cout << qed[i]->GetName() << "    " << nentries << endl;
  
    Long64_t nbytes = 0, nb = 0;
    //for (Long64_t jentry=0; jentry<10;jentry++) {
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry_evt = qedR.LoadTree(jentry);
      if (ientry_evt < 0) break;
      nb = qedR.fChain->GetEntry(jentry);   nbytes += nb;

      

      if(qedR.ok_neuexcl != 1) continue; //neutral exclusivity
      if(qedR.ok_chexcl_extrk != 1) continue; //charged exclusivity
      if(qedR.vSum_M < 5) continue; //invmass
      if(qedR.vSum_Pt > 2) continue; //diele pt
      if(abs(qedR.eleEta_1) > 2.2) continue;
      if(abs(qedR.eleEta_2) > 2.2) continue;

        float sf = getAcoBinSF(qedR.ele_acop);
       if(i==0)hAcoplanarity[i]->Fill(qedR.ele_acop,sf);
       if(i>0) hAcoplanarity[i]->Fill(qedR.ele_acop,wt[i]);
      if(qedR.ele_acop > 0.01) continue; //acop

	    
      //cout << "Acoplanarity :" << qedR.ele_acop <<  endl;

    
	

      if(i==0){hSF[i]->Fill(sf); 
	  //cout << qedR.ele_acop << "   " << sf << endl;
 	   hele_pt[i]->Fill(qedR.elePt_1,sf);
	    hele_eta[i]->Fill(qedR.eleEta_1,sf);
	    hele_phi[i]->Fill(qedR.elePhi_1,sf);
	    
	    hele_pt2[i]->Fill(qedR.elePt_2,sf);
	    hele_eta2[i]->Fill(qedR.eleEta_2,sf);
	    hele_phi2[i]->Fill(qedR.elePhi_2,sf);
	    
	    hdiele_pt[i]->Fill(qedR.vSum_Pt,sf);
	    hdiele_Rapidity[i]->Fill(qedR.vSum_Rapidity,sf);
	    hInvmass[i]->Fill(qedR.vSum_M,sf);

        }

        if(i>0){
	hele_pt[i]->Fill(qedR.elePt_1,wt[i]);
	hele_eta[i]->Fill(qedR.eleEta_1,wt[i]);
	hele_phi[i]->Fill(qedR.elePhi_1,wt[i]);
	
	hele_pt2[i]->Fill(qedR.elePt_2,wt[i]);
	hele_eta2[i]->Fill(qedR.eleEta_2,wt[i]);
	hele_phi2[i]->Fill(qedR.elePhi_2,wt[i]);
	
	hdiele_pt[i]->Fill(qedR.vSum_Pt,wt[i]);
	hdiele_Rapidity[i]->Fill(qedR.vSum_Rapidity,wt[i]);
	hInvmass[i]->Fill(qedR.vSum_M,wt[i]);
      } //if not data
      
    } //entry
  } // for 4 files
  
  for (int i = 0; i < nSample; i++){    hele_pt[i]->Add(hele_pt2[i]);
    hele_eta[i]->Add(hele_eta2[i]);
    hele_phi[i]->Add(hele_phi2[i]);
  }
  
  int W = 700;
  int H = 600;
  
  float T = 0.08;
  float B = 0.14; 
  float L = 0.14;
  float R = 0.04;

  //hInvmass[0]->Draw("p");
  
  TCanvas* cc1 = new TCanvas("Sum_pt","dielectron pT",254,411,639,592);
  make_canvas(cc1);
  PlotHistsAndRatio(cc1, hdiele_pt[0], hdiele_pt[1], hdiele_pt[2], 0.0,2.0,0,4500,0.7,1.8,"Dielectron p_{T}", 0);

  TCanvas* c2 = new TCanvas("Inv_mass","Invmass",254,411,639,592);
  make_canvas(c2);
  PlotHistsAndRatio(c2, hInvmass[0], hInvmass[1], hInvmass[2], 0,120,0.1,10000,0.6,1.4,"Invariant Mass", 1);

  TCanvas* c3 = new TCanvas("Rapidity","Rapidity",254,411,639,592);
  make_canvas(c3);
  PlotHistsAndRatio(c3, hdiele_Rapidity[0], hdiele_Rapidity[1], hdiele_Rapidity[2], -3,3,0,3500,0.7,1.3,"Rapidity", 0);

  TCanvas* c4 = new TCanvas("Electron_pt","Electron pT",254,411,639,592);
  make_canvas(c4);
  PlotHistsAndRatio(c4, hele_pt[0], hele_pt[1], hele_pt[2], 0,50,0.1,40000,0.7,1.3,"Electron p_{T}", 1);

  TCanvas* c5 = new TCanvas("Electron_eta","Electron eta",254,411,639,592);
  make_canvas(c5);
  PlotHistsAndRatio(c5, hele_eta[0], hele_eta[1], hele_eta[2], -3,3,0,5000,0.7,1.3,"Electron #eta", 0);

  TCanvas* c6 = new TCanvas("Electron_phi","Electron phi",254,411,639,592);
  make_canvas(c6);
  PlotHistsAndRatio(c6, hele_phi[0], hele_phi[1], hele_phi[2], -4,4,0,5000,0.7,1.3,"Electron #phi", 0);


  TCanvas* c7 = new TCanvas("Acoplanarity","Acoplanarity",254,411,639,592);
  make_canvas(c7);
  PlotHistsAndRatio(c7, hAcoplanarity[0], hAcoplanarity[1], hAcoplanarity[2], 0,0.6,0.9,100000,0.7,1.3,"A_{#phi}", 1);
  
 /*  TLegend *leg1=new TLegend(0.75,0.70,0.98,0.87);
     leg1->SetFillColor(0);
     leg1->SetBorderSize(0);
     leg1->SetFillStyle(0);
     leg1->SetTextFont(43);
     leg1->SetTextSize(24);
     leg1->AddEntry(hacoplanarity[2],"Data ","pl");
     leg1->AddEntry(hacoplanarity[0],"Superchic","f");
     leg1->AddEntry(hacoplanarity[1],"Starlight","f");


     /// dielectron acoplanarity ...........................................
     TCanvas* c10 = new TCanvas("c10","acoplanarity n-1",50,50,W,H);
     make_canvas(c10);
     c10->cd();
     gPad->SetLogy();
     hacoplanarity[0]->SetMinimum(0.1);  
     //make_hist(hacoplanarity[1], kYellow, 21);
     //hacoplanarity[1]->Draw("hist");   
     hacoplanarity[1]->GetXaxis()->SetTitle("e^{+}e^{-} acoplanarity");//,"dN/dp_{T}^{2} (1/GeV)^{2} 
     hacoplanarity[1]->GetXaxis()->SetNdivisions(509);
     hacoplanarity[1]->GetXaxis()->SetRangeUser(0,0.1);
     hacoplanarity[1]->GetYaxis()->SetTitle("Events");

     hacoplanarity[1]->SetFillColorAlpha(kRed,0.2);
     hacoplanarity[1]->Draw("hist");

     hacoplanarity[0]->SetFillColorAlpha(kBlack, 0.2);
     hacoplanarity[0]->Draw("histsame");


     hacoplanarity[2]->SetMarkerColor(kBlack);
     hacoplanarity[2]->SetLineColor(kBlack);
     hacoplanarity[2]->SetMarkerStyle(23);
     hacoplanarity[2]->Draw("psame");



     leg1->Draw();
     //CMS_lumi( c10, 104, 10,lumi_PbPb2015 );
     c10->Print("./figures_eta2p2_dielePt2/acoplanarity.gif");
     c10->Print("./figures_eta2p2_dielePt2/acoplanarity.pdf");

     new TCanvas();
     hInvmassPt[2]->Draw("colz");*/


  // cout << " Max: " << hInvmass[2]->GetXaxis()->GetXmax() << "   Min:" << hInvmass[2]->GetXaxis()->GetXmin() << endl;
  cout << " invariant mass " << sample[0] <<  " :" << hInvmass[0]->Integral() << endl;  
  cout << " invariant mass " << sample[1] <<  " :" << hInvmass[1]->Integral() << endl;  
  cout << " invariant mass " << sample[2] <<  " :" << hInvmass[2]->Integral() << endl;  
  //outf->cd();
  //outf->Write();
  //outf->Close();
  
   /*hacoplanarity[0]->Write();
    hacoplanarity[2]->Write();
    hacoplanarity[1]->Write();*/

  
}


TCanvas* PlotHistsAndRatio(TCanvas* c1, TH1D* hdata, TH1D* hmc, TH1D* hmc2, double hxmin, double hxmax, double hymin, double hymax, double rymin , double rymax, const char *ytitle, bool iflogy){
  
  float T = 0.08;
  float B = 0.14; 
  float L = 0.14;
  float R = 0.04;
  
  TString strRatio=hmc2->GetName();
  strRatio+="_over_";
  strRatio+=hmc2->GetName();
  
  TH1D* hratio=(TH1D*)hdata->Clone(strRatio);
  hratio->Sumw2();  
  
  hratio->Divide(hmc);
  
  TH1D* hratio2=(TH1D*)hdata->Clone(strRatio);
  hratio2->Sumw2();  
  
  hratio2->Divide(hmc2);
  
  c1->Divide(1,2);
  TPad* pad1 = (TPad*)c1->GetPad(1);
  TPad* pad2 = (TPad*)c1->GetPad(2);
  pad1->SetPad(0,0.3,1.0,1.0);
  pad2->SetPad(0,0,  1.0,0.28);
  pad1->SetLeftMargin(0.18);
  pad1->SetTopMargin(0.08);
  pad1->SetRightMargin(0.07);
  pad1->SetBottomMargin(0.01); // All X axis labels and titles are thus cut off
  pad2->SetLeftMargin(0.18);
  pad2->SetTopMargin(0.01);
  pad2->SetRightMargin(0.07);
  pad2->SetBottomMargin(0.45);
  
  pad1->cd();
  if(iflogy)pad1->SetLogy(); 
  hdata->SetTitle("");
  hmc2->SetTitle("");
  hmc2->GetXaxis()->SetRangeUser(hxmin,hxmax);
  hmc2->GetYaxis()->SetRangeUser(hymin,hymax);
  hmc2->SetLabelColor(1, "XYZ");
  hmc2->SetLabelFont(42, "XYZ");
  hmc2->SetLabelOffset(0.007, "XYZ");
  hmc2->SetLabelSize(0.06, "XYZ");
  hmc2->GetYaxis()->SetTitleSize(0.07);
  hmc2->GetYaxis()->SetTitle("Events");

  hmc2->SetFillColorAlpha(kRed,0.571);
  //hmc2->SetFillColorAlpha(kRed,0.2);
  hmc2->Draw("hist");

  hmc->SetFillColorAlpha(kBlue, 0.464);
  //hmc->SetFillColorAlpha(kBlack, 0.2);
  hmc->Draw("histsame");


  hdata->SetMarkerColor(kBlack);
  hdata->SetLineColor(kBlack);
  hdata->SetMarkerStyle(23);
  hdata->Draw("psame");


  
  TLegend *leg2=new TLegend(0.65,0.75,0.98,0.9);
  leg2->SetFillColor(0);
  leg2->SetBorderSize(0);
  leg2->SetFillStyle(0);
  leg2->SetTextFont(43);
  leg2->SetTextSize(20);
  leg2->AddEntry(hdata,"Data ","pl");
  leg2->AddEntry(hmc,"Superchic","f");
  leg2->AddEntry(hmc2,"Starlight","f");
  
  leg2->Draw();
  
  pad2->cd();
  pad2->SetGridy(1);
  hratio->SetLineWidth(2);
  //hratio->SetStats(0);
  hratio->GetXaxis()->SetRangeUser(hxmin,hxmax);
  hratio->GetYaxis()->SetRangeUser(rymin,rymax);
  //hratio->GetXaxis()->SetTitle("Dielectron p_{T}");
  hratio->GetXaxis()->SetTitle(ytitle);
  hratio->GetYaxis()->SetTitle("Data/MC");
  hratio->GetYaxis()->SetNdivisions(504);
  hratio->GetYaxis()->SetLabelSize(0.11);
  hratio->GetXaxis()->SetLabelSize(0.15);
  hratio->GetXaxis()->SetTitleSize(0.18);
  hratio->GetYaxis()->SetTitleSize(0.15);
  hratio->GetXaxis()->SetTitleOffset(1.1);
  hratio->GetYaxis()->SetTitleOffset(0.31);
  hratio->GetXaxis()->SetTickLength(0.09);
  //hratio->SetMarkerColor(33);
  hratio->SetMarkerColor(kBlue);
  //hratio->SetMarkerStyle(23);
  hratio->SetLineColor(kBlue);
  hratio->Draw("p");

  hratio2->SetMarkerColor(kRed);
  //hratio2->SetMarkerColor(47);
  hratio2->SetMarkerStyle(22);
  hratio2->SetLineColor(kRed);
  hratio2->Draw("psame");
  
  double xmin = hmc->GetXaxis()->GetXmin();
  double xmax = hmc->GetXaxis()->GetXmax();

  TLine *l1 = new TLine(xmin,1,hxmax,1);
  l1->SetLineColor(kRed);
  l1->Draw();
   


  TString cName=c1->GetName();
  cName+=".png";
  c1->SaveAs("figures_eta2p2_dielePt2_acoSF/"+cName);
  TString c2Name=c1->GetName();
  c2Name+=".pdf";
  c1->SaveAs("figures_eta2p2_dielePt2_acoSF/"+c2Name);
  return c1;
}
  

void make_canvas(TCanvas *& canvas){

  int W = 600;
  int H = 670;
  float T = 0.08;
  float B = 0.14; 
  float L = 0.18;
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

void make_canvas_ratio(TCanvas *& can){

  int W = 700;
  int H = 600;
  float T = 0.08;
  float B = 0.14; 
  float L = 0.14;
  float R = 0.04;

  can->SetFillColor(0);
  can->SetBorderMode(0);
  can->SetFrameFillStyle(0);
  can->SetFrameBorderMode(0);
  can->SetLeftMargin( L );
  can->SetRightMargin( R );
  can->SetTopMargin( T );
  can->SetBottomMargin( B );
  can->SetTickx(0);
  can->SetTicky(0);
}


void make_hist(TH1D *& hist, Color_t kcolor, int kstyle){
  // For the axis labels:
  hist->SetLabelColor(1, "XYZ");
  hist->SetLabelFont(42, "XYZ");
  hist->SetLabelOffset(0.007, "XYZ");
  hist->SetLabelSize(0.05, "XYZ");
 
  hist->SetMarkerColor(kcolor);
  hist->SetFillColor(kcolor);
  hist->SetMarkerStyle(kstyle);
 
}

void make_hist_ratio(TH1D *& hist, Color_t kcolor, int kstyle){
  // For the axis labels:
  hist->SetLabelColor(1, "XYZ");
  hist->SetLabelFont(42, "XYZ");
  hist->SetLabelOffset(0.007, "XYZ");
  hist->SetLabelSize(0.1, "XYZ");

  // For the axis titles:
  hist->SetTitleFont(42, "XYZ");
  hist->SetTitleSize(0.11, "XYZ");
  hist->GetXaxis()->SetTitleOffset(1.1);
  hist->GetYaxis()->SetTitleOffset(0.4);
  hist->SetMarkerColor(kcolor);
  hist->SetFillColor(kcolor);
  hist->SetMarkerStyle(kstyle);
 
}


float getAcoBinSF(float acop) {
      if (acop<0.002) return 0.990761;
      else if (acop<0.004) return 0.962675;
      else if (acop<0.006) return 0.861166;
      else if (acop<0.008) return 0.598683;
      else if (acop<0.01) return 0.264046;    
      else return 1;
   
}

