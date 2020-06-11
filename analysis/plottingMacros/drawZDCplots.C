#include "../include/Helpers.hpp"

string inputPath  = "../results/basicPlots_default.root";
string outputPath = "../plots/distributions";

const double markerSize = 0.3;
const bool drawLegends = false;

const double goldenRatio = 1.61803398875;
const int baseHistWidth  = 600;
const int baseHistHeight = baseHistWidth/goldenRatio;


const double xMin = 1000;
const double xMax = 100000;
const double yMin = 2e-4;
const double yMax = 2e-3;

const int rebin = 5;

const bool logX = true;
const bool logY = true;

const double rejectFrom1 = 0;
const double rejectTo1   = 300;

const double rejectFrom2 = 600;
const double rejectTo2   = 30000;

int polyDegree = 5;

vector<tuple<string, string>> histParams = {
  // title                     x axis title
  { "zdc_sum_energy_pos_all" , "#sum E_{ZDC}^{+} (GeV)" },
  { "zdc_sum_energy_neg_all" , "#sum E_{ZDC}^{-} (GeV)" },
};

void prepareHist(TH1D *hist, string xAxisTitle)
{
  hist->SetLineColor(datasetColor.at(kData));
  hist->SetFillColorAlpha(datasetColor.at(kData), 0.2);
  
  hist->SetMarkerColor(datasetColor.at(kData));
  hist->SetMarkerStyle(20);
  hist->SetMarkerSize(markerSize);
  
  hist->SetTitle("");
  hist->GetXaxis()->SetRangeUser(xMin, xMax);
  hist->GetXaxis()->SetTitle(xAxisTitle.c_str());
  hist->GetXaxis()->SetTitleSize(0.06);
  hist->GetXaxis()->SetLabelSize(0.06);
  hist->GetXaxis()->SetTitleOffset(1.4);
  
  hist->GetYaxis()->SetTitle("# events");
  hist->GetYaxis()->SetTitleSize(0.06);
  hist->GetYaxis()->SetLabelSize(0.06);
  hist->GetYaxis()->SetTitleOffset(1.4);
  
  hist->SetMaximum(yMax);
  hist->SetMinimum(yMin);
}

void preparePad()
{
  gPad->SetLogx(logX);
  gPad->SetLogy(logY);
  gPad->SetTopMargin(0.1);
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.2);
}


Double_t backFun(Double_t *x, Double_t *par)
{
  if((x[0] > rejectFrom1 && x[0] < rejectTo1) ||
     (x[0] > rejectFrom2 && x[0] < rejectTo2)
     ){
    TF1::RejectPoint();
    return 0;
  }
  
  double result = 0;

  for(int i=0;i<polyDegree;i++){
     result += par[i]*pow(x[0],i);
   }
  
  result = exp(result);
  
//  result = par[0]/(par[1] * sqrt(2*TMath::Pi())) * exp(-1./2 * pow((x[0]-par[2])/ par[1], 2));
//  result += par[0]/pow(x[0], par[1]);
    
  return result;
}

void drawZDCplots()
{
  gStyle->SetOptStat(0);
  
  TFile *inFile = TFile::Open(inputPath.c_str());
  TCanvas* canvas = new TCanvas("ZDC", "ZDC", baseHistWidth*1, baseHistHeight*2);
  canvas->Divide(1, 2);
  int iPad=1;
  
  
  for(auto &[histName, xAxisTitle] : histParams){
  
    TH1D* hist = (TH1D*)inFile->Get((histName+"_Data").c_str());
    
    if(!hist){
      cout<<"ERROR -- no histogram \""<<histName<<endl;
      continue;
    }
    
    hist->Rebin(rebin);
    hist->Scale(1./rebin);
    hist->Scale(1./hist->GetEntries());
    
    canvas->cd(iPad++);
    
    preparePad();
    prepareHist(hist, xAxisTitle);
    
    hist->Draw("PE");
    
    
    
    TF1 *backgroundFun = new TF1("backgroundFun", backFun, xMin, xMax, polyDegree);
    
    for(int i=0;i<polyDegree;i++) backgroundFun->SetParameter(i,1);
//
//    backgroundFun->SetParameter(0, 1.26117e+05);
//    backgroundFun->SetParameter(1, 2.68249);
//    backgroundFun->SetParameter(2, -4.48738e-07);
//    backgroundFun->SetParameter(3, 2e-4);
//    backgroundFun->FixParameter(4, 1e-1);
        
    hist->Fit(backgroundFun, "0");
    backgroundFun->Draw("same");
    

    
//    string fitFunString;
//
//    fitFunString = "[0]/([1] * sqrt(2*TMath::Pi())) * exp(-1./2 * pow((x-[2])/ [1], 2))";
//    fitFunString += " + [3]/pow(x, [4])";
    
//    fitFunString += " + [5]/([6]*sqrt(2*TMath::Pi())) * exp(-1./2 * pow((x-[7]) / [6],2))";
//    fitFunString += " + [8]/([9]*sqrt(2*TMath::Pi())) * exp(-1./2 * pow((x-[10])/ [9],2))";
//    fitFunString += " + [11]/([12]*sqrt(2*TMath::Pi())) * exp(-1./2 * pow((x-[13])/ [12],2))";
//
//    TF1 *fitFun = new TF1("fitFun", fitFunString.c_str(), xMin, xMax);
////
//    for(int i=0; i<5; i++) fitFun->SetParameter(i, backgroundFun->GetParameter(i));
    
//
//    fitFun->SetParameter(5, 2.48447);
//    fitFun->SetParameter(6, 8.90283e+02); // sigma
//    fitFun->SetParameter(7, 2.63408e+03); // mu
//
//    fitFun->SetParameter(8, 0.418990);
//    fitFun->SetParameter(9, 5.92983e+02); // sigma
//    fitFun->SetParameter(10, 5.19683e+03); // mu
//
//    fitFun->SetParameter(11, -0.00591599);
//    fitFun->SetParameter(12, 2.64659e+0); // sigma
//    fitFun->SetParameter(13, 7.03975e+03); // mu
//
//    hist->Fit(fitFun);
    
//    fitFun->Draw("same");
    
    TLegend *legend = new TLegend(0.6, 0.8, 0.9, 0.9 );
    legend->AddEntry(hist, "UPC Data", "pel");
    legend->Draw();
  }
  
  
  canvas->SaveAs((outputPath+"_zdc.pdf").c_str());
  
}
