#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include <iostream>

using namespace std;

void prepareInputs_axion(int imass) {
   TFile *f = TFile::Open("input_hinvmass.root","UPDATE");
   // extend the mass range
   const int nbins = 7;
   double massbins[8] = {5,7.5,10,12.5,15,17.5,20,200};

   // arrays
   double mass[9] = {5, 6, 9, 11, 14, 16, 22, 30, 90};
   double acc[9] = {0.328, 0.763764, 0.830831, 0.873874, 0.895896, 0.916917, 0.941, 0.967968, 0.996997};
   double eff[9] = {0.089, 0.187, 0.327, 0.361, 0.389, 0.412, 0.409, 0.436, 0.367};
   double deff[9] = {0.5e-2, 0.5e-2, 0.7e-2, 0.7e-2, 0.8e-2, 0.8e-2, 0.7e-2, 0.8e-2, 0.7e-2};

   // functions for resolution
   TF1 *fm = new TF1("fm","[0]+[1]*exp([2]*x)",5,20);
   fm->SetParameters(9.24958e-01,6.17813e-01,-3.47891e-01);
   TF1 *fr = new TF1("fr","[0]+[1]*exp([2]*x)",5,20);
   fr->SetParameters(0.0909661,-0.207283,-0.307946);


   // function for efficiency
   TF1 fe("f","[0]*(1-exp((x-[1])/[2]))",0,30);
   fe.SetParameters(3.32406e-01,4.28904e+00,-2.64850e+00);
   // binned efficiencies for syst
   double x[8],y[8];
   x[0]=5.5; y[0]=0.105285;
   x[1]=6.5; y[1]=0.203834;
   x[2]=7.5; y[2]=0.241597;
   x[3]=9; y[3]=0.271701;
   x[4]=11; y[4]=0.288428;
   x[5]=13.5; y[5]=0.317935;
   x[6]=17.5; y[6]=0.366667;
   x[7]=25; y[7]=0.309735;
   TGraph g(8,x,y);

   double xsec = 10e-3; // mub
   double lumi = 363.959;//370.884;  // mub-1
   int nevts = 1e6;
   double sf = pow(1.05*0.987,2)*1.12/1.09;

   // generate histo based on mass scale and resolution
   // TH1D *h = new TH1D(Form("axion%d",imass),"",nbins,massbins);
   // TF1 *fgaus = new TF1("fgaus","gaus",0,200);
   // fgaus->SetParameters(1, mass[imass]*fm->Eval(mass[imass]), mass[imass]*fr->Eval(mass[imass]));
   // // h->FillRandom("fgaus",nevts);
   // for (int i=0; i<nevts; i++) {
   //    double m = fgaus->GetRandom();
   //    if (m<5) m=5;
   //    h->Fill(m);
   // }
   // // h->Scale(xsec*lumi*acc[imass]*fe.Eval(mass[imass])/nevts);
   // h->Scale(xsec*lumi*acc[imass]*eff[imass]/nevts);

   // get histo from full sim
   TFile *fax = TFile::Open("histos_alps_two_new_points.root");
   TH1D *hax = (TH1D*) fax->Get(Form("hinvmass%d",imass));
   // for (int ibin=1; ibin<7; ibin++) {
   //    h->SetBinContent(ibin,hax->GetBinContent(ibin+2));
   //    h->SetBinError(ibin,hax->GetBinContent(ibin+2));
   // }
   // double err=0;
   // double intg = hax->IntegralAndError(9,80,err);
   // h->SetBinContent(7,intg);
   // h->SetBinError(7,err);
   hax->Rebin(nbins,Form("axion%d",imass),massbins);
   TH1D *h = (TH1D*) gDirectory->Get(Form("axion%d",imass));

   cout << mass[imass] << ": " << h->Integral(1,nbins) << endl;;
   // cout << "syst eff: " << (fe.Eval(mass[imass])-g.Eval(mass[imass]))/fe.Eval(mass[imass]) << endl;
   cout << "syst eff: " << deff[imass]/eff[imass] << endl;

   f->cd();
   h->Write();
   f->Write();
   f->Close();
}

void prepareInputs_axion() {
   for (int i=0; i<9; i++) prepareInputs_axion(i);
}
