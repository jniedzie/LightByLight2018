#include "DumpEvent.hpp"
#include "Logger.hpp"

#include "TChain.h"

int main(int argc, const char** argv) {
   if (argc != 2) {
      Log(0)<<"This app requires 1 parameter.\n";
      Log(0)<<"./runEventList inputFile\n";
      exit(0);
   }
   TChain *tch = new TChain("ggHiNtuplizer/EventTree");
   tch->Add(argv[1]);

   DumpEvent toto(tch);
   toto.Loop_evtlist();
}
