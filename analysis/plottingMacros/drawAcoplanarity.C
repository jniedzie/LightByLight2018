
string inputPath  = "../results/acoplanarity.root";
string outputPath = "../plots/acoplanarity.pdf";

void prepareHist(TH1D *hist, int color)
{
  hist->SetLineColor(color);
  hist->SetFillColorAlpha(color, 0.2);
  
  hist->Scale(1./hist->GetEntries());
  hist->Sumw2(false);
}

void drawAcoplanarity()
{
  TFile *inFile = TFile::Open(inputPath.c_str());
  
  TCanvas *canvas = new TCanvas("Shower shape", "Shower shape", 800, 500);
  
  gStyle->SetOptStat(0);
  TLegend *legend = new TLegend(0.6, 0.6, 0.9, 0.9 );
  
  auto acoplanarityHistLbL = (TH1D*)inFile->Get("acoplanarityLbL");
  auto acoplanarityHistQED = (TH1D*)inFile->Get("acoplanarityQED");
  auto acoplanarityHistCEP = (TH1D*)inFile->Get("acoplanarityCEP");
  auto dataGraph           = (TH1D*)inFile->Get("acoplanarityData");
  
  legend->AddEntry(dataGraph, "Data", "elp");
  legend->AddEntry(acoplanarityHistLbL, "LbL MC", "f");
  legend->AddEntry(acoplanarityHistQED, "QED SC MC", "f");
  legend->AddEntry(acoplanarityHistCEP, "CEP MC", "f");
  
  prepareHist(acoplanarityHistLbL, kBlack);
  prepareHist(acoplanarityHistQED, kBlue);
  prepareHist(acoplanarityHistCEP, kRed);
  prepareHist(dataGraph, kOrange+2);
  
  dataGraph->SetMarkerStyle(21);
  dataGraph->SetLineColor(kOrange+3);
  dataGraph->SetMarkerColor(kOrange+2);
  dataGraph->SetMarkerSize(1);
  
  THStack *backgroundsStack = new THStack();
  backgroundsStack->Add(acoplanarityHistQED);
  backgroundsStack->Add(acoplanarityHistCEP);
  backgroundsStack->Add(acoplanarityHistLbL);
  
  canvas->cd(1);
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);
  
  backgroundsStack->Draw();
  backgroundsStack->GetXaxis()->SetRangeUser(0, 0.2);
  backgroundsStack->SetTitle("");
  backgroundsStack->GetYaxis()->SetTitle("# events");
  backgroundsStack->GetYaxis()->SetTitleSize(0.06);
  backgroundsStack->GetXaxis()->SetTitle("A_{#phi}^{#gamma#gamma}");
  backgroundsStack->GetXaxis()->SetTitleSize(0.06);
  
  dataGraph->Draw("samePE");
  legend->Draw("same");
  
  canvas->SaveAs(outputPath.c_str());
}
