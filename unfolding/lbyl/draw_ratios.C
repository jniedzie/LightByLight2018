#include <iostream>
#include <fstream>
#include <sstream>
#include "TROOT.h"
#include "TStyle.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TAxis.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TText.h"
#include "TLorentzVector.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TAxis.h"
#include "TH1.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH1I.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TMath.h"
#include "TVector3.h"
#include "TString.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TSystem.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TLegend.h>
#include <TMath.h>
#include <TPad.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TPad.h>

double syst_uncertainty = 0.26;
double syst_uncertainty_mc = 0.10;

void make_hist(TH1D *&, string, string, int, float, Color_t, int, int) ;
TH1D* get_stat_uncertainty_hist(TH1D *input_hist, double uncertainty = syst_uncertainty);
void prepare_canvas(TCanvas *canvas);
vector<TPad*> get_pads();
TH1D* get_ratio(TH1D *hist_num, TH1D* hist_den);

int canvas_width = 1200;
int canvas_height = 700;

int mc_gen_color = kBlue;
int data_unfold_color = kRed;
int mc_reco_color = kBlack;
int data_reco_color = kOrange+1;

void draw_ratios()
{
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  TH1::SetDefaultSumw2();
  gStyle->SetPadRightMargin(0.005);
  
  string MethID1 = "Bayes_unfo";
  //  string MethID1 = "Svd_unfo"
  //  string MethID1 = "BinByBin_unfo";
  
  TFile *f1= new TFile(Form("unfolding_histograms_%s.root", MethID1.c_str()),"r");
  TFile *f2= new TFile(Form("unfolding_histograms_invmass_%s.root", MethID1.c_str()), "r");
  
  TH1D *hist_rapidity_mc_gen          = (TH1D*)f1->Get("hGenRap_xSec");
  TH1D *hist_rapidity_data_unfolded   = (TH1D*)f1->Get("hUnfoDataRap_xSec");
  TH1D *hist_invmass_mc_gen           = (TH1D*)f2->Get("hGenInvmass_xSec");
  TH1D *hist_invmass_data_unfolded    = (TH1D*)f2->Get("hUnfoDataInvmass_xSec");
  
  TLegend *legend = new TLegend(0.30, 0.68, 0.90, 0.9);
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->SetTextFont(43);
  legend->SetTextSize(24);
  legend->AddEntry(hist_rapidity_data_unfolded,"Unfolded data (Bayes)","pl");
  legend->AddEntry(hist_rapidity_mc_gen, "Gen-level MC (Superchic)", "pl");
  
  
  TCanvas* canvas = new TCanvas("canvas","canvas", 50, 50, canvas_width, canvas_height);
//  prepare_canvas(canvas);
  
  vector<TPad*> pads = get_pads();
  
  
  // Rapidity
  string x_title = "|y_{#gamma#gamma}|";
  string y_title = "d#sigma_{#gamma#gamma}/dy_{#gamma#gamma} (nb)";
  
  hist_rapidity_data_unfolded->SetMaximum(100);
  hist_rapidity_data_unfolded->SetMinimum(0);
  
  make_hist(hist_rapidity_data_unfolded, x_title, y_title, 20, 1.0, data_unfold_color, 1, 2);
  make_hist(hist_rapidity_mc_gen, x_title, y_title, 20, 1.0, mc_gen_color, 1, 2);
  
  auto hist_rapidity_data_unfolded_syst = get_stat_uncertainty_hist(hist_rapidity_data_unfolded);
  auto hist_rapidity_mc_gen_syst = get_stat_uncertainty_hist(hist_rapidity_mc_gen, syst_uncertainty_mc);
  
  canvas->cd();
  pads[0]->Draw();
  pads[0]->cd();
//  canvas->cd();
  hist_rapidity_data_unfolded_syst->Draw("e2");
  hist_rapidity_data_unfolded->Draw("psameex0");
  hist_rapidity_mc_gen_syst->Draw("e2same");
  hist_rapidity_mc_gen->Draw("histsamex0");
  
  canvas->cd();
  pads[1]->Draw();
  pads[1]->cd();
  TH1D *hist_rapidity_ratio = get_ratio(hist_rapidity_data_unfolded, hist_rapidity_mc_gen);
  auto hist_rapidity_ratio_syst = get_stat_uncertainty_hist(hist_rapidity_ratio);
  hist_rapidity_ratio->Draw("pex0");
  hist_rapidity_ratio_syst->Draw("e2same");
  
  auto line = new TF1("line", "1", 0, 100);
  line->SetLineColor(kBlack);
  line->SetLineStyle(2);
  line->DrawCopy("same");
  
  
  //invmass
  x_title = "m_{#gamma#gamma} (GeV)";
  y_title = "d#sigma_{#gamma#gamma}/dm_{#gamma#gamma} (nb / 2 GeV)";
  
  hist_invmass_data_unfolded->SetMaximum(50);
  hist_invmass_data_unfolded->SetMinimum(0);
  
  make_hist(hist_invmass_data_unfolded, x_title, y_title, 20, 1.0, data_unfold_color, 1, 2);
  make_hist(hist_invmass_mc_gen, x_title, y_title, 20, 1.0, mc_gen_color, 1, 2);
  auto hist_invmass_data_unfolded_syst = get_stat_uncertainty_hist(hist_invmass_data_unfolded);
  auto hist_invmass_mc_gen_syst = get_stat_uncertainty_hist(hist_invmass_mc_gen, syst_uncertainty_mc);
  
  canvas->cd();
  pads[2]->Draw();
  pads[2]->cd();
  hist_invmass_data_unfolded_syst->Draw("e2");
  hist_invmass_data_unfolded->Draw("psameex0");
  hist_invmass_mc_gen_syst->Draw("e2same");
  hist_invmass_mc_gen->Draw("histsamex0");
  
  legend->Draw();
  
  canvas->cd();
  pads[3]->Draw();
  pads[3]->cd();
  TH1D *hist_invmass_ratio = get_ratio(hist_invmass_data_unfolded, hist_invmass_mc_gen);
  auto hist_invmass_ratio_syst = get_stat_uncertainty_hist(hist_invmass_ratio);
  hist_invmass_ratio->Draw("pex0");
  hist_invmass_ratio_syst->Draw("e2same");
  line->DrawCopy("same");
  
  //CMS_lumi( canvas_mass, 1, 10 );
  
  canvas->SaveAs("./fig/diphoton_unfolding_ratios.pdf");
}

