
string inputPath  = "../results/basicPlots_default.root";

vector<tuple<string, string>> histParams = {
  { "lbl_photon_et"         , "photon E_{t} (GeV)"      },
  { "lbl_photon_eta"        , "photon #eta"             },
  { "lbl_photon_phi"        , "photon #phi"             },
  { "lbl_diphoton_mass"     , "diphoton m_{inv} (GeV)"  },
  { "lbl_diphoton_rapidity" , "diphoton rapidity"       },
  { "lbl_diphoton_pt"       , "diphoton p_{t}"          },
  
  { "track_dz"              , "track d_{z} (cm)"        },
  { "track_dxy"             , "track d_{xy} (cm)"       },
  { "track_valid_hits"      , "N_{hits}^{valid}"        },
  { "track_pt"              , "track p_{t}"             },
  { "track_eta"             , "track #eta"              },
  { "track_missing_hits"    , "N_{hits}^{missing}"      },
  { "nTracks"               , "N_{tracks}"              },
  
  { "lbl_nee_failing"       , "# failing calo"          },
  
};

void compareLowHighAco()
{
  gStyle->SetOptStat(0);
  TFile *inFile = TFile::Open(inputPath.c_str());
  
  TCanvas *canvas = new TCanvas("canvas", "canvas", 2800, 1800);
  canvas->Divide(4, 4);
  
  int iCanvas=1;
  
  for(auto &[histName, xAxis] : histParams){
    canvas->cd(iCanvas++);
    
    TH1D *histLowAco  = (TH1D*)inFile->Get((histName+"_low_aco_Data").c_str());
    TH1D *histHighAco = (TH1D*)inFile->Get((histName+"_high_aco_Data").c_str());
    
    if(!histLowAco || !histHighAco){
      cout<<"ERROR -- no histogram \""<<histName<<"\" found"<<endl;
      continue;
    }
    histLowAco->SetLineColor(kGreen+2);
    histLowAco->SetMarkerColor(kGreen+2);
    histLowAco->SetMarkerStyle(20);
    histLowAco->SetMarkerSize(0.7);
    
    histHighAco->SetLineColor(kRed);
    histHighAco->SetMarkerColor(kRed);
    histHighAco->SetMarkerStyle(20);
    histHighAco->SetMarkerSize(0.7);
    
    histHighAco->SetTitle("");
    histHighAco->GetXaxis()->SetTitle(xAxis.c_str());
    histHighAco->GetXaxis()->SetTitleSize(0.07);
    
    gPad->SetBottomMargin(0.2);
    
    histHighAco->DrawNormalized("pe");
    histLowAco->DrawNormalized("pesame");
    
//    histHighAco->Scale(1./histHighAco->GetBinContent(3)*histLowAco->GetBinContent(3));
//    histHighAco->Draw("pe");
//    histLowAco->Draw("pesame");
    
    if(iCanvas==2){
      TLegend *leg = new TLegend(0.6, 0.7, 0.9, 0.9);
      leg->AddEntry(histLowAco, "A_{#phi} < 0.01", "ep");
      leg->AddEntry(histHighAco,"A_{#phi} > 0.01", "ep");
      leg->Draw();
    }
    
  }
  
}
