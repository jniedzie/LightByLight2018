//================================================================================================
//
// This macro creates raw, ugly histograms from LHE files.
//

// Set input path and output filename here:

// QED SuperChic
//string basePath = "/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed/lhe_superchic_with_cuts/";
//string outFileName = "results/raw_plots_qed_sc.root";
//int pid1 = 11;
//int pid2 = -11;

// QED Starlight
//string basePath = "/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed/lhe_starlight_with_cuts/";
////string basePath = "./";
//string outFileName = "results/raw_plots_qed_sl.root";
//int pid1 = 11;
//int pid2 = -11;

// LbL SuperChic
//string basePath = "/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_lbl/lhe_superchic/";
//string outFileName = "results/raw_plots_lbl_sc.root";
//int pid1 = 22;
//int pid2 = 22;

// CEP SuperChic
string basePath = "/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_cep/lhe_superchic/";
  string outFileName = "results/raw_plots_cep_sc.root";
int pid1 = 22;
int pid2 = 22;

// Say how many files (at most) to process:
int nFiles = 50;

// Here modify titles, axis labels, number of bins and histogram ranges.
// If you add a new histogram, you must fill it in loops over particels in the main loop.

map<string, tuple<string, int, double, double>> histParams = {
// name                      title                nBins min     max
  {"pair_m"     , make_tuple("Pair dN/dm"        , 100 ,  0.0  , 100.  )},
  {"pair_pt"    , make_tuple("Pair dN/dp_{T}"    , 100 ,  0.0  , 0.5   )},
  {"pair_pz"    , make_tuple("Pair dN/dp_{z}"    , 150 ,  0.0  , 1500. )},
  {"pair_y"     , make_tuple("Pair dN/dy"        , 100 , -10.0 , 10.0  )},
  {"pair_aco"   , make_tuple("Pair dN/dA_{#phi}" , 500 ,  0    , 1.0   )},
  
  {"single_pt"  , make_tuple("Single dN/dp_{T}"  , 1000, 0.0   , 100.  )},
  {"single_pz"  , make_tuple("Single dN/dp_{z}"  , 1000, 0.0   , 1000. )},
  {"single_y"   , make_tuple("Single dN/dy"      , 100 , -10.0 , 10.0  )},
  {"single_eta" , make_tuple("Signle dN/d#eta"   , 100 , -10.0 , 10.0  )},
  {"single_phi" , make_tuple("Single dN/d#phi"   , 100 , -4    , 4     )},
};

// Normally no need to modify below this point.
//
//================================================================================================

#include <dirent.h>

vector<string> GetFilesInPath()
{
  vector<string> files;
  
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir (basePath.c_str())) != NULL) {
    while ((ent = readdir (dir)) != NULL) {
      files.push_back(ent->d_name);
    }
    closedir (dir);
  }
  else{
    cout<<"Could not open directory: "<<basePath<<endl;
  }
  vector<string> lheFiles;
  
  for(auto fileName : files){
    if (fileName.find(".dat") != std::string::npos ||
        fileName.find(".lhe") != std::string::npos ||
        fileName.find(".out") != std::string::npos){
      
      if (fileName.find("merged") != std::string::npos) continue;
      if (fileName.find(".sys.") != std::string::npos) continue;
      
      lheFiles.push_back(fileName);
    }
  }
  
  return lheFiles;
}

void ReadParticlesFromFiles(vector<TLorentzVector> &particles1, vector<TLorentzVector> &particles2, vector<TLorentzVector> &particlesSum);

int nEvents=0;

