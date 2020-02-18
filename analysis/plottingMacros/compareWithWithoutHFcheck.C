
string inputPathWithHFcheck  = "../results/basicPlots_withHFcheck.root";
string inputPathNoHFcheck    = "../results/basicPlots_noHFcheck.root";

vector<tuple<string, string>> histParams = {
  { "lbl_photon_et"          , "photon E_{t} (GeV)"      },
  { "lbl_photon_eta"         , "photon #eta"             },
  { "lbl_photon_phi"         , "photon #phi"             },
  { "lbl_diphoton_mass"      , "diphoton m_{inv} (GeV)"  },
  { "lbl_diphoton_rapidity"  , "diphoton rapidity"       },
  { "lbl_diphoton_pt"        , "diphoton p_{t}"          },
};

void compareWithWithoutHFcheck()
{
  gStyle->SetOptStat(0);
  TFile *inFileWithHFcheck  = TFile::Open(inputPathWithHFcheck.c_str());
  TFile *inFileNoHFcheck    = TFile::Open(inputPathNoHFcheck.c_str());
  
  TCanvas *canvas = new TCanvas("canvas", "canvas", 2800, 1800);
  canvas->Divide(3, 2);
  
  int iCanvas=1;
  
  for(auto &[histName, xAxis] : histParams){
    canvas->cd(iCanvas++);
    
    TH1D *histWithHFcheck   = (TH1D*)inFileWithHFcheck->Get((histName+"_high_aco_Data").c_str());
    TH1D *histNoHFcheck     = (TH1D*)inFileNoHFcheck->Get((histName+"_high_aco_Data").c_str());
    
    if(!histWithHFcheck || !histNoHFcheck){
      cout<<"ERROR -- no histogram \""<<histName<<"\" found"<<endl;
      continue;
    }
    histWithHFcheck->SetLineColor(kGreen+2);
    histWithHFcheck->SetMarkerColor(kGreen+2);
    histWithHFcheck->SetMarkerStyle(20);
    histWithHFcheck->SetMarkerSize(0.7);
    
    histNoHFcheck->SetLineColor(kRed);
    histNoHFcheck->SetMarkerColor(kRed);
    histNoHFcheck->SetMarkerStyle(20);
    histNoHFcheck->SetMarkerSize(0.7);
    
    histNoHFcheck->SetTitle("");
    histNoHFcheck->GetXaxis()->SetTitle(xAxis.c_str());
    histNoHFcheck->GetXaxis()->SetTitleSize(0.07);
    
    gPad->SetBottomMargin(0.2);
    
    histNoHFcheck->DrawNormalized("pe");
    histWithHFcheck->DrawNormalized("pesame");
    
    if(iCanvas==2){
      TLegend *leg = new TLegend(0.6, 0.7, 0.9, 0.9);
      leg->AddEntry(histWithHFcheck , "with HF check" , "ep");
      leg->AddEntry(histNoHFcheck   , "no HF check"   , "ep");
      leg->Draw();
    }
    
  }
  
}
