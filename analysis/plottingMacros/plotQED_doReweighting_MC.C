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
//#include "../eta2p2/CMS_lumi.C"

const double LumiLossHotZDCneg = 0.047433369; // 1034./21799 from QED number LbyL 5Aug 2022 slides
//const double LumiLossHotZDCneg = 0; // 1034./21799 from QED number LbyL 5Aug 2022 slides



const int nSample = 5;
const char *sample[nSample]={"Data","QEDSCFSR","QEDSL","QEDMG5FSROnePhton","QEDMG5FSRTwoPhton"};

int ireg(double et, double eta);
void make_canvas(TCanvas *&);
void make_canvas_ratio(TCanvas *&);
void make_hist(TH1D *&, Color_t , int );
void make_hist_ratio(TH1D *&,Color_t, int) ;

//const double luminosity       = 1635.123139823; // μb^-1
//const double luminosity       = 1639.207543; // μb^-1
const double luminosity       = 1647.228136; // μb^-1 //update from Gabi on 12 Feb 2022
const double nEventsGeneratedSL = 66750000; // older number with less files 63398400; //starlight
const double xsecGeneratedSL    = 7920; // μb, starlight

//const double zdcFraction       = 0.838; 
const double zdcFraction       = 1; 

//const double nEventsGeneratedSC = 67810000; //Superchic
const double nEventsGeneratedSC = 59260000;//Superchic + photos
const double xsecGeneratedSC    = 8827.220; // μb

double scaleFactorsSC = 0.85 *  // NEE    31.12.2021
                        0.93 *      // CHE  31.12.2021
                        //pow(0.976, 2)* // electron reco+ID 31.12.2021
                        //1.037 *       // L1 EG trigger
                        0.866;  // HF veto


double scaleFactorsSL = 0.85 *  // NEE    31.12.2021
                        0.93 *      // CHE  31.12.2021
                        //pow(0.976, 2)* // electron reco+ID 31.12.2021
                        //1.037 *       // L1 EG trigger
                        0.866;  // HF veto



double lumiNormSC = xsecGeneratedSC*luminosity*scaleFactorsSC*(1-LumiLossHotZDCneg)/nEventsGeneratedSC;
double lumiNormSL = xsecGeneratedSL*luminosity*scaleFactorsSL*(1-LumiLossHotZDCneg)/nEventsGeneratedSL;


//estimate Madgraph QED 1 FSR normalisation factors
const double nEventsGeneratedQEDMG_1FSR = 10000000; // older number with less files 67262800 superchic 
const double xsecGeneratedQEDMG_1FSR    = 13.45; // μb
double lumiNormQEDMG_1FSR = xsecGeneratedQEDMG_1FSR*luminosity*scaleFactorsSC*(1-LumiLossHotZDCneg)/nEventsGeneratedQEDMG_1FSR;

//estimate Madgraph QED 2 FSR normalisation factors
const double nEventsGeneratedQEDMG_2FSR = 6600000; // older number with less files 67262800 superchic 
const double xsecGeneratedQEDMG_2FSR    = 0.194; // μb
double lumiNormQEDMG_2FSR = xsecGeneratedQEDMG_2FSR*luminosity*scaleFactorsSC*(1-LumiLossHotZDCneg)/nEventsGeneratedQEDMG_2FSR;

const double wt[nSample] = {1, lumiNormSC, lumiNormSL,lumiNormQEDMG_1FSR,lumiNormQEDMG_2FSR};

float getAcoBinSF(float acop);
double SFReco(double et, double eta);
double SFReco_uncert(double et, double eta);
double SFTrig(double et, double eta);

TCanvas* PlotHistsAndRatio(TCanvas* , TH1D* , TH1D*, TH1D*, TH1D*, double , double , double , double , double , double , const char *, bool); 
TH1D* SFuncert(TTree *tr, const char* name, const char* var, const char* cut, int nbins, double binmin, double binmax);

void drawText(const char *text, float xp, float yp, int size){
  TLatex *tex = new TLatex(xp,yp,text);
  tex->SetTextFont(43);
  tex->SetTextSize(size);
  tex->SetTextColor(kMagenta);
  tex->SetLineWidth(1);
  tex->SetNDC();
  tex->Draw();
}


