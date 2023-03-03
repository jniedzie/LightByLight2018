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
#include "MyCanvas.C"

//const double LumiLossHotZDCneg = 0.047433369; // 1034./21799 from QED number LbyL 5Aug 2022 slides
const double LumiLossHotZDCneg = 0;

//const double luminosity       = 1635.123139823; // μb^-1
//const double luminosity       = 1639.207543; // μb^-1
//const double luminosity       = 1647.228136; // μb^-1 from Gabi Feb 13, 2022
const double luminosity       = 1561.948136; // μb^-1 from Gabi Aug, 2022, removing ZDC neg hot region 85.28 mub

const int nSample = 5;
const char *sample[nSample]={"Data","QEDSCFSR","QEDSL","QEDMG5FSROnePhton","QEDMG5FSRTwoPhton"};

int ireg(double et, double eta);
void make_canvas(TCanvas *&);
void make_canvas_ratio(TCanvas *&);
void make_hist(TH1D *&, Color_t , int );
void make_hist_ratio(TH1D *&,Color_t, int) ;

const double nEventsGeneratedSL = 66750000; // older number with less files 63398400; //starlight
const double xsecGeneratedSL    = 7920; // μb, starlight

//const double nEventsGeneratedSC = 67810000; //Superchic
const double nEventsGeneratedSC = 59260000;//Superchic + photos
const double xsecGeneratedSC    = 8827.220; // μb

double scaleFactorsSC = 0.85 *  // NEE    31.12.2021
                        0.93 *      // CHE  31.12.2021
                        pow(0.952, 2)* // electron reco+ID 05 Oct 2022 from singleEG3 only
                        1.008 *       // L1 EG trigger 05 Oct 2022 from singleEG5 only
                        0.866;  // HF veto


double scaleFactorsSL = 0.85 *  // NEE    31.12.2021
                        0.93 *      // CHE  31.12.2021
                        pow(0.952, 2)* // electron reco+ID 05 Oct 2022 from singleEG3 only
                        1.008 *       // L1 EG trigger 05 Oct 2022 from singleEG5 only
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

TCanvas* PlotHistsAndRatio(TCanvas* , TH1D* , TH1D*, TH1D*, TH1D*, TH1D*, double , double , double , double , double , double , const char *, bool); 
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


