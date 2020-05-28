#include "../include/Helpers.hpp"

string inputPath  = "../results/basicPlots_default.root";
//string inputPath  = "../results/basicPlots_default_inverted.root";
//string inputPath  = "../results/basicPlots_data_muchLooserCHE.root";
//string inputPath  = "../results/basicPlots_data_noPixelTracks.root";
//string inputPath  = "../results/basicPlots_data_ZDCcut.root";
//string inputPath  = "../results/basicPlots_data_ZDCcut_200.root";
//string inputPath  = "../results/basicPlots_data_totalZDCcut.root";
//string inputPath  = "../results/basicPlots_data_newCuts.root";

//string inputPath  = "../results/basicPlots_test.root";

string outputPath = "../plots/distributions";

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

const double markerSize = 0.5;
const bool drawLegends = true;

// Only those datasets will be analyzed
const vector<EDataset> datasetsToAnalyze = {
  kData,
  kMCcep,
  kMCqedSC,
//  kMCqedSL,
  kMClbl,
};

const double goldenRatio = 1.61803398875;
const int baseHistWidth  = 600;
const int baseHistHeight = baseHistWidth/goldenRatio;

vector<tuple<string, int, int>> canvasParams = {
  // title       col row
  {"Photon"             , 3 , 3 }, // 0
  {"Diphoton"           , 2 , 4 }, // 1
  {"Triphoton"          , 2 , 2 }, // 2
  {"Electron"           , 2 , 2 }, // 3
  {"Dielectron"         , 2 , 3 }, // 4
  {"Same sign ee"       , 2 , 2 }, // 5
  {"QED calo"           , 3 , 3 }, // 6
  {"tracks"             , 3 , 3 }, // 7
  {"vertex"             , 3 , 3 }, // 8
  {"vertex/track"       , 2 , 2 }, // 9
  {"LbL calo"           , 3 , 2 }, // 10
  {"N objects"          , 3 , 3 }, // 11
  {"Photons"            , 2 , 3 }, // 12
  {"Acoplanarity (LbL)" , 1 , 1 }, // 13
  {"Electrons"          , 2 , 3 }, // 14
  {"Acoplanarity (QED)" , 1 , 1 }, // 15
};

enum ENorm { kXsec, kEntries, kFirstBin, kNoScaling };

