#include "../analysis/include/Helpers.hpp"

int canvasWidth = 1000;
int canvasHeight = 1800;

string basePath = "results/";

map<EDataset, string> inputPaths = {
  { kMCcep    , "raw_plots_cep_sc.root" },
  { kMCqedSC  , "raw_plots_qed_sc.root" },
  { kMCqedSL  , "raw_plots_qed_sl.root" },
  { kMClbl    , "raw_plots_lbl_sc.root" },
};

//            name    x label y label logX  logY  xMin    xMax    yMax   rebin
typedef tuple<string, string, string, bool, bool, double, double, double, int> histParams;

vector<histParams> pairHistParams = {
// name          x label           y label    logX    logY     xMin    xMax    yMax
  {"pair_m"     , "m (GeV/c)"     , "Entries", true , true   , 0.0 ,  90.  , 1.0   , 1 },
  {"pair_pt"    , "p_{T} (GeV/c)" , "Entries", true , false  , 0.001 , 0.4   , 0.2   , 1 },
  {"pair_pz"    , "p_{z} (GeV/c)" , "Entries", true , true   , 0.0   , 1000  , 1.0   , 1 },
  {"pair_y"     , "y"             , "Entries", false, false  , -10.0 , 10.0  , 0.09  , 1 },
  {"pair_aco"   , "A_{#phi}"      , "Entries", true , true   , 0.0   , 1.0   , 0.5   , 1 },
};

vector<histParams> singleHistParams = {
// name          x label           y label    logX    logY     xMin    xMax    yMax
  {"single_pt"  , "p_{T} (GeV/c)" , "Entries", true , true   , 0.1   , 50    , 0.5   , 5 },
  {"single_pz"  , "p_{z} (GeV/c)" , "Entries", false, true   , 0.0   , 1000  , 1.0   , 5 },
  {"single_y"   , "y"             , "Entries", false, false  , -10.0 , 10.0  , 0.04  , 1 },
  {"single_eta" , "#eta"          , "Entries", false, false  , -10.0 , 10.0  , 0.04  , 1 },
  {"single_phi" , "#phi"          , "Entries", false, false  , -4.0  , -4.0  , 0.02  , 1 },
};

TH1D* DrawPlot(TFile *inFile, histParams params, int color, bool firstFile)
{
  auto &[histName, xTitle, yTitle, logX, logY, xMin, xMax, yMax, rebin] = params;
  
  TH1D *hist = (TH1D*)inFile->Get(histName.c_str());
  hist->SetLineColor(color);
  hist->GetXaxis()->SetTitle(xTitle.c_str());
  hist->GetYaxis()->SetTitle(yTitle.c_str());
  if(logX) gPad->SetLogx();
  if(logY) gPad->SetLogy();
  
  hist->RebinX(rebin);
  hist->Scale(1./hist->GetEntries());
  hist->SetMaximum(yMax);
  
  hist->Sumw2(false);
  hist->Draw(firstFile ? "" : "same");
  
  hist->GetXaxis()->SetRangeUser(xMin, xMax);
  
  return hist;
}

void drawGenLevelPlots()
{
  TCanvas *canvasPair = new TCanvas("Gen-level pair plots", "Gen-level pair plots",
                                    canvasWidth, canvasHeight);
  canvasPair->Divide(2,3);
  
  TCanvas *canvasSingle = new TCanvas("Gen-level single plots", "Gen-level single plots",
                                      canvasWidth, canvasHeight);
  canvasSingle->Divide(2,3);
  
  TLegend *legend = new TLegend(0.2,0.2,0.8,0.8);
  
  gStyle->SetOptStat(0);
  
  bool firstFile=true;
  
  for(auto &[dataset, path] : inputPaths){
    if(dataset == kData) continue;
    
    string fileName = basePath+path;
    TFile *inFile = TFile::Open(fileName.c_str());
    
    int color = datasetColor.at(dataset);
    string sampleName = datasetDescription.at(dataset);
    
    int iPad=1;
    bool firstHist=true;
    for(auto &params : pairHistParams){
      canvasPair->cd(iPad++);
      TH1D* hist = DrawPlot(inFile, params, color, firstFile);
      if(firstHist){
        legend->AddEntry(hist, sampleName.c_str(), "l");
        firstHist = false;
      }
    }
    canvasPair->cd(iPad);
    legend->Draw();
    
    iPad=1;
    for(auto &params : singleHistParams){
      canvasSingle->cd(iPad++);
      DrawPlot(inFile, params, color, firstFile);
    }
    canvasSingle->cd(iPad);
    legend->Draw();
    
    firstFile=false;
  }

  canvasSingle->SaveAs("plots/gen_level_single.pdf");
  canvasPair->SaveAs("plots/gen_level_pair.pdf");
  
}
