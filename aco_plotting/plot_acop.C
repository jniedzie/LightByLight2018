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
#include "ReadTree.C"
#include "../CMS_lumi.C"
#include "TStyle.h"
#include "TPaveStats.h"
#include "TText.h"
#include "TCut.h"
#include "TChain.h"
#include "THStack.h"

int xlo = 1;
int xhi = 2;
int nbin = 8;


void make_canvas(TCanvas *&);
void make_hist(TH1D *&, Color_t , int );
TCanvas* PlotHistsAndRatio(TCanvas* , TH1D* , TH1D* , TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, double , double , double , double , double , double , const char *, bool); 

const int nSample = 8;
const char *sample[nSample]={"data","LbyL", "QEDSC" , "CEP", "CEPIncoh","QEDSCFSR", "QEDMG5-FSROnePhoton", "QEDMG5-FSRTwoPhoton"};

const char *dir = "figures_eta2p2";

#define PI 3.141592653589



//const double luminosity       = 1635.123139823; // μb^-1
//const double luminosity       = 1639.207543; // μb^-1
const double luminosity       = 1642.797392; // μb^-1 from Gabi


const double nEventsGeneratedSC = 67810000; // older number with less files 67262800 superchic 
const double xsecGeneratedSC    = 8827.220; // μb
const double purity = 0.96; 

//estimate superchic QED normalisation factors
double scaleFactorsSC = 0.85 *  // NEE    21.12.2021
                        0.93 *      // CHE  21.12.2021
                        pow(0.976, 2)* // electron reco+ID 21.12.2021
                        0.866 *      // HF veto
                       1.008;       // L1 EG trigger
                       
double lumiNormSC = xsecGeneratedSC*luminosity*scaleFactorsSC/nEventsGeneratedSC;
const double nEventsGeneratedSCFSR = 59260000; //photos superchic from oliver
double lumiNormSCFSR = xsecGeneratedSC*luminosity*scaleFactorsSC/nEventsGeneratedSCFSR;


//estimate starlight QED normalisation factors
const double nEventsGeneratedSL = 66750000; // older number with less files 63398400; //starlight
const double xsecGeneratedSL    = 7920; // μb, starlight
double scaleFactorsSL = 0.85 *  // NEE    21.12.2021
  0.93 *      // CHE  21.12.2021
  pow(0.976, 2)* // electron reco+ID 21.12.2021
  0.866 *      // HF veto
  1.008;       // L1 EG trigger
double lumiNormSL = xsecGeneratedSL*luminosity*scaleFactorsSL/nEventsGeneratedSL;


double scaleFactorPhoton = 0.85 *  // NEE    21.12.2021
  0.93 *      // CHE  21.12.2021
  pow(1.048, 2)* // photon reco+ID 21.12.2021
  0.866 *      // HF veto
  1.008;       // L1 EG trigger

const double xsecGeneratedLbLSC    = 2.59; // μb Superchic
const double nEventsGeneratedLbLSC = 466000;  //Superchic
double norm_LbLSC = scaleFactorPhoton*xsecGeneratedLbLSC*luminosity/nEventsGeneratedLbLSC;  //31.12.21 (SF = 1.048, took the square here). 

const double xsecGeneratedLbLMG    = 0.1406; // μb Madgraph David
const double nEventsGeneratedLbLMG = 788069; //Madgraph David
double norm_LbLMG = scaleFactorPhoton*xsecGeneratedLbLMG*luminosity/nEventsGeneratedLbLMG;  //31.12.21 (SF = 1.048, took the square here). 


const double xsecGeneratedCEP    = 0.0058; // μb
const double nEventsGeneratedCEP = 668000; 
double norm_cep = scaleFactorPhoton*xsecGeneratedCEP*luminosity/nEventsGeneratedCEP; 

const double xsecGeneratedCEPIncoh    = 0.001431; // μb
const double nEventsGeneratedCEPIncoh = 500000; 
double norm_cepIncoh = scaleFactorPhoton*xsecGeneratedCEPIncoh*luminosity/nEventsGeneratedCEPIncoh; 

//estimate Madgraph QED 1 FSR normalisation factors
const double nEventsGeneratedQEDMG_1FSR = 10000000; // older number with less files 67262800 superchic 
const double xsecGeneratedQEDMG_1FSR    = 13.45; // μb
double lumiNormQEDMG_1FSR = xsecGeneratedQEDMG_1FSR*luminosity*scaleFactorsSC/nEventsGeneratedQEDMG_1FSR;

