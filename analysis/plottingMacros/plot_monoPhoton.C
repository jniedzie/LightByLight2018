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
#include "ReadMonoPhoTree.C"

int xlo = 1;
int xhi = 4;
int nbin = 8;


const char *dataset[2]={"data","mc"};//,"LbLSC", "CEPSC"};
//const char *dataset[4]={"Data","QEDSC", "ccbar", "bbbar"};//,"QEDSC", "QEDSC"};


const char *dir = "figures";

#define PI 3.141592653589

void make_hist(TH1D *&, Color_t , int );
bool outside_HEM(Double_t SCEta, Double_t SCPhi){
  if(SCEta < -1.39 && SCEta > -3 && SCPhi > -1.6 && SCPhi < -0.9) return false; //original HEM
  //if(SCEta < -1.34 && SCEta > -3 && SCPhi > -1.65 && SCPhi < -0.85) return false; //extended HEM
  return true;
}

bool outside_crack(Double_t SCEta){
  if(abs(SCEta) > 1.4442 && abs(SCEta) < 1.566) return false; //original crack
  //if(abs(SCEta) > 1.3942 && abs(SCEta) < 1.616) return false; //extended crack
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

//const double wt[4] = {1, lumiNormSC, norm_exgg, norm_cep};
const double wt[4] = {1, lumiNormSC, 1, 1};

void plot_monoPhoton(){
 
  //gROOT->LoadMacro("CMS_lumi.C");
  bool outOfFrame    = false;
  TH1::SetDefaultSumw2();
   gStyle->SetOptStat("nemro");



  TFile *outf= new TFile("histos.root","recreate");  


  TChain *monoPho[4], *monoEle[4];
  TH1D* hpho_pt_monoPho[4], * hpho_eta_monoPho[4],  * hpho_phi_monoPho[4], *hpho_hovere[4], *hpho_etawidth[4], *hpho_swisscross[4], *hpho_seedTime[4];
  TH1D* hL1pho_pt_monoPho[4], * hL1pho_eta_monoPho[4],  * hL1pho_phi_monoPho[4], * hL1pho_dr_monoPho[4],  *hnL1pho[4];
  TH2D* hpho_eta_phi[4], *hL1pho_eta_phi[4]; TH1D *hpixelRecHits[4];

  TH1D *hlumi[4], *hrun[4], *hevent[4];

  for (int i=0; i<2; i++){
    monoPho[i] = new TChain("monoPhoton_tree");
    //monoPho[i]->Add(Form("%sAll_SeedTime_19Aprl21.root",dataset[i]));
  //monoPho[i]->Add(Form("%sAll_pixelRecHits.root",dataset[i]));
  monoPho[i]->Add(Form("merged_anomalous_%s_newThresholds.root",dataset[i]));

   hlumi[i]   = new TH1D(Form("hlumi%d",i),"",1400,0,1400);
   hrun[i]    = new TH1D(Form("hrun%d",i),"",1400,326381,327564);

   hpho_pt_monoPho[i]   = new TH1D(Form("hpho_pt_monoPho%d",i),"",20,0,20);
   hpho_eta_monoPho[i]  = new TH1D(Form("hpho_eta_monoPho%d",i),"",100,-2.4,2.4);
   hpho_phi_monoPho[i]  = new TH1D(Form("hpho_phi_monoPho%d",i),"",100,-PI,PI);

   hL1pho_pt_monoPho[i]   = new TH1D(Form("hL1pho_pt_monoPho%d",i),"",50,0,100);
   hL1pho_eta_monoPho[i]  = new TH1D(Form("hL1pho_eta_monoPho%d",i),"",100,-2.4,2.4);
   hL1pho_phi_monoPho[i]  = new TH1D(Form("hL1pho_phi_monoPho%d",i),"",100,-PI,PI);
   hL1pho_dr_monoPho[i]   = new TH1D(Form("hL1pho_dr_monoPho%d",i),"",50,0,5);
   hnL1pho[i]             = new TH1D(Form("hnL1pho%d",i),"",10,0,10);
   hL1pho_eta_phi[i]      = new TH2D(Form("hL1pho_eta_phi%d",i),"",30,-PI,PI,48,-2.4,2.4);

   hpho_hovere[i]       = new TH1D(Form("hpho_hovere%d",i),"",50,0,0.1);
   hpho_etawidth[i]     = new TH1D(Form("hpho_etawidth%d",i),"",100,0,0.1);
   hpho_swisscross[i]   = new TH1D(Form("hpho_swisscross%d",i),"",100,0.5,1);
   hpho_seedTime[i]     = new TH1D(Form("hpho_seedTime%d",i),"",100,-20,20);
   hpho_eta_phi[i]      = new TH2D(Form("hpho_eta_phi%d",i),"",30,-PI,PI,48,-2.4,2.4);

   hpixelRecHits[i]     = new TH1D(Form("hpixelRecHits%d",i),"",60,0,240);

  cout << "file " << monoPho[i]->GetEntries()  << endl;
  ReadMonoPhoTree monoR(monoPho[i]);
  //monoR.fChain->SetBranchStatus("ls",1);
  monoR.fChain->SetBranchStatus("monoPho*",1);
  /*monoR.fChain->SetBranchStatus("monoPhoSCEta",1);
  monoR.fChain->SetBranchStatus("monoPhoSCPhi",1);
  monoR.fChain->SetBranchStatus("monoPhoEtaWidth",1);
  monoR.fChain->SetBranchStatus("monoPhoHoverE",1);
  monoR.fChain->SetBranchStatus("monoPhoEnergyTop",1);
  monoR.fChain->SetBranchStatus("monoPhoEnergyBottom",1);
  monoR.fChain->SetBranchStatus("monoPhoEnergyLeft",1);
  monoR.fChain->SetBranchStatus("monoPhoEnergyRight",1);
  monoR.fChain->SetBranchStatus("monoPhoEnergyCrysMax",1);
  monoR.fChain->SetBranchStatus("monoPhoSeedTime",1);*/
  monoR.fChain->SetBranchStatus("leading*",1);
  monoR.fChain->SetBranchStatus("mono_nL1Pho",1);
  monoR.fChain->SetBranchStatus("monoPhoL1*",1);
  //monoR.fChain->SetBranchStatus("leadingEmEnergy_EE",1);

  if (monoR.fChain == 0) return;
  
  Long64_t nentries = monoR.fChain->GetEntriesFast();
  cout << nentries << endl;
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    //if (jentry%100==0) cout << "--> " << jentry << "/" << nentries << endl;
    Long64_t ientry_evt = monoR.LoadTree(jentry);
    if (ientry_evt < 0) break;
    nb = monoR.fChain->GetEntry(jentry);   nbytes += nb;
    
   if(i==0) { if(monoR.monoPhook_zdcexcl != 1) continue;}
   if(!(outside_crack(monoR.monoPhoSCEta)))continue;
    
    //if(abs(monoR.monoPhoSCEta)<1.8) continue;
    //if(monoR.monoPhoSCPhi>2.1 && monoR.monoPhoSCPhi<2.4 && monoR.monoPhoSCEta<-1.8) continue; // hot tower region
    if(outside_HEM(monoR.monoPhoSCEta,monoR.monoPhoSCPhi)){

      double E4 = monoR.monoPhoEnergyTop + monoR.monoPhoEnergyBottom +  monoR.monoPhoEnergyLeft + monoR.monoPhoEnergyRight;
      double swissCross = 1 - (E4/monoR.monoPhoEnergyCrysMax);
   
      if(abs(monoR.monoPhoSCEta)>1.446)continue;
      if(abs(monoR.monoPhoSeedTime)>3)continue;
      if(swissCross>0.95)continue;
      hpho_swisscross[i]->Fill(swissCross,wt[i]);
      hpho_seedTime[i]->Fill(monoR.monoPhoSeedTime,wt[i]);
      if(abs(monoR.monoPhoSigmaIEta)>0.02)continue;

      
      hlumi[i]->Fill(monoR.ls,wt[i]);
      hrun[i]->Fill(monoR.run,wt[i]);
      
      cout << monoR.run << ":" << monoR.ls << ":" << monoR.evtnb << endl;
      hpho_pt_monoPho[i]->Fill(monoR.monoPhoEt,wt[i]);
      hpho_eta_monoPho[i]->Fill(monoR.monoPhoSCEta,wt[i]);
      hpho_phi_monoPho[i]->Fill(monoR.monoPhoSCPhi,wt[i]);
      hpho_eta_phi[i]->Fill(monoR.monoPhoPhi,monoR.monoPhoEta);
      hpho_hovere[i]->Fill(monoR.monoPhoHoverE,wt[i]);
      hpho_etawidth[i]->Fill(monoR.monoPhoSigmaIEta,wt[i]);

      hpixelRecHits[i]->Fill(monoR.monoPho_nPixelRecHits, wt[i]);

      hnL1pho[i]->Fill(monoR.mono_nL1Pho,wt[i]);
      for(int j=0; j < monoR.mono_nL1Pho; j++){
	hL1pho_pt_monoPho[i]->Fill(monoR.monoPhoL1Et->at(j),wt[i]);
	hL1pho_eta_monoPho[i]->Fill(monoR.monoPhoL1Eta->at(j),wt[i]);
	hL1pho_phi_monoPho[i]->Fill(monoR.monoPhoL1Phi->at(j),wt[i]);
	hL1pho_dr_monoPho[i]->Fill(monoR.monoPhoL1dr->at(j),wt[i]);
        hL1pho_eta_phi[i]->Fill(monoR.monoPhoL1Phi->at(j),monoR.monoPhoL1Eta->at(j));
      }
    } //outside HEM
  } //entry
  } // for 4 files
  
  hlumi[0]->Draw();   

  TLegend *leg2=new TLegend(0.6865449,0.4844936,0.907414,0.743542,NULL,"brNDC");
  leg2->SetFillColor(0);
  leg2->SetBorderSize(0);
  leg2->SetFillStyle(0);
  leg2->SetTextFont(43);
  leg2->SetTextSize(18);
  leg2->AddEntry(hpho_pt_monoPho[0],"Data ","pl");
  leg2->AddEntry(hpho_pt_monoPho[1],"QED SC ","f");
  //leg2->AddEntry(hpho_pt_monoPho[2],"LbL ","f");
  //leg2->AddEntry(hpho_pt_monoPho[3],"CEP ","f");
  
  int W = 700;
  int H = 600;
  float T = 0.08;
  float B = 0.14; 
  float L = 0.14;
  float R = 0.04;

  //// Mono photon plots
  THStack *hs_pt  = new THStack("hs_pt","photon pt");
  THStack *hs_eta = new THStack("hs_eta","photon eta");
  THStack *hs_phi = new THStack("hs_phi","photon phi");
  
  TCanvas* c1 = new TCanvas("c1","mono Photon Et",50,50,W,H);
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
  c1->Divide(2,2);
  c1->cd(1);
  gPad->SetLogy();
  make_hist(hpho_pt_monoPho[1], kYellow, 21);
  hs_pt->Add(hpho_pt_monoPho[1]); 
  //make_hist(hpho_pt_monoPho[2], 95, 21);
  //hs_pt->Add(hpho_pt_monoPho[2]); 
  //make_hist(hpho_pt_monoPho[3], 51, 21);
  //hs_pt->Add(hpho_pt_monoPho[3]); 

  //hpho_pt_monoPho->SetMaximum(1000);
  hpho_pt_monoPho[0]->SetMinimum(0.05);
  make_hist(hpho_pt_monoPho[0], kBlack, 21);
  hpho_pt_monoPho[0]->SetLineColor(kBlack);

  hpho_pt_monoPho[0]->GetXaxis()->SetTitle("mono Photon Et (GeV)");//,"dN/dp_{T}^{2} (1/GeV)^{2} 
  hpho_pt_monoPho[0]->GetYaxis()->SetTitle("# events");
  hpho_pt_monoPho[0]->Draw("hist");

  hs_pt->Draw("histsame");
  leg2->Draw();
  
  c1->cd(2);
  make_hist(hpho_eta_monoPho[1], kYellow, 21);
  hs_eta->Add(hpho_eta_monoPho[1]); 
  //make_hist(hpho_eta_monoPho[2], 95, 21);
  //hs_eta->Add(hpho_eta_monoPho[2]); 
  //make_hist(hpho_eta_monoPho[3], 51, 21);
  //hs_eta->Add(hpho_eta_monoPho[3]); 

  //hpho_eta_monoPho->SetMaximum(1000);
  hpho_eta_monoPho[0]->SetMinimum(0.0);
 
  make_hist(hpho_eta_monoPho[0], kBlack, 21);
  hpho_eta_monoPho[0]->SetLineColor(kBlack);

  hpho_eta_monoPho[0]->GetXaxis()->SetTitle("mono Photon #eta ");//,"dN/dp_{T}^{2} (1/GeV)^{2} 
  hpho_eta_monoPho[0]->GetYaxis()->SetTitle("# events");
  hpho_eta_monoPho[0]->Draw("hist");

  hs_eta->Draw("histsame");


  c1->cd(3);
  make_hist(hpho_phi_monoPho[1], kYellow, 21);
  hs_phi->Add(hpho_phi_monoPho[1]); 
  //make_hist(hpho_phi_monoPho[2], 95, 21);
  //hs_phi->Add(hpho_phi_monoPho[2]); 
  //make_hist(hpho_phi_monoPho[3], 51, 21);
  //hs_phi->Add(hpho_phi_monoPho[3]); 

  //hpho_phi_monoPho->SetMaximum(1000);
  hpho_phi_monoPho[0]->SetMinimum(0.0);
 
  make_hist(hpho_phi_monoPho[0], kBlack, 21);
  hpho_phi_monoPho[0]->SetLineColor(kBlack);

  hpho_phi_monoPho[0]->GetXaxis()->SetTitle("mono Photon #phi");//,"dN/dp_{T}^{2} (1/GeV)^{2} 
  hpho_phi_monoPho[0]->GetYaxis()->SetTitle("# events");
  hpho_phi_monoPho[0]->Draw("hist");

  hs_phi->Draw("histsame");

  c1->cd(4);
  hpho_eta_phi[0]->Draw("colz");
  hpho_eta_phi[0]->GetXaxis()->SetTitle("mono Photon #phi");//,"dN/dp_{T}^{2} (1/GeV)^{2} 
  hpho_eta_phi[0]->GetYaxis()->SetTitle("mono Photon #eta");
 
  c1->SaveAs("monoPhotonPlots/plot1.png");
 
  TCanvas* c2 = new TCanvas("c2","mono Photon Et",50,50,W,H);
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
  c2->Divide(2,2);
  c2->cd(1);
  gPad->SetLogy();
  make_hist(hpho_etawidth[0], kBlack, 20);
  hpho_etawidth[0]->GetXaxis()->SetTitle("#sigma i#eta i#eta ");//,"dN/dp_{T}^{2} (1/GeV)^{2} 
  hpho_etawidth[0]->GetYaxis()->SetTitle("# events");
  hpho_etawidth[0]->Draw("p");


   c2->cd(2);
  gPad->SetLogy();
  hpho_hovere[0]->SetMaximum(100000);
  hpho_hovere[0]->SetMinimum(0.01);
  make_hist(hpho_hovere[0],kBlack, 20);
  hpho_hovere[0]->GetXaxis()->SetTitle("H/E");//,"dN/dp_{T}^{2} (1/GeV)^{2} 
  hpho_hovere[0]->GetYaxis()->SetTitle("# events");
  make_hist(hpho_hovere[1],kRed, 20);
  hpho_hovere[0]->Draw("p");
  hpho_hovere[1]->Draw("psame");

  c2->cd(3);
  gPad->SetLogy();
  hpho_swisscross[0]->SetMaximum(100000);
  hpho_swisscross[0]->SetMinimum(0.01);
  make_hist(hpho_swisscross[0], kBlack, 20);
  hpho_swisscross[1]->GetXaxis()->SetTitle("E4/E ");//,"dN/dp_{T}^{2} (1/GeV)^{2} 
  hpho_swisscross[0]->GetYaxis()->SetTitle("# events");
  make_hist(hpho_swisscross[1], kRed, 21);
  hpho_swisscross[0]->Draw("p");
  hpho_swisscross[1]->Draw("psame");


  c2->cd(4);
  //gPad->SetLogy();
  make_hist(hpho_seedTime[0], kBlack, 20);
  hpho_seedTime[0]->GetXaxis()->SetTitle("seed time ");//,"dN/dp_{T}^{2} (1/GeV)^{2} 
  hpho_seedTime[0]->GetYaxis()->SetTitle("# events");
  hpho_seedTime[0]->Draw("p");
  make_hist(hpho_seedTime[1], kRed, 20);
  hpho_seedTime[1]->Draw("psame");


  c2->SaveAs("monoPhotonPlots/plot2.png");


  THStack *hs_nL1  = new THStack("hs_nL1","photon pt");
  THStack *hs_dr  = new THStack("hs_dr","photon pt");
  THStack *hs_ptL1  = new THStack("hs_ptL1","photon pt");
  THStack *hs_etaL1 = new THStack("hs_etaL1","photon eta");
  THStack *hs_phiL1 = new THStack("hs_phiL1","photon phi");

  TCanvas* c3 = new TCanvas("c3","mono Photon Et",50,50,W,H);
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
  c3->Divide(2,3);
  c3->cd(1);
  gPad->SetLogy();
  make_hist(hnL1pho[1], kYellow, 21);
  hs_nL1->Add(hnL1pho[1]); 
  //make_hist(hnL1pho[2], 95, 21);
  //hs_nL1->Add(hnL1pho[2]); 
  //make_hist(hnL1pho[3], 51, 21);
  //hs_nL1->Add(hnL1pho[3]); 
  make_hist(hnL1pho[0], kBlack, 21);
  hnL1pho[0]->GetXaxis()->SetTitle("No. of L1 EG ");//,"dN/dp_{T}^{2} (1/GeV)^{2} 
  hnL1pho[0]->GetYaxis()->SetTitle("# events");
  hnL1pho[0]->Draw("hist");
  hs_nL1->Draw("histsame");
  leg2->Draw();

  c3->cd(2);
  gPad->SetLogy();
  make_hist(hL1pho_pt_monoPho[1], kYellow, 21);
  hs_ptL1->Add(hL1pho_pt_monoPho[1]); 
  //make_hist(hL1pho_pt_monoPho[2], 95, 21);
  //hs_ptL1->Add(hL1pho_pt_monoPho[2]); 
 // make_hist(hL1pho_pt_monoPho[3], 51, 21);
  //hs_ptL1->Add(hL1pho_pt_monoPho[3]); 

  //hL1pho_pt_monoPho->SetMaximum(1000);
  hL1pho_pt_monoPho[0]->SetMinimum(0.05);
  make_hist(hL1pho_pt_monoPho[0], kBlack, 21);
  hL1pho_pt_monoPho[0]->SetLineColor(kBlack);

  hL1pho_pt_monoPho[0]->GetXaxis()->SetTitle("L1 EG Et (GeV)");//,"dN/dp_{T}^{2} (1/GeV)^{2} 
  hL1pho_pt_monoPho[0]->GetYaxis()->SetTitle("# events");
  hL1pho_pt_monoPho[0]->Draw("hist");

  hs_ptL1->Draw("histsame");
  //leg2->Draw();
  
  c3->cd(3);
  make_hist(hL1pho_eta_monoPho[1], kYellow, 21);
  hs_etaL1->Add(hL1pho_eta_monoPho[1]); 
  //make_hist(hL1pho_eta_monoPho[2], 95, 21);
  //hs_etaL1->Add(hL1pho_eta_monoPho[2]); 
  //make_hist(hL1pho_eta_monoPho[3], 51, 21);
  //hs_etaL1->Add(hL1pho_eta_monoPho[3]); 

  //hL1pho_eta_monoPho->SetMaximum(1000);
  hL1pho_eta_monoPho[0]->SetMinimum(0.0);
 
  make_hist(hL1pho_eta_monoPho[0], kBlack, 21);
  hL1pho_eta_monoPho[0]->SetLineColor(kBlack);

  hL1pho_eta_monoPho[0]->GetXaxis()->SetTitle("L1 EG #eta ");//,"dN/dp_{T}^{2} (1/GeV)^{2} 
  hL1pho_eta_monoPho[0]->GetYaxis()->SetTitle("# events");
  hL1pho_eta_monoPho[0]->Draw("hist");

  hs_etaL1->Draw("histsame");


  c3->cd(4);
  make_hist(hL1pho_phi_monoPho[1], kYellow, 21);
  hs_phiL1->Add(hL1pho_phi_monoPho[1]); 
  //make_hist(hL1pho_phi_monoPho[2], 95, 21);
  //hs_phiL1->Add(hL1pho_phi_monoPho[2]); 
  //make_hist(hL1pho_phi_monoPho[3], 51, 21);
  //hs_phiL1->Add(hL1pho_phi_monoPho[3]); 

  //hL1pho_phi_monoPho->SetMaximum(1000);
  hL1pho_phi_monoPho[0]->SetMinimum(0.0);
 
  make_hist(hL1pho_phi_monoPho[0], kBlack, 21);
  hL1pho_phi_monoPho[0]->SetLineColor(kBlack);

  hL1pho_phi_monoPho[0]->GetXaxis()->SetTitle("L1 EG #phi");//,"dN/dp_{T}^{2} (1/GeV)^{2} 
  hL1pho_phi_monoPho[0]->GetYaxis()->SetTitle("# events");
  hL1pho_phi_monoPho[0]->Draw("hist");

  hs_phiL1->Draw("histsame");

  c3->cd(5);
  gPad->SetLogy();
  hL1pho_dr_monoPho[0]->SetMinimum(0.05);
  make_hist(hL1pho_dr_monoPho[1], kYellow, 21);
  hs_dr->Add(hL1pho_dr_monoPho[1]); 
  //make_hist(hL1pho_dr_monoPho[2], 95, 21);
 // hs_dr->Add(hL1pho_dr_monoPho[2]); 
  //make_hist(hL1pho_dr_monoPho[3], 51, 21);
  //hs_dr->Add(hL1pho_dr_monoPho[3]); 
  make_hist(hL1pho_dr_monoPho[0], kBlack, 21);
  hL1pho_dr_monoPho[0]->GetXaxis()->SetTitle("dr(L1 EG, photon) ");//,"dN/dp_{T}^{2} (1/GeV)^{2} 
  hL1pho_dr_monoPho[0]->GetYaxis()->SetTitle("# events");
  hL1pho_dr_monoPho[0]->Draw("hist");
  hs_dr->Draw("histsame");


  c3->cd(6);
  hL1pho_eta_phi[0]->Draw("colz");
  hL1pho_eta_phi[0]->GetXaxis()->SetTitle("L1 EG #phi");//,"dN/dp_{T}^{2} (1/GeV)^{2} 
  hL1pho_eta_phi[0]->GetYaxis()->SetTitle("L1 EG #eta");
  
  c3->SaveAs("monoPhotonPlots/plot3.png");


 
  TCanvas* c11 = new TCanvas("c11","mono Photon Et",50,50,W,H);
  c11->SetFillColor(0);
  c11->SetBorderMode(0);
  c11->SetFrameFillStyle(0);
  c11->SetFrameBorderMode(0);
  c11->SetLeftMargin( L );
  c11->SetRightMargin( R );
  c11->SetTopMargin( T );
  c11->SetBottomMargin( B );
  c11->SetTickx(0);
  c11->SetTicky(0);
  c11->Divide(2,2);
  c11->cd(1);
  gPad->SetLogy();
  make_hist(hpixelRecHits[1], kYellow, 21);
  hs_pt->Add(hpixelRecHits[1]); 

  hpixelRecHits[0]->SetMinimum(0.05);
  make_hist(hpixelRecHits[0], kBlack, 21);
  hpixelRecHits[0]->SetLineColor(kBlack);

  hpixelRecHits[0]->GetXaxis()->SetTitle("N pixel rec hits");//,"dN/dp_{T}^{2} (1/GeV)^{2} 
  hpixelRecHits[0]->GetYaxis()->SetTitle("# events");
  hpixelRecHits[0]->Draw("p");

  hs_pt->Draw("psame");
  leg2->Draw();

  c11->SaveAs("monoPhotonPlots/plot4.png");

 // new TCanvas();
 // hlumi[0]->Draw();   

//  new TCanvas();
//  hrun[0]->Draw();   
}

void make_hist(TH1D *& hist, Color_t kcolor, int kstyle){
  // For the axis labels:
  hist->SetLabelColor(1, "XYZ");
  hist->SetLabelFont(42, "XYZ");
  hist->SetLabelOffset(0.007, "XYZ");
  hist->SetLabelSize(0.05, "XYZ");
 
  hist->SetMarkerColor(kcolor);
  hist->SetMarkerSize(1.0);
  hist->SetFillColorAlpha(kcolor,0.3);
  hist->SetMarkerStyle(kstyle);
  
 
}

