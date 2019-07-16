//================================================================================================
//
// This macro creates raw, ugly histograms from LHE files.
//


// Set input path and output filename here:

// QED SuperChic
//string basePath = "./mc_qed/lhe_superchic_with_cuts/";
//string outFileName = "raw_plots_qed_sc.root";
//int pid1 = 11;
//int pid2 = -11;

// QED Starlight
//string basePath = "./mc_qed/lhe_starlight_with_cuts/";
//string outFileName = "raw_plots_qed_sl.root";
//int pid1 = 11;
//int pid2 = -11;

// LbL SuperChic
//string basePath = "./mc_lbyl/lhe_superchic/";
//string outFileName = "raw_plots_lbl_sc.root";
//int pid1 = 22;
//int pid2 = 22;

// CEP SuperChic
string basePath = "./mc_cep/lhe_superchic/";
string outFileName = "raw_plots_cep_sc.root";
int pid1 = 22;
int pid2 = 22;

// Say how many files (at most) to process:
int nFiles = 100;

// Here modify titles, axis labels, number of bins and histogram ranges.
// If you add a new histogram, you must fill it in loops over particels in the main loop.

map<string, tuple<string, int, double, double>> histParams = {
// name            title                nBins min     max
  {"pair_m"     , {"Pair dN/dm"        , 100 ,  0.0  , 100.  }},
  {"pair_pt"    , {"Pair dN/dp_{T}"    , 100 ,  0.0  , 0.5   }},
  {"pair_pz"    , {"Pair dN/dp_{z}"    , 150 ,  0.0  , 1500. }},
  {"pair_y"     , {"Pair dN/dy"        , 100 , -10.0 , 10.0  }},
//  {"pair_theta" , {"Pair dN/d#theta"   , 100 ,  0.0  , 3.14  }},
  {"pair_aco"   , {"Pair dN/dA_{#phi}" , 500 ,  0.0  , 0.5   }},
  
  {"single_pt"  , {"Single dN/dp_{T}"  , 1000, 0.0   , 100.  }},
  {"single_pz"  , {"Single dN/dp_{z}"  , 1000, 0.0   , 1000. }},
  {"single_y"   , {"Single dN/dy"      , 100 , -10.0 , 10.0  }},
  {"single_eta" , {"Signle dN/d#eta"   , 100 , -10.0 , 10.0  }},
  {"single_phi" , {"Single dN/d#phi"   , 100 , -4    , 4     }},
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
  
  for(int i=0; i<particles1.size(); i++){
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
    
    double acoplanarity = 1 - TMath::Abs(TMath::Abs(particles2[i].Phi()-particles1[i].Phi()))/TMath::Pi(); // acoplanarity
    hists["pair_aco"]->Fill(acoplanarity);
  }
  
  for(auto p :particlesSum){
    hists["pair_m"]->Fill(p.M());
    hists["pair_pt"]->Fill(p.Pt());
    hists["pair_pz"]->Fill(p.Pz());
    hists["pair_y"]->Fill(p.Rapidity());
    hists["pair_theta"]->Fill(p.Theta());
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
  
  for(auto fileName : files){
    if(iFiles >= nFiles) break;
    iFiles++;
    
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

        TLorentzVector particleSum(0.,0.,0.,0.);
        particleSum = particle1 + particle2;
        particlesSum.push_back(particleSum);
      }
    }
    lheFile.close();
  }
}
