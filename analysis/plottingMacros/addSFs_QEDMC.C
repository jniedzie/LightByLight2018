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
#include "../eta2p2/CMS_lumi.C"

const int nSample = 5;
const char *sample[nSample]={"QEDSC","QEDSL","QEDSCFSR","QEDMG5FSROnePhton","QEDMG5FSRTwoPhton"};


int ireg(double et, double eta);

const double wt[nSample] = {1};//, lumiNormSC, lumiNormSL};
float getAcoBinSF(float acop);
double SFReco(double et, double eta);
double SFReco_uncert(double et, double eta);
double SFTrig(double et, double eta);
double SFTrig_uncert(double et, double eta);

TH1D* SFuncert(TTree *tr, const char* name, const char* var, const char* cut, int nbins, double binmin, double binmax, float* sf);

void drawText(const char *text, float xp, float yp, int size){
  TLatex *tex = new TLatex(xp,yp,text);
  tex->SetTextFont(43);
  tex->SetTextSize(size);
  tex->SetTextColor(kMagenta);
  tex->SetLineWidth(1);
  tex->SetNDC();
  tex->Draw();
}

float  elePt1;
float  eleEta1;
float  elePhi1;
float  elePt2;
float  eleEta2;
float  elePhi2;

float vSum_M;
float vSum_Pt;
float vSum_Rapidity;
float ele_acop;
float costhetastar;

int ok_acop;
float SFweightR[7];
float SFweightT[7];

/// initialise tree
void InitTree(TTree *tr) {
  tr->Branch("elePt1",             &elePt1,       "elePt1/F");
  tr->Branch("eleEta1",            &eleEta1,      "eleEta1/F");
  tr->Branch("elePhi1",            &elePhi1,      "elePhi1/F");
  tr->Branch("elePt2",             &elePt2,       "elePt2/F");
  tr->Branch("eleEta2",            &eleEta2,      "eleEta2/F");
  tr->Branch("elePhi2",            &elePhi2,      "elePhi2/F");

  tr->Branch("vSum_M",              &vSum_M,       "vSum_M/F");
  tr->Branch("vSum_Pt",             &vSum_Pt,      "vSum_Pt/F");
  tr->Branch("vSum_Rapidity",       &vSum_Rapidity,"vSum_Rapidity/F");
  tr->Branch("ele_acop",            &ele_acop,        "ele_acop/F");
  tr->Branch("costhetastar",        &costhetastar,        "costhetastar/F");
  tr->Branch("ok_acop",             &ok_acop,   "ok_acop/I");

  tr->Branch("SFweightR",            SFweightR,"SFweightR[7]/F");
  tr->Branch("SFweightT",            SFweightT,"SFweightT[7]/F");

}

// reset all variables
void ResetVars() {

  elePt1= 0 ;
  eleEta1= 0 ;
  elePhi1= 0 ;
  elePt2= 0 ;
  eleEta2= 0 ;
  elePhi2= 0 ;

  vSum_M = 0 ;
  vSum_Pt = 0 ;
  vSum_Rapidity = 0 ;

  ele_acop = 0;
  costhetastar = -999;
  ok_acop = 0;
}

void addSFs_QEDMC(){
 
  //gROOT->LoadMacro("CMS_lumi.C");
  bool outOfFrame    = false;
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);

  TFile *outf[nSample];






  TChain *qed[nSample];

  for (int i = 0; i < nSample; i++){
    outf[i] = new TFile(Form("%s_withSFs.root",sample[i]),"recreate");  
  
    TTree *tr = new TTree("trMC","");
    InitTree(tr);


    qed[i] = new TChain("output_tree");
    qed[i]->Add(Form("%s_cosThetaStar_qed.root",sample[i]));

    cout << "file " << qed[i]->GetEntries()  << endl;
    ReadQEDTree qedR(qed[i]);
    qedR.fChain->SetBranchStatus("*",1);


    if (qedR.fChain == 0) return;
  
    Long64_t nentries = qedR.fChain->GetEntriesFast();
    cout << qed[i]->GetName() << "    " << nentries << endl;
  
    Long64_t nbytes = 0, nb = 0;

    //for (Long64_t jentry=0; jentry<100;jentry++) {
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry_evt = qedR.LoadTree(jentry);
      if (ientry_evt < 0) break;
      nb = qedR.fChain->GetEntry(jentry);   nbytes += nb;

      ResetVars();  

      if(qedR.ok_neuexcl != 1) continue; //neutral exclusivity
      if(qedR.ok_chexcl_extrk != 1) continue; //charged exclusivity
      if(qedR.vSum_M < 5) continue; //invmass
      if(qedR.vSum_Pt > 2) continue; //diele pt
      if(abs(qedR.eleEta_1) > 2.2) continue;
      if(abs(qedR.eleEta_2) > 2.2) continue;
      if(qedR.elePt_1 < 2.5) continue;
      if(qedR.elePt_2 < 2.5) continue;

      ok_acop = qedR.ele_acop < 0.01 ;

      elePt1  = qedR.elePt_1 ;
      eleEta1 = qedR.eleEta_1 ;
      elePhi1 = qedR.elePhi_1 ;
      elePt2  = qedR.elePt_2 ;
      eleEta2 = qedR.eleEta_2 ;
      elePhi2 = qedR.elePhi_2 ;
      
      vSum_M = qedR.vSum_M ;
      vSum_Pt = qedR.vSum_Pt ;
      vSum_Rapidity = qedR.vSum_Rapidity ;
      
      ele_acop = qedR.ele_acop;
      costhetastar = qedR.costhetastar;
      
      // reco+ID scale factor   
      double sf1_reco = SFReco(qedR.elePt_1, qedR.eleEta_1);
      double sf2_reco = SFReco(qedR.elePt_2, qedR.eleEta_2);
      SFweightR[0] = sf1_reco*sf2_reco;
      
      for (int ivar=1; ivar<7; ivar++) {
	double sf1p=sf1_reco, sf2p=sf2_reco;
	if (ireg(qedR.elePt_1, qedR.eleEta_1)==ivar) sf1p += SFReco_uncert(qedR.elePt_1, qedR.eleEta_1);
	if (ireg(qedR.elePt_2, qedR.eleEta_2)==ivar) sf2p += SFReco_uncert(qedR.elePt_2, qedR.eleEta_2);
	SFweightR[ivar] = sf1p*sf2p;
      }
      
      
      
      
      // trigger scale factor
      double sf1 = SFTrig(qedR.eleSCEt_1, qedR.eleSCEta_1);
      double sf2 = SFTrig(qedR.eleSCEt_2, qedR.eleSCEta_2);
      SFweightT[0] = sf1*sf2;
	
	for (int ivar=1; ivar<7; ivar++) {
	double sf1p=sf1, sf2p=sf2;
	if (ireg(qedR.eleSCEt_1, qedR.eleSCEta_1)==ivar) sf1p += SFTrig_uncert(qedR.eleSCEt_1, qedR.eleSCEta_1);
	if (ireg(qedR.eleSCEt_2, qedR.eleSCEta_2)==ivar) sf2p += SFTrig_uncert(qedR.eleSCEt_2, qedR.eleSCEta_2);
	SFweightT[ivar] = sf1p*sf2p;
	}
      
    
      tr->Fill();
      
    } //entry

  
  
  outf[i]->cd();
  outf[i]->Write();
  outf[i]->Close();
  } // for 4 files
  
 
}


