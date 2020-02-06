#include "CaloNoiseHelpers.h"

double getThreshold(TH1D *hist)
{
  hist->Scale(1./hist->GetEntries());
  
  double histIntegral = hist->Integral(hist->GetXaxis()->FindFixBin(0.0),
                                       hist->GetXaxis()->FindFixBin(20.0));
  
//  double histIntegral = 1;//hist->Integral();
  
//  cout<<"integral: "<<histIntegral<<endl;
  
  double threshold;
  
  for(threshold=0; threshold <= 20.0; threshold+=0.001){
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
    
    canvas->cd(iDet+1);
    gPad->SetLogy();
    hist->Draw();
    
    TLine *thresholdLine = new TLine(threshold, hist->GetMinimum(), threshold, hist->GetMaximum());
    thresholdLine->SetLineColor(kMagenta+2);
    thresholdLine->SetLineWidth(1.0);
    thresholdLine->Draw();
  }
  
  TH2D *histEEvsEta = (TH2D*)inFile->Get("energyHistEEVsEta");
  TH2D *histEEvsFabsEta = new TH2D(*histEEvsEta);
  histEEvsFabsEta->Reset();

  for(int xBin=1; xBin <= histEEvsEta->GetNbinsX(); xBin++){
    double eta = fabs(histEEvsEta->GetXaxis()->GetBinCenter(xBin));
    int newXbin = histEEvsFabsEta->GetXaxis()->FindFixBin(eta);

    for(int yBin=1; yBin <= histEEvsEta->GetNbinsY(); yBin++){
      
      histEEvsFabsEta->Fill(histEEvsFabsEta->GetXaxis()->GetBinCenter(newXbin),
                            histEEvsFabsEta->GetYaxis()->GetBinCenter(yBin),
                            histEEvsEta->GetBinContent(xBin, yBin));
    }
  }
  
    
  //  TH1D *histEE = (TH1D*)histEEvsEta->ProjectionY();
    
    double eta = 2.4;
    TH1D *histEEp = (TH1D*)histEEvsFabsEta->ProjectionY("",
                                                    histEEvsFabsEta->GetXaxis()->FindFixBin(0.0),
                                                    histEEvsFabsEta->GetXaxis()->FindFixBin(eta));
    histEEp->Draw();
    double threshold = getThreshold(histEEp);
    cout<<"Threshold for EE with eta < "<<eta<<": "<<threshold<<" GeV"<<endl;
  
  
  double etaStep = 0.1;

  for(double eta=1.5; eta<=3.2; eta+=etaStep){
    int binLow  = histEEvsEta->GetXaxis()->FindFixBin(eta);
    int binHigh = histEEvsEta->GetXaxis()->FindFixBin(eta+etaStep);

    TH1D *slice = histEEvsEta->ProjectionY("", binLow, binHigh);

    cout<<eta<<"\t"<<getThreshold(slice)<<endl;
  }
  
}
