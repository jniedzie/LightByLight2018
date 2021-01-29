#include "CaloNoiseHelpers.h"

vector<tuple<string,int,double,double>> inputVarParams = {
  // varName,       nBins,min, max
  {"CaloTower_hadE",  100,  0, 10},
  {"CaloTower_emE",   100,  0, 10},
  {"CaloTower_e",     100,  0, 10},
  {"CaloTower_et",    100,  0, 10},
  {"CaloTower_eta",   100, -6, 6 },
  {"CaloTower_phi",   100,-PI, PI},
};

vector<string> allowedTriggers = {
  "HLT_HIL1NotBptxOR_v1",
  "HLT_HIL1UnpairedBunchBptxMinus_v1",
  "HLT_HIL1UnpairedBunchBptxPlus_v1",
};

int main(int argc, char** argv)
{
  if(argc!=3){
    cout<<"Usage: ./getCaloNoiseThresholds inputPath outputPath"<<endl;
    exit(0);
  }
  const char* inputPath   = argv[1];
  const char* outputPath  = argv[2];
  
  // Read input file
  TFile *inFile = TFile::Open(inputPath);
  if(!inFile){
    cout<<"ERROR -- input file not found"<<endl;
    exit(0);
  }
  
  TTree *eventTree = (TTree*)inFile->Get("ggHiNtuplizer/EventTree");
  if(!eventTree){
    cout<<"ERROR -- event tree not found"<<endl;
    exit(0);
  }

  TTree *hltTree = (TTree*)inFile->Get("hltanalysis/HltTree");
  if(!hltTree){
    cout<<"ERROR -- hlt tree not found"<<endl;
    exit(0);
  }
  
  map<string, int> triggers;
  
  for(string triggerName : allowedTriggers){
    if(!hltTree->GetBranchStatus(triggerName.c_str())){
      cout<<"WARNING -- no branch named "<<triggerName<<"!!"<<endl;
      triggers[triggerName] = 0;
      continue;
    }
    hltTree->SetBranchAddress(triggerName.c_str(), &triggers[triggerName]);
  }
  
  // For each input variable setup reader and create a histogram
  map<string, vector<float>*> inputVariables;
  map<string, TH1D*> inputHists;
  
  for(auto &[varName, nBins, min, max] : inputVarParams){
    eventTree->SetBranchAddress(varName.c_str(), &inputVariables[varName]);
    inputHists[varName] = new TH1D(varName.c_str(), varName.c_str(), nBins, min, max);
  }
  
  // Loop over events
  cout<<"Reading events from input file and filling histograms"<<endl;
  vector<CaloTower> leadingCaloTowers[nDets];
  
  int nEvents = eventTree->GetEntries();

  for(int iEvent=0; iEvent<nEvents; iEvent++){
    if(iEvent%1000==0) cout<<"Processing event "<<iEvent<<" / "<<nEvents<<endl;
    
    eventTree->GetEntry(iEvent);
    hltTree->GetEntry(iEvent);
    
    bool hasTrigger = false;
    
    for(auto triggerName : allowedTriggers){
      if(triggers[triggerName]) hasTrigger = true;
    }
    if(!hasTrigger) continue;
    
    // Loop over calo towers in an event
    vector<CaloTower> caloTowersInEvent;
    int nTowers = inputVariables.begin()->second->size();
    
    for(int iTower=0; iTower<nTowers; iTower++){
      
      // Loop over histograms and fill them
      for(auto &[varName, a, b, c] : inputVarParams){
        inputHists[varName]->Fill(inputVariables[varName]->at(iTower));
      }
      
      // Add towers in this event to the vector of calo towers
      CaloTower tower(inputVariables["CaloTower_eta"]->at(iTower),
                      inputVariables["CaloTower_phi"]->at(iTower),
                      inputVariables["CaloTower_e"]->at(iTower),
                      inputVariables["CaloTower_emE"]->at(iTower),
                      inputVariables["CaloTower_hadE"]->at(iTower),
                      inputVariables["CaloTower_et"]->at(iTower));
      
      caloTowersInEvent.push_back(tower);
    }
    
    // find the leading tower in each sub-detector
    double maxEnergy[nDets] = {0};
    CaloTower leadingTower[nDets];
    
    for(auto tower : caloTowersInEvent){
      double eta = fabs(tower.eta);
      
      if(tower.energyEm > maxEnergy[kEB] &&
         eta > detLimits[kEB].first && eta < detLimits[kEB].second){
        maxEnergy[kEB] = tower.energyEm;
        leadingTower[kEB] = tower;
      }
      
      if(tower.energyEm > maxEnergy[kEE] &&
         eta > detLimits[kEE].first && eta < detLimits[kEE].second){
        maxEnergy[kEE] = tower.energyEm;
        leadingTower[kEE] = tower;
      }
      
      if(tower.energyHad > maxEnergy[kHB] &&
         eta > detLimits[kHB].first && eta < detLimits[kHB].second){
        maxEnergy[kHB] = tower.energyHad;
        leadingTower[kHB] = tower;
      }
      
      if(tower.energyHad > maxEnergy[kHE] &&
         eta > detLimits[kHE].first && eta < detLimits[kHE].second){
        maxEnergy[kHE] = tower.energyHad;
        leadingTower[kHE] = tower;
      }
      
      if(tower.energy > maxEnergy[kHFm] &&
        tower.eta > detLimits[kHFm].first && tower.eta < detLimits[kHFm].second){
        maxEnergy[kHFm] = tower.energy;
        leadingTower[kHFm] = tower;
      }
      
      if(tower.energy > maxEnergy[kHFp] &&
         tower.eta > detLimits[kHFp].first && tower.eta < detLimits[kHFp].second){
        maxEnergy[kHFp] = tower.energy;
        leadingTower[kHFp] = tower;
      }
      
    }
    
    for(int iDet=0;iDet<nDets;iDet++){
      if(leadingTower[iDet].energy >= 0){
        leadingCaloTowers[iDet].push_back(leadingTower[iDet]);
      }
      else{
        cout<<"no valid leading tower for "<<detNames[iDet]<<" found..."<<endl;
      }
    }
  }
  
  // Fill output histograms with leading tower energy
  vector<TH1D*> energyHist;
  vector<TH2D*> energyVsEtaHist;
  
  for(int iDet=0;iDet<nDets;iDet++){
    const char* histName = ("energyHist"+detNames[iDet]).c_str();
    energyHist.push_back(new TH1D(histName, histName, 200, 0, 20));
    energyVsEtaHist.push_back(new TH2D(Form("%sVsEta",histName), Form("%sVsEta",histName), 100, -5, 5, 200, 0, 20));
    
    for(auto tower : leadingCaloTowers[iDet]){
      if(iDet == kEE || iDet == kEB){
        energyHist[iDet]->Fill(tower.energyEm);
        energyVsEtaHist[iDet]->Fill(tower.eta, tower.energyEm);
      }
      else if(iDet == kHE || iDet == kHB){
        energyHist[iDet]->Fill(tower.energyHad);
        energyVsEtaHist[iDet]->Fill(tower.eta, tower.energyHad);
      }
      else{
        energyHist[iDet]->Fill(tower.energy);
        energyVsEtaHist[iDet]->Fill(tower.eta, tower.energy);
      }
    }
  }
  
  
  TFile *outFile = new TFile(outputPath, "recreate");
  
  for(auto &[varName, a, b, c] : inputVarParams){
    inputHists[varName]->Write();
  }
  
  for(int iDet=0;iDet<nDets;iDet++){
    energyHist[iDet]->Write();
    energyVsEtaHist[iDet]->Write();
  }
  
  outFile->Close();
  
  return 0;
}
