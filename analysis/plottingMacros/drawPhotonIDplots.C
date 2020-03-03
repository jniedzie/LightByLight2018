#include "../include/Helpers.hpp"

string inputPath  = "../results/photonID_test.root";
string outputPathShower = "../plots/photonShowerShape_test.pdf";
string outputPathHoverE = "../plots/photonHoverE_test.pdf";

vector<EDataset> datasetsToAnalyze = {
  kData,
  kMCqedSC,
  kMClbl,
  kMCcep
};

void prepareHist(TH1D *hist, int color)
{
  hist->SetLineColor(color);
  hist->SetTitle("");
  hist->GetYaxis()->SetTitle("# events");
  hist->GetYaxis()->SetTitleSize(0.06);
  hist->GetXaxis()->SetTitle("#sigma_{i#etai#eta}");
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
  
  TCanvas *canvasShower = new TCanvas("Shower shape", "Shower shape", 1000, 1000);
  TCanvas *canvasHoverE = new TCanvas("H/E", "H/E", 1000, 1000);
  canvasShower->Divide(2,2);
  canvasHoverE->Divide(2,2);
  
  gStyle->SetOptStat(0);
  TLegend *legend = new TLegend(0.5, 0.7, 0.9, 0.9 );
  
  
  bool first = true;
  for(EDataset dataset : datasetsToAnalyze){
    string name = datasetName.at(dataset);

    auto shapeBarrel     = (TH1D*)inFile->Get(("showerShapeBarrel"+name).c_str());
    if(!shapeBarrel) cout<<"Could not open showerShapeBarrel hist"<<endl;
    
    auto shapeEndcap     = (TH1D*)inFile->Get(("showerShapeEndcap"+name).c_str());
    if(!shapeEndcap) cout<<"Could not open shapeEndcap hist"<<endl;
    
    auto shapeEndcap2p3  = (TH1D*)inFile->Get(("showerShapeEndcap2p3"+name).c_str());
    if(!shapeEndcap2p3) cout<<"Could not open shapeEndcap2p3 hist"<<endl;
    
    auto etaEndcap       = (TH1D*)inFile->Get(("etaEndcap"+name).c_str());
    if(!etaEndcap) cout<<"Could not open etaEndcap hist"<<endl;
    
    auto etaNarrowEndcap = (TH1D*)inFile->Get(("etaLowWidthEndcap"+name).c_str());
    if(!etaNarrowEndcap) cout<<"Could not open etaNarrowEndcap hist"<<endl;
    
    auto hOverEbarrel    = (TH1D*)inFile->Get(("HoverEbarrel"+name).c_str());
    if(!hOverEbarrel) cout<<"Could not open hOverEbarrel hist"<<endl;
    
    auto hOverEendcap    = (TH1D*)inFile->Get(("HoverEendcap"+name).c_str());
    if(!hOverEendcap) cout<<"Could not open hOverEendcap hist"<<endl;
    
    auto hOverEmapNum    = (TH2D*)inFile->Get(("HoverEmapNum"+name).c_str());
    if(!hOverEmapNum) cout<<"Could not open hOverEmapNum hist"<<endl;
    
    auto hOverEmapDen    = (TH2D*)inFile->Get(("HoverEmapDen"+name).c_str());
    if(!hOverEmapDen) cout<<"Could not open hOverEmapDen hist"<<endl;
    
    auto hSwissCrossBarrel = (TH1D*)inFile->Get(("swissCrossBarrel"+name).c_str());
    if(!hSwissCrossBarrel) cout<<"Could not open hSwissCrossBarrel hist"<<endl;
    
    auto hSwissCrossEndcap = (TH1D*)inFile->Get(("swissCrossEndcap"+name).c_str());
    if(!hSwissCrossEndcap) cout<<"Could not open hSwissCrossEndcap hist"<<endl;
    
    int color = datasetColor.at(dataset);
    
    prepareHist(shapeBarrel, color);
    prepareHist(shapeEndcap, color);
    prepareHist(shapeEndcap2p3, color);
    prepareHist(hOverEbarrel, color);
    prepareHist(hOverEendcap, color);
    prepareHist(hOverEmapNum, color);
    prepareHist(hSwissCrossBarrel, color);
    prepareHist(hSwissCrossEndcap, color);
    
    canvasShower->cd(1); preparePad();
    shapeBarrel->SetTitle("#sigma_{i#etai#eta} Barrel");
    shapeBarrel->Draw(first ? "" : "same");
    if(first) drawThreshold(0.0106, "0.0106");
    
    canvasShower->cd(2); preparePad();
    shapeEndcap->SetTitle("#sigma_{i#etai#eta} Endcap");
    shapeEndcap->Draw(first ? "" : "same");
    if(first) drawThreshold(0.0272, "0.0272");
    
    canvasShower->cd(3); preparePad();
    hSwissCrossBarrel->SetTitle("Swiss cross Barrel");
//    hSwissCrossBarrel->GetXaxis()->SetRangeUser(0.0, 0.07);
    hSwissCrossBarrel->GetYaxis()->SetRangeUser(1E-8, 1.0);
    hSwissCrossBarrel->GetXaxis()->SetTitle("E4/E");
    hSwissCrossBarrel->Draw(first ? "" : "same");
    if(first) drawThreshold(0.005, "0.005");
    
    canvasShower->cd(4); preparePad();
    hSwissCrossEndcap->SetTitle("Swiss cross Endcap");
//    hSwissCrossEndcap->GetXaxis()->SetRangeUser(0.0, 0.07);
    hSwissCrossEndcap->GetXaxis()->SetTitle("E4/E");
    hSwissCrossEndcap->Draw(first ? "" : "same");
    if(first) drawThreshold(0.005, "0.005");
    
    /*
    if(dataset == kData){
      etaNarrowEndcap->Rebin(2);
      etaEndcap->Rebin(2);
      TH1D *notNarrow = new TH1D(*etaEndcap);
      notNarrow->Add(etaNarrowEndcap, -1);
      
      canvasShower->cd(3); preparePad();
      etaNarrowEndcap->SetLineColor(kRed);
      etaNarrowEndcap->SetTitle("");
      etaNarrowEndcap->GetXaxis()->SetTitle("#eta");
      etaNarrowEndcap->GetXaxis()->SetRangeUser(1, 3.2);
      etaNarrowEndcap->Scale(1./etaNarrowEndcap->GetEntries());
      etaNarrowEndcap->Sumw2(false);
      etaNarrowEndcap->Draw(first ? "" : "same");
      etaNarrowEndcap->GetXaxis()->SetRangeUser(1.5, 3.2);
      
      notNarrow->SetLineColor(kGreen+2);
      notNarrow->Scale(1./notNarrow->GetEntries());
      notNarrow->Sumw2(false);
      notNarrow->Draw("same");
      
      TLegend *legendEta = new TLegend(0.15, 0.75, 0.5, 0.9 );
      legendEta->AddEntry(etaNarrowEndcap, "#sigma_{i#etai#eta} < 0.001", "l");
      legendEta->AddEntry(notNarrow, "#sigma_{i#etai#eta} >= 0.001", "l");
      legendEta->Draw("same");
    }*/
    /*
    canvasShower->cd(4); preparePad();
    shapeEndcap2p3->SetTitle("Endcap, |#eta| < 2.3");
    shapeEndcap2p3->Draw(first ? "" : "same");
    if(first) drawThreshold(0.0272, "0.0272");
    */
    canvasHoverE->cd(1); preparePad();
    hOverEbarrel->GetXaxis()->SetTitle("H/E");
    hOverEbarrel->SetTitle("Barrel");
    hOverEbarrel->Rebin(5);
    hOverEbarrel->Draw(first ? "" : "same");
    if(first) drawThreshold(0.04596, "0.04596");
    
    canvasHoverE->cd(2); preparePad();
    hOverEendcap->GetXaxis()->SetTitle("H/E");
    hOverEendcap->SetTitle("Endcap");
    hOverEendcap->Rebin(5);
    hOverEendcap->Draw(first ? "" : "same");
    if(first) drawThreshold(0.0590, "0.0590");
    
    if(dataset == kData || dataset == kData_LbLsignal){
      canvasHoverE->cd(3); preparePad();
      gPad->SetLogy(false);
      gPad->SetRightMargin(0.15);
      
      int rebin = 2;
      hOverEmapNum->Rebin2D(rebin,rebin);
      hOverEmapDen->Rebin2D(rebin,rebin);
      hOverEmapNum->Divide(hOverEmapDen);
      
      hOverEmapNum->GetXaxis()->SetTitle("#phi");
      hOverEmapNum->GetYaxis()->SetTitle("#eta");
      hOverEmapNum->GetZaxis()->SetTitle("< H/E >");
      hOverEmapNum->GetZaxis()->SetTitleOffset(1.5);
      hOverEmapNum->GetZaxis()->SetRangeUser(0, 0.5);
      hOverEmapNum->Draw("colz");
    }
    
    legend->AddEntry(shapeBarrel, datasetDescription.at(dataset).c_str(), "l");
    
    first = false;
  }
  
  canvasShower->cd(1); legend->Draw("same");
  canvasShower->cd(2); legend->Draw("same");
  canvasShower->cd(4); legend->Draw("same");
  canvasHoverE->cd(1); legend->Draw("same");
  canvasHoverE->cd(2); legend->Draw("same");
  
  canvasShower->SaveAs(outputPathShower.c_str());
  canvasHoverE->SaveAs(outputPathHoverE.c_str());
}
