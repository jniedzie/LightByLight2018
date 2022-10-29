//  Helpers.hpp
//
//  Created by Jeremi Niedziela on 22/07/2019.

#ifndef Helpers_h
#define Helpers_h

#pragma clang diagnostic push // save the current state
#pragma clang diagnostic ignored "-Wdocumentation" // turn off ROOT's warnings
#pragma clang diagnostic ignored "-Wconversion"

#include "TH1D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TF1.h"
#include "TTree.h"
#include "TFile.h"
#include "TEnv.h"
#include "TLorentzVector.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TLine.h"
#include "TLatex.h"
//#include "RooFit.h"
//#include "RooRealVar.h"
//#include "RooDataSet.h"
//#include "RooArgSet.h"
#include "TGraphPolar.h"

#pragma clang diagnostic pop // restores the saved state for diagnostics

#include <ostream>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <memory>

using namespace std;

// List of allowed LbL triggers

enum ETrigger{
  kDoubleEG2noHF,
  kSingleEG3noHF,
  kSingleEG5noHF,
  kSingleEG3singleTrack,
  kSingleEG5singleTrack,
  kSingleMuOpenNoHF,
  nTriggers
};

const vector<ETrigger> triggers = {
  kDoubleEG2noHF, kSingleEG3noHF, kSingleEG5noHF,
  kSingleEG3singleTrack, kSingleEG5singleTrack, kSingleMuOpenNoHF,
};

const map<ETrigger, string> triggerNames = {
  { kDoubleEG2noHF       , "HLT_HIUPC_DoubleEG2_NotMBHF2AND_v1"                            },
  { kSingleEG3noHF       , "HLT_HIUPC_SingleEG3_NotMBHF2AND_v1"                            },
  { kSingleEG5noHF       , "HLT_HIUPC_SingleEG5_NotMBHF2AND_v1"                            },
  { kSingleEG3singleTrack, "HLT_HIUPC_SingleEG3_BptxAND_SinglePixelTrack_MaxPixelTrack_v1" },
  { kSingleEG5singleTrack, "HLT_HIUPC_SingleEG5_BptxAND_SinglePixelTrack_MaxPixelTrack_v1" },
  { kSingleMuOpenNoHF    , "HLT_HIUPC_SingleMuOpen_NotMBHF2AND_v1"                         },
};
  
enum EDataset{
  kData,
  kMCqedSC,
  kMCqedSL,
  kMClbl,
  kMCcep,
  kMCqedFSR,
  nDatasets
};

const vector<EDataset> datasets = { kData, kMCqedSC, kMCcep, kMCqedSL, kMClbl, kMCqedFSR };

enum class EPhysObjType {
  kGenParticle,
  kGoodGenPhoton,
  kPhoton,
  kPhotonInAcceptance,
  kGoodPhoton,
  kCaloTower,
  kCastor,
  kGeneralTrack,
  kGoodGeneralTrack,
  kElectron,
  kGoodGenElectron,
  kElectronInAcceptance,
  kGoodElectron,
  kGoodMatchedElectron,
  kMuon,
  kGoodMuon,
  kL1EG,
  kPixelTrack,
  kGoodPixelTrack,
  kZDC,
};

const vector<EPhysObjType> physObjTypes = {
  EPhysObjType::kGenParticle,
  EPhysObjType::kGoodGenPhoton,
  EPhysObjType::kPhoton,
  EPhysObjType::kPhotonInAcceptance,
  EPhysObjType::kGoodPhoton,
  EPhysObjType::kCaloTower,
  EPhysObjType::kCastor,
  EPhysObjType::kGeneralTrack,
  EPhysObjType::kGoodGeneralTrack,
  EPhysObjType::kElectron,
  EPhysObjType::kGoodGenElectron,
  EPhysObjType::kElectronInAcceptance,
  EPhysObjType::kGoodElectron,
  EPhysObjType::kGoodMatchedElectron,
  EPhysObjType::kMuon,
  EPhysObjType::kGoodMuon,
  EPhysObjType::kL1EG,
  EPhysObjType::kPixelTrack,
  EPhysObjType::kGoodPixelTrack,
  EPhysObjType::kZDC,
};

