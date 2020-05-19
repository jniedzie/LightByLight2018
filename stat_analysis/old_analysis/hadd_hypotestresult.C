#include "RooStats/HypoTestResult.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TKey.h"

RooStats::HypoTestResult* hadd_hypotestresult(const char* filename) {
   TFile *f = TFile::Open(filename);

   TDirectory *toyDir = f->GetDirectory("toys");
   if (!toyDir) throw std::logic_error("Cannot use readHypoTestResult: empty toy dir in input file empty");

   RooStats::HypoTestResult* ret=NULL;
   TIter next(toyDir->GetListOfKeys()); TKey *k;
   while ((k = (TKey *) next()) != 0) {
      if (! (TString(k->GetName()).Contains("HypoTestResult"))) continue;
      cout << k->GetName() << endl;
      RooStats::HypoTestResult *toy = dynamic_cast<RooStats::HypoTestResult *>(toyDir->Get(k->GetName()));
      if (toy == 0) continue;
      if (ret == NULL) {
         ret = new RooStats::HypoTestResult(*toy);
      } else {
         ret->Append(toy);
      }
   }

   return ret;
}
