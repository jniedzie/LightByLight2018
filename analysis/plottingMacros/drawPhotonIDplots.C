#include "../include/Helpers.hpp"

string inputPath        = "../results/photonIDplots.root";
string outputPathShower = "../plots/photonShowerShape.pdf";
string outputPathHoverE = "../plots/photonHoverE.pdf";

vector<TCanvas*> canvas;

vector<tuple<string, int, int, int, int>> canvasParams = {
// title           width  height nCol nRow
  {"Shower shape" , 1000, 1000  , 2 , 2 },
  {"H/E"          , 1000, 1000  , 2 , 2 },
};

vector<tuple<string, string, string, int, int, int, double, double, double, double, double>> histParams = {
  // name                  title                   xTitle          rebin  iCanvas iPad  cut     xMin xMax   yMin   yMax
  {"showerShapeBarrel"    , "Shower shape barrel" , "#eta width"  , 1    , 0    , 1   , 0.0106 , 0 , 1     , 1E-4 , 1 },
  {"showerShapeEndcap"    , "Shower shape endcap" , "#eta width"  , 1    , 0    , 2   , 0.0272 , 0 , 1     , 1E-4 , 1 },
  {"swissCrossBarrel"     , "Swiss cross barrel"  , "E4/E"        , 1    , 0    , 3   , 0.005  , 0 , 0.05  , 1E-5 , 1 },
  {"swissCrossEndcap"     , "Swiss cross endcap"  , "E4/E"        , 1    , 0    , 4   , 0.005  , 0 , 0.05  , 1E-5 , 1 },
  
  {"HoverEbarrel"         , "H/E barrel"          , "H/E"         , 5    , 1    , 1   , 0.04596, 0 , 1     , 1E-4 , 1 },
  {"HoverEendcap"         , "H/E endcap"          , "H/E"         , 5    , 1    , 2   , 0.0590 , 0 , 1     , 1E-4 , 1 },
};

vector<EDataset> datasetsToAnalyze = {
  kData,
  kMCqedSC,
  kMClbl,
  kMCcep
};

void prepareHist(TH1D *hist, int color, int rebin)
{
  hist->SetLineColor(color);
  hist->SetTitle("");
  hist->GetYaxis()->SetTitle("# events");
  hist->GetYaxis()->SetTitleSize(0.06);
  hist->GetXaxis()->SetTitle("#sigma_{i#etai#eta}");
  hist->GetXaxis()->SetTitleSize(0.06);
  hist->Scale(1./hist->GetEntries());
  hist->GetYaxis()->SetRangeUser(1e-4, 1.0);
  
  hist->Rebin(rebin);
  hist->Scale(1./rebin);
  
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
  gPad->SetLogy();
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);
}

void drawThreshold(double threshold, string label="")
{
  TLine *line = new TLine(threshold, 0, threshold, 1.0);
  line->SetLineColor(kGreen+2);
  line->SetLineWidth(2);
  line->Draw("same");
  TLatex *text = new TLatex(threshold+0.005, 3e-2, label=="" ? Form("%.2f", threshold) : label.c_str());
  text->SetTextColor(kGreen+2);
  text->SetTextSize(0.05);
  text->Draw("same");
}

void drawPhotonIDplots()
{
  TFile *inFile = TFile::Open(inputPath.c_str());
  TLegend *legend = new TLegend(0.5, 0.7, 0.9, 0.9 );
  gStyle->SetOptStat(0);
  
  
  // Prepare canvases
  for(auto &[title, width, height, nCol, nRow] : canvasParams){
    canvas.push_back(new TCanvas(title.c_str(), title.c_str(), width, height));
    canvas.back()->Divide(nCol, nRow);
  }
  
  // Plot 1D plots
  bool firstDataset = true;
  bool firstHist = true;
  
  for(EDataset dataset : datasetsToAnalyze){
    firstHist = true;
    
    for(auto &[name, title, xTitle, rebin, iCanvas, iPad, threshold, xMin, xMax, yMin, yMax] : histParams){
      
      TH1D *hist = (TH1D*)inFile->Get((name+datasetName.at(dataset)).c_str());
      if(!hist) cout<<"Could not open "<<name<<" hist"<<endl;
      
      int color = datasetColor.at(dataset);
      prepareHist(hist, color, rebin);
      
      canvas[iCanvas]->cd(iPad);
      preparePad();
      hist->SetTitle(title.c_str());
      hist->GetXaxis()->SetTitle(xTitle.c_str());
      hist->Draw(firstDataset ? "" : "same");
      hist->GetXaxis()->SetRangeUser(xMin, xMax);
      hist->GetYaxis()->SetRangeUser(yMin, yMax);
      if(firstDataset) drawThreshold(threshold, to_string(threshold));
      
      if(firstHist) legend->AddEntry(hist, datasetDescription.at(dataset).c_str(), "l");
      
      firstHist = false;
    }
    
    
    firstDataset = false;
  }
  
  // Draw 2D H/E map
  canvas[1]->cd(3); preparePad();
  gPad->SetLogy(false);
  gPad->SetRightMargin(0.15);
  
  TH2D *num = (TH2D*)inFile->Get("HoverEmapNumData");
  TH2D *den = (TH2D*)inFile->Get("HoverEmapDenData");
  
  num->Rebin2D(2, 2);
  den->Rebin2D(2, 2);
  num->Divide(den);
  
  num->SetTitle("Average H/E map");
  num->GetXaxis()->SetTitle("#phi");
  num->GetYaxis()->SetTitle("#eta");
  num->GetZaxis()->SetTitle("< H/E >");
  num->GetZaxis()->SetTitleOffset(1.5);
  num->GetZaxis()->SetRangeUser(0, 0.5);
  num->Draw("colz");
       
  // Add legends
  canvas[0]->cd(1); legend->Draw("same");
  canvas[0]->cd(2); legend->Draw("same");
  canvas[0]->cd(4); legend->Draw("same");
  canvas[1]->cd(1); legend->Draw("same");
  canvas[1]->cd(2); legend->Draw("same");
  
  // Save results
  canvas[0]->SaveAs(outputPathShower.c_str());
  canvas[1]->SaveAs(outputPathHoverE.c_str());
}
