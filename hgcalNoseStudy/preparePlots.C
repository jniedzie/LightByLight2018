

int nFiles = 1;

string basePath = "./";
string baseFileName = "evrec_p";
string fileExtension = ".out";

string outFileName = "alp_hists.root";

map<string, TH1D*> hists;

vector<tuple<string, string, string, string, int, double, double>> histParams = {
  {"pair_mass"            , "dN/dm"               , "m (GeV)", "Entries" , 200, 0.0, 100.0 },
  {"pair_mass_eta_le_4"   , "dN/dm (|#eta| < 4.0)", "m (GeV)", "Entries" , 200, 0.0, 100.0 },
  {"pair_mass_eta_le_3"   , "dN/dm (|#eta| < 3.0)", "m (GeV)", "Entries" , 200, 0.0, 100.0 },
  {"pair_mass_eta_le_2p4" , "dN/dm (|#eta| < 2.4)", "m (GeV)", "Entries" , 200, 0.0, 100.0 },
  
  //  TH1F *pt_pair_distrib = new TH1F ("pt_pair_distrib","dN/dp_{T}",nBins_pt_pair,ptmin,ptmax);
  //  TH1F *y_pair_distrib = new TH1F ("y_pair_distrib", "dN/dy", nBins_y_pair, ymin, ymax);
  //  TH1F *aco_pair_distrib = new TH1F("aco_pair_distrib","dN/dA_{#phi}",nBins,0,0.1);
  //  TH1F *theta_pair_distrib = new TH1F("theta_pair_distrib","dN/d#theta",nBins,0,Pi);
  //  TH1F *pz_pair_distrib = new TH1F ("pz_pair_distrib","dN/dp_{L}",nBins,plmin,plmax);
  //
  //  TH1F *y_single = new TH1F ("y_single", "dN/dy", nBins, ymin, ymax);
  //  TH1F *eta_single = new TH1F ("eta_single", "dN/d#eta", nBins_eta_single, etamin, etamax);
  //  TH1F *pt_single = new TH1F ("pt_single","dN/dp_{T}",nBins_pt_single,ptmin_single,ptmax_single);
  //  TH1F *pz_single = new TH1F ("pz_single","dN/dp_{L}",nBins*10,plmin,plmax);
  //  TH1F *phi_single = new TH1F ("phi_single","dN/d#phi",nBins_phi_single,-4,4);
  //  int nBins = 100;
  //  int nBins_m = 200;
  //  double min_m = 0., max_m = 100.;
  //
  //  int nBins_pt_pair = 300;
  //  int nBins_pt_single = 100;
  //  double ptmin_single=0.0, ptmax_single=99; // GeV
  //
  //  double ptmin=0.0, ptmax=0.5 ; // GeV
  //  double plmin=0.0, plmax=1000. ; // GeV
  //
  //  int nBins_y_pair = 105;double ymin=-6., ymax=6.;
  //
  //  int nBins_eta_single = 105;double etamin=-10., etamax=10.;
  //  int nBins_phi_single = 70;;
  //  pt_pair_distrib->GetXaxis()->SetTitle("p_{T} #left[ GeV/c #right]");
  //   pt_pair_distrib->GetYaxis()->SetTitle("Entries/( MeV/c)");
  //
  //   pz_pair_distrib->GetXaxis()->SetTitle("p_{L} #left[ GeV/c #right]");
  //   pz_pair_distrib->GetYaxis()->SetTitle("Entries/( MeV/c)");
  //
  //   aco_pair_distrib->GetXaxis()->SetTitle("#phi");
  //   aco_pair_distrib->GetYaxis()->SetTitle("Entries");
  //
  //   y_pair_distrib->GetXaxis()->SetTitle("y");
  //   y_pair_distrib->GetYaxis()->SetTitle("Entries");
  //
  //   y_single->GetXaxis()->SetTitle("y single");
  //   y_single->GetYaxis()->SetTitle("Entries");
  //   eta_single->GetXaxis()->SetTitle("#eta single");
  //   eta_single->GetYaxis()->SetTitle("Entries");
  //   pt_single->GetXaxis()->SetTitle("p_{T} single");
  //   pt_single->GetYaxis()->SetTitle("Entries/( MeV/c)");
  //
  //   pz_single->GetXaxis()->SetTitle("p_{L} single");
  //   pz_single->GetYaxis()->SetTitle("Entries/( MeV/c)");
  //
};

