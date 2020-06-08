#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "CMS_lumi.C"
#include "tdrstyle.C"

const double excleff_hm        = 89.9e-2;
const double excleff_hm_stat   = 1.3e-2;
const double excleff_hm_syst   = 5.1e-2;
const double excleff_ged       = 89.5e-2;
const double excleff_ged_stat  = 1.3e-2;
const double excleff_ged_syst  = 5.03e-2;
const double xsec_3_53         = 1.086453e-01*20.6e3*4.82/4.73; // in mub
const double xsec_3_53_err     = (0.15/4.82)*xsec_3_53; // FIXME what is the uncertainty?
const double lumi_brilcalc     = 391; // in mub-1
const double lumi_brilcalc_err = 0.12*lumi_brilcalc;
const double sf_hm             = 0.98*0.98;//*0.931*0.928;
const double sf_hm_syst        = sqrt(pow(0.03,2)+pow(2*0.02,2));
// const double sf_ged            = 0.989*0.989*0.931*0.928;
const double sf_ged            = 0.98*0.98;//*0.931*0.928;//*1.09;
const double sf_ged_syst       = sqrt(pow(0.03,2)+pow(2*0.02,2));//+pow(0.003/0.931,2)+pow(0.020/0.928,2))*sf_ged;
const int    ngen              = (int) (2399759.*(290214.+98326.)/98326.);// scale old number of events by the new+old number of reco events // was 7929199;
const double acop_cut          = 0.06;
const double glob_syst         = 2.*(0.02/0.98); // reco+ID

TH1D* SFuncert(TTree *tr, const char* name, const char* var, const char* cut, int nbins, double binmin, double binmax, bool dorew=false);


