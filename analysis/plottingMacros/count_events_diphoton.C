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
//#include "../../CMS_lumi.C"
#include "TStyle.h"
#include "TPaveStats.h"
#include "TText.h"
#include "THStack.h"
#include "TCut.h"
#include "TAxis.h"
#include "TChain.h"


const double luminosity       = 1635.123139823; // μb^-1
const double nEventsGeneratedSL = 63957000; // older number with less files 63398400; //starlight
const double xsecGeneratedSL    = 7920; // μb, starlight

const double nEventsGeneratedSC = 67536400; // older number with less files 67262800 superchic 
const double xsecGeneratedSC    = 8827.220; // μb
const double purity = 0.96; 
double scaleFactorsSC = 0.848 *  // NEE
                       // 0.971 *      // CHE  13.01.2021
                         0.932 *      // CHE    22.11.2021
                        pow(0.98, 2)* // electron reco+ID
                        0.67 *      // HF veto
                        0.99;       // L1 EG trigger

double scaleFactorsSL =0.848 *  // NEE
                       // 0.971 *      // CHE  13.01.2021
                         0.932 *      // CHE    22.11.2021
                        pow(0.98, 2)* // electron reco+ID
                        0.67 *      // HF veto
                        0.99;       // L1 EG trigger


double lumiNormSC = xsecGeneratedSC*luminosity*purity*scaleFactorsSC/nEventsGeneratedSC;
double lumiNormSL = xsecGeneratedSL*luminosity*purity*scaleFactorsSL/nEventsGeneratedSL;


const double xsecGeneratedLbL    = 2.59; // μb
const double nEventsGeneratedLbL = 466000; 
double norm_exgg = 0.83*0.99*xsecGeneratedLbL*luminosity/nEventsGeneratedLbL; 


const double xsecGeneratedCEP    = 0.0058; // μb
const double nEventsGeneratedCEP = 668000; 
double norm_cep = xsecGeneratedCEP*luminosity/nEventsGeneratedCEP; 

const double xsecGeneratedCEPIncoh    = 0.001431; // μb
const double nEventsGeneratedCEPIncoh = 500000; 
double norm_cepIncoh = xsecGeneratedCEPIncoh*luminosity/nEventsGeneratedCEPIncoh; 

