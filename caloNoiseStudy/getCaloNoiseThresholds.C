#include "CaloNoiseHelpers.h"

void getCaloNoiseThresholds()
{
  
  // Find noise thresholds
  for(int iDet=0;iDet<nDets;iDet++){
    // Normalize histograms by number of entries
    energyHist[iDet]->Scale(1/energyHist[iDet]->GetEntries());
    
    double histIntegral = energyHist[iDet]->Integral(energyHist[iDet]->GetXaxis()->FindFixBin(0.0),
                                                     energyHist[iDet]->GetXaxis()->FindFixBin(10.0));
    
    double threshold;
    
    for(threshold=0; threshold<10.0; threshold+=0.01){
      double currentIntegral = energyHist[iDet]->Integral(energyHist[iDet]->GetXaxis()->FindFixBin(0.0),
                                                          energyHist[iDet]->GetXaxis()->FindFixBin(threshold));
      
      if(currentIntegral >= 0.99*histIntegral) break;
    }
    
    cout<<"Threshold for "<<detNames[iDet]<<": "<<threshold<<" GeV"<<endl;
  }
  
  
  // Draw histograms and save the output
  auto inputCanvas  = new TCanvas("inputCanvas", "inputCanvas",   800, 1200);
  auto outputCanvas = new TCanvas("outputCanvas", "outputCanvas", 800, 1200);
  
  inputCanvas->Divide(2,3);
  outputCanvas->Divide(2,3);
  
  int iPad=1;
  for(auto &[varName, a, b, c] : inputVarParams){
    inputCanvas->cd(iPad++);
    inputHists[varName]->Draw();
  }
  
  for(int iDet=0;iDet<nDets;iDet++){
    outputCanvas->cd(iDet+1);
    gPad->SetLogy();
    energyHist[iDet]->Draw();
  }
  
  
}
