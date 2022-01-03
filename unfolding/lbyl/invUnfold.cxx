#if !(defined(__CINT__) || defined(__CLING__)) || defined(__ACLIC__)
#include <iostream>
#include <fstream>
#include <sstream>
#include <TFile.h>
#include <TDirectory.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TROOT.h>

#include "TStyle.h"
#include "TPaveStats.h"
#include "TText.h"
#include "THStack.h"
#include "TCut.h"
#include "TAxis.h"
#include "TChain.h"
#include "RooUnfoldResponse.h"
#include "RooUnfoldBinByBin.h"
#include "RooUnfoldBayes.h"
#include "RooUnfoldSvd.h"
#include "RooUnfoldTUnfold.h"
#endif

#include "ReadLbyLTree.C"

const int nSample = 1;
//const char *sample[nSample]={"Data","QED_SC","QED_SL"};
const char *sample[nSample]={"LbL"};

void make_canvas(TCanvas *&);
void make_canvas_ratio(TCanvas *&);
void make_hist(TH1D *&, Color_t , int );
void make_hist_ratio(TH1D *&,Color_t, int) ;

//const double luminosity       = 1635.123139823; // μb^-1
const double luminosity       = 1;
//const double luminosity       = 1639.207543; // μb^-1
const double nEventsGeneratedSL = 66750000; // older number with less files 63398400; //starlight
//const double xsecGeneratedSL    = 7920; // μb, starlight
const double xsecGeneratedSL    = 7920000; // nb, starlight

const double nEventsGeneratedSC = 67810000; // older number with less files 67262800 superchic 
//const double xsecGeneratedSC    = 8827.220; // μb
const double xsecGeneratedSC    = 8827220; // nb
const double purity = 0.96; 
double scaleFactorsSC = 0.85 *  // NEE    21.12.2021
                        0.93 *      // CHE  21.12.2021
                        pow(0.976, 2)* // electron reco+ID 21.12.2021
                        0.866 *      // HF veto
                       1.008;       // L1 EG trigger

double scaleFactorsSL = 0.85 *  // NEE    21.12.2021
  0.93 *      // CHE  21.12.2021
  pow(0.976, 2)* // electron reco+ID 21.12.2021
  0.866 *      // HF veto
  1.008;       // L1 EG trigger



double lumiNormSC = xsecGeneratedSC*luminosity*purity*scaleFactorsSC/nEventsGeneratedSC;
double lumiNormSL = xsecGeneratedSL*luminosity*purity*scaleFactorsSL/nEventsGeneratedSL;

//const double xsecGeneratedLbL    = 2.59; // μb
const double xsecGeneratedLbL    = 2590; // nb
const double nEventsGeneratedLbL = 466000; 
//double norm_exgg = 0.83*0.99*xsecGeneratedLbL*luminosity/nEventsGeneratedLbL; 
double norm_exgg = 1.09*xsecGeneratedLbL*luminosity/nEventsGeneratedLbL;  //31.12.21 (SF = 1.048, took the square here). 

void printOutput(TH1D *hist);

const double wt[nSample] = {norm_exgg};
float getAcoBinSF(float acop);


void drawText(const char *text, float xp, float yp, int size){
  TLatex *tex = new TLatex(xp,yp,text);
  tex->SetTextFont(43);
  tex->SetTextSize(size);
  tex->SetTextColor(kMagenta);
  tex->SetLineWidth(1);
  tex->SetNDC();
  tex->Draw();
}
const int nMassbins=4;
double Massbin[nMassbins]={5.0,7.0,10.0,16.0};
const int nMassbin= sizeof(Massbin)/sizeof(double) - 1;


TH1D* subtractBkg(TH1D *hdata, TH1D *hqed, TH1D *hcep, const char* name, int nbins, float xmin, float xmax);

TH1D* getXSecHist(TH1D *hist, const char* name, float lumi);

