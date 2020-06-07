#include "CMS_lumi.C"
#include "MyCanvas.C"

const double xsec_3_53         = 1.086453e-01*20.6e3*4.82/4.73; // in mub
const double sf                = 0.98*0.98;
const int    ngen              = (int) (2399759.*(290214.+98326.)/98326.);// scale old number of events by the new+old number of reco events // was 7929199;
const double glob_syst         = 2.*(0.02/0.98); // reco+ID

TH1D* SFuncert(TTree *tr, const char* name, const char* var, const char* cut, int nbins, double binmin, double binmax, bool dorew=false);

void plotQED(TString algo="GED", double acop_cut=0.01, double luminosity=363.959, double mass_cut=5) {
   TFile *fdata = TFile::Open("outputDataAll_noexcl.root");
   TTree *trdata = (TTree*) fdata->Get("tr" + algo);
   // TFile *fMC = TFile::Open("outputMCAll.root");
   TFile *fMC = TFile::Open("outputMCAll_noexcl_OldAndNew.root");
   TTree *trMC = (TTree*) fMC->Get("tr" + algo);

   TH1D *hmass_data = new TH1D("hmass_data",";M (e^{+}e^{-}) (GeV);Entries / (2 GeV)",50,0,100);
   TH1D *hdeltapt_data = new TH1D("hdeltapt_data",";#Delta p_{T} (e^{+}e^{-}) (GeV);Entries / (1 GeV)",10,0,1);
   TH1D *hrap_data = new TH1D("hrap_data",";y (e^{+}e^{-});Entries / (0.2)",25,-2.5,2.5);
   TH1D *hpt_data = new TH1D("hpt_data",";p_{T} (e^{+}e^{-}) (GeV);Entries / (0.5 GeV)",20,0,1);
   TH1D *hacop_data = new TH1D("hacop_data",Form(";Dielectron A_{#phi};Entries / (%.4f)",acop_cut/20.),20,0,acop_cut);

   hmass_data->Sumw2(kFALSE);
   hdeltapt_data->Sumw2(kFALSE);
   hrap_data->Sumw2(kFALSE);
   hpt_data->Sumw2(kFALSE);
   hacop_data->Sumw2(kFALSE);

   trdata->Project(hmass_data->GetName(),"mass",Form("doubleEG2&&acop<%f&&mass>=%f&&pt<=1",acop_cut,mass_cut));
   trdata->Project(hdeltapt_data->GetName(),"deltapt",Form("doubleEG2&&acop<%f&&mass>=%f&&pt<=1",acop_cut,mass_cut));
   trdata->Project(hrap_data->GetName(),"rap",Form("doubleEG2&&acop<%f&&mass>=%f&&pt<=1",acop_cut,mass_cut));
   trdata->Project(hpt_data->GetName(),"pt",Form("doubleEG2&&acop<%f&&mass>=%f&&pt<=1",acop_cut,mass_cut));
   trdata->Project(hacop_data->GetName(),"acop",Form("doubleEG2&&acop<%f&&mass>=%f&&pt<=1",acop_cut,mass_cut));

   hmass_data->SetBinErrorOption(TH1::kPoisson);
   hdeltapt_data->SetBinErrorOption(TH1::kPoisson);
   hrap_data->SetBinErrorOption(TH1::kPoisson);
   hpt_data->SetBinErrorOption(TH1::kPoisson);
   hacop_data->SetBinErrorOption(TH1::kPoisson);

   TH1D *hmass_MC = SFuncert(trMC,"hmass_MC","mass",Form("doubleEG2&&acop<%f&&mass>=%f&&pt<=1",acop_cut,mass_cut),50,0,100);
   TH1D *hdeltapt_MC = SFuncert(trMC,"hdeltapt_MC","deltapt",Form("doubleEG2&&acop<%f&&mass>=%f&&pt<=1",acop_cut,mass_cut),10,0,1);
   TH1D *hrap_MC = SFuncert(trMC,"hrap_MC","rap",Form("doubleEG2&&acop<%f&&mass>=%f&&pt<=1",acop_cut,mass_cut),25,-2.5,2.5);
   TH1D *hpt_MC = SFuncert(trMC,"hpt_MC","pt",Form("doubleEG2&&acop<%f&&mass>=%f&&pt<=1",acop_cut,mass_cut),20,0,1);
   TH1D *hacop_MC = SFuncert(trMC,"hacop_MC","acop",Form("doubleEG2&&acop<%f&&mass>=%f&&pt<=1",acop_cut,mass_cut),20,0,acop_cut);

   // scale MC
   double xsec = xsec_3_53;
   hmass_MC->Scale(luminosity*xsec*sf/ngen); hmass_MC->SetLineColor(kBlack); hmass_MC->SetFillColor(kYellow);
   hdeltapt_MC->Scale(luminosity*xsec*sf/ngen); hdeltapt_MC->SetLineColor(kBlack); hdeltapt_MC->SetFillColor(kYellow);
   hrap_MC->Scale(luminosity*xsec*sf/ngen); hrap_MC->SetLineColor(kBlack); hrap_MC->SetFillColor(kYellow);
   hpt_MC->Scale(luminosity*xsec*sf/ngen); hpt_MC->SetLineColor(kBlack); hpt_MC->SetFillColor(kYellow);
   hacop_MC->Scale(luminosity*xsec*sf/ngen); hacop_MC->SetLineColor(kBlack); hacop_MC->SetFillColor(kYellow);

   int W = 700;
   int H = 600;

   float T = 0.08;
   float B = 0.14;
   float L = 0.14;
   float R = 0.04;

   MyCanvas mc1("mass","Dielectron invariant mass (GeV)", "Entries / (2 GeV)", W, H);
   mc1.SetLogy(false);
   mc1.SetYRange(0.1,9000);
   mc1.SetRatioRange(0.1,1.9);
   mc1.SetLegendPosition(0.3,0.68,0.7,0.85);
   mc1.CanvasWithHistogramsRatioPlot(hmass_data,hmass_MC,"Data","QED #gamma#gamma #rightarrow e^{+}e^{-} (MC)","Data/MC",kBlack,kYellow,kFALSE,kTRUE,"E0","hist SAME");
   mc1.PrintCanvas();
   mc1.PrintCanvas_C();

   MyCanvas mc2("deltapt","Dielectron #Delta p_{T} (GeV)", "Entries / (1GeV)", W, H);
   mc2.SetYRange(0.,4000);
   mc2.SetRatioRange(0.1,1.9);
   mc2.SetLegendPosition(0.3,0.68,0.6,0.85);
   mc2.CanvasWithHistogramsRatioPlot(hdeltapt_data,hdeltapt_MC,"Data","QED #gamma#gamma #rightarrow e^{+}e^{-} (MC)","Data/MC",kBlack,kYellow,kFALSE,kTRUE,"E0","hist SAME");
   mc2.PrintCanvas();
   mc2.PrintCanvas_C();

   MyCanvas mc3("rap","Dielectron y", "Entries / (0.2)", W, H);
   // mc3.SetLogy(false);
   mc3.SetYRange(0,1900);
   mc3.SetRatioRange(0.1,1.9);
   mc3.SetLegendPosition(0.16,0.68,0.56,0.85);
   mc3.CanvasWithHistogramsRatioPlot(hrap_data,hrap_MC,"Data","QED #gamma#gamma #rightarrow e^{+}e^{-} (MC)","Data/MC",kBlack,kYellow,kFALSE,kTRUE,"E0","hist SAME");
   mc3.PrintCanvas();
   mc3.PrintCanvas_C();

   MyCanvas mc4("pt","Dielectron p_{T} (GeV)", "Entries / (0.5 GeV)", W, H);
   // mc4.SetLogy(false);
   mc4.SetYRange(0.,2000);
   mc4.SetRatioRange(0.1,1.9);
   mc4.SetLegendPosition(0.3,0.68,0.7,0.85);
   mc4.CanvasWithHistogramsRatioPlot(hpt_data,hpt_MC,"Data","QED #gamma#gamma #rightarrow e^{+}e^{-} (MC)","Data/MC",kBlack,kYellow,kFALSE,kTRUE,"E0","hist SAME");
   mc4.PrintCanvas();
   mc4.PrintCanvas_C();

   MyCanvas mc5("acop","Dielectron A_{#phi}", Form("Entries / (%.4f)",acop_cut/20.), W, H);
   mc5.SetLogy(false);
   mc5.SetYRange(2,9000);
   mc5.SetRatioRange(0.1,1.9);
   mc5.SetLegendPosition(0.3,0.68,0.7,0.85);
   mc5.CanvasWithHistogramsRatioPlot(hacop_data,hacop_MC,"Data","QED #gamma#gamma #rightarrow e^{+}e^{-} (MC)","Data/MC",kBlack,kYellow,kFALSE,kTRUE,"E0","hist SAME");
   mc5.PrintCanvas();
   mc5.PrintCanvas_C();
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
