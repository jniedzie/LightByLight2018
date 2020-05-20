#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TF1.h>

string slBaseName = "sl_qed_q2_bm4";
string scBaseName = "sc_qed_q2";

//string slBaseName = "histos_PbPb_gammagamma_5TeV";
//string scBaseName = "sc_lbl";

double crossSection = 20.6e3;
double luminosity = 363.959;

//double scScale = 1.086453e-01 * crossSection * 4.82/4.73 * luminosity; // cross section from superchic3
//double slScale = 1.086453e-01 * crossSection * luminosity; // cross section from starlight

double slScale = 1.801; // Starlight 2.99, BM=4
//double slScale = 2.256; // Starlight 2.99, BM=5
// double scScale = 2.517; // SC 3.0
double scScale = 2.697; // SC 3.02

//double slScale = 0.9*1.85;
//double scScale = 1.04;

bool scale=true;

TFile *scFile, *slFile;

TGraphAsymmErrors* GetAsymmGraph(TH1F *hist)
{
  TGraphAsymmErrors *graph = new TGraphAsymmErrors();
  
  for(int i=0;i<hist->GetNbinsX();i++){
    double val = hist->GetBinContent(i);
    
    if(val != 0){
      graph->SetPoint(i, hist->GetBinCenter(i),val);
      
      double errX = hist->GetXaxis()->GetBinWidth(i)/2.;
      double errY = hist->GetBinError(i);
      double errYdown = errY;
      
      if(val - errY < 0) errYdown = val;
      
      graph->SetPointError(i,errX,errX, errYdown,errY);
      
    }
  }
  
  graph->SetMarkerStyle(20);
  graph->SetMarkerSize(0.1);
  graph->SetMarkerColor(kGreen+2);
  graph->SetLineColor(kGreen+2);
  
  return graph;
}

void Draw(const char* histName,const char* altHistName,double minX,double maxX, int rebin=1, bool log=false)
{
  TCanvas *c1 = new TCanvas(histName,histName,600,800);
  c1->Divide(1,2);
  
  TH1F *scHist = (TH1F*)scFile->Get(histName);
  if(!scHist){
    scHist = (TH1F*)scFile->Get(altHistName);
  }
  TH1F *slHist = (TH1F*)slFile->Get(histName);
  if(!slHist){
    slHist = (TH1F*)slFile->Get(altHistName);
  }
  
  if(!scHist || !slHist){
    cout<<"Hist not found:"<<histName<<"\ttries also:"<<altHistName<<endl;
    return;
  }
  
  if(scale){
    scHist->Scale(scScale/scHist->GetEntries());
    slHist->Scale(slScale/slHist->GetEntries());
  }
  
  scHist->Sumw2();
  slHist->Sumw2();
  scHist->Rebin(rebin);
  slHist->Rebin(rebin);
  
  scHist->SetLineColor(kRed);
  
  c1->cd(1);
  if(log) gPad->SetLogy();
  
  scHist->Draw();
  slHist->Draw("same");
  scHist->GetXaxis()->SetRangeUser(minX,maxX);
  
  double legendW=0.25, legendH=0.20, legendX=0.65, legendY=0.2;
  TLegend *leg = new TLegend(legendX,legendY,legendX+legendW,legendY+legendH);
  leg->AddEntry(scHist,"Superchic3","epl");
  leg->AddEntry(slHist,"STARlight","epl");
  leg->Draw();
  
  c1->cd(2);
  TH1F *ratioBase = new TH1F(*slHist);
  
  cout<<altHistName<<":"<<ratioBase->GetXaxis()->GetBinCenter(1)<<"\t"<<ratioBase->GetXaxis()->GetBinCenter(ratioBase->GetNbinsX())<<endl;
  
  if(ratioBase->GetNbinsX() != scHist->GetNbinsX()){
    cout<<altHistName<<":"<<ratioBase->GetNbinsX()<<endl;
    cout<<"sc:"<<scHist->GetNbinsX()<<endl;
    return;
  }
  
  ratioBase->Divide(scHist);
  
  TGraphAsymmErrors *ratio = GetAsymmGraph(ratioBase);
  TF1 *fun = new TF1("fun","[0]",0,100);
  fun->SetParameter(0,1);
  ratio->Fit(fun);
  
  cout<<"\n\n"<<histName<<" integrals ratio (SL/SC):"<<slHist->Integral()/(double)scHist->Integral()<<"\n\n"<<endl;
  
  ratio->Draw("APE1");
  
  ratio->SetTitle("ratio(STARlight/Superchic3)");
  ratio->GetXaxis()->SetTitle(scHist->GetXaxis()->GetTitle());
  ratio->GetYaxis()->SetTitle("Ratio");
  ratio->GetXaxis()->SetLimits(minX,maxX);
  ratio->SetMaximum(5.0);
  ratio->SetMinimum(0.0);
  
  TLine *line2 = new TLine(minX,1,maxX,1);
  line2->Draw("same");
  
  c1->SaveAs(Form("%s.pdf",histName));
}


void GetRatio()
{
  gStyle->SetOptFit();
  
  scFile = TFile::Open((scBaseName+".root").c_str());
  slFile = TFile::Open((slBaseName+".root").c_str());
  
  Draw("pt_single","h_dNdpT_photons_single",   0,  30.0, 100, true);
  Draw("eta_single","h_dNdeta_photons_single", -10, 10,   1,   false);
  Draw("phi_single","h_dNdphi_photons_single",  -4, 4,    3,   false);
  
  Draw("pt_pair_distrib","h_dNdpT_photons_pair", 0,  0.5,  1,  true);
  Draw("y_pair_distrib","h_dNdy_photons_pair", -6,  6,    1,  false);
  Draw("m_pair_distrib","h_dNdminv_photons_pair",  0,  100,  1,  true);
  Draw("aco_pair_distrib","", 0,  0.1,  2,  true);
}
