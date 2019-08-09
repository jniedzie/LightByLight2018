#include "../include/Helpers.hpp"

string inputPath  = "../results/electronID_test.root";
string outputPath = "../plots/electronID.pdf";

vector<tuple<string, string, double, string, bool>> histParams = {
// name                 title                         threshold thresholdLabel logY
  {"nMissingHits"       , "N missing hits"            , 1       , "1"       , false },
  {"HoverEbarrel"       , "H/E (barrel)"              , 0.02    , "0.02"    , true  },
  {"HoverEendcap"       , "H/E (endcap)"              , 0.02    , "0.02"    , true  },
  {"relIsoWithEAbarrel" ,  "RelIso (barrel)"          , 9999    , ""        , true  },
  {"relIsoWithEAendcap" ,  "RelIso (endcap)"          , 9999    , ""        , true  },
  {"dEtaSeedbarrel"     , "#Delta#eta seed (barrel)"  , 0.00377 , "0.00377" , true  },
  {"dEtaSeedendcap"     , "#Delta#eta seed (endcap)"  , 0.00674 , "0.00674" , true  },
};

void prepareHist(TH1D *hist, int color)
{
  hist->SetLineColor(color);
  hist->SetTitle("");
  hist->GetYaxis()->SetTitleSize(0.06);
  hist->GetXaxis()->SetTitleSize(0.06);
  hist->Scale(1./hist->GetEntries());
  hist->GetYaxis()->SetRangeUser(1e-4, 1.0);
  hist->Sumw2(false);
}

void prepareHist(TH2D *hist, int color)
{
  hist->SetTitle("");
  hist->GetYaxis()->SetTitleSize(0.06);
  hist->GetXaxis()->SetTitleSize(0.06);
}

void preparePad()
{
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);
}

void drawThreshold(double threshold, string label="", double yPosition = 3e-2)
{
  TLine *line = new TLine(threshold, 0, threshold, 1.0);
  line->SetLineColor(kGreen+2);
  line->SetLineWidth(2);
  line->Draw("same");
  TLatex *text = new TLatex(threshold+0.005, yPosition, label=="" ? Form("%.2f", threshold) : label.c_str());
  text->SetTextColor(kGreen+2);
  text->SetTextSize(0.05);
  text->Draw("same");
}

void drawElectronIDplots()
{
  TFile *inFile = TFile::Open(inputPath.c_str());
  gStyle->SetOptStat(0);
  
  TCanvas *canvas = new TCanvas("Shower shape", "Shower shape", 1000, 2000);
  canvas->Divide(2,4);

  TLegend *legend = new TLegend(0.5, 0.7, 0.9, 0.9 );
  
  bool first = true;
  for(EDataset dataset : datasets){
    string dataName = datasetName.at(dataset);
    int color = datasetColor.at(dataset);
    
    map<string, TH1D*> hists;
    
    int iPad=1;
    for(auto &[histName, histTitle, threshold, thresholdLabel, logY] : histParams){
      hists[histName] = (TH1D*)inFile->Get((histName+dataName).c_str());
      if(!hists[histName]) cout<<"Could not open hist: "<<histName<<dataName<<endl;
      
      prepareHist(hists[histName], color);
      
      canvas->cd(iPad++); preparePad();
      gPad->SetLogy(logY);
      hists[histName]->SetTitle(histTitle.c_str());
      hists[histName]->Draw(first ? "" : "same");
      if(first) drawThreshold(threshold, thresholdLabel, logY ? 3e-2 : 0.5);
    }
    
    legend->AddEntry(hists.begin()->second, datasetDescription.at(dataset).c_str(), "l");
    
    first = false;
  }
  
  for(int iPad=1; iPad<=histParams.size(); iPad++){
    canvas->cd(iPad); legend->Draw("same");
  }
  
  canvas->SaveAs(outputPath.c_str());
}
