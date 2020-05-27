string inputFileName = "input_hacoplanarity.root";
string outputPath = "datacards/datacard_acoplanarity.txt";

void addHeaderToFile(ofstream &file, int observedRate)
{
  file<<"# Simple counting experiment, with one signal and a few background processes"<<endl;
  file<<"# Simplified version of LHC lbyl counts"<<endl;
  file<<"imax 1  number of channels"<<endl;
  file<<"jmax 2  number of backgrounds"<<endl;
  file<<"kmax 3  number of nuisance parameters (sources of systematical uncertainties)"<<endl;
  file<<"------------"<<endl;
  file<<"shapes * * "<<inputFileName<<"  $PROCESS $PROCESS_$SYSTEMATIC"<<endl;
  file<<"------------"<<endl;
  file<<"# we have just one channel, in which we observe X events"<<endl;
  file<<"bin bin1"<<endl;
  file<<"observation "<<observedRate<<endl;
  file<<"------------"<<endl;
  file<<"# now we list the expected events for signal and all backgrounds in that bin"<<endl;
  file<<"# the second 'process' line must have a positive number for backgrounds, and 0 for signal"<<endl;
  file<<"# then we list the independent sources of uncertainties, and give their effect (syst. error)"<<endl;
  file<<"# on each process and bin"<<endl;
  file<<"bin            bin1  bin1 bin1"<<endl;
  file<<"process        lbyl  cep  qed"<<endl;
  file<<"process        0      1     2"<<endl;
}

void addRatesToFile(ofstream &file, double lblRate, double cepRate, double qedRate)
{
  file<<"rate           "<<" "<<lblRate<<" "<<cepRate<<" "<<qedRate<<""<<endl;
}

void addNuisancesToFile(ofstream &file)
{
  file<<"------------"<<endl;
  file<<"sig_syst     lnN    1.23  -   -    exp systs: efficiency, purity..."<<endl;
  file<<"TH_signal    lnN    1.10  -   -    TH xsec"<<endl;
  file<<"# TH_qed_mc    lnN     -      -     1.21  QED MC stats: 21%"<<endl;
  file<<"# TH_cep_mc    lnN     -    1.08   -      CEP MC stats: 8%"<<endl;
  file<<"# TH_cep_norm  lnN     -    1.34   -      CEP data-driven norm: 34%"<<endl;
  file<<"TH_cep_norm  lnN     -    100000000   -      CEP data-driven norm: inf%"<<endl;
  file<<"bin1   autoMCStats  10000"<<endl;
}

void generateDatacardsSignificance()
{
  TFile *inFile       = TFile::Open(inputFileName.c_str());
  TH1D *observedHist  = (TH1D*)inFile->Get("data_obs");
  TH1D *lblHist       = (TH1D*)inFile->Get("lbyl");
  TH1D *cepHist       = (TH1D*)inFile->Get("cep");
  TH1D *qedHist       = (TH1D*)inFile->Get("qed");
  
  double observedRate=0, lblRate=0, cepRate=0, qedRate=0;
  
  for(int i=1; i<=observedHist->GetNbinsX(); i++) observedRate += observedHist->GetBinContent(i);
  for(int i=1; i<=lblHist->GetNbinsX(); i++)      lblRate += lblHist->GetBinContent(i);
  for(int i=1; i<=cepHist->GetNbinsX(); i++)      cepRate += cepHist->GetBinContent(i);
  for(int i=1; i<=qedHist->GetNbinsX(); i++)      qedRate += qedHist->GetBinContent(i);
  
  ofstream outfile(outputPath);
  
  addHeaderToFile(outfile, observedRate);
  addRatesToFile(outfile, lblRate, cepRate, qedRate);
  addNuisancesToFile(outfile);
  
  outfile.close();
  
  
}