void count_events(){
 
  //gROOT->LoadMacro("CMS_lumi.C");
  bool outOfFrame    = false;
  TH1::SetDefaultSumw2();
   gStyle->SetOptStat(0);

  TChain *data = new TChain("output_tree");
  data->Add("diphoton_data13.root");
 
 
  TChain *lbl = new TChain("output_tree");
  lbl->Add("diphoton_lbl12.root");
lumiNormSC = lumiNormSL;

  TChain *mcsl = new TChain("output_tree");
  mcsl->Add("diphoton_qed12.root");

  TChain *cep = new TChain("output_tree");
  cep->Add("diphoton_cep12.root");

  TChain *cepIncoh = new TChain("output_tree");
  cepIncoh->Add("CEPIncoh_diphoton.root");

 
   const TCut swiss_cross  = "phoSwissCross_1 < 0.95 && phoSwissCross_2 < 0.95";
   const TCut no_addittional_tower  = " ok_neuexcl==1";
   const TCut no_extrk  = " ok_chexcl_goodtracks == 1 && ok_chexcl_goodelectrons==1" && swiss_cross;
   const TCut zdc_cut  = " ok_zdcexcl_4n_pos == 1 && ok_zdcexcl_4n_neg == 1";

  TH1D* hmass_data_goodPho   = new TH1D("hmass_data_goodPho","",75,0,150);
  TH1D* hmass_data_ch   = new TH1D("hmass_data_ch","",75,0,150);
  TH1D* hmass_data_neu  = new TH1D("hmass_data_neu","",75,0,150);
  TH1D* hmass_data_zdc  = new TH1D("hmass_data_zdc","",75,0,150);
  TH1D* hmass_data_inv  = new TH1D("hmass_data_inv","",75,0,150);
  TH1D* hmass_data_pt  = new TH1D("hmass_data_pt","",75,0,150);
  TH1D* hmass_data_acop  = new TH1D("hmass_data_acop","",75,0,150);

  data->Project(hmass_data_goodPho->GetName(), "vSum_M",swiss_cross);
  data->Project(hmass_data_inv->GetName(), "vSum_M","vSum_M>5" && swiss_cross );
  data->Project(hmass_data_ch->GetName(), "vSum_M",no_extrk && "vSum_M>5");
  data->Project(hmass_data_neu->GetName(), "vSum_M",no_extrk && no_addittional_tower && "vSum_M>5" );
  data->Project(hmass_data_zdc->GetName(), "vSum_M",no_extrk && no_addittional_tower && zdc_cut && "vSum_M>5" );
  data->Project(hmass_data_pt->GetName(), "vSum_M", no_extrk && no_addittional_tower && zdc_cut && "vSum_M>5 && vSum_Pt<2" );
  data->Project(hmass_data_acop->GetName(), "vSum_M",no_extrk && no_addittional_tower && zdc_cut && "vSum_M>5 && vSum_Pt<2 && pho_acop<0.01" );


  TH1D* hmass_lbl_goodPho   = new TH1D("hmass_lbl_goodPho","",75,0,150);
  TH1D* hmass_lbl_ch   = new TH1D("hmass_lbl_ch","",75,0,150);
  TH1D* hmass_lbl_neu  = new TH1D("hmass_lbl_neu","",75,0,150);
  TH1D* hmass_lbl_zdc  = new TH1D("hmass_lbl_zdc","",75,0,150);
  TH1D* hmass_lbl_inv  = new TH1D("hmass_lbl_inv","",75,0,150);
  TH1D* hmass_lbl_pt  = new TH1D("hmass_lbl_pt","",75,0,150);
  TH1D* hmass_lbl_acop  = new TH1D("hmass_lbl_acop","",75,0,150);

  lbl->Project(hmass_lbl_goodPho->GetName(), "vSum_M",swiss_cross);
  lbl->Project(hmass_lbl_inv->GetName(), "vSum_M","vSum_M>5"  && swiss_cross );
  lbl->Project(hmass_lbl_ch->GetName(), "vSum_M",no_extrk && "vSum_M>5");
  lbl->Project(hmass_lbl_neu->GetName(), "vSum_M",no_extrk && no_addittional_tower && "vSum_M>5" );
  lbl->Project(hmass_lbl_zdc->GetName(), "vSum_M",no_extrk && no_addittional_tower && "vSum_M>5" );
  lbl->Project(hmass_lbl_pt->GetName(), "vSum_M", no_extrk && no_addittional_tower && "vSum_M>5 && vSum_Pt<2" );
  lbl->Project(hmass_lbl_acop->GetName(), "vSum_M",no_extrk && no_addittional_tower &&  "vSum_M>5 && vSum_Pt<2 && pho_acop<0.01" );


  hmass_lbl_ch->Scale(norm_exgg);  hmass_lbl_neu->Scale(norm_exgg); hmass_lbl_inv->Scale(norm_exgg);  hmass_lbl_goodPho->Scale(norm_exgg); 
  hmass_lbl_pt->Scale(norm_exgg);   hmass_lbl_acop->Scale(norm_exgg); hmass_lbl_zdc->Scale(norm_exgg);


  TH1D* hmass_mcsl_goodPho   = new TH1D("hmass_mcsl_goodPho","",75,0,150);
  TH1D* hmass_mcsl_ch   = new TH1D("hmass_mcsl_ch","",75,0,150);
  TH1D* hmass_mcsl_neu  = new TH1D("hmass_mcsl_neu","",75,0,150);
  TH1D* hmass_mcsl_zdc  = new TH1D("hmass_mcsl_zdc","",75,0,150);
  TH1D* hmass_mcsl_inv  = new TH1D("hmass_mcsl_inv","",75,0,150);
  TH1D* hmass_mcsl_pt  = new TH1D("hmass_mcsl_pt","",75,0,150);
  TH1D* hmass_mcsl_acop  = new TH1D("hmass_mcsl_acop","",75,0,150);

  mcsl->Project(hmass_mcsl_goodPho->GetName(), "vSum_M",swiss_cross);
  mcsl->Project(hmass_mcsl_inv->GetName(), "vSum_M","vSum_M>5"  && swiss_cross  );
  mcsl->Project(hmass_mcsl_ch->GetName(), "vSum_M",no_extrk && "vSum_M>5");
  mcsl->Project(hmass_mcsl_neu->GetName(), "vSum_M",no_extrk && no_addittional_tower && "vSum_M>5" );
  mcsl->Project(hmass_mcsl_zdc->GetName(), "vSum_M",no_extrk && no_addittional_tower && "vSum_M>5" );
  mcsl->Project(hmass_mcsl_pt->GetName(), "vSum_M", no_extrk && no_addittional_tower && "vSum_M>5 && vSum_Pt<2" );
  mcsl->Project(hmass_mcsl_acop->GetName(), "vSum_M",no_extrk && no_addittional_tower &&  "vSum_M>5 && vSum_Pt<2 && pho_acop<0.01" );

  lumiNormSL = 0.346834;
  hmass_mcsl_ch->Scale(lumiNormSL);  hmass_mcsl_neu->Scale(lumiNormSL); hmass_mcsl_inv->Scale(lumiNormSL);  hmass_mcsl_goodPho->Scale(lumiNormSL); 
  hmass_mcsl_pt->Scale(lumiNormSL);   hmass_mcsl_acop->Scale(lumiNormSL);  hmass_mcsl_zdc->Scale(lumiNormSL);



  // cep 
  TH1D* hmass_cep_goodPho   = new TH1D("hmass_cep_goodPho","",75,0,150);
  TH1D* hmass_cep_ch   = new TH1D("hmass_cep_ch","",75,0,150);
  TH1D* hmass_cep_neu  = new TH1D("hmass_cep_neu","",75,0,150);
  TH1D* hmass_cep_zdc  = new TH1D("hmass_cep_zdc","",75,0,150);
  TH1D* hmass_cep_inv  = new TH1D("hmass_cep_inv","",75,0,150);
  TH1D* hmass_cep_pt  = new TH1D("hmass_cep_pt","",75,0,150);
  TH1D* hmass_cep_acop  = new TH1D("hmass_cep_acop","",75,0,150);

  cep->Project(hmass_cep_goodPho->GetName(), "vSum_M",swiss_cross);
  cep->Project(hmass_cep_inv->GetName(), "vSum_M","vSum_M>5"  && swiss_cross );
  cep->Project(hmass_cep_ch->GetName(), "vSum_M",no_extrk && "vSum_M>5");
  cep->Project(hmass_cep_neu->GetName(), "vSum_M",no_extrk && no_addittional_tower && "vSum_M>5" );
  cep->Project(hmass_cep_zdc->GetName(), "vSum_M",no_extrk && no_addittional_tower && "vSum_M>5" );
  cep->Project(hmass_cep_pt->GetName(), "vSum_M", no_extrk && no_addittional_tower && "vSum_M>5 && vSum_Pt<2" );
  cep->Project(hmass_cep_acop->GetName(), "vSum_M",no_extrk && no_addittional_tower &&  "vSum_M>5 && vSum_Pt<2 && pho_acop<0.01" );


  hmass_cep_ch->Scale(norm_cep);  hmass_cep_neu->Scale(norm_cep); hmass_cep_inv->Scale(norm_cep);  hmass_cep_goodPho->Scale(norm_cep); 
  hmass_cep_pt->Scale(norm_cep);   hmass_cep_acop->Scale(norm_cep); hmass_cep_zdc->Scale(norm_cep);





  // cepIncoh 
  TH1D* hmass_cepIncoh_goodPho   = new TH1D("hmass_cepIncoh_goodPho","",75,0,150);
  TH1D* hmass_cepIncoh_ch   = new TH1D("hmass_cepIncoh_ch","",75,0,150);
  TH1D* hmass_cepIncoh_neu  = new TH1D("hmass_cepIncoh_neu","",75,0,150);
  TH1D* hmass_cepIncoh_zdc  = new TH1D("hmass_cepIncoh_zdc","",75,0,150);
  TH1D* hmass_cepIncoh_inv  = new TH1D("hmass_cepIncoh_inv","",75,0,150);
  TH1D* hmass_cepIncoh_pt  = new TH1D("hmass_cepIncoh_pt","",75,0,150);
  TH1D* hmass_cepIncoh_acop  = new TH1D("hmass_cepIncoh_acop","",75,0,150);

  cepIncoh->Project(hmass_cepIncoh_goodPho->GetName(), "vSum_M",swiss_cross);
  cepIncoh->Project(hmass_cepIncoh_inv->GetName(), "vSum_M","vSum_M>5"  && swiss_cross );
  cepIncoh->Project(hmass_cepIncoh_ch->GetName(), "vSum_M",no_extrk && "vSum_M>5");
  cepIncoh->Project(hmass_cepIncoh_neu->GetName(), "vSum_M",no_extrk && no_addittional_tower && "vSum_M>5" );
  cepIncoh->Project(hmass_cepIncoh_zdc->GetName(), "vSum_M",no_extrk && no_addittional_tower && "vSum_M>5" );
  cepIncoh->Project(hmass_cepIncoh_pt->GetName(), "vSum_M", no_extrk && no_addittional_tower && "vSum_M>5 && vSum_Pt<2" );
  cepIncoh->Project(hmass_cepIncoh_acop->GetName(), "vSum_M",no_extrk && no_addittional_tower &&  "vSum_M>5 && vSum_Pt<2 && pho_acop<0.01" );


  hmass_cepIncoh_ch->Scale(norm_cepIncoh);  hmass_cepIncoh_neu->Scale(norm_cepIncoh); hmass_cepIncoh_inv->Scale(norm_cepIncoh);  hmass_cepIncoh_goodPho->Scale(norm_cepIncoh); 
  hmass_cepIncoh_pt->Scale(norm_cepIncoh);   hmass_cepIncoh_acop->Scale(norm_cepIncoh); hmass_cepIncoh_zdc->Scale(norm_cepIncoh);



  hmass_cep_ch->Add(hmass_cepIncoh_ch);  hmass_cep_neu->Add(hmass_cepIncoh_neu); hmass_cep_inv->Add(hmass_cepIncoh_inv);  
  hmass_cep_goodPho->Add(hmass_cepIncoh_goodPho); 
  hmass_cep_pt->Add(hmass_cepIncoh_pt);   hmass_cep_acop->Add(hmass_cepIncoh_acop); hmass_cep_zdc->Add(hmass_cepIncoh_zdc);

  cout << "Good photon  & " << hmass_data_goodPho->Integral() <<"  &  " <<hmass_lbl_goodPho->Integral() <<"  &  " << hmass_mcsl_goodPho->Integral() << endl;
  cout << "diele m >5   & " <<  hmass_data_inv->Integral() <<"  &  " << hmass_lbl_inv->Integral() <<"  &  " << hmass_mcsl_inv->Integral() << endl;
  cout << "chrg excl  & " << hmass_data_ch->Integral() <<"  &  " <<hmass_lbl_ch->Integral() <<"  &  " << hmass_mcsl_ch->Integral() << endl;
  cout << "neu excl   & " << hmass_data_neu->Integral() <<"  &  " <<  hmass_lbl_neu->Integral() <<"  &  " <<  hmass_mcsl_neu->Integral() << endl;
  cout << "zdc excl   & " << hmass_data_zdc->Integral() <<"  &  " <<  hmass_lbl_zdc->Integral() <<"  &  " <<  hmass_mcsl_zdc->Integral() << endl;
  cout << "pt < 1: & " << hmass_data_pt->Integral()<<"  &  " << hmass_lbl_pt->Integral() <<"  &  " << hmass_mcsl_pt->Integral() << endl;
  cout << "acop < 0.01:    & "<< hmass_data_acop->Integral() <<"  &  " <<hmass_lbl_acop->Integral() <<"  &  " <<hmass_mcsl_acop->Integral() << endl;


  cout << "Good photon  & " << hmass_cep_goodPho->Integral() << endl;
  cout << "diele m >5   & " <<  hmass_cep_inv->Integral()  << endl;
  cout << "chrg excl  & " << hmass_cep_ch->Integral() << endl;
  cout << "neu excl   & " << hmass_cep_neu->Integral() << endl;
  cout << "zdc excl   & " << hmass_cep_zdc->Integral() <<endl;
  cout << "pt < 1: & " << hmass_cep_pt->Integral()<< endl;
  cout << "acop < 0.01:    & "<< hmass_cep_acop->Integral() <<endl;



}