vector<tuple<string, string, bool, ENorm, int, int, int, double, double>> histParams = {
  // title                            x axis title                  log Y  norm      iCanvas iPad rebin xMin xMax
  { "lbl_photon_et_all"               , "photon E_{t} (GeV)"      , false, kXsec    ,   0   , 1  , 1 ,   0  , 30  },
  { "lbl_photon_eta_all"              , "photon #eta"             , false, kXsec    ,   0   , 2  , 1 , -3.0 , 3.0 },
  { "lbl_photon_phi_all"              , "photon #phi"             , false, kXsec    ,   0   , 3  , 1 , -3.5 , 3.5 },
  { "lbl_bad_photon_et_all"           , "bad photon E_{t} (GeV)"  , false, kXsec    ,   0   , 4  , 1 ,   0  , 30  },
  { "lbl_bad_photon_eta_all"          , "bad photon #eta"         , false, kXsec    ,   0   , 5  , 1 , -3.5 , 3.5 },
  { "lbl_bad_photon_phi_all"          , "bad photon #phi"         , false, kXsec    ,   0   , 6  , 1 , -3.5 , 3.5 },
  { "lbl_nee_failing_all"             , ""                        , false, kEntries ,   0   , 7  , 1 ,   0  , 10  },
  
  { "lbl_acoplanarity_all"            , "A_{#phi}^{#gamma#gamma}" , false, kXsec    ,   1   , 1  , 1 ,   0  , 0.2 },
  { "lbl_diphoton_mass_all"           , "diphoton m_{inv} (GeV)"  , false, kXsec    ,   1   , 2  , 1 ,   0  , 50  },
  { "lbl_diphoton_pt_all"             , "diphoton p_{t}"          , false, kXsec    ,   1   , 3  , 1 ,   0  , 2.0 },
  { "lbl_diphoton_rapidity_all"       , "diphoton rapidity"       , false, kXsec    ,   1   , 4  , 1 , -3.0 , 3.0 },
  { "lbl_n_all_photons_all"           , "N_{photons}^{all}"       , false, kEntries ,   1   , 5  , 1 ,   0  , 100 },
  { "lbl_n_all_calo_towers_all"       , "N_{towers}^{all}"        , false, kEntries ,   1   , 6  , 1 ,   0  , 100 },
  { "lbl_n_all_L1EG_all"              , "N_{L1EG}^{all}"          , false, kEntries ,   1   , 7  , 1 ,   0  , 100 },
  { "lbl_cut_flow_all"                , ""                        , true , kXsec    ,   1   , 8  , 1 ,   0  , 12  },
  
  { "lbl_triphoton_mass_all"          , "triphoton m_{inv} (GeV)" , false, kXsec    ,   2   , 1  , 2 ,   0  , 30  },
  { "lbl_triphoton_rapidity_all"      , "triphoton rapidity"      , false, kXsec    ,   2   , 2  , 1 , -3.0 , 3.0 },
  { "lbl_triphoton_pt_all"            , "triphoton p_{t}"         , false, kXsec    ,   2   , 3  , 2 ,   0  , 30  },
  
  { "qed_electron_pt_all"             , "electron p_{t} (GeV)"    , false, kXsec    ,   3   , 1  , 1 ,   0  , 40  },
  { "qed_electron_eta_all"            , "electron #eta"           , false, kXsec    ,   3   , 2  , 1 , -2.5 , 2.5 },
  { "qed_electron_phi_all"            , "electron #phi"           , false, kXsec    ,   3   , 3  , 1 , -3.5 , 3.5 },
  { "qed_electron_cutflow_all"        , ""                        , true , kXsec    ,   3   , 4  , 1 ,   0  , 12  },
  
  { "qed_acoplanarity_all"            , "A_{#phi}^{e^{+}e^{-}}"   , true , kXsec    ,   4   , 1  , 1 ,   0  , 0.1 },
  { "qed_dielectron_mass_all"         , "dielectron m_{inv} (GeV)", false, kXsec    ,   4   , 2  , 1 ,   0  , 100 },
  { "qed_dielectron_pt_all"           , "dielectron p_{t}"        , false, kXsec    ,   4   , 3  , 1 ,   0  , 2.0 },
  { "qed_dielectron_rapidity_all"     , "dielectron rapidity"     , false, kXsec    ,   4   , 4  , 1 ,  -3.0, 3.0 },
  { "qed_cut_flow_all"                , ""                        , false, kXsec    ,   4   , 5  , 1 ,   0  , 10  },
  
  { "samesign_dielectron_mass_all"    , "dielectron m_{inv} (GeV)", false, kXsec    ,   5   , 1  , 1 ,   0  , 100 },
  { "samesign_dielectron_pt_all"      , "dielectron p_{t}"        , false, kXsec    ,   5   , 2  , 1 ,   0  , 2.0 },
  { "samesign_dielectron_rapidity_all", "dielectron rapidity"     , false, kXsec    ,   5   , 3  , 1 ,  -3.0, 3.0 },
  
  { "qed_HFp_all"                     , "HF+ energy (GeV)"        , true , kEntries ,   6   , 1  , 1 ,   0  , 10  },
  { "qed_HFm_all"                     , "HF- energy (GeV)"        , true , kEntries ,   6   , 2  , 1 ,   0  , 10  },
  { "qed_HFp_leading_tower_all"       , "HF+ leading energy (GeV)", true , kEntries ,   6   , 3  , 1 ,   0  , 10  },
  { "qed_HFm_leading_tower_all"       , "HF- leading energy (GeV)", true , kEntries ,   6   , 4  , 1 ,   0  , 10  },
  { "qed_EB_leading_tower_all"        , "EB leading energy (GeV)" , true , kEntries ,   6   , 5  , 1 ,   0  , 5   },
  { "qed_EE_leading_tower_all"        , "EE leading energy (GeV)" , true , kEntries ,   6   , 6  , 1 ,   0  , 10  },
  { "qed_HB_leading_tower_all"        , "HB leading energy (GeV)" , true , kEntries ,   6   , 7  , 1 ,   0  , 5   },
  { "qed_HE_leading_tower_all"        , "HE leading energy (GeV)" , true , kEntries ,   6   , 8  , 1 ,   0  , 5  },
  
  { "track_charge_all"                , "track charge"            , false, kEntries ,   7   , 1  , 1 ,   -1 , 2   },
  { "track_pt_all"                    , "track p_{t} (GeV)"       , false, kEntries ,   7   , 2  , 5 ,   0  , 10  },
  { "track_eta_all"                   , "track #eta"              , false, kEntries ,   7   , 3  , 1 , -3.0 , 3.0 },
  { "track_phi_all"                   , "track #phi"              , false, kEntries ,   7   , 4  , 1 , -3.5 , 3.5 },
  { "track_chi2_all"                  , "track #chi^{2}/NDF"      , true , kEntries ,   7   , 5  , 1 ,   0  , 20  },
  { "track_valid_hits_all"            , "N_{hits}^{valid}"        , false, kEntries ,   7   , 6  , 1 ,   0  , 30  },
  { "track_missing_hits_all"          , "N_{hits}^{missing}"      , false, kEntries ,   7   , 7  , 1 ,   0  , 20  },
  { "track_purity_all"                , "track purity"            , false, kEntries ,   7   , 8  , 1 ,   0  , 20  },
  { "tracks_cut_flow_all"             , ""                        , false, kFirstBin,   7   , 9  , 1 ,   0  , 10  },
  
  { "track_dxy_all"                   , "track d_{xy} (cm)"       , true , kEntries ,   8   , 1  ,20 ,    0 , 0.2 },
  { "track_dz_all"                    , "track d_{z} (cm)"        , true , kEntries ,   8   , 2  ,300,  -30 , 30  },
  { "track_dxy_from_bs_all"           , "|track, BS|_{xy} (cm)"   , true , kEntries ,   8   , 3  ,100,    0 , 0.5 },
  { "track_dz_from_bs_all"            , "|track, BS|_{z} (cm)"    , true , kEntries ,   8   , 4  ,300,    0 , 30  },
  { "track_dxy_over_sigma_all"        , "|d_{xy}/#sigma_{xy}|"    , true , kEntries ,   8   , 5  , 2 ,    0 , 10  },
  { "track_dz_over_sigma_all"         , "|d_{z}/#sigma_{z}|"      , true , kEntries ,   8   , 6  , 2 ,    0 , 10  },
  { "track_vx_all"                    , "track vertex x (cm)"     , true , kEntries ,   8   , 7  ,25 ,  -0.5, 0.5 },
  { "track_vy_all"                    , "track vertex y (cm)"     , true , kEntries ,   8   , 8  ,25 ,  -0.5, 0.5 },
  { "track_vz_all"                    , "track vertex z (cm)"     , true , kEntries ,   8   , 9  ,600,  -30 , 30  },
  
  { "track_dxy_1_track_all"           , "1 track d_{xy} (cm)"     , true , kEntries ,   9   , 1  ,20 ,    0 , 0.2 },
  { "track_dxy_2_track_all"           , "2 tracks d_{xy} (cm)"    , true , kEntries ,   9   , 2  ,20 ,    0 , 0.2 },
  { "track_dxy_3_track_all"           , "3 tracks d_{xy} (cm)"    , true , kEntries ,   9   , 3  ,20 ,    0 , 0.2 },
  { "track_dxy_ge4_track_all"         , "≥4 tracks d_{xy} (cm)"   , true , kEntries ,   9   , 4  ,20 ,    0 , 0.2 },
  
  { "lbl_EB_leading_tower_all"        , "EB leading energy (GeV)" , true , kEntries ,   10   , 1  , 1 ,   0  , 5   },
  { "lbl_EE_leading_tower_all"        , "EE leading energy (GeV)" , true , kEntries ,   10   , 2  , 1 ,   0  , 10  },
  { "lbl_HB_leading_tower_all"        , "HB leading energy (GeV)" , true , kEntries ,   10   , 3  , 1 ,   0  , 5   },
  { "lbl_HE_leading_tower_all"        , "HE leading energy (GeV)" , true , kEntries ,   10   , 4  , 1 ,   0  , 5   },
  { "lbl_HFp_leading_tower_all"       , "HF+ leading energy (GeV)", true , kEntries ,   10   , 5  , 1 ,   0  , 10  },
  { "lbl_HFm_leading_tower_all"       , "HF- leading energy (GeV)", true , kEntries ,   10   , 6  , 1 ,   0  , 10  },
  
  { "lbl_n_pixel_tracks_all"          , "LbL N_{tracks}^{pixel}"  , false, kEntries ,   11   , 1  , 1 ,   0  , 20  },
  { "lbl_n_zdc_all"                   , "LbL N_{ZDC}"             , false, kEntries ,   11   , 2  , 1 ,   0  , 20  },
  { "lbl_zdc_energy_all"              , "LbL E_{ZDC} (A.U.)"      , true , kEntries ,   11   , 3  , 1 ,   0  ,50000},
  { "lbl_zdc_sum_energy_all"          , "LbL #sum E_{ZDC} (A.U.)" , true , kEntries ,   11   , 4  , 50,   0 ,100000},
  { "lbl_zdc_sum_energy_pos_all"      , "LbL #sum E_{ZDC}^{+} (A.U.)",true,kEntries ,   11   , 5  , 50,   0 ,100000},
  { "lbl_zdc_sum_energy_neg_all"      , "LbL #sum E_{ZDC}^{-} (A.U.)",true,kEntries ,   11   , 6  , 50,   0 ,100000},
  { "zdc_sum_energy_pos_all"          , "#sum E_{ZDC}^{+} (A.U.)" , true , kEntries ,   11   , 7  , 1 ,   0 ,100000},
  { "zdc_sum_energy_neg_all"          , "#sum E_{ZDC}^{-} (A.U.)" , true , kEntries ,   11   , 8  , 1 ,   0 ,100000},
  
  
  // Here nice plots for AN. Don't apply scaling again: kNoScaling
  { "lbl_photon_et_all"               , "photon E_{t} (GeV)"      , false, kNoScaling    ,   12  , 1  , 1 ,   0  , 30  },
  { "lbl_diphoton_mass_all"           , "diphoton m_{inv} (GeV)"  , false, kNoScaling    ,   12  , 2  , 1 ,   0  , 50  },
  { "lbl_photon_eta_all"              , "photon #eta"             , false, kNoScaling    ,   12  , 3  , 1 , -3.0 , 3.0 },
  { "lbl_diphoton_rapidity_all"       , "diphoton rapidity"       , false, kNoScaling    ,   12  , 4  , 1 , -3.0 , 3.0 },
  { "lbl_photon_phi_all"              , "photon #phi"             , false, kNoScaling    ,   12  , 5  , 1 , -3.5 , 3.5 },
  { "lbl_diphoton_pt_all"             , "diphoton p_{t}"          , false, kNoScaling    ,   12  , 6  , 1 ,   0  , 2.0 },
  
  { "lbl_acoplanarity_all"            , "A_{#phi}^{#gamma#gamma}" , false, kNoScaling    ,   13  , 1  , 1 ,   0  , 0.2 },
  
  
  { "qed_electron_pt_all"             , "electron p_{t} (GeV)"    , false, kNoScaling    ,   14  , 1  , 1 ,   0  , 40  },
  { "qed_dielectron_mass_all"         , "dielectron m_{inv} (GeV)", false, kNoScaling    ,   14  , 2  , 1 ,   0  , 100 },
  { "qed_electron_eta_all"            , "electron #eta"           , false, kNoScaling    ,   14  , 3  , 1 , -2.5 , 2.5 },
  { "qed_dielectron_rapidity_all"     , "dielectron rapidity"     , false, kNoScaling    ,   14  , 4  , 1 ,  -3.0, 3.0 },
  { "qed_electron_phi_all"            , "electron #phi"           , false, kNoScaling    ,   14  , 5  , 1 , -3.5 , 3.5 },
  { "qed_dielectron_pt_all"           , "dielectron p_{t}"        , false, kNoScaling    ,   14  , 6  , 1 ,   0  , 2.0 },
  
  { "qed_acoplanarity_all"            , "A_{#phi}^{e^{+}e^{-}}"   , true , kNoScaling    ,   15  , 1  , 1 ,   0  , 0.1 },
};

