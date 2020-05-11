#include "../include/Helpers.hpp"


const bool qed = true;
const double yMax = qed ? 1E4 : 25;
const double xMax = qed ? 0.1 : 0.2;


vector<tuple<string, string, int, int, double>> inputPaths  = {
//  {"../results/basicPlots_data_newCuts.root"                      , "default"                               , kBlack      , 25 , 1.2 },
//  {"../results/basicPlots_data_default_noZDCcuts.root"            , "default, no ZDC cuts"                  , kGreen      , 25 , 1.2 },
//  {"../results/basicPlots_data_default.root"                      , "current default"                       , kBlack      , 20 , 1.2 },
  {"../results/basicPlots_data_muchLooserCHE.root"                , "2018"                                  , kBlack      , 20 , 1.2 },
  
//  {"../results/basicPlots_data_looserHINPhotonHESigma.root"       , "HIN loose"                             , kRed        , 20 , 1.0 },
//  {"../results/basicPlots_data_ruchi.root"                        , "2015"                                  , kRed        , 20 , 1.2 },
  
  // CHE
//  {"../results/basicPlots_data_looserCHE.root"                    , "looser CHE cuts"                       , kRed        , 21 , 0.6 },
//  {"../results/basicPlots_data_noCHE.root"                        , "no CHE cuts"                           , kGreen      , 22 , 0.6 },
//  {"../results/basicPlots_data_looserCHE_noZDCcuts.root"          , "looser CHE, no ZDC cuts"               , kRed        , 21 , 0.6 },
//  {"../results/basicPlots_data_noCHE_noZDCcuts.root"              , "no CHE, no ZDC cuts"                   , kGreen      , 22 , 0.6 },
  
  // Pixel tracks
//  {"../results/basicPlots_data_looserPixelTracks.root"            , "looser pixel tracks cuts"              , kRed        , 21 , 0.6 },
//  {"../results/basicPlots_data_noPixelTracks.root"                , "no pixel tracks cuts"                  , kGreen      , 22 , 0.6 },
//  {"../results/basicPlots_data_looserPixelTracks_noZDCcuts.root"  , "looser pixel tracks cuts, no ZDC cuts" , kRed        , 21 , 0.6 },
//  {"../results/basicPlots_data_noPixelTracks_noZDCcuts.root"      , "no pixel tracks cuts, no ZDC cuts"     , kGreen      , 22 , 0.6 },
//  {"../results/basicPlots_data_muchLooserPixelTracks.root"        , "much looser pixel tracks cuts"         , kGreen      , 21 , 0.6 },
  
  // ZDC
//  {"../results/basicPlots_data_looserZDC.root"                    , "looser ZDC cuts"                       , kRed        , 21 , 0.6 },
//  {"../results/basicPlots_data_noZDC.root"                        , "no ZDC cuts"                           , kGreen      , 22 , 0.6 },
//  {"../results/basicPlots_data_ZDCcoincidence.root"               , "ZDC coincidence (>25k)"                , kGreen      , 22 , 0.6 },
  
  // NEE
//  {"../results/basicPlots_data_looserNEE.root"                    , "looser NEE cuts"                       , kRed        , 21 , 0.6 },
//  {"../results/basicPlots_data_noNEE.root"                        , "no NEE cuts"                           , kGreen      , 22 , 0.6 },
//  {"../results/basicPlots_data_looserNEE_noZDCcuts.root"          , "looser NEE cuts, no ZDC cuts"          , kRed        , 21 , 0.6 },
//  {"../results/basicPlots_data_noNEE_noZDCcuts.root"              , "no NEE cuts, no ZDC cuts"              , kGreen      , 22 , 0.6 },
  
//  {"../results/basicPlots_data_looserEB.root"                     , "looser EB cuts, no ZDC cuts"           , kRed        , 21 , 0.6 },
//  {"../results/basicPlots_data_looserEE.root"                     , "looser EE cuts, no ZDC cuts"           , kGreen      , 22 , 0.6 },
//  {"../results/basicPlots_data_looserHB.root"                     , "looser HB cuts, no ZDC cuts"           , kBlue       , 23 , 0.6 },
//  {"../results/basicPlots_data_looserHE.root"                     , "looser HE cuts, no ZDC cuts"           , kViolet     , 24 , 0.6 },
//  {"../results/basicPlots_data_looserHF.root"                     , "looser HF cuts, no ZDC cuts"           , kOrange+2   , 26 , 0.6 },
  
//  {"../results/basicPlots_data_HF_8.root"                         , "threshold 8 GeV"                       , kRed        , 21 , 0.6 },
//  {"../results/basicPlots_data_HF_9.root"                         , "threshold 9 GeV"                       , kGreen      , 22 , 0.6 },
//  {"../results/basicPlots_data_HF_10.root"                        , "threshold 10 GeV"                      , kBlue       , 23 , 0.6 },
//  {"../results/basicPlots_data_HF_11.root"                        , "threshold 11 GeV"                      , kViolet     , 24 , 0.6 },
//  {"../results/basicPlots_data_HF_12.root"                        , "threshold 12 GeV"                      , kOrange+2   , 26 , 1.0 },
//  {"../results/basicPlots_data_HF_13.root"                        , "threshold 13 GeV"                      , kMagenta+2  , 27 , 0.6 },
//  {"../results/basicPlots_data_HF_14.root"                        , "threshold 14 GeV"                      , kCyan+2     , 28 , 2.0 },
//  {"../results/basicPlots_data_HF_15.root"                        , "threshold 15 GeV"                      , kGreen+3    , 29 , 0.6 },
  
  // Photon ID
//  {"../results/basicPlots_data_looserPhotonID.root"               , "looser PhotonID cuts"                  , kRed        , 21 , 0.6 },
//  {"../results/basicPlots_data_noPhotonID.root"                   , "no PhotonID cuts"                      , kGreen      , 22 , 0.6 },
//  {"../results/basicPlots_data_looserPhotonID_noZDCcuts.root"     , "looser PhotonID cuts, no ZDC cuts"     , kRed        , 21 , 0.6 },
//  {"../results/basicPlots_data_noPhotonID_noZDCcuts.root"         , "no PhotonID cuts, no ZDC cuts"         , kGreen      , 22 , 0.6 },
  
//  {"../results/basicPlots_data_looserPhotonEt.root"               , "looser photon Et"                      , kRed        , 21 , 0.6 },
//  {"../results/basicPlots_data_looserPhotonHEbarrel.root"         , "looser photon H/E (barrel)"            , kGreen      , 22 , 0.6 },
//  {"../results/basicPlots_data_looserPhotonHEendcap.root"         , "looser photon H/E (endcap)"            , kBlue       , 23 , 0.6 },
//  {"../results/basicPlots_data_looserPhotonSigmaBarrel.root"      , "looser photon #sigma_{#eta} (barrel)"  , kViolet     , 24 , 0.6 },
//  {"../results/basicPlots_data_looserPhotonSigmaEndcap.root"      , "looser photon #sigma_{#eta} (endcap)"  , kOrange+2   , 26 , 1.0 },
//  {"../results/basicPlots_data_looserPhotonMass.root"             , "looser m_{#gamma#gamma}"               , kMagenta+2  , 27 , 0.6 },
};