TCanvas* PlotHistsAndRatio(TCanvas* , TH1D* , TH1D*, TH1D*, double , double , double , double , double , double , const char *, bool); 
void invUnfold(int method=1){
 
  //gROOT->LoadMacro("CMS_lumi.C");
  bool outOfFrame    = false;
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);
  
  char MethID1[100]; 
  if(method==1){
        
      sprintf(MethID1,"Bayes_unfo");
    } 
  if(method==2){
    
      sprintf(MethID1,"Svd_unfo ");
    }
  if(method==3){
    
      sprintf(MethID1,"BinByBin_unfo");
    }


  TFile *outf= new TFile(Form("unfolding_histograms_invmass_%s.root",MethID1),"recreate");  
  
  TChain *lbyl[nSample];
  
  TH1D* hdipho_Pt[nSample], *hdipho_Rapidity[nSample], *hdipho_Invmass[nSample], *hAcoplanarity[nSample] ; TH1F *hSF[nSample]; 
  
  TH1D* hdipho_GenPt[nSample], *hdipho_GenRapidity[nSample], *hdipho_GenInvmass[nSample];
  TH2D* hdipho_RecoGenPt[nSample], *hdipho_RecoGenRapidity[nSample], *hRecoGenInvmass[nSample];


  //RooUnfoldResponse responseRapidity (hdipho_Rapidity, hdipho_GenRapidity);
  //RooUnfoldResponse responseInvmass (hdipho_Invmass, hdipho_GenInvmass);
  
  cout << "define hists"<< endl;
  
  int i =0;
  //for (int i = 0; i < nSample; i++){
    lbyl[i] = new TChain("output_tree");
    //lbyl[i]->Add(Form("%s_eta2p2_GenInfo.root",sample[i]));
    lbyl[i]->Add("../eta2p2/lbyl_diphoton_genInfo.root");
    
    hdipho_Pt[i]    = new TH1D(Form("hdipho_Pt%s", sample[i]),"",10,0,2);
    hdipho_Rapidity[i]   = new TH1D(Form("hdipho_Rapidity%s",sample[i]),"",4,0,2.2);
    hdipho_Invmass[i]   = new TH1D(Form("hdipho_Invmass%s",sample[i]),"",nMassbin, Massbin);
    hAcoplanarity[i]   = new TH1D(Form("hAcoplanarity%s",sample[i]),"",50,0,0.1);
    
    hdipho_GenPt[i]         = new TH1D(Form("hdipho_GenPt%s", sample[i]),"",10,0,2);
    hdipho_GenRapidity[i]   = new TH1D(Form("hdipho_GenRapidity%s",sample[i]),"",4,0,2.2);
    hdipho_GenInvmass[i]          = new TH1D(Form("hdipho_GenInvmass%s",sample[i]),"",nMassbin, Massbin);
    
    hdipho_RecoGenPt[i]         = new TH2D(Form("hdipho_RecoGenPt%s", sample[i]),"",10,0,2,10,0,2);
    hdipho_RecoGenRapidity[i]   = new TH2D(Form("hdipho_RecoGenRapidity%s",sample[i]),"",4,0,2.2,4,0,2.2);
    hRecoGenInvmass[i]          = new TH2D(Form("hRecoGenInvmass%s",sample[i]),"",nMassbin, Massbin,nMassbin, Massbin);


  // ===================   Cross section histograms   ======================     

  TH1D* hGenPt_xSec              = new TH1D("hGenPt_xSec", "Pt gen MC",10,0,2);
  TH1D* hGenRap_xSec             = new TH1D("hGenRap_xSec","Rap gen MC",4,0,2.2);
  TH1D* hGenInvmass_xSec         = new TH1D("hGenInvmass_xSec","Invmass gen MC",nMassbin, Massbin);

  TH1D* hRecoMCPt_xSec              = new TH1D("hRecoMCPt_xSec", "Pt gen MC",10,0,2);
  TH1D* hRecoMCRap_xSec             = new TH1D("hRecoMCRap_xSec","Rap gen MC",4,0,2.2);
  TH1D* hRecoMCInvmass_xSec         = new TH1D("hRecoMCInvmass_xSec","Invmass gen MC",nMassbin, Massbin);

  TH1D* hRecoDataPt_xSec              = new TH1D("hRecoDataPt_xSec", "Pt gen MC",10,0,2);
  TH1D* hRecoDataRap_xSec             = new TH1D("hRecoDataRap_xSec","Rap gen MC",4,0,2.2);
  TH1D* hRecoDataInvmass_xSec         = new TH1D("hRecoDataInvmass_xSec","Invmass gen MC",nMassbin, Massbin);


  TH1D* hUnfoMCPt_xSec              = new TH1D("hUnfoMCPt_xSec", "Pt gen MC",10,0,2);
  TH1D* hUnfoMCRap_xSec             = new TH1D("hUnfoMCRap_xSec","Rap gen MC",4,0,2.2);
  TH1D* hUnfoMCInvmass_xSec         = new TH1D("hUnfoMCInvmass_xSec","Invmass gen MC",nMassbin, Massbin);

  TH1D* hUnfoDataPt_xSec              = new TH1D("hUnfoDataPt_xSec", "Pt gen MC",10,0,2);
  TH1D* hUnfoDataRap_xSec             = new TH1D("hUnfoDataRap_xSec","Rap gen MC",4,0,2.2);
  TH1D* hUnfoDataInvmass_xSec         = new TH1D("hUnfoDataInvmass_xSec","Invmass gen MC",nMassbin, Massbin);





    RooUnfoldResponse responsePt (hdipho_Pt[i], hdipho_GenPt[i]);
    RooUnfoldResponse responseRapidity (hdipho_Rapidity[i], hdipho_GenRapidity[i]);
    RooUnfoldResponse responseInvmass (hdipho_Invmass[i], hdipho_GenInvmass[i]);

    cout << "file " << lbyl[i]->GetEntries()  << endl;
    ReadLbyLTree  lbylR(lbyl[i]);
    lbylR.fChain->SetBranchStatus("*",1);

    if (lbylR.fChain == 0) return;
    
    Long64_t nentries = lbylR.fChain->GetEntriesFast();
    cout << lbyl[i]->GetName() << "    " << nentries << endl;
    
    Long64_t nbytes = 0, nb = 0;
    //for (Long64_t jentry=0; jentry<10;jentry++) {
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry_evt = lbylR.LoadTree(jentry);
      if (ientry_evt < 0) break;
      nb = lbylR.fChain->GetEntry(jentry);   nbytes += nb;
     

      // "===================      Fill gen Info here ======================     
      if(abs(lbylR.gen_Eta1) > 2.2 || abs(lbylR.gen_Eta1) > 2.2 || lbylR.gen_Pt1 < 2.0 || lbylR.gen_Pt2 < 2.0 || lbylR.gen_diPho_M < 5) continue;
      if(abs(lbylR.gen_diPho_Rapidity) > 2.2) continue;

      hdipho_GenPt[i]->Fill(lbylR.gen_diPho_Pt,wt[i]);
      hdipho_GenRapidity[i]->Fill(lbylR.gen_diPho_Rapidity,wt[i]);
      hdipho_GenInvmass[i]->Fill(lbylR.gen_diPho_M,wt[i]);


      // ===================   Apply analysis cuts on reco MC ======================           
      bool isPassing = lbylR.phoSwissCross_1 < 0.95 && lbylR.phoSwissCross_2 <  0.95
		        && lbylR.ok_neuexcl == 1 && lbylR.ok_chexcl_goodtracks == 1 && lbylR.ok_chexcl_goodelectrons == 1 
		        && lbylR.vSum_M > 5 && lbylR.vSum_Pt < 2 
 			&& abs(lbylR.phoEta_1) < 2.2 && abs(lbylR.phoEta_2) < 2.2 && lbylR.phoEt_1 > 2.0 && lbylR.phoEt_2 > 2.0		
		 	&& lbylR.pho_acop < 0.01;
			
      if(lbylR.ok_trigger == 1) { //trigger 
	if(isPassing){
	/*if(lbylR.phoSwissCross_1 > 0.95 || lbylR.phoSwissCross_2 >  0.95)continue;
	if(lbylR.ok_neuexcl != 1) continue; //neutral exclusivity
	if(lbylR.ok_chexcl_goodtracks != 1 || lbylR.ok_chexcl_goodelectrons != 1) continue; //charged exclusivity
	if(lbylR.vSum_M < 5) continue; //invmass
	if(lbylR.vSum_Pt > 2) continue; //dipho pt
	if(abs(lbylR.phoEta_1) > 2.2) continue;
	if(abs(lbylR.phoEta_2) > 2.2) continue;
	
	if(lbylR.phoEt_1 < 2.0) continue;
	if(lbylR.phoEt_2 < 2.0) continue;
	
	if(lbylR.pho_acop > 0.01) continue; //acop*/
	
	hdipho_Pt[i]->Fill(lbylR.vSum_Pt,wt[i]);
	hdipho_Rapidity[i]->Fill(lbylR.vSum_Rapidity,wt[i]);
	hdipho_Invmass[i]->Fill(lbylR.vSum_M,wt[i]);
	
	hdipho_RecoGenPt[i]->Fill(lbylR.vSum_Pt,lbylR.gen_diPho_Pt,wt[i]);
	hdipho_RecoGenRapidity[i]->Fill(lbylR.vSum_Rapidity,lbylR.gen_diPho_Rapidity,wt[i]);
	hRecoGenInvmass[i]->Fill(lbylR.vSum_M,lbylR.gen_diPho_M,wt[i]);

	responsePt.Fill(lbylR.vSum_Pt,lbylR.gen_diPho_Pt,wt[i]);
	responseRapidity.Fill(lbylR.vSum_Rapidity,lbylR.gen_diPho_Rapidity,wt[i]);
	responseInvmass.Fill(lbylR.vSum_M,lbylR.gen_diPho_M,wt[i]);
	} //isPassing analysis cuts
	else {
	responsePt.Miss(lbylR.gen_diPho_Pt,wt[i]);
	responseRapidity.Miss(lbylR.gen_diPho_Rapidity,wt[i]);
	responseInvmass.Miss(lbylR.gen_diPho_M,wt[i]);
	}
      } //trigger
	else {
	responsePt.Miss(lbylR.gen_diPho_Pt,wt[i]);
	responseRapidity.Miss(lbylR.gen_diPho_Rapidity,wt[i]);
	responseInvmass.Miss(lbylR.gen_diPho_M,wt[i]);
	}
      
      
    } //entry
 // } // for 4 files
  
 // hdipho_Invmass[0]->Draw("p");

  cout<< "======================================Response matrix========================="<<endl;
  char MethID2[100]; 
  //if(method==1)
   // {
      //RooUnfoldBayes unfold(&responsePt, hdipho_Pt[0], 4);
      //RooUnfoldBayes unfold2(&responseRapidity, hdipho_Rapidity[0], 4);
      RooUnfoldBayes unfold3(&responseInvmass, hdipho_Invmass[0], 4);
      sprintf(MethID2,"Bayes unfolding");
   // }  // OR
  if(method==2)
    { RooUnfoldSvd unfold(&responsePt, hdipho_Pt[0], 4);
      RooUnfoldSvd unfold2(&responseRapidity, hdipho_Rapidity[0], 4);
      RooUnfoldSvd unfold3(&responseInvmass, hdipho_Invmass[0], 4);
      sprintf(MethID2,"Svd unfolding");
    } // OR


  TH1D* hUnfoldInvmass= (TH1D*) unfold3.Hreco();
  unfold3.PrintTable (cout,hdipho_GenInvmass[0]);
  


  /***************************  Start reading data and subtract background contributions ********************************/

  TFile *f1=new TFile("diphoton_histos.root","r"); 

  TH1D *hdipho_Pt_data        = (TH1D*)f1->Get("hdiphoton_pt_data");
  TH1D *hdipho_Rapidity_data  = (TH1D*)f1->Get("hdiphoton_rapidity_data"); 
  TH1D *hdipho_Invmass_data   = (TH1D*)f1->Get("hinvmass_data"); 

  TH1D *hdipho_Pt_qed        = (TH1D*)f1->Get("hdiphoton_pt_qed");
  TH1D *hdipho_Rapidity_qed  = (TH1D*)f1->Get("hdiphoton_rapidity_qed"); 
  TH1D *hdipho_Invmass_qed   = (TH1D*)f1->Get("hinvmass_qed"); 

  TH1D *hdipho_Pt_cep        = (TH1D*)f1->Get("hdiphoton_pt_cep");
  TH1D *hdipho_Rapidity_cep  = (TH1D*)f1->Get("hdiphoton_rapidity_cep"); 
  TH1D *hdipho_Invmass_cep   = (TH1D*)f1->Get("hinvmass_cep"); 

  // "===================      Subtract background ======================     
  hdipho_Invmass_qed->Add(hdipho_Invmass_cep,1);

  TH1D* hInvmass_data_bkgSub = (TH1D*)hdipho_Invmass_data->Clone();
  hInvmass_data_bkgSub->Add(hdipho_Invmass_qed,-1);


  // "===================     Unfold data ======================     
  TCanvas *c2 = new TCanvas("c2","Dimuon pt ",1100,500);
  c2->Divide(2,1);
  c2->cd(1);


      RooUnfoldBayes unfold_dataInvmass(&responseInvmass, hInvmass_data_bkgSub, 4);
      sprintf(MethID2,"Bayes unfolding");

  if(method==2)
    {
      RooUnfoldSvd  unfold_dataInvmass(&responseInvmass, hInvmass_data_bkgSub, 4);
      sprintf(MethID2,"Svd unfolding");
    } // OR
  //if(method==3)
  //  { RooUnfoldBinByBin unfold_data(&response, hmumu_pt2_data_test);
  //    RooUnfoldBinByBin unfold_data_rap(&response_rap, hmumu_rapidity_data_test);
  //    sprintf(MethID2,"BinByBin unfolding");
  //  }
  


  TH1D* hUnfoldInvmass_data= (TH1D*) unfold_dataInvmass.Hreco();
  unfold_dataInvmass.PrintTable (cout, hInvmass_data_bkgSub);


  printOutput(hUnfoldInvmass_data);

  // divide histograms by luminosty and binwidth to get the cross-sections. 
  
  hGenInvmass_xSec = getXSecHist(hdipho_GenInvmass[0], "hGenInvmass_xSec" ,1 );

  
  hRecoMCInvmass_xSec = getXSecHist(hdipho_Invmass[0], "hRecoMCInvmass_xSec",1 );

  hRecoDataInvmass_xSec = getXSecHist(hdipho_Invmass_data, "hRecoDataInvmass_xSec", 1.639);
  hUnfoMCInvmass_xSec = getXSecHist(hUnfoldInvmass, "hUnfoMCInvmass_xSec", 1 );
  hUnfoDataInvmass_xSec = getXSecHist(hUnfoldInvmass_data, "hUnfoDataInvmass_xSec", 1.639);

  







  cout << " invariant mass " << sample[0] <<  " :" << hdipho_Invmass[0]->Integral() << endl;  
  //cout << " invariant mass " << sample[1] <<  " :" << hdipho_Invmass[1]->Integral() << endl;  
  //cout << " invariant mass " << sample[2] <<  " :" << hdipho_Invmass[2]->Integral() << endl;  
  outf->cd();
  //outf->Write();
 
  hGenInvmass_xSec->Write();

  hRecoMCInvmass_xSec->Write();

  hRecoDataInvmass_xSec->Write();

  hUnfoMCInvmass_xSec->Write();

  hUnfoDataInvmass_xSec->Write();


  outf->Close();

  


  
}