void fillLabels(TH1D *hist, vector<const char*> labels)
{
  int i=1;
  for(auto label : labels){
    hist->GetXaxis()->SetBinLabel(i, label);
    hist->GetXaxis()->ChangeLabel(i, 45);
    i++;
  }
  hist->LabelsOption("u", "X");
}

vector<const char *> labelsLbL = {
  "Initial", "Trigger", "CHE", "CHE_{pix}", "N_{hits}^{pixel}", "ZDC", "NEE", "2 good photons",
  "diphoton m_{inv}", "diphoton p_{t}", "diphoton y", "acoplanarity"
};

// inverted cuts order:
//vector<const char *> labelsLbL = {
//  "Initial", "Trigger", "2 good photons",
//  "diphoton m_{inv}", "CHE", "CHE_{pix}", "N_{hits}^{pixel}", "ZDC", "NEE", "diphoton p_{t}", "diphoton y", "acoplanarity"
//};

vector<const char *> labelsQED = {
  "Initial", "Trigger", "NEE", "CHE", "2 good electrons", "opposite q",
  "dielectron m_{inv}", "dielectron p_{t}", "dielectron y"
};

void setCutflowLabels(TH1D *hist, bool lbl)
{
  fillLabels(hist, lbl ? labelsLbL : labelsQED);
}

