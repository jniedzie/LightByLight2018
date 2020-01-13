//  drawEfficiencies
//
//  Created by Jeremi Niedziela on 22/07/2019.
//
// Draws a canvas with MC efficiencies dependance on kinematic variables.

#include "../include/Helpers.hpp"

const string dataType = "QED_SC";
//const string dataType = "Data";

const string  inputPath    = "../results/efficienciesQED_"+dataType+"_test.root";
const string  outputPath   = "../plots/efficienciesQED_"+dataType+"_test.pdf";

const double  canvasWidth  = 800;
const double  canvasHeight = 800;
const int     nRaws        = 2;
const int     nColumns     = 2;

void drawEfficienciesQED()
{
  TFile *inFile = TFile::Open(inputPath.c_str());

  TCanvas *canvas = new TCanvas("Efficiencies", "Efficiencies", canvasWidth, canvasHeight);
  canvas->Divide(nColumns, nRaws);
  
  
  canvas->cd(1);
  TH1D *reco_id_eff_vs_pt     = (TH1D*)inFile->Get(("reco_id_eff_vs_pt"+dataType+"_num").c_str());
  TH1D *reco_id_eff_vs_pt_den = (TH1D*)inFile->Get(("reco_id_eff_vs_pt"+dataType+"_den").c_str());
  reco_id_eff_vs_pt->Divide(reco_id_eff_vs_pt_den);
  reco_id_eff_vs_pt->Draw();
  
  canvas->cd(2);
  TH1D *reco_id_cut_through = (TH1D*)inFile->Get(("cut_through_reco_id_eff"+dataType).c_str());
  gPad->SetLogy(true);
  reco_id_cut_through->Draw();
  
  canvas->cd(3);
  TH1D *reco_id_eff_vs_eta     = (TH1D*)inFile->Get(("reco_id_eff_vs_eta"+dataType+"_num").c_str());
  TH1D *reco_id_eff_vs_eta_den = (TH1D*)inFile->Get(("reco_id_eff_vs_eta"+dataType+"_den").c_str());
  reco_id_eff_vs_eta->Divide(reco_id_eff_vs_eta_den);
  reco_id_eff_vs_eta->Draw();
  
  
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
