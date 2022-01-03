string alpsFilePath = "input_files/histos_axions_2018.root";
//string backgroundFilePath = "input_files/histos_diphoton_2018.root";
string backgroundFilePath = "input_files/diphoton_histos_allSfsApplied.root";
string outputFilePath = "input_hinvmass_2018_withSFs.root";

string backgroundBaseName = "hinvmass_";

//double luminosity = 1609.910015010; // from brilcalc, 1/μb
double luminosity = 1639.207543; // from Ruchi, 1/μb
bool scaleBackgrounds = false;

double referenceAlpXsec = 10e-3; // (μb)

vector<tuple<int, int>> alpParams = {
// mass nGenEvents
  {5  , 754000  },
  {6  , 729000  },
  {9  , 722000  },
  {11 , 692000  },
  {14 , 712000  },
  {16 , 682000  },
  {22 , 694000  },
  {30 , 719000  },
  {50 , 511000  },
  {90 , 449000  },
};

vector<tuple<string, string, int, double>> backgroundParams = {
// input_name      output_name  nGenEvents  xSec (μb)
  {"data"         , "data_obs"  , -1      , -1      },
  {"lbyl_stack_3" , "lbyl"      , 466000  , 2.59    },
  {"cep_stack_2"  , "cep"       , 668000  , 0.0058  },
  {"qed_stack_1"  , "qed"       , 66770000, 7920    },
};

void prepareALPinput()
{
  TFile *backgroundFile = TFile::Open(backgroundFilePath.c_str());
  TFile *alpsFile = TFile::Open(alpsFilePath.c_str());
  TFile *outputFile = new TFile(outputFilePath.c_str(), "recreate");
  outputFile->cd();
  
  for(auto &[mass, nEvents] : alpParams){
    TH1D *hist = (TH1D*)alpsFile->Get(("axion"+to_string(mass)).c_str());
    hist->Scale(luminosity*referenceAlpXsec/nEvents);
    hist->Write();
  }
  
  for(auto &[inputName, outputName, nEvents, xSec] : backgroundParams){
    TH1D *hist = (TH1D*)backgroundFile->Get((backgroundBaseName+inputName).c_str());
    
    if(nEvents > 0 && scaleBackgrounds){
      hist->Scale(luminosity*xSec/nEvents);
    }
    
    hist->SetName(outputName.c_str());
    hist->Write();
  }
  
  outputFile->Close();
}