//single EG3 SFs reco
double SFReco(double et, double eta) {
   if (fabs(eta)<1.5) {
      if (et<3) return 0.958607;
      else if (et<4) return 0.926425;
      /*else if (et<5) return 0.958565;
      else if (et<6) return 0.962403;
      else if (et<7) return 0.960784;
      else if (et<10) return 0.943825;
      else if (et<14) return 0.981701;
      else return 1.01947;*/
      else return 0.959847;
   } else {
      if (et<3) return 0.874925;
      else if (et<4) return 0.972655;
      /*else if (et<5) return 0.936749;
      else if (et<6) return 0.876799;
      else if (et<7) return 0.922121;
      else if (et<10) return 0.860435;
      else if (et<14) return 0.955876;
      else return 0.955876;*/
      else return 0.911326;
   }
}

//single EG3 SFs uncertainty reco
double SFReco_uncert(double et, double eta) {
   if (fabs(eta)<1.5) {
      if (et<3) return 0.0315724;
      else if (et<4) return 0.0166131;
      /*else if (et<5) return 0.0156997;
      else if (et<6) return 0.0175102;
      else if (et<7) return 0.0207733;
      else if (et<10) return 0.0182742;
      else if (et<14) return 0.0316075;
      else return 0.0535442;*/
      else return 0.00845752;
   } else {
      if (et<3) return 0.0779765;
      else if (et<4) return 0.0527206;
      /*else if (et<5) return 0.0598152;
      else if (et<6) return 0.075128;
      else if (et<7) return 0.0968333;
      else if (et<10) return 0.0875204;
      else if (et<14) return 0.17171;
      else return 0.17171;*/
      else return 0.0369696;
   }
}


//single EG5 SFs trigger
double SFTrig(double et, double eta) {
   if (fabs(eta)<1.5) {
      if (et<3) return 1.23302;
      else if (et<4) return 1.08211;
      /*else if (et<5) return 1.04166;
      else if (et<6) return 1.02292;
      else if (et<7) return 1.02729;
      else if (et<10) return 1.01991;
      else if (et<14) return 1.01316;
      else return 1.0065;*/
      else return 1.02044;
   } else {
      if (et<3) return 1.23484;
      else if (et<4) return 1.08954;
      /*else if (et<5) return 1.03469;
      else if (et<6) return 0.910735;
      else if (et<7) return 0.977826;
      else if (et<10) return 0.995701;
      else if (et<14) return 0.974374;
      else return 1.04167;*/
      else return 0.982363;
   }
}

//single EG5 uncertainty SFs trigger
double SFTrig_uncert(double et, double eta) {
   if (fabs(eta)<1.5) {
      if (et<3) return 0.066362;
      else if (et<4) return 0.0149044;
      /*else if (et<5) return 0.00520108;
      else if (et<6) return 0.00304072;
      else if (et<7) return 0.00243473;
      else if (et<10) return 0.0016732;
      else if (et<14) return 0.00209417;
      else return 0.00622046;*/
      else return 0.00103982;
   } else {
      if (et<3) return 0.136079;
      else if (et<4) return 0.0483131;
      /*else if (et<5) return 0.0235355;
      else if (et<6) return 0.0212358;
      else if (et<7) return 0.015191;
      else if (et<10) return 0.0126787;
      else if (et<14) return 0.0302115;
      else return 0.0777695;*/
      else return 0.00794602;
   }
}

int ireg(double et, double eta) {
   if (fabs(eta)<1.5) {
      if (et<3) return 1;
      else if (et<4) return 2;
      /*else if (et<5) return 3;
      else if (et<6) return 4;
      else if (et<7) return 5;
      else if (et<10) return 6;
      else if (et<14) return 7;
      else return 8;*/
      else return 3;
   } else {
      if (et<3) return 4;
      else if (et<4) return 5;
      /*else if (et<5) return 11;
      else if (et<6) return 12;
      else if (et<7) return 13;
      else if (et<10) return 14;
      else if (et<14) return 15;
      else return 16;*/
      else return 6;
   }
}


