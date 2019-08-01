#include "../include/Helpers.hpp"

string inputPath  = "../results/showerShape.root";
string outputPath = "../plots/showerShape.pdf";

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

void preparePad()
{
  gPad->SetLogy();
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);
}

void drawShowerShape()
{
  TFile *inFile = TFile::Open(inputPath.c_str());
  
  TCanvas *canvas = new TCanvas("Shower shape", "Shower shape", 1000, 1000);
  canvas->Divide(2,2);
  gStyle->SetOptStat(0);
  TLegend *legend = new TLegend(0.5, 0.7, 0.9, 0.9 );
  
  
  bool first = true;
  for(EDataset dataset : datasets){
    string name = datasetName.at(dataset);

    auto shapeBarrel     = (TH1D*)inFile->Get(("showerShapeBarrel"+name).c_str());
    auto shapeEndcap     = (TH1D*)inFile->Get(("showerShapeEndcap"+name).c_str());
    auto shapeEndcap2p3  = (TH1D*)inFile->Get(("showerShapeEndcap2p3"+name).c_str());
    auto etaBarrel       = (TH1D*)inFile->Get(("etaBarrel"+name).c_str());
    auto etaEndcap       = (TH1D*)inFile->Get(("etaEndcap"+name).c_str());
    auto etaNarrowBarrel = (TH1D*)inFile->Get(("etaLowWidthBarrel"+name).c_str());
    auto etaNarrowEndcap = (TH1D*)inFile->Get(("etaLowWidthEndcap"+name).c_str());

    int color = datasetColor.at(dataset);
    
    prepareHist(shapeBarrel, color);
    prepareHist(shapeEndcap, color);
    prepareHist(shapeEndcap2p3, color);
//    prepareHist(etaBarrel, color);
//    prepareHist(etaEndcap, color);
//    prepareHist(etaNarrowBarrel, color);
//    prepareHist(etaNarrowEndcap, color);
    
    canvas->cd(1); preparePad();
    shapeBarrel->SetTitle("Barrel");
    shapeBarrel->Draw(first ? "" : "same");
    
    canvas->cd(2); preparePad();
    shapeEndcap->SetTitle("Endcap");
    shapeEndcap->Draw(first ? "" : "same");

    if(dataset == kData){
      etaNarrowEndcap->Rebin(2);
      etaEndcap->Rebin(2);
      
      canvas->cd(3); preparePad();
      etaNarrowEndcap->SetLineColor(kRed);
      etaNarrowEndcap->GetXaxis()->SetTitle("#eta");
      etaNarrowEndcap->GetXaxis()->SetRangeUser(1, 3.2);
      etaNarrowEndcap->Draw(first ? "" : "same");
      
      TH1D *notNarrow = new TH1D(*etaEndcap);
      notNarrow->Add(etaNarrowEndcap, -1);
      notNarrow->SetLineColor(kGreen+2);
      
      notNarrow->Draw("same");
      
      TLegend *legendEta = new TLegend(0.15, 0.75, 0.5, 0.9 );
      legendEta->AddEntry(etaNarrowEndcap, "#sigma_{i#etai#eta} < 0.001", "l");
      legendEta->AddEntry(notNarrow, "#sigma_{i#etai#eta} >= 0.001", "l");
      legendEta->Draw("same");
    }
    
    canvas->cd(4); preparePad();
    shapeEndcap2p3->SetTitle("Endcap, |#eta| < 2.3");
    shapeEndcap2p3->Draw(first ? "" : "same");

    legend->AddEntry(shapeBarrel, datasetDescription.at(dataset).c_str(), "l");
    
    first = false;
  }
  
  canvas->cd(1); legend->Draw("same");
  canvas->cd(2); legend->Draw("same");
  canvas->cd(4); legend->Draw("same");
  
  canvas->SaveAs(outputPath.c_str());
}
