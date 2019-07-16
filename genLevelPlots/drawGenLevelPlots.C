int canvasWidth = 1000;
int canvasHeight = 1800;

vector<tuple<string, int>> datasetParams = {
  {"raw_plots_cep_sc.root", kRed    },
  {"raw_plots_qed_sc.root", kBlue   },
  {"raw_plots_lbl_sc.root", kBlack  },
  {"raw_plots_qed_sl.root", kGreen  },
};

vector<tuple<string, string, string, bool>> pairHistNames = {
  {"pair_m"     , "m (GeV/c)"     , "Entries", true },
  {"pair_pt"    , "p_{T} (GeV/c)" , "Entries", false},
  {"pair_pz"    , "p_{z} (GeV/c)" , "Entries", true },
  {"pair_y"     , "y"             , "Entries", false},
  {"pair_theta" , "#theta"        , "Entries", true },
  {"pair_aco"   , "A_{#phi}"      , "Entries", false},
};
vector<tuple<string, string, string, bool>> singleHistNames = {
  {"single_pt"  , "p_{T} (GeV/c)" , "Entries", true },
  {"single_pz"  , "p_{z} (GeV/c)" , "Entries", true },
  {"single_y"   , "y"             , "Entries", false},
  {"single_eta" , "#eta"          , "Entries", false},
  {"single_phi" , "#phi"          , "Entries", false},
};


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
    for(auto &[histName, xTitle, yTitle, logY] : pairHistNames){
      canvasPair->cd(iPad++);
      TH1D *hist = (TH1D*)inFile->Get(histName.c_str());
      hist->SetLineColor(color);
      hist->GetXaxis()->SetTitle(xTitle.c_str());
      hist->GetYaxis()->SetTitle(yTitle.c_str());
      if(logY) gPad->SetLogy();
      hist->DrawNormalized(firstFile ? "" : "same");
    }
    
    iPad=1;
    for(auto &[histName, xTitle, yTitle, logY] : singleHistNames){
      canvasSingle->cd(iPad++);
      TH1D *hist = (TH1D*)inFile->Get(histName.c_str());
      hist->SetLineColor(color);
      hist->GetXaxis()->SetTitle(xTitle.c_str());
      hist->GetYaxis()->SetTitle(yTitle.c_str());
      if(logY) gPad->SetLogy();
      hist->DrawNormalized(firstFile ? "" : "same");
    }
    
    firstFile=false;
  }

}
