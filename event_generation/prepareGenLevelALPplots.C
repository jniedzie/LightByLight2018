
string basePath = "/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_alps/lhe_superchic/merged_alps_";
string fileSuffix = "GeV.lhe";
vector<int> alpMasses = { 5, 6, 9, 11, 14, 16, 22, 30, 50, 90 };
string outFileName = "results/raw_plots_alp_sc.root";

map<string, tuple<string, int, double, double>> histParams = {
// name                      title                nBins min     max
  {"pair_m"     , make_tuple("Pair dN/dm"             , 80  ,  0.0  , 200.  )},
  {"pair_m_2p4" , make_tuple("Pair dN/dm (|#eta|<2.4)", 80  ,  0.0  , 200.  )},
  {"pair_m_3p0" , make_tuple("Pair dN/dm (|#eta|<3.0)", 80  ,  0.0  , 200.  )},
  {"pair_m_4p0" , make_tuple("Pair dN/dm (|#eta|<4.0)", 80  ,  0.0  , 200.  )},
  {"pair_m_4p5" , make_tuple("Pair dN/dm (|#eta|<4.5)", 80  ,  0.0  , 200.  )},
  
  {"pair_pt"    , make_tuple("Pair dN/dp_{T}"         , 100 ,  0.0  , 0.5   )},
  {"pair_pz"    , make_tuple("Pair dN/dp_{z}"         , 150 ,  0.0  , 1500. )},
  {"pair_y"     , make_tuple("Pair dN/dy"             , 100 , -10.0 , 10.0  )},
  {"pair_aco"   , make_tuple("Pair dN/dA_{#phi}"      , 500 ,  0    , 1.0   )},
  
  {"single_pt"  , make_tuple("Single dN/dp_{T}"       , 1000, 0.0   , 100.  )},
  {"single_pz"  , make_tuple("Single dN/dp_{z}"       , 1000, 0.0   , 1000. )},
  {"single_y"   , make_tuple("Single dN/dy"           , 100 , -10.0 , 10.0  )},
  {"single_eta" , make_tuple("Signle dN/d#eta"        , 100 , -10.0 , 10.0  )},
  {"single_phi" , make_tuple("Single dN/d#phi"        , 100 , -4    , 4     )},
};

double getAcoplanarity(const TLorentzVector &particle1, const TLorentzVector &particle2)
{
  double phi1 = particle1.Phi();
  double phi2 = particle2.Phi();
  
  // Make sure that angles are in range [0, 2π)
  while(phi1 < 0)               phi1 += 2*TMath::Pi();
  while(phi1 >= 2*TMath::Pi())  phi1 -= 2*TMath::Pi();
  
  while(phi2 < 0)               phi2 += 2*TMath::Pi();
  while(phi2 >= 2*TMath::Pi())  phi2 -= 2*TMath::Pi();
  
  double deltaPhi = fabs(phi2-phi1);
  
  // Make sure that Δφ is in range [0, π]
  if(deltaPhi > TMath::Pi()) deltaPhi = 2*TMath::Pi() - deltaPhi;
  
  // Calcualte acoplanarity
  double aco = 1 - deltaPhi/TMath::Pi();
  
  return aco;
}

void prepareGenLevelALPplots()
{
  istringstream curstring;
    
  TFile *outFile = new TFile(outFileName.c_str(), "recreate");
  outFile->cd();
  
  for(int mass : alpMasses){
    cout<<"Processing mass: "<<mass<<endl;
    
    map<string, TH1D*> hists;
    
    string axionName = "_axion"+to_string(mass);
    
    for(auto &[name, paramsTuple] : histParams){
      auto &[title, nBins, min, max] = paramsTuple;
    
      string histName = name+axionName;
      hists[histName] = new TH1D(histName.c_str(), title.c_str(), nBins, min, max);
    }
    
    int nHighAco=0;
    ifstream lheFile((basePath+to_string(mass)+fileSuffix).c_str());
    
    if(!lheFile.good()){
      cout<<"Could not open file: "<<basePath+to_string(mass)+fileSuffix<<endl;
    }
    
    int nEventsGenerated = 0;
    int nEventsPassing = 0;
    
    while(lheFile.good()){
      string line;
      getline(lheFile,line);
      
      curstring.clear();
      curstring.str(line);
      
      if(line.find("<event>")!=string::npos){
        nEventsGenerated++;
        
        TLorentzVector particle1(0.,0.,0.,0.);
        TLorentzVector particle2(0.,0.,0.,0.);
        bool first=true;
        
        while(line.find("</event>")==string::npos &&
              lheFile.good()){
          getline(lheFile,line);
          curstring.clear();
          curstring.str(line);
          
          double pdgID, useless, p1[4];
          
          curstring >> pdgID;
          for(int i=0;i<5;i++){curstring >> useless;}
          curstring >> p1[0] >> p1[1] >> p1[2] >> p1[3];
          for(int i=0;i<3;i++){curstring >> useless;}
          
          if((pdgID == 22) && first){
            particle1.SetPxPyPzE(p1[0],p1[1],p1[2],p1[3]);
            first=false;
          }
          else if((pdgID == 22) && !first){
            particle2.SetPxPyPzE(p1[0],p1[1],p1[2],p1[3]);
          }
        }
        
        hists["single_y"+axionName]->Fill(particle1.Rapidity());
        hists["single_eta"+axionName]->Fill(particle1.Eta());
        hists["single_pt"+axionName]->Fill(particle1.Pt());
        hists["single_pz"+axionName]->Fill(particle1.Pz());
        hists["single_phi"+axionName]->Fill(particle1.Phi());
        
        hists["single_y"+axionName]->Fill(particle2.Rapidity());
        hists["single_eta"+axionName]->Fill(particle2.Eta());
        hists["single_pt"+axionName]->Fill(particle2.Pt());
        hists["single_pz"+axionName]->Fill(particle2.Pz());
        hists["single_phi"+axionName]->Fill(particle2.Phi());
        
        
        TLorentzVector particleSum(0.,0.,0.,0.);
        particleSum = particle1 + particle2;
        
        double eta1 = fabs(particle1.Eta());
        double eta2 = fabs(particle2.Eta());
        
        hists["pair_m"+axionName]->Fill(particleSum.M());
        hists["pair_pt"+axionName]->Fill(particleSum.Pt());
        hists["pair_pz"+axionName]->Fill(particleSum.Pz());
        hists["pair_y"+axionName]->Fill(particleSum.Rapidity());
        hists["pair_aco"+axionName]->Fill(getAcoplanarity(particle1, particle2));
        
        if(eta1 < 2.4 && eta2 < 2.4) hists["pair_m_2p4"+axionName]->Fill(particleSum.M());
        if(eta1 < 3.0 && eta2 < 3.0) hists["pair_m_3p0"+axionName]->Fill(particleSum.M());
        if(eta1 < 4.0 && eta2 < 4.0) hists["pair_m_4p0"+axionName]->Fill(particleSum.M());
        if(eta1 < 4.5 && eta2 < 4.5) hists["pair_m_4p5"+axionName]->Fill(particleSum.M());
      }
    }
    
    for(auto &[name, hist] : hists) hist->Write();
    
    lheFile.close();
    cout<<"N events generated: "<<nEventsGenerated<<endl;
  }
  
  outFile->Close();
}
