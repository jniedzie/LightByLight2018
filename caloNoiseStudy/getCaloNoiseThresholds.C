#include "CaloNoiseHelpers.h"

void getCaloNoiseThresholds()
{
  TFile *inFile = TFile::Open("noiseStudyOutput_merged.root");
  auto canvas = new TCanvas("canvas", "canvas", 800, 1200);
  canvas->Divide(2,3);
  
  // Find noise thresholds
  for(int iDet=0;iDet<nDets;iDet++){
    // Normalize histograms by number of entries
    auto hist = (TH1D*)inFile->Get(("energyHist"+detNames[iDet]).c_str());
    
    hist->Scale(1/hist->GetEntries());
    
    double histIntegral = hist->Integral(hist->GetXaxis()->FindFixBin(0.0),
                                                     hist->GetXaxis()->FindFixBin(10.0));
    
    double threshold;
    
    for(threshold=0; threshold<10.0; threshold+=0.01){
      double currentIntegral = hist->Integral(hist->GetXaxis()->FindFixBin(0.0),
                                                          hist->GetXaxis()->FindFixBin(threshold));
      
      if(currentIntegral >= 0.99*histIntegral) break;
    }
    
    cout<<"Threshold for "<<detNames[iDet]<<": "<<threshold<<" GeV"<<endl;
    
    TLine thresholdLine(threshold, 0, threshold, 1);
    thresholdLine.SetLineColor(kMagenta+2);
    thresholdLine.SetLineWidth(1.0);
    
    canvas->cd(iDet+1);
    gPad->SetLogy();
    hist->Draw();
    thresholdLine.Draw();
  }
}
