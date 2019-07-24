void drawEfficiencies()
{
  TFile *inFile = TFile::Open("results/efficiencies.root");
  
  // Reco+ID efficiency
  TH1D *recoIdEff = (TH1D*)inFile->Get("reco_id_eff");
  
  recoIdEff->SetLineColor(kViolet+2);
  recoIdEff->SetTitle("");
  recoIdEff->GetXaxis()->SetTitle("Photon E_{T} (GeV)");
  recoIdEff->GetXaxis()->SetTitleSize(0.05);
  recoIdEff->GetYaxis()->SetTitle("Eff^{ID}_{MC}");
  recoIdEff->GetYaxis()->SetTitleSize(0.05);
  
  TCanvas *efficienciesCanvas = new TCanvas("Efficiencies", "Efficiencies", 800, 1200);
  efficienciesCanvas->Divide(2,3);
  
  efficienciesCanvas->cd(1);
  
  gStyle->SetOptStat(0);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.12);
  recoIdEff->Draw();
  
  // Trigger efficiency
  TH1D *triggerEff = (TH1D*)inFile->Get("trigger_eff");
  TH1D *triggerSingleEff = (TH1D*)inFile->Get("trigger_single_eff");
  TH1D *triggerDoubleEff = (TH1D*)inFile->Get("trigger_double_eff");
  
  triggerEff->SetLineColor(kViolet+2);
  triggerEff->SetTitle("");
  triggerEff->GetXaxis()->SetTitle("Diphoton m_{inv} (GeV)");
  triggerEff->GetXaxis()->SetTitleSize(0.05);
  triggerEff->GetYaxis()->SetTitle("Eff^{TRIG}_{MC}");
  triggerEff->GetYaxis()->SetTitleSize(0.05);
  
  triggerSingleEff->SetLineColor(kGreen+2);
  triggerDoubleEff->SetLineColor(kRed+2);
  
  efficienciesCanvas->cd(2);
  gStyle->SetOptStat(0);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.12);
  triggerEff->Draw();
  triggerSingleEff->Draw("same");
  triggerDoubleEff->Draw("same");
  
  TLegend *legTrigger = new TLegend(0.5, 0.15, 0.9, 0.5);
  legTrigger->AddEntry(triggerEff, "SingleEG3 or DoubleEG2", "le");
  legTrigger->AddEntry(triggerSingleEff, "SingleEG3 only", "le");
  legTrigger->AddEntry(triggerDoubleEff, "DoubleEG2 only", "le");
  
  legTrigger->Draw("same");
  
  
  // Charged exclusivity efficiency
  TH1D *chargedExclEff = (TH1D*)inFile->Get("charged_excl_eff");
  
  chargedExclEff->SetLineColor(kViolet+2);
  chargedExclEff->SetTitle("");
  chargedExclEff->GetXaxis()->SetTitle("Diphoton m_{inv} (GeV)");
  chargedExclEff->GetXaxis()->SetTitleSize(0.05);
  chargedExclEff->GetYaxis()->SetTitle("Eff^{CHE}_{MC}");
  chargedExclEff->GetYaxis()->SetTitleSize(0.05);
  
  efficienciesCanvas->cd(3);
  gStyle->SetOptStat(0);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.12);
  chargedExclEff->Draw();
  
  // Neutral exclusivity efficiency
  TH1D *neutralExclEff = (TH1D*)inFile->Get("neutral_excl_eff");
  
  neutralExclEff->SetLineColor(kViolet+2);
  neutralExclEff->SetTitle("");
  neutralExclEff->GetXaxis()->SetTitle("Diphoton m_{inv} (GeV)");
  neutralExclEff->GetXaxis()->SetTitleSize(0.05);
  neutralExclEff->GetYaxis()->SetTitle("Eff^{NEE}_{MC}");
  neutralExclEff->GetYaxis()->SetTitleSize(0.05);
  
  efficienciesCanvas->cd(4);
  gStyle->SetOptStat(0);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.12);
  neutralExclEff->Draw();
  
  
  
  
  
  
  
  
  
  efficienciesCanvas->SaveAs("plots/efficiencies.pdf");
  
}