void plotQED_doReweighting_MC(){
 
  //gROOT->LoadMacro("CMS_lumi.C");
  bool outOfFrame    = false;
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);

  TFile *outf= new TFile("output_dataSF.root","recreate");  

  TChain *qed[nSample];

  TH1D* hElePt1[nSample], *hEleEta1[nSample], *hElePhi1[nSample], *hElePt2[nSample], *hEleEta2[nSample], *hElePhi2[nSample]; 
  TH1D* hSumPt[nSample], *hRap[nSample], *hInvmass[nSample], *hAcop[nSample] ; TH1F *hSF[nSample], *hInvmass_err[nSample];
  TH1D* hCosThetaStar[nSample];
 
  TH1D* hZDCPos[nSample], *hZDCNeg[nSample];


  for (int i = 0; i < 1; i++){
    qed[i] = new TChain("output_tree");
    qed[i]->Add(Form("%s_cosThetaStar_qed.root",sample[i]));

    hElePt1[i]    = new TH1D(Form("hElePt1%s", sample[i]),"",50,0,50);
    hEleEta1[i]   = new TH1D(Form("hEleEta1%s",sample[i]),"",24,-2.4,2.4);
    hElePhi1[i]   = new TH1D(Form("hElePhi1%s",sample[i]),"",16,-4,4);

    hElePt2[i]    = new TH1D(Form("hElePt2%s", sample[i]),"",50,0,50);
    hEleEta2[i]   = new TH1D(Form("hEleEta2%s",sample[i]),"",24,-2.4,2.4);
    hElePhi2[i]   = new TH1D(Form("hElePhi2%s",sample[i]),"",16,-4,4);
 
    hSumPt[i]    = new TH1D(Form("hSumPt%s", sample[i]),"",40,0,2);
    hRap[i]   = new TH1D(Form("hRap%s",sample[i]),"",24,-2.4,2.4);
    hInvmass[i]   = new TH1D(Form("hInvmass%s",sample[i]),"",50,0,100);
    hAcop[i]   = new TH1D(Form("hAcop%s",sample[i]),"",100,0,0.1);

    hSF[i]   = new TH1F(Form("hSF%s",sample[i]),"",100,0,1.0);

    hCosThetaStar[i]   = new TH1D(Form("hCosThetaStar%s",sample[i]),"",20,0,1);
    
    hZDCPos[i]   = new TH1D(Form("hZDCPos%s",sample[i]),"",110,0,220000);
    hZDCNeg[i]   = new TH1D(Form("hZDCNeg%s",sample[i]),"",425,0,850000);

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

     // float acoSF = getAcoBinSF(qedR.ele_acop); 
      float acoSF = 1; 
      //if(i==0 && qedR.ok_zdcexcl_4n_pos == 1 && qedR.ok_zdcexcl_4n_neg == 1) hAcop[i]->Fill(qedR.ele_acop,acoSF);
      //if(i==0 && qedR.ok_zdcexcl_4n_pos == 1 ) hAcop[i]->Fill(qedR.ele_acop,acoSF);
      //if(i==0 && qedR.zdc_energy_pos < 10000 && (qedR.zdc_energy_neg < 10000 || qedR.zdc_energy_neg > 750000 ) ) hAcop[i]->Fill(qedR.ele_acop,acoSF);      
      //if(i==0 && qedR.zdc_energy_pos < 10000 && qedR.zdc_energy_neg > 750000 ) hAcop[i]->Fill(qedR.ele_acop,acoSF);
      
      if(i==0 && qedR.zdc_energy_pos < 10000 && qedR.zdc_energy_neg < 10000 ) hAcop[i]->Fill(qedR.ele_acop,acoSF);
            
     // if(i==0) hAcop[i]->Fill(qedR.ele_acop,acoSF);
      if(i>0) 	hAcop[i]->Fill(qedR.ele_acop,wt[i]);



      if(qedR.ele_acop > 0.01) continue; //acop

      
      if(i==0){
        //if(qedR.ok_zdcexcl_4n_pos == 1 && qedR.ok_zdcexcl_4n_neg == 1){
        //if(qedR.zdc_energy_pos < 10000 && (qedR.zdc_energy_neg < 10000 || qedR.zdc_energy_neg > 750000) ){
        //if(qedR.zdc_energy_pos < 10000 && qedR.zdc_energy_neg > 750000){
        if(qedR.zdc_energy_pos < 10000 && qedR.zdc_energy_neg < 10000 ){


	//cout << "Entry:" << jentry << "  " << qedR.ele_acop << "   " << acoSF << endl;
	hElePt1[i]->Fill(qedR.elePt_1,acoSF);
	hEleEta1[i]->Fill(qedR.eleEta_1,acoSF);
	hElePhi1[i]->Fill(qedR.elePhi_1,acoSF);
	
	hElePt2[i]->Fill(qedR.elePt_2,acoSF);
	hEleEta2[i]->Fill(qedR.eleEta_2,acoSF);
	hElePhi2[i]->Fill(qedR.elePhi_2,acoSF);
	
	hSumPt[i]->Fill(qedR.vSum_Pt,acoSF);
	hRap[i]->Fill(qedR.vSum_Rapidity,acoSF);
	hInvmass[i]->Fill(qedR.vSum_M,acoSF);

	hCosThetaStar[i]->Fill(abs(qedR.costhetastar),acoSF);
	hZDCPos[i]->Fill(qedR.zdc_energy_pos,acoSF);
	hZDCNeg[i]->Fill(qedR.zdc_energy_neg,acoSF);
       } //zdc cut
      }
      
    } //entry
  } // for 4 files

  for (int i = 0; i < 1; i++){    
    hElePt1[i]->Add(hElePt2[i]);
    hEleEta1[i]->Add(hEleEta2[i]);
    hElePhi1[i]->Add(hElePhi2[i]);
  }
  

    
 
  TTree *tr[nSample];   TFile *fMC[nSample];
  
  for (int i = 1; i < nSample; i++){
    
    fMC[i] = TFile::Open(Form("%s_withSFs.root",sample[i]));
      tr[i]   = (TTree*) fMC[i]->Get("trMC");

  cout << " file is opened: " << sample[i] << endl;


  hInvmass[i] = SFuncert(tr[i],Form("hInvmass%s",sample[i]),"vSum_M","ele_acop<0.01",50,0,100);
  hSumPt[i]   = SFuncert(tr[i],Form("hSumPt%s",sample[i]),"vSum_Pt","ele_acop<0.01",40,0,2);
  hRap[i]     = SFuncert(tr[i],Form("hRap%s",sample[i]),"vSum_Rapidity","ele_acop<0.01",24,-2.4,2.4);
  hAcop[i]    = SFuncert(tr[i],Form("hAcop%s",sample[i]),"ele_acop","ele_acop<0.1",100,0,0.1);

  hElePt1[i]   = SFuncert(tr[i],Form("hElePt1%s",sample[i]),"elePt1","ele_acop<0.01",50,0,50);
  hElePt2[i]   = SFuncert(tr[i],Form("hElePt2%s",sample[i]),"elePt2","ele_acop<0.01",50,0,50);
  hEleEta1[i]   = SFuncert(tr[i],Form("hEleEta1%s",sample[i]),"eleEta1","ele_acop<0.01",24,-2.4,2.4);
  hEleEta2[i]   = SFuncert(tr[i],Form("hEleEta2%s",sample[i]),"eleEta2","ele_acop<0.01",24,-2.4,2.4);
  hElePhi1[i]   = SFuncert(tr[i],Form("hElePhi1%s",sample[i]),"elePhi1","ele_acop<0.01",16,-4,4);
  hElePhi2[i]   = SFuncert(tr[i],Form("hElePhi2%s",sample[i]),"elePhi2","ele_acop<0.01",16,-4,4);
  
  hInvmass[i]->Scale(wt[i]);    hSumPt[i]->Scale(wt[i]);  hRap[i]->Scale(wt[i]); hAcop[i]->Scale(wt[i]);
  hElePt1[i]->Scale(wt[i]);    hElePt2[i]->Scale(wt[i]); hElePt1[i]->Add(hElePt2[i]);
  hEleEta1[i]->Scale(wt[i]);    hEleEta2[i]->Scale(wt[i]); hEleEta1[i]->Add(hEleEta2[i]);
  hElePhi1[i]->Scale(wt[i]);    hElePhi2[i]->Scale(wt[i]); hElePhi1[i]->Add(hElePhi2[i]);
  
  }
 
 
    


  
   int W = 700;
   int H = 600;

   float T = 0.08;
   float B = 0.14;
   float L = 0.14;
   float R = 0.04;

  TCanvas* cc1 = new TCanvas("Sum_pt","dielectron pT",254,411,639,592);
  make_canvas(cc1);
  PlotHistsAndRatio(cc1, hSumPt[0], hSumPt[1], hSumPt[3],hSumPt[4], 0.0,2.0,0.1,8000,0.5,2.0,"Dielectron p_{T}", 1);



  TCanvas* c3 = new TCanvas("Rapidity","Rapidity",254,411,639,592);
  make_canvas(c3);
  PlotHistsAndRatio(c3, hRap[0], hRap[1], hRap[3], hRap[4],-3,3,0,7000,0.7,1.3,"Rapidity", 0);

  TCanvas* c4 = new TCanvas("Electron_pt","Electron pT",254,411,639,592);
  make_canvas(c4);
  PlotHistsAndRatio(c4, hElePt1[0], hElePt1[1], hElePt1[3], hElePt1[4], 0,50,0.1,40000,0.1,1.8,"Electron p_{T}", 1);

  TCanvas* c5 = new TCanvas("Electron_eta","Electron eta",254,411,639,592);
  make_canvas(c5);
  PlotHistsAndRatio(c5, hEleEta1[0], hEleEta1[1], hEleEta1[3], hEleEta1[4], -3,3,0,7000,0.7,1.3,"Electron #eta", 0);

  TCanvas* c6 = new TCanvas("Electron_phi","Electron phi",254,411,639,592);
  make_canvas(c6);
  PlotHistsAndRatio(c6, hElePhi1[0], hElePhi1[1], hElePhi1[3],hElePhi1[4], -4,4,0,7000,0.7,1.3,"Electron #phi", 0);

  TCanvas* c2 = new TCanvas("Inv_mass","Invmass",254,411,639,592);
  make_canvas(c2);
  PlotHistsAndRatio(c2, hInvmass[0], hInvmass[1], hInvmass[3],hInvmass[4], 0,120,0.1,20000,0.6,1.4,"Invariant Mass", 1);
  
  TCanvas* c7 = new TCanvas("Acoplanarity","Acoplanarity",254,411,639,592);
  make_canvas(c7);
  PlotHistsAndRatio(c7, hAcop[0], hAcop[1], hAcop[3], hAcop[4], 0,0.1,0.01,100000,0.7,1.3,"A_{#phi}", 1);

 new TCanvas();
 make_hist(hZDCPos[0], kBlack, 20);
 hZDCPos[0]->Draw("p");
 
  new TCanvas();
  make_hist(hZDCNeg[0], kBlack, 20);
  hZDCNeg[0]->Draw("p");

  cout << "count for acop < 0.01 = " << sample[0] <<  " :" << hAcop[0]->Integral(1,10) << endl;  
  cout << "count for acop < 0.01 = " <<  sample[1] << " :" << hAcop[1]->Integral(1,10) << endl;  
  cout << "count for acop < 0.01 = " <<  sample[2] << " :" << hAcop[2]->Integral(1,10) << endl;  
  cout << "count for acop < 0.01 = " <<  sample[3] << " :" << hAcop[3]->Integral(1,10) << endl;  
  cout << "count for acop < 0.01 = " <<  sample[4] << " :" << hAcop[4]->Integral(1,10) << endl;  



  
}