void qedNorm(const char* type = "GED", double mass_cut=5) {
   TFile *fdata = TFile::Open("outputDataAll_noexcl.root");
   TFile *fmc = TFile::Open("outputMCAll_noexcl_OldAndNew.root");
   TTree *trdata = (TTree*) fdata->Get(Form("tr%s",type));
   TTree *trmc = (TTree*) fmc->Get(Form("tr%s",type));

   double sf, sf_err;
   if (TString(type)=="GED") {
      sf = sf_ged;
      sf_err = sf_ged_syst;
   } else {
      sf = sf_hm;
      sf_err = sf_hm_syst;
   }

   // estimate the purity in data
   TH1F *hacop_data = new TH1F("hacop_data",";Dielectron A_{#phi};Entries / (0.002)",30,0,acop_cut);
   // TH1F *hacop_mc = new TH1F("hacop_mc",";Acoplanarity;Entries / 0.002",30,0,acop_cut);
   trdata->Project(hacop_data->GetName(),"acop",Form("doubleEG2&&acop<%f&&mass>=%f&&pt<=1",acop_cut,mass_cut));
   // trmc->Project(hacop_mc->GetName(),"acop",Form("doubleEG2&&acop<%f&&mass>=%f&&pt<=1",acop_cut,mass_cut));
   TH1D *hacop_mc = SFuncert(trmc,"hacop_mc","acop",Form("doubleEG2&&acop<%f&&mass>=%f&&pt<=1",acop_cut,mass_cut),30,0,acop_cut,false);

   TF1 *fexp = new TF1("fexp","[0]*exp(-[1]*x) + [2]*exp(-[3]*x)",0,acop_cut);
   fexp->SetParNames("Norm_sig","Decay_sig","Norm_bkg","Decay_bkg");
   fexp->SetParameters(1.5e4,6.8e2,2e2,1.2e1);
   fexp->SetLineColor(kRed);

   // normalise MC: force the data and MC integrals to be the same within acop<0.01
   double norm_mc_err,norm_data_err;
   double norm_mc = hacop_mc->IntegralAndError(1,5,norm_mc_err,"width");
   double norm_data = hacop_data->IntegralAndError(1,5,norm_data_err,"width");
   cout << "Scaling MC by " << norm_mc << " / " << norm_data << " = " << norm_mc/norm_data << endl;
   hacop_mc->Scale(norm_data/norm_mc);
   hacop_mc->SetFillColor(kYellow);

   int W = 700;
   int H = 600;

   float T = 0.08;
   float B = 0.14;
   float L = 0.14;
   float R = 0.04;

   setTDRStyle();
   gROOT->SetStyle( "tdrStyle" );
   gStyle->SetNumberContours(100);

   TCanvas* c_aco = new TCanvas("c_aco","Acoplanarity",50,50,W,H);
   c_aco->SetFillColor(0);
   c_aco->SetBorderMode(0);
   c_aco->SetFrameFillStyle(0);
   c_aco->SetFrameBorderMode(0);
   // c_aco->SetLeftMargin( L );
   // c_aco->SetRightMargin( R );
   // c_aco->SetTopMargin( T );
   // c_aco->SetBottomMargin( B );
   c_aco->SetTickx(0);
   c_aco->SetTicky(0);
   gStyle->SetOptStat(0);
   gStyle->SetOptFit(0);
   c_aco->SetLogy();
   hacop_data->Draw();
   hacop_mc->Draw("hist same");
   TH1D *h2c = (TH1D*) hacop_mc->Clone();
   h2c->SetFillColor(kBlack);
   h2c->SetFillStyle(3005);
   h2c->SetMarkerSize(0);
   h2c->Draw("E2 same");
   hacop_data->Draw("same");
   TFitResultPtr r = hacop_data->Fit(fexp,"ILEMS");

   TLegend *tleg = new TLegend(0.3,0.6,0.7,0.9);
   tleg->SetBorderSize(0);
   tleg->AddEntry(hacop_data,"Data","LP");
   tleg->AddEntry(hacop_mc,"QED #gamma#gamma #rightarrow e^{+}e^{-} (MC)","F");
   tleg->AddEntry(fexp,"2-exponential fit to data","L");
   tleg->Draw();

   c_aco->RedrawAxis();
   CMS_lumi( c_aco, 104, 33,lumi_PbPb2015 );
   c_aco->SaveAs("acop_fit_prelim.C");
   c_aco->SaveAs("acop_fit_prelim.pdf");
   c_aco->SaveAs("acop_fit_prelim.root");

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

   // get the purity
   // according to the fit
   double purity_fit = intsig / inttot;
   double purity_fit_err = purity_fit * sqrt(pow(intsig_err/intsig,2)+pow(inttot_err/inttot,2)-2.*pow(inttot_err,2)/(intsig*inttot));
   // cout << intsig << " " << inttot << endl;
   // cout << intsig_err << " " << inttot_err << endl;
   cout << "Purity according to the fit: " << purity_fit << " +/- " << purity_fit_err << endl;

   // according to counting
   double purity_cnt = intsig / norm_data;
   double purity_cnt_err = purity_cnt * sqrt(pow(intsig_err/intsig,2)+pow(norm_data_err/norm_data,2)-2.*pow(intsig_err,2)/(intsig*norm_data));
   // cout << norm_data << " " << inttot << endl;
   cout << "Purity according to the counting: " << purity_cnt << " +/- " << purity_cnt_err << endl;

   // systematic uncertainty associated to this
   double purity_syst = sqrt(pow(purity_cnt-purity_fit,2) + pow(purity_fit_err,2));

   // compute the cross section
   cout << endl;
   double xsec = norm_data*purity_cnt*(ngen/(norm_mc*sf))/lumi_brilcalc;
   double xsec_stat = (norm_data_err/norm_data)*xsec;
   double xsec_lumi = (lumi_brilcalc_err/lumi_brilcalc)*xsec;
   double xsec_purity = (purity_syst/purity_cnt)*xsec;
   // double xsec_excl = (excleff_err/excleff)*xsec;
   double xsec_mcstat = (norm_mc_err/norm_mc)*xsec;
   double xsec_sf = sf_err*xsec; 
   double xsec_syst = sqrt(pow(xsec_lumi,2)+pow(xsec_purity,2)+pow(xsec_sf,2)+pow(xsec_mcstat,2));
   double xsec_syst_nolumi = sqrt(pow(xsec_purity,2)+pow(xsec_sf,2)+pow(xsec_mcstat,2));
   cout << "Cross section for QED e+e- 3<M<53GeV, in mub: " << endl;
   cout << "Generator: " << xsec_3_53 << " +/- " << xsec_3_53_err << endl;
   cout << "Data: " << endl;
   cout << xsec << " +/- " << sqrt(pow(xsec_stat,2)+pow(xsec_syst,2)) << " (tot)" << endl;
   cout << xsec << " +/- " << xsec_stat << " (stat) +/- " << xsec_syst << " (syst+lumi)" << endl;
   cout << xsec << " +/- " << xsec_stat << " (stat) +/- " << xsec_syst_nolumi << " (syst) +/- " << xsec_lumi << " (lumi)" << endl;
   cout << "Full list of uncertainties, in %:" << endl;
   cout << "stat: " << 100.*xsec_stat/xsec << endl;
   cout << "lumi: " << 100.*xsec_lumi/xsec << endl;
   cout << "purity: " << 100.*xsec_purity/xsec << endl;
   cout << "MC stat: " << 100.*xsec_mcstat/xsec << endl;
   cout << "data-driven eff: " << 100.*xsec_sf/xsec << endl;

   // compute the lumi
   cout << endl;
   double lumimeas = norm_data*purity_cnt*(ngen/(norm_mc*sf))/xsec_3_53;
   double lumimeas_stat = (norm_data_err/norm_data)*lumimeas;
   double lumimeas_xsec = (xsec_3_53_err/xsec_3_53)*lumimeas;
   double lumimeas_purity = (purity_syst/purity_cnt)*lumimeas;
   double lumimeas_mcstat = (norm_mc_err/norm_mc)*lumimeas;
   double lumimeas_sf = sf_err*lumimeas; 
   double lumimeas_syst = sqrt(pow(lumimeas_xsec,2)+pow(lumimeas_purity,2)+pow(lumimeas_sf,2)+pow(lumimeas_mcstat,2));
   double lumimeas_syst_noxsec = sqrt(pow(lumimeas_purity,2)+pow(lumimeas_sf,2)+pow(lumimeas_mcstat,2));
   cout << "Luminosity in mub-1: " << endl;
   cout << "Brilcalc: " << lumi_brilcalc << " +/- " << lumi_brilcalc_err << endl;
   cout << "Data: " << endl;
   cout << lumimeas << " +/- " << sqrt(pow(lumimeas_stat,2)+pow(lumimeas_syst,2)) << " (tot)" << endl;
   cout << lumimeas << " +/- " << lumimeas_stat << " (stat) +/- " << lumimeas_syst << " (syst+xsec)" << endl;
   cout << lumimeas << " +/- " << lumimeas_stat << " (stat) +/- " << lumimeas_syst_noxsec << " (syst) +/- " << lumimeas_xsec << " (xsec)" << endl;
   cout << "Full list of uncertainties, in %:" << endl;
   cout << "stat: " << 100.*lumimeas_stat/lumimeas << endl;
   cout << "xsec: " << 100.*lumimeas_xsec/lumimeas << endl;
   cout << "purity: " << 100.*lumimeas_purity/lumimeas << endl;
   cout << "MC stat: " << 100.*lumimeas_mcstat/lumimeas << endl;
   cout << "data-driven eff: " << 100.*lumimeas_sf/lumimeas << endl;

   // print also the ingredients
   cout << endl;
   cout << "Ingredients" << endl;
   double binwidth = hacop_data->GetBinWidth(1);
   cout << "Ndata: " << norm_data/binwidth << " +- " << norm_data_err/binwidth << endl;
   cout << "Purity: " << purity_cnt << " +- " << purity_syst << endl;
   cout << "Acc*eff: " << norm_mc/ngen/binwidth << " +- " << norm_mc_err/ngen/binwidth << endl;
   cout << "SF: " << sf << " +/- " << sf_err << endl;
}

TH1D* SFuncert(TTree *tr, const char* name, const char* var, const char* cut, int nbins, double binmin, double binmax, bool dorew) {
   TH1D *hvari[14];
   for (int ivar=0; ivar<14; ivar++) {
      TString namei = Form("%s_%d",name,ivar);
      hvari[ivar] = new TH1D(namei,"",nbins,binmin, binmax);
      tr->Project(namei,var,Form("SFweight[%d]*(%s)",ivar,cut));
   }

   TH1D *hans = new TH1D(name,"",nbins,binmin,binmax);
   if (dorew) hans = (TH1D*) hvari[0]->Clone(name);
   else tr->Project(name,var,cut); 

   for (int i=1; i<=hans->GetNbinsX(); i++) {
      double err=0;
      for (int ivar=1; ivar<14; ivar++) err += pow(hvari[ivar]->GetBinContent(i)-hvari[0]->GetBinContent(i),2);
      hans->SetBinError(i,sqrt(err+pow(hans->GetBinError(i),2)+pow(glob_syst,2)));
   }

   return hans;
}