void setCaloLabels(TH1D *hist)
{
  vector<const char *> labels = { "EB", "EE", "HB", "HE", "HF+", "HF-" };
  fillLabels(hist, labels);
}

void setElectronCutsLabels(TH1D *hist)
{
  vector<const char *> labels = {
    "Initial", "p_{t}", "Cracks", "#eta", "HEM", "missing hits",
    "H/E", "#Delta#eta seed", "Iso charge", "Iso photon", "Iso neutral"
  };
  fillLabels(hist, labels);
}

void setTrackCutsLabels(TH1D *hist)
{
  vector<const char *> labels = {
    "Initial", "p_{t}", "Eta", "d_{xy}", "|d_{xy}/#sigma_{xy}|",
    "d_{z}", "|d_{z}/#sigma_{z}|", "N_{hits}^{valid}", "#chi^{2}" };
  fillLabels(hist, labels);
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
    if(!hists[dataset]) continue;
    
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
  double maxValue = -999999999;
  
  for(EDataset dataset : datasetsToAnalyze){
    if(!hists[dataset]) continue;
    
    for(int i=0; i<hists[dataset]->GetNbinsX(); i++){
      double value = hists[dataset]->GetBinContent(i);
      if(value > maxValue) maxValue = value;
    }
  }
  return maxValue;
}

