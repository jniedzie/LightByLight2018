//  drawEfficiencies
//
//  Created by Jeremi Niedziela on 22/07/2019.
//
// Draws a canvas with MC efficiencies dependance on kinematic variables.

#include "../include/Helpers.hpp";

const string  inputPath    = "../results/efficienciesLbL.root";
const string  outputPath   = "../plots/efficienciesLbL.pdf";

const double  canvasWidth  = 800;
const double  canvasHeight = 800;
const int     nRaws        = 2;
const int     nColumns     = 2;

vector<tuple<string, string, string, int, int>> histParams = {
// hist name             x label                     y label             color       iPad
  {"reco_id_eff"        , "Photon E_{T} (GeV)"      , "Eff^{ID}_{MC}"   , datasetColor.at(kMClbl) , 1 },
  {"trigger_eff"        , "Diphoton m_{inv} (GeV)"  , "Eff^{TRIG}_{MC}" , datasetColor.at(kMClbl) , 2 },
  {"trigger_single_eff" , "Diphoton m_{inv} (GeV)"  , "Eff^{TRIG}_{MC}" , kGreen+2                , 2 },
  {"trigger_double_eff" , "Diphoton m_{inv} (GeV)"  , "Eff^{TRIG}_{MC}" , kRed+2                  , 2 },
  {"charged_excl_eff"   , "Diphoton m_{inv} (GeV)"  , "Eff^{TRIG}_{CHE}", datasetColor.at(kMClbl) , 3 },
  {"neutral_excl_eff"   , "Diphoton m_{inv} (GeV)"  , "Eff^{TRIG}_{NEE}", datasetColor.at(kMClbl) , 4 },
};

void drawEfficienciesLbL()
{
  TFile *inFile = TFile::Open(inputPath.c_str());
  TCanvas *canvas = new TCanvas("Efficiencies", "Efficiencies", canvasWidth, canvasHeight);
  canvas->Divide(nColumns, nRaws);
  
  int previousPad = -1;
  for(auto &[name, xLabel, yLabel, color, iPad] : histParams){
  
    canvas->cd(iPad);
    TH1D *hist = (TH1D*)inFile->Get(name.c_str());
    hist->SetLineColor(color);
    hist->SetTitle("");
    hist->GetXaxis()->SetTitle(xLabel.c_str());
    hist->GetXaxis()->SetTitleSize(0.05);
    hist->GetYaxis()->SetTitle(yLabel.c_str());
    hist->GetYaxis()->SetTitleSize(0.05);
    hist->GetYaxis()->SetRangeUser(0, 1.1);
    hist->SetBinContent(1, -1);
    
    gStyle->SetOptStat(0);
    gPad->SetLeftMargin(0.13);
    gPad->SetBottomMargin(0.12);
    
    hist->Draw(iPad != previousPad ? "" : "same");
    previousPad = iPad;
  }
  
  canvas->SaveAs(outputPath.c_str());
  
}
