#include <TMath.h>
#include <TFile.h>
#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include <TH1D.h>
#include <TCanvas.h>

#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

double PI = TMath::Pi();

vector<tuple<string,int,double,double>> inputVarParams = { // varName, nBins, min, max
  {"CaloTower_hadE",  100,  0, 10},
  {"CaloTower_emE",   100,  0, 10},
  {"CaloTower_e",     100,  0, 10},
  {"CaloTower_et",    100,  0, 10},
  {"CaloTower_eta",   100, -6, 6 },
  {"CaloTower_phi",   100,-PI, PI},
};

enum EDet { kEB, kEE, kHB, kHE, kHF, nDets };
vector<string> detNames = { "EB", "EE", "HB", "HE", "HF", "unknown" };

vector<pair<double,double>> detLimits = {
  {0    , 1.479 }, // EB
  {1.479, 3.0   }, // EE
  {0    , 1.3   }, // HB
  {1.3  , 3.0   }, // HE
  {3.0  , 5.2   }, // HF
};

struct CaloTower {
  CaloTower(double _eta, double _phi, double _energy, double _energyEm, double _energyHad, double _energyTransverse) :
  eta(_eta), phi(_phi), energy(_energy), energyEm(_energyEm), energyHad(_energyHad), energyTransverse(_energyTransverse){}
  
  CaloTower() : eta(0), phi(0), energy(-1), energyEm(-1), energyHad(-1), energyTransverse(-1){}
  
  double eta;
  double phi;
  double energy;
  double energyEm;
  double energyHad;
  double energyTransverse;
  
  void Print(){
    cout<<"Tower eta: "<<eta<<"\tphi: "<<phi<<"\tE: "<<energy<<"\tE_em: "<<energyEm<<"\tE_had: "<<energyHad<<endl;
  }
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
  TTreeReader treeReader("ggHiNtuplizer/EventTree", inFile);
  
  // For each input variable setup reader and create a histogram
  map<string, TTreeReaderArray<float>> inputVariables;
  map<string, TH1D*> inputHists;
  
  for(auto &[varName, nBins, min, max] : inputVarParams){
    inputVariables.emplace(make_pair(varName, TTreeReaderArray<float>(treeReader,  varName.c_str())));
    inputHists[varName] = new TH1D(varName.c_str(), varName.c_str(), nBins, min, max);
  }
  
  // Loop over events
  cout<<"Reading events from input file and filling histograms"<<endl;
  vector<CaloTower> leadingCaloTowers[nDets];
  int iter=0;
  
  while(treeReader.Next()){
    if(iter%1000==0) cout<<"Processing event "<<iter<<"/"<<treeReader.GetEntries(false)<<endl;
    iter++;
    
    // Loop over calo towers in an event
    vector<CaloTower> caloTowersInEvent;
    int nTowers = inputVariables.begin()->second.GetSize();
    
    for(int iTower=0; iTower<nTowers; iTower++){
      
      // Loop over histograms and fill them
      for(auto &[varName, a, b, c] : inputVarParams){
        inputHists[varName]->Fill(inputVariables.at(varName)[iTower]);
      }
      
      // Add towers in this event to the vector of calo towers
      CaloTower tower(inputVariables.at("CaloTower_eta")[iTower],
                      inputVariables.at("CaloTower_phi")[iTower],
                      inputVariables.at("CaloTower_e")[iTower],
                      inputVariables.at("CaloTower_emE")[iTower],
                      inputVariables.at("CaloTower_hadE")[iTower],
                      inputVariables.at("CaloTower_et")[iTower]);
      
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
      
      if(tower.energy > maxEnergy[kHF] &&
         eta > detLimits[kHB].first && eta < detLimits[kHB].second){
        maxEnergy[kHF] = tower.energy;
        leadingTower[kHF] = tower;
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
  for(int iDet=0;iDet<nDets;iDet++){
    const char* histName = ("energyHist"+detNames[iDet]).c_str();
    energyHist.push_back(new TH1D(histName, histName, 100, 0, 10));
    
    for(auto tower : leadingCaloTowers[iDet]){
      if(iDet == kEE || iDet == kEB)        energyHist[iDet]->Fill(tower.energyEm);
      else if(iDet == kHE || iDet == kHB)   energyHist[iDet]->Fill(tower.energyHad);
      else                                  energyHist[iDet]->Fill(tower.energy);
    }
  }
  
  // Find noise thresholds
  for(int iDet=0;iDet<nDets;iDet++){
    // Normalize histograms by number of entries
    energyHist[iDet]->Scale(1/energyHist[iDet]->GetEntries());
    
    double histIntegral = energyHist[iDet]->Integral(energyHist[iDet]->GetXaxis()->FindFixBin(0.0),
                                                     energyHist[iDet]->GetXaxis()->FindFixBin(10.0));
    
    double threshold;
    
    for(threshold=0; threshold<10.0; threshold+=0.01){
      double currentIntegral = energyHist[iDet]->Integral(energyHist[iDet]->GetXaxis()->FindFixBin(0.0),
                                                          energyHist[iDet]->GetXaxis()->FindFixBin(threshold));
      
      if(currentIntegral >= 0.99*histIntegral) break;
    }
    
    cout<<"Threshold for "<<detNames[iDet]<<": "<<threshold<<" GeV"<<endl;
  }
  
  
  
  // Draw histograms and save the output
  auto inputCanvas  = new TCanvas("inputCanvas", "inputCanvas",   800, 1200);
  auto outputCanvas = new TCanvas("outputCanvas", "outputCanvas", 800, 1200);
  
  inputCanvas->Divide(2,3);
  outputCanvas->Divide(2,3);
  
  TFile *outFile = new TFile(outputPath, "recreate");
  
  int iPad=1;
  for(auto &[varName, a, b, c] : inputVarParams){
    inputCanvas->cd(iPad++);
    inputHists[varName]->Draw();
    inputHists[varName]->Write();
  }
  
  for(int iDet=0;iDet<nDets;iDet++){
    outputCanvas->cd(iDet+1);
    gPad->SetLogy();
    energyHist[iDet]->Draw();
    energyHist[iDet]->Write();
  }

  inputCanvas->Write();
  outputCanvas->Write();

  outFile->Close();
  
  return 0;
}
