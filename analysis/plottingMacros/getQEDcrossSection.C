

//string inputPath  = "../results/basicPlots_default_HEMupdate.root";
string inputPath  = "../results/basicPlots_default.root";

// efficiency for exclusivity, with stat and syst errors.
const double neutralExclusivityEfficiency        = 0.71; // 0.895;
const double neutralExclusivityEfficiencyErrStat = 0.03; // 0.013;
const double neutralExclusivityEfficiencyErrSyst = 0.0;
const double neutralExclusivityEfficiencyErr     = sqrt(pow(neutralExclusivityEfficiencyErrStat, 2) +
                                                        pow(neutralExclusivityEfficiencyErrSyst, 2));

const double chargedExclusivityEfficiency        = 0.88;
const double chargedExclusivityEfficiencyErrStat = 0.04;
const double chargedExclusivityEfficiencyErrSyst = 0.0;
const double chargedExclusivityEfficiencyErr     = sqrt(pow(chargedExclusivityEfficiencyErrStat, 2) +
                                                        pow(chargedExclusivityEfficiencyErrSyst, 2));

const double generatorCutsEfficiency  = 0.7184;
const double dataAvailableFraction    = 0.8514227642; // we are missing 15% of the data

// From SuperChic
const double xsecGenerated    = dataAvailableFraction * generatorCutsEfficiency * 8827.220; // μb
const double xsecGeneratedErr = 79.73715; // μb

// TODO: replace luminosity by the one calculated for our ntuples

const double luminosity       = 1642.797392287; // μb^-1
// luminosity from brilcalc obtained with this command:
// brilcalc lumi --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_BRIL.json  -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/HI/PromptReco/Cert_326381-327564_HI_PromptReco_Collisions18_JSON.txt --hltpath HLT_HIUPC_DoubleEG2_NotMBHF2AND_v1


// luminosity in our ntuples:
// brilcalc lumi --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_BRIL.json  -i /afs/cern.ch/work/j/jniedzie/private/lbl_ntuplizer/CMSSW_10_3_4/src/HeavyIonsAnalysis/PhotonAnalysis/test/crab_projects/crab_ntuples_data_lbl/results/processedLumis.json --hltpath HLT_HIUPC_DoubleEG2_NotMBHF2AND_v1

// 1247.958558851

// +

// brilcalc lumi --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_BRIL.json  -i /afs/cern.ch/work/j/jniedzie/private/lbl_ntuplizer/CMSSW_10_3_4/src/HeavyIonsAnalysis/PhotonAnalysis/test/crab_projects/crab_ntuples_data_lbl/results/processedLumis.json --hltpath HLT_HIUPC_DoubleEG2_NotMBHF2AND_v1

// 387.164580972

// = 1635.123139823

const double luminosityErr    = 0.015 * luminosity;
// Relative uncertainty on luminosity as recommended by: http://cms.cern.ch/iCMS/analysisadmin/cadilines?line=LUM-18-001

const double scaleFactor          = pow(0.71, 2); // This is Reco+ID only.
const double scaleFactorErrStat   = 0.03;
const double scaleFactorErr       = 2 * scaleFactorErrStat;

// const double scaleFactorErr       = sqrt(pow(scale, 2) + pow( 2 * 0.02, 2)); // TODO: why second term is multiplied by 2?

const double nEventsGenerated     = 980000; // TODO: update number of events when full stat available

const double acoplanarityCut = 0.06;
const double maxAcolpanarity = 0.01; // TODO: what's the difference between those two numbers?

const double globalSystErr = 2 * scaleFactorErrSyst/sqrt(scaleFactor); // relative uncertainty on Reco+ID scale factor