TH1D* getAcoplanarityHist(string path, string description, int color, double markerStyle, double markerSize)
{
  TFile *inFile = TFile::Open(path.c_str());
  TH1D *acoHist = nullptr;
  string sampleName = qed ? "qed" : "lbl";
  
  if(description=="2015")  acoHist = (TH1D*)inFile->Get("hacoplanarity_data");
  else                     acoHist = (TH1D*)inFile->Get((sampleName+"_acoplanarity_all_Data").c_str());
  
  if(!acoHist){
    cout<<"Couldn't find acoplanarity histogram!!"<<endl;
  }
  acoHist->SetLineColor(color);
  acoHist->SetMarkerColor(color);
  acoHist->SetMarkerStyle(markerStyle);
  acoHist->SetMarkerSize(markerSize);
  
  return acoHist;
}

TF1* getDoubleExp(string description)
{
  TF1 *fun = new TF1(("fun_"+description).c_str(), "exp([0]+[1]*x)+exp([2]+[3]*x)", 0, 0.1);
  fun->SetParameter(2, 10);
  fun->SetParameter(3, -100);
  fun->SetParameter(0, 1);
  fun->SetParLimits(0, 0.0, 1000);
  fun->SetParameter(1, -1000);
  return fun;
}

void setupHist(TH1D *hist)
{
  hist->SetTitle("");
  
  hist->GetXaxis()->SetRangeUser(0.0, 0.2);
  hist->GetXaxis()->SetTitle(qed ? "A_{#phi}^{e^{+}e^{-}}" : "A_{#phi}^{#gamma#gamma}");
  hist->GetXaxis()->SetTitleSize(0.06);
  hist->GetXaxis()->SetLabelSize(0.06);
  hist->GetXaxis()->SetNdivisions(8, 8, 1);
  
  hist->GetYaxis()->SetTitle("# events");
  hist->GetYaxis()->SetTitleSize(0.06);
  hist->GetYaxis()->SetTitleOffset(1.15);
  hist->GetYaxis()->SetLabelSize(0.06);
  
  hist->SetMinimum(qed ? 1 : 0);
  hist->SetMaximum(yMax);
  hist->GetXaxis()->SetRangeUser(0, xMax);
}