void fillHistograms(TLorentzVector particle1, TLorentzVector particle2)
{
  TLorentzVector particleSum(0.,0.,0.,0.);
  particleSum = particle1 + particle2;
  
  //        y_single->Fill(particle1.Rapidity());
  //        eta_single->Fill(particle1.Eta());
  //        pt_single->Fill(particle1.Pt());
  //        pz_single->Fill(particle1.Pz());
  //        phi_single->Fill(particle1.Phi());
  //
  //        y_single->Fill(particle2.Rapidity());
  //        eta_single->Fill(particle2.Eta());
  //        pt_single->Fill(particle2.Pt());
  //        pz_single->Fill(particle2.Pz());
  //        phi_single->Fill(particle2.Phi());
  
  hists["pair_mass"]->Fill(particleSum.M());
  
  if(fabs(particle1.Eta()) < 4.0 && fabs(particle2.Eta()) < 4.0) hists["pair_mass_eta_le_4"]->Fill(particleSum.M());
  if(fabs(particle1.Eta()) < 3.0 && fabs(particle2.Eta()) < 3.0) hists["pair_mass_eta_le_3"]->Fill(particleSum.M());
  if(fabs(particle1.Eta()) < 2.4 && fabs(particle2.Eta()) < 2.4) hists["pair_mass_eta_le_2p4"]->Fill(particleSum.M());
  
  //        pt_pair_distrib->Fill(particleSum.Pt());
  //        y_pair_distrib->Fill(particleSum.Rapidity());
  
  double Dphi=1 - TMath::Abs(TMath::Abs(particle2.Phi()-particle1.Phi()))/TMath::Pi(); // acoplanarity
  //        aco_pair_distrib->Fill(Dphi);
  
  //        theta_pair_distrib->Fill(particleSum.Theta());
  //        pz_pair_distrib->Fill(particleSum.Pz());
}

void loopOnEvents(ifstream &lheFile)
{
  istringstream curstring;
  TLorentzVector particle1(0.,0.,0.,0.);
  TLorentzVector particle2(0.,0.,0.,0.);
  int nEvents=0;
  
  while (lheFile.good()){
    string line;
    getline(lheFile,line);
    curstring.clear();
    curstring.str(line);
    
    if(line.find("<event>")!=string::npos){
      nEvents++;
      
      // digest unnecessary lines
      getline(lheFile,line);
      getline(lheFile,line);
      getline(lheFile,line);
      getline(lheFile,line);
      
      // get params of final state particles
      getline(lheFile,line);
      
      curstring.clear();
      curstring.str(line);
      
      double useless;
      double p1[4], p2[4];
      
      for(int i=0;i<6;i++){curstring >> useless;}
      curstring >> p1[0] >> p1[1] >> p1[2] >> p1[3];
      for(int i=0;i<3;i++){curstring >> useless;}
      
      getline(lheFile,line);
      curstring.clear();
      curstring.str(line);
      
      for(int i=0;i<6;i++){curstring >> useless;}
      curstring >> p2[0] >> p2[1] >> p2[2] >> p2[3];
      for(int i=0;i<3;i++){curstring >> useless;}
      
      particle1.SetPxPyPzE(p1[0],p1[1],p1[2],p1[3]);
      particle2.SetPxPyPzE(p2[0],p2[1],p2[2],p2[3]);
      
      fillHistograms(particle1, particle2);
    }
  }
  cout<<"nEvents:"<<nEvents<<endl;
}

void preparePlots()
{
  for(auto &[name, title, xTitle, yTitle, nBins, min, max] : histParams){
    hists[name] = new TH1D(name.c_str(), title.c_str(), nBins, min, max);
    hists[name]->GetXaxis()->SetTitle(xTitle.c_str());
    hists[name]->GetYaxis()->SetTitle(yTitle.c_str());
  }
  
  for(int iFile=0;iFile<nFiles;iFile++){
    
    string fileName = basePath+baseFileName+to_string(iFile)+fileExtension;
    cout<<"Processing file "<<fileName<<endl;
    ifstream lheFile(fileName.c_str());
    
    loopOnEvents(lheFile);
    
    lheFile.close();
  }
  
  TFile *outFile = new TFile(outFileName.c_str(),"recreate");
  outFile->cd();
  
  for(auto &[title, hist] : hists) hist->Write();
  
  outFile->Close();
  
  
}
