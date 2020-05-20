
string inFileName = "alp_hists.root";

void drawPlots()
{
  gStyle->SetOptStat(0);
  
  TFile *inFile = TFile::Open(inFileName.c_str());
  
  TH1D *pairMass4   = (TH1D*)inFile->Get("pair_mass_eta_le_4");
  TH1D *pairMass3   = (TH1D*)inFile->Get("pair_mass_eta_le_3");
  TH1D *pairMass2p4 = (TH1D*)inFile->Get("pair_mass_eta_le_2p4");
  
  TCanvas *canvas = new TCanvas("hists", "hists", 800, 600);
  canvas->Divide(1,1);
  
  TLegend *legend = new TLegend(0.6, 0.7, 0.9, 0.9);
  legend->AddEntry(pairMass4    , "|#eta| < 4.0", "l");
  legend->AddEntry(pairMass3    , "|#eta| < 3.0", "l");
  legend->AddEntry(pairMass2p4  , "|#eta| < 2.4", "l");
  
  canvas->cd(1);
  
  pairMass4->SetTitle("Pair mass");
  pairMass4->SetLineColor(kRed+2);
  pairMass4->GetXaxis()->SetRangeUser(0, 20);
  pairMass4->Draw();
  
  pairMass3->SetLineColor(kOrange+2);
  pairMass3->Draw("same");
  
  pairMass2p4->SetLineColor(kYellow+2);
  pairMass2p4->Draw("same");
  
  legend->Draw();
  
}
