#include "../include/Helpers.hpp"

vector<tuple<string, string, int, int, double>> inputPaths  = {
  {"../results/basicPlots_data_newCuts.root"                      , "default"                               , kBlack  , 25 , 1.2 },
  {"../results/basicPlots_data_default_noZDCcuts.root"            , "default, no ZDC cuts"                  , kBlack  , 25 , 1.2 },

  // CHE
//  {"../results/basicPlots_data_looserCHE.root"                    , "looser CHE cuts"                       , kRed    , 21 , 0.6 },
//  {"../results/basicPlots_data_noCHE.root"                        , "no CHE cuts"                           , kGreen  , 22 , 0.6 },
//
//  {"../results/basicPlots_data_looserCHE_noZDCcuts.root"          , "looser CHE cuts, no ZDC cuts"          , kRed    , 21 , 0.6 },
//  {"../results/basicPlots_data_noCHE_noZDCcuts.root"              , "no CHE cuts, no ZDC cuts"              , kGreen  , 22 , 0.6 },
  
  
  // Pixel tracks
//  {"../results/basicPlots_data_looserPixelTracks.root"            , "looser pixel tracks cuts"              , kRed    , 21 , 0.6 },
//  {"../results/basicPlots_data_noPixelTracks.root"                , "no pixel tracks cuts"                  , kGreen  , 22 , 0.6 },
//
//  {"../results/basicPlots_data_looserPixelTracks_noZDCcuts.root"  , "looser pixel tracks cuts, no ZDC cuts" , kRed    , 21 , 0.6 },
//  {"../results/basicPlots_data_noPixelTracks_noZDCcuts.root"      , "no pixel tracks cuts, no ZDC cuts"     , kGreen  , 22 , 0.6 },

  
  // ZDC
//  {"../results/basicPlots_data_looserZDC.root"                    , "looser ZDC cuts"                       , kRed    , 21 , 0.6 },
//  {"../results/basicPlots_data_noZDC.root"                        , "no ZDC cuts"                           , kGreen  , 22 , 0.6 },
  
  
  // NEE
//  {"../results/basicPlots_data_looserNEE.root"                    , "looser NEE cuts"                       , kRed    , 21 , 0.6 },
//  {"../results/basicPlots_data_noNEE.root"                        , "no NEE cuts"                           , kGreen  , 22 , 0.6 },
//
//  {"../results/basicPlots_data_looserNEE_noZDCcuts.root"          , "looser NEE cuts, no ZDC cuts"          , kRed    , 21 , 0.6 },
//  {"../results/basicPlots_data_noNEE_noZDCcuts.root"              , "no NEE cuts, no ZDC cuts"              , kGreen  , 22 , 0.6 },
  
  
  // Photon ID
//  {"../results/basicPlots_data_looserPhotonID.root"               , "looser PhotonID cuts"                  , kRed    , 21 , 0.6 },
//  {"../results/basicPlots_data_noPhotonID.root"                   , "no PhotonID cuts"                      , kGreen  , 22 , 0.6 },
//  
//  {"../results/basicPlots_data_looserPhotonID_noZDCcuts.root"     , "looser PhotonID cuts, no ZDC cuts"     , kRed    , 21 , 0.6 },
//  {"../results/basicPlots_data_noPhotonID_noZDCcuts.root"         , "no PhotonID cuts, no ZDC cuts"         , kGreen  , 22 , 0.6 },
  
};

const double yMax = 25;

void compareCuts()
{
  
  
  TCanvas *canvas = new TCanvas("canvas", "canvas", 800, 600);
  canvas->cd(1);
  
  gStyle->SetOptStat(0);
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);
  
  TLegend *legend = new TLegend(0.6, 0.7, 0.9, 0.9);
  
  bool first = true;
  
  for(auto &[path, description, color, markerStyle, markerSize] : inputPaths){
    
    TFile *inFile = TFile::Open(path.c_str());
    
    TH1D *acoHist = (TH1D*)inFile->Get("lbl_acoplanarity_all_Data");
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
      
      acoHist->SetMinimum(0);
      acoHist->SetMaximum(yMax);
      
      acoHist->Draw("PE");
      
      first = false;
    }
    else{
      acoHist->Draw("PEsame");
    }
    
    TF1 *fun = new TF1(("fun_"+description).c_str(), "[0]*x+[1]", 0, 0.2);
    fun->SetParameter(0, 1);
    fun->SetParameter(1, 0);
    
    acoHist->Fit(fun, "", "", 0.01, 0.20);
    
    fun->SetLineColor(color);
    fun->Draw("same");
    
    double SB = acoHist->GetBinContent(1) + acoHist->GetBinContent(2);
    double B = fun->Eval(0.01) + fun->Eval(0.02);
    double S = SB-B;
    
    double significance = S/sqrt(SB);
    cout<<description<<" significance: "<<significance<<endl;
    
    legend->AddEntry(acoHist, (description+" ("+to_string_with_precision(significance, 1)+")").c_str(), "PE");
    
  }
    
  legend->Draw();
}
