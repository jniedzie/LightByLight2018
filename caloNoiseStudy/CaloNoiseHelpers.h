#include <TMath.h>
#include <TFile.h>
#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>

#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

double PI = TMath::Pi();

enum EDet { kEB, kEE, kHB, kHE, kHFm, kHFp, nDets };
vector<string> detNames = { "EB", "EE", "HB", "HE", "HFm", "HFp", "unknown" };

vector<pair<double,double>> detLimits = {
  {0    , 1.479 }, // EB
  {1.479, 3.0   }, // EE
  {0    , 1.3   }, // HB
  {1.3  , 3.0   }, // HE
  {-5.2 ,-3.0   }, // HFm
  {3.0  , 5.2   }, // HFp
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
