string inputPath  = "../analysis/results/basicPlots_default.root";
string outputPath = "input_hacoplanarity.root";

string histName = "lbl_acoplanarity_all_";

double luminosity = 1609.910015010; // from brilcalc, 1/μb

double referenceAlpXsec = 10e-3; // (μb)

vector<tuple<string, string, int, double>> backgroundParams = {
// input_name   output_name nGenEvents  xSec (μb)
  {"Data"     , "data_obs"  , -1      , -1      },
  {"LbL"      , "lbyl"      , 371000  , 2.59    },
  {"CEP"      , "cep"       , 738000  , 0.0058  },
  {"QED_SC"   , "qed"       , 950000  , 8830    },
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
    
    if(nEvents > 0){
      hist->Scale(luminosity*xSec/nEvents);
    }
    
    hist->SetName(outputName.c_str());
    hist->Write();
  }
  
  outputFile->Close();
}