pair<double, double> getCrossingPoint(TF1 *doubleExp)
{
  double a1 = doubleExp->GetParameter(0);
  double b1 = doubleExp->GetParameter(1);
  double a2 = doubleExp->GetParameter(2);
  double b2 = doubleExp->GetParameter(3);
  
  
  double x = (a2-a1)/(b1-b2);
  double y = exp(a1+b1*x);
  
  return make_pair(x, y);
}

pair<TF1*, TF1*> getPeakAndTailFunctions(TF1 *doubleExp, string description)
{
  TF1 *peakFun = new TF1(("peak_fun_"+description).c_str(), "exp([0]+[1]*x)", 0, 1.0);
  peakFun->FixParameter(0, doubleExp->GetParameter(0));
  peakFun->FixParameter(1, doubleExp->GetParameter(1));
  
  TF1 *tailFun = new TF1(("tail_fun_"+description).c_str(), "exp([0]+[1]*x)", 0, 1.0);
  tailFun->FixParameter(0, doubleExp->GetParameter(2));
  tailFun->FixParameter(1, doubleExp->GetParameter(3));
  
  return make_pair(peakFun, tailFun);
}

void drawLinesAndCrossingPoint(TF1 *doubleExp, int color)
{
  auto [x, y] = getCrossingPoint(doubleExp);
  
  TGraph *criticalPoint = new TGraph();
  criticalPoint->SetPoint(0, x, y);
  criticalPoint->SetMarkerStyle(20);
  criticalPoint->SetMarkerSize(1.0);
  criticalPoint->SetMarkerColor(color);
  criticalPoint->Draw("sameP");
  
  TLine *linePeak = new TLine(0, exp(doubleExp->GetParameter(0)), x, y);
  TLine *lineTail = new TLine(x, y , -doubleExp->GetParameter(2)/doubleExp->GetParameter(3), 1);
  
  linePeak->SetLineStyle(2);
  linePeak->SetLineColor(color);
  lineTail->SetLineStyle(2);
  lineTail->SetLineColor(color);
  
  linePeak->Draw();
  lineTail->Draw();
}

void findBestCutOnIntegrals(TH1D *acoHist, TF1 *peakFun, TF1 *tailFun)
{
  double bestSignificance = -1;
  double bestCut;
  double bestPeakIntegral;
  double bestTailIntegral;
  
  for(double cut=0; cut<1; cut+=0.0001){
    double peakIntegral = peakFun->Integral(0, cut);
    double tailIntegral = tailFun->Integral(0, cut);
    
    double signal = peakIntegral - tailIntegral;
    double background = tailIntegral;
    
    double significance = signal/sqrt(signal+background);
    
    if(significance > bestSignificance){
      bestSignificance = significance;
      bestCut = cut;
      bestPeakIntegral = peakIntegral;
      bestTailIntegral = tailIntegral;
    }
  }
  
  double entriesPeak = acoHist->Integral(1, acoHist->GetXaxis()->FindFixBin(bestCut));
  double entriesTail = acoHist->Integral(acoHist->GetXaxis()->FindFixBin(bestCut), acoHist->FindFixBin(0.2));
  
  cout<<"Best cut position: "<<bestCut<<endl;
  cout<<"Best significance: "<<bestSignificance<<"\tpeak: "<<bestPeakIntegral<<"\ttail: "<<bestTailIntegral<<endl;
  cout<<"Entries in peak: "<<entriesPeak<<"\ttail: "<<entriesTail<<endl;
}

