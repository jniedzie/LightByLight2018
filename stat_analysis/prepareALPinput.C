
string backgroundFilePath = "../analysis/results/basicPlots_default.root";

string outputFilePath = "input_hinvmass.root";

void prepareALPinput()
{
  TFile *backgroundFile = TFile::Open(backgroundFilePath.c_str());
  
  TH1D *observedMassHist  = (TH1D*)backgroundFile->Get("lbl_diphoton_mass_all_Data");
  TH1D *lblMassHist       = (TH1D*)backgroundFile->Get("lbl_diphoton_mass_all_LbL");
  TH1D *cepMassHist       = (TH1D*)backgroundFile->Get("lbl_diphoton_mass_all_CEP");
  TH1D *qedMassHist       = (TH1D*)backgroundFile->Get("lbl_diphoton_mass_all_QED_SC");
  
  observedMassHist->SetLineColor(kBlack);
  lblMassHist->SetLineColor(kRed);
  cepMassHist->SetLineColor(kGreen);
  qedMassHist->SetLineColor(kBlue);
  
  
  observedMassHist->Draw();
  lblMassHist->Draw("same");
  cepMassHist->Draw("same");
  qedMassHist->Draw("same");
 
  
  
  TFile *outputFile = new TFile(outputFilePath.c_str(), "recreate");
  outputFile->cd();
  
  observedMassHist->SetName("data_obs");
  observedMassHist->Write();
  
  lblMassHist->SetName("lbyl");
  lblMassHist->Write();
  
  cepMassHist->SetName("cep");
  cepMassHist->Write();
  
  qedMassHist->SetName("qed");
  qedMassHist->Write();
  
  outputFile->Close();
  
}
