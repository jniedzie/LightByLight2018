#include "../include/Helpers.hpp"

string inputPath  = "../results/basicPlots.root";
string outputPath = "../plots/acoplanarity.pdf";

// Only those datasets will be analyzed
const vector<EDataset> datasetsToAnalyze = {
  kData,
//  kData_SingleEG3,
//  kData_recoEff,
//  kData_triggerEff,
    kMCqedSC,
//  kMCqedSC_SingleEG3,
//  kMCqedSC_recoEff,
//  kMCqedSC_triggerEff,
//    kMCqedSL,
//  kMClbl,
//  kMCcep
};

void prepareHist(TH1D *hist, int color)
{
  hist->SetLineColor(color);
  hist->SetFillColorAlpha(color, 0.2);
  
  hist->Scale(1./hist->GetEntries());
  hist->Sumw2(false);
}

map<EDataset, string> legendOptions = {
  {kData,     "elp" },
  {kMCcep,    "f"   },
  {kMCqedSL,  "f"   },
  {kMCqedSC,  "f"   },
  {kMClbl,    "f"   },
};

void drawAcoplanarity()
{
  TFile *inFile = TFile::Open(inputPath.c_str());
  
  TCanvas *canvas = new TCanvas("Shower shape", "Shower shape", 800, 500);
  
  gStyle->SetOptStat(0);
  TLegend *legend = new TLegend(0.6, 0.6, 0.9, 0.9 );
  
  
  map<EDataset, TH1D*> hists;
  THStack *backgroundsStack = new THStack();
  
  for(EDataset dataset : datasetsToAnalyze){
    string legendOption = legendOptions[dataset];
    
    hists[dataset] = (TH1D*)inFile->Get(("acoplanarity"+datasetName.at(dataset)).c_str());
    
    if(!hists[dataset]){
      cout<<"ERROR -- no histogram found for dataset "<<datasetName.at(dataset)<<endl;
      continue;
    }
    
    legend->AddEntry(hists[dataset], datasetDescription.at(dataset).c_str(), legendOption.c_str());
    prepareHist(hists[dataset], datasetColor.at(dataset));
    
    if(dataset == kData){
      hists[dataset]->SetMarkerStyle(21);
      hists[dataset]->SetLineColor(datasetColor.at(dataset));
      hists[dataset]->SetMarkerColor(datasetColor.at(dataset));
      hists[dataset]->SetMarkerSize(1);
    }
    else{
      backgroundsStack->Add(hists[dataset]);
    }
  }
  
  canvas->cd(1);
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);
  
  backgroundsStack->Draw();
  backgroundsStack->GetXaxis()->SetRangeUser(0, 0.2);
  backgroundsStack->SetTitle("");
  backgroundsStack->GetYaxis()->SetTitle("# events");
  backgroundsStack->GetYaxis()->SetTitleSize(0.06);
  backgroundsStack->GetXaxis()->SetTitle("A_{#phi}^{#gamma#gamma}");
  backgroundsStack->GetXaxis()->SetTitleSize(0.06);
  
  hists[kData]->Draw("samePE");
  legend->Draw("same");
  
  canvas->SaveAs(outputPath.c_str());
}