void getQEDcrossSection()
{
  TFile *inFile = TFile::Open(inputPath.c_str());
  
  if(!inFile){
    cout<<"ERROR -- could not open input file: "<<inputPath<<endl;
    exit(0);
  }
  
  TH1D *acoplanarityHistData = (TH1D*)inFile->Get("qed_acoplanarity_all_Data");
  if(!acoplanarityHistData){
    cout<<"ERROR -- could not find Data acoplanarity histogram in the input file!"<<endl;
    exit(0);
  }
  
  TH1D *acoplanarityHistMC = (TH1D*)inFile->Get("qed_acoplanarity_all_QED_SC");
  if(!acoplanarityHistMC){
    cout<<"ERROR -- could not find MC acoplanarity histogram in the input file!"<<endl;
    exit(0);
  }
  
  
  TTree *triggerSFtree = (TTree*)inFile->Get("triggerScaleFactorsTree");
  if(!triggerSFtree){
    cout<<"ERROR -- could not find trigger scale factors tree in the input file!"<<endl;
    exit(0);
  }
  
  
  vector<float> *triggerScaleFactors = nullptr;
  
  triggerSFtree->SetBranchAddress("SFweights", &triggerScaleFactors);
  triggerSFtree->GetEntry(0);
  
  const int nVariations = triggerScaleFactors->size();
  
  TH1D *errorVariationHists[nVariations];
  for(int iVariation=0; iVariation<nVariations; iVariation++){
    string name = "variationHist" + to_string(iVariation);
    errorVariationHists[iVariation] = new TH1D(name.c_str(), name.c_str(), 30, 0, acoplanarityCut);
  }
  
  for(int iEntry=0; iEntry<triggerSFtree->GetEntries(); iEntry++){
    triggerSFtree->GetEntry(iEntry);
    
    for(int iVariation=0; iVariation<nVariations; iVariation++){
      errorVariationHists[iVariation]->Fill(triggerScaleFactors->at(iVariation));
    }
  }

  for(int iBin=1; iBin<=acoplanarityHistMC->GetNbinsX(); iBin++){
    double err=0;
    for(int iVariation=1; iVariation<nVariations; iVariation++){
      err += pow(errorVariationHists[iVariation]->GetBinContent(iBin) - errorVariationHists[0]->GetBinContent(iBin), 2);
    }
    
    double totalErr = sqrt(err + pow(acoplanarityHistMC->GetBinError(iBin), 2) + pow(globalSystErr, 2));
    
    acoplanarityHistMC->SetBinError(iBin, totalErr);
  }

  
  
  // normalize MC: force the data and MC integrals to be the same within acop<0.01
  
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
  
  // TODO: why do we calculate it this way?
  double xsec = normalizationData * purityCounting * (nEventsGenerated/(normalizationMC*scaleFactor))/luminosity;
  
  
  double xsecErrStat                = xsec * (normalizationDataErr/normalizationData);
  
  double xsecErrLumi                = xsec * (luminosityErr/luminosity);
  double xsecErrPurity              = xsec * (purityErrSyst/purityCounting);
  double xsecErrNeutralExclusivity  = xsec * (neutralExclusivityEfficiencyErr/neutralExclusivityEfficiency);
  double xsecErrChargedExclusivity  = xsec * (chargedExclusivityEfficiencyErr/chargedExclusivityEfficiency);
  double xsecErrScaleFactor         = xsec * scaleFactorErr;
  double xsecErrMCstat              = xsec * (normalizationMCerr/normalizationMC);
  
  
  double xsecErrSyst        = sqrt(pow(xsecErrLumi, 2) +
                                   pow(xsecErrPurity, 2) +
                                   pow(xsecErrScaleFactor, 2) +
                                   pow(xsecErrNeutralExclusivity, 2) +
                                   pow(xsecErrChargedExclusivity, 2) +
                                   pow(xsecErrMCstat, 2));
  
  double xsecErrSystNoLumi  = sqrt(pow(xsecErrPurity, 2) +
                                   pow(xsecErrScaleFactor, 2) +
                                   pow(xsecErrNeutralExclusivity, 2) +
                                   pow(xsecErrChargedExclusivity, 2) +
                                   pow(xsecErrMCstat, 2));
  
  double xsecErr = sqrt(pow(xsecErrStat, 2) + pow(xsecErrSyst, 2));
  
  
  cout<<"\n\n----------------------------------------"<<endl;
  cout<<"Cross section\n"<<endl;
  
  cout<<"Generator: " <<xsecGenerated<<" +/- "<<xsecGeneratedErr<<" (mub)"<<endl;
  cout<<"Data: "      <<xsec         <<" +/- "<<xsecErr<<" (mub)"<<endl;
  
  cout<<"Breakdown of uncertainties: "<<endl;
  cout<<"\t- stat: "                << xsecErrStat                << "\t\t("<< 100.*xsecErrStat/xsec               <<"%)"<<endl;
  cout<<"\t- syst+lumi: "           << xsecErrSyst                << "\t\t("<< 100.*xsecErrSyst/xsec               <<"%)"<<endl;
  cout<<"\t- syst: "                << xsecErrSystNoLumi          << "\t\t("<< 100.*xsecErrSystNoLumi/xsec         <<"%)"<<endl;
  cout<<"\t- lumi: "                << xsecErrLumi                << "\t\t("<< 100.*xsecErrLumi/xsec               <<"%)"<<endl;
  cout<<"\t- neutral exclutivity: " << xsecErrNeutralExclusivity  << "\t\t("<< 100.*xsecErrNeutralExclusivity/xsec <<"%)"<<endl;
  cout<<"\t- charged exclutivity: " << xsecErrChargedExclusivity  << "\t\t("<< 100.*xsecErrChargedExclusivity/xsec <<"%)"<<endl;
  cout<<"\t- purity: "              << xsecErrPurity              << "\t\t("<< 100.*xsecErrPurity/xsec             <<"%)"<<endl;
  cout<<"\t- MC stat: "             << xsecErrMCstat              << "\t\t("<< 100.*xsecErrMCstat/xsec             <<"%)"<<endl;
  cout<<"\t- data-driven eff: "     << xsecErrScaleFactor         << "\t\t("<< 100.*xsecErrScaleFactor/xsec        <<"%)"<<endl;
  cout<<"----------------------------------------\n\n"<<endl;
  
  
  // compute the lumi
  
  double measuredLumi = normalizationData * purityCounting * (nEventsGenerated/(normalizationMC*scaleFactor))/xsecGenerated;
  
  
  double measuredLumiErrStat        = measuredLumi * (normalizationDataErr/normalizationData);
  
  double measuredLumiErrXsec        = measuredLumi * (xsecGeneratedErr/xsecGenerated);
  double measuredLumiErrPurity      = measuredLumi * (purityErrSyst/purityCounting);
  double measuredLumiErrNeutralExclusivity = measuredLumi * (neutralExclusivityEfficiencyErr/neutralExclusivityEfficiency);
  double measuredLumiErrChargedExclusivity = measuredLumi * (chargedExclusivityEfficiencyErr/chargedExclusivityEfficiency);
  double measuredLumiErrScaleFactor = measuredLumi * scaleFactorErr;
  double measuredLumiErrMCstat      = measuredLumi * (normalizationMCerr/normalizationMC);
  
  
  double measuredLumiErrSyst        = sqrt(pow(measuredLumiErrXsec, 2) +
                                           pow(measuredLumiErrPurity, 2) +
                                           pow(measuredLumiErrNeutralExclusivity, 2) +
                                           pow(measuredLumiErrChargedExclusivity, 2) +
                                           pow(measuredLumiErrScaleFactor,2) +
                                           pow(measuredLumiErrMCstat,2));
  
  double measuredLumiErrSystNoXsec  = sqrt(pow(measuredLumiErrPurity, 2) +
                                           pow(measuredLumiErrNeutralExclusivity, 2) +
                                           pow(measuredLumiErrChargedExclusivity, 2) +
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
  cout<<"\t- neutral exclusivity: " << measuredLumiErrNeutralExclusivity << "\t("<<100.*measuredLumiErrNeutralExclusivity/measuredLumi  <<"%)"<<endl;
  cout<<"\t- charged exclusivity: " << measuredLumiErrChargedExclusivity << "\t("<<100.*measuredLumiErrChargedExclusivity/measuredLumi  <<"%)"<<endl;
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


