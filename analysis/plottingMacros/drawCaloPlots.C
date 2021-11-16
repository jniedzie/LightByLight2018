#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include "plotStyle.h"

void drawCaloPlots(){
  //TFile f("/eos/cms/store/group/phys_heavyions/osuranyi/lbyl_2018/caloPlots/merged_caloPlots.root");
  TFile f("../test_calo.root");
  TFile f_lbl("../test_calo_lbl.root");

  initRootStyle();

  TH1F *eEB = (TH1F*)f.Get("eEBData");
  TH1F *eEE = (TH1F*)f.Get("eEEData");
  TH1F *eHB = (TH1F*)f.Get("eHBData");
  TH1F *eHE = (TH1F*)f.Get("eHEData");
  TH1F *eHFp = (TH1F*)f.Get("eHFpData");
  TH1F *eHFm = (TH1F*)f.Get("eHFmData");

  TH1F *eEB_lbl = (TH1F*)f_lbl.Get("eEBData");
  TH1F *eEE_lbl = (TH1F*)f_lbl.Get("eEEData");
  TH1F *eHB_lbl = (TH1F*)f_lbl.Get("eHBData");
  TH1F *eHE_lbl = (TH1F*)f_lbl.Get("eHEData");
  TH1F *eHFp_lbl = (TH1F*)f_lbl.Get("eHFpData");
  TH1F *eHFm_lbl = (TH1F*)f_lbl.Get("eHFmData");


  TH2F *eEB_eta = (TH2F*)f.Get("eEB_etaData");
  TH2F *eEE_eta = (TH2F*)f.Get("eEE_etaData");
  TH2F *eHB_eta = (TH2F*)f.Get("eHB_etaData");
  TH2F *eHE_eta = (TH2F*)f.Get("eHE_etaData");
  TH2F *eHF_eta = (TH2F*)f.Get("eHF_etaData");
 
  TH2F *eEB_eta_phi = (TH2F*)f.Get("eEB_eta_phiData");
  TH2F *eEE_eta_phi = (TH2F*)f.Get("eEE_eta_phiData");
  TH2F *eHB_eta_phi = (TH2F*)f.Get("eHB_eta_phiData");
  TH2F *eHE_eta_phi = (TH2F*)f.Get("eHE_eta_phiData");
  TH2F *eHF_eta_phi = (TH2F*)f.Get("eHF_eta_phiData");

  // index version
  TH2F *eEB_ieta = (TH2F*)f.Get("eEB_ietaData");
  TH2F *eEE_ieta = (TH2F*)f.Get("eEE_ietaData");
  TH2F *eHB_ieta = (TH2F*)f.Get("eHB_ietaData");
  TH2F *eHE_ieta = (TH2F*)f.Get("eHE_ietaData");
  TH2F *eHF_ieta = (TH2F*)f.Get("eHF_ietaData");
 
  TH2F *eEB_ieta_iphi = (TH2F*)f.Get("eEB_ieta_iphiData");
  TH2F *eEE_ieta_iphi = (TH2F*)f.Get("eEE_ieta_iphiData");
  TH2F *eHB_ieta_iphi = (TH2F*)f.Get("eHB_ieta_iphiData");
  TH2F *eHE_ieta_iphi = (TH2F*)f.Get("eHE_ieta_iphiData");
  TH2F *eHF_ieta_iphi = (TH2F*)f.Get("eHF_ieta_iphiData");

  // Leading tower distributions
  TH1F *eEB_leadingTower = (TH1F*)(TH2F*)f.Get("eEB_leadingTowerData");
  TH1F *eEE_leadingTower = (TH1F*)(TH2F*)f.Get("eEE_leadingTowerData");
  TH1F *eHB_leadingTower = (TH1F*)(TH2F*)f.Get("eHB_leadingTowerData");
  TH1F *eHE_leadingTower = (TH1F*)(TH2F*)f.Get("eHE_leadingTowerData");
  TH1F *eHFp_leadingTower = (TH1F*)(TH2F*)f.Get("eHFp_leadingTowerData");
  TH1F *eHFm_leadingTower = (TH1F*)(TH2F*)f.Get("eHFm_leadingTowerData");

  TH1F *eEB_leadingTower_lbl = (TH1F*)(TH2F*)f_lbl.Get("eEB_leadingTowerData");
  TH1F *eEE_leadingTower_lbl = (TH1F*)(TH2F*)f_lbl.Get("eEE_leadingTowerData");
  TH1F *eHB_leadingTower_lbl = (TH1F*)(TH2F*)f_lbl.Get("eHB_leadingTowerData");
  TH1F *eHE_leadingTower_lbl = (TH1F*)(TH2F*)f_lbl.Get("eHE_leadingTowerData");
  TH1F *eHFp_leadingTower_lbl = (TH1F*)(TH2F*)f_lbl.Get("eHFp_leadingTowerData");
  TH1F *eHFm_leadingTower_lbl = (TH1F*)(TH2F*)f_lbl.Get("eHFm_leadingTowerData");


  TH2F *eEB_eta_leadingTower = (TH2F*)f.Get("eEB_eta_leadingTowerData");
  TH2F *eEE_eta_leadingTower = (TH2F*)f.Get("eEE_eta_leadingTowerData");
  TH2F *eHB_eta_leadingTower = (TH2F*)f.Get("eHB_eta_leadingTowerData");
  TH2F *eHE_eta_leadingTower = (TH2F*)f.Get("eHE_eta_leadingTowerData");
  TH2F *eHF_eta_leadingTower = (TH2F*)f.Get("eHF_eta_leadingTowerData");
 
  TH2F *eEB_eta_phi_leadingTower = (TH2F*)f.Get("eEB_eta_phi_leadingTowerData");
  TH2F *eEE_eta_phi_leadingTower = (TH2F*)f.Get("eEE_eta_phi_leadingTowerData");
  TH2F *eHB_eta_phi_leadingTower = (TH2F*)f.Get("eHB_eta_phi_leadingTowerData");
  TH2F *eHE_eta_phi_leadingTower = (TH2F*)f.Get("eHE_eta_phi_leadingTowerData");
  TH2F *eHF_eta_phi_leadingTower = (TH2F*)f.Get("eHF_eta_phi_leadingTowerData");

  // index version
  TH2F *eEB_ieta_leadingTower = (TH2F*)f.Get("eEB_ieta_leadingTowerData");
  TH2F *eEE_ieta_leadingTower = (TH2F*)f.Get("eEE_ieta_leadingTowerData");
  TH2F *eHB_ieta_leadingTower = (TH2F*)f.Get("eHB_ieta_leadingTowerData");
  TH2F *eHE_ieta_leadingTower = (TH2F*)f.Get("eHE_ieta_leadingTowerData");
  TH2F *eHF_ieta_leadingTower = (TH2F*)f.Get("eHF_ieta_leadingTowerData");
 
  TH2F *eEB_ieta_iphi_leadingTower = (TH2F*)f.Get("eEB_ieta_iphi_leadingTowerData");
  TH2F *eEE_ieta_iphi_leadingTower = (TH2F*)f.Get("eEE_ieta_iphi_leadingTowerData");
  TH2F *eHB_ieta_iphi_leadingTower = (TH2F*)f.Get("eHB_ieta_iphi_leadingTowerData");
  TH2F *eHE_ieta_iphi_leadingTower = (TH2F*)f.Get("eHE_ieta_iphi_leadingTowerData");
  TH2F *eHF_ieta_iphi_leadingTower = (TH2F*)f.Get("eHF_ieta_iphi_leadingTowerData");


  TCanvas* c1 = new TCanvas();

  //////////////////////
  // Set axis labels //
  /////////////////////

  eEB->GetXaxis()->SetTitle("E [GeV]");
  eEB->GetYaxis()->SetTitle("Entries");

  eEE->GetXaxis()->SetTitle("E [GeV]");
  eEE->GetYaxis()->SetTitle("Entries");

  eHB->GetXaxis()->SetTitle("E [GeV]");
  eHB->GetYaxis()->SetTitle("Entries");

  eHE->GetXaxis()->SetTitle("E [GeV]");
  eHE->GetYaxis()->SetTitle("Entries");

  eHFp->GetXaxis()->SetTitle("E [GeV]");
  eHFp->GetYaxis()->SetTitle("Entries");

  eHFm->GetXaxis()->SetTitle("E [GeV]");
  eHFm->GetYaxis()->SetTitle("Entries");


  eEB_eta->GetXaxis()->SetTitle("#eta");
  eEB_eta->GetYaxis()->SetTitle("E [GeV]");

  eEE_eta->GetXaxis()->SetTitle("#eta");
  eEE_eta->GetYaxis()->SetTitle("E [GeV]");

  eHB_eta->GetXaxis()->SetTitle("#eta");
  eHB_eta->GetYaxis()->SetTitle("E [GeV]");

  eHE_eta->GetXaxis()->SetTitle("#eta");
  eHE_eta->GetYaxis()->SetTitle("E [GeV]");

  eHF_eta->GetXaxis()->SetTitle("#eta");
  eHF_eta->GetYaxis()->SetTitle("E [GeV]");


  eEB_eta_phi->GetXaxis()->SetTitle("#eta");
  eEB_eta_phi->GetYaxis()->SetTitle("#phi");

  eEE_eta_phi->GetXaxis()->SetTitle("#eta");
  eEE_eta_phi->GetYaxis()->SetTitle("#phi");

  eHB_eta_phi->GetXaxis()->SetTitle("#eta");
  eHB_eta_phi->GetYaxis()->SetTitle("#phi");

  eHE_eta_phi->GetXaxis()->SetTitle("#eta");
  eHE_eta_phi->GetYaxis()->SetTitle("#phi");

  eHF_eta_phi->GetXaxis()->SetTitle("#eta");
  eHF_eta_phi->GetYaxis()->SetTitle("#phi");

  // Index versions
  
  eEB_ieta->GetXaxis()->SetTitle("i#eta");
  eEB_ieta->GetYaxis()->SetTitle("E [GeV]");

  eEE_ieta->GetXaxis()->SetTitle("i#eta");
  eEE_ieta->GetYaxis()->SetTitle("E [GeV]");

  eHB_ieta->GetXaxis()->SetTitle("i#eta");
  eHB_ieta->GetYaxis()->SetTitle("E [GeV]");

  eHE_ieta->GetXaxis()->SetTitle("i#eta");
  eHE_ieta->GetYaxis()->SetTitle("E [GeV]");

  eHF_ieta->GetXaxis()->SetTitle("i#eta");
  eHF_ieta->GetYaxis()->SetTitle("E [GeV]");


  eEB_ieta_iphi->GetXaxis()->SetTitle("i#eta");
  eEB_ieta_iphi->GetYaxis()->SetTitle("i#phi");

  eEE_ieta_iphi->GetXaxis()->SetTitle("i#eta");
  eEE_ieta_iphi->GetYaxis()->SetTitle("i#phi");

  eHB_ieta_iphi->GetXaxis()->SetTitle("i#eta");
  eHB_ieta_iphi->GetYaxis()->SetTitle("i#phi");

  eHE_ieta_iphi->GetXaxis()->SetTitle("i#eta");
  eHE_ieta_iphi->GetYaxis()->SetTitle("i#phi");

  eHF_ieta_iphi->GetXaxis()->SetTitle("i#eta");
  eHF_ieta_iphi->GetYaxis()->SetTitle("i#phi");

  /////////////////////
  
  eEB_leadingTower->GetXaxis()->SetTitle("Leading tower E[GeV]");
  eEB_leadingTower->GetYaxis()->SetTitle("Entries");

  eEE_leadingTower->GetXaxis()->SetTitle("Leading tower E[GeV]");
  eEE_leadingTower->GetYaxis()->SetTitle("Entries");

  eHB_leadingTower->GetXaxis()->SetTitle("Leading tower E[GeV]");
  eHB_leadingTower->GetYaxis()->SetTitle("Entries");

  eHE_leadingTower->GetXaxis()->SetTitle("Leading tower E[GeV]");
  eHE_leadingTower->GetYaxis()->SetTitle("Entries");

  eHFp_leadingTower->GetXaxis()->SetTitle("Leading tower E[GeV]");
  eHFp_leadingTower->GetYaxis()->SetTitle("Entries");

  eHFm_leadingTower->GetXaxis()->SetTitle("Leading tower E[GeV]");
  eHFm_leadingTower->GetYaxis()->SetTitle("Entries");


  eEB_eta_leadingTower->GetXaxis()->SetTitle("Leading tower #eta");
  eEB_eta_leadingTower->GetYaxis()->SetTitle("Leading tower E[GeV]");

  eEE_eta_leadingTower->GetXaxis()->SetTitle("Leading tower #eta");
  eEE_eta_leadingTower->GetYaxis()->SetTitle("Leading tower E[GeV]");

  eHB_eta_leadingTower->GetXaxis()->SetTitle("Leading tower #eta");
  eHB_eta_leadingTower->GetYaxis()->SetTitle("Leading tower E[GeV]");

  eHE_eta_leadingTower->GetXaxis()->SetTitle("Leading tower #eta");
  eHE_eta_leadingTower->GetYaxis()->SetTitle("Leading tower E[GeV]");

  eHF_eta_leadingTower->GetXaxis()->SetTitle("Leading tower #eta");
  eHF_eta_leadingTower->GetYaxis()->SetTitle("Leading tower E[GeV]");


  eEB_eta_phi_leadingTower->GetXaxis()->SetTitle("Leading tower #eta");
  eEB_eta_phi_leadingTower->GetYaxis()->SetTitle("Leading tower #phi");

  eEE_eta_phi_leadingTower->GetXaxis()->SetTitle("Leading tower #eta");
  eEE_eta_phi_leadingTower->GetYaxis()->SetTitle("Leading tower #phi");

  eHB_eta_phi_leadingTower->GetXaxis()->SetTitle("Leading tower #eta");
  eHB_eta_phi_leadingTower->GetYaxis()->SetTitle("Leading tower #phi");

  eHE_eta_phi_leadingTower->GetXaxis()->SetTitle("Leading tower #eta");
  eHE_eta_phi_leadingTower->GetYaxis()->SetTitle("Leading tower #phi");

  eHF_eta_phi_leadingTower->GetXaxis()->SetTitle("Leading tower #eta");
  eHF_eta_phi_leadingTower->GetYaxis()->SetTitle("Leading tower #phi");

  // index versions
  eEB_ieta_leadingTower->GetXaxis()->SetTitle("Leading tower i#eta");
  eEB_ieta_leadingTower->GetYaxis()->SetTitle("Leading tower E[GeV]");

  eEE_ieta_leadingTower->GetXaxis()->SetTitle("Leading tower i#eta");
  eEE_ieta_leadingTower->GetYaxis()->SetTitle("Leading tower E[GeV]");

  eHB_ieta_leadingTower->GetXaxis()->SetTitle("Leading tower i#eta");
  eHB_ieta_leadingTower->GetYaxis()->SetTitle("Leading tower E[GeV]");

  eHE_ieta_leadingTower->GetXaxis()->SetTitle("Leading tower i#eta");
  eHE_ieta_leadingTower->GetYaxis()->SetTitle("Leading tower E[GeV]");

  eHF_ieta_leadingTower->GetXaxis()->SetTitle("Leading tower i#eta");
  eHF_ieta_leadingTower->GetYaxis()->SetTitle("Leading tower E[GeV]");


  eEB_ieta_iphi_leadingTower->GetXaxis()->SetTitle("Leading tower i#eta");
  eEB_ieta_iphi_leadingTower->GetYaxis()->SetTitle("Leading tower i#phi");

  eEE_ieta_iphi_leadingTower->GetXaxis()->SetTitle("Leading tower i#eta");
  eEE_ieta_iphi_leadingTower->GetYaxis()->SetTitle("Leading tower i#phi");

  eHB_ieta_iphi_leadingTower->GetXaxis()->SetTitle("Leading tower i#eta");
  eHB_ieta_iphi_leadingTower->GetYaxis()->SetTitle("Leading tower i#phi");

  eHE_ieta_iphi_leadingTower->GetXaxis()->SetTitle("Leading tower i#eta");
  eHE_ieta_iphi_leadingTower->GetYaxis()->SetTitle("Leading tower i#phi");

  eHF_ieta_iphi_leadingTower->GetXaxis()->SetTitle("Leading tower i#eta");
  eHF_ieta_iphi_leadingTower->GetYaxis()->SetTitle("Leading tower i#phi");

  /////////////////////

  // Scale plots
  eEB->Scale(1.0/eEB->Integral());
  eEE->Scale(1.0/eEE->Integral());
  eHB->Scale(1.0/eHB->Integral());
  eHE->Scale(1.0/eHE->Integral());
  eHFp->Scale(1.0/eHFp->Integral());
  eHFm->Scale(1.0/eHFm->Integral());
 
  eEB_leadingTower->Scale(1.0/eEB_leadingTower->Integral());
  eEE_leadingTower->Scale(1.0/eEE_leadingTower->Integral());
  eHB_leadingTower->Scale(1.0/eHB_leadingTower->Integral());
  eHE_leadingTower->Scale(1.0/eHE_leadingTower->Integral());
  eHFp_leadingTower->Scale(1.0/eHFp_leadingTower->Integral());
  eHFm_leadingTower->Scale(1.0/eHFm_leadingTower->Integral());

  
  eEB_lbl->Scale(1.0/eEB_lbl->Integral());
  eEE_lbl->Scale(1.0/eEE_lbl->Integral());
  eHB_lbl->Scale(1.0/eHB_lbl->Integral());
  eHE_lbl->Scale(1.0/eHE_lbl->Integral());
  eHFp_lbl->Scale(1.0/eHFp_lbl->Integral());
  eHFm_lbl->Scale(1.0/eHFm_lbl->Integral());
 
  eEB_leadingTower_lbl->Scale(1.0/eEB_leadingTower_lbl->Integral());
  eEE_leadingTower_lbl->Scale(1.0/eEE_leadingTower_lbl->Integral());
  eHB_leadingTower_lbl->Scale(1.0/eHB_leadingTower_lbl->Integral());
  eHE_leadingTower_lbl->Scale(1.0/eHE_leadingTower_lbl->Integral());
  eHFp_leadingTower_lbl->Scale(1.0/eHFp_leadingTower_lbl->Integral());
  eHFm_leadingTower_lbl->Scale(1.0/eHFm_leadingTower_lbl->Integral());
 

  // Set LbL plot line colors
 
  eEB_lbl->SetLineColor(2);
  eEE_lbl->SetLineColor(2);
  eHB_lbl->SetLineColor(2);
  eHE_lbl->SetLineColor(2);
  eHFp_lbl->SetLineColor(2);
  eHFm_lbl->SetLineColor(2);

  eEB_leadingTower_lbl->SetLineColor(2);
  eEE_leadingTower_lbl->SetLineColor(2);
  eHB_leadingTower_lbl->SetLineColor(2);
  eHE_leadingTower_lbl->SetLineColor(2);
  eHFp_leadingTower_lbl->SetLineColor(2);
  eHFm_leadingTower_lbl->SetLineColor(2);


  /////////////////////
  c1->SetLogz();

  eEB->Draw("hist e");
  eEB_lbl->Draw("hist e same");
  c1->SaveAs("caloPlots_lbl/allTower/eEB.png");

  eEE->Draw("hist e");
  eEE_lbl->Draw("hist e same");
  c1->SaveAs("caloPlots_lbl/allTower/eEE.png");
  
  eHB->Draw("hist e");
  eHB_lbl->Draw("hist e same");
  c1->SaveAs("caloPlots_lbl/allTower/eHB.png");
  
  eHE->Draw("hist e");
  eHE_lbl->Draw("hist e same");
  c1->SaveAs("caloPlots_lbl/allTower/eHE.png");
  
  eHFp->Draw("hist e");
  eHFp_lbl->Draw("hist e same");
  c1->SaveAs("caloPlots_lbl/allTower/eHFp.png");
  
  eHFm->Draw("hist e");
  eHFm_lbl->Draw("hist e same");
  c1->SaveAs("caloPlots_lbl/allTower/eHFm.png");

  eEB_eta->Draw("colz");
  c1->SaveAs("caloPlots_lbl/allTower/eEB_eta.png");

  eEE_eta->Draw("colz");
  c1->SaveAs("caloPlots_lbl/allTower/eEE_eta.png");
  
  eHB_eta->Draw("colz");
  c1->SaveAs("caloPlots_lbl/allTower/eHB_eta.png");
  
  eHE_eta->Draw("colz");
  c1->SaveAs("caloPlots_lbl/allTower/eHE_eta.png");
  
  eHF_eta->Draw("colz");
  c1->SaveAs("caloPlots_lbl/allTower/eHF_eta.png");
  

  eEB_eta_phi->Draw("colz");
  c1->SaveAs("caloPlots_lbl/allTower/eEB_eta_phi.png");

  eEE_eta_phi->Draw("colz");
  c1->SaveAs("caloPlots_lbl/allTower/eEE_eta_phi.png");
  
  eHB_eta_phi->Draw("colz");
  c1->SaveAs("caloPlots_lbl/allTower/eHB_eta_phi.png");
  
  eHE_eta_phi->Draw("colz");
  c1->SaveAs("caloPlots_lbl/allTower/eHE_eta_phi.png");
  
  eHF_eta_phi->Draw("colz");
  c1->SaveAs("caloPlots_lbl/allTower/eHF_eta_phi.png");

  // index version
  eEB_ieta->Draw("colz");
  c1->SaveAs("caloPlots_lbl/allTower_index/eEB_ieta.png");

  eEE_ieta->Draw("colz");
  c1->SaveAs("caloPlots_lbl/allTower_index/eEE_ieta.png");
  
  eHB_ieta->Draw("colz");
  c1->SaveAs("caloPlots_lbl/allTower_index/eHB_ieta.png");
  
  eHE_ieta->Draw("colz");
  c1->SaveAs("caloPlots_lbl/allTower_index/eHE_ieta.png");
  
  eHF_ieta->Draw("colz");
  c1->SaveAs("caloPlots_lbl/allTower_index/eHF_ieta.png");
  

  eEB_ieta_iphi->Draw("colz");
  c1->SaveAs("caloPlots_lbl/allTower_index/eEB_ieta_iphi.png");

  eEE_ieta_iphi->Draw("colz");
  c1->SaveAs("caloPlots_lbl/allTower_index/eEE_ieta_iphi.png");
  
  eHB_ieta_iphi->Draw("colz");
  c1->SaveAs("caloPlots_lbl/allTower_index/eHB_ieta_iphi.png");
  
  eHE_ieta_iphi->Draw("colz");
  c1->SaveAs("caloPlots_lbl/allTower_index/eHE_ieta_iphi.png");
  
  eHF_ieta_iphi->Draw("colz");
  c1->SaveAs("caloPlots_lbl/allTower_index/eHF_ieta_iphi.png");
  

  // Leading tower plots
  eEB_leadingTower->Draw("hist e");
  eEB_leadingTower_lbl->Draw("hist e same");
  c1->SaveAs("caloPlots_lbl/leadingTower/eEB_leadingTower.png");

  eEE_leadingTower->Draw("hist e");
  eEE_leadingTower_lbl->Draw("hist e same");
  c1->SaveAs("caloPlots_lbl/leadingTower/eEE_leadingTower.png");
  
  eHB_leadingTower->Draw("hist e");
  eHB_leadingTower_lbl->Draw("hist e same");
  c1->SaveAs("caloPlots_lbl/leadingTower/eHB_leadingTower.png");
  
  eHE_leadingTower->Draw("hist e");
  eHE_leadingTower_lbl->Draw("hist e same");
  c1->SaveAs("caloPlots_lbl/leadingTower/eHE_leadingTower.png");
  
  eHFp_leadingTower->Draw("hist e");
  eHFp_leadingTower_lbl->Draw("hist e same");
  c1->SaveAs("caloPlots_lbl/leadingTower/eHFp_leadingTower.png");
  
  eHFm_leadingTower->Draw("hist e");
  eHFm_leadingTower_lbl->Draw("hist e same");
  c1->SaveAs("caloPlots_lbl/leadingTower/eHFm_leadingTower.png");


  eEB_eta_leadingTower->Draw("colz");
  c1->SaveAs("caloPlots_lbl/leadingTower/eEB_eta_leadingTower.png");

  eEE_eta_leadingTower->Draw("colz");
  c1->SaveAs("caloPlots_lbl/leadingTower/eEE_eta_leadingTower.png");
  
  eHB_eta_leadingTower->Draw("colz");
  c1->SaveAs("caloPlots_lbl/leadingTower/eHB_eta_leadingTower.png");
  
  eHE_eta_leadingTower->Draw("colz");
  c1->SaveAs("caloPlots_lbl/leadingTower/eHE_eta_leadingTower.png");
  
  eHF_eta_leadingTower->Draw("colz");
  c1->SaveAs("caloPlots_lbl/leadingTower/eHF_eta_leadingTower.png");


  eEB_eta_phi_leadingTower->Draw("colz");
  c1->SaveAs("caloPlots_lbl/leadingTower/eEB_eta_phi_leadingTower.png");

  eEE_eta_phi_leadingTower->Draw("colz");
  c1->SaveAs("caloPlots_lbl/leadingTower/eEE_eta_phi_leadingTower.png");
  
  eHB_eta_phi_leadingTower->Draw("colz");
  c1->SaveAs("caloPlots_lbl/leadingTower/eHB_eta_phi_leadingTower.png");
  
  eHE_eta_phi_leadingTower->Draw("colz");
  c1->SaveAs("caloPlots_lbl/leadingTower/eHE_eta_phi_leadingTower.png");
  
  eHF_eta_phi_leadingTower->Draw("colz");
  c1->SaveAs("caloPlots_lbl/leadingTower/eHF_eta_phi_leadingTower.png");

  // index version
  eEB_ieta_leadingTower->Draw("colz");
  c1->SaveAs("caloPlots_lbl/leadingTower_index/eEB_ieta_leadingTower.png");

  eEE_ieta_leadingTower->Draw("colz");
  c1->SaveAs("caloPlots_lbl/leadingTower_index/eEE_ieta_leadingTower.png");
  
  eHB_ieta_leadingTower->Draw("colz");
  c1->SaveAs("caloPlots_lbl/leadingTower_index/eHB_ieta_leadingTower.png");
  
  eHE_ieta_leadingTower->Draw("colz");
  c1->SaveAs("caloPlots_lbl/leadingTower_index/eHE_ieta_leadingTower.png");
  
  eHF_ieta_leadingTower->Draw("colz");
  c1->SaveAs("caloPlots_lbl/leadingTower_index/eHF_ieta_leadingTower.png");


  eEB_ieta_iphi_leadingTower->Draw("colz");
  c1->SaveAs("caloPlots_lbl/leadingTower_index/eEB_ieta_iphi_leadingTower.png");

  eEE_ieta_iphi_leadingTower->Draw("colz");
  c1->SaveAs("caloPlots_lbl/leadingTower_index/eEE_ieta_iphi_leadingTower.png");
  
  eHB_ieta_iphi_leadingTower->Draw("colz");
  c1->SaveAs("caloPlots_lbl/leadingTower_index/eHB_ieta_iphi_leadingTower.png");
  
  eHE_ieta_iphi_leadingTower->Draw("colz");
  c1->SaveAs("caloPlots_lbl/leadingTower_index/eHE_ieta_iphi_leadingTower.png");
  
  eHF_ieta_iphi_leadingTower->Draw("colz");
  c1->SaveAs("caloPlots_lbl/leadingTower_index/eHF_ieta_iphi_leadingTower.png");


}