pair<double, double> findBestCutOnEntries(TH1D *acoHist, TF1 *peakFun, TF1 *tailFun)
{
  double bestSignalEntries;
  double bestBackgroundEntries;
  double bestSignificance = -1;
  double bestCut;
  double bestPeakIntegral;
  double bestTailIntegral;
  
  for(double cut=0; cut<1; cut+=0.0001){
  
    double signalEntries = 0;
    double backgroundEntries = 0;
    
    for(int iBin=1; iBin<=acoHist->GetNbinsX(); iBin++){
      double x = acoHist->GetBinCenter(iBin);
      if(x > cut) break;
      backgroundEntries += tailFun->Eval(x);
      signalEntries += (peakFun->Eval(x) - tailFun->Eval(x));
    }
    
    double significance = signalEntries/sqrt(signalEntries+backgroundEntries);
    
    if(significance > bestSignificance){
      bestSignificance = significance;
      bestCut = cut;
      bestSignalEntries = signalEntries;
      bestBackgroundEntries = backgroundEntries;
    }
  }
  
  cout<<"Significance from entries: "<<bestSignificance<<"\tfor cut: "<<bestCut<<endl;
  cout<<"Signal entries in the peak: "<<bestSignalEntries<<"\tbackground: "<<bestBackgroundEntries<<endl;
  
  return make_pair(bestSignalEntries, bestBackgroundEntries);
}

void compareCuts()
{
  TCanvas *canvas = new TCanvas("canvas", "canvas", 800, 600);
  canvas->cd(1);
  
  gStyle->SetOptStat(0);
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);
  gPad->SetLogy(qed);
  
  double legYmin = 0.9 - inputPaths.size()*0.05;
  TLegend *legend = new TLegend(0.3, legYmin, 0.9, 0.9);
  
  bool first = true;
  
  for(auto &[path, description, color, markerStyle, markerSize] : inputPaths){
    
    TH1D *acoHist = getAcoplanarityHist(path, description, color, markerSize, markerStyle);
    
    if(first){
      setupHist(acoHist);
      acoHist->Draw("PELC");
      first = false;
    }
    else{
      acoHist->Draw("PELCsame");
    }
    
    if(qed){
      TF1 *fun = getDoubleExp(description);
      acoHist->Fit(fun);
      fun->SetLineColor(color);
      fun->Draw("same");
    
      auto [peakFun, tailFun] = getPeakAndTailFunctions(fun, description);
      
      findBestCutOnIntegrals(acoHist, peakFun, tailFun);
      auto [signal, background] = findBestCutOnEntries(acoHist, peakFun, tailFun);
      
      string peakDescription = "peak: "+to_string_with_precision(signal, 1)+"";
      string tailDescription = "tail: "+to_string_with_precision(background, 1)+"";
      string significanceDescription = "Z: "+to_string_with_precision(signal/sqrt(signal+background), 1);
      
      legend->AddEntry(acoHist, (description+" ("+peakDescription+", "+tailDescription+", "+significanceDescription+")").c_str(), "PE");
      
      drawLinesAndCrossingPoint(fun, color);
      
    }
    else{
      TF1 *fun = new TF1(("fun_"+description).c_str(), "[0]*x+[1]", 0, 0.2);
      fun->SetParameter(0, 1);
      fun->SetParameter(1, 0);
      acoHist->Fit(fun, "", "", 0.01, 0.20);
      
      double SB = acoHist->GetBinContent(1) + acoHist->GetBinContent(2);
      double B = fun->Eval(0.01) + fun->Eval(0.02);
      double S = SB-B;
      double significanceInclined = S/sqrt(SB);
      
      fun->FixParameter(0, 1);
      acoHist->Fit(fun, "0", "", 0.01, 0.20);
      SB = acoHist->GetBinContent(1) + acoHist->GetBinContent(2);
      B = fun->Eval(0.01) + fun->Eval(0.02);
      S = SB-B;
      double significanceFlat = S/sqrt(SB);
      
      cout<<description<<" significance flat: "<<significanceFlat<<"\tinclined: "<<significanceInclined<<endl;
      legend->AddEntry(acoHist, (description+" (flat: "+to_string_with_precision(significanceFlat, 2)+", inclined: "+to_string_with_precision(significanceInclined, 2)+")").c_str(), "PE");
    }
  }
    
  legend->Draw();
}
