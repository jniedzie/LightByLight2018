#include "../include/Helpers.hpp"

string inputPath  = "../results/basicPlots_noHFcheck.root";
string outputPath = "../plots/distributions";

//double qedInitialNevents = 67820000; // total

map<EDataset, double> initialNevents = {
//  { kMCqedSC, 67820000  }, // total
  { kMCqedSC, 960000    }, // currently available
  { kMClbl  , 362000    }, // currently available
  { kMCcep  , 144900    }, // currently available
};

map<EDataset, double> crossSection = { // μb
  { kMCqedSC, 8830    },
  { kMClbl  , 2.59    },
//  { kMCcep  , 5.8  },
  { kMCcep  , 0.0058  },
};

//double luminosity = 1847.99; // from CMS pages, 1/μb
double luminosity = 1609.910015010; // from brilcalc, 1/μb
//double luminosity = 1847.99; // from brilcalc, 1/μb

const double markerSize = 0.5;


// Only those datasets will be analyzed
const vector<EDataset> datasetsToAnalyze = {
  kData,
  kMCcep,
  kMCqedSC,
//  kMCqedSL,
  kMClbl,
  
};

vector<tuple<string, string, bool, bool, int, int, int>> histParams = {
  // title                  x axis title                  log Y   norm?  iCanvas iPad rebin
  { "lbl_acoplanarity"       , "A_{#phi}^{#gamma#gamma}" , false, false ,   0   , 1  , 1 },
  { "lbl_photon_et"          , "photon E_{t} (GeV)"      , false, false ,   0   , 2  , 1 },
  { "lbl_photon_eta"         , "photon #eta"             , false, false ,   0   , 3  , 1 },
  { "lbl_photon_phi"         , "photon #phi"             , false, false ,   0   , 4  , 1 },
  { "lbl_diphoton_mass"      , "diphoton m_{inv} (GeV)"  , false, false ,   0   , 5  , 1 },
  { "lbl_diphoton_rapidity"  , "diphoton rapidity"       , false, false ,   0   , 6  , 1 },
  { "lbl_diphoton_pt"        , "diphoton p_{t}"          , false, false ,   0   , 7  , 1 },
  { "lbl_cut_through"        , "# cut"                   , false, true  ,   0   , 8  , 1 },

  { "lbl_photon_et_high_aco"          , "photon E_{t} (GeV)"      , false, false ,   4   , 1   , 1 },
  { "lbl_photon_eta_high_aco"         , "photon #eta"             , false, false ,   4   , 2   , 1 },
  { "lbl_photon_phi_high_aco"         , "photon #phi"             , false, false ,   4   , 3   , 1 },
  { "lbl_diphoton_mass_high_aco"      , "diphoton m_{inv} (GeV)"  , false, false ,   4   , 4   , 1 },
  { "lbl_diphoton_rapidity_high_aco"  , "diphoton rapidity"       , false, false ,   4   , 5   , 1 },
  { "lbl_diphoton_pt_high_aco"        , "diphoton p_{t}"          , false, false ,   4   , 6   , 1 },
  { "lbl_HFp_high_aco"                , "HF+ energy (GeV)"        , true , true  ,   4   , 7   , 1 },
  { "lbl_HFm_high_aco"                , "HF- energy (GeV)"        , true , true  ,   4   , 8   , 1 },
  { "lbl_HFp_leading_tower_high_aco"  , "HF+ leading energy (GeV)", true , true  ,   4   , 9   , 1 },
  { "lbl_HFm_leading_tower_high_aco"  , "HF- leading energy (GeV)", true , true  ,   4   , 10  , 1 },
  
  { "lbl_triphoton_mass"     , "triphoton m_{inv} (GeV)" , false, false ,   0   , 9  , 1 },
  { "lbl_triphoton_rapidity" , "triphoton rapidity"      , false, false ,   0   , 10 , 1 },
  { "lbl_triphoton_pt"       , "triphoton p_{t}"         , false, false ,   0   , 11 , 1 },
  
  { "qed_acoplanarity"       , "A_{#phi}^{e^{+}e^{-}}"   , true , false ,   1   , 1  , 1 },
  { "qed_electron_pt"        , "electron p_{t} (GeV)"    , false, false ,   1   , 2  , 1 },
  { "qed_electron_eta"       , "electron #eta"           , false, false ,   1   , 3  , 1 },
  { "qed_electron_phi"       , "electron #phi"           , false, false ,   1   , 4  , 1 },
  { "qed_dielectron_mass"    , "dielectron m_{inv} (GeV)", false, false ,   1   , 5  , 1 },
  { "qed_dielectron_rapidity", "dielectron rapidity"     , false, false ,   1   , 6  , 1 },
  { "qed_dielectron_pt"      , "dielectron p_{t}"        , false, false ,   1   , 7  , 1 },
  { "qed_cut_through"        , ""                        , false, false ,   1   , 8  , 1 },
  { "qed_electron_cutflow"   , "# cut"                   , false, false ,   1   , 9  , 1 },
  
  { "qed_HFp_no_cuts"                , "HF+ energy (GeV)"        , true , true  ,   2   , 1 , 1},
  { "qed_HFm_no_cuts"                , "HF- energy (GeV)"        , true , true  ,   2   , 2 , 1},
  { "qed_HFp_leading_tower_no_cuts"  , "HF+ leading energy (GeV)", true , true  ,   2   , 3 , 1},
  { "qed_HFm_leading_tower_no_cuts"  , "HF- leading energy (GeV)", true , true  ,   2   , 4 , 1},
  { "qed_HFp"                , "HF+ energy (GeV)"        , true , true  ,   2   , 5  , 1 },
  { "qed_HFm"                , "HF- energy (GeV)"        , true , true  ,   2   , 6  , 1 },
  { "qed_HFp_leading_tower"  , "HF+ leading energy (GeV)", true , true  ,   2   , 7  , 1 },
  { "qed_HFm_leading_tower"  , "HF- leading energy (GeV)", true , true  ,   2   , 8  , 1 },
  
  { "qed_aco_HF_gt_5"        , "A_{#phi}^{e^{+}e^{-}}"   , true , false ,   2   , 9  , 1 },
  { "qed_aco_HF_gt_10"       , "A_{#phi}^{e^{+}e^{-}}"   , true , false ,   2   , 10 , 1 },
  { "qed_aco_HF_gt_15"       , "A_{#phi}^{e^{+}e^{-}}"   , true , false ,   2   , 11 , 1 },
  
  { "qed_acoplanarity_no_cuts"       , "A_{#phi}^{e^{+}e^{-}}"   , true , false ,   3   , 1 , 1},
  { "qed_electron_pt_no_cuts"        , "electron p_{t} (GeV)"    , false, false ,   3   , 2 , 1},
  { "qed_electron_eta_no_cuts"       , "electron #eta"           , false, false ,   3   , 3 , 1},
  { "qed_electron_phi_no_cuts"       , "electron #phi"           , false, false ,   3   , 4 , 1},
  { "qed_dielectron_mass_no_cuts"    , "dielectron m_{inv} (GeV)", false, false ,   3   , 5 , 1},
  { "qed_dielectron_mass_low_no_cuts", "dielectron m_{inv} (GeV)", false, false ,   3   , 6 , 1},
  { "qed_dielectron_rapidity_no_cuts", "dielectron rapidity"     , false, false ,   3   , 7 , 1},
  { "qed_dielectron_pt_no_cuts"      , "dielectron p_{t}"        , false, false ,   3   , 8 , 1},
};