//estimate Madgraph QED 2 FSR normalisation factors
const double nEventsGeneratedQEDMG_2FSR = 6600000; // older number with less files 67262800 superchic 
const double xsecGeneratedQEDMG_2FSR    = 0.194; // μb
double lumiNormQEDMG_2FSR = xsecGeneratedQEDMG_2FSR*luminosity*scaleFactorsSC/nEventsGeneratedQEDMG_2FSR;

//const double wt[nSample] = {1, norm_LbLSC, 1, norm_cep, norm_cepIncoh};

void BinLogX(TH1* h);


void plot_acop(bool QEDNorm, bool CEPNorm, bool QEDNormMG5){
   if(CEPNorm) {norm_cep = 1; norm_cepIncoh = 1;}
   if(QEDNormMG5){lumiNormQEDMG_1FSR = 1;}
  
   const double wt[nSample] = {1, norm_LbLSC, lumiNormSC, norm_cep, norm_cepIncoh, lumiNormSCFSR, lumiNormQEDMG_1FSR, lumiNormQEDMG_2FSR};

  cout << "FSR normalization is:" << lumiNormSC << endl;
 
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);

  string mc_name = "SC";


  TFile *outf= new TFile("diphoton_histos.root","recreate");  

  TChain *tree[nSample];

  //// histograms
  TH1D* hpho_pt[nSample], *hpho_eta[nSample], *hpho_phi[nSample], *hpho_pt2[nSample], *hpho_eta2[nSample], *hpho_phi2[nSample]; 
  TH1D* hdipho_pt[nSample], *hdipho_Rapidity[nSample], *hInvmass[nSample], *hAcoplanarity[nSample], *hdipho_cosThetaStar[nSample];

  for (int i = 0; i < nSample; i++){
    tree[i] = new TChain("output_tree");
    tree[i]->Add(Form("%s_diphoton.root",sample[i]));
    //if(i==2)tree[i]->Add("diphoton_qed_with_photos3.root");
    /*if(i==1)tree[i]->Add("lbylSC_diphoton_genInfo.root");

    if(i==3)tree[i]->Add("../oliver_thresholds/diphoton_cep12.root");
    if(i==4)tree[i]->Add("../oliver_thresholds/CEPIncoh_diphoton.root");*/


    hpho_pt[i]    = new TH1D(Form("hpho_pt%s", sample[i]),"",8,2,10);
    hpho_eta[i]   = new TH1D(Form("hpho_eta%s",sample[i]),"",11,-2.2,2.2);
    hpho_phi[i]   = new TH1D(Form("hpho_phi%s",sample[i]),"",12,-PI,PI);

    hpho_pt2[i]    = new TH1D(Form("hpho_pt2%s", sample[i]),"",8,2,10);
    hpho_eta2[i]   = new TH1D(Form("hpho_eta2%s",sample[i]),"",11,-2.2,2.2);
    hpho_phi2[i]   = new TH1D(Form("hpho_phi2%s",sample[i]),"",12,-PI,PI);
 
    hdipho_pt[i]    = new TH1D(Form("hdipho_pt%s", sample[i]),"",10,0,2);
    hdipho_Rapidity[i]   = new TH1D(Form("hdipho_Rapidity%s",sample[i]),"",11,-2.2,2.2);
    hInvmass[i]   = new TH1D(Form("hInvmass%s",sample[i]),"",12,0,50);
    hAcoplanarity[i]   = new TH1D(Form("hAcoplanarity%s",sample[i]),"",20,0,0.1);


    hdipho_cosThetaStar[i]   = new TH1D(Form("hdipho_cosThetaStar%s",sample[i]),"",5,-1,1);

    cout << "file " << sample[i] << ":" << tree[i]->GetEntries()  << endl;
    ReadTree  treeR(tree[i]);
    treeR.fChain->SetBranchStatus("*",1);


    if (treeR.fChain == 0) return;
  
    Long64_t nentries = treeR.fChain->GetEntriesFast();
    cout << tree[i]->GetName() << "    " << nentries << endl;
  
    Long64_t nbytes = 0, nb = 0;
    //for (Long64_t jentry=0; jentry<10;jentry++) {
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry_evt = treeR.LoadTree(jentry);
      if (ientry_evt < 0) break;
      nb = treeR.fChain->GetEntry(jentry);   nbytes += nb;

      if(treeR.phoSwissCross_1 > 0.95) continue;
      if(treeR.phoSwissCross_2 > 0.95) continue;
      if(treeR.ok_neuexcl != 1) continue; //neutral exclusivity
      if(treeR.ok_chexcl_goodtracks != 1 || treeR.ok_chexcl_goodelectrons !=1 ) continue; //charged exclusivity
      if(treeR.vSum_M < 5) continue; //invmass
      if(treeR.vSum_Pt > 2) continue; //diele pt
      if(abs(treeR.phoEta_1) > 2.2) continue;
      if(abs(treeR.phoEta_2) > 2.2) continue;
      //if(abs(treeR.phoSeedTime_1) > 5) continue;
      //if(abs(treeR.phoSeedTime_2) > 5) continue;
      
      if(i==0) {
      //if(treeR.ok_zdcexcl_4n_pos != 1 || treeR.ok_zdcexcl_4n_neg != 1) continue;
       if(treeR.zdc_energy_pos > 10000 || (treeR.zdc_energy_neg > 10000 && treeR.zdc_energy_neg < 750000 )) continue;
       }
  
      //if(i==1)
      //{  if(treeR.ok_trigger!=1) continue; }


      hAcoplanarity[i]->Fill(treeR.pho_acop,wt[i]);



      if(treeR.pho_acop > 0.01) continue; //acop
         
      	
	hpho_pt[i]->Fill(treeR.phoEt_1,wt[i]);
	hpho_eta[i]->Fill(treeR.phoEta_1,wt[i]);
	hpho_phi[i]->Fill(treeR.phoPhi_1,wt[i]);
	
	hpho_pt2[i]->Fill(treeR.phoEt_2,wt[i]);
	hpho_eta2[i]->Fill(treeR.phoEta_2,wt[i]);
	hpho_phi2[i]->Fill(treeR.phoPhi_2,wt[i]);
	
	hdipho_pt[i]->Fill(treeR.vSum_Pt,wt[i]);
	hdipho_Rapidity[i]->Fill(treeR.vSum_Rapidity,wt[i]);
	hInvmass[i]->Fill(treeR.vSum_M,wt[i]);

	hdipho_cosThetaStar[i]->Fill(treeR.costhetastar,wt[i]);

      
    } //entry
  } // for 4 files
  
  for (int i = 0; i < nSample; i++){    
    hpho_pt[i]->Add(hpho_pt2[i]);
    hpho_eta[i]->Add(hpho_eta2[i]);
    hpho_phi[i]->Add(hpho_phi2[i]);
  }


 //add cep coh and Incoh contribution
  hpho_pt[3]->Add(hpho_pt[4]);   hpho_eta[3]->Add(hpho_eta[4]);   hpho_phi[3]->Add(hpho_phi[4]);
  hdipho_pt[3]->Add(hdipho_pt[4]);   hdipho_Rapidity[3]->Add(hdipho_Rapidity[4]);   hInvmass[3]->Add(hInvmass[4]);
  hAcoplanarity[3]->Add(hAcoplanarity[4]); 

  cout << "data:"<< hAcoplanarity[0]->Integral(6,20) << endl;
  cout << "Lbyl:"<< hAcoplanarity[1]->Integral(6,20) << endl;
  cout << "CEP:"<< hAcoplanarity[3]->Integral(6,20) << endl;
  cout << "QED:"<< hAcoplanarity[5]->Integral(6,20) << endl;


  // Normalizing QED xsec to tail 
 if(QEDNorm){
  double old_norm = lumiNormSC;
  lumiNormSC = (hAcoplanarity[0]->Integral(5,20) - hAcoplanarity[1]->Integral(5,20) - hAcoplanarity[3]->Integral(5,20) ) / hAcoplanarity[2]->Integral(5,20);
 

  std::cout << "new lumi Norm   " << lumiNormSC << std::endl;
  //std::cout << "Scale factor " << lumiNormSC/old_norm << std::endl;

  hpho_pt[2]->Scale(lumiNormSC);   hpho_eta[2]->Scale(lumiNormSC);   hpho_phi[2]->Scale(lumiNormSC);     
  hAcoplanarity[2] ->Scale(lumiNormSC);   
  hdipho_pt[2]->Scale(lumiNormSC);   hdipho_Rapidity[2]->Scale(lumiNormSC);     hInvmass[2]->Scale(lumiNormSC);   
  }
  
 if(QEDNormMG5){
  double old_norm = lumiNormQEDMG_1FSR;
  lumiNormQEDMG_1FSR = (hAcoplanarity[0]->Integral(5,20) - hAcoplanarity[1]->Integral(5,20) - hAcoplanarity[3]->Integral(5,20) ) / hAcoplanarity[6]->Integral(5,20);
 

  std::cout << "new lumi Norm   " << lumiNormQEDMG_1FSR << std::endl;
  //std::cout << "Scale factor " << lumiNormSC/old_norm << std::endl;

  hpho_pt[6]->Scale(lumiNormQEDMG_1FSR);   hpho_eta[6]->Scale(lumiNormQEDMG_1FSR);   hpho_phi[6]->Scale(lumiNormQEDMG_1FSR);     
  hAcoplanarity[6] ->Scale(lumiNormQEDMG_1FSR);   
  hdipho_pt[6]->Scale(lumiNormQEDMG_1FSR);   hdipho_Rapidity[6]->Scale(lumiNormQEDMG_1FSR);     hInvmass[6]->Scale(lumiNormQEDMG_1FSR);   
  }

  // Normalizing CEP xsec to tail 
 if(CEPNorm){
  double old_norm = norm_cep;
  //double norm_cep2 = (hAcoplanarity[0]->Integral(5,20) - hAcoplanarity[1]->Integral(5,20) - hAcoplanarity[5]->Integral(5,20) ) / hAcoplanarity[3]->Integral(5,20);
  double norm_cep2 = (hAcoplanarity[0]->Integral(6,20) - hAcoplanarity[1]->Integral(6,20) - hAcoplanarity[5]->Integral(6,20) ) / hAcoplanarity[3]->Integral(6,20);
  //double norm_cep2 = (hAcoplanarity[0]->Integral(7,20) - hAcoplanarity[1]->Integral(7,20) - hAcoplanarity[5]->Integral(7,20) ) / hAcoplanarity[3]->Integral(7,20);
 

  std::cout << "new lumi Norm   " << norm_cep2 << std::endl;
  //std::cout << "Scale factor " << norm_cep2/old_norm << std::endl;

  hpho_pt[3]->Scale(norm_cep2);   hpho_eta[3]->Scale(norm_cep2);   hpho_phi[3]->Scale(norm_cep2);     
  hAcoplanarity[3] ->Scale(norm_cep2);   
  hdipho_pt[3]->Scale(norm_cep2);   hdipho_Rapidity[3]->Scale(norm_cep2);     hInvmass[3]->Scale(norm_cep2);   
  }

  cout << "CEP integral after normalizing :"<< hAcoplanarity[3]->Integral(6,20) << endl;
  

  int W = 700;
  int H = 600;
  
  float T = 0.08;
  float B = 0.14; 
  float L = 0.14;
  float R = 0.04;

  //hInvmass[0]->Draw("p");
 
 //(TCanvas* c1, TH1D* hdata, TH1D* hmc, TH1D* hmc2, double hxmin, double hxmax, double hymin, double hymax, double rymin , double rymax, const char *ytitle, bool iflogy)
 


  TCanvas* c7 = new TCanvas("Acoplanarity","Acoplanarity",254,411,639,592);
  make_canvas(c7);
 // PlotHistsAndRatio(c7, hAcoplanarity[0], hAcoplanarity[1], hAcoplanarity[2], hAcoplanarity[3], hAcoplanarity[5], 0,0.16,0.001,300,0.,2.5,"A_{#phi}", 1);

  PlotHistsAndRatio(c7, hAcoplanarity[0], hAcoplanarity[1], hAcoplanarity[2], hAcoplanarity[3], hAcoplanarity[5], hAcoplanarity[6], hAcoplanarity[7], 0,0.16,0,25,0.,2.5,"A_{#phi}", 0);
 

  cout << " invariant mass " << sample[0] <<  " :" << hInvmass[0]->Integral() << endl;  
  cout << " invariant mass " << sample[1] <<  " :" << hInvmass[1]->Integral() << endl;  
  cout << " invariant mass " << sample[2] <<  " :" << hInvmass[2]->Integral() << endl;  
  cout << " invariant mass " << sample[3] <<  " :" << hInvmass[3]->Integral() << endl;  
  cout << " invariant mass " << sample[5] <<  " :" << hInvmass[5]->Integral() << endl;  
  cout << " invariant mass " << sample[6] <<  " :" << hInvmass[6]->Integral() << endl;  
  cout << " invariant mass " << sample[7] <<  " :" << hInvmass[7]->Integral() << endl;  
  
}