TCanvas* PlotHistsAndRatio(TCanvas* c1, TH1D* hdata, TH1D* hmc, TH1D* hmc2, TH1D* hmc3, double hxmin, double hxmax, double hymin, double hymax, double rymin , double rymax, const char *ytitle, bool iflogy){
  
  float T = 0.08;
  float B = 0.14; 
  float L = 0.14;
  float R = 0.04;
  
  TString strRatio=hmc2->GetName();
  strRatio+="_over_";
  strRatio+=hmc2->GetName();
  
  TH1D* htotal=(TH1D*)hmc->Clone(strRatio);
  htotal->Sumw2();  
  htotal->Add(hmc2);

  TH1D* hratio=(TH1D*)hdata->Clone(strRatio);
  hratio->Sumw2();  
  
  hratio->Divide(htotal);
  
  //TH1D* hratio2=(TH1D*)hdata->Clone(strRatio);
  //hratio2->Sumw2();  
  
  //hratio2->Divide(hmc2);
  
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

  THStack *hs = new THStack("hs"," ");
  hs->SetMaximum(hymax);
  hs->SetMinimum(hymin);

  make_hist(hmc3, 30, 21);
  //hs->Add(hmc3);

  make_hist(hmc2, kRed, 21);
  //hs->Add(hmc2);

  make_hist(hmc, kBlue, 21);
  hs->Add(hmc);


  //hs->SetTitle("# events");

  hs->Draw("hist");   
  hs->GetYaxis()->SetTitle("# events");
  hs->GetXaxis()->SetRangeUser(hxmin,hxmax);

  /*hdata->SetTitle("");
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

      hmc2->GetXaxis()->SetNdivisions(509);

  hmc2->Draw("hist ");

  hmc->SetFillColorAlpha(kBlue, 0.464);
  //hmc->SetFillColorAlpha(kBlack, 0.2);
  hmc->Draw("histsame");

      TH1D *h2c = (TH1D*) hmc2->Clone();
      h2c->SetFillColor(kBlack);
      h2c->SetFillStyle(3005);
      h2c->SetMarkerSize(0);
      h2c->Draw("E2 SAME");*/

  hdata->GetYaxis()->SetTitle("Events");
  hdata->SetMarkerColor(kBlack);
  hdata->SetLineColor(kBlack);
  hdata->SetMarkerStyle(23);
  hdata->Draw("psame");

 // CMS_lumi( pad1, 104, 33,lumi_PbPb2018 );

  
  TLegend *leg2=new TLegend(0.35,0.70,0.60,0.9);
  leg2->SetFillColor(0);
  leg2->SetBorderSize(0);
  leg2->SetFillStyle(0);
  leg2->SetTextFont(43);
  leg2->SetTextSize(20);
  leg2->AddEntry(hdata,"Data ","pl");
  leg2->AddEntry(hmc,"Superchic + Photos","f");
  //leg2->AddEntry(hmc,"Starlight","f");
  //leg2->AddEntry(hmc2,"MG5 1 FSR","f");
  //leg2->AddEntry(hmc3,"MG5 2 FSR","f");
  
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

  /*hratio2->SetMarkerColor(kRed);
  //hratio2->SetMarkerColor(47);
  hratio2->SetMarkerStyle(22);
  hratio2->SetLineColor(kRed);
  //hratio2->Draw("psame");*/
  
  double xmin = hmc->GetXaxis()->GetXmin();
  double xmax = hmc->GetXaxis()->GetXmax();

  TLine *l1 = new TLine(xmin,1,hxmax,1);
  l1->SetLineColor(kRed);
  l1->Draw();
   

  c1->Update();
  TString cName=c1->GetName();
  cName+=".png";
  c1->SaveAs("figures/stack_SCPhotos_LumiLossHotZDCneg/"+cName);

  TString c2Name=c1->GetName();
  c2Name+=".pdf";
  c1->SaveAs("figures/stack_SCPhotos_LumiLossHotZDCneg/"+c2Name);
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
  hist->SetFillColorAlpha(kcolor,0.57);
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



TH1D* SFuncert(TTree *tr, const char* name, const char* var, const char* cut, int nbins, double binmin, double binmax) {

   bool dorew  =1;
   TH1D *hvari[7];
   for (int ibin=0; ibin<7; ibin++) {
      TString namei = Form("Reco%s_%d",name,ibin);
      hvari[ibin] = new TH1D(namei,"",nbins,binmin, binmax);
      tr->Project(namei,var,Form("SFweightR[%d]*SFweightT[%d]*(%s)",ibin,ibin,cut));

      
   }

   /*TH1D *hvariT[17];
   for (int ibin=0; ibin<17; ibin++) {
      TString namei = Form("Trig%s_%d",name,ibin);
      hvariT[ibin] = new TH1D(namei,"",nbins,binmin, binmax);
      tr->Project(namei,var,Form("SFweightT[%d]*(%s)",ibin,cut));

      
   }

   /*new TCanvas(); 
   hvari[0]->SetLineColor(kRed);
   hvari[0]->Draw("p");
   hvari[1]->SetLineColor(kMagenta);
   hvari[1]->SetLineColor(kOrange+7);
   hvari[3]->SetLineColor(40);
   hvari[4]->SetLineColor(kCyan);
   hvari[9]->SetLineColor(kBlack);*/


  // for (int ibin=1; ibin<17; ibin++)    hvari[ibin]->Draw("psame");


   TH1D *hans = new TH1D(name,"",nbins,binmin,binmax);
   if (dorew) hans = (TH1D*) hvari[0]->Clone(name);
   else tr->Project(name,var,cut); 


   for (int i=1; i<=hans->GetNbinsX(); i++) {
      double err=0; double errT = 0;
      for (int ibin=1; ibin<7; ibin++){ 
	err += pow(hvari[ibin]->GetBinContent(i)-hvari[0]->GetBinContent(i),2);
	//errT += pow(hvariT[ibin]->GetBinContent(i)-hvariT[0]->GetBinContent(i),2);

      }
      //cout << i << " +/" << err << "   " << sqrt(err) << endl;
      hans->SetBinError(i,sqrt(err+errT+pow(hans->GetBinError(i),2)));
   }

   return hans;
}

