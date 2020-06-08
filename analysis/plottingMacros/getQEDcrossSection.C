

string inputPath  = "../results/basicPlots_default_HEMupdate.root";

// efficiency for exclusivity, with stat and syst errors.
const double exclusivityEfficiency        = 89.5e-2;
const double exclusivityEfficiencyErrStat = 1.3e-2;
const double exclusivityEfficiencyErrSyst = 5.03e-2;
const double exclusivityEfficiencyErr     = sqrt(pow(exclusivityEfficiencyErrStat, 2) + pow(exclusivityEfficiencyErrSyst, 2));

const double xsecGenerated         = 8830;// = 1.086453e-01*20.6e3*4.82/4.73; // in mub
const double xsecGeneratedErr     = (0.15/4.82) * xsecGenerated; // FIXME what is the uncertainty?

const double luminosity     = 1609.910015010; // 391; // in mub-1
const double luminosityErr  = 0.12 * luminosity;



const double scaleFactor          = 0.98 * 0.98;//*0.931*0.928;//*1.09;
const double scaleFactorErr       = sqrt(pow(0.03,2)+pow(2*0.02,2));//+pow(0.003/0.931,2)+pow(0.020/0.928,2))*sf_ged;
const int    nEventsGenerated     = 960000;
//(int) (2399759.*(290214.+98326.)/98326.);// scale old number of events by the new+old number of reco events // was 7929199;

const double acoplanarityCut = 0.06;


const double glob_syst         = 2.*(0.02/0.98); // reco+ID


