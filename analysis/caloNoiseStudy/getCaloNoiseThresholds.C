//#include "CaloNoiseHelpers.h"
#include "../include/Helpers.hpp"

string inputPath = "noiseStudyOutputEmpty_newGT.root";

double getThreshold(TH1D *hist)
{
  hist->Scale(1./hist->GetEntries());
  
  double histIntegral = hist->Integral(hist->GetXaxis()->FindFixBin(0.0),
                                       hist->GetXaxis()->FindFixBin(20.0));
  
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
  TFile *inFile = TFile::Open(inputPath.c_str());
  auto canvas = new TCanvas("canvas", "canvas", 800, 1200);
  canvas->Divide(2,3);
  
  auto canvasEE = new TCanvas("canvasEE", "canvasEE", 800, 400);
  canvasEE->Divide(2,1);
 
  gStyle->SetOptStat(0);
  
  // Find noise thresholds
  for(ECaloType iDet : calotypes){
    if(iDet==kEE) continue;
    
    // Normalize histograms by number of entries
    auto hist = (TH1D*)inFile->Get(("energyHist"+caloName.at(iDet)).c_str());
    
    hist->SetTitle(("Leading tower energy in "+caloName.at(iDet)).c_str());
    hist->GetXaxis()->SetTitle("Leading tower E (GeV)");
    
    double threshold = getThreshold(hist);
    cout<<"Threshold for "<<caloName.at(iDet)<<": "<<threshold<<" GeV"<<endl;
    
    canvas->cd(iDet+1);
    gPad->SetLogy();
    hist->Draw();
    
    TLine *thresholdLine = new TLine(threshold, hist->GetMinimum(), threshold, hist->GetMaximum());
    thresholdLine->SetLineColor(kGreen+2);
    thresholdLine->SetLineWidth(1.0);
    thresholdLine->Draw();
    
    TLatex *text = new TLatex(threshold+0.005, 3e-2, Form("   %.1f GeV", threshold));
    text->SetTextColor(kGreen+2);
    text->SetTextSize(0.05);
    text->Draw("same");
    
  }
  
  // Plots for EE
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
  
  canvasEE->cd(1);
  histEEvsFabsEta->GetXaxis()->SetRangeUser(1.4, 3.0);
  histEEvsFabsEta->SetTitle("Leading tower energy in EE vs. #eta");
  histEEvsFabsEta->GetXaxis()->SetTitle("|#eta|");
  histEEvsFabsEta->GetYaxis()->SetTitle("Leading tower energy (GeV)");
  histEEvsFabsEta->Draw("colz");
  
  
  
  double eta = 2.4;
  TH1D *histEEp = (TH1D*)histEEvsFabsEta->ProjectionY("histEEp",
                                                      histEEvsFabsEta->GetXaxis()->FindFixBin(0.0),
                                                      histEEvsFabsEta->GetXaxis()->FindFixBin(eta),
                                                      "e");
  
  
  
  
  
  double etaStep = 0.2;
  
  canvasEE->cd(2);
  
  TLegend *legend = new TLegend(0.4, 0.55, 0.9, 0.9);
  
  vector<tuple<double, int>> etaParams ={
    {1.4,   kGreen+3   },
    {1.6,   kGreen     },
    {1.8,   kCyan      },
    {2.0,   kBlue      },
    {2.2,   kViolet+2  },
    {2.4,   kMagenta   },
    {2.6,   kOrange    },
    {2.8,   kOrange+2  },
    {3.0,   kRed       },
  };
  
  for(auto &[eta, color] : etaParams){
    TH1D *histEEp = (TH1D*)histEEvsFabsEta->ProjectionY(("histEEp"+to_string(eta)).c_str(),
                                                        histEEvsFabsEta->GetXaxis()->FindFixBin(0.0),
                                                        histEEvsFabsEta->GetXaxis()->FindFixBin(eta),
                                                        "e");
    
    for(int i=1; i<=histEEp->GetNbinsX(); i++) histEEp->SetBinError(i, 0);
    histEEp->Rebin(5);
    histEEp->SetLineColor(color);
    histEEp->SetTitle("Leading tower energy in EE");
    if(eta==1.4){
      histEEp->GetXaxis()->SetTitle("Leading tower energy (GeV)");
      histEEp->SetMinimum(1e-4);
      histEEp->SetMaximum(1e3);
      histEEp->DrawNormalized();
      
    }
    else{
      histEEp->DrawNormalized("same");
    }
    double threshold = getThreshold(histEEp);
    
    legend->AddEntry(histEEp, ("|#eta| < "+to_string_with_precision(eta, 1)+" ("+to_string_with_precision(threshold, 1)+" GeV)").c_str(), "l");

    gPad->SetLogy();
  }
  legend->Draw();

                    
  canvas->SaveAs("noise_thresholds.pdf");
  canvasEE->SaveAs("noise_thresholds_EE.pdf");
  
}
