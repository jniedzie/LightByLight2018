#include "../include/Helpers.hpp"

string inputPath  = "../results/basicPlots.root";
string outputPath = "../plots/distributions.pdf";

// Only those datasets will be analyzed
const vector<EDataset> datasetsToAnalyze = {
  kData,
  kMCqedSC,
//  kMCqedSL,
//  kMClbl,
//  kMCcep
};

vector<tuple<string, string>> histParams = {
  // title              x axis title
  {"lbl_acoplanarity"       , "A_{#phi}^{#gamma#gamma}"},
  {"lbl_photon_et"          , "photon E_{t} (GeV)"    },
  {"lbl_photon_eta"         , "photon #eta"           },
  {"lbl_photon_phi"         , "photon #phi"           },
  {"lbl_diphoton_mass"      , "diphoton m_{inv} (GeV)"},
  {"lbl_diphoton_rapidity"  , "diphoton rapidity"     },
  {"lbl_diphoton_pt"        , "diphoton p_{t}"        },
  {"qed_acoplanarity"       , "A_{#phi}^{e^{+}e^{-}}"},
};

void prepareHist(TH1D *hist, EDataset dataset)
{
  hist->SetLineColor(datasetColor.at(dataset));
  hist->SetFillColorAlpha(datasetColor.at(dataset), 0.2);
  
  if(dataset == kData){
    hist->SetMarkerStyle(21);
    hist->SetMarkerColor(datasetColor.at(dataset));
    hist->SetMarkerSize(1);
  }
  
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

void drawBasicPlots()
{
  TFile *inFile = TFile::Open(inputPath.c_str());
  
  TCanvas *canvas = new TCanvas("Canvas", "Canvas", 2880, 1800);
  canvas->Divide(3,3);
  gStyle->SetOptStat(0);
  
  int iCanvas=1;
  
  for(auto &[histName, xAxisTitle] : histParams){
    map<EDataset, TH1D*> hists;
    TLegend *legend = new TLegend(0.6, 0.6, 0.9, 0.9 );
    THStack *backgroundsStack = new THStack();
    
    for(EDataset dataset : datasetsToAnalyze){
      string legendOption = legendOptions[dataset];
      
      hists[dataset] = (TH1D*)inFile->Get((histName+"_"+datasetName.at(dataset)).c_str());
      if(!hists[dataset]){
        cout<<"ERROR -- no histogram found for dataset "<<datasetName.at(dataset)<<endl;
        continue;
      }
      
      legend->AddEntry(hists[dataset], datasetDescription.at(dataset).c_str(), legendOption.c_str());
      
      prepareHist(hists[dataset], dataset);
      
      if(dataset != kData) backgroundsStack->Add(hists[dataset]);
    }
    
    canvas->cd(iCanvas++);
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.15);
    
    backgroundsStack->Draw();
//    backgroundsStack->GetXaxis()->SetRangeUser(0, 0.2);
    backgroundsStack->SetTitle(histName.c_str());
    backgroundsStack->GetYaxis()->SetTitle("# events");
    backgroundsStack->GetYaxis()->SetTitleSize(0.06);
    backgroundsStack->GetXaxis()->SetTitle(xAxisTitle.c_str());
    backgroundsStack->GetXaxis()->SetTitleSize(0.06);
    
    hists[kData]->Draw("samePE");
    legend->Draw("same");
  }
    
    
  canvas->SaveAs(outputPath.c_str());
}
