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
  "HLT_HIUPC_SingleEG3_BptxAND_SinglePixelTrack_MaxPixelTrack_v1",
};

enum EDataset{
  kData,
  kData_SingleEG3,
  kData_recoEff,
  kData_triggerEff,
  kData_HFveto,
  kData_exclusivity,
  kData_LbLsignal,
  kData_QEDsignal,
  kMCqedSC,
  kMCqedSC_SingleEG3,
  kMCqedSC_recoEff,
  kMCqedSC_triggerEff,
  kMCqedSC_HFveto,
  kMCqedSC_exclusivity,
  kMCqedSC_LbLsignal,
  kMCqedSC_QEDsignal,
  kMCqedSL,
  kMClbl,
  kMCcep,
  nDatasets
};

const vector<EDataset> datasets = { kData, kData_SingleEG3, kData_recoEff, kData_triggerEff,
                                    kData_HFveto, kData_exclusivity, kData_LbLsignal, kData_QEDsignal,
                                    kMCqedSC, kMCqedSC_SingleEG3, kMCqedSC_recoEff, kMCqedSC_triggerEff,
                                    kMCqedSC_HFveto, kMCqedSC_exclusivity, kMCqedSC_LbLsignal, kMCqedSC_QEDsignal,
                                    kMCcep, kMCqedSL, kMClbl,  };

const map<EDataset, string> inFileNames = {
//  {kData                , "ntuples/ntuples_data_small_sample_merged.root"     },
  {kData                , "ntuples/ntuples_data_small_sample.root"                    },
  {kData_SingleEG3      , "ntuples/ntuples_data_withSingleEG3.root"                   },
  {kData_recoEff        , "ntuples/ntuples_data_forRecoEff.root"                      },
  {kData_triggerEff     , "ntuples/ntuples_data_forTriggerEff.root"                   },
  {kData_HFveto         , "ntuples/ntuples_data_forHFveto.root"                       },
  {kData_exclusivity    , "ntuples/ntuples_data_forExclusivity.root"                  },
//  {kData_LbLsignal      , "ntuples/ntuples_data_forSignalExtraction.root"             },
  {kData_LbLsignal      , "ntuples/ntuples_data_forLbLsignal_noHFcheck.root"          },
//  {kData_LbLsignal      , "ntuples/ntuples_data_forLbLsignal_CHE_500MeV.root"          },
  {kData_QEDsignal      , "ntuples/ntuples_data_forQEDsignal_noNEEapplied.root"       },
//  {kMCqedSC             , "ntuples/ntuples_mc_qed_sc.root"                            },
  {kMCqedSC             , "ntuples/ntuples_mc_qed_sc_small_sample.root"               },
  {kMCqedSC_SingleEG3   , "ntuples/ntuples_mc_qed_withSingleEG3.root"                 },
  {kMCqedSC_recoEff     , "ntuples/ntuples_mc_qed_sc_forRecoEff.root"                 },
  {kMCqedSC_triggerEff  , "ntuples/ntuples_mc_qed_sc_forTriggerEff.root"              },
  {kMCqedSC_HFveto      , "ntuples/ntuples_mc_qed_sc_forHFveto.root"                  },
  {kMCqedSC_exclusivity , "ntuples/ntuples_mc_qed_sc_forExclusivity.root"             },
  {kMCqedSC_LbLsignal   , "ntuples/ntuples_mc_qed_sc_forLbLsignal.root"               },
  {kMCqedSC_QEDsignal   , "ntuples/ntuples_mc_qed_sc_forQEDsignal_noNEEapplied.root"  },
  {kMCqedSL             , "ntuples/ntuples_mc_qed_sl.root"                            },
  {kMClbl               , "ntuples/ntuples_mc_lbl_sc_forLbLsignal.root"               },
//  {kMClbl               , "ntuples/ntuples_mc_lbl_sc_small_sample.root"               },
  {kMCcep               , "ntuples/ntuples_mc_cep_sc_forLbLsignal.root"               },
//  {kMCcep               , "ntuples/ntuples_mc_cep_sc_small_sample.root"               },
};

const map<EDataset, int> datasetColor = {
  {kData                , kBlack    },
  {kData_SingleEG3      , kBlack    },
  {kData_recoEff        , kBlack    },
  {kData_triggerEff     , kBlack    },
  {kData_HFveto         , kBlack    },
  {kData_exclusivity    , kBlack    },
  {kData_LbLsignal      , kBlack    },
  {kData_QEDsignal      , kBlack    },
  {kMCqedSC             , kRed      },
  {kMCqedSC_SingleEG3   , kRed      },
  {kMCqedSC_recoEff     , kRed      },
  {kMCqedSC_triggerEff  , kRed      },
  {kMCqedSC_HFveto      , kRed      },
  {kMCqedSC_exclusivity , kRed      },
  {kMCqedSC_LbLsignal   , kRed      },
  {kMCqedSC_QEDsignal   , kRed      },
  {kMCqedSL             , kOrange+2 },
  {kMClbl               , kViolet+2 },
  {kMCcep               , kGreen+2  },
};

const map<EDataset, string> datasetName = {
  {kData                , "Data"    },
  {kData_SingleEG3      , "Data"    },
  {kData_recoEff        , "Data"    },
  {kData_triggerEff     , "Data"    },
  {kData_HFveto         , "Data"    },
  {kData_exclusivity    , "Data"    },
  {kData_LbLsignal      , "Data"    },
  {kData_QEDsignal      , "Data"    },
  {kMCqedSC             , "QED_SC"  },
  {kMCqedSC_SingleEG3   , "QED_SC"  },
  {kMCqedSC_recoEff     , "QED_SC"  },
  {kMCqedSC_triggerEff  , "QED_SC"  },
  {kMCqedSC_HFveto      , "QED_SC"  },
  {kMCqedSC_exclusivity , "QED_SC"  },
  {kMCqedSC_LbLsignal   , "QED_SC"  },
  {kMCqedSC_QEDsignal   , "QED_SC"  },
  {kMCqedSL             , "QED_SL"  },
  {kMClbl               , "LbL"     },
  {kMCcep               , "CEP"     },
};

const map<EDataset, string> datasetDescription = {
  {kData                , "Data"          },
  {kData_SingleEG3      , "Data"          },
  {kData_recoEff        , "Data"          },
  {kData_triggerEff     , "Data"          },
  {kData_HFveto         , "Data"          },
  {kData_exclusivity    , "Data"          },
  {kData_LbLsignal      , "Data"          },
  {kData_QEDsignal      , "Data"          },
  {kMCqedSC             , "QED MC (SC)"   },
  {kMCqedSC_SingleEG3   , "QED MC (SC)"   },
  {kMCqedSC_recoEff     , "QED MC (SC)"   },
  {kMCqedSC_triggerEff  , "QED MC (SC)"   },
  {kMCqedSC_HFveto      , "QED MC (SC)"   },
  {kMCqedSC_exclusivity , "QED MC (SC)"   },
  {kMCqedSC_LbLsignal   , "QED MC (SC)"   },
  {kMCqedSC_QEDsignal   , "QED MC (SC)"   },
  {kMCqedSL             , "QED MC (SL)"   },
  {kMClbl               , "LbL MC"        },
  {kMCcep               , "CEP MC"        },
};

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

template <typename T>
string to_string_with_precision(const T a_value, const int n = 6)
{
  ostringstream out;
  out.precision(n);
  out << fixed << a_value;
  return out.str();
}

#endif /* Helpers_h */