const map<EDataset, int> datasetColor = {
  {kData                , kBlack    },
  {kMCqedSC             , kRed      },
  {kMCqedSL             , kOrange+2 },
  {kMClbl               , kViolet+2 },
  {kMCcep               , kGreen+2  },
  {kMCqedFSR            , kMagenta  },
};

const map<EDataset, string> datasetName = {
  {kData                , "Data"    },
  {kMCqedSC             , "QED_SC"  },
  {kMCqedSL             , "QED_SL"  },
  {kMClbl               , "LbL"     },
  {kMCcep               , "CEP"     },
  {kMCqedFSR            , "QED_FSR" },
};

const map<EDataset, string> datasetDescription = {
  {kData                , "Data"          },
  {kMCqedSC             , "QED MC (SC)"   },
  {kMCqedSL             , "QED MC (SL)"   },
  {kMClbl               , "LbL MC"        },
  {kMCcep               , "CEP MC"        },
  {kMCqedFSR            , "QED MC (FSR)"  },
};

const map<string, EDataset> datasetForName = {
  {"Data"   , kData     },
  {"QED_SC" , kMCqedSC  },
  {"QED_SL" , kMCqedSL  },
  {"LbL"    , kMClbl    },
  {"CEP"    , kMCcep    },
  {"QED_FSR", kMCqedFSR },
};

inline tuple<double, double, double> GetBeamSpot(EDataset dataset)
{
  bool isMC = datasetName.at(dataset) != "Data";
  if(isMC) return make_tuple(0.10482, 0.16867, -1.0985);
  return make_tuple(0.010, 0.047, 0.903);
}

enum ECaloType { kEB, kEE, kHB, kHE, kHFp, kHFm, nCaloTypes };
constexpr initializer_list<ECaloType> calotypes = {kEB, kEE, kHB, kHE, kHFp, kHFm};

const map<ECaloType, string> caloName = {
  { kEB  , "EB"  },
  { kEE  , "EE"  },
  { kHB  , "HB"  },
  { kHE  , "HE"  },
  { kHFp , "HFp" },
  { kHFm , "HFm" },
};

const double maxEtaEB = 1.479;
const double minEtaEE = maxEtaEB;
const double maxEtaEE = 3.0;

const double maxEtaHB = 1.305;
const double minEtaHE = maxEtaHB;
const double maxEtaHE = 3.0;

const double minEtaHF = 2.9;
const double maxEtaHF = 5.2;

inline void PrintEfficiency(double num, double den)
{
  cout<<(double)num/den<<"\t#pm "<<sqrt(1./num+1./den)*(double)num/den<<endl;
}

template <typename T>
string to_string_with_precision(const T a_value, const int n = 6)
{
  ostringstream out;
  out.precision(n);
  out << fixed << a_value;
  return out.str();
}

inline long long GetEntryNumber(TTree *tree, uint runNumber, uint lumiSection, ULong64_t eventNumber)
{
  // uberhack to select needed entry directly...
  tree->Draw("Entry$>>hist(Entries$,0,Entries$)",
             ("lumis=="+to_string(lumiSection)+
              "&&run=="+to_string(runNumber)+
              "&&event=="+to_string(eventNumber)).c_str(),
             "goff");
  
  TH1I *hist = (TH1I*)gDirectory->Get("hist");
  Long64_t iEntry = hist->GetBinLowEdge(hist->FindFirstBinAbove(0));
  if(hist) delete hist;
  
  if(iEntry==0){
    cout<<"No event with run: "<<runNumber<<"\tlumi: "<<lumiSection<<"\tevNumber: "<<eventNumber<<" was found\n";
    return -1;
  }
  return iEntry;
}



#endif /* Helpers_h */
