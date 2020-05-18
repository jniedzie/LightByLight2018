
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
      hists[name] = new TH1D(histName.c_str(), title.c_str(), nBins, min, max);
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
        
        hists["single_y"+axionName]->Fill(particles1[i].Rapidity());
        hists["single_eta"+axionName]->Fill(particles1[i].Eta());
        hists["single_pt"+axionName]->Fill(particles1[i].Pt());
        hists["single_pz"+axionName]->Fill(particles1[i].Pz());
        hists["single_phi"+axionName]->Fill(particles1[i].Phi());
        
        hists["single_y"+axionName]->Fill(particles2[i].Rapidity());
        hists["single_eta"+axionName]->Fill(particles2[i].Eta());
        hists["single_pt"+axionName]->Fill(particles2[i].Pt());
        hists["single_pz"+axionName]->Fill(particles2[i].Pz());
        hists["single_phi"+axionName]->Fill(particles2[i].Phi());
        
        
        TLorentzVector particleSum(0.,0.,0.,0.);
        particleSum = particle1 + particle2;
        
        double eta1 = fabs(particle1.Eta());
        double eta2 = fabs(particle2.Eta());
        
        hists["pair_m"+axionName]->Fill(p.M());
        hists["pair_pt"+axionName]->Fill(p.Pt());
        hists["pair_pz"+axionName]->Fill(p.Pz());
        hists["pair_y"+axionName]->Fill(p.Rapidity());
        
        if(eta1 < 2.4 && eta2 < 2.4) hists["pair_m_2p4"+axionName]->Fill(p.M());
        if(eta1 < 3.0 && eta2 < 3.0) hists["pair_m_3p0"+axionName]->Fill(p.M());
        if(eta1 < 4.0 && eta2 < 4.0) hists["pair_m_4p0"+axionName]->Fill(p.M());
        if(eta1 < 4.5 && eta2 < 4.5) hists["pair_m_4p5"+axionName]->Fill(p.M());
      }
    }
    
    for(auto &[name, hist] : hists) hist->Write();
    
    lheFile.close();
    cout<<"N events generated: "<<nEventsGenerated<<endl;
  }
  
  outFile->Close();
}