double getMinValueInHists(map<EDataset, TH1D*> hists, bool logY)
{
  double minValue = 999999999;
  
  for(EDataset dataset : datasetsToAnalyze){
    if(!hists[dataset]) continue;
    
    for(int i=0; i<hists[dataset]->GetNbinsX(); i++){
      double value = hists[dataset]->GetBinContent(i);
      if(value < minValue){
        if(value > 0 || !logY) minValue = value;
      }
    }
  }
  return minValue;
}

void normalizeHists(map<EDataset, TH1D*> hists, ENorm normStrategy)
{
  for(EDataset dataset : datasetsToAnalyze){
    if(!hists[dataset]) continue;
    if(hists[dataset]->GetEntries() == 0) continue;
    
    if(normStrategy == kEntries){
      hists[dataset]->Scale(1./hists[dataset]->GetEntries());
    }
    else if(normStrategy == kFirstBin){
      if(dataset == kData) continue;
      hists[dataset]->Scale(1./hists[dataset]->GetBinContent(1)*hists[kData]->GetBinContent(1));
    }
    else if(normStrategy == kXsec){
      if(dataset == kData) continue;
      hists[dataset]->Scale(luminosity*crossSection[dataset]/initialNevents[dataset]);
      hists[dataset]->Sumw2(false);
    }
    else if(normStrategy == kNoScaling){
      if(dataset == kData) continue;
      hists[dataset]->Sumw2(false);
    }
  }
}

