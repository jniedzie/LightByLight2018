#include "DumpEvent.hpp"

#include "TChain.h"

int main(int argc, const char** argv) {
   TChain *tch = new TChain("ggHiNtuplizer/EventTree");
   tch->Add("/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_doubleEG2_tracker_branches/merged/merged_ntuples_*.root");
   // tch->Add("/eos/cms/store/group/phys_diffraction/lbyl_2018/skimmed_ntuples/data_doubleEG2_tracker_branches/merged/merged_ntuples_4.root");

   DumpEvent toto(tch);
   toto.Loop("histos_lowaco.root",true);
   toto.Loop("histos_highaco.root",false);
}