void getQEDcrossSection()
{
  TFile *inFile = TFile::Open(inputPath.c_str());
  TH1D *acoplanarityHistData  = (TH1D*)inFile->Get("qed_acoplanarity_all_Data");
  TH1D *acoplanarityHistMC    = (TH1D*)inFile->Get("qed_acoplanarity_all_QED_SC");
  
  
  
  /*
  TFile *fdata = TFile::Open("outputDataAll_noexcl.root");
  TTree *trdata = (TTree*)fdata->Get("tree");
  
  TFile *fmc = TFile::Open("outputMCAll_noexcl_OldAndNew.root");
  TTree *trmc = (TTree*) fmc->Get("tree");
  
  
  // estimate the purity in data
  TH1F *acoplanarityHistData = new TH1F("acoplanarityHistData",";Dielectron A_{#phi};Entries / (0.002)", 30, 0, acoplanarityCut);
  trdata->Project(acoplanarityHistData->GetName(),"acop",Form("doubleEG2&&acop<%f&&mass>=%f&&pt<=1",acoplanarityCut,mass_cut));
  
  
  //
  TH1D *hvari[14];
  
  
  
  string name = "acoplanarityHistMC";
  const char* var = "acop";
  
  const char* cut = Form("doubleEG2&&acop<%f&&mass>=%f&&pt<=1",acoplanarityCut,mass_cut);
  
  for(int ivar=0; ivar<14; ivar++){
    TString namei = Form("%s_%d", name, ivar);
    // namei = acoplanarityHistMC_0, acoplanarityHistMC_1...
    
    
    hvari[ivar] = new TH1D(namei, "", 30, 0, acoplanarityCut);
    
    // selection = SFweight[0]*()
    tr->Project(namei, var, Form("SFweight[%d]*(%s)", ivar, cut));
  }
  
  TH1D *acoplanarityHistMC = new TH1D(name,"", 30, 0 ,acoplanarityCut);
  
  else trmc->Project(name,var,cut);
  
  for (int i=1; i<=acoplanarityHistMC->GetNbinsX(); i++){
    double err=0;
    for(int ivar=1; ivar<14; ivar++) err += pow(hvari[ivar]->GetBinContent(i)-hvari[0]->GetBinContent(i),2);
    acoplanarityHistMC->SetBinError(i,sqrt(err+pow(acoplanarityHistMC->GetBinError(i),2)+pow(glob_syst,2)));
  }
  */
  //
  
  

  
  
  // normalize MC: force the data and MC integrals to be the same within acop<0.01
  
  double maxAcolpanarity = 0.01;
  
  int maxBin = acoplanarityHistData->FindFixBin(maxAcolpanarity);
  
  double normalizationMCerr, normalizationDataErr;
  
  double normalizationMC  = acoplanarityHistMC->IntegralAndError(1, maxBin, normalizationMCerr, "width");
  double normalizationData = acoplanarityHistData->IntegralAndError(1, maxBin, normalizationDataErr,"width");
  
  cout << "Scaling MC by " << normalizationMC << " / " << normalizationData << " = " << normalizationMC/normalizationData << endl;
  
  acoplanarityHistMC->Scale(normalizationData/normalizationMC);
  acoplanarityHistMC->SetFillColor(kYellow);
  
  
  // Fit data with double-exponential function
  TF1 *fitFunction = new TF1("fitFunction","[0]*exp(-[1]*x) + [2]*exp(-[3]*x)", 0, acoplanarityCut);
  fitFunction->SetParNames("Norm_sig","Decay_sig","Norm_bkg","Decay_bkg");
  fitFunction->SetParameters(1.5e4, 6.8e2, 2e2, 1.2e1);
  fitFunction->SetLineColor(kRed);
  
  TFitResultPtr fitResults = acoplanarityHistData->Fit(fitFunction,"ILEMS");
  
  // get total (S+B) integral
  const double *params = fitResults->GetParams();
  for(int i=0; i<4; i++) fitFunction->SetParameter(i, params[i]);
  
  double integralTotal    = fitFunction->Integral(0, maxAcolpanarity);
  double integralTotalErr = fitFunction->IntegralError(0, maxAcolpanarity, params,
                                                       fitResults->GetCovarianceMatrix().GetMatrixArray());
  
  
  // get signal integral (set background part of the fit to zero)
  double paramsNoBackground[4];
  paramsNoBackground[0] = params[0];
  paramsNoBackground[1] = params[1];
  paramsNoBackground[2] = 0;
  paramsNoBackground[3] = 0;
  for(int i=0; i<4; i++) fitFunction->SetParameter(i, paramsNoBackground[i]);
  
  double integralSignal     = fitFunction->Integral(0, maxAcolpanarity);
  double integralSignalErr  = fitFunction->IntegralError(0, maxAcolpanarity, paramsNoBackground,
                                                         fitResults->GetCovarianceMatrix().GetMatrixArray());
  
  
  cout<<"Integral signal: "<<integralSignal<<" +/- "<<integralSignalErr<<endl;
  cout<<"Integral total: " <<integralTotal <<" +/-" <<integralTotalErr <<endl;
  
  
  // get purity from the fit
  double purityFit    = integralSignal/integralTotal;
  double purityFitErr = purityFit * sqrt(  pow(integralSignalErr/integralSignal, 2)
                                         + pow(integralTotalErr/integralTotal, 2)
                                         - 2*pow(integralTotalErr, 2)/(integralSignal*integralTotal) );
  
  cout<<"Purity from fit: "<<purityFit<<" +/- "<<purityFitErr<<endl;
  
  
  
  // according to counting
  double purityCounting     = integralSignal/normalizationData;
  double purityCountingErr  = purityCounting * sqrt(  pow(integralSignalErr/integralSignal, 2)
                                                    + pow(normalizationDataErr/normalizationData, 2)
                                                    - 2*pow(integralSignalErr, 2)/(integralSignal*normalizationData) );
  
  cout<<"Purity from counting: "<<purityCounting<<" +/- "<<purityCountingErr<<endl;
  
  
  
  // systematic uncertainty associated to this
  double purityErrSyst = sqrt(pow(purityCounting-purityFit, 2) + pow(purityFitErr, 2));
  
  // compute the cross section
  
  double xsec = normalizationData * purityCounting * (nEventsGenerated/(normalizationMC*scaleFactor))/luminosity;
  
  
  
  double xsecErrStat        = xsec * (normalizationDataErr/normalizationData);
  
  double xsecErrLumi        = xsec * (luminosityErr/luminosity);
  double xsecErrPurity      = xsec * (purityErrSyst/purityCounting);
  double xsecErrExclusivity = xsec * (exclusivityEfficiencyErr/exclusivityEfficiency);
  double xsecErrScaleFactor = xsec * scaleFactorErr;
  double xsecErrMCstat      = xsec * (normalizationMCerr/normalizationMC);
  
  
  double xsecErrSyst        = sqrt(pow(xsecErrLumi, 2) +
                                   pow(xsecErrPurity, 2) +
                                   pow(xsecErrScaleFactor, 2) +
                                   pow(xsecErrExclusivity, 2) +
                                   pow(xsecErrMCstat, 2));
  
  double xsecErrSystNoLumi  = sqrt(pow(xsecErrPurity, 2) +
                                   pow(xsecErrScaleFactor, 2) +
                                   pow(xsecErrExclusivity, 2) +
                                   pow(xsecErrMCstat, 2));
  
  double xsecErr = sqrt(pow(xsecErrStat, 2) + pow(xsecErrSyst, 2));
  
  
  cout<<"\n\n----------------------------------------"<<endl;
  cout<<"Cross section\n"<<endl;
  
  cout<<"Generator: " <<xsecGenerated<<" +/- "<<xsecGeneratedErr<<" (mub)"<<endl;
  cout<<"Data: "      <<xsec         <<" +/- "<<xsecErr<<" (mub)"<<endl;
  
  cout<<"Breakdown of uncertainties: "<<endl;
  cout<<"\t- stat: "            << xsecErrStat        << "\t\t("<< 100.*xsecErrStat/xsec        <<"%)"<<endl;
  cout<<"\t- syst+lumi: "       << xsecErrSyst        << "\t\t("<< 100.*xsecErrSyst/xsec        <<"%)"<<endl;
  cout<<"\t- syst: "            << xsecErrSystNoLumi  << "\t\t("<< 100.*xsecErrSystNoLumi/xsec  <<"%)"<<endl;
  cout<<"\t- lumi: "            << xsecErrLumi        << "\t\t("<< 100.*xsecErrLumi/xsec        <<"%)"<<endl;
  cout<<"\t- exclutivity: "     << xsecErrExclusivity << "\t\t("<< 100.*xsecErrExclusivity/xsec <<"%)"<<endl;
  cout<<"\t- purity: "          << xsecErrPurity      << "\t\t("<< 100.*xsecErrPurity/xsec      <<"%)"<<endl;
  cout<<"\t- MC stat: "         << xsecErrMCstat      << "\t\t("<< 100.*xsecErrMCstat/xsec      <<"%)"<<endl;
  cout<<"\t- data-driven eff: " << xsecErrScaleFactor << "\t\t("<< 100.*xsecErrScaleFactor/xsec <<"%)"<<endl;
  cout<<"----------------------------------------\n\n"<<endl;
  
  
  
  
  // compute the lumi
  
  double measuredLumi = normalizationData * purityCounting * (nEventsGenerated/(normalizationMC*scaleFactor))/xsecGenerated;
  
  
  double measuredLumiErrStat        = measuredLumi * (normalizationDataErr/normalizationData);
  
  double measuredLumiErrXsec        = measuredLumi * (xsecGeneratedErr/xsecGenerated);
  double measuredLumiErrPurity      = measuredLumi * (purityErrSyst/purityCounting);
  double measuredLumiErrExclusivity = measuredLumi * (exclusivityEfficiencyErr/exclusivityEfficiency);
  double measuredLumiErrScaleFactor = measuredLumi * scaleFactorErr;
  double measuredLumiErrMCstat      = measuredLumi * (normalizationMCerr/normalizationMC);
  
  
  double measuredLumiErrSyst        = sqrt(pow(measuredLumiErrXsec, 2) +
                                           pow(measuredLumiErrPurity, 2) +
                                           pow(measuredLumiErrExclusivity, 2) +
                                           pow(measuredLumiErrScaleFactor,2) +
                                           pow(measuredLumiErrMCstat,2));
  
  double measuredLumiErrSystNoXsec  = sqrt(pow(measuredLumiErrPurity, 2) +
                                           pow(measuredLumiErrExclusivity, 2) +
                                           pow(measuredLumiErrScaleFactor,2) +
                                           pow(measuredLumiErrMCstat, 2));
  
  double measuredLumiErr            = sqrt(pow(measuredLumiErrStat, 2) + pow(measuredLumiErrSyst, 2));
  
  
  
  cout<<"\n\n----------------------------------------"<<endl;
  cout<<"Luminosity\n"<<endl;
  
  cout<<"Brilcalc: "<<luminosity  <<" +/- "<<luminosityErr  <<" (mub^-1)"<<endl;
  cout<<"Data: "    <<measuredLumi<<" +/- "<<measuredLumiErr<<" (mub^-1)"<<endl;
  
  cout<<"Breakdown of uncertainties: "<<endl;
  cout<<"\t- stat: "            << measuredLumiErrStat        << "\t("<<100.*measuredLumiErrStat/measuredLumi         <<"%)"<<endl;
  cout<<"\t- syst+xsec: "       << measuredLumiErrSyst        << "\t("<<100.*measuredLumiErrSyst/measuredLumi         <<"%)"<<endl;
  cout<<"\t- syst: "            << measuredLumiErrSystNoXsec  << "\t("<<100.*measuredLumiErrSystNoXsec/measuredLumi   <<"%)"<<endl;
  cout<<"\t- xsec: "            << measuredLumiErrXsec        << "\t("<<100.*measuredLumiErrXsec/measuredLumi         <<"%)"<<endl;
  cout<<"\t- exclusivity: "     << measuredLumiErrExclusivity << "\t("<<100.*measuredLumiErrExclusivity/measuredLumi  <<"%)"<<endl;
  cout<<"\t- purity: "          << measuredLumiErrPurity      << "\t("<<100.*measuredLumiErrPurity/measuredLumi       <<"%)"<<endl;
  cout<<"\t- MC stat: "         << measuredLumiErrMCstat      << "\t("<<100.*measuredLumiErrMCstat/measuredLumi       <<"%)"<<endl;
  cout<<"\t- data-driven eff: " << measuredLumiErrMCstat      << "\t("<<100.*measuredLumiErrScaleFactor/measuredLumi  <<"%)"<<endl;
  
  
  // print also the ingredients
  
  double binwidth = acoplanarityHistData->GetBinWidth(1);
  
  cout<<"\n\n----------------------------------------"<<endl;
  cout<<"Ingredients\n"<<endl;
  
  cout<<"Data normalization: "      <<normalizationData/binwidth                  << " +/- " << normalizationDataErr/binwidth<<endl;
  cout<<"Purity: "                  << purityCounting                             << " +/- " << purityErrSyst<<endl;
  cout<<"Acceptance * efficiency: " << normalizationMC/nEventsGenerated/binwidth  << " +/- " << normalizationMCerr/nEventsGenerated/binwidth<<endl;
  cout<<"Scale factor: "            << scaleFactor                                << " +/- " << scaleFactorErr<<endl;
  cout<<"----------------------------------------\n\n"<<endl;
  
  
  // plot and save results
  acoplanarityHistData->SetMarkerStyle(20);
  acoplanarityHistData->Draw("P");
  
  acoplanarityHistMC->SetLineColor(kRed);
  acoplanarityHistMC->Draw("same");
  
  gPad->SetLogy();
  
  acoplanarityHistData->GetXaxis()->SetRangeUser(0, 0.1);
  
  
  TLegend *legend = new TLegend(0.5, 0.5, 0.9, 0.9);
  legend->SetBorderSize(0);
  legend->AddEntry(acoplanarityHistData , "Data"                                          , "LP");
  legend->AddEntry(acoplanarityHistMC   , "QED #gamma#gamma #rightarrow e^{+}e^{-} (MC)"  , "F" );
  legend->AddEntry(fitFunction          , "2-exponential fit to data"                     , "L" );
  legend->Draw();
  
}