void plotQED_addUncertainty(){
 
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
  TH1D* hnVtx[nSample], *hxVtx[nSample], *hyVtx[nSample], *hzVtx[nSample], *hnRun[nSample], *hnLS[nSample], *hnEvt[nSample];//For vertex info//


  for (int i = 0; i < 1; i++){
    qed[i] = new TChain("output_tree");
    qed[i]->Add(Form("/eos/user/p/pjana/LByL/AcoRootFromRuchi/fordielectron/%s_qed.root",sample[i]));

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
    ///Vertex info
    hnVtx[i]  = new TH1D(Form("hnVtx%s", sample[i]),"",10,0,10);
    hxVtx[i]  = new TH1D(Form("hxVtx%s", sample[i]),"",96,-0.8,0.8);
    hyVtx[i]  = new TH1D(Form("hyVtx%s", sample[i]),"",96,-0.8,0.8);
    hzVtx[i]  = new TH1D(Form("hzVtx%s", sample[i]),"",40,-20,20);
    /////
    hnRun[i]  = new TH1D(Form("hnRun%s", sample[i]),"",330, 0, 330000);
    hnLS[i]  = new TH1D(Form("hnLS%s", sample[i]),"",1400, 0, 1400);
    hnEvt[i]  = new TH1D(Form("hnEvt%s", sample[i]),"",70000, 0, 700000000);

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
      if(qedR.vSum_Pt > 1) continue; //diele pt
      if(abs(qedR.eleEta_1) > 2.2) continue;
      if(abs(qedR.eleEta_2) > 2.2) continue;
      if(qedR.elePt_1 < 2.5) continue;
      if(qedR.elePt_2 < 2.5) continue;

     // float acoSF = getAcoBinSF(qedR.ele_acop); 
      float acoSF = 1; 
       if(i==0 ){  
        //if(i==0 && qedR.ok_zdcexcl_4n_pos == 1 && qedR.ok_zdcexcl_4n_neg == 1) 
        //if(i==0 && qedR.zdc_energy_pos < 10000 && qedR.zdc_energy_neg < 10000 ) 
        //if(qedR.ok_zdcexcl != 1 ) continue;  //bad ZDC negative runs removed in ok_zdcexcl variable
        }
            

      hAcop[i]->Fill(qedR.ele_acop,acoSF); 
      
      if(qedR.ele_acop > 0.01) continue; //acop

 
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
        //
        hnVtx[i]->Fill(qedR.nVtx);
        hxVtx[i]->Fill(qedR.xVtx);
        hyVtx[i]->Fill(qedR.yVtx);
        hzVtx[i]->Fill(qedR.zVtx);
        cout << "xVtx = " << qedR.xVtx << endl;
        cout << "yVtx = " << qedR.yVtx << endl;
        cout << "zVtx = " << qedR.zVtx << endl;
        hnRun[i]->Fill(qedR.run);
        cout << "nRun: " << qedR.run;
        hnLS[i]->Fill(qedR.ls);
        cout << ":" << qedR.ls;
        hnEvt[i]->Fill(qedR.evtnb);
        cout << ":" << qedR.evtnb << endl;

      
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
      //tr[i]   = (TTree*) fMC[i]->Get("trMC");

  cout << " file is opened: " << sample[i] << endl;

  const TCut acop_cut    = "ele_acop<0.01 && vSum_Pt < 1";
  
  hInvmass[i] = SFuncert(tr[i],Form("hInvmass%s",sample[i]),"vSum_M",acop_cut,50,0,100);
  hSumPt[i]   = SFuncert(tr[i],Form("hSumPt%s",sample[i]),"vSum_Pt",acop_cut,40,0,2);
  hRap[i]     = SFuncert(tr[i],Form("hRap%s",sample[i]),"vSum_Rapidity",acop_cut,24,-2.4,2.4);
  hAcop[i]    = SFuncert(tr[i],Form("hAcop%s",sample[i]),"ele_acop","vSum_Pt < 1",100,0,0.1);

  hElePt1[i]   = SFuncert(tr[i],Form("hElePt1%s",sample[i]),"elePt1",acop_cut,50,0,50);
  hElePt2[i]   = SFuncert(tr[i],Form("hElePt2%s",sample[i]),"elePt2",acop_cut,50,0,50);
  hEleEta1[i]   = SFuncert(tr[i],Form("hEleEta1%s",sample[i]),"eleEta1",acop_cut,24,-2.4,2.4);
  hEleEta2[i]   = SFuncert(tr[i],Form("hEleEta2%s",sample[i]),"eleEta2",acop_cut,24,-2.4,2.4);
  hElePhi1[i]   = SFuncert(tr[i],Form("hElePhi1%s",sample[i]),"elePhi1",acop_cut,16,-4,4);
  hElePhi2[i]   = SFuncert(tr[i],Form("hElePhi2%s",sample[i]),"elePhi2",acop_cut,16,-4,4);
  
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
   //
   TCanvas*c21 = new TCanvas();
   hxVtx[0]->Draw("HIST");
   c21->Print("xVtx.png");

   TCanvas*c20 = new TCanvas();
   hnVtx[0]->Draw("HIST");
   c20->Print("nVtx.png");

   TCanvas*c22 = new TCanvas();
   hyVtx[0]->Draw("HIST");
   c22->Print("yVtx.png");

   TCanvas*c23 = new TCanvas();
   hzVtx[0]->Draw("HIST");
   c23->Print("zVtx.png");
   //Run no
   TCanvas*c24 = new TCanvas();
   hnRun[0]->Draw("HIST");
   //LS
   TCanvas*c25 = new TCanvas();
   hnLS[0]->Draw("HIST");
   //Event no
   TCanvas*c26 = new TCanvas();
   hnEvt[0]->Draw("HIST");

   
   ///////   
   
   MyCanvas mc1("mass","Dielectron invariant mass (GeV)", "Entries / (2 GeV)", W, H);
   mc1.SetLogy(false);
   mc1.SetYRange(0.1,10000);
   mc1.SetRatioRange(0.1,1.9);
   mc1.SetLegendPosition(0.60,0.68,0.9,0.85);
   mc1.CanvasWithThreeHistogramsRatioPlot(hInvmass[0],hInvmass[1],hInvmass[2],"Data","Superchic+Photos","Starlight","Data/MC",kBlack,kBlue,kRed,kFALSE,kTRUE,kTRUE,"EP","hist SAME", "hist SAME");
   mc1.PrintCanvas();
 
 
   MyCanvas mc2("pt","Dielectron p_{T} (GeV)", "Entries / (0.5 GeV)", W, H);
   mc2.SetLogy(true);
   mc2.SetYRange(0.1,8000);
   mc2.SetXRange(0,1);
   mc2.SetRatioRange(0.1,1.9);
   mc2.SetLegendPosition(0.6,0.68,0.9,0.85);
   mc2.CanvasWithThreeHistogramsRatioPlot(hSumPt[0],hSumPt[1],hSumPt[2],"Data","Superchic+photos","Starlight","Data/MC",kBlack,kBlue,kRed,kFALSE,kTRUE,kTRUE,"EP","hist SAME", "hist SAME");
   mc2.PrintCanvas();   
   
   MyCanvas mc3("rap","Dielectron y", "Entries / (0.2)", W, H);
   mc3.SetYRange(0,5000);
   mc3.SetRatioRange(0.1,1.9);
   mc3.SetLegendPosition(0.16,0.68,0.56,0.85);
   mc3.CanvasWithThreeHistogramsRatioPlot(hRap[0],hRap[1],hRap[2],"Data","Superchic+Photos","Starlight","Data/MC",kBlack,kBlue,kRed,kFALSE,kTRUE,kTRUE,"EP","hist SAME", "hist SAME");
   mc3.PrintCanvas();
   
   MyCanvas mc4("elePt","Electron Pt", "Entries / (0.2)", W, H);
   mc4.SetLogy(false);
   mc4.SetYRange(0.1,50000);
   mc4.SetRatioRange(0.1,1.9);
   mc4.SetLegendPosition(0.6,0.68,0.9,0.85);
   mc4.CanvasWithThreeHistogramsRatioPlot(hElePt1[0],hElePt1[1],hElePt1[2],"Data","Superchic+Photos","Starlight","Data/MC",kBlack,kBlue,kRed,kFALSE,kTRUE,kTRUE,"EP","hist SAME", "hist SAME");
   mc4.PrintCanvas();

 

   MyCanvas mc5("eleEta","Electron Eta", "Entries / (0.2)", W, H);
   mc5.SetYRange(0,5000);
   mc5.SetRatioRange(0.1,1.9);
   mc5.SetLegendPosition(0.16,0.68,0.56,0.85);
   mc5.CanvasWithThreeHistogramsRatioPlot(hEleEta1[0],hEleEta1[1],hEleEta1[2],"Data","Superchic+Photos","Starlight","Data/MC",kBlack,kBlue,kRed,kFALSE,kTRUE,kTRUE,"EP","hist SAME", "hist SAME");
   mc5.PrintCanvas();



   MyCanvas mc6("elePhi","Electron Phi", "Entries / (0.2)", W, H);
   mc6.SetYRange(0,5000);
   mc6.SetRatioRange(0.1,1.9);
   mc6.SetLegendPosition(0.16,0.68,0.56,0.85);
   mc6.CanvasWithThreeHistogramsRatioPlot(hElePhi1[0],hElePhi1[1],hElePhi1[2],"Data","Superchic+Photos","Starlight","Data/MC",kBlack,kBlue,kRed,kFALSE,kTRUE,kTRUE,"EP","hist SAME", "hist SAME");
   mc6.PrintCanvas();
  

   MyCanvas mc7("acop","Dielectron acoplanarity", "Entries / (2 GeV)", W, H);
   mc7.SetLogy(false);
   mc7.SetXRange(0,0.06);
   mc7.SetYRange(0.1,100000);
   mc7.SetRatioRange(0.1,1.9);
   mc7.SetLegendPosition(0.6,0.68,0.9,0.85);
   mc7.CanvasWithThreeHistogramsRatioPlot(hAcop[0],hAcop[1],hAcop[2],"Data","Superchic+Photos","Starlight","Data/MC",kBlack,kBlue,kRed,kFALSE,kTRUE,kTRUE,"EP","hist SAME", "hist SAME");
   mc7.PrintCanvas();


  for (int i = 0; i < nSample; i++){
  cout << " Acop < 0.01 " << sample[i] <<  " :" << hAcop[i]->Integral(1,10) << endl;  
  cout << " sum pt: " << sample[i] <<  " :" << hSumPt[i]->Integral() << endl;  
 }

  
}

TH1D* SFuncert(TTree *tr, const char* name, const char* var, const char* cut, int nbins, double binmin, double binmax) {

   bool dorew  =0;
   TH1D *hvari[7];
   for (int ibin=0; ibin<7; ibin++) {
      TString namei = Form("Reco%s_%d",name,ibin);
      hvari[ibin] = new TH1D(namei,"",nbins,binmin, binmax);
 //     tr->Project(namei,var,Form("SFweightR[%d]*SFweightT[%d]*(%s)",ibin,ibin,cut));

      
   }

   /*TH1D *hvariT[17];
   for (int ibin=0; ibin<17; ibin++) {
      TString namei = Form("Trig%s_%d",name,ibin);
      hvariT[ibin] = new TH1D(namei,"",nbins,binmin, binmax);
      tr->Project(namei,var,Form("SFweightT[%d]*(%s)",ibin,cut));

      
   }*/

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
//   else tr->Project(name,var,cut); 


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

