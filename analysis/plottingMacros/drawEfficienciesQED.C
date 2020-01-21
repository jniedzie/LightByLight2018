//  drawEfficiencies
//
//  Created by Jeremi Niedziela on 22/07/2019.
//
// Draws a canvas with MC efficiencies dependance on kinematic variables.

#include "../include/Helpers.hpp"

const string  inputPath    = "../results/efficienciesQED_test.root";
const string  outputPath   = "../plots/efficienciesQED_test.pdf";

const double  canvasWidth  = 2880;
const double  canvasHeight = 1800;
const int     nRaws        = 4;
const int     nColumns     = 4;

TFile *inFile;

void printEfficiencies(string dataType)
{
  TH1D *reco_id_eff_num = (TH1D*)inFile->Get(("reco_id_eff_num_"+dataType).c_str());
  TH1D *reco_id_eff_den = (TH1D*)inFile->Get(("reco_id_eff_den_"+dataType).c_str());
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
  TH1D *reco_id_eff_vs     = (TH1D*)inFile->Get((histName+"_num_"+dataType).c_str());
  if(!reco_id_eff_vs) cout<<"ERROR -- could not find histogram: "<<histName<<dataType<<"_num"<<endl;
  
  TH1D *reco_id_eff_vs_den = (TH1D*)inFile->Get((histName+"_den_"+dataType).c_str());
  if(!reco_id_eff_vs_den) cout<<"ERROR -- could not find histogram: "<<histName<<dataType<<"_den"<<endl;
  
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
  plotSingleHistogram("reco_id_eff_cut_through_Data"   , true  , kBlue);
  plotSingleHistogram("reco_id_eff_cut_through_QED_SC" , false , kGreen+2);
  gPad->SetLogy(true);
  
  canvas->cd(3);
  plotDoubleHistogram("reco_id_eff_vs_eta", "Data", true);
  plotDoubleHistogram("reco_id_eff_vs_eta", "QED_SC", false);
  
  canvas->cd(4);
  TLegend *leg = new TLegend(0.8, 1.0, 0.8, 1.0);
  
  plotSingleHistogram("ele_acoplanarity_QED_SC"  , true  , kGreen+2, leg);
  plotSingleHistogram("ele_acoplanarity_Data"    , false ,  kBlue  , leg);
  leg->Draw();
  
  canvas->cd(5);
  plotSingleHistogram("brem_track_pt_Data"   , true  , kBlue);
  plotSingleHistogram("brem_track_pt_QED_SC" , false , kGreen+2);
  
  canvas->cd(6);
  plotSingleHistogram("failingPhotonEt_Data"   , true  , kBlue);
  plotSingleHistogram("failingPhotonEt_QED_SC" , false , kGreen+2);
  
  canvas->cd(7);
  plotSingleHistogram("failingPhotonEta_Data"   , true  , kBlue);
  plotSingleHistogram("failingPhotonEta_QED_SC" , false , kGreen+2);
  
  canvas->cd(8);
  plotSingleHistogram("failingPhotonSigmaBarrel_Data"   , true  , kBlue);
  plotSingleHistogram("failingPhotonSigmaBarrel_QED_SC" , false , kGreen+2);
  
  canvas->cd(9);
  plotSingleHistogram("failingPhotonSigmaEndcap_Data"   , true  , kBlue);
  plotSingleHistogram("failingPhotonSigmaEndcap_QED_SC" , false , kGreen+2);
  
  canvas->cd(10);
  plotSingleHistogram("failingPhotonHEbarrel_Data"   , true  , kBlue);
  plotSingleHistogram("failingPhotonHEbarrel_QED_SC" , false , kGreen+2);
  
  canvas->cd(11);
  plotSingleHistogram("failingPhotonHEendcap_Data"   , true  , kBlue);
  plotSingleHistogram("failingPhotonHEendcap_QED_SC" , false , kGreen+2);
  
  canvas->cd(12);
  plotSingleHistogram("delta_pt_tracks_Data"   , true  , kBlue);
  plotSingleHistogram("delta_pt_tracks_QED_SC" , false , kGreen+2);
  
  canvas->cd(13);
  plotSingleHistogram("delta_phi_electron_photon_Data"   , true  , kBlue);
  plotSingleHistogram("delta_phi_electron_photon_QED_SC" , false , kGreen+2);
  
  
  
  printEfficiencies("Data");
  printEfficiencies("QED_SC");
  
  canvas->SaveAs(outputPath.c_str());
  
}
