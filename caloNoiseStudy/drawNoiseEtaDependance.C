void drawNoiseEtaDependance(const char *inFileName)
{
  TFile *inFile = TFile::Open(inFileName);
  TH2D *noiseVsEtaEE = (TH2D*)inFile->Get("energyHistEEVsEta");
  TH2D *noiseVsEtaHF = (TH2D*)inFile->Get("energyHistHFVsEta");
  
//  TCanvas *c1 = new TCanvas("c1","c1",2880,1800);
//  c1->Divide(3,2);
  
//  c1->cd(1);
  noiseVsEtaEE->GetXaxis()->SetTitle("#eta");
  noiseVsEtaEE->DrawCopy("colz");
  
  noiseVsEtaEE->SaveAs("noise_vs_eta.pdf");

  /*
  c1->cd(2);
  noiseVsEtaHF->DrawCopy("colz");
  
//  noiseVsEtaEE->ProjectionX()->DrawCopy();
  
//  TH1D *avgNoiseVsEta = new TH1D("avgNoiseVsEta", "avgNoiseVsEta", 100, -5, 5);
//
//  for(int etaBin=1; etaBin <= noiseVsEtaEE->GetNbinsX(); etaBin++){
//    TH1D *energyDist = noiseVsEtaEE->ProjectionY("", etaBin, etaBin);
//    double avg = energyDist->GetMean();
//    avgNoiseVsEta->SetBinContent(etaBin, avg);
//  }
  
//  avgNoiseVsEta->Draw();
  
  TH2D *noiseVsAbsEtaEE = new TH2D("noiseVsAbsEtaEE", "noiseVsAbsEtaEE", 50, 0, 5, 200, 0, 20);
  TH2D *noiseVsAbsEtaHF = new TH2D("noiseVsAbsEtaHF", "noiseVsAbsEtaHF", 50, 0, 5, 200, 0, 20);
  
  for(int etaBin=1; etaBin <= noiseVsEtaEE->GetNbinsX(); etaBin++){
    double eta = noiseVsEtaEE->GetXaxis()->GetBinCenter(etaBin);
    
    for(int energyBin=1; energyBin <= noiseVsEtaEE->GetNbinsY(); energyBin++){
      double energy = noiseVsEtaEE->GetYaxis()->GetBinCenter(energyBin);
      
      double valEE = noiseVsEtaEE->GetBinContent(etaBin, energyBin);
      double valHF = noiseVsEtaHF->GetBinContent(etaBin, energyBin);

      noiseVsAbsEtaEE->Fill(fabs(eta), energy, valEE);
      noiseVsAbsEtaHF->Fill(fabs(eta), energy, valHF);
    }
  }
  
  
  
  c1->cd(3);
  noiseVsAbsEtaEE->Draw("colz");
  
  c1->cd(4);
  noiseVsAbsEtaHF->Draw("colz");
  
  
  c1->cd(5);
  TH1D *noiseEEwithCut = noiseVsEtaEE->ProjectionY("",
                                                   noiseVsEtaEE->GetXaxis()->FindFixBin(-2.6),
                                                   noiseVsEtaEE->GetXaxis()->FindFixBin(2.6));
  noiseEEwithCut->Draw();
  

  
  TH1D *avgNoiseVsEta = new TH1D("avgNoiseVsEta", "avgNoiseVsEta", 100, -5, 5);
  
  for(int etaBin=1; etaBin <= noiseVsEtaHF->GetNbinsX(); etaBin++){
    TH1D *energyDist = noiseVsEtaHF->ProjectionY("", etaBin, etaBin);
    double avg = energyDist->GetMean();
    double eta = noiseVsEtaHF->GetXaxis()->GetBinCenter(etaBin);
    avgNoiseVsEta->Fill(fabs(eta), 0.5*avg);
  }
  c1->cd(6);
  avgNoiseVsEta->Draw();
  
*/
}
