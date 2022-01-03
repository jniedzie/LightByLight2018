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

#include "ReadqedTree.C"

const int nSample = 1;
//const char *sample[nSample]={"Data","QED_SC","QED_SL"};
const char *sample[nSample]={"QEDSC"};

void make_canvas(TCanvas *&);
void make_canvas_ratio(TCanvas *&);
void make_hist(TH1D *&, Color_t , int );
void make_hist_ratio(TH1D *&,Color_t, int) ;

//const double luminosity       = 1635.123139823; // μb^-1
const double luminosity       = 1;
//const double luminosity       = 1639.207543; // μb^-1
const double nEventsGeneratedSL = 66750000; // older number with less files 63398400; //starlight
const double xsecGeneratedSL    = 7920; // μb, starlight
//const double xsecGeneratedSL    = 7920000; // nb, starlight

const double nEventsGeneratedSC = 67810000; // older number with less files 67262800 superchic 
const double xsecGeneratedSC    = 8827.220; // μb
//const double xsecGeneratedSC    = 8827220; // nb
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



double lumiNormSC = xsecGeneratedSC*luminosity*scaleFactorsSC/nEventsGeneratedSC;
double lumiNormSL = xsecGeneratedSL*luminosity*scaleFactorsSL/nEventsGeneratedSL;

const double xsecGeneratedLbL    = 2.59; // μb
//const double xsecGeneratedLbL    = 2590; // nb
const double nEventsGeneratedLbL = 466000; 
//double norm_exgg = 0.83*0.99*xsecGeneratedLbL*luminosity/nEventsGeneratedLbL; 
double norm_exgg = 1.09*xsecGeneratedLbL*luminosity/nEventsGeneratedLbL;  //31.12.21 (SF = 1.048, took the square here). 

const double wt[nSample] = {lumiNormSL};
//const double wt[nSample] = {lumiNormSC};
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

TH1D* subtractBkg(TH1D *hdata, TH1D *hqed, TH1D *hcep, const char* name, int nbins, float xmin, float xmax);
TH1D* getXSecHist(TH1D *hist, const char* name, int nbins, float xmin, float xmax, float lumi);

