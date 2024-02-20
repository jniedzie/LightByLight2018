#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TCut.h"
#include "TChain.h"
#include "TFitResult.h"
#include <TMath.h>
#include <TLegend.h>
#include <TLatex.h>
#include "TStyle.h"

double getError(double A, double eA, double B, double eB);

void fit_aco_hf_eff() {

  TH1::SetDefaultSumw2();

  TFile *data = new TFile("/eos/cms/store/group/phys_heavyions/rchudasa/lbyl_2018/analysis_ruchi/hfVeto_eff/hfveto_eff_data_elePt2_dielePt1.root","r");  
  //TFile *data = new TFile("/eos/cms/store/group/phys_heavyions/rchudasa/lbyl_2018/analysis_ruchi/hfVeto_eff/hfveto_eff_mc_elePt2_dielePt1.root","r");  
  
   
  //// data histogram 
 TH1D* hacop_with_hf        = (TH1D*)data->Get("trigger_HFveto_eff_vs_acoplanarity_num_Data");
 TH1D* hacop_wo_hf          = (TH1D*)data->Get("trigger_HFveto_eff_vs_acoplanarity_den_Data");

  //TH1D* hacop_with_hf        = (TH1D*)data->Get("trigger_HFveto_eff_vs_acoplanarity_num_QED_SC");
  //TH1D* hacop_wo_hf          = (TH1D*)data->Get("trigger_HFveto_eff_vs_acoplanarity_den_QED_SC");
  

   TF1 *fexp = new TF1("fexp","[0]*exp(-[1]*x) + [2]*exp(-[3]*x)",0,0.05);
   fexp->SetParNames("Norm_sig","Decay_sig","Norm_bkg","Decay_bkg");
   fexp->SetParameters(1.5e4,6.8e2,2e2,1.2e1);

   // normalise MC: force the data and MC integrals to be the same within acop<0.01
   double num_data_err, den_data_err;

   double num_data = hacop_with_hf->IntegralAndError(1,5,num_data_err);
   double den_data = hacop_wo_hf->IntegralAndError(1,5,den_data_err);

  cout <<"Eff:" << num_data/den_data << " +/-" << getError(num_data,num_data_err,den_data,den_data_err) << endl;

 

  int W = 700;
  int H = 600;
  
  float T = 0.08;
  float B = 0.14; 
  float L = 0.14;
  float R = 0.04;

  TLegend *leg1=new TLegend(0.5974212,0.7944251,0.9971347,0.8954704,NULL,"brNDC");
  leg1->SetFillColor(0);
  leg1->SetBorderSize(0);
  leg1->SetFillStyle(0);
  leg1->SetTextFont(43);
  leg1->SetTextSize(24);
  leg1->AddEntry(hacop_wo_hf,"Denominator ","pl");
  leg1->AddEntry(hacop_with_hf,"Numerator","pl");



  //// Diphoton invmass......................
  TCanvas* c1 = new TCanvas("c1","Reco efficiency",50,50,W,H);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetFrameFillStyle(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin( L );
  c1->SetRightMargin( R );
  c1->SetTopMargin( T );
  c1->SetBottomMargin( B );
  c1->SetTickx(0);
  c1->SetTicky(0);
  
  c1->cd();
   c1->SetLogy();
   hacop_with_hf->SetMarkerColor(kBlack);
   hacop_with_hf->SetLineColor(kBlack);
   hacop_with_hf->GetYaxis()->SetTitle("Events");
   hacop_with_hf->GetXaxis()->SetTitle("A_{#phi}(e^{+}e^{-})");
   hacop_with_hf->Draw("p");
   hacop_wo_hf->SetMarkerColor(kRed);
   hacop_wo_hf->SetLineColor(kRed);
   hacop_wo_hf->Draw("psame");
   hacop_wo_hf->GetXaxis()->SetTitle("Acoplanarity");
   leg1->Draw();


   // fit with hf data here.................

  /* TFitResultPtr r = hacop_with_hf->Fit(fexp,"ILEMS");
   c1->RedrawAxis();

   const double *params = r->GetParams();
   // get the total
   params = r->GetParams();
   for (int i=0; i<4; i++) fexp->SetParameter(i,params[i]);
   double inttot = fexp->Integral(0,0.01);
   double inttot_err = fexp->IntegralError(0,0.01,params,r->GetCovarianceMatrix().GetMatrixArray());
   // set the bkg part to 0, to get the sig part
   double params2[4];
   params2[0] = params[0];
   params2[1] = params[1];
   params2[2] = 0;
   params2[3] = 0;
   for (int i=0; i<4; i++) fexp->SetParameter(i,params2[i]);
   double intsig = fexp->Integral(0,0.01);
   double intsig_err = fexp->IntegralError(0,0.01,params2,r->GetCovarianceMatrix().GetMatrixArray());

 


   // **********************************************************************************
   // fit wo hf data here.................


   TF1 *fexp2 = new TF1("fexp2","[0]*exp(-[1]*x) + [2]*exp(-[3]*x)",0,0.06);
   fexp2->SetParNames("Norm_sig","Decay_sig","Norm_bkg","Decay_bkg");
   fexp2->SetParameters(1.5e4,6.8e2,2e2,1.2e1);

   TFitResultPtr r1 = hacop_wo_hf->Fit(fexp2,"ILEMS");
   c1->RedrawAxis();

   const double *params3 = r1->GetParams();
   // get the total
   params3 = r1->GetParams();
   for (int ii=0; ii<4; ii++) fexp2->SetParameter(ii,params3[ii]);
   double inttot2     = fexp2->Integral(0,0.01);
   double inttot2_err = fexp2->IntegralError(0,0.01,params3,r1->GetCovarianceMatrix().GetMatrixArray());
   // set the bkg part to 0, to get the sig part
   double params4[4];
   params4[0] = params3[0];
   params4[1] = params3[1];
   params4[2] = 0;
   params4[3] = 0;
   for (int ii=0; ii<4; ii++) fexp2->SetParameter(ii,params4[ii]);
   double intsig2     = fexp2->Integral(0,0.01);
   double intsig2_err = fexp2->IntegralError(0,0.01,params4,r1->GetCovarianceMatrix().GetMatrixArray());

   // get the purity

   double purity_fit = intsig / inttot;
   double purity_fit_err = purity_fit * sqrt(pow(intsig_err/intsig,2)+pow(inttot_err/inttot,2)-2.*pow(inttot_err,2)/(intsig*inttot));
   cout << "With hf:"<< intsig << " +/- " << intsig_err << endl;
   //cout << "Purity according to the fit: " << purity_fit << " +/- " << purity_fit_err << endl;


   // according to the fit
   double purity_fit2 = intsig2 / inttot2;
   double purity_fit2_err = purity_fit2 * sqrt(pow(intsig2_err/intsig2,2)+pow(inttot2_err/inttot2,2)-2.*pow(inttot2_err,2)/(intsig2*inttot2));
   cout << "Wo hf:"<< intsig2 << " +/- " << intsig2_err << endl;
   //cout << "Purity according to the fit: " << purity_fit2 << " +/- " << purity_fit2_err << endl;


   double efficiency = intsig/ intsig2;
   double eff_err = efficiency * sqrt(pow(intsig2_err/intsig2,2)+pow(intsig_err/intsig,2));
   cout <<"Efficiency:" << efficiency << " +/- " << eff_err << endl;
 
   // according to counting
   //double purity_cnt2 = intsig2 / norm_data;
   //double purity_cnt_err = purity_cnt * sqrt(pow(intsig_err/intsig,2)+pow(norm_data_err/norm_data,2)-2.*pow(intsig_err,2)/(intsig*norm_data));
   //cout << norm_data << " " << inttot << endl;
   //cout << "Purity according to the counting: " << purity_cnt << " +/- " << purity_cnt_err << endl;
*/

}

//Ratio Error
double getError(double A, double eA, double B, double eB){
  double f=A/B;
  double fA=eA/A;
  double fB=eB/B;
  double eR=  f*sqrt( (fA*fA + fB*fB )) ;
  return eR;
}
