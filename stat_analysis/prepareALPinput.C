string alpsFilePath = "../event_generation/results/raw_plots_alp_4p5.root";
string backgroundFilePath = "../analysis/results/basicPlots_default.root";
string outputFilePath = "input_hinvmass_4p5.root";

string backgroundBaseName = "lbl_diphoton_mass_all_";

double luminosity = 1609.910015010; // from brilcalc, 1/μb

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
// input_name   output_name nGenEvents  xSec (μb)
  {"Data"     , "data_obs"  , -1      , -1      },
  {"LbL"      , "lbyl"      , 371000  , 2.59    },
  {"CEP"      , "cep"       , 738000  , 0.0058  },
  {"QED_SC"   , "qed"       , 950000  , 8830    },
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
    
    if(nEvents > 0){
      hist->Scale(luminosity*xSec/nEvents);
    }
    
    hist->SetName(outputName.c_str());
    hist->Write();
  }
  
  outputFile->Close();
}
