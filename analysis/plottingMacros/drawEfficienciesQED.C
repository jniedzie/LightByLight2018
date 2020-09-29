//  drawEfficiencies
//
//  Created by Jeremi Niedziela on 22/07/2019.
//
// Draws a canvas with MC efficiencies dependance on kinematic variables.

#include "../include/Helpers.hpp"

//const string  inputPath    = "../results/efficienciesQED.root";
const string  inputPath    = "../results/efficienciesQED_test.root";
//const string  inputPath    = "../results/efficienciesQED_noPhotonIso.root";
//const string  inputPath    = "../results/efficienciesQED_noElectronIDcuts.root";
const string  outputPath   = "../plots/efficienciesQED.pdf";

const double  canvasWidth  = 2880;
const double  canvasHeight = 1800;
const int     nRaws        = 4;
const int     nColumns     = 4;

TFile *inFile;

vector<tuple<string>> efficienciesParams = {
  { "electron_reco_id"    },
  { "reco_id"             },
  { "trigger_HFveto"      },
  { "charged_exclusivity" },
  { "neutral_exclusivity" },
};

vector<EDataset> datasetsToAnalyze = {
//  kData,
//  kMCqedSC,
  kMCqedSL,
};

void printEfficiencies()
{
  for(auto &[efficiencyType] : efficienciesParams){
 
    
    cout<<"\n------------------------------------------------"<<endl;
    double effData, effDataErr, effMC, effMCerr;
    
    for(EDataset dataset : datasetsToAnalyze){
      
      string numName = efficiencyType+"_eff_num_"+datasetName.at(dataset);
      string denName = efficiencyType+"_eff_den_"+datasetName.at(dataset);
      
      TH1D *histNum = (TH1D*)inFile->Get(numName.c_str());
      TH1D *histDen = (TH1D*)inFile->Get(denName.c_str());
      
      if(!histNum || !histDen){
        cout<<"Could not open hist: "<<numName<<"\t or: "<<denName<<endl;
        continue;
      }
      
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

void plotScaleFactor(string histName, EDataset datasetData, EDataset datasetMC)
{
  return;
  string dataName = histName+"_num_"+datasetName.at(datasetData);
  TH1D *histNumData = new TH1D(*(TH1D*)inFile->Get(dataName.c_str()));
//  TH1D *histDenData = new TH1D(*(TH1D*)inFile->Get((histName+"_den_"+datasetName.at(datasetData)).c_str()));
//  histNumData->Divide(histDenData);

  string mcName = histName+"_num_"+datasetName.at(datasetMC);
  TH1D *histNumMC = new TH1D(*(TH1D*)inFile->Get(mcName.c_str()));
//  TH1D *histDenMC = new TH1D(*(TH1D*)inFile->Get((histName+"_den_"+datasetName.at(datasetMC)).c_str()));
//  histNumMC->Divide(histDenMC);
                   

  if(!histNumData){
    cout<<"Could not open hist: "<<dataName<<endl;
    return;
  }
  if(!histNumMC){
    cout<<"Could not open hist: "<<mcName<<endl;
    return;
  }
                   
  histNumData->Divide(histNumMC);
  
  histNumData->Draw();
  histNumData->GetYaxis()->SetRangeUser(0, 1.5);
  histNumData->SetLineColor(kBlack);
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
  // hist name                                    doubleRatio logY
  {"reco_id_eff_vs_pt"                              , true  , false },
  {"reco_id_eff_vs_eta"                             , true  , false },
  
  {"electron_reco_id_eff_vs_pt"                     , true  , false },
  {"electron_reco_id_eff_vs_eta"                    , true  , false },
  
  {"electron_reco_id_eff_n_good_electrons"          , false , false },
  {"electron_reco_id_eff_n_good_matched_electrons"  , false , false },
  
  {"charged_exclusivity_eff_vs_dielectron_mass"     , true  , false },
  {"charged_exclusivity_eff_vs_dielectron_eta"      , true  , false },
  {"charged_exclusivity_eff_vs_dielectron_pt"       , true  , false },
  
  {"neutral_exclusivity_eff_vs_dielectron_mass"     , true  , false },
  {"neutral_exclusivity_eff_vs_dielectron_eta"      , true  , false },
  {"neutral_exclusivity_eff_vs_dielectron_pt"       , true  , false },
  
  {"reco_id_eff_cut_through"                        , false , true  },
  {"ele_acoplanarity"                               , false , false },
  {"brem_track_pt"                                  , false , false },
  {"failingPhotonEt"                                , false , false },
  {"failingPhotonEta"                               , false , false },
  {"failingPhotonSigmaBarrel"                       , false , false },
  {"failingPhotonSigmaEndcap"                       , false , false },
  {"failingPhotonHEbarrel"                          , false , false },
  {"failingPhotonHEendcap"                          , false , false },
  {"delta_pt_tracks"                                , false , false },
  {"delta_phi_electron_photon"                      , false , false },
};

void drawEfficienciesQED()
{
  inFile = TFile::Open(inputPath.c_str());
  
  TCanvas *canvas = new TCanvas("Efficiencies", "Efficiencies", canvasWidth, canvasHeight);
  canvas->Divide(nColumns, nRaws);
  
  TCanvas *canvasSF = new TCanvas("Scale factors", "Scale factors", canvasWidth, canvasHeight);
  canvasSF->Divide(nColumns, nRaws);
  
  gStyle->SetOptStat(0);
  
  int iPad=1;
  
  for(auto &[histName, doubleRatio, logY] : histParams){
    
    canvas->cd(iPad);
    gPad->SetLogy(logY);
    
    bool first = true;
    TLegend *leg = new TLegend(0.6, 0.7, 0.9, 0.9);
    
    for(EDataset dataset : datasetsToAnalyze){
      if(doubleRatio) plotDoubleHistogram(histName, dataset, first, leg);
      else            plotSingleHistogram(histName, dataset, first, leg);
      
      first = false;
    }
    
    leg->Draw();
    
    // Scale factors
    
    canvasSF->cd(iPad);
    if(doubleRatio) plotScaleFactor(histName, kData, kMCqedSL);
    
    
    
    iPad++;
  }
  
  printEfficiencies();
  
  canvas->SaveAs(outputPath.c_str());
  
}