void plotFromLHE()
{
  map<string, TH1D*> hists;
  
  for(auto &[name, paramsTuple] : histParams){
    auto &[title, nBins, min, max] = paramsTuple;
    
    hists[name] = new TH1D(name.c_str(), title.c_str(), nBins, min, max);
  }
  
  vector<TLorentzVector> particles1;
  vector<TLorentzVector> particles2;
  vector<TLorentzVector> particlesSum;
  
  ReadParticlesFromFiles(particles1, particles2, particlesSum);
  
  cout<<"N particles 1: "<<particles1.size()<<endl;
  cout<<"N particles 2: "<<particles2.size()<<endl;
  
  for(int i=0; i<min(particles1.size(), particles1.size()); i++){
    if(i%100000==0) cout<<"Processing particle "<<i<<endl;
    
    hists["single_y"]->Fill(particles1[i].Rapidity());
    hists["single_eta"]->Fill(particles1[i].Eta());
    hists["single_pt"]->Fill(particles1[i].Pt());
    hists["single_pz"]->Fill(particles1[i].Pz());
    hists["single_phi"]->Fill(particles1[i].Phi());
    
    hists["single_y"]->Fill(particles2[i].Rapidity());
    hists["single_eta"]->Fill(particles2[i].Eta());
    hists["single_pt"]->Fill(particles2[i].Pt());
    hists["single_pz"]->Fill(particles2[i].Pz());
    hists["single_phi"]->Fill(particles2[i].Phi());
    
    double phi1 = particles1[i].Phi();
    double phi2 = particles2[i].Phi();
    
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
    if(aco>0.2){
      cout<<"filling with high aco:"<<aco<<endl;
    }
    hists["pair_aco"]->Fill(aco);
  }
  
  for(auto p :particlesSum){
    hists["pair_m"]->Fill(p.M());
    hists["pair_pt"]->Fill(p.Pt());
    hists["pair_pz"]->Fill(p.Pz());
    hists["pair_y"]->Fill(p.Rapidity());
  }
  
  TFile *outFile = new TFile(outFileName.c_str(),"recreate");
  outFile->cd();
  for(auto &[name, hist] : hists) hist->Write();
  outFile->Close();
  
  cout<<"nEvents:"<<nEvents<<endl;
}

void ReadParticlesFromFiles(vector<TLorentzVector> &particles1,
                            vector<TLorentzVector> &particles2,
                            vector<TLorentzVector> &particlesSum)
{
  istringstream curstring;
  
  vector<string> files = GetFilesInPath();
  
  int iFiles=0;
  
//  files = {
//    "starlight_QED_p9555.lhe"
//  };
  
  for(auto fileName : files){
    
    if(iFiles >= nFiles) break;
    iFiles++;
    
    int nHighAco=0;
    cout<<"Processing file "<<fileName<<endl;
    ifstream lheFile((basePath+"/"+fileName).c_str());
    
    while(lheFile.good()){
      string line;
      getline(lheFile,line);
      
      curstring.clear();
      curstring.str(line);
      
      if(line.find("<event>")!=string::npos){
        nEvents++;
        
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
          
         
          if(pid1 != pid2){ // electrons
            if(pdgID == pid1){
              particle1.SetPxPyPzE(p1[0],p1[1],p1[2],p1[3]);
              particles1.push_back(particle1);
            }
            else if(pdgID == pid2){
              particle2.SetPxPyPzE(p1[0],p1[1],p1[2],p1[3]);
              particles2.push_back(particle2);
            }
          }
          else{ // photons
            if((pdgID == pid1) && first){
              particle1.SetPxPyPzE(p1[0],p1[1],p1[2],p1[3]);
              particles1.push_back(particle1);
              first=false;
            }
            else if((pdgID == pid2) && !first){
              particle2.SetPxPyPzE(p1[0],p1[1],p1[2],p1[3]);
              particles2.push_back(particle2);
            }
          }
        }
        double phi1 = particles1.back().Phi();
        double phi2 = particles2.back().Phi();
        
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

        if(aco > 0.2){
          cout<<"High aco in file "<<fileName<<endl;
          nHighAco++;
          particles1.back().Print();
          particles2.back().Print();
        }
        
        TLorentzVector particleSum(0.,0.,0.,0.);
        particleSum = particle1 + particle2;
        particlesSum.push_back(particleSum);
        
        if(particlesSum.size() > 3e7) return;
      }
    }
    if(nHighAco>0){
      cout<<"nHighAco: "<<nHighAco<<endl<<endl;
    }
    lheFile.close();
  }
}
