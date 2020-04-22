#include "../include/Helpers.hpp"


const bool qed = true;
const double yMax = qed ? 1E4 : 25;
const double xMax = qed ? 0.1 : 0.2;


vector<tuple<string, string, int, int, double>> inputPaths  = {
//  {"../results/basicPlots_data_newCuts.root"                      , "default"                               , kBlack  , 25 , 1.2 },
  {"../results/basicPlots_data_default_noZDCcuts.root"            , "default, no ZDC cuts"                  , kBlack  , 25 , 1.2 },
//  {"../results/basicPlots_data_default.root"            , "current default"                  , kBlack  , 20 , 1.2 },

  // CHE
//  {"../results/basicPlots_data_looserCHE.root"                    , "looser CHE cuts"                       , kRed    , 21 , 0.6 },
//  {"../results/basicPlots_data_noCHE.root"                        , "no CHE cuts"                           , kGreen  , 22 , 0.6 },
//
//  {"../results/basicPlots_data_looserCHE_noZDCcuts.root"          , "looser CHE, no ZDC cuts"          , kRed    , 21 , 0.6 },
//  {"../results/basicPlots_data_noCHE_noZDCcuts.root"              , "no CHE, no ZDC cuts"              , kGreen  , 22 , 0.6 },
//  {"../results/basicPlots_data_muchLooserCHE.root"                , "much looser CHE, no ZDC cuts"     , kBlue   , 23 , 0.6 },
  
  
  // Pixel tracks
//  {"../results/basicPlots_data_looserPixelTracks.root"            , "looser pixel tracks cuts"              , kRed    , 21 , 0.6 },
//  {"../results/basicPlots_data_noPixelTracks.root"                , "no pixel tracks cuts"                  , kGreen  , 22 , 0.6 },
//
//  {"../results/basicPlots_data_looserPixelTracks_noZDCcuts.root"  , "looser pixel tracks cuts, no ZDC cuts" , kRed    , 21 , 0.6 },
//  {"../results/basicPlots_data_noPixelTracks_noZDCcuts.root"      , "no pixel tracks cuts, no ZDC cuts"     , kGreen  , 22 , 0.6 },

//  {"../results/basicPlots_data_muchLooserPixelTracks.root"         , "much looser pixel tracks cuts"                , kGreen    , 21 , 0.6 },
  
  // ZDC
//  {"../results/basicPlots_data_looserZDC.root"                    , "looser ZDC cuts"                       , kRed    , 21 , 0.6 },
//  {"../results/basicPlots_data_noZDC.root"                        , "no ZDC cuts"                           , kGreen  , 22 , 0.6 },
  
  
  // NEE
//  {"../results/basicPlots_data_looserNEE.root"                    , "looser NEE cuts"                       , kRed    , 21 , 0.6 },
//  {"../results/basicPlots_data_noNEE.root"                        , "no NEE cuts"                           , kGreen  , 22 , 0.6 },
//
//  {"../results/basicPlots_data_looserNEE_noZDCcuts.root"          , "looser NEE cuts, no ZDC cuts"          , kRed    , 21 , 0.6 },
//  {"../results/basicPlots_data_noNEE_noZDCcuts.root"              , "no NEE cuts, no ZDC cuts"              , kGreen  , 22 , 0.6 },
  

//  {"../results/basicPlots_data_looserEB.root"                       , "looser EB cuts, no ZDC cuts"           , kRed    , 21 , 0.6 },
//  {"../results/basicPlots_data_looserEE.root"                       , "looser EE cuts, no ZDC cuts"           , kGreen  , 22 , 0.6 },
//  {"../results/basicPlots_data_looserHB.root"                       , "looser HB cuts, no ZDC cuts"           , kBlue   , 23 , 0.6 },
//  {"../results/basicPlots_data_looserHE.root"                       , "looser HE cuts, no ZDC cuts"           , kViolet , 24 , 0.6 },
//  {"../results/basicPlots_data_looserHF.root"                       , "looser HF cuts, no ZDC cuts"           , kOrange+2, 26 , 0.6 },
  
  {"../results/basicPlots_data_HF_8.root"                       , "threshold 8 GeV"           , kRed        , 21 , 0.6 },
  {"../results/basicPlots_data_HF_9.root"                       , "threshold 9 GeV"           , kGreen      , 22 , 0.6 },
  {"../results/basicPlots_data_HF_10.root"                      , "threshold 10 GeV"          , kBlue       , 23 , 0.6 },
  {"../results/basicPlots_data_HF_11.root"                      , "threshold 11 GeV"          , kViolet     , 24 , 0.6 },
  {"../results/basicPlots_data_HF_12.root"                      , "threshold 12 GeV"          , kOrange+2   , 26 , 1.0 },
  {"../results/basicPlots_data_HF_13.root"                      , "threshold 13 GeV"          , kMagenta+2  , 27 , 0.6 },
  {"../results/basicPlots_data_HF_14.root"                      , "threshold 14 GeV"          , kCyan+2     , 28 , 2.0 },
  {"../results/basicPlots_data_HF_15.root"                      , "threshold 15 GeV"          , kGreen+3    , 29 , 0.6 },
  
  // Photon ID
//  {"../results/basicPlots_data_looserPhotonID.root"               , "looser PhotonID cuts"                  , kRed    , 21 , 0.6 },
//  {"../results/basicPlots_data_noPhotonID.root"                   , "no PhotonID cuts"                      , kGreen  , 22 , 0.6 },
//  
//  {"../results/basicPlots_data_looserPhotonID_noZDCcuts.root"     , "looser PhotonID cuts, no ZDC cuts"     , kRed    , 21 , 0.6 },
//  {"../results/basicPlots_data_noPhotonID_noZDCcuts.root"         , "no PhotonID cuts, no ZDC cuts"         , kGreen  , 22 , 0.6 },
  
//    {"../results/basicPlots_data_looserPhotonEt.root"               , "looser photon Et"                      , kRed        , 21 , 0.6 },
//    {"../results/basicPlots_data_looserPhotonHEbarrel.root"         , "looser photon H/E (barrel)"            , kGreen      , 22 , 0.6 },
//    {"../results/basicPlots_data_looserPhotonHEendcap.root"         , "looser photon H/E (endcap)"            , kBlue       , 23 , 0.6 },
//    {"../results/basicPlots_data_looserPhotonSigmaBarrel.root"      , "looser photon #sigma_{#eta} (barrel)"  , kViolet     , 24 , 0.6 },
//    {"../results/basicPlots_data_looserPhotonSigmaEndcap.root"      , "looser photon #sigma_{#eta} (endcap)"  , kOrange+2   , 26 , 1.0 },
//    {"../results/basicPlots_data_looserPhotonMass.root"             , "looser m_{#gamma#gamma}"               , kMagenta+2  , 27 , 0.6 },
  
};



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
  string sampleName = qed ? "qed" : "lbl";
  
  for(auto &[path, description, color, markerStyle, markerSize] : inputPaths){
    
    TFile *inFile = TFile::Open(path.c_str());
    
    TH1D *acoHist = (TH1D*)inFile->Get((sampleName+"_acoplanarity_all_Data").c_str());
    if(!acoHist){
      cout<<"Couldn't find acoplanarity histogram!!"<<endl;
    }
    acoHist->SetLineColor(color);
    acoHist->SetMarkerColor(color);
    acoHist->SetMarkerStyle(markerStyle);
    acoHist->SetMarkerSize(markerSize);
    
    
    
    if(first){
      acoHist->SetTitle("");
      
      acoHist->GetXaxis()->SetRangeUser(0.0, 0.2);
      acoHist->GetXaxis()->SetTitle("A_{#phi}^{#gamma#gamma}");
      acoHist->GetXaxis()->SetTitleSize(0.06);
      acoHist->GetXaxis()->SetLabelSize(0.06);
      acoHist->GetXaxis()->SetNdivisions(8, 8, 1);
      
      acoHist->GetYaxis()->SetTitle("# events");
      acoHist->GetYaxis()->SetTitleSize(0.06);
      acoHist->GetYaxis()->SetTitleOffset(1.15);
      acoHist->GetYaxis()->SetLabelSize(0.06);
      
      acoHist->SetMinimum(qed ? 1 : 0);
      acoHist->SetMaximum(yMax);
      acoHist->GetXaxis()->SetRangeUser(0, xMax);
      
      acoHist->Draw("PELC");
      
      first = false;
    }
    else{
      acoHist->Draw("PELCsame");
    }
    
    if(qed){
      TF1 *fun = new TF1(("fun_"+description).c_str(), "exp([0]+[1]*x)+exp([2]+[3]*x)", 0, 0.1);
      fun->SetParameter(2, 10);
      fun->SetParameter(3, -100);
      fun->SetParameter(0, 1);
      fun->SetParLimits(0, 0.0, 1000);
      fun->SetParameter(1, -1000);
      
      acoHist->Fit(fun);
      fun->SetLineColor(color);
      fun->Draw("same");
      
      double a1 = fun->GetParameter(0);
      double b1 = fun->GetParameter(1);
      double a2 = fun->GetParameter(2);
      double b2 = fun->GetParameter(3);
      
      
      double x = (a2-a1)/(b1-b2);
      double y = exp(a1+b1*x);
      
      double entriesPeak = 0;
      double entriesTail = 0;
      
      for(int i=1; i<=acoHist->GetNbinsX(); i++){
        if(acoHist->GetXaxis()->GetBinCenter(i) < x)  entriesPeak += acoHist->GetBinContent(i);
        else                                          entriesTail += acoHist->GetBinContent(i);
      }
      
      entriesPeak /= acoHist->GetEntries();
      entriesTail /= acoHist->GetEntries();
      
      cout<<"x: "<<x<<"\ty: "<<y<<endl;
      cout<<"Fraction of entries in the peak: "<<(entriesPeak*100)<<"%, tail: "<<(entriesTail*100)<<"%"<<endl;
      
      string peakDescription = "peak: "+to_string_with_precision(entriesPeak*100, 2)+"%";
      string tailDescription = "tail: "+to_string_with_precision(entriesTail*100, 2)+"%";
      
      legend->AddEntry(acoHist, (description+" ("+peakDescription+", "+tailDescription+")").c_str(), "PE");
      
      TGraph *criticalPoint = new TGraph();
      criticalPoint->SetPoint(0, x, y);
      criticalPoint->SetMarkerStyle(20);
      criticalPoint->SetMarkerSize(1.0);
      criticalPoint->SetMarkerColor(color);
      criticalPoint->Draw("sameP");
      
      TLine *linePeak = new TLine(0, exp(a1), x, y);
      TLine *lineTail = new TLine(x, y , -a2/b2, 1);
      
      linePeak->SetLineStyle(2);
      linePeak->SetLineColor(color);
      lineTail->SetLineStyle(2);
      lineTail->SetLineColor(color);
      
      linePeak->Draw();
      lineTail->Draw();
      
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
