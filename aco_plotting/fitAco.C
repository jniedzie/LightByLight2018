//string inputFileName = "diphoton_histos_allSfsApplied.root";
string inputFileName = "diphoton_histos.root";

TFile *inputFile;
TH1D *lblHist, *qedHist, *cepHist, *dataHist, *qedFsr1photonHists, *qedFsr2photonHists;

void loadHistograms()
{
  inputFile = TFile::Open(inputFileName.c_str());
  
//  dataHist = (TH1D*)inputFile->Get("hacoplanarity_data");
  dataHist = (TH1D*)inputFile->Get("hAcoplanaritydata");
  
//  lblHist = (TH1D*)inputFile->Get("hacoplanarity_lbyl_stack_3");
  lblHist = (TH1D*)inputFile->Get("hAcoplanarityLbyL");
  
//  qedHist = (TH1D*)inputFile->Get("hacoplanarity_qed_stack_1");
//  qedHist = (TH1D*)inputFile->Get("hAcoplanarityQEDSCFSR");
  
  qedHist = (TH1D*)inputFile->Get("hAcoplanarityQEDSC");
//  qedHist = (TH1D*)inputFile->Get("hAcoplanarityQEDSL");
  qedFsr1photonHists = (TH1D*)inputFile->Get("hAcoplanarityQEDMG5-FSROnePhoton");
  qedFsr2photonHists = (TH1D*)inputFile->Get("hAcoplanarityQEDMG5-FSRTwoPhoton");
  
//  cepHist = (TH1D*)inputFile->Get("hacoplanarity_cep_stack_2");
  cepHist = (TH1D*)inputFile->Get("hAcoplanarityCEP");
}

Double_t histFitFunction(Double_t *x, Double_t *par){
  double value = 0;
  value += par[0] * qedHist->GetBinContent(qedHist->GetXaxis()->FindFixBin(x[0]));
  value += par[1] * cepHist->GetBinContent(cepHist->GetXaxis()->FindFixBin(x[0]));
  value += par[2] * lblHist->GetBinContent(lblHist->GetXaxis()->FindFixBin(x[0]));
  value += par[3] * qedFsr1photonHists->GetBinContent(qedFsr1photonHists->GetXaxis()->FindFixBin(x[0]));
  value += par[4] * qedFsr2photonHists->GetBinContent(qedFsr2photonHists->GetXaxis()->FindFixBin(x[0]));
  return value;
}

TF1* getFittedFunction()
{
  auto fitFunction = new TF1("fit", histFitFunction, 0, 0.1, 5);
  fitFunction->SetParameters(1, 1, 1);
  
  fitFunction->FixParameter(0, 1); // QED
//  fitFunction->FixParameter(1, 1); // CEP
  fitFunction->FixParameter(2, 1); // LbL
  fitFunction->FixParameter(3, 1); // 1 photon
  fitFunction->FixParameter(4, 1); // 2 photons
  
//  fitFunction->SetParLimits(0, 0.8, 2); // QED
  fitFunction->SetParLimits(1, 0.1, 1000); // CEP
//  fitFunction->SetParLimits(2, 0.8, 1.2); // LbL
//  fitFunction->SetParLimits(3, 0.8, 2); // QCD FSR 1 photon
//  fitFunction->SetParLimits(4, 0.8, 2); // QCD FSR 2 photons
  
  fitFunction->SetParNames ("QED", "CEP", "LbL", "QED FSR 1", "QED FSR 2");
  dataHist->Fit(fitFunction, "0");
  
  cout<<"chi2: "<<fitFunction->GetChisquare()/(dataHist->GetNbinsX()+1)<<endl;
  
  return fitFunction;
}

string getLabel(TF1* fun, string name)
{
  char label[100];
  snprintf(label, sizeof(label), "%s (scale: %.2f)", name.c_str(), fun->GetParameter(name.c_str()));
  return string(label);
}

void fitAco()
{
  loadHistograms();
  auto fitFunction = getFittedFunction();
  
//  Scale histograms according to the best fit
  cepHist->Scale(fitFunction->GetParameter("CEP"));
  qedHist->Scale(fitFunction->GetParameter("QED"));
  lblHist->Scale(fitFunction->GetParameter("LbL"));
  qedFsr1photonHists->Scale(fitFunction->GetParameter("QED FSR 1"));
  qedFsr2photonHists->Scale(fitFunction->GetParameter("QED FSR 2"));
  
//  Plot results
  auto canvas = new TCanvas("canvas", "canvas", 1280, 1000);
  canvas->cd();
  auto stack = new THStack();
  stack->Add(cepHist);
  stack->Add(qedHist);
  stack->Add(lblHist);
  stack->Add(qedFsr1photonHists);
  stack->Add(qedFsr2photonHists);
  stack->Draw("Fhist");
  stack->SetMaximum(25);
  stack->GetXaxis()->SetTitle("Aco_{#gamma#gamma}");
  dataHist->Draw("same");
  
  auto legend = new TLegend(0.5, 0.7, 0.9, 0.9);
  legend->AddEntry(dataHist, "data", "pel");
  legend->AddEntry(qedHist, getLabel(fitFunction, "QED").c_str(), "f");
  legend->AddEntry(cepHist, getLabel(fitFunction, "CEP").c_str(), "f");
  legend->AddEntry(lblHist, getLabel(fitFunction, "LbL").c_str(), "f");
  legend->AddEntry(qedFsr1photonHists, getLabel(fitFunction, "QED FSR 1").c_str(), "f");
  legend->AddEntry(qedFsr2photonHists, getLabel(fitFunction, "QED FSR 2").c_str(), "f");
  
  legend->Draw();
  canvas->SaveAs("diphoton_aco_fitted.pdf");
  
// Print results
  double signalEntries = lblHist->GetBinContent(1)+lblHist->GetBinContent(2);
  double backgroundEntries = qedHist->GetBinContent(1)+qedHist->GetBinContent(2)
                            +cepHist->GetBinContent(1)+cepHist->GetBinContent(2)
                            +qedFsr1photonHists->GetBinContent(1)+qedFsr1photonHists->GetBinContent(2);
                            +qedFsr2photonHists->GetBinContent(1)+qedFsr2photonHists->GetBinContent(2);
  
  cout<<"N signal events < 0.01: "<<signalEntries<<endl;
  cout<<"N background events < 0.01: "<<backgroundEntries<<endl;
  cout<<"Z: "<<signalEntries/sqrt(signalEntries+backgroundEntries)<<endl;
  
}

