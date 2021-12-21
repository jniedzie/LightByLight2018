
#include <iostream>
#include <fstream>
#include <fstream>
#include <sstream>
#include <string>

#include "TLorentzVector.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TMath.h"
#include "TArrow.h"
#include "TH2.h"
#include "TParticle.h"

/*

.L /home/enterria/progs/starlight/convert_starlight2root.C++
convert_starlight("slight.in","starlight_histos.root",sigma_mub_norm)

*/


void convert_starlight2root(const char *infile="slight.out", const char *fileOut="starlight_histos.root", const double sigma_mub=1.)
{

  string temp_string, temp;
  istringstream curstring;

  // HISTOS

  gROOT->Reset();
  gStyle->SetOptStat(11111111);

  double Pi = TMath::Pi();

  Int_t nbins = 100;
  Double_t ptmin=0.0, ptmax=10.0 ; // GeV
  Double_t plmin=0.0, plmax=1000. ; // GeV
  Double_t ymin=-10.;
  Double_t ymax=10.;

  Double_t mmin = 0.;
  Double_t mmax = 20.;

  // Histos

  TH1F * y_pair_distrib = new TH1F ("y_pair_distrib", "dN/dy", nbins, ymin, ymax);
  TH1F * m_pair_distrib = new TH1F ("m_pair_distrib", "dN/dm", nbins, mmin, mmax);
  TH1F * pt_pair_distrib = new TH1F ("pt_pair_distrib","dN/dp_{T}",nbins,ptmin,ptmax);
  //TH1F * phi_pair_distrib = new TH1F("phi_pair_distrib","dN/d#phi",nbins,-Pi,Pi); 
  TH1F * phi_pair_distrib = new TH1F("phi_pair_distrib","dN/d#phi",nbins,0,1.); 
  TH1F * theta_pair_distrib = new TH1F("theta_pair_distrib","dN/d#theta",nbins,0,Pi); 
  TH1F * pz_pair_distrib = new TH1F ("pz_pair_distrib","dN/dp_{L}",nbins,plmin,plmax);
  
  TH1F * y_single = new TH1F ("y_single", "dN/dy", nbins, ymin, ymax);
  TH1F * pt_single = new TH1F ("pt_single","dN/dp_{T}",nbins*10,ptmin,ptmax*10.);
  TH1F * pz_single = new TH1F ("pz_single","dN/dp_{L}",nbins*10,plmin,plmax);
  TH1F * phi_single = new TH1F ("phi_single","dN/d#phi",nbins,-Pi,Pi);

  TH1F * y_pair_distrib_cuts = new TH1F ("y_pair_distrib_cuts", "dN/dy (ET_ecal > 3 GeV)", nbins, ymin, ymax);
  TH1F * m_pair_distrib_cuts = new TH1F ("m_pair_distrib_cuts ", "dN/dm(ET_ecal > 3 GeV)", nbins, mmin, mmax);
  TH1F * pt_pair_distrib_cuts = new TH1F ("pt_pair_distrib_cuts","dN/dp_{T} (ET_ecal > 3 GeV)",nbins,ptmin,ptmax);

  TH1F * decay_asymm_cuts = new TH1F ("decay_asymm_cuts","decay_asymm (ET_ecal > 3 GeV)",nbins,0.,1.);
  TH1F * decay_asymm = new TH1F ("decay_asymm","decay_asymm",nbins,0.,1.);
  TH1F * y_pair_largeasymm = new TH1F ("y_pair_largeasymm","y_pair_largeasymm",nbins,ymin, ymax);

  pt_pair_distrib->GetXaxis()->SetTitle("p_{T} #left[ GeV/c #right]");
  pt_pair_distrib->GetYaxis()->SetTitle("Entries/( MeV/c)");

  pz_pair_distrib->GetXaxis()->SetTitle("p_{L} #left[ GeV/c #right]");
  pz_pair_distrib->GetYaxis()->SetTitle("Entries/( MeV/c)");

  phi_pair_distrib->GetXaxis()->SetTitle("#phi");
  phi_pair_distrib->GetYaxis()->SetTitle("Entries");

  y_pair_distrib->GetXaxis()->SetTitle("y");
  y_pair_distrib->GetYaxis()->SetTitle("Entries");

  y_single->GetXaxis()->SetTitle("y single");
  y_single->GetYaxis()->SetTitle("Entries");
  pt_single->GetXaxis()->SetTitle("p_{T} single");
  pt_single->GetYaxis()->SetTitle("Entries/( MeV/c)");

  pz_single->GetXaxis()->SetTitle("p_{L} single");
  pz_single->GetYaxis()->SetTitle("Entries/( MeV/c)");

  // open file
  std::ifstream in(infile,ios::in);
  // if problems during the opening of the file
  if(!in){
    std::cerr<< "unable to open the file "<< infile << std::endl;
    return;
  }
  cout << "<I> Reading: " << infile << endl; 

  Int_t evtcount =0;
  Int_t L1countrate =0;

  TLorentzVector particle1(0.,0.,0.,0.);
  TLorentzVector particle2(0.,0.,0.,0.);
  TLorentzVector particlesum(0.,0.,0.,0.);

  int first=1;
  double E1 = 0.;

  int countAll=0;
  int countLoss=0;
  
  
  //line by line in the file
  while (getline(in,temp_string)) {
	
	curstring.clear(); // needed when using several tims istringstream::str(string)
	curstring.str(temp_string);

	if(strstr(temp_string.c_str(),"TRACK:")) {

	  double px, py, pz, mass;
	  int useless, part_n, pdg_id;

	  //TRACK:      6   2.9797       3.1399       84.461          1      1      0    -13
	  curstring >> temp >> useless >> px >> py >> pz >> part_n >> useless >> useless >> pdg_id;

	  TParticle p1(pdg_id, 0, 0, 0, 0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	  mass = p1.GetMass();
	  //std::cout << mass << std::endl;

	  double E = TMath::Sqrt(px*px+py*py+pz*pz+mass*mass);

	  // if it is the first particle in the event
	  if(first) {
	    E1 = E;
	    particle1.SetPxPyPzE(px,py,pz,E1);
	    
	    y_single->Fill(particle1.Rapidity());
	    pt_single->Fill(particle1.Pt());
	    pz_single->Fill(particle1.Pz());
	    phi_single->Fill(particle1.Phi());
	    
	    evtcount++;
	    //if(evtcount%100==0)
	    //{
	    cout << "px: " << px <<  " py: " << py <<  " pz: " << pz << " E: " << E1 << endl;
	    //std::cout<<evtcount<<std::endl;
	    //}
	    
	    first=0;
	  }
	  //if it is the second particle in the event
	  else {

	    first=1; // reset to first

	    double E2 = E;
	    particle2.SetPxPyPzE(px,py,pz,E2);
	    
	    //if(evtcount%100==0)
	    //{
	    cout << " px: " << px <<  " py: " << py <<  " pz: " << pz << " E: " << E2 << endl;
	    std::cout<<evtcount<<std::endl;
	    //}
	    
	    // Single
	    
	    y_single->Fill(particle2.Rapidity());
	    pt_single->Fill(particle2.Pt());
	    pz_single->Fill(particle2.Pz());
	    phi_single->Fill(particle2.Phi());
	    
	    double Dphi=TMath::Abs(Pi-TMath::Abs(particle2.Phi()-particle1.Phi())); // acoplanarity
	    
	    double asym = TMath::Abs(E2-E1)/(E2+E1);	    
	    decay_asymm->Fill(asym);
	    
	    // Pairs
	    
	    particlesum = particle1 +particle2;
	    	    
	    if (asym>0.90) {
	      y_pair_largeasymm->Fill(particlesum.Rapidity());
	    }
	    
	    m_pair_distrib->Fill(particlesum.M());
	    y_pair_distrib->Fill(particlesum.Rapidity());
	    pt_pair_distrib->Fill(particlesum.Pt());
	    phi_pair_distrib->Fill(particlesum.Phi());
	    theta_pair_distrib->Fill(particlesum.Theta());
	    pz_pair_distrib->Fill(particlesum.Pz());
	    	    
	    // CUTS L1

	    if ( (particle1.Pt()>2. && TMath::Abs(particle1.Rapidity())<2.5) &&
		 (particle2.Pt()>2. && TMath::Abs(particle2.Rapidity())<2.5) ) {
        countAll++;
        if(   (particle1.Eta() >= 1.444 && particle1.Eta() <= 1.566)
           || (particle2.Eta() >= 1.444 && particle2.Eta() <= 1.566)
           || (particle1.Eta() <= -1.444 && particle1.Eta() >= -1.566)
           || (particle2.Eta() <= -1.444 && particle2.Eta() >= -1.566)
           ){
        countLoss++;
        }
          
        
	      L1countrate++;
	    //phi_pair_distrib->Fill(Dphi);
	      decay_asymm_cuts->Fill(asym);
	      m_pair_distrib_cuts->Fill(particlesum.M());
	      y_pair_distrib_cuts->Fill(particlesum.Rapidity());
	      pt_pair_distrib_cuts->Fill(particlesum.Pt());
	    }
	    

	  } // 2nd particle in event
	  
	} // 'TRACK' LINE
	
  } // reading loop of the input file
  
 
  //plot the distribs
  // TCanvas *c1 = new TCanvas("c1","dN/dm",200,10,700,500);
  //c1->cd();
  //mdistrib->Draw();
  //TH2 *frame = new TH2F("frame","frame",1000,-100.,+100.,100,-2.,2.);
  //frame->Draw();

  m_pair_distrib->GetXaxis()->SetTitle("M #left[ GeV/c^{2} #right]");
  m_pair_distrib->GetYaxis()->SetTitle("Entries/( MeV/c^{2})");
  
  Double_t NEvent=m_pair_distrib->GetEntries();
  double mb2mub = 1e+3;
  
  std::cout<< NEvent<<std::endl;

  TH1F* dsigma_dm_pair = (TH1F*)m_pair_distrib->Clone();
  dsigma_dm_pair->SetName("dsigma_dm_pair");
  dsigma_dm_pair->Scale(sigma_mub*nbins/(NEvent*(mmax-mmin)));
  dsigma_dm_pair->SetTitle("d#sigma/dm");
  dsigma_dm_pair->GetXaxis()->SetTitle("m #left(GeV/c^{2}#right)");
  dsigma_dm_pair->GetYaxis()->SetTitle("d#sigma/dm #mub/(GeV/c^{2})");

  TH1F* dsigma_dpt_pair = (TH1F*)pt_pair_distrib->Clone();
  dsigma_dpt_pair->SetName("dsigma_dpt_pair");
  dsigma_dpt_pair->Scale(sigma_mub*nbins/(NEvent*(ptmax-ptmin)));
  dsigma_dpt_pair->SetTitle("d#sigma/dp_{T}");
  dsigma_dpt_pair->GetXaxis()->SetTitle("p_{T} #left(GeV/c#right)");
  dsigma_dpt_pair->GetYaxis()->SetTitle("d#sigma/dp_{T} #mub/(GeV/c)");

  TH1F* dsigma_dy_pair = (TH1F*)y_pair_distrib->Clone();
  dsigma_dy_pair->SetName("dsigma_dy_pair");
  dsigma_dy_pair->Scale(sigma_mub*nbins/(NEvent*(ymax-ymin)));
  dsigma_dy_pair->SetTitle("d#sigma/dy");
  dsigma_dy_pair->GetXaxis()->SetTitle("y");
  dsigma_dy_pair->GetYaxis()->SetTitle("d#sigma/dy #left(#mub #right)");


  //save the distrib
  TFile f(fileOut,"recreate");
  f.cd();

  m_pair_distrib->Write();
  y_pair_distrib->Write();
  phi_pair_distrib->Write();
  pt_pair_distrib->Write();
  theta_pair_distrib->Write();
  pz_pair_distrib->Write();

  y_single->Write();
  pt_single->Write();
  pz_single->Write();
  phi_single->Write();

  decay_asymm->Write();
  decay_asymm_cuts->Write();
  y_pair_largeasymm->Write();

  m_pair_distrib_cuts->Write();
  y_pair_distrib_cuts->Write();
  pt_pair_distrib_cuts->Write();

  dsigma_dy_pair->Write();
  dsigma_dm_pair->Write();
  dsigma_dpt_pair->Write();

  f.Close();

  cout << " Events that pass the UPC-L1 cuts (ETi>3. GeV and |eta_i|<2.5): " << L1countrate 
       << "(" << L1countrate*100./(double)evtcount << "%)" << endl;

  cout << fileOut << " written " << endl;
 
  cout<<"Count all:"<<countAll<<endl;
  cout<<"Count loss:"<<countLoss<<endl;
  
}
