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

const double luminosity       = 1647.228136; // μb^-1 //update from Gabi on 12 Feb 2022
const double LumiLossHotZDCneg = 1-(luminosity-85.282007)/luminosity; // update from Gabi on 30 Aug 2022

vector<string> sampleNames={"Data","QEDSCFSR","QEDSL","QEDMG5FSROnePhton","QEDMG5FSRTwoPhton"};



map<string, double> nEventsGenerated = {
  {"QEDSC"    , 67810000},
  {"QEDSCFSR" , 59260000},
  {"QEDSL"    , 66750000},
  {"QEDMG5FSROnePhton"    , 10000000},
  {"QEDMG5FSRTwoPhton"    , 6600000},
};

map<string, double> xsecGenerated = { // μb
  {"QEDSC"    , 8827.220},
  {"QEDSCFSR" , 8827.220},
  {"QEDSL"    , 7920},
  {"QEDMG5FSROnePhton"    , 13.45},
  {"QEDMG5FSRTwoPhton"    , 0.194},
};

double scaleFactor = 0.85 *  // NEE    31.12.2021
0.93 *      // CHE  31.12.2021
//pow(0.976, 2)* // electron reco+ID 31.12.2021
//1.037 *       // L1 EG trigger
0.866;  // HF veto

int ireg(double et, double eta);
void make_canvas(TCanvas *&);
void make_canvas_ratio(TCanvas *&);
void make_hist(TH1D *&, Color_t , int );
void make_hist_ratio(TH1D *&,Color_t, int);
float getAcoBinSF(float acop);
double SFReco(double et, double eta);
double SFReco_uncert(double et, double eta);
double SFTrig(double et, double eta);
TCanvas* PlotHistsAndRatio(TCanvas* , TH1D* , TH1D*, TH1D*, TH1D*, double , double , double , double , double , double , const char *, bool); 
TH1D* SFuncert(TTree *tr, const char* name, const char* var, const char* cut, int nbins, double binmin, double binmax);
void drawText(const char *text, float xp, float yp, int size);