void setCutflowLabels(TH1D *hist, bool lbl)
{
  vector<const char *> labelsQED = {
    "Initial", "Trigger", "HB NEE", "HE NEE", "HF+ NEE", "HF- NEE", "EB NEE",
    "EE NEE", "CHE", "2 good electrons", "dielectron m_{inv}", "dielectron p_{t}", "dielectron y"
  };
  
  vector<const char *> labelsLbL = {
    "Initial", "Trigger", "CHE", "HB NEE", "HE NEE", "HF+ NEE", "HF- NEE", "EB NEE",
    "EE NEE", "2 good photons", "diphoton m_{inv}", "diphoton p_{t}", "diphoton y", "acoplanarity"
  };
  
  int i=1;
  for(auto label : (lbl ? labelsLbL : labelsQED)){
    hist->GetXaxis()->SetBinLabel(i, label);
    hist->GetXaxis()->ChangeLabel(i, 45);
    i++;
  }
  hist->LabelsOption("u", "X");
//  gPad->SetLeftMargin(0.17);
//  gPad->SetBottomMargin(0.22);
}

map<EDataset, string> legendOptions = {
  {kData,     "elp" },
  {kMCcep,    "f"   },
  {kMCqedSL,  "f"   },
  {kMCqedSC,  "f"   },
  {kMClbl,    "f"   },
};

