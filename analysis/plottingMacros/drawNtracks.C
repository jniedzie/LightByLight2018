#include "../include/Helpers.hpp"

const int maxNevents = 10000;

string inputPath  = "../results/basicPlots.root";
string outputPath = "../plots/nTracks.pdf";

void prepareHist(TH1D *hist, int color)
{
  hist->SetLineColor(color);
  hist->SetLineWidth(2);
  hist->SetTitle("");
  hist->GetYaxis()->SetTitle("# events");
  hist->GetYaxis()->SetTitleSize(0.06);
  hist->GetXaxis()->SetTitle("# tracks");
  hist->GetXaxis()->SetTitleSize(0.06);
  hist->Scale(1./hist->GetEntries());
  hist->GetXaxis()->SetRangeUser(0, 15);
  hist->GetYaxis()->SetRangeUser(1e-4, 1.0);
  hist->Sumw2(false);
}

void preparePad()
{
  gPad->SetLogy();
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);
}

void drawNtracks()
{
  TFile *inFile = TFile::Open(inputPath.c_str());
  
  TCanvas *canvas = new TCanvas("N tracks", "n Tracks", 1000, 1000);
  canvas->Divide(2,2);
  
  gStyle->SetOptStat(0);
  TLegend *legend = new TLegend(0.5, 0.7, 0.9, 0.9 );
  
  bool first = true;
  for(EDataset dataset : datasets){
    string name        = datasetName.at(dataset);
    string description = datasetDescription.at(dataset);
    
    cout<<"Processing "<<description<<" events"<<endl;
    
    auto nTrackHist       = (TH1D*)inFile->Get(("nTracks"+name).c_str());
    auto nTrackHighPtHist = (TH1D*)inFile->Get(("nTracks_pt_geq_100_MeV"+name).c_str());
    auto nTrackLowPtHist  = (TH1D*)inFile->Get(("nTracks_pt_lt_100_MeV"+name).c_str());
    auto trackPtHist      = (TH1D*)inFile->Get(("track_pt"+name).c_str());
    
    int color = datasetColor.at(dataset);
    
    prepareHist(nTrackHist, color);
    prepareHist(nTrackLowPtHist, color);
    prepareHist(nTrackHighPtHist, color);
    prepareHist(trackPtHist, color);
    
    canvas->cd(1); preparePad();
    nTrackHist->SetTitle("# tracks");
    nTrackHist->Draw(first ? "" : "same");
   
    canvas->cd(2); preparePad();
    trackPtHist->SetTitle("Track p_{T}");
    trackPtHist->SetLineWidth(1);
    trackPtHist->GetXaxis()->SetTitle("p_{T} (GeV)");
    trackPtHist->GetXaxis()->SetRangeUser(0, 1);
    trackPtHist->GetYaxis()->SetRangeUser(1e-6, 1);
    trackPtHist->Draw(first ? "" : "same");
   
    canvas->cd(3); preparePad();
    nTrackLowPtHist->SetTitle("# tracks, p_{T} < 100 MeV");
    nTrackLowPtHist->Draw(first ? "" : "same");
   
    canvas->cd(4); preparePad();
    nTrackHighPtHist->SetTitle("# tracks, p_{T} #geq 100 MeV");
    nTrackHighPtHist->Draw(first ? "" : "same");
   
    legend->AddEntry(nTrackHist, datasetDescription.at(dataset).c_str(), "l");
   
    first = false;
  }
  canvas->cd(1); legend->Draw("same");
  canvas->cd(2); legend->Draw("same");
  canvas->cd(3); legend->Draw("same");
  canvas->cd(4); legend->Draw("same");
  
  canvas->SaveAs(outputPath.c_str());
}