void plotQED_new(){
  
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);
  
  map<string, TChain*> qed;
  
  map<string, TH1D*> hElePt1, hEleEta1, hElePhi1, hElePt2, hEleEta2, hElePhi2;
  map<string, TH1D*> hSumPt, hRap, hInvmass, hAcop, hSF, hInvmass_err;
  map<string, TH1D*> hCosThetaStar, hZDCPos, hZDCNeg;
  
  qed["Data"] = new TChain("output_tree");
  qed["Data"]->Add("../ntuples/qed_Data.root");
  
  hElePt1["Data"]          = new TH1D("hElePt1Data","",50,0,50);
  hEleEta1["Data"]         = new TH1D("hEleEta1Data","",24,-2.4,2.4);
  hElePhi1["Data"]         = new TH1D("hElePhi1Data","",16,-4,4);
  hElePt2["Data"]          = new TH1D("hElePt2Data","",50,0,50);
  hEleEta2["Data"]         = new TH1D("hEleEta2Data","",24,-2.4,2.4);
  hElePhi2["Data"]         = new TH1D("hElePhi2Data","",16,-4,4);
  hSumPt["Data"]           = new TH1D("hSumPtData","",40,0,2);
  hRap["Data"]             = new TH1D("hRapData","",24,-2.4,2.4);
  hInvmass["Data"]         = new TH1D("hInvmassData","",50,0,100);
  hAcop["Data"]            = new TH1D("hAcopData","",100,0,0.1);
  hSF["Data"]              = new TH1D("hSFData","",100,0,1.0);
  hCosThetaStar["Data"]    = new TH1D("hCosThetaStarData","",20,0,1);
  hZDCPos["Data"]          = new TH1D("hZDCPosData","",110,0,220000);
  hZDCNeg["Data"]          = new TH1D("hZDCNegData","",425,0,850000);
  
  cout << "file " << qed["Data"]->GetEntries()  << endl;
  ReadQEDTree qedR(qed["Data"]);
  qedR.fChain->SetBranchStatus("*",1);

  if(qedR.fChain == 0) return;
  
  Long64_t nentries = qedR.fChain->GetEntriesFast();
  cout << qed["Data"]->GetName() << "    " << nentries << endl;
  
  Long64_t nbytes = 0, nb = 0;
  
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
    
    hAcop["Data"]->Fill(qedR.ele_acop,1);
    
    if(qedR.ele_acop > 0.01) continue; //acop
    if(qedR.zdc_energy_pos > 10000 || qedR.zdc_energy_neg > 10000 ) continue;
      
    hElePt1["Data"]->Fill(qedR.elePt_1,1);
    hEleEta1["Data"]->Fill(qedR.eleEta_1,1);
    hElePhi1["Data"]->Fill(qedR.elePhi_1,1);
    
    hElePt2["Data"]->Fill(qedR.elePt_2,1);
    hEleEta2["Data"]->Fill(qedR.eleEta_2,1);
    hElePhi2["Data"]->Fill(qedR.elePhi_2,1);
    
    hSumPt["Data"]->Fill(qedR.vSum_Pt,1);
    hRap["Data"]->Fill(qedR.vSum_Rapidity,1);
    hInvmass["Data"]->Fill(qedR.vSum_M,1);
    
    hCosThetaStar["Data"]->Fill(abs(qedR.costhetastar),1);
    hZDCPos["Data"]->Fill(qedR.zdc_energy_pos,1);
    hZDCNeg["Data"]->Fill(qedR.zdc_energy_neg,1);
  } //entry
  
  for (int i = 0; i < 1; i++){
    hElePt1["Data"]->Add(hElePt2["Data"]);
    hEleEta1["Data"]->Add(hEleEta2["Data"]);
    hElePhi1["Data"]->Add(hElePhi2["Data"]);
  }
  
  map<string, TTree*> tr;
  map<string, TFile*> fMC;
  
  for(string sampleName : sampleNames){
    if(sampleName == "Data") continue;
    
    double wt = xsecGenerated[sampleName] * luminosity * scaleFactor * (1-LumiLossHotZDCneg) / nEventsGenerated[sampleName];
    
    auto filename = "from_ruchi/dielectron/" + sampleName + "_withSFs.root";
    
    fMC[sampleName] = TFile::Open(filename.c_str());
    
    if(!fMC[sampleName]){
      cout<<"Couldn't open file: "<<filename<<endl;
      continue;
    }
    
    tr[sampleName] = (TTree*)fMC[sampleName]->Get("trMC");
    cout << " file is opened: " << sampleName << endl;
    
    hInvmass[sampleName] = SFuncert(tr[sampleName], Form("hInvmass%s",sampleName.c_str()),"vSum_M","ele_acop<0.01",50,0,100);
    hSumPt[sampleName]   = SFuncert(tr[sampleName], Form("hSumPt%s",sampleName.c_str()),"vSum_Pt","ele_acop<0.01",40,0,2);
    hRap[sampleName]     = SFuncert(tr[sampleName], Form("hRap%s",sampleName.c_str()),"vSum_Rapidity","ele_acop<0.01",24,-2.4,2.4);
    hAcop[sampleName]    = SFuncert(tr[sampleName], Form("hAcop%s",sampleName.c_str()),"ele_acop","ele_acop<0.1",100,0,0.1);
    hElePt1[sampleName]   = SFuncert(tr[sampleName], Form("hElePt1%s",sampleName.c_str()),"elePt1","ele_acop<0.01",50,0,50);
    hElePt2[sampleName]   = SFuncert(tr[sampleName], Form("hElePt2%s",sampleName.c_str()),"elePt2","ele_acop<0.01",50,0,50);
    hEleEta1[sampleName]   = SFuncert(tr[sampleName], Form("hEleEta1%s",sampleName.c_str()),"eleEta1","ele_acop<0.01",24,-2.4,2.4);
    hEleEta2[sampleName]   = SFuncert(tr[sampleName], Form("hEleEta2%s",sampleName.c_str()),"eleEta2","ele_acop<0.01",24,-2.4,2.4);
    hElePhi1[sampleName]   = SFuncert(tr[sampleName], Form("hElePhi1%s",sampleName.c_str()),"elePhi1","ele_acop<0.01",16,-4,4);
    hElePhi2[sampleName]   = SFuncert(tr[sampleName], Form("hElePhi2%s",sampleName.c_str()),"elePhi2","ele_acop<0.01",16,-4,4);
    
    hInvmass[sampleName]->Scale(wt);
    hSumPt[sampleName]->Scale(wt);
    hRap[sampleName]->Scale(wt);
    hAcop[sampleName]->Scale(wt);
    hElePt1[sampleName]->Scale(wt);
    hElePt2[sampleName]->Scale(wt);
    hElePt1[sampleName]->Add(hElePt2[sampleName]);
    hEleEta1[sampleName]->Scale(wt);
    hEleEta2[sampleName]->Scale(wt);
    hEleEta1[sampleName]->Add(hEleEta2[sampleName]);
    hElePhi1[sampleName]->Scale(wt);
    hElePhi2[sampleName]->Scale(wt);
    
    hElePhi1[sampleName]->Add(hElePhi2[sampleName]);
  }
  
  int W = 700;
  int H = 600;
  
  float T = 0.08;
  float B = 0.14;
  float L = 0.14;
  float R = 0.04;
  
  TCanvas* cc1 = new TCanvas("Sum_pt","dielectron pT",254,411,639,592);
  make_canvas(cc1);
  PlotHistsAndRatio(cc1, hSumPt["Data"], hSumPt["QEDSL"], nullptr,nullptr, 0.0,2.0,0.1,8000,0.5,2.0,"Dielectron p_{T}", 1);
  
  TCanvas* c3 = new TCanvas("Rapidity","Rapidity",254,411,639,592);
  make_canvas(c3);
  PlotHistsAndRatio(c3, hRap["Data"], hRap["QEDSL"], nullptr, nullptr,-3,3,0,7000,0.7,1.3,"Rapidity", 0);
  
  TCanvas* c4 = new TCanvas("Electron_pt","Electron pT",254,411,639,592);
  make_canvas(c4);
  PlotHistsAndRatio(c4, hElePt1["Data"], hElePt1["QEDSL"], nullptr, nullptr, 0,50,0.1,40000,0.1,1.8,"Electron p_{T}", 1);
  
  TCanvas* c5 = new TCanvas("Electron_eta","Electron eta",254,411,639,592);
  make_canvas(c5);
  PlotHistsAndRatio(c5, hEleEta1["Data"], hEleEta1["QEDSL"], nullptr, nullptr, -3,3,0,7000,0.7,1.3,"Electron #eta", 0);
  
  TCanvas* c6 = new TCanvas("Electron_phi","Electron phi",254,411,639,592);
  make_canvas(c6);
  PlotHistsAndRatio(c6, hElePhi1["Data"], hElePhi1["QEDSL"], nullptr,nullptr, -4,4,0,7000,0.7,1.3,"Electron #phi", 0);
  
  TCanvas* c2 = new TCanvas("Inv_mass","Invmass",254,411,639,592);
  make_canvas(c2);
  PlotHistsAndRatio(c2, hInvmass["Data"], hInvmass["QEDSL"], nullptr,nullptr, 0,120,0.1,20000,0.6,1.4,"Invariant Mass", 1);
  
  TCanvas* c7 = new TCanvas("Acoplanarity","Acoplanarity",254,411,639,592);
  make_canvas(c7);
  PlotHistsAndRatio(c7, hAcop["Data"], hAcop["QEDSL"], nullptr, nullptr, 0,0.1,0.01,100000,0.7,1.3,"A_{#phi}", 1);
  
  new TCanvas();
  make_hist(hZDCPos["Data"], kBlack, 20);
  hZDCPos["Data"]->Draw("p");
  
  new TCanvas();
  make_hist(hZDCNeg["Data"], kBlack, 20);
  hZDCNeg["Data"]->Draw("p");
  
  for(string sampleName : sampleNames){
    cout << "count for acop < 0.01 = " << sampleName <<  " :" << hAcop[sampleName]->Integral(1,10) << endl;
  }
}