TCanvas* PlotHistsAndRatio(TCanvas* c1, TH1D* hdata, TH1D* hlbyl, TH1D* hqed, TH1D* hcep,TH1D *hfsr, TH1D *hMG5, TH1D *hMG5_2FSR, double hxmin, double hxmax, double hymin, double hymax, double rymin , double rymax, const char *ytitle, bool iflogy){
  
  float T = 0.08;
  float B = 0.14; 
  float L = 0.14;
  float R = 0.04;

  /*c1->Divide(1,2);
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
  
  pad1->cd();*/

  //hdata->Add(hlbyl,-1); 
  //hdata->Add(hfsr,-1); 
 
  THStack *hs = new THStack("hs"," ");
  if(iflogy)gPad->SetLogy();

  hs->SetMaximum(hymax);
  hs->SetMinimum(hymin);
  //hs->GetXaxis()->SetMinimum(hxmin);
 
  make_hist(hfsr, kYellow, 21);
  hs->Add(hfsr);

  make_hist(hMG5, kBlue, 21);
  hs->Add(hMG5);

  make_hist(hMG5_2FSR, 30, 21);
  hs->Add(hMG5_2FSR);

  make_hist(hcep, 51, 21);
  hcep->SetFillStyle(3001);
  hs->Add(hcep);

  make_hist(hlbyl, 95, 21);
  hs->Add(hlbyl);
 
  hs->Draw("hist");   
  hs->GetXaxis()->SetTitle(ytitle);//,"dN/dp_{T}^{2} (1/GeV)^{2} 
  hs->GetYaxis()->SetTitle("# events");

  make_hist(hdata, kBlack, 21);
  hdata->SetLineColor(kBlack);
  hdata->Draw("psame");


  make_hist(hqed, kRed, 21);
  hqed->SetLineColor(kRed);
  //hqed->Draw("psame");

  //make_hist(hMG5, kBlue, 21);
  //hMG5->SetLineColor(kBlue);
  //hMG5->Draw("psame");
  
  TLegend *leg2=new TLegend(0.38,0.60,0.60,0.91);
  leg2->SetFillColor(0);
  leg2->SetBorderSize(0);
  leg2->SetFillStyle(0);
  leg2->SetTextFont(43);
  leg2->SetTextSize(20); 
  leg2->AddEntry(hdata,"Data","pl");
  leg2->AddEntry(hlbyl,"LbyL #gamma #gamma #rightarrow #gamma #gamma (MC)","f");
  leg2->AddEntry(hcep,"CEP (gg #rightarrow #gamma #gamma) + other bkg","f");
  //leg2->AddEntry(hqed,"QED #gamma #gamma #rightarrow e^{+}e^{-} (without FSR)","f");
  leg2->AddEntry(hfsr,"QED SC +Photos","f");
  leg2->AddEntry(hMG5,"QED Madgraph 1 FSR","f");
  leg2->AddEntry(hMG5_2FSR,"QED Madgraph 2 FSR","f");
  
  leg2->Draw();
  

  TString strRatio=hqed->GetName();
  strRatio+="_over_";
  strRatio+=hqed->GetName();
  
  TH1D* hratio=(TH1D*)hfsr->Clone(strRatio);
  hratio->Sumw2();  
  
  hratio->Divide(hqed);

  /*pad2->cd();
  pad2->SetGridy(1);
  hratio->SetLineWidth(2);
  //hratio->SetStats(0);
  hratio->GetXaxis()->SetRangeUser(hxmin,hxmax);
  hratio->GetYaxis()->SetRangeUser(rymin,rymax);
  //hratio->GetXaxis()->SetTitle("Dielectron p_{T}");
  hratio->GetXaxis()->SetTitle(ytitle);
  hratio->GetYaxis()->SetTitle("QED+FSR/QED");
  hratio->GetYaxis()->SetNdivisions(504);
  hratio->GetYaxis()->SetLabelSize(0.11);
  hratio->GetXaxis()->SetLabelSize(0.15);
  hratio->GetXaxis()->SetTitleSize(0.18);
  hratio->GetYaxis()->SetTitleSize(0.15);
  hratio->GetXaxis()->SetTitleOffset(1.1);
  hratio->GetYaxis()->SetTitleOffset(0.31);
  hratio->GetXaxis()->SetTickLength(0.09);
  //hratio->SetMarkerColor(33);
  hratio->SetMarkerColor(kBlack);
  //hratio->SetMarkerStyle(23);
  hratio->SetLineColor(kBlack);
  //hratio->Fit("pol0","W");
 // hratio->Draw("p");*/

  //CMS_lumi( c1, 104, 33,lumi_PbPb2018 );

  c1->Update();
  TString cName=c1->GetName();
  cName+=".png";
  //c1->SaveAs("figures_photos_qedScaleTail/"+cName);
  //c1->SaveAs("figures_photos/"+cName);
  TString c2Name=c1->GetName();
  c2Name+=".pdf";
  //c1->SaveAs("figures_photos_qedScaleTail/"+c2Name);
  //c1->SaveAs("figures_photos/"+c2Name);
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
  hist->SetLineColor(kcolor);
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