TCanvas* PlotHistsAndRatio(TCanvas* , TH1D* , TH1D*, TH1D*, double , double , double , double , double , double , const char *, bool); 
void makeUnfold(int method=1){
 
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


  TFile *outf= new TFile(Form("unfolding_QEDSL_histograms_%s.root",MethID1),"recreate");  
  
  TChain *qed[nSample];
  
  TH1D* hdiele_Pt[nSample], *hdiele_Rapidity[nSample], *hdiele_Invmass[nSample], *hAcoplanarity[nSample] ; TH1F *hSF[nSample]; 
  
  TH1D* hdiele_GenPt[nSample], *hdiele_GenRapidity[nSample], *hdiele_GenInvmass[nSample];
  TH2D* hdiele_RecoGenPt[nSample], *hdiele_RecoGenRapidity[nSample], *hRecoGenInvmass[nSample];


  
  cout << "define hists"<< endl;
  
  int i =0;
  //for (int i = 0; i < nSample; i++){
    qed[i] = new TChain("output_tree");
    //qed[i]->Add(Form("%s_eta2p2_GenInfo.root",sample[i]));
    qed[i]->Add("QEDSL_genInfo_properChExcl.root");
    
    hdiele_Pt[i]    = new TH1D(Form("hdiele_Pt%s", sample[i]),"",40,0,2);
    hdiele_Rapidity[i]   = new TH1D(Form("hdiele_Rapidity%s",sample[i]),"",24,-2.4,2.4);
    hdiele_Invmass[i]   = new TH1D(Form("hdiele_Invmass%s",sample[i]),"",50,0,100);
    hAcoplanarity[i]   = new TH1D(Form("hAcoplanarity%s",sample[i]),"",50,0,0.1);
    
    hdiele_GenPt[i]         = new TH1D(Form("hdiele_GenPt%s", sample[i]),"",40,0,2);
    hdiele_GenRapidity[i]   = new TH1D(Form("hdiele_GenRapidity%s",sample[i]),"",24,-2.4,2.4);
    hdiele_GenInvmass[i]          = new TH1D(Form("hdiele_GenInvmass%s",sample[i]),"",50,0,100);
    
    hdiele_RecoGenPt[i]         = new TH2D(Form("hdiele_RecoGenPt%s", sample[i]),"",40,0,2,40,0,2);
    hdiele_RecoGenRapidity[i]   = new TH2D(Form("hdiele_RecoGenRapidity%s",sample[i]),"",24,-2.4,2.4,24,-2.4,2.4);
    hRecoGenInvmass[i]          = new TH2D(Form("hRecoGenInvmass%s",sample[i]),"",50,0,100,50,0,100);


  // ===================   Cross section histograms   ======================     

  TH1D* hGenPt_xSec              = new TH1D("hGenPt_xSec", "Pt gen MC",40,0,2);
  TH1D* hGenRap_xSec             = new TH1D("hGenRap_xSec","Rap gen MC",24,-2.4,2.4);
  TH1D* hGenInvmass_xSec         = new TH1D("hGenInvmass_xSec","Invmass gen MC",50,0,100);

  TH1D* hRecoMCPt_xSec              = new TH1D("hRecoMCPt_xSec", "Pt gen MC",40,0,2);
  TH1D* hRecoMCRap_xSec             = new TH1D("hRecoMCRap_xSec","Rap gen MC",24,-2.4,2.4);
  TH1D* hRecoMCInvmass_xSec         = new TH1D("hRecoMCInvmass_xSec","Invmass gen MC",50,0,100);

  TH1D* hRecoDataPt_xSec              = new TH1D("hRecoDataPt_xSec", "Pt gen MC",40,0,2);
  TH1D* hRecoDataRap_xSec             = new TH1D("hRecoDataRap_xSec","Rap gen MC",24,-2.4,2.4);
  TH1D* hRecoDataInvmass_xSec         = new TH1D("hRecoDataInvmass_xSec","Invmass gen MC",50,0,100);


  TH1D* hUnfoMCPt_xSec              = new TH1D("hUnfoMCPt_xSec", "Pt gen MC",40,0,2);
  TH1D* hUnfoMCRap_xSec             = new TH1D("hUnfoMCRap_xSec","Rap gen MC",24,-2.4,2.4);
  TH1D* hUnfoMCInvmass_xSec         = new TH1D("hUnfoMCInvmass_xSec","Invmass gen MC",50,0,100);

  TH1D* hUnfoDataPt_xSec              = new TH1D("hUnfoDataPt_xSec", "Pt gen MC",40,0,2);
  TH1D* hUnfoDataRap_xSec             = new TH1D("hUnfoDataRap_xSec","Rap gen MC",24,-2.4,2.4);
  TH1D* hUnfoDataInvmass_xSec         = new TH1D("hUnfoDataInvmass_xSec","Invmass gen MC",50,0,100);





    RooUnfoldResponse responsePt (hdiele_Pt[i], hdiele_GenPt[i]);
    RooUnfoldResponse responseRapidity (hdiele_Rapidity[i], hdiele_GenRapidity[i]);
    RooUnfoldResponse responseInvmass (hdiele_Invmass[i], hdiele_GenInvmass[i]);

    cout << "file " << qed[i]->GetEntries()  << endl;
    ReadqedTree  qedR(qed[i]);
    qedR.fChain->SetBranchStatus("*",1);

    if (qedR.fChain == 0) return;
    
    Long64_t nentries = qedR.fChain->GetEntriesFast();
    cout << qed[i]->GetName() << "    " << nentries << endl;
    
    Long64_t nbytes = 0, nb = 0;
    //for (Long64_t jentry=0; jentry<100000;jentry++) {
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry_evt = qedR.LoadTree(jentry);
      if (ientry_evt < 0) break;
      nb = qedR.fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%100000==0)cout << "Entry:" << jentry << endl;
     

      // "===================      Fill gen Info here ======================     
      if(abs(qedR.gen_Eta1) > 2.2 || abs(qedR.gen_Eta1) > 2.2 || qedR.gen_Pt1 < 2.0 || qedR.gen_Pt2 < 2.0 || qedR.gen_diEle_M < 5) continue;
      if(abs(qedR.gen_diEle_Rapidity) > 2.2) continue;

      hdiele_GenPt[i]->Fill(qedR.gen_diEle_Pt,wt[i]);
      hdiele_GenRapidity[i]->Fill(qedR.gen_diEle_Rapidity,wt[i]);
      hdiele_GenInvmass[i]->Fill(qedR.gen_diEle_M,wt[i]);


      // ===================   Apply analysis cuts on reco MC ======================           
      bool isPassing =  qedR.ok_neuexcl == 1 && qedR.ok_chexcl_extrk == 1 
		        && qedR.vSum_M > 5 && qedR.vSum_Pt < 2 
 			&& abs(qedR.eleEta_1) < 2.2 && abs(qedR.eleEta_2) < 2.2 && qedR.elePt_1 > 2.0 && qedR.elePt_2 > 2.0		
		 	&& qedR.ele_acop < 0.01;
			
      if(qedR.ok_trigger == 1) { //trigger 
	if(isPassing){
	
	hdiele_Pt[i]->Fill(qedR.vSum_Pt,wt[i]);
	hdiele_Rapidity[i]->Fill(qedR.vSum_Rapidity,wt[i]);
	hdiele_Invmass[i]->Fill(qedR.vSum_M,wt[i]);
	
	hdiele_RecoGenPt[i]->Fill(qedR.vSum_Pt,qedR.gen_diEle_Pt,wt[i]);
	hdiele_RecoGenRapidity[i]->Fill(qedR.vSum_Rapidity,qedR.gen_diEle_Rapidity,wt[i]);
	hRecoGenInvmass[i]->Fill(qedR.vSum_M,qedR.gen_diEle_M,wt[i]);

	responsePt.Fill(qedR.vSum_Pt,qedR.gen_diEle_Pt,wt[i]);
	responseRapidity.Fill(qedR.vSum_Rapidity,qedR.gen_diEle_Rapidity,wt[i]);
	responseInvmass.Fill(qedR.vSum_M,qedR.gen_diEle_M,wt[i]);
	} //isPassing analysis cuts
	else {
	responsePt.Miss(qedR.gen_diEle_Pt,wt[i]);
	responseRapidity.Miss(qedR.gen_diEle_Rapidity,wt[i]);
	responseInvmass.Miss(qedR.gen_diEle_M,wt[i]);
	}
      } //trigger
	else {
	responsePt.Miss(qedR.gen_diEle_Pt,wt[i]);
	responseRapidity.Miss(qedR.gen_diEle_Rapidity,wt[i]);
	responseInvmass.Miss(qedR.gen_diEle_M,wt[i]);
	}
      
      
    } //entry
 // } // for 4 files
  


  cout<< "======================================Response matrix========================="<<endl;
  char MethID2[100]; 
  //if(method==1)
   // {
      RooUnfoldBayes unfold(&responsePt, hdiele_Pt[0], 4);
      RooUnfoldBayes unfold2(&responseRapidity, hdiele_Rapidity[0], 4);
      RooUnfoldBayes unfold3(&responseInvmass, hdiele_Invmass[0], 4);
      sprintf(MethID2,"Bayes unfolding");
   // }  // OR
  if(method==2)
    { RooUnfoldSvd unfold(&responsePt, hdiele_Pt[0], 4);
      RooUnfoldSvd unfold2(&responseRapidity, hdiele_Rapidity[0], 4);
      RooUnfoldSvd unfold3(&responseInvmass, hdiele_Invmass[0], 4);
      sprintf(MethID2,"Svd unfolding");
    } // OR
  //if(method==3)
   // { RooUnfoldBinByBin unfold(&responsePt, hdiele_Pt[0], 4);
   //   RooUnfoldBinByBin unfold2(&responseRapidity, hdiele_Rapidity[0], 4);
   //   RooUnfoldBinByBin unfold3(&responseInvmass, hdiele_Invmass[0], 4);
   //   sprintf(MethID2,"BinByBin unfolding");
   // }

  TH1D* hUnfoldPt= (TH1D*) unfold.Hreco();
  unfold.PrintTable (cout,hdiele_GenPt[0]);

  TH1D* hUnfoldRapidity= (TH1D*) unfold2.Hreco();
  unfold2.PrintTable (cout,hdiele_GenRapidity[0]);

  TH1D* hUnfoldInvmass= (TH1D*) unfold3.Hreco();
  unfold3.PrintTable (cout,hdiele_GenInvmass[0]);
  


  // =============  Start reading acoplanarity dependent scaled data ==============

  TFile *f1=new TFile("output_dataSF.root","r"); 

  TH1D *hdiele_Pt_data        = (TH1D*)f1->Get("hdiele_ptData");
  TH1D *hdiele_Rapidity_data  = (TH1D*)f1->Get("hdiele_RapidityData"); 
  TH1D *hdiele_Invmass_data   = (TH1D*)f1->Get("hInvmassData"); 


  // "===================     Unfold data ======================     
  TCanvas *c2 = new TCanvas("c2","Dimuon pt ",1100,500);
  c2->Divide(2,1);
  c2->cd(1);

      RooUnfoldBayes unfold_dataPt(&responsePt, hdiele_Pt_data, 4); // unfold data
      RooUnfoldBayes unfold_dataRapidity(&responseRapidity, hdiele_Rapidity_data, 4);
      RooUnfoldBayes unfold_dataInvmass(&responseInvmass, hdiele_Invmass_data, 4);
      sprintf(MethID2,"Bayes unfolding");

  if(method==2)
    { RooUnfoldSvd  unfold_dataPt(&responsePt, hdiele_Pt_data, 4); // unfold data
      RooUnfoldSvd  unfold_dataRapidity(&responseRapidity, hdiele_Rapidity_data, 4);
      RooUnfoldSvd  unfold_dataInvmass(&responseInvmass, hdiele_Invmass_data, 4);
      sprintf(MethID2,"Svd unfolding");
    } // OR
  //if(method==3)
  //  { RooUnfoldBinByBin unfold_data(&response, hmumu_pt2_data_test);
  //    RooUnfoldBinByBin unfold_data_rap(&response_rap, hmumu_rapidity_data_test);
  //    sprintf(MethID2,"BinByBin unfolding");
  //  }
  
  TH1D* hUnfoldPt_data= (TH1D*) unfold_dataPt.Hreco();
  unfold_dataPt.PrintTable (cout, hdiele_Pt_data);

  TH1D* hUnfoldRapidity_data= (TH1D*) unfold_dataRapidity.Hreco();
  unfold_dataRapidity.PrintTable (cout, hdiele_Rapidity_data);

  TH1D* hUnfoldInvmass_data= (TH1D*) unfold_dataInvmass.Hreco();
  unfold_dataInvmass.PrintTable (cout, hdiele_Invmass_data);


  // divide histograms by luminosty and binwidth to get the cross-sections. 
  hGenPt_xSec  = getXSecHist(hdiele_GenPt[0], "hGenPt_xSec", 40,0,2 ,1 );
  hGenRap_xSec = getXSecHist(hdiele_GenRapidity[0], "hGenRap_xSec", 24,-2.4,2.4,1 );
  hGenInvmass_xSec = getXSecHist(hdiele_GenInvmass[0], "hGenInvmass_xSec", 50,0,100,1 );

  hRecoMCPt_xSec  = getXSecHist(hdiele_Pt[0], "hRecoMCPt_xSec", 40,0,2,1 );
  hRecoMCRap_xSec = getXSecHist(hdiele_Rapidity[0], "hRecoMCRap_xSec", 24,-2.4,2.4,1 );
  hRecoMCInvmass_xSec = getXSecHist(hdiele_Invmass[0], "hRecoMCInvmass_xSec", 50,0,100,1 );

  hRecoDataPt_xSec  = getXSecHist(hdiele_Pt_data, "hRecoDataPt_xSec", 40,0,2, 1639);
  hRecoDataRap_xSec = getXSecHist(hdiele_Rapidity_data, "hRecoDataRap_xSec", 24,-2.4,2.4, 1639);
  hRecoDataInvmass_xSec = getXSecHist(hdiele_Invmass_data, "hRecoDataInvmass_xSec", 50,0,100, 1639);

  hUnfoMCPt_xSec  = getXSecHist(hUnfoldPt,       "hUnfoMCPt_xSec", 40,0,2,1 );
  hUnfoMCRap_xSec = getXSecHist(hUnfoldRapidity, "hUnfoMCRap_xSec", 24,-2.4,2.4,1 );
  hUnfoMCInvmass_xSec = getXSecHist(hUnfoldInvmass, "hUnfoMCInvmass_xSec", 50,0,100,1 );

  hUnfoDataPt_xSec  = getXSecHist(hUnfoldPt_data, "hUnfoDataPt_xSec", 40,0,2, 1639);
  hUnfoDataRap_xSec = getXSecHist(hUnfoldRapidity_data, "hUnfoDataRap_xSec", 24,-2.4,2.4, 1639);
  hUnfoDataInvmass_xSec = getXSecHist(hUnfoldInvmass_data, "hUnfoDataInvmass_xSec",50,0,100, 1639);

