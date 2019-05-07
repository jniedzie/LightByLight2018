#include "CaloNoiseHelpers.h"

void getCaloNoiseThresholds(const char* infileName)
{
  TFile *inFile = TFile::Open(infileName);
  if(!inFile){
    cout<<"File not found:"<<infileName<<endl;
    exit(0);
  }
  TH1D *energyHist[nDets];
  double thresholds[nDets];
  
  // Find noise thresholds
  for(int iDet=0;iDet<nDets;iDet++){
    energyHist[iDet] = (TH1D*)inFile->Get(Form("energyHist%s",detNames[iDet].c_str()));
    
    // Normalize histograms by number of entries
    energyHist[iDet]->Scale(1/energyHist[iDet]->GetEntries());
    
    double histIntegral = energyHist[iDet]->Integral(1, energyHist[iDet]->GetNbinsX()+1);
    
    for(int iBin=1; iBin<=energyHist[iDet]->GetNbinsX(); iBin++){
      double currentIntegral = energyHist[iDet]->Integral(1,iBin);
      thresholds[iDet] = energyHist[iDet]->GetBinCenter(iBin);
      if(currentIntegral >= 0.99*histIntegral) break;
    }
    
    cout<<"Threshold for "<<detNames[iDet]<<": "<<thresholds[iDet]<<" GeV"<<endl;
  }
  
  // Draw histograms and save the output
  auto thresholdsCanvas = new TCanvas("thresholdsCanvas", "thresholdsCanvas", 800, 1200);

  thresholdsCanvas->Divide(2,3);
  
  for(int iDet=0;iDet<nDets;iDet++){
    thresholdsCanvas->cd(iDet+1);
    gPad->SetLogy();
    energyHist[iDet]->Draw();
  }
  
  
}
