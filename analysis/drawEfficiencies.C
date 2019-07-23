void drawEfficiencies()
{
  TFile *inFile = TFile::Open("efficiencies.root");
  
  TH1D *recoIdEff = (TH1D*)inFile->Get("reco_id_eff");
  
  recoIdEff->SetLineColor(kViolet+2);
  recoIdEff->SetTitle("");
  recoIdEff->GetXaxis()->SetTitle("Photon E_{T} (GeV)");
  recoIdEff->GetXaxis()->SetTitleSize(0.05);
  recoIdEff->GetYaxis()->SetTitle("Eff^{reco+ID}_{MC-driven}");
  recoIdEff->GetYaxis()->SetTitleSize(0.05);
  
  gStyle->SetOptStat(0);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.12);
 
  TCanvas *recoIdEffCanvas = new TCanvas("reco_id_eff", "reco_id_eff", 640, 480);
  recoIdEffCanvas->cd();
  recoIdEff->Draw();
  recoIdEffCanvas->SaveAs("plots/reco_id_eff.pdf");
  
}