TH1D* subtractBkg(TH1D *hdata, TH1D *hqed, TH1D *hcep, const char* name, int nbins, float xmin, float xmax){

  TH1D *hans = new TH1D(name,"",nbins,xmin,xmax);
  //TH1D* hans = (TH1D*)hdata->Clone();
   cout << " Name of histogram :" << name << endl;
   for (int i=1; i<=hdata->GetNbinsX(); i++) {
      double binCont  = hdata->GetBinContent(i)-hqed->GetBinContent(i)-hcep->GetBinContent(i);
      double binError = sqrt(pow(hdata->GetBinError(i),2) + pow(hqed->GetBinError(i),2)  + pow(hcep->GetBinError(i),2) );


      hans->SetBinContent(i, binCont);
      hans->SetBinError(i, binError);
      cout << "******bin:" << i << " " << hdata->GetBinContent(i) << " " << hqed->GetBinContent(i) << " " << hcep->GetBinContent(i) << "   " <<  hans->GetBinContent(i) << "+/-" <<  binError<< endl;
      //double err=0;
      //for (int ivar=1; ivar<14; ivar++) err += pow(hvari[ivar]->GetBinContent(i)-hvari[0]->GetBinContent(i),2);
      //hans->SetBinError(i,sqrt(err+pow(hans->GetBinError(i),2)+pow(glob_syst,2)));
   }

   return hans;
}



