string inputPath  = "input_files/diphoton_histos_allSfsApplied.root";
string outputPath = "input_hacoplanarity_2018_withSFs.root";

string histName = "hacoplanarity_";

//double luminosity = 1609.910015010; // from brilcalc, 1/μb
double luminosity = 1639.207543; // from Ruchi, 1/μb

bool scaleBackgrounds = false;

vector<tuple<string, string, int, double>> backgroundParams = {
// input_name   output_name nGenEvents  xSec (μb)
  {"data"         , "data_obs"  , -1      , -1      },
  {"lbyl_stack_3" , "lbyl"      , 466000  , 2.59    },
  {"cep_stack_2"  , "cep"       , 668000  , 0.0058  },
  {"qed_stack_1"  , "qed"       , 66770000, 7920    },
};

void prepareSignificanceInput()
{
  TFile *backgroundFile = TFile::Open(inputPath.c_str());
  
  TFile *outputFile = new TFile(outputPath.c_str(), "recreate");
  outputFile->cd();
  
  
  for(auto &[inputName, outputName, nEvents, xSec] : backgroundParams){
    TH1D *hist = (TH1D*)backgroundFile->Get((histName+inputName).c_str());
    
    if(!hist){
      cout<<"ERROR - hist not found: "<<histName<<inputName<<endl;
    }
    
    if(nEvents > 0 && scaleBackgrounds){
      hist->Scale(luminosity*xSec/nEvents);
    }
    
    hist->SetName(outputName.c_str());
    hist->Write();
  }
  
  outputFile->Close();
}
