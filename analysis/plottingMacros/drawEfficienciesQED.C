//  drawEfficiencies
//
//  Created by Jeremi Niedziela on 22/07/2019.
//
// Draws a canvas with MC efficiencies dependance on kinematic variables.

#include "../include/Helpers.hpp"

const string dataType = "QED_SC";
const string suffix = "_test";
//const string dataType = "Data";
//const string suffix = "_noCuts_newProcedure";


const string  inputPath    = "../results/efficienciesQED_"+dataType+suffix+".root";
const string  outputPath   = "../plots/efficienciesQED_"+dataType+suffix+".pdf";

const double  canvasWidth  = 800;
const double  canvasHeight = 800;
const int     nRaws        = 2;
const int     nColumns     = 2;

void drawEfficienciesQED()
{
  TFile *inFile = TFile::Open(inputPath.c_str());

  TCanvas *canvas = new TCanvas("Efficiencies", "Efficiencies", canvasWidth, canvasHeight);
  canvas->Divide(nColumns, nRaws);
  
  gStyle->SetOptStat(0);
  
  canvas->cd(1);
  TH1D *reco_id_eff_vs_pt     = (TH1D*)inFile->Get(("reco_id_eff_vs_pt"+dataType+"_num").c_str());
  TH1D *reco_id_eff_vs_pt_den = (TH1D*)inFile->Get(("reco_id_eff_vs_pt"+dataType+"_den").c_str());
  reco_id_eff_vs_pt->Divide(reco_id_eff_vs_pt_den);
  reco_id_eff_vs_pt->Draw();
  reco_id_eff_vs_pt->GetYaxis()->SetRangeUser(0, 1.0);
  
  canvas->cd(2);
  TH1D *reco_id_cut_through = (TH1D*)inFile->Get(("cut_through_reco_id_eff"+dataType).c_str());
  gPad->SetLogy(true);
  reco_id_cut_through->Draw();
  
  canvas->cd(3);
  TH1D *reco_id_eff_vs_eta     = (TH1D*)inFile->Get(("reco_id_eff_vs_eta"+dataType+"_num").c_str());
  TH1D *reco_id_eff_vs_eta_den = (TH1D*)inFile->Get(("reco_id_eff_vs_eta"+dataType+"_den").c_str());
  reco_id_eff_vs_eta->Divide(reco_id_eff_vs_eta_den);
  reco_id_eff_vs_eta->Draw();
  reco_id_eff_vs_eta->GetYaxis()->SetRangeUser(0, 1.0);
  
  
  TH1D *reco_id_eff_num = (TH1D*)inFile->Get(("reco_id_eff"+dataType+"_num").c_str());
  TH1D *reco_id_eff_den = (TH1D*)inFile->Get(("reco_id_eff"+dataType+"_den").c_str());
  double nTagsRecoId    = reco_id_eff_num->GetBinContent(1);
  double nProbesRecoId  = reco_id_eff_den->GetBinContent(1);
  
  cout<<"Reco and ID efficiency:"<<endl;
  cout<<"N probes: "<<nProbesRecoId<<endl;
  cout<<"N tags: "<<nTagsRecoId<<endl;
  cout<<"Eff: "<<(nTagsRecoId/nProbesRecoId);
  cout<<" +/- "<<(nTagsRecoId/nProbesRecoId*sqrt(1/nTagsRecoId+1/nProbesRecoId))<<endl;
  
  
  canvas->SaveAs(outputPath.c_str());
  
}
