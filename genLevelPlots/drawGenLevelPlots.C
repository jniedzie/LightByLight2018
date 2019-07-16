int canvasWidth = 1000;
int canvasHeight = 1800;

vector<tuple<string, int>> datasetParams = {
  {"raw_plots_cep_sc.root", kRed    },
  {"raw_plots_qed_sc.root", kBlue   },
  {"raw_plots_lbl_sc.root", kBlack  },
  {"raw_plots_qed_sl.root", kGreen  },
};
//            name    x label y label logY  xMin    xMax    yMax
typedef tuple<string, string, string, bool, double, double, double> histParams;

vector<histParams> pairHistParams = {
// name          x label           y label    logY     xMin    xMax    yMax
  {"pair_m"     , "m (GeV/c)"     , "Entries", true   , 0.0   ,  90.  , 1.0   },
  {"pair_pt"    , "p_{T} (GeV/c)" , "Entries", false  , 0.0   , 0.4   , 0.2   },
  {"pair_pz"    , "p_{z} (GeV/c)" , "Entries", true   , 0.0   , 1000  , 1.0   },
  {"pair_y"     , "y"             , "Entries", false  , -10.0 , 10.0  , 0.05  },
//  {"pair_theta" , "#theta"        , "Entries", true   ,},
  {"pair_aco"   , "A_{#phi}"      , "Entries", false  , 0.0   , 0.5   , 0.25  },
};

vector<histParams> singleHistParams = {
// name          x label           y label    logY     xMin    xMax    yMax
  {"single_pt"  , "p_{T} (GeV/c)" , "Entries", true   , 0.0   , 50    , 0.11  },
  {"single_pz"  , "p_{z} (GeV/c)" , "Entries", true   , 0.0   , 1000  , 1.0   },
  {"single_y"   , "y"             , "Entries", false  , -10.0 , 10.0  , 0.025 },
  {"single_eta" , "#eta"          , "Entries", false  , -10.0 , 10.0  , 0.04  },
  {"single_phi" , "#phi"          , "Entries", false  , -4.0  , -4.0  , 0.015 },
};

void DrawPlot(TFile *inFile, histParams params, int color, bool firstFile)
{
  auto &[histName, xTitle, yTitle, logY, xMin, xMax, yMax] = params;
  
  TH1D *hist = (TH1D*)inFile->Get(histName.c_str());
  hist->SetLineColor(color);
  hist->GetXaxis()->SetTitle(xTitle.c_str());
  hist->GetYaxis()->SetTitle(yTitle.c_str());
  hist->GetXaxis()->SetRangeUser(xMin, xMax);
  if(logY) gPad->SetLogy();
  hist->Scale(1./hist->GetEntries());
  hist->SetMaximum(yMax);
  hist->Sumw2(false);
  hist->Draw(firstFile ? "" : "same");
}

void drawGenLevelPlots()
{
  TCanvas *canvasPair = new TCanvas("Gen-level pair plots", "Gen-level pair plots", canvasWidth, canvasHeight);
  canvasPair->Divide(2,3);
  
  TCanvas *canvasSingle = new TCanvas("Gen-level single plots", "Gen-level single plots", canvasWidth, canvasHeight);
  canvasSingle->Divide(2,3);
  
  bool firstFile=true;
  for(auto &[fileName, color] : datasetParams){
    TFile *inFile = TFile::Open(fileName.c_str());
    
    int iPad=1;
    for(auto &params : pairHistParams){
      canvasPair->cd(iPad++);
      DrawPlot(inFile, params, color, firstFile);
    }
    
    iPad=1;
    for(auto &params : singleHistParams){
      canvasSingle->cd(iPad++);
      DrawPlot(inFile, params, color, firstFile);
    }
    
    firstFile=false;
  }

}
