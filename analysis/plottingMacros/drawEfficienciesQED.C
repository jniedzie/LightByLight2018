//  drawEfficiencies
//
//  Created by Jeremi Niedziela on 22/07/2019.
//
// Draws a canvas with MC efficiencies dependance on kinematic variables.

#include "../include/Helpers.hpp"

const string  inputPath    = "../results/efficienciesQED_test.root";
const string  outputPath   = "../plots/efficienciesQED_test.pdf";

const double  canvasWidth  = 1200;
const double  canvasHeight = 800;
const int     nRaws        = 2;
const int     nColumns     = 3;

TFile *inFile;

void printEfficiencies(string dataType)
{
  TH1D *reco_id_eff_num = (TH1D*)inFile->Get(("reco_id_eff"+dataType+"_num").c_str());
  TH1D *reco_id_eff_den = (TH1D*)inFile->Get(("reco_id_eff"+dataType+"_den").c_str());
  double nTagsRecoId    = reco_id_eff_num->GetBinContent(1);
  double nProbesRecoId  = reco_id_eff_den->GetBinContent(1);
  
  cout<<"\n\nReco and ID efficiency in "<<dataType<<":"<<endl;
  cout<<"N probes: "<<nProbesRecoId<<endl;
  cout<<"N tags: "<<nTagsRecoId<<endl;
  cout<<"Eff : "<<(nTagsRecoId/nProbesRecoId);
  cout<<" +/- "<<(nTagsRecoId/nProbesRecoId*sqrt(1/nTagsRecoId+1/nProbesRecoId))<<endl;
}

void plotDoubleHistogram(string histName, string dataType, bool first)
{
  TH1D *reco_id_eff_vs     = (TH1D*)inFile->Get((histName+dataType+"_num").c_str());
  if(!reco_id_eff_vs) cout<<"ERROR -- could not find histogram: "<<histName<<dataType<<"_num"<<endl;
  
  TH1D *reco_id_eff_vs_den = (TH1D*)inFile->Get((histName+dataType+"_den").c_str());
  if(!reco_id_eff_vs) cout<<"ERROR -- could not find histogram: "<<histName<<dataType<<"_den"<<endl;
  
  reco_id_eff_vs->Divide(reco_id_eff_vs_den);
  reco_id_eff_vs->Draw(first ? "" : "same");
  if(first) reco_id_eff_vs->GetYaxis()->SetRangeUser(0, 1.5);
  else reco_id_eff_vs->SetLineColor(kGreen+2);
}

void plotSingleHistogram(string histName, bool first, int color, TLegend *leg=nullptr)
{
  TH1D *hist = (TH1D*)inFile->Get(histName.c_str());
  if(!hist) cout<<"ERROR -- could not find histogram: "<<histName<<endl;
  hist->Scale(1./hist->GetEntries());
  hist->SetLineColor(color);
  hist->Draw(first ? "" : "same");
//  if(first) hist->GetYaxis()->SetRangeUser(0, 1.0);
  
  if(leg) leg->AddEntry(hist, histName.c_str(), "elp");
}


void drawEfficienciesQED()
{
  inFile = TFile::Open(inputPath.c_str());

  TCanvas *canvas = new TCanvas("Efficiencies", "Efficiencies", canvasWidth, canvasHeight);
  canvas->Divide(nColumns, nRaws);
  
  gStyle->SetOptStat(0);
  
  canvas->cd(1);
  plotDoubleHistogram("reco_id_eff_vs_pt", "Data", true);
  plotDoubleHistogram("reco_id_eff_vs_pt", "QED_SC", false);
  
  canvas->cd(2);
  plotSingleHistogram("cut_through_reco_id_effData"   , true  , kBlue);
  plotSingleHistogram("cut_through_reco_id_effQED_SC" , false , kGreen+2);
  gPad->SetLogy(true);
  
  canvas->cd(3);
  plotDoubleHistogram("reco_id_eff_vs_eta", "Data", true);
  plotDoubleHistogram("reco_id_eff_vs_eta", "QED_SC", false);
  
  canvas->cd(4);
  TLegend *leg = new TLegend(0.8, 1.0, 0.8, 1.0);
  
  plotSingleHistogram("ele_acoplanarityQED_SC_den"  , true  , kGreen+2, leg);
  plotSingleHistogram("ele_acoplanarityData_den"    , false ,  kBlue  , leg);
  leg->Draw();
  
  canvas->cd(5);
  plotSingleHistogram("brem_track_ptData_den"   , true  , kBlue);
  plotSingleHistogram("brem_track_ptQED_SC_den" , false , kGreen+2);
  
  printEfficiencies("Data");
  printEfficiencies("QED_SC");
  
  canvas->SaveAs(outputPath.c_str());
  
}
