#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include "plotStyle.h"

void drawCastorPlots(){
  TFile f("/eos/cms/store/group/phys_heavyions/osuranyi/lbyl_2018/castorPlots/merged_castorPlots_data.root");
  
  initRootStyle();

  std::array<TH1F*,16> energyHists;
  std::array<TLine*,16> lines;

  for(int i = 0; i < 16; i++)
    energyHists[i] = (TH1F*)f.Get(Form("eTotCastor%dData",i));

  TCanvas* c1 = new TCanvas();

  //c1->SetLogy();

  double q[3];
  double p[3] = {1.0-0.01, 1.0-0.005, 1.0-0.001};

  std::ofstream thresholdFile("thresholds.dat");

  for(int i = 0; i < 16; i++){
    energyHists[i]->SetTitle("");
    energyHists[i]->GetXaxis()->SetTitle("E [GeV]");
    energyHists[i]->GetYaxis()->SetTitle("Entries");
    
    energyHists[i]->SetMarkerSize(1);
    energyHists[i]->SetMarkerColor(4);
    energyHists[i]->SetMarkerStyle(20);

    energyHists[i]->SetLineColor(4);

    energyHists[i]->GetQuantiles(3,q,p);

    thresholdFile << q[0] << "\t" << q[1] << "\t" << q[2] << std::endl;

    lines[i] = new TLine(q[0],0.0,q[0],energyHists[i]->GetMaximum()*0.7);
    lines[i]->SetLineWidth(2);
    lines[i]->SetLineStyle(2);

    energyHists[i]->Draw("hist e");
    lines[i]->Draw("same");
    c1->SaveAs(Form("castorPlots/energyHistPhi%d.png",i));
  }
}