hUnfoDataRap_xSec->Draw("p");


  new TCanvas();
 
 hdiele_GenPt[0]->SetLineColor(kGreen);
 hdiele_GenPt[0]->Draw("hist");
 hdiele_Pt_data->SetLineColor(kBlue);
 hdiele_Pt_data->Draw("histsame");

 hUnfoldPt_data->SetLineColor(kRed);
 hUnfoldPt_data->Draw("psame");


  new TCanvas();
 
 hdiele_GenRapidity[0]->SetLineColor(kGreen);
 hdiele_GenRapidity[0]->Draw("hist");
 hdiele_Rapidity_data->SetLineColor(kBlue);
 hdiele_Rapidity_data->Draw("histsame");

 hUnfoldRapidity_data->SetLineColor(kRed);
 hUnfoldRapidity_data->Draw("psame");

  new TCanvas();
 
 hdiele_GenInvmass[0]->SetLineColor(kGreen);
 hdiele_GenInvmass[0]->Draw("hist");
 hdiele_Invmass_data->SetLineColor(kBlue);
 hdiele_Invmass_data->Draw("histsame");

 hUnfoldInvmass_data->SetLineColor(kRed);
 hUnfoldInvmass_data->Draw("psame");



  cout << " invariant mass " << sample[0] <<  " :" << hdiele_Invmass[0]->Integral() << endl;  
  //cout << " invariant mass " << sample[1] <<  " :" << hdiele_Invmass[1]->Integral() << endl;  
  //cout << " invariant mass " << sample[2] <<  " :" << hdiele_Invmass[2]->Integral() << endl;  
  outf->cd();
  outf->Write();
 //hPt_data_bkgSub->Write();
  hGenPt_xSec->Write();
  hGenRap_xSec->Write();
  hGenInvmass_xSec->Write();

  hRecoMCPt_xSec->Write();
  hRecoMCRap_xSec->Write();
  hRecoMCInvmass_xSec->Write();

  hRecoDataPt_xSec->Write();
  hRecoDataRap_xSec->Write();
  hRecoDataInvmass_xSec->Write();

  hUnfoMCPt_xSec->Write();
  hUnfoMCRap_xSec->Write();
  hUnfoMCInvmass_xSec->Write();

  hUnfoDataPt_xSec->Write();
  hUnfoDataRap_xSec->Write();
  hUnfoDataInvmass_xSec->Write();





  //hUnfold->Write();
  //hUnfoldRapidity->Write();
  //hUnfoldRapidity_data->Write();
  //hUnfoldInvmass->Write();*/


  outf->Close();
  
  


  
}

