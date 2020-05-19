#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TF1.h>

string inFileName = "starlight_histos_AN.root";

TFile *inFile;
TCanvas *c1;

double crossSection = 20.6e3;
double luminosity = 363.959;

bool scale = false;
double scaleFactor = crossSection * luminosity; // cross section from superchic3

void Draw(const char* histName,int pad, double minX,double maxX, int rebin=1, bool log=false)
{
  c1->cd(pad);
  if(log) gPad->SetLogy();
  
  TH1F *hist = (TH1F*)inFile->Get(histName);
  if(scale) hist->Scale(scaleFactor/hist->GetEntries());
  hist->Rebin(rebin);
  hist->SetLineColor(kRed);
  hist->Draw();
  hist->GetXaxis()->SetRangeUser(minX,maxX);
}

void plotGen()
{
  gStyle->SetOptFit();
  
  inFile = TFile::Open((inFileName).c_str());
  c1 = new TCanvas("c1","c1",800,1200);
  c1->Divide(2,4);
  
  Draw("pt_single",       1,  0,30,   100,true);
  Draw("eta_single",      2, -10,10,  1,  false);
  Draw("phi_single",      3,  -4,4,   3,  false);
  Draw("pt_pair_distrib", 4,  0,0.5,  1,  true);
  Draw("y_pair_distrib",  5,  -6,6,   1,  false);
  Draw("m_pair_distrib",  6,  0,100,  1,  true);
  Draw("aco_pair_distrib",7,  0,0.1,  2,  false);

  //  Draw("theta_pair_distrib",0,3.14,false,3);
//  Draw("pz_pair_distrib",0,80);
//  Draw("y_single",-2.5,2.5);
//  Draw("pz_single",0,25.0);
  
}
