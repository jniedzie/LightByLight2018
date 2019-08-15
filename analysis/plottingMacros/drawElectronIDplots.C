#include "../include/Helpers.hpp"

string inputPath  = "../results/electronID.root";
string outputPath = "../plots/electronID";

vector<EDataset> datasetsToSkip = { kMCcep, kMClbl };

vector<tuple<string, string, double, string, bool, bool, double>> histParams = {
// name                 title                                  threshold tsldLabel logY withCuts maxX
  {"chargedIsoBarrel"         ,  "Charged isolation (barrel)" , 0.1    , "0.1"    , true  , true  , 2.0  },
  {"chargedIsoEndcap"         ,  "Charged isolation (endcap)" , 0.1    , "0.1"    , true  , true  , 2.0  },
  {"photonIsoBarrel"          ,  "Photon isolation (barrel)"  , 0.035  , "0.035"  , true  , true  , 1.0  },
  {"photonIsoEndcap"          ,  "Photon isolation (endcap)"  , 0.035  , "0.035"  , true  , true  , 1.0  },
  {"neutralIsoBarrel"         ,  "Neutral isolation (barrel)" , 0.07   , "0.07"   , true  , true  , 2.0  },
  {"neutralIsoEndcap"         ,  "Neutral isolation (endcap)" , 0.07   , "0.07"   , true  , true  , 2.0  },
  
  {"HoverE_Barrel"            , "H/E (barrel)"                , 0.005  , "0.005"  , true  , true  , 0.1  },
  {"HoverE_Endcap"            , "H/E (endcap)"                , 0.005  , "0.005"  , true  , true  , 0.1  },
  
//  {"relIsoWithEA_Barrel"      ,  "RelIso (barrel)"            , 9999    , ""        , true  , true  , 10.0  },
//  {"relIsoWithEA_Endcap"      ,  "RelIso (endcap)"            , 9999    , ""        , true  , true  , 10.0  },
  
  {"dEtaSeedBarrel"           , "#Delta#eta seed (barrel)"    , 0.1    , "0.1"    , true  , true  , 0.12 },
  {"dEtaSeedEndcap"           , "#Delta#eta seed (endcap)"    , 0.1    , "0.1"    , true  , true  , 0.12 },
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
  
  TCanvas *canvas         = new TCanvas("Electon ID", "Electon ID", 1000, 1000);
  TCanvas *canvasIso = new TCanvas("Electon ID isolation ", "Electon ID isolation", 1000, 1500);
  canvas->Divide(2,2);
  canvasIso->Divide(2,3);

  TLegend *legend = new TLegend(0.5, 0.7, 0.9, 0.9 );
  
  bool first = true;
  for(EDataset dataset : datasets){
    if(find(datasetsToSkip.begin(), datasetsToSkip.end(), dataset) != datasetsToSkip.end()) continue;
    
    string dataName = datasetName.at(dataset);
    int color = datasetColor.at(dataset);
    
    map<string, TH1D*> hists;
    
    int iPad=1;
    for(auto &[histName, histTitle, threshold, thresholdLabel, logY, withCuts, maxX] : histParams){
      
      hists[histName] = (TH1D*)inFile->Get((histName+dataName+(withCuts ? "_withCuts" : "")).c_str());
      
      if(!hists[histName]){
        cout<<"Could not open hist: "<<histName<<dataName<<endl;
        continue;
      }
      if(hists[histName]->GetEntries()==0){
        cout<<"No entries in hist "<<histName<<dataName<<endl;
        continue;
      }
      
      if(iPad < 7) canvasIso->cd(iPad);
      else         canvas->cd(iPad-6);
      preparePad();
      gPad->SetLogy(logY);
      prepareHist(hists[histName], color);
      hists[histName]->SetTitle(histTitle.c_str());
      hists[histName]->GetXaxis()->SetRangeUser(0, maxX);
      hists[histName]->Draw(first ? "" : "same");
      if(first) drawThreshold(threshold, thresholdLabel, logY ? 3e-2 : 0.5);
      
      iPad++;
      
    }
    
    legend->AddEntry(hists.begin()->second, datasetDescription.at(dataset).c_str(), "l");
    
    first = false;
  }
  
  for(int iPad=1; iPad<=histParams.size(); iPad++){
    canvas->cd(iPad); legend->Draw("same");
    canvasIso->cd(iPad); legend->Draw("same");
  }
  
  canvas->SaveAs((outputPath+".pdf").c_str());
  canvasIso->SaveAs((outputPath+"_isolation.pdf").c_str());
}
