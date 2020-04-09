void checkNevents()
{
  string baseBathOld = "/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_doubleEG2_tracker_branches/merged/";
  string baseBathNew = "/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_doubleEG2_trackerAndPixelBranches/";
  
  
  for(int iFile=0; iFile<60; iFile++){
    cout<<"\niFile: "<<iFile<<endl;
    
    string fileNameNew = "ntuples_"+to_string(iFile)+".root";
    string fileNameOld = "merged_ntuples_"+to_string(iFile)+".root";
    
    int entriesNew = -1;
    int entriesOld = -1;
    
    TFile *fileNew = TFile::Open((baseBathNew+fileNameNew).c_str());
    if(!fileNew) cout<<"New file not found"<<endl;
    else{
      TTree *treeNew = (TTree*)fileNew->Get("ggHiNtuplizer/EventTree");
      if(!treeNew)  cout<<"New tree not found"<<endl;
      else          entriesNew = treeNew->GetEntries();
    }
    
    TFile *fileOld = TFile::Open((baseBathOld+fileNameOld).c_str());
    if(!fileOld) cout<<"Old file not found"<<endl;
    else{
      TTree *treeOld = (TTree*)fileOld->Get("ggHiNtuplizer/EventTree");
      if(!treeOld)  cout<<"Old tree not found"<<endl;
      else          entriesOld = treeOld->GetEntries();
    }
    
    cout<<"Entries old: "<<entriesOld<<"\tnew: "<<entriesNew<<endl;
  }
  
}
