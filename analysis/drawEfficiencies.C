void drawEfficiencies()
{
  TFile *inFile = TFile::Open("results/efficiencies.root");
  
  // Reco+ID efficiency
  TH1D *recoIdEff = (TH1D*)inFile->Get("reco_id_eff");
  
  recoIdEff->SetLineColor(kViolet+2);
  recoIdEff->SetTitle("");
  recoIdEff->GetXaxis()->SetTitle("Photon E_{T} (GeV)");
  recoIdEff->GetXaxis()->SetTitleSize(0.05);
  recoIdEff->GetYaxis()->SetTitle("Eff^{reco+ID}_{MC-driven}");
  recoIdEff->GetYaxis()->SetTitleSize(0.05);
  
  TCanvas *recoIdEffCanvas = new TCanvas("reco_id_eff", "reco_id_eff", 640, 480);
  recoIdEffCanvas->cd();
  
  gStyle->SetOptStat(0);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.12);
  recoIdEff->Draw();
  recoIdEffCanvas->SaveAs("plots/reco_id_eff.pdf");
  
  
  
  // Trigger efficiency
  TH1D *triggerEff = (TH1D*)inFile->Get("trigger_eff");
  TH1D *triggerSingleEff = (TH1D*)inFile->Get("trigger_single_eff");
  TH1D *triggerDoubleEff = (TH1D*)inFile->Get("trigger_double_eff");
  
  triggerEff->SetLineColor(kViolet+2);
  triggerEff->SetTitle("");
  triggerEff->GetXaxis()->SetTitle("Diphoton m_{inv} (GeV)");
  triggerEff->GetXaxis()->SetTitleSize(0.05);
  triggerEff->GetYaxis()->SetTitle("Eff^{trigger}_{MC-driven}");
  triggerEff->GetYaxis()->SetTitleSize(0.05);
  
  triggerSingleEff->SetLineColor(kGreen+2);
  triggerDoubleEff->SetLineColor(kBlue+2);
  
  TCanvas *triggerEffCanvas = new TCanvas("trigger_eff", "trigger_eff", 640, 480);
  triggerEffCanvas->cd();
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
  
  triggerEffCanvas->SaveAs("plots/trigger_eff.pdf");
  
}
