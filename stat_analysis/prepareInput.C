#include "TFile.h"
#include "TH1D.h"

void prepareInput(const char* filename, const char* varname) {
   TFile *fin = TFile::Open(filename);

   TH1D *hdata = (TH1D*) fin->Get(Form("%s_data",varname))->Clone("data_obs");
   TH1D *hlbyl;
   if (fin->Get(Form("%s_lbyl",varname))) hlbyl = (TH1D*) fin->Get(Form("%s_lbyl",varname))->Clone("lbyl");
   else hlbyl = (TH1D*) fin->Get(Form("%s_lbyl_stack_3",varname))->Clone("lbyl");
   TH1D *hqed;
   if (fin->Get(Form("%s_qed",varname))) hqed = (TH1D*) fin->Get(Form("%s_qed",varname))->Clone("qed");
   else hqed = (TH1D*) fin->Get(Form("%s_qed_stack_1",varname))->Clone("qed");
   TH1D *hcep;
   if (fin->Get(Form("%s_cep",varname))) hcep = (TH1D*) fin->Get(Form("%s_cep",varname))->Clone("cep");
   else hcep = (TH1D*) fin->Get(Form("%s_cep_stack_2",varname))->Clone("cep");
   
   double factor = 363.959/391;//370.884/391.; // correct the lumi
   double factorx = pow(1.05*0.987,2)*1.12/1.09; // 138./123.; // correct the xsec // but now the correct xsec is used already, but need to account for trigger SF and reco-ID SF for photons
   hlbyl->Scale(factor*factorx);
   hcep->Scale(factor);
   hqed->Scale(factor);

   // special case of mass (for axion searches): include overflow as an actual mass bin, form 20 to 200 GeV
   if (TString(varname)=="hinvmass") {
      const int nbins = 7;
      double massbins[8] = {5,7.5,10,12.5,15,17.5,20,200};

      TH1D *hdata_orig = hdata;
      hdata_orig->SetName("hdata_orig");
      hdata = new TH1D("data_obs","",nbins,massbins);
      TH1D *hlbyl_orig = hlbyl;
      hlbyl_orig->SetName("hlbyl_orig");
      hlbyl = new TH1D("lbyl","",nbins,massbins);
      TH1D *hcep_orig = hcep;
      hcep_orig->SetName("hcep_orig");
      hcep = new TH1D("cep","",nbins,massbins);
      TH1D *hqed_orig = hqed;
      hqed_orig->SetName("hqed_orig");
      hqed = new TH1D("qed","",nbins,massbins);
      for (int i=0; i<=nbins; i++) {
         hdata->SetBinContent(i,hdata_orig->GetBinContent(i));
         hdata->SetBinError(i,hdata_orig->GetBinError(i));
         hlbyl->SetBinContent(i,hlbyl_orig->GetBinContent(i));
         hlbyl->SetBinError(i,hlbyl_orig->GetBinError(i));
         // hlbyl->SetBinError(i,1e-10);
         hcep->SetBinContent(i,hcep_orig->GetBinContent(i));
         hcep->SetBinError(i,hcep_orig->GetBinError(i));
         // hcep->SetBinError(i,1e-10);
         hqed->SetBinContent(i,hqed_orig->GetBinContent(i));
         hqed->SetBinError(i,hqed_orig->GetBinError(i));
         // hqed->SetBinError(i,1e-10);
      }
   }

   TFile *fout = new TFile(Form("input_%s.root",varname),"RECREATE");
   hdata->Write();
   hlbyl->Write();
   hcep->Write();
   hqed->Write();

   cout << "data: " << hdata->Integral(1,hdata->GetNbinsX()) << endl;
   cout << "lbyl: " << hlbyl->Integral(1,hlbyl->GetNbinsX()) << endl;
   cout << "cep: " << hcep->Integral(1,hcep->GetNbinsX()) << endl;
   cout << "qed: " << hqed->Integral(1,hqed->GetNbinsX()) << endl;

   // // let's implement Barlow-Beeston by hand
   // double norm_lbl = hlbyl->Integral()/hlbyl->GetEntries();
   // double norm_cep = hcep->Integral()/hcep->GetEntries();
   // double norm_qed = hqed->Integral()/hqed->GetEntries();

   // const double alpha = 1 - 0.6827;;
   // for (int i=1; i<=hlbyl->GetNbinsX(); i++) {
   //    double ntot=0, etot=0;
   //    
   //    int binc = hlbyl->GetBinContent(i)/norm_lbl;
   //    ntot += binc;
   //    double bincup = ROOT::Math::gamma_quantile_c(alpha/2,binc+1,1.);
   //    double bincdown = (binc==0) ? 0  : (ROOT::Math::gamma_quantile(alpha/2,binc,1.));
   //    etot += (bincup-bincdown)/2.;
   //    if (ntot>0) cout << "mcsigstats_bin" << i << "  lnN  " << 1.+etot/ntot << "    -     -   signal MC stats bin " << i << endl;

   //    ntot=0;
   //    etot=0;

   //    binc = hcep->GetBinContent(i)/norm_cep;
   //    ntot += binc;
   //    bincup = ROOT::Math::gamma_quantile_c(alpha/2,binc+1,1.);
   //    bincdown = (binc==0) ? 0  : (ROOT::Math::gamma_quantile(alpha/2,binc,1.));
   //    etot += (bincup-bincdown)/2.;

   //    binc = hqed->GetBinContent(i)/norm_qed;
   //    ntot += binc;
   //    bincup = ROOT::Math::gamma_quantile_c(alpha/2,binc+1,1.);
   //    bincdown = (binc==0) ? 0  : (ROOT::Math::gamma_quantile(alpha/2,binc,1.));
   //    etot += (bincup-bincdown)/2.;
   //    cout << "mcstats_bin" << i << "  lnN  -    " << 1.+etot/ntot << "   " << 1.+etot/ntot << "   bkg MC stats bin " << i << endl;
   // }

   fout->Close();
   fin->Close();
}
