#include "CaloNoiseHelpers.h"

TH1D* GetEEhist(TFile *inFile, double etaMin, double etaMax);
TH1D* GetHFphist(TFile *inFile, double etaMin);
TH1D* GetHFmhist(TFile *inFile, double etaMax);

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
//    if(iDet == kEE){ // EE is very noisy, so we need to remove some eta regions
//      energyHist[iDet] = GetEEhist(inFile, -2.3, 2.3);
//    }
//    else if(iDet == kHFp){
//      energyHist[iDet] = GetHFphist(inFile, 3.4);
//    }
//    else if(iDet == kHFm){
//      energyHist[iDet] = GetHFmhist(inFile,-3.4);
//    }
//    else{
      energyHist[iDet] = (TH1D*)inFile->Get(Form("energyHist%s",detNames[iDet].c_str()));
//    }
    if(!energyHist[iDet]){
      continue;
    }
    
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
    if(!energyHist[iDet]) continue;
    thresholdsCanvas->cd(iDet+1);
    gPad->SetLogy();
    energyHist[iDet]->Draw();
    energyHist[iDet]->GetXaxis()->SetRangeUser(0, 10);
  }
  
  
}

TH1D* GetEEhist(TFile *inFile, double etaMin, double etaMax)
{
  TH2D *noiseVsEtaEE = (TH2D*)inFile->Get("energyHistEEVsEta");
  TH1D *noiseEEwithCut = noiseVsEtaEE->ProjectionY("projEE",
                                                   noiseVsEtaEE->GetXaxis()->FindFixBin(etaMin),
                                                   noiseVsEtaEE->GetXaxis()->FindFixBin(etaMax));
  
  noiseEEwithCut->SetTitle("energyHistEE");
  
  return noiseEEwithCut;
}

TH1D* GetHFphist(TFile *inFile, double etaMin)
{
  TH2D *noiseVsEtaHF = (TH2D*)inFile->Get("energyHistHFpVsEta");
  
  TH1D *noiseHFwithCut = noiseVsEtaHF->ProjectionY("projHFpos",
                                                   noiseVsEtaHF->GetXaxis()->FindFixBin(etaMin),
                                                   noiseVsEtaHF->GetNbinsX());
  return noiseHFwithCut;
}

TH1D* GetHFmhist(TFile *inFile, double etaMax)
{
  TH2D *noiseVsEtaHF = (TH2D*)inFile->Get("energyHistHFmVsEta");
  
  TH1D *noiseHFwithCut = noiseVsEtaHF->ProjectionY("projHFneg",
                                                   1,
                                                   noiseVsEtaHF->GetXaxis()->FindFixBin(etaMax));
  
  return noiseHFwithCut;
}
