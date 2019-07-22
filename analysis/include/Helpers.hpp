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
  "HLT_HIUPC_DoubleEG5_NotMBHF2AND_v1",
  "HLT_HIUPC_SingleEG3_NotMBHF2AND_v1"
};

#endif /* Helpers_h */