TF1* fitHistogram(TH1D* hist, bool dz)
{
  TF1 *fitFun = new TF1("fitFun",
                        "[0]/([1]*sqrt(2*TMath::Pi()))*exp(-1./2*pow((x-[2])/[1],2))+ [3]/([4]*sqrt(2*TMath::Pi()))*exp(-1./2*pow((x-[5])/[4],2))",-100, 100);
  
  fitFun->SetParameter(0, 1); // scale 1
  fitFun->SetParameter(1, dz ? 10 : 1); // sigma 1
  fitFun->SetParameter(2, 0); // mu 1
  
  fitFun->SetParameter(3, 1); // scale 2
  fitFun->SetParameter(4, dz ? 100 : 0.1); // sigma 2
  fitFun->SetParameter(5, dz ? 0 : 0.1); // mu 2
  
  hist->Fit(fitFun, "0");
  
  return fitFun;
}

void drawBasicPlots()
{
  gStyle->SetOptStat(0);
  
  TFile *inFile = TFile::Open(inputPath.c_str());
  
  vector<TCanvas*> canvas;
  
  for(auto &[title, nCol, nRow] : canvasParams){
    canvas.push_back(new TCanvas(title.c_str(), title.c_str(), baseHistWidth*nCol, baseHistHeight*nRow));
    canvas.back()->Divide(nCol, nRow);
  }
  
  for(auto &[histName, xAxisTitle, logY, normStrategy, iCanvas, iPad, rebin, xMin, xMax] : histParams){
    
    map<EDataset, TH1D*> hists = getHistsFromFile(inFile, histName);
    
    THStack *backgroundsStack = new THStack();
    TH1D *dataHist;
    
    for(EDataset dataset : datasetsToAnalyze){
      if(!hists[dataset]) continue;
      if(hists[dataset]->GetEntries() == 0) continue;
      
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

    normalizeHists(hists, normStrategy);
    
    if(histName == "lbl_acoplanarity_all"){
      double signal = dataHist->GetBinContent(1);
      double background = 0;
      for(int i=2; i<=dataHist->GetNbinsX(); i++){
        background += dataHist->GetBinContent(i);
      }
      background /= 25;
      cout<<"Significance: "<<(signal-background)/sqrt(signal)<<endl;
    }
    
    if(histName == "lbl_cut_flow_all"){
      for(EDataset dataset : datasetsToAnalyze){
        if(!hists[dataset]) continue;
        
        cout<<"\n----------------------------"<<endl;
        cout<<"Dataset: "<<datasetName.at(dataset)<<endl;
        
        for(int i=0; i<labelsLbL.size(); i++){
          cout<<labelsLbL[i]<<": "<<to_string_with_precision(hists[dataset]->GetBinContent(i+1), 2);
          cout<<"\t+/- "<<to_string_with_precision(hists[dataset]->GetBinError(i+1), 2)<<endl;
        }
      }
    }
    
    dataHist->SetTitle("");
    
    dataHist->GetXaxis()->SetRangeUser(xMin, xMax);
    dataHist->GetXaxis()->SetTitle("");
    dataHist->GetXaxis()->SetTitleSize(0.06);
    dataHist->GetXaxis()->SetLabelSize(0);
    
    dataHist->GetYaxis()->SetTitle("# events");
    dataHist->GetYaxis()->SetTitleSize(0.06);
    dataHist->GetYaxis()->SetTitleOffset(1.15);
    dataHist->GetYaxis()->SetLabelSize(0.06);
    
    if(logY){
      double min = getMinValueInHists(hists, logY);
      dataHist->SetMaximum(5 * getMaxValueInHists(hists));
      if(min > 0) dataHist->SetMinimum(0.2 * min);
      else{
        cout<<"ERROR -- Log scale required for plot "<<histName<<" containing negative values!!!"<<endl;
      }
    }
    else{
      dataHist->SetMaximum(1.5 * getMaxValueInHists(hists));
      dataHist->SetMinimum(0.7 * getMinValueInHists(hists, logY));
    }
    
    if(normStrategy == kFirstBin){
      dataHist->Draw("PE");
      backgroundsStack->Draw("sameNostack");
    }
    else if(normStrategy == kEntries){
      dataHist->Draw("PE");
      backgroundsStack->Draw("sameNostack");
    }
    else if(normStrategy == kXsec || normStrategy == kNoScaling){
      dataHist->Draw("PE");
      backgroundsStack->Draw("same");
      dataHist->Draw("PEsame");
    }
    
    
    
    if(histName.find("track_dz_all") != string::npos){
      for(auto dataset : datasetsToAnalyze){
        TF1 *fun = fitHistogram(hists.at(dataset), true);
        fun->SetLineColor(datasetColor.at(dataset));
        fun->Draw("same");
        cout<<"Tracks d_z mean for "<<datasetName.at(dataset)<<": ";
        cout<<fun->GetParameter(2)<<" +/- "<<fun->GetParError(2)<<endl;
      }
    }
//    if(histName.find("track_dxy_all") != string::npos){
//      for(auto dataset : datasetsToAnalyze){
//        TF1 *fun = fitHistogram(hists.at(dataset), false);
//        fun->SetLineColor(datasetColor.at(dataset));
//        fun->Draw("same");
//        cout<<"Tracks d_xy mean for "<<datasetName.at(dataset)<<": ";
//        cout<<fun->GetParameter(2)<<" +/- "<<fun->GetParError(2)<<endl;
//      }
//    }
    
    
    
    if(drawLegends) getLegendForHists(hists)->Draw();
    
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
    TH1D *backgroundsSum = nullptr;
    bool first = true;
    
    for(auto &[dataset, hist] : hists){
      if(dataset == kData) continue;
      if(!hists[dataset]) continue;
      
      if(first){
        backgroundsSum = new TH1D(*hist);
        first = false;
      }
      else{
        backgroundsSum->Add(hist);
      }
    }
    
    if(backgroundsSum) ratio->Divide(backgroundsSum);
    
    ratio->Draw();
    
    ratio->SetMaximum(1.2 * getMaxHistValue(ratio));
    ratio->SetMinimum(0.8 * getMinHistValue(ratio));
    
    ratio->SetTitle("");
    
    if(histName == "qed_cut_flow_all")          setCutflowLabels(ratio, false);
    if(histName == "lbl_cut_flow_all")          setCutflowLabels(ratio, true);
    if(histName == "qed_electron_cutflow_all")  setElectronCutsLabels(ratio);
    if(histName == "tracks_cut_flow_all")       setTrackCutsLabels(ratio);
    if(histName == "lbl_nee_failing_all")       setCaloLabels(ratio);
    
    
    ratio->GetXaxis()->SetTitle(xAxisTitle.c_str());
    ratio->GetXaxis()->SetTitleSize(0.2);
    ratio->GetXaxis()->SetTitleOffset(1.1);
    ratio->GetXaxis()->SetLabelSize(0.2);
    ratio->GetXaxis()->SetRangeUser(xMin, xMax);
    
    if(histName.find("cut_flow") != string::npos || histName.find("nee_failing") != string::npos){
      ratio->GetXaxis()->SetLabelSize(0.16);
      ratio->GetXaxis()->SetLabelOffset(0.055);
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
  
  canvas[12]->SaveAs((outputPath+"_photons.pdf").c_str());
  canvas[13]->SaveAs((outputPath+"_acoplanarity_lbl.pdf").c_str());
  canvas[14]->SaveAs((outputPath+"_electrons.pdf").c_str());
  canvas[15]->SaveAs((outputPath+"_acoplanarity_qed.pdf").c_str());
}