void prepareHist(TH1D *hist, EDataset dataset)
{
  hist->SetLineColor(datasetColor.at(dataset));
  hist->SetFillColorAlpha(datasetColor.at(dataset), 0.2);
  
  hist->SetMarkerColor(datasetColor.at(dataset));
  hist->SetMarkerStyle(20);
  hist->SetMarkerSize(markerSize);
  
//  hist->Scale(1./hist->GetEntries());
//  hist->Sumw2(false);
}



map<EDataset, TH1D*> getHistsFromFile(TFile *inFile, string histName)
{
  map<EDataset, TH1D*> hists;
  
  for(EDataset dataset : datasetsToAnalyze){
    hists[dataset] = (TH1D*)inFile->Get((histName+"_"+datasetName.at(dataset)).c_str());
    if(!hists[dataset]){
      cout<<"ERROR -- no histogram \""<<histName<<"\" found for dataset "<<datasetName.at(dataset)<<endl;
      continue;
    }
    prepareHist(hists[dataset], dataset);
  }
  return hists;
}

TLegend* getLegendForHists(map<EDataset, TH1D*> hists)
{
  TLegend *legend = new TLegend(0.6, 0.7, 0.9, 0.9 );
  for(EDataset dataset : datasetsToAnalyze){
    legend->AddEntry(hists[dataset], datasetDescription.at(dataset).c_str(), legendOptions[dataset].c_str());
  }
  return legend;
}

int getTotalBackgroundEntries(map<EDataset, TH1D*> hists)
{
  int totalBackgroundEntries = 0;
  
  for(EDataset dataset : datasetsToAnalyze){
    if(dataset != kData) totalBackgroundEntries += hists[dataset]->GetEntries();
  }
  return totalBackgroundEntries;
}

double getMaxHistValue(TH1D *hist)
{
  double max = -999999;
  for(int i=0; i<hist->GetNbinsX(); i++){
    double value = hist->GetBinContent(i);
    if(value > max) max = value;
  }
  return max;
}

double getMinHistValue(TH1D *hist)
{
  double min = 999999;
  for(int i=0; i<hist->GetNbinsX(); i++){
    double value = hist->GetBinContent(i);
    if(value < min) min = value;
  }
  return min;
}

double getMaxValueInHists(map<EDataset, TH1D*> hists)
{
  double maxValue = -999;
  
  for(EDataset dataset : datasetsToAnalyze){
    for(int i=0; i<hists[dataset]->GetNbinsX(); i++){
      double value = hists[dataset]->GetBinContent(i);
      if(value > maxValue) maxValue = value;
    }
  }
  return maxValue;
}

void normalizeHists(map<EDataset, TH1D*> hists, bool normalize, bool cutFlow)
{
  if(normalize){
    int totalBackgroundEntries = getTotalBackgroundEntries(hists);
    
    for(EDataset dataset : datasetsToAnalyze){
      if(dataset == kData) continue;
      
      if(hists[dataset]->GetEntries() == 0) continue;
      
      if(cutFlow) hists[dataset]->Scale(1./hists[dataset]->GetEntries());
      else        hists[dataset]->Scale(1./totalBackgroundEntries);
//      hists[dataset]->Sumw2(false);
    }
  }
  else{
    for(EDataset dataset : datasetsToAnalyze){
      if(dataset == kData) continue;
      hists[dataset]->Scale(luminosity*crossSection[dataset]/initialNevents[dataset]);
      hists[dataset]->Sumw2(false);
    }
  }
}