TH1D* getXSecHist(TH1D *hist, const char* name, float luminosity){

  TH1D *hans = new TH1D(name,"",nMassbin, Massbin);
   cout << " Name of histogram :" << name << endl;
   for (int i=1; i<=hist->GetNbinsX(); i++) {

      double binCont  = hist->GetBinContent(i)/(luminosity*hist->GetBinWidth(i));

      double binError = binCont * sqrt(pow(hist->GetBinError(i)/hist->GetBinContent(i),2));
      //double binError = hist->GetBinError(i);
      if(binCont == 0){ hans->SetBinContent(i, 0);
       hans->SetBinError(i, 0);}
	else{
      hans->SetBinContent(i, binCont);
      hans->SetBinError(i, binError);
    }

      cout << "******bin:" << i << " " << hans->GetBinContent(i) << "+/-" <<  binError<< endl;
      //double err=0;
      //for (int ivar=1; ivar<14; ivar++) err += pow(hvari[ivar]->GetBinContent(i)-hvari[0]->GetBinContent(i),2);
      //hans->SetBinError(i,sqrt(err+pow(hans->GetBinError(i),2)+pow(glob_syst,2)));
   }
   return hans;

}


void printOutput(TH1D *hist){
 for (int i=1; i<=hist->GetNbinsX(); i++) {
      cout << "******bin:" << i << " " << hist->GetBinContent(i) << "+/-" <<  hist->GetBinError(i) << endl; 
    }
}
void make_canvas(TCanvas *& canvas){

  int W = 600;
  int H = 670;
  float T = 0.08;
  float B = 0.14; 
  float L = 0.18;
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

void make_canvas_ratio(TCanvas *& can){

  int W = 700;
  int H = 600;
  float T = 0.08;
  float B = 0.14; 
  float L = 0.14;
  float R = 0.04;

  can->SetFillColor(0);
  can->SetBorderMode(0);
  can->SetFrameFillStyle(0);
  can->SetFrameBorderMode(0);
  can->SetLeftMargin( L );
  can->SetRightMargin( R );
  can->SetTopMargin( T );
  can->SetBottomMargin( B );
  can->SetTickx(0);
  can->SetTicky(0);
}


void make_hist(TH1D *& hist, Color_t kcolor, int kstyle){
  // For the axis labels:
  hist->SetLabelColor(1, "XYZ");
  hist->SetLabelFont(42, "XYZ");
  hist->SetLabelOffset(0.007, "XYZ");
  hist->SetLabelSize(0.05, "XYZ");
 
  hist->SetMarkerColor(kcolor);
  hist->SetFillColor(kcolor);
  hist->SetMarkerStyle(kstyle);
 
}

void make_hist_ratio(TH1D *& hist, Color_t kcolor, int kstyle){
  // For the axis labels:
  hist->SetLabelColor(1, "XYZ");
  hist->SetLabelFont(42, "XYZ");
  hist->SetLabelOffset(0.007, "XYZ");
  hist->SetLabelSize(0.1, "XYZ");

  // For the axis titles:
  hist->SetTitleFont(42, "XYZ");
  hist->SetTitleSize(0.11, "XYZ");
  hist->GetXaxis()->SetTitleOffset(1.1);
  hist->GetYaxis()->SetTitleOffset(0.4);
  hist->SetMarkerColor(kcolor);
  hist->SetFillColor(kcolor);
  hist->SetMarkerStyle(kstyle);
 
}


float getAcoBinSF(float acop) {
      if (acop<0.002) return 0.990761;
      else if (acop<0.004) return 0.962675;
      else if (acop<0.006) return 0.861166;
      else if (acop<0.008) return 0.598683;
      else if (acop<0.01) return 0.264046;    
      else return 1;
   
}


