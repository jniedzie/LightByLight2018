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

#pragma clang diagnostic pop // restores the saved state for diagnostics

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <memory>

using namespace std;

// List of allowed LbL triggers
const vector<string> triggerNamesLbL = {
  "HLT_HIUPC_DoubleEG2_NotMBHF2AND_v1",
  "HLT_HIUPC_SingleEG3_NotMBHF2AND_v1",
  "HLT_HIUPC_SingleEG5_NotMBHF2AND_v1",
};

enum EDataset{
  kData,
  kMCqedSC,
  kMCqedSL,
  kMClbl,
  kMCcep,
  nDatasets
};

const vector<EDataset> datasets = { kData, kMCcep, kMCqedSC, kMCqedSL, kMClbl,  };

const map<EDataset, string> inFileNames = {
  {kData    , "ntuples/ntuples_data_small_sample_merged.root" },
  {kMCqedSC , "ntuples/ntuples_mc_qed_sc_merged.root"         },
  {kMCqedSL , "ntuples/ntuples_mc_qed_sl_merged.root"         },
  {kMClbl   , "ntuples/ntuples_mc_lbl_merged.root"            },
  {kMCcep   , "ntuples/ntuples_mc_cep_merged.root"            },
};

const map<EDataset, int> datasetColor = {
  {kData    , kBlack    },
  {kMCqedSC , kRed      },
  {kMCqedSL , kOrange+2 },
  {kMClbl   , kViolet+2 },
  {kMCcep   , kGreen+2  },
};

const map<EDataset, string> datasetName = {
  {kData    , "Data"    },
  {kMCqedSC , "QED_SC"  },
  {kMCqedSL , "QED_SL"  },
  {kMClbl   , "LbL"     },
  {kMCcep   , "CEP"     },
};

const map<EDataset, string> datasetDescription = {
  {kData    , "Data"          },
  {kMCqedSC , "QED MC (SC)"   },
  {kMCqedSL , "QED MC (SL)"   },
  {kMClbl   , "LbL MC"        },
  {kMCcep   , "CEP MC"        },
};

enum ECaloType { kEB, kEE, kHB, kHE, kHFp, kHFm, nCaloTypes };

const map<ECaloType, double> caloNoiseThreshold = { // in GeV
  {kEB, 0.8},
  {kEE, 3.7},
  {kHB, 2.9},
  {kHE, 2.5},
  {kHFp, 7.3},
  {kHFm, 7.6}
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

#endif /* Helpers_h */