TCanvas* PlotHistsAndRatio(TCanvas* c1, TH1D* hdata, TH1D* hmc, TH1D* hmc2, TH1D* hmc3,
                           double hxmin, double hxmax, double hymin, double hymax, double rymin , double rymax,
                           const char *ytitle, bool iflogy){
  
  float T = 0.08;
  float B = 0.14;
  float L = 0.14;
  float R = 0.04;
  
  TString strRatio= "";
  if(hmc2){
    strRatio = hmc2->GetName();
    strRatio+="_over_";
    strRatio+=hmc2->GetName();
  }
  
  TH1D* htotal=(TH1D*)hmc->Clone(strRatio);
  htotal->Sumw2();
  
  if(hmc2) htotal->Add(hmc2);
  
  TH1D* hratio=(TH1D*)hdata->Clone(strRatio);
  hratio->Sumw2();
  
  hratio->Divide(htotal);
  
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
  
  if(hmc3) make_hist(hmc3, 30, 21);
  if(hmc2) make_hist(hmc2, kRed, 21);
  make_hist(hmc, kBlue, 21);
  hs->Add(hmc);
  
  hs->Draw("hist");
  hs->GetYaxis()->SetTitle("# events");
  hs->GetXaxis()->SetRangeUser(hxmin,hxmax);
  
  hdata->GetYaxis()->SetTitle("Events");
  hdata->SetMarkerColor(kBlack);
  hdata->SetLineColor(kBlack);
  hdata->SetMarkerStyle(23);
  hdata->Draw("psame");

  TLegend *leg2=new TLegend(0.35,0.70,0.60,0.9);
  leg2->SetFillColor(0);
  leg2->SetBorderSize(0);
  leg2->SetFillStyle(0);
  leg2->SetTextFont(43);
  leg2->SetTextSize(20);
  leg2->AddEntry(hdata,"Data ","pl");
  leg2->AddEntry(hmc,"Superchic + Photos","f");
  leg2->Draw();
  
  pad2->cd();
  pad2->SetGridy(1);
  hratio->SetLineWidth(2);
  hratio->GetXaxis()->SetRangeUser(hxmin,hxmax);
  hratio->GetYaxis()->SetRangeUser(rymin,rymax);
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
  hratio->SetMarkerColor(kBlue);
  hratio->SetLineColor(kBlue);
  hratio->Draw("p");
  
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


TH1D* SFuncert(TTree *tr, const char* name, const char* var, const char* cut, int nbins, double binmin, double binmax){
  
  TH1D *hvari[7];
  for(int ibin=0; ibin<7; ibin++){
    TString namei = Form("Reco%s_%d",name,ibin);
    hvari[ibin] = new TH1D(namei,"",nbins,binmin, binmax);
    tr->Project(namei,var,Form("SFweightR[%d]*SFweightT[%d]*(%s)",ibin,ibin,cut));
  }
  
  TH1D *hans = (TH1D*) hvari[0]->Clone(name);
  
  for(int i=1; i<=hans->GetNbinsX(); i++){
    double err=0; double errT = 0;
    for (int ibin=1; ibin<7; ibin++){
      err += pow(hvari[ibin]->GetBinContent(i)-hvari[0]->GetBinContent(i),2);
    }
    hans->SetBinError(i,sqrt(err+errT+pow(hans->GetBinError(i),2)));
  }
  return hans;
}


void drawText(const char *text, float xp, float yp, int size){
  TLatex *tex = new TLatex(xp,yp,text);
  tex->SetTextFont(43);
  tex->SetTextSize(size);
  tex->SetTextColor(kMagenta);
  tex->SetLineWidth(1);
  tex->SetNDC();
  tex->Draw();
}