void drawBasicPlots()
{
  gStyle->SetOptStat(0);
  
  TFile *inFile = TFile::Open(inputPath.c_str());
  
  vector<TCanvas*> canvas;
  
  canvas.push_back(new TCanvas("Canvas LbL", "Canvas LbL", 2800, 1800));
  canvas.push_back(new TCanvas("Canvas QED", "Canvas QED", 2800, 1800));
  canvas.push_back(new TCanvas("Canvas calo", "Canvas calo", 2800, 1800));
  canvas.push_back(new TCanvas("Canvas QED no cuts", "Canvas QED no cuts", 2800, 1800));
  canvas.push_back(new TCanvas("Canvas LbL high aco", "Canvas LbL high aco", 2800, 1800));
  canvas[0]->Divide(4,3);
  canvas[1]->Divide(3,3);
  canvas[2]->Divide(4,3);
  canvas[3]->Divide(3,3);
  canvas[4]->Divide(4,3);
  
  for(auto &[histName, xAxisTitle, logY, normalize, iCanvas, iPad, rebin] : histParams){
    
    map<EDataset, TH1D*> hists = getHistsFromFile(inFile, histName);
    
    
    THStack *backgroundsStack = new THStack();
    TH1D *dataHist;
    
    for(EDataset dataset : datasetsToAnalyze){
      hists[dataset]->Rebin(rebin);
      hists[dataset]->Scale(1./rebin);
      
      if(dataset != kData)  backgroundsStack->Add(hists[dataset]);
      else                  dataHist = hists[dataset];
    }
    
    //
    // Draw main plot
    //
    
    canvas[iCanvas]->cd(iPad);
    
    TPad *histsPad = new TPad("histsPad", "histsPad", 0.0, 0.0, 1., 1.);
    histsPad->SetTopMargin(0.1);
		histsPad->SetLeftMargin(0.15);
		histsPad->SetBottomMargin(0.4);
    histsPad->SetLogy(logY);
		histsPad->Draw();
		histsPad->cd();
    
    bool isCutFlow = histName.find("cut_through") != string::npos;
    
    normalizeHists(hists, normalize, isCutFlow);
    
    if(normalize){
      dataHist->DrawNormalized("PE");
    }
    else{
      dataHist->Draw("PE");
      dataHist->SetMaximum(1.5 * getMaxValueInHists(hists));
    }
    backgroundsStack->Draw(isCutFlow ? "sameNostack" : "same");
    getLegendForHists(hists)->Draw();
    
    dataHist->SetTitle("");
    
    dataHist->GetXaxis()->SetTitle("");
    dataHist->GetXaxis()->SetTitleSize(0.06);
    dataHist->GetXaxis()->SetLabelSize(0);
    
    dataHist->GetYaxis()->SetTitle("# events");
    dataHist->GetYaxis()->SetTitleSize(0.06);
    dataHist->GetYaxis()->SetTitleOffset(1.15);
    dataHist->GetYaxis()->SetLabelSize(0.06);
    
    //
    // Draw ratio
    //
    
    TPad *ratioPad = new TPad("ratioPad", "ratioPad", 0.0, 0.1, 1.0, 0.4);
    ratioPad->SetTopMargin(0);
    ratioPad->SetLeftMargin(0.15);
    ratioPad->SetBottomMargin(0.5);
    ratioPad->SetGrid();
    ratioPad->Draw();
    ratioPad->cd();
    
    TH1D *ratio = new TH1D(*dataHist);
    TH1D *backgroundsSum;
    bool first = true;
    
    for(auto &[dataset, hist] : hists){
      if(dataset == kData) continue;
      if(first){
        backgroundsSum = new TH1D(*hist);
        first = false;
      }
      else{
        backgroundsSum->Add(hist);
      }
    }
    
    ratio->Divide(backgroundsSum);
    ratio->Draw();
    
    ratio->SetMaximum(1.2 * getMaxHistValue(ratio));
    ratio->SetMinimum(0.8 * getMinHistValue(ratio));
    
    ratio->SetTitle("");
    
    if(histName == "qed_cut_through") setCutflowLabels(ratio, false);
    if(histName == "lbl_cut_through") setCutflowLabels(ratio, true);
    
    
    
    ratio->GetXaxis()->SetTitle(xAxisTitle.c_str());
    ratio->GetXaxis()->SetTitleSize(0.2);
    ratio->GetXaxis()->SetTitleOffset(1.1);
    ratio->GetXaxis()->SetLabelSize(0.2);
    
    if(histName == "qed_cut_through" || histName == "lbl_cut_through"){
      ratio->GetXaxis()->SetLabelSize(0.16);
      ratio->GetXaxis()->SetLabelOffset(0.05);
      ratioPad->SetBottomMargin(0.55);
    }
    
    ratio->GetYaxis()->SetTitle("Data/MC ");
    ratio->GetYaxis()->SetTitleSize(0.17);
    ratio->GetYaxis()->SetTitleOffset(0.3);
    ratio->GetYaxis()->SetLabelSize(0.15);
    ratio->GetYaxis()->SetNdivisions(5);
    
  }
    
    
  canvas[0]->SaveAs((outputPath+"_LbL.pdf").c_str());
  canvas[1]->SaveAs((outputPath+"_QED.pdf").c_str());
  canvas[2]->SaveAs((outputPath+"_Calo.pdf").c_str());
  canvas[3]->SaveAs((outputPath+"_QED_no_cuts.pdf").c_str());
}
