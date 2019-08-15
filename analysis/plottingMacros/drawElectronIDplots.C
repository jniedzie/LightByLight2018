#include "../include/Helpers.hpp"

string inputPath  = "../results/electronID_test.root";
string outputPath = "../plots/electronID.pdf";

vector<EDataset> datasetsToSkip = { kMCcep, kMClbl };

vector<tuple<string, string, double, string, bool>> histParams = {
// name                 title                                  threshold thresholdLabel logY
  {"HoverE_Barrel"            , "H/E (barrel)"                , 0.02    , "0.02"    , true  },
  {"HoverE_Endcap"            , "H/E (endcap)"                , 0.02    , "0.02"    , true  },
  
  {"chargedIsoBarrel"         ,  "Charged isolation (barrel)" , 9999    , ""        , true  },
  {"chargedIsoEndcap"         ,  "Charged isolation (endcap)" , 9999    , ""        , true  },
  {"photonIsoBarrel"          ,  "Photon isolation (barrel)"  , 9999    , ""        , true  },
  {"photonIsoEndcap"          ,  "Photon isolation (endcap)"  , 9999    , ""        , true  },
  {"neutralIsoBarrel"         ,  "Neutral isolation (barrel)" , 9999    , ""        , true  },
  {"neutralIsoEndcap"         ,  "Neutral isolation (endcap)" , 9999    , ""        , true  },
  
  {"relIsoWithEA_Barrel"      ,  "RelIso (barrel)"            , 9999    , ""        , true  },
  {"relIsoWithEA_Endcap"      ,  "RelIso (endcap)"            , 9999    , ""        , true  },
  
  {"dEtaSeedBarrel"           , "#Delta#eta seed (barrel)"    , 0.00377 , "0.00377" , true  },
  {"dEtaSeedEndcap"           , "#Delta#eta seed (endcap)"    , 0.00674 , "0.00674" , true  },
//  {"nMissingHits"             , "N missing hits"              , 1       , "1"       , false },
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
  
  TCanvas *canvas         = new TCanvas("Electon ID", "Electon ID", 2880, 1800);
  TCanvas *canvasWithCuts = new TCanvas("Electon ID (after cuts) ", "Electon ID (after cuts)", 2880, 1800);
  canvas->Divide(4,3);
  canvasWithCuts->Divide(4,3);

  TLegend *legend = new TLegend(0.5, 0.7, 0.9, 0.9 );
  
  bool first = true;
  for(EDataset dataset : datasets){
    if(find(datasetsToSkip.begin(), datasetsToSkip.end(), dataset) != datasetsToSkip.end()) continue;
    
    string dataName = datasetName.at(dataset);
    int color = datasetColor.at(dataset);
    
    map<string, TH1D*> hists;
    
    int iPad=1;
    for(auto &[histName, histTitle, threshold, thresholdLabel, logY] : histParams){
      hists[histName] = (TH1D*)inFile->Get((histName+dataName).c_str());
      hists[histName+"_withCuts"] = (TH1D*)inFile->Get((histName+dataName+"_withCuts").c_str());
      if(!hists[histName] || !hists[histName+"_withCuts"]){
        cout<<"Could not open hist: "<<histName<<dataName<<endl;
        continue;
      }
      if(hists[histName]->GetEntries()==0 || hists[histName+"_withCuts"]->GetEntries()==0){
        cout<<"No entries in hist "<<histName<<dataName<<endl;
        continue;
      }
      
      canvas->cd(iPad); preparePad();
      gPad->SetLogy(logY);
      prepareHist(hists[histName], color);
      hists[histName]->SetTitle(histTitle.c_str());
      hists[histName]->Draw(first ? "" : "same");
      if(first) drawThreshold(threshold, thresholdLabel, logY ? 3e-2 : 0.5);
      
      canvasWithCuts->cd(iPad); preparePad();
      gPad->SetLogy(logY);
      prepareHist(hists[histName+"_withCuts"], color);
      hists[histName+"_withCuts"]->SetTitle(histTitle.c_str());
      hists[histName+"_withCuts"]->Draw(first ? "" : "same");
      if(first) drawThreshold(threshold, thresholdLabel, logY ? 3e-2 : 0.5);
      
      iPad++;
    }
    
    legend->AddEntry(hists.begin()->second, datasetDescription.at(dataset).c_str(), "l");
    
    first = false;
  }
  
  for(int iPad=1; iPad<=histParams.size(); iPad++){
    canvas->cd(iPad); legend->Draw("same");
    canvasWithCuts->cd(iPad); legend->Draw("same");
  }
  
  canvas->SaveAs((outputPath+".pdf").c_str());
  canvasWithCuts->SaveAs((outputPath+"_withCuts.pdf").c_str());
}
