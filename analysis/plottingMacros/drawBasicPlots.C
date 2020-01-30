#include "../include/Helpers.hpp"

string inputPath  = "../results/basicPlots.root";
string outputPath = "../plots/distributions";

// Only those datasets will be analyzed
const vector<EDataset> datasetsToAnalyze = {
  kData,
  kMCqedSC,
//  kMCqedSL,
//  kMClbl,
//  kMCcep
};

vector<tuple<string, string, bool, bool>> histParams = {
  // title                  x axis title                  log Y   normalize
  { "lbl_acoplanarity"       , "A_{#phi}^{#gamma#gamma}" , false, false },
  { "lbl_photon_et"          , "photon E_{t} (GeV)"      , false, false },
  { "lbl_photon_eta"         , "photon #eta"             , false, false },
  { "lbl_photon_phi"         , "photon #phi"             , false, false },
  { "lbl_diphoton_mass"      , "diphoton m_{inv} (GeV)"  , false, false },
  { "lbl_diphoton_rapidity"  , "diphoton rapidity"       , false, false },
  { "lbl_diphoton_pt"        , "diphoton p_{t}"          , false, false },
  { "lbl_cut_through"        , "# cut"                   , true , true  },
  
  { "qed_acoplanarity"       , "A_{#phi}^{e^{+}e^{-}}"   , true , false },
  { "qed_electron_pt"        , "electron p_{t} (GeV)"    , false, false },
  { "qed_electron_eta"       , "electron #eta"           , false, false },
  { "qed_electron_phi"       , "electron #phi"           , false, false },
  { "qed_dielectron_mass"    , "dielectron m_{inv} (GeV)", false, false },
  { "qed_dielectron_rapidity", "dielectron rapidity"     , false, false },
  { "qed_dielectron_pt"      , "dielectron p_{t}"        , false, false },
  { "qed_cut_through"        , "# cut"                   , true , false },
};

void prepareHist(TH1D *hist, EDataset dataset)
{
  hist->SetLineColor(datasetColor.at(dataset));
  hist->SetFillColorAlpha(datasetColor.at(dataset), 0.2);
  
  if(dataset == kData){
    hist->SetMarkerStyle(20);
    hist->SetMarkerColor(datasetColor.at(dataset));
    hist->SetMarkerSize(0.5);
  }
  
//  hist->Scale(1./hist->GetEntries());
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
  
  TCanvas *canvasLbL = new TCanvas("Canvas LbL", "Canvas LbL", 1000, 1800);
  TCanvas *canvasQED = new TCanvas("Canvas QED", "Canvas QED", 1000, 1800);
  canvasLbL->Divide(2,4);
  canvasQED->Divide(2,4);
  gStyle->SetOptStat(0);
  
  int iCanvasLbL=1;
  int iCanvasQED=1;
  
  for(auto &[histName, xAxisTitle, logY, normalize] : histParams){
    map<EDataset, TH1D*> hists;
    TLegend *legend = new TLegend(0.6, 0.6, 0.9, 0.9 );
    THStack *backgroundsStack = new THStack();
    
    double maxYvalue = 0;
    
    int totalBackgroundEntries=0;
    
    for(EDataset dataset : datasetsToAnalyze){
      string legendOption = legendOptions[dataset];
      
      hists[dataset] = (TH1D*)inFile->Get((histName+"_"+datasetName.at(dataset)).c_str());
      if(!hists[dataset]){
        cout<<"ERROR -- no histogram found for dataset "<<datasetName.at(dataset)<<endl;
        continue;
      }
      
      for(int i=0; i<hists[dataset]->GetNbinsX(); i++){
        double value = hists[dataset]->GetBinContent(i);
        if(value > maxYvalue) maxYvalue = value;
      }
      
      legend->AddEntry(hists[dataset], datasetDescription.at(dataset).c_str(), legendOption.c_str());
      
      prepareHist(hists[dataset], dataset);
      
      if(dataset != kData){
        backgroundsStack->Add(hists[dataset]);
        totalBackgroundEntries += hists[dataset]->GetEntries();
      }
    }
    
    if(histName.find("lbl") != string::npos) canvasLbL->cd(iCanvasLbL++);
    else if(histName.find("qed") != string::npos) canvasQED->cd(iCanvasQED++);
    else cout<<"\n\nERROR -- Cannot determine which canvas to use!!\n\n"<<endl;
    

    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.15);
    
    gPad->SetLogy(logY);
    
    if(normalize){
      
      for(EDataset dataset : datasetsToAnalyze){
        if(dataset == kData) continue;
        hists[dataset]->Scale(1./totalBackgroundEntries);
        hists[dataset]->Sumw2(false);
      }
      backgroundsStack->Draw();
      hists[kData]->DrawNormalized("samePE");
    }
    else{
      backgroundsStack->Draw();
      hists[kData]->Draw("samePE");
      backgroundsStack->SetMaximum(1.5*maxYvalue);
    }
    
    
    
    
    backgroundsStack->SetTitle(histName.c_str());
    backgroundsStack->GetYaxis()->SetTitle("# events");
    backgroundsStack->GetYaxis()->SetTitleSize(0.06);
    backgroundsStack->GetXaxis()->SetTitle(xAxisTitle.c_str());
    backgroundsStack->GetXaxis()->SetTitleSize(0.06);
    
    
    
    
    legend->Draw("same");
    
    
  }
    
    
  canvasLbL->SaveAs((outputPath+"_LbL.pdf").c_str());
  canvasQED->SaveAs((outputPath+"_QED.pdf").c_str());
}
