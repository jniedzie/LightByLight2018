#ifndef toyStudy_h
#define toyStudy_h

#include "TGraphAsymmErrors.h"
#include "TF1.h"
#include "TRandom.h"
#include "TMath.h"
#include "TString.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TH1F.h"
#include "TArrow.h"

#include <fstream>

const int nToys = 1;

double assym_gaus(double *x, double *par) {
   double mean = par[0];
   double sigmal = par[1];
   double sigmah = par[2];

   // beware, sometimes one of the two parameters is 0... that's bad
   if (sigmal<1e-3) sigmal = max(1e-3, sigmah);
   if (sigmah<1e-3) sigmah = max(1e-3, sigmal);

   if ((x[0] < mean))
      return TMath::Gaus(x[0],mean,sigmal,kTRUE);
   else
      return TMath::Gaus(x[0],mean,sigmah,kTRUE);
};

void toyStudy(TGraphAsymmErrors *gdata, TGraphAsymmErrors *gmc, TF1 *fdata, TF1 *fmc, TString outputname) {
   const int nbinsdata = gdata->GetN();
   const double *xdata = gdata->GetX();
   const double *exldata = gdata->GetEXlow();
   const double *exhdata = gdata->GetEXhigh();
   const double *ydata = gdata->GetY();
   const double *eyldata = gdata->GetEYlow();
   const double *eyhdata = gdata->GetEYhigh();
   const int nbinsmc = gmc->GetN();
   const double *xmc = gmc->GetX();
   const double *exlmc = gmc->GetEXlow();
   const double *exhmc = gmc->GetEXhigh();
   const double *ymc = gmc->GetY();
   const double *eylmc = gmc->GetEYlow();
   const double *eyhmc = gmc->GetEYhigh();

   TF1 *tfAsyGauss = new TF1("tfAsy",assym_gaus,0,1.0,3);
   // tfAsyGauss->SetNpx(1000);

   ofstream fileout(TString("correction_functions_toys_") + outputname + ".txt");
   TFile *tfileout = new TFile(TString("correction_functions_toys_") + outputname + ".root","RECREATE");
   tfileout->cd();

   float *effdata = new float[nbinsdata];
   float *effdata_fit = new float[nbinsdata];
   float *effmc = new float[nbinsmc];
   float *effmc_fit = new float[nbinsmc];

   TTree *tr = new TTree("tr","tr");
   tr->Branch("effdata",effdata,Form("effdata[%i]/F",nbinsdata));
   tr->Branch("effdata_fit",effdata_fit,Form("effdata_fit[%i]/F",nbinsdata));
   tr->Branch("effmc",effmc,Form("effmc[%i]/F",nbinsmc));
   tr->Branch("effmc_fit",effmc_fit,Form("effmc_fit[%i]/F",nbinsmc));

   TCanvas *cdata = new TCanvas("cdata");
   TCanvas *cmc = new TCanvas("cmc");
   TH1F *hPad = new TH1F("hPad",";p^{#mu}_{T} [GeV/c];Single #mu Efficiency",5,0,30);
   hPad->GetXaxis()->CenterTitle();
   hPad->GetXaxis()->SetLabelSize(0.05);
   hPad->GetXaxis()->SetTitleSize(0.05);
   hPad->GetXaxis()->SetTitleOffset(1.2);
   hPad->GetYaxis()->SetLabelSize(0.05);
   hPad->GetYaxis()->SetTitleSize(0.05);
   hPad->GetYaxis()->SetTitleOffset(1.);
   hPad->GetYaxis()->SetRangeUser(0.,1.05);
   cdata->cd(); hPad->Draw();
   cmc->cd(); hPad->Draw();

   for (int i=0; i<nToys; i++) {
      // generate the toys
      // data
      TGraphAsymmErrors *gtoydata = new TGraphAsymmErrors(nbinsdata,xdata,ydata,exldata,exhdata,eyldata,eyhdata);
      for (int j=0; j<nbinsdata; j++) {
         tfAsyGauss->SetParameters(ydata[j],eyldata[j],eyhdata[j]);
         effdata[j] = tfAsyGauss->GetRandom();
         gtoydata->SetPoint(j,xdata[j],effdata[j]);
      }

      // mc
      TGraphAsymmErrors *gtoymc = new TGraphAsymmErrors(nbinsmc,xmc,ymc,exlmc,exhmc,eylmc,eyhmc);
      for (int j=0; j<nbinsmc; j++) {
         tfAsyGauss->SetParameters(ymc[j],eylmc[j],eyhmc[j]);
         effmc[j] = tfAsyGauss->GetRandom();
         gtoymc->SetPoint(j,xmc[j],effmc[j]);
      }

      // fit the graphs
      TF1 *ftoydata = (TF1*) fdata->Clone(Form("ftoydata%i",i));
      ftoydata->SetLineColor(kOrange+7);
      // ftoydata->SetParameter(2,gtoydata->GetX()[nbinsdata]);
      TF1 *ftoymc = (TF1*) fmc->Clone(Form("ftoymc%i",i));
      ftoymc->SetLineColor(kBlack);
      // ftoymc->SetParameter(2,gtoymc->GetX()[nbinsmc]);

      gtoydata->Fit(ftoydata,"WRM");
      gtoymc->Fit(ftoymc,"WRM");

      // compute the efficiency from fit, for the tree
      for (int j=0; j<nbinsdata; j++) {
         effdata_fit[j] = ftoydata->Eval(xdata[j]);
      }
      for (int j=0; j<nbinsmc; j++) {
         effmc_fit[j] = ftoymc->Eval(xmc[j]);
      }

      // draw
      cdata->cd();
      ftoydata->Draw("l same");
      cmc->cd();
      ftoymc->Draw("l same");

      // print results to file
      fileout << Form("%0.4f*TMath::Erf((x-%0.4f)/%0.4f)",ftoydata->GetParameter(0),ftoydata->GetParameter(1),ftoydata->GetParameter(2)) << endl;
      // fileout << Form("%0.4f*TMath::Erf((x-%0.4f)/%0.4f)",ftoymc->GetParameter(0),ftoymc->GetParameter(1),ftoymc->GetParameter(2)) << endl;
      tr->Fill();
   }


   // superimpose nominal results
   cdata->cd();
   gdata->Draw("pz same");
   fdata->Draw("l same");
   TLegend *tlegdata = new TLegend(0.6,0.2,0.9,0.4);
   tlegdata->AddEntry(gdata,"Data","lp");
   tlegdata->AddEntry(fdata,"Nominal fit","lp");
   tlegdata->Draw();
   cmc->cd();
   gmc->Draw("pz same");
   fmc->Draw("l same");
   TLegend *tlegmc = new TLegend(0.6,0.2,0.9,0.4);
   tlegmc->AddEntry(gmc,"MC","lp");
   tlegmc->AddEntry(fmc,"Nominal fit","lp");
   tlegmc->Draw();

   cdata->SaveAs(TString("toysdata_") + outputname + ".pdf");
   cmc->SaveAs(TString("toysmc_") + outputname + ".pdf");

   // plot the efficiency distribution for each bin
   TCanvas *cdata_dists = new TCanvas("cdata_dists","cdata_dists",1670,560);
   cdata_dists->Divide(nbinsdata/2,2);
   for (int j=0; j<nbinsdata; j++) {
      cdata_dists->cd(j+1);
      TString hname = Form("distdata%i",j);
      TString hname_fit = Form("distdata%i_fit",j);
      double xmin = min(ydata[j]-5.*eyldata[j], fdata->Eval(xdata[j])-5.*eyldata[j]);
      double xmax = max(ydata[j]+5.*eyldata[j], fdata->Eval(xdata[j])+5.*eyldata[j]);
      TH1F *hdist = new TH1F(hname,hname,10,xmin,xmax);
      hdist->GetXaxis()->SetTitle("Efficiency"); hdist->GetYaxis()->SetTitle("Counts");
      hdist->SetLineColor(kBlue); hdist->SetMarkerColor(kBlue);
      TH1F *hdist_fit = new TH1F(hname_fit,hname_fit,10,ydata[j]-5.*eyldata[j],ydata[j]+5.*eyhdata[j]);
      hdist_fit->GetXaxis()->SetTitle("Efficiency"); hdist_fit->GetYaxis()->SetTitle("Counts");
      hdist_fit->SetLineColor(kCyan); hdist_fit->SetMarkerColor(kCyan);
      tr->Draw(Form("effdata[%i]>>",j) + hname);
      tr->Draw(Form("effdata_fit[%i]>>",j) + hname_fit);
      hdist->Draw(); hdist->GetYaxis()->SetRangeUser(0,100); 
      hdist_fit->Draw("same");
      if (j==0) {
         TLegend *tleg = new TLegend(0.7,0.7,0.9,0.9);
         tleg->AddEntry(hdist,"Toys","lp");
         tleg->AddEntry(hdist_fit,"Fit","lp");
         tleg->Draw();
      }
      TLatex *lt1 = new TLatex();
      lt1->SetNDC();
      lt1->DrawLatex(0.43,0.95,Form("p_{T} #in [%.1f,%.1f]",xdata[j]-exldata[j],xdata[j]+exhdata[j]));

      // represent the input for these distribitions
      TArrow *arrlow = new TArrow(ydata[j],70.,ydata[j]-eyldata[j],70.,0.01,"|->");
      arrlow->SetLineColor(kBlue); arrlow->Draw();
      TArrow *arrhigh = new TArrow(ydata[j],70.,ydata[j]+eyhdata[j],70.,0.01,"|->");
      arrhigh->SetLineColor(kBlue); arrhigh->Draw();
      TArrow *arrfit = new TArrow(fdata->Eval(xdata[j]),50.,fdata->Eval(xdata[j]),0.,0.01,"->");
      arrfit->SetLineColor(kCyan); arrfit->Draw();
   }
   cdata_dists->SaveAs(TString("toysdata_dists_") + outputname + ".pdf");

   TCanvas *cmc_dists = new TCanvas("cmc_dists","cmc_dists",1670,560);
   cmc_dists->Divide(nbinsmc/2,2);
   for (int j=0; j<nbinsmc; j++) {
      cmc_dists->cd(j+1);
      TString hname = Form("distmc%i",j);
      TString hname_fit = Form("distmc%i_fit",j);
      double xmin = min(ymc[j]-5.*eylmc[j], fmc->Eval(xmc[j])-5.*eylmc[j]);
      double xmax = max(ymc[j]+5.*eylmc[j], fmc->Eval(xmc[j])+5.*eylmc[j]);
      TH1F *hdist = new TH1F(hname,hname,10,xmin,xmax);
      hdist->GetXaxis()->SetTitle("Efficiency"); hdist->GetYaxis()->SetTitle("Counts");
      hdist->SetLineColor(kRed); hdist->SetMarkerColor(kRed);
      TH1F *hdist_fit = new TH1F(hname_fit,hname_fit,10,ymc[j]-5.*eylmc[j],ymc[j]+5.*eyhmc[j]);
      hdist_fit->GetXaxis()->SetTitle("Efficiency"); hdist_fit->GetYaxis()->SetTitle("Counts");
      hdist_fit->SetLineColor(kMagenta); hdist_fit->SetMarkerColor(kMagenta);
      tr->Draw(Form("effmc[%i]>>",j) + hname);
      tr->Draw(Form("effmc_fit[%i]>>",j) + hname_fit);
      hdist->Draw(); hdist->GetYaxis()->SetRangeUser(0,100);
      hdist_fit->Draw("same");
      if (j==0) {
         TLegend *tleg = new TLegend(0.7,0.7,0.9,0.9);
         tleg->AddEntry(hdist,"Toys","lp");
         tleg->AddEntry(hdist_fit,"Fit","lp");
         tleg->Draw();
      }
      TLatex *lt1 = new TLatex();
      lt1->SetNDC();
      lt1->DrawLatex(0.43,0.95,Form("p_{T} #in [%.1f,%.1f]",xmc[j]-exlmc[j],xmc[j]+exhmc[j]));

      // represent the input for these distribitions
      TArrow *arrlow = new TArrow(ymc[j],70.,ymc[j]-eylmc[j],70.,0.01,"|->");
      arrlow->SetLineColor(kRed); arrlow->Draw();
      TArrow *arrhigh = new TArrow(ymc[j],70.,ymc[j]+eyhmc[j],70.,0.01,"|->");
      arrhigh->SetLineColor(kRed); arrhigh->Draw();
      TArrow *arrfit = new TArrow(fmc->Eval(xmc[j]),50.,fmc->Eval(xmc[j]),0.,0.01,"->");
      arrfit->SetLineColor(kMagenta); arrfit->Draw();
   }
   cmc_dists->SaveAs(TString("toysmc_dists_") + outputname + ".pdf");

   // write and close open files
   fileout.close();
   tfileout->Write();
   tfileout->Close();

   // more cleaning
   delete cdata, cmc;
   delete cdata_dists, cmc_dists;
};

#endif // #ifndef toyStudy_h
