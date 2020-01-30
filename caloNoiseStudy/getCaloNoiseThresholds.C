#include "CaloNoiseHelpers.h"

double getThreshold(TH1D *hist)
{
  hist->Scale(1/hist->GetEntries());
  
  double histIntegral = hist->Integral(hist->GetXaxis()->FindFixBin(0.0),
                                                   hist->GetXaxis()->FindFixBin(10.0));
  
  double threshold;
  
  for(threshold=0; threshold<10.0; threshold+=0.01){
    double currentIntegral = hist->Integral(hist->GetXaxis()->FindFixBin(0.0),
                                                        hist->GetXaxis()->FindFixBin(threshold));
    
    if(currentIntegral >= 0.99*histIntegral) break;
  }
  return threshold;
}

void getCaloNoiseThresholds()
{
  TFile *inFile = TFile::Open("noiseStudyOutputEmpty_newGT.root");
  auto canvas = new TCanvas("canvas", "canvas", 800, 1200);
  canvas->Divide(2,3);
  
  // Find noise thresholds
  for(int iDet=0;iDet<nDets;iDet++){
    // Normalize histograms by number of entries
    auto hist = (TH1D*)inFile->Get(("energyHist"+detNames[iDet]).c_str());
    
    double threshold = getThreshold(hist);
    
    cout<<"Threshold for "<<detNames[iDet]<<": "<<threshold<<" GeV"<<endl;
    
    TLine thresholdLine(threshold, 0, threshold, 1);
    thresholdLine.SetLineColor(kMagenta+2);
    thresholdLine.SetLineWidth(1.0);
    
    canvas->cd(iDet+1);
    gPad->SetLogy();
    hist->Draw();
    thresholdLine.Draw();
  }
  
  TH2D *histEEvsEta = (TH2D*)inFile->Get("energyHistEEVsEta");
  
  TH2D *histEEvsFabsEta = new TH2D(*histEEvsEta);
  histEEvsFabsEta->Reset();
  
  for(int xBin=1; xBin <=histEEvsFabsEta->GetNbinsX(); xBin++){
    double eta = fabs(histEEvsEta->GetXaxis()->GetBinCenter(xBin));
    int newXbin = histEEvsFabsEta->GetXaxis()->FindFixBin(eta);
    
    for(int yBin=1; yBin <=histEEvsFabsEta->GetNbinsY(); yBin++){
      histEEvsFabsEta->Fill(histEEvsEta->GetXaxis()->GetBinCenter(newXbin),
                            histEEvsEta->GetYaxis()->GetBinCenter(yBin),
                            histEEvsEta->GetBinContent(xBin, yBin));
    }
  }
  
  double etaStep = 0.1;
  
  for(double eta=1.5; eta<=3.2; eta+=etaStep){
    int binLow  = histEEvsEta->GetXaxis()->FindFixBin(eta);
    int binHigh = histEEvsEta->GetXaxis()->FindFixBin(eta+etaStep);
    
    TH1D *slice = histEEvsEta->ProjectionY("", binLow, binHigh);
    
    cout<<eta<<"\t"<<getThreshold(slice)<<endl;
    
    slice->Draw("same");
  }
  
  
  for(double eta=1.0; eta<3.1; eta+=0.1){
    
  }
  
}
