//  drawEfficiencies
//
//  Created by Jeremi Niedziela on 22/07/2019.
//
// Draws a canvas with MC efficiencies dependance on kinematic variables.

#include "../include/Helpers.hpp"

const string  inputPath    = "../results/efficienciesQED.root";
const string  outputPath   = "../plots/efficienciesQED.pdf";

const double  canvasWidth  = 2880;
const double  canvasHeight = 1800;
const int     nRaws        = 4;
const int     nColumns     = 4;

TFile *inFile;

vector<tuple<string>> efficienciesParams = {
  { "reco_id"             },
  { "trigger_HFveto"      },
  { "charged_exclusivity" },
  { "neutral_exclusivity" },
};

vector<EDataset> datasetsToAnalyze = {
  kData,
  kMCqedSC
};

void printEfficiencies()
{
  for(auto &[efficiencyType] : efficienciesParams){
 
    
    cout<<"\n------------------------------------------------"<<endl;
    double effData, effDataErr, effMC, effMCerr;
    
    for(EDataset dataset : datasetsToAnalyze){
      
      TH1D *histNum = (TH1D*)inFile->Get((efficiencyType+"_eff_num_"+datasetName.at(dataset)).c_str());
      TH1D *histDen = (TH1D*)inFile->Get((efficiencyType+"_eff_den_"+datasetName.at(dataset)).c_str());
      double nTags    = histNum->GetBinContent(1);
      double nProbes  = histDen->GetBinContent(1);
    
      cout<<"\n"<<efficiencyType<<" efficiency in "<<datasetName.at(dataset)<<":"<<endl;
      cout<<"N probes: "<<nProbes<<endl;
      cout<<"N tags: "<<nTags<<endl;
      cout<<"Eff : "<<(nTags/nProbes);
      cout<<" +/- "<<(nTags/nProbes*sqrt(1/nTags+1/nProbes))<<endl;
      
      if(dataset == kData){
        effData     = nTags/nProbes;
        effDataErr  = (nTags/nProbes*sqrt(1/nTags+1/nProbes));
      }
      else{
        effMC     = nTags/nProbes;
        effMCerr  = (nTags/nProbes*sqrt(1/nTags+1/nProbes));
      }
    }
    
    double scaleFactor = effData/effMC;
    double scaleFactorErr = scaleFactor * sqrt(pow(effDataErr/effData, 2) + pow(effMCerr/effMC, 2));
                                           
    cout<<"\nScale factor: "<<scaleFactor<<" +/- "<<scaleFactorErr<<endl;
    cout<<"------------------------------------------------\n"<<endl;
  }
  
}

void plotDoubleHistogram(string histName, EDataset dataset, bool first, TLegend *leg=nullptr)
{
  TH1D *histNum = (TH1D*)inFile->Get((histName+"_num_"+datasetName.at(dataset)).c_str());
  if(!histNum) cout<<"ERROR -- could not find histogram: "<<histName<<"_num_"<<datasetName.at(dataset)<<endl;
  
  TH1D *histDen = (TH1D*)inFile->Get((histName+"_den_"+datasetName.at(dataset)).c_str());
  if(!histDen) cout<<"ERROR -- could not find histogram: "<<histName<<"_den_"<<datasetName.at(dataset)<<endl;
  
  histNum->Divide(histDen);
  histNum->Draw(first ? "" : "same");
  histNum->GetYaxis()->SetRangeUser(0, 1.5);
  histNum->SetLineColor(datasetColor.at(dataset));
  
  if(leg) leg->AddEntry(histNum, datasetName.at(dataset).c_str(), "elp");
}

void plotSingleHistogram(string histName, EDataset dataset, bool first, TLegend *leg=nullptr)
{
  TH1D *hist = (TH1D*)inFile->Get((histName+"_"+datasetName.at(dataset)).c_str());
  if(!hist) cout<<"ERROR -- could not find histogram: "<<histName<<endl;
  
  hist->Scale(1./hist->GetEntries());
  hist->SetLineColor(datasetColor.at(dataset));
  hist->Draw(first ? "" : "same");
  //  if(first) hist->GetYaxis()->SetRangeUser(0, 1.0);
  
  if(leg) leg->AddEntry(hist, datasetName.at(dataset).c_str(), "elp");
}

vector<tuple<string, bool, bool>> histParams = {
  // hist name              doubleRatio logY
  {"reco_id_eff_vs_pt"        , true  , false },
  {"reco_id_eff_vs_eta"       , true  , false },
  
  {"reco_id_eff_cut_through"  , false , true  },
  {"ele_acoplanarity"         , false , false },
  {"brem_track_pt"            , false , false },
  {"failingPhotonEt"          , false , false },
  {"failingPhotonEta"         , false , false },
  {"failingPhotonSigmaBarrel" , false , false },
  {"failingPhotonSigmaEndcap" , false , false },
  {"failingPhotonHEbarrel"    , false , false },
  {"failingPhotonHEendcap"    , false , false },
  {"delta_pt_tracks"          , false , false },
  {"delta_phi_electron_photon", false , false },
};

void drawEfficienciesQED()
{
  inFile = TFile::Open(inputPath.c_str());
  
  TCanvas *canvas = new TCanvas("Efficiencies", "Efficiencies", canvasWidth, canvasHeight);
  canvas->Divide(nColumns, nRaws);
  gStyle->SetOptStat(0);
  
  int iPad=1;
  
  for(auto &[histName, doubleRatio, logY] : histParams){
    
    canvas->cd(iPad++);
    gPad->SetLogy(logY);
    
    bool first = true;
    TLegend *leg = new TLegend(0.6, 0.7, 0.9, 0.9);
    
    for(EDataset dataset : datasetsToAnalyze){
      if(doubleRatio) plotDoubleHistogram(histName, dataset, first, leg);
      else            plotSingleHistogram(histName, dataset, first, leg);
      
      first = false;
    }
    
    leg->Draw();
    
  }
  
  printEfficiencies();
  
  canvas->SaveAs(outputPath.c_str());
  
}
