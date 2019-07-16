//================================================================================================
//
// This macro creates raw, ugly histograms from LHE files.
//


// Set input path and output filename here:

// QED SuperChic
//string basePath = "./mc_qed/lhe_superchic_with_cuts/";
//string outFileName = "raw_plots_qed_sc.root";

// QED Starlight
//string basePath = "./mc_qed/lhe_starlight_with_cuts/";
//string outFileName = "raw_plots_qed_sl.root";

// LbL SuperChic
//string basePath = "./mc_lbyl/lhe_superchic/";
//string outFileName = "raw_plots_lbl_sc.root";

// CEP SuperChic
string basePath = "./mc_cep/lhe_superchic/";
string outFileName = "raw_plots_cep_sc.root";


// Say how many files to process:
int nFiles = 1;


// Here modify titles, axis labels, number of bins and histogram ranges.
// If you add a new histogram, you must fill it in loops over particels in the main loop.

map<string, tuple<string, string, string, int, double, double>> histParams = {
// name            title                 X axis            Y axis     nBins min     max
  {"pair_m"     , {"Pair dN/dm"         , "m (GeV/c)"     , "Entries", 100 ,  0.0  , 100.  }},
  {"pair_pt"    , {"Pair dN/dp_{T}"     , "p_{T} (GeV/c)" , "Entries", 100 ,  0.0  , 0.5   }},
  {"pair_pz"    , {"Pair dN/dp_{L}"     , "p_{z} (GeV/c)" , "Entries", 100 ,  0.0  , 1000. }},
  {"pair_y"     , {"Pair dN/dy"         , "y"             , "Entries", 100 , -6.0  , 6.0   }},
  {"pair_theta" , {"Pair dN/d#theta"    , "#theta"        , "Entries", 100 ,  0.0  , 3.14  }},
  {"pair_aco"   , {"Pair dN/dA_{#phi}"  , "A_{#phi}"      , "Entries", 100 ,  0.0  , 0.1   }},
  
  {"single_pt"  , {"Single dN/dp_{T}"   , "p_{T} (GeV/c)" , "Entries", 1000, 0.0   , 100.  }},
  {"single_pz"  , {"Single dN/dp_{L}"   , "p_{z} (GeV/c)" , "Entries", 1000, 0.0   , 1000. }},
  {"single_y"   , {"Single dN/dy"       , "y"             , "Entries", 100 , -6.0  , 6.    }},
  {"single_eta" , {"Signle dN/d#eta"    , "#eta"          , "Entries", 100 , -10.0 , 10.   }},
  {"single_phi" , {"Single dN/d#phi"    , "#phi"          , "Entries", 100 , -4    , 4     }},
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
    auto &[title, xTitle, yTitle, nBins, min, max] = paramsTuple;
    
    hists[name] = new TH1D(name.c_str(), title.c_str(), nBins, min, max);
    hists[name]->GetXaxis()->SetTitle(xTitle.c_str());
    hists[name]->GetYaxis()->SetTitle(yTitle.c_str());
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
        
        TLorentzVector particle1(0.,0.,0.,0.);
        particle1.SetPxPyPzE(p1[0],p1[1],p1[2],p1[3]);
        particles1.push_back(particle1);
        
        TLorentzVector particle2(0.,0.,0.,0.);
        particle2.SetPxPyPzE(p2[0],p2[1],p2[2],p2[3]);
        particles2.push_back(particle2);
        
        TLorentzVector particleSum(0.,0.,0.,0.);
        particleSum = particle1 + particle2;
        particlesSum.push_back(particleSum);
      }
    }
    lheFile.close();
  }
}
