#include "../analysis/include/Helpers.hpp"

int canvasWidth = 1000;
int canvasHeight = 1800;

string basePath = "results/";

string inputPath = "raw_plots_alp_sc.root";
vector<tuple<int, int>> alpParams =
{
// mass color
  {5,    kGreen+3   },
  {6,    kGreen     },
  {9,    kCyan      },
  {11,   kBlue      },
  {14,   kViolet+2  },
  {16,   kMagenta   },
  {22,   kOrange    },
  {30,   kOrange+2  },
  {50,   kRed       },
  {90,   kRed+2     },
};

//            name    x label y label logX  logY  xMin    xMax    yMax   rebin
typedef tuple<string, string, string, bool, bool, double, double, double, int> histParams;

vector<histParams> pairHistParams = {
// name          x label           y label    logX    logY     xMin    xMax    yMax  rebin
  {"pair_m"     , "m (GeV/c)"     , "Entries", false, false  , 0.0   , 110.  , 1.0   , 1 },
  {"pair_pt"    , "p_{T} (GeV/c)" , "Entries", false, false  , 0.001 , 0.15  , 0.2   , 1 },
  {"pair_pz"    , "p_{z} (GeV/c)" , "Entries", false, true   , 0.0   , 1000  , 1.0   , 1 },
  {"pair_y"     , "y"             , "Entries", false, false  , -6.0  , 6.0   , 0.12  , 1 },
  {"pair_aco"   , "A_{#phi}"      , "Entries", false, true   , 1e-3  , 1.0   , 0.5   , 1 },
};

vector<histParams> singleHistParams = {
// name          x label           y label    logX    logY     xMin    xMax    yMax   rebin
  {"single_pt"  , "p_{T} (GeV/c)" , "Entries", false, false  , 0.1   , 50    , 0.5   , 5 },
  {"single_pz"  , "p_{z} (GeV/c)" , "Entries", false, true   , 0.0   , 1000  , 1.0   , 5 },
  {"single_y"   , "y"             , "Entries", false, false  , -6.0  , 6.0   , 0.08  , 1 },
  {"single_eta" , "#eta"          , "Entries", false, false  , -6.0  , 6.0   , 0.08  , 1 },
  {"single_phi" , "#phi"          , "Entries", false, false  , -4.0  , -4.0  , 0.02  , 1 },
};

TH1D* DrawPlot(TFile *inFile, histParams params, int color, int mass, bool firstFile)
{
  auto &[histName, xTitle, yTitle, logX, logY, xMin, xMax, yMax, rebin] = params;
  histName = histName+"_axion"+to_string(mass);
  
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

void drawGenLevelALPplots()
{
  TCanvas *canvasPair = new TCanvas("Gen-level pair plots", "Gen-level pair plots",
                                    canvasWidth, canvasHeight);
  canvasPair->Divide(2,3);
  
  TCanvas *canvasSingle = new TCanvas("Gen-level single plots", "Gen-level single plots",
                                      canvasWidth, canvasHeight);
  canvasSingle->Divide(2,3);
  
  TLegend *legend = new TLegend(0.2,0.2,0.8,0.8);
  
  gStyle->SetOptStat(0);
  
  string fileName = basePath+inputPath;
  TFile *inFile = TFile::Open(fileName.c_str());
  
  bool firstMass=true;
  
  for(auto &[mass, color] : alpParams){
    string sampleName = "axion "+to_string(mass)+" GeV";
    
    int iPad=1;
    bool firstHist=true;
    for(auto &params : pairHistParams){
      canvasPair->cd(iPad++);
      TH1D* hist = DrawPlot(inFile, params, color, mass, firstMass);
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
      DrawPlot(inFile, params, color, mass, firstMass);
    }
    canvasSingle->cd(iPad);
    legend->Draw();
    
    firstMass=false;
  }

  canvasSingle->SaveAs("plots/gen_level_alps_single.pdf");
  canvasPair->SaveAs("plots/gen_level_alps_pair.pdf");
  
}