void make_hist(TH1D *& hist, string xtitle, string ytitle, int kstyle, float ksize, Color_t kcolor, int lstyle, int lwidth){
  // For the axis labels:
  hist->SetLabelColor(1, "XYZ");
  hist->SetLabelFont(42, "XYZ");
  hist->SetLabelOffset(0.007, "XYZ");
  hist->SetLabelSize(0.05, "XYZ");
  
  // For the axis titles:
  hist->SetTitleFont(42, "XYZ");
  hist->SetTitleSize(0.06, "XYZ");
  hist->GetXaxis()->SetTitleOffset(0.9);
  hist->GetYaxis()->SetTitleOffset(1.0);
  hist->SetMarkerColor(kcolor);
  hist->SetLineColor(kcolor);
  hist->SetMarkerStyle(kstyle);
  hist->SetMarkerSize(ksize);
  hist->GetYaxis()->SetTitle(ytitle.c_str());
  hist->GetXaxis()->SetTitle(xtitle.c_str());
  hist->SetLineStyle(lstyle);
  hist->SetLineWidth(lwidth);
}

TH1D* get_stat_uncertainty_hist(TH1D *input_hist, double uncertainty = syst_uncertainty){
  
  TH1D *output_hist = (TH1D*)input_hist->Clone();
  
  for(int iBin=1; iBin<=output_hist->GetNbinsX(); iBin++){
    double value = output_hist->GetBinContent(iBin);
    output_hist->SetBinError(iBin, uncertainty * value);
  }
  
  output_hist->SetFillColorAlpha(input_hist->GetLineColor(), 0.2);
  return output_hist;
}

void prepare_canvas(TCanvas *canvas){
  float T = 0.08;
  float B = 0.14;
  float L = 0.14;
  float R = 0.04;
  
  canvas->SetFillColor(0);
  canvas->SetBorderMode(0);
  canvas->SetFrameFillStyle(0);
  canvas->SetFrameBorderMode(0);
  canvas->SetLeftMargin( L );
  canvas->SetRightMargin( R );
  canvas->SetTopMargin( T );
  canvas->SetBottomMargin( B );
  canvas->SetTickx(0);
  canvas->SetTicky(0);
}

vector<TPad*> get_pads(){
  
  vector<TPad*> pads;
  
  double right_margin = 0.05;
  
  auto pad_0 = new TPad("pad_0", "pad_0", 0.0, 0.25, 0.5, 1.00);
  pad_0->SetBottomMargin(0);
  pad_0->SetRightMargin(right_margin);
  
  auto pad_1 = new TPad("pad_1", "pad_1", 0.0, 0.00, 0.5, 0.25);
  pad_1->SetTopMargin(0);
  pad_1->SetBottomMargin(0.3);
  pad_1->SetRightMargin(right_margin);
  
  auto pad_2 = new TPad("pad_2", "pad_2", 0.5, 0.25, 1.0, 1.0);
  pad_2->SetBottomMargin(0);
  pad_2->SetRightMargin(right_margin);
  
  auto pad_3 = new TPad("pad_3", "pad_3", 0.5, 0.00, 1.0, 0.25);
  pad_3->SetTopMargin(0);
  pad_3->SetBottomMargin(0.3);
  pad_3->SetRightMargin(right_margin);
  
  pads.push_back(pad_0);
  pads.push_back(pad_1);
  pads.push_back(pad_2);
  pads.push_back(pad_3);
  
  return pads;
}

TH1D* get_ratio(TH1D *hist_num, TH1D* hist_den){
  auto hist_ratio = (TH1D*)hist_num->Clone();
  hist_ratio->Divide(hist_den);
  
  hist_ratio->SetMinimum(0.5);
  hist_ratio->SetMaximum(1.5);
  
  hist_ratio->GetXaxis()->SetTitleFont(43);
  hist_ratio->GetXaxis()->SetTitleSize(20);
  hist_ratio->GetXaxis()->SetTitleOffset(4);
  hist_ratio->GetXaxis()->SetLabelFont(43);
  hist_ratio->GetXaxis()->SetLabelSize(20);
  
  hist_ratio->GetYaxis()->SetTitle("Ratio Data/MC");
  hist_ratio->GetYaxis()->SetTitleFont(43);
  hist_ratio->GetYaxis()->SetTitleSize(20);
  hist_ratio->GetYaxis()->SetTitleOffset(2);
  hist_ratio->GetYaxis()->SetLabelFont(43);
  hist_ratio->GetYaxis()->SetLabelSize(20);
  hist_ratio->GetYaxis()->SetNdivisions(5);
  
  
  
  return hist_ratio;
}