TH1D* subtractBkg(TH1D *hdata, TH1D *hqed, TH1D *hcep, const char* name, int nbins, float xmin, float xmax){

  TH1D *hans = new TH1D(name,"",nbins,xmin,xmax);
  //TH1D* hans = (TH1D*)hdata->Clone();

   for (int i=1; i<=hdata->GetNbinsX(); i++) {
      double binCont  = hdata->GetBinContent(i)-hqed->GetBinContent(i)-hcep->GetBinContent(i);
      double binError = sqrt(pow(hdata->GetBinError(i),2) + pow(hqed->GetBinError(i),2)  + pow(hcep->GetBinError(i),2) );


      hans->SetBinContent(i, binCont);
      hans->SetBinError(i, binError);
      //cout << "******bin:" << i << " " << hans->GetBinContent(i) << "+/-" <<  binError<< endl;
      //double err=0;
      //for (int ivar=1; ivar<14; ivar++) err += pow(hvari[ivar]->GetBinContent(i)-hvari[0]->GetBinContent(i),2);
      //hans->SetBinError(i,sqrt(err+pow(hans->GetBinError(i),2)+pow(glob_syst,2)));
   }

   return hans;
}

TH1D* getXSecHist(TH1D *hist, const char* name, int nbins, float xmin, float xmax, float luminosity){

  TH1D *hans = new TH1D(name,"",nbins,xmin,xmax);
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
   }
   return hans;

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


