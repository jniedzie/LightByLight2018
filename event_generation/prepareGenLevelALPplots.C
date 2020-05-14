
string basePath = "/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_alps/lhe_superchic/merged_alps_";
string fileSuffix = "GeV.lhe";
vector<int> alpMasses = { 5, 6, 9, 11, 14, 16, 22, 30, 50, 90 };
string outFileName = "results/raw_plots_alp_4p5.root";

double maxEta = 4.5;

void prepareGenLevelALPplots()
{
  istringstream curstring;
    
  TFile *outFile = new TFile(outFileName.c_str(), "recreate");
  outFile->cd();
  
  for(int mass : alpMasses){
    cout<<"Processing mass: "<<mass<<endl;
    string histName = "axion"+to_string(mass);
    TH1D *massHist = new TH1D(histName.c_str(), histName.c_str(), 80, 0, 200);
    
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
        double eta1 = particle1.Eta();
        double eta2 = particle2.Eta();
        
        if(fabs(eta1) < maxEta && fabs(eta2) < maxEta){
          TLorentzVector particleSum(0.,0.,0.,0.);
          particleSum = particle1 + particle2;
          massHist->Fill(particleSum.M());
          nEventsPassing++;
        }
      }
    }
    massHist->Write();
    lheFile.close();
    cout<<"N events generated: "<<nEventsGenerated<<"\tpassing: "<<nEventsPassing<<endl;
  }
  
  outFile->Close();
}
