#define EventTree_cxx
#include "EventTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void EventTree::Loop()
{
  //   In a ROOT session, you can do:
  //      root> .L processedLumis.C
  //      root> processedLumis t
  //      root> t.GetEntry(12); // Fill t data members with entry number 12
  //      root> t.Show();       // Show values of entry 12
  //      root> t.Show(16);     // Read and show values of entry 16
  //      root> t.Loop();       // Loop on all entries
  //
  
  //     This is the loop skeleton where:
  //    jentry is the global entry number in the chain
  //    ientry is the entry number in the current Tree
  //  Note that the argument to GetEntry must be:
  //    jentry for TChain::GetEntry
  //    ientry for TTree::GetEntry and TBranch::GetEntry
  //
  //       To read only selected branches, Insert statements like:
  // METHOD1:
  fChain->SetBranchStatus("*",0);  // disable all branches
  fChain->SetBranchStatus("run",1);  // activate branchname
  fChain->SetBranchStatus("lumis",1);  // activate branchname
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  // nentries = 10000;
  
  set<pair<int,int> > pl;
  
  Long64_t nbytes = 0, nb = 0;
  
  cout<<"First loop"<<endl;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    if(jentry%10000==0) cout<<jentry<<endl;
    
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    
    pair<int,int> p(run,lumis);
    if (pl.find(p) == pl.end()) pl.insert(p);
  }
  
  ofstream of("processedLumis.txt");
  of << "{";
  
  int previousrun = -1;
  int previousLS = -1;
  
  cout<<"second loop"<<endl;
  for (set<pair<int,int> >::const_iterator it = pl.begin(); it != pl.end(); it++) {
    int run = it->first;
    int LS = it->second;
    
    if (run != previousrun) {
      if (previousrun<0) of << "\"" << run << "\":";
      else of << previousLS << "]]," << endl << "\"" << run << "\": ";
      previousLS = -1;
    }
    
    if (LS > previousLS+1) {
      if (previousLS == -1) {
        of << "[[" << LS << ",";
      } else {
        of << previousLS << "], [" << LS << ",";
      }
    }
    
    
    previousrun = run;
    previousLS = LS;
  }
  
  of << previousLS << "]]}" << endl;
  
  of.close();
  
}
