#include "../include/Helpers.hpp"

string inputPath  = "../results/photonID.root";
string outputPathShower = "../plots/photonShowerShape.pdf";
string outputPathHoverE = "../plots/photonHoverE.pdf";

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
  for(EDataset dataset : datasets){
    string name = datasetName.at(dataset);

    auto shapeBarrel     = (TH1D*)inFile->Get(("showerShapeBarrel"+name).c_str());
    auto shapeEndcap     = (TH1D*)inFile->Get(("showerShapeEndcap"+name).c_str());
    auto shapeEndcap2p3  = (TH1D*)inFile->Get(("showerShapeEndcap2p3"+name).c_str());
    auto etaEndcap       = (TH1D*)inFile->Get(("etaEndcap"+name).c_str());
    auto etaNarrowEndcap = (TH1D*)inFile->Get(("etaLowWidthEndcap"+name).c_str());
    
    auto hOverE          = (TH1D*)inFile->Get(("HoverE"+name).c_str());
    auto hOverE2p3       = (TH1D*)inFile->Get(("HoverE2p3"+name).c_str());
    auto etaLowHoverE    = (TH1D*)inFile->Get(("etaLowHoverE"+name).c_str());
    auto etaHighHoverE   = (TH1D*)inFile->Get(("etaHighHoverE"+name).c_str());

    int color = datasetColor.at(dataset);
    
    prepareHist(shapeBarrel, color);
    prepareHist(shapeEndcap, color);
    prepareHist(shapeEndcap2p3, color);
    prepareHist(hOverE, color);
    prepareHist(hOverE2p3, color);
    
    canvasShower->cd(1); preparePad();
    shapeBarrel->SetTitle("Barrel");
    shapeBarrel->Draw(first ? "" : "same");
    
    canvasShower->cd(2); preparePad();
    shapeEndcap->SetTitle("Endcap");
    shapeEndcap->Draw(first ? "" : "same");

    if(dataset == kData){
      etaNarrowEndcap->Rebin(2);
      etaEndcap->Rebin(2);
      TH1D *notNarrow = new TH1D(*etaEndcap);
      notNarrow->Add(etaNarrowEndcap, -1);
      
      canvasShower->cd(3); preparePad();
      etaNarrowEndcap->SetLineColor(kRed);
      etaNarrowEndcap->GetXaxis()->SetTitle("#eta");
      etaNarrowEndcap->GetXaxis()->SetRangeUser(1, 3.2);
      etaNarrowEndcap->Scale(1./etaNarrowEndcap->GetEntries());
      etaNarrowEndcap->Sumw2(false);
      etaNarrowEndcap->Draw(first ? "" : "same");
      
      notNarrow->SetLineColor(kGreen+2);
      notNarrow->Scale(1./notNarrow->GetEntries());
      notNarrow->Sumw2(false);
      notNarrow->Draw("same");
      
      TLegend *legendEta = new TLegend(0.15, 0.75, 0.5, 0.9 );
      legendEta->AddEntry(etaNarrowEndcap, "#sigma_{i#etai#eta} < 0.001", "l");
      legendEta->AddEntry(notNarrow, "#sigma_{i#etai#eta} >= 0.001", "l");
      legendEta->Draw("same");
      
      
      canvasHoverE->cd(2); preparePad();
      etaHighHoverE->SetLineColor(kRed);
      etaHighHoverE->GetXaxis()->SetTitle("#eta");
      etaHighHoverE->GetXaxis()->SetRangeUser(1, 3.2);
      etaHighHoverE->Scale(1./etaHighHoverE->GetEntries());
      etaHighHoverE->Rebin(5);
      etaHighHoverE->Sumw2(false);
      etaHighHoverE->Draw(first ? "" : "same");
      
      etaLowHoverE->SetLineColor(kGreen+2);
      etaLowHoverE->Scale(1./etaLowHoverE->GetEntries());
      etaLowHoverE->Rebin(5);
      etaLowHoverE->Sumw2(false);
      etaLowHoverE->Draw("same");
      
      TLegend *legendEtaHoverE = new TLegend(0.15, 0.75, 0.5, 0.9 );
      legendEtaHoverE->AddEntry(etaHighHoverE,"H/E > 0.15", "l");
      legendEtaHoverE->AddEntry(etaLowHoverE, "H/E <= 0.15", "l");
      legendEtaHoverE->Draw("same");
    }
    
    canvasShower->cd(4); preparePad();
    shapeEndcap2p3->SetTitle("Endcap, |#eta| < 2.3");
    shapeEndcap2p3->Draw(first ? "" : "same");
    
    canvasHoverE->cd(1); preparePad();
    hOverE->GetXaxis()->SetTitle("H/E");
    hOverE->Rebin(5);
    hOverE->Draw(first ? "" : "same");

    canvasHoverE->cd(3); preparePad();
    hOverE2p3->GetXaxis()->SetTitle("H/E");
    hOverE2p3->Rebin(5);
    hOverE2p3->Draw(first ? "" : "same");
    
    legend->AddEntry(shapeBarrel, datasetDescription.at(dataset).c_str(), "l");
    
    first = false;
  }
  
  canvasShower->cd(1); legend->Draw("same");
  canvasShower->cd(2); legend->Draw("same");
  canvasShower->cd(4); legend->Draw("same");
  canvasHoverE->cd(1); legend->Draw("same");
  canvasHoverE->cd(3); legend->Draw("same");
  
  canvasShower->SaveAs(outputPathShower.c_str());
  canvasHoverE->SaveAs(outputPathHoverE.c_str());
}
