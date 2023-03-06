  #include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include <iostream>
#include "TFile.h"
#include "TTree.h"

// Compile with:
// g++ countEvents.C -o countEvents `root-config --libs` `root-config --cflags`
//

using namespace std;

//string inputPath = "/eos/cms/store/group/phys_diffraction/lbyl_2018/HIForward_Reco/ntuples/ntuples_data_tracker_branches/HIForward/ntuples_data_lbl_tracker_branches/200317_103751";
//string inputPath = "/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_doubleEG2_noPixelTracks";
//string inputPath = "/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_doubleEG2_complete";
//string inputPath = "/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_doubleEG2_noPixelTracks_full";
//string inputPath = "/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_doubleEG2_complete_full";
//string inputPath = "/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_doubleEG2_full_lumi";
//string inputPath = "/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_doubleEG2_full_lumi_complete";
//string inputPath = "/eos/cms/store/group/phys_diffraction/lbyl_2018/mc_qed/ntuples_sl_full_lumi/QEDGammaGamma_5p02TeV_STARlight/reco_mc_qed_sl_full_lumi/200625_125406/0000";
//string inputPath = "/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_doubleEG2_complete_full/merged/";

//string inputPath = "/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/mc_qed_sl_doubleEG2_full_lumi";
string inputPath = "/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/mc_qed_sl_doubleEG2_full_lumi_complete";



string treePath = "ggHiNtuplizer/EventTree";

int nFiles = 0;
int nEvents = 0;
int nErrors = 0;

void readRootFile(string path)
{
  if(nFiles%10 == 0) cout<<"Files analyzed so far: "<<nFiles<<"\ttotal events so far: "<<nEvents<<endl;
  
  TFile *file = TFile::Open(path.c_str());
  
  if(!file){
    cout<<"ERROR - could not read file: "<<path<<endl;
    nErrors++;
    return;
  }
  
  TTree *tree = (TTree*)file->Get(treePath.c_str());
  if(!tree){
    cout<<"ERROR - could not find tree in file:"<<path<<endl;
    nErrors++;
    file->Close();
    return;
  }
  
  nEvents+= tree->GetEntriesFast();
  nFiles++;
  file->Close();
}

bool isDirectory(string path)
{
  struct stat path_stat;
  stat(path.c_str(), &path_stat);
  return !S_ISREG(path_stat.st_mode);
}

void readDirectoryRecursively(string basePath)
{
  DIR* dirp = opendir(basePath.c_str());
  struct dirent * dp;
  
  while((dp = readdir(dirp))) {
    string fileName = dp->d_name;
    
    if(fileName==".")   continue;
    if(fileName=="..")  continue;
    
    if(fileName.find("merge") != string::npos) continue;
    
    string currentFullPath = basePath+"/"+fileName;
    
    if(fileName.find(".root") != string::npos){
      readRootFile(currentFullPath);
    }
    else if(isDirectory(currentFullPath)){
      readDirectoryRecursively(currentFullPath);
    }
  }
  closedir(dirp);
}

int main()
{
  cout<<"\n----------------------------------------------------------------------------------------"<<endl;
  cout<<"Counting events in all files in path: "<<inputPath<<endl;
  cout<<"All .root files in this directory and all sub-directories will be taken into account,"<<endl;
  cout<<"except for those containing word \"merge\", which will be skipped."<<endl;
  cout<<"----------------------------------------------------------------------------------------\n"<<endl;
  
  readDirectoryRecursively(inputPath);
  
  cout<<"Files analyzed: "<<nFiles<<endl;
  cout<<"Total number of events: "<<nEvents<<endl;
  cout<<"Total number of errors: "<<nErrors<<endl;
}

