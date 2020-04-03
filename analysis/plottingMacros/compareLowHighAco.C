
//string inputPath  = "../results/basicPlots_default.root";
string inputPath  = "../results/basicPlots_data_default_tracker_branches.root";




vector<tuple<string, string, int, double, double>> histParams = {

//  name                      axis                      rebin min max
  { "lbl_photon_eta"        , "photon #eta"             , 1, -4 , 4 },
  { "lbl_photon_phi"        , "photon #phi"             , 1, -4 , 4 },
  
  { "lbl_n_all_photons"     , "N_{photons}^{all}"       , 1 ,0  , 20 },
  { "lbl_n_all_calo_towers" , "N_{towers}^{all}"        , 1 ,0  , 20 },
  { "lbl_n_all_L1EG"        , "N_{L1EG}^{all}"          , 1 ,0  , 20 },
  
//  { "lbl_diphoton_mass"     , "diphoton m_{inv} (GeV)"  },
//  { "lbl_diphoton_rapidity" , "diphoton rapidity"       },
  
//
//  { "track_dz"              , "track d_{z} (cm)"        },
//  { "track_dxy"             , "track d_{xy} (cm)"       },
//  { "track_valid_hits"      , "N_{hits}^{valid}"        },

//  { "track_eta"             , "track #eta"              },
//  { "track_missing_hits"    , "N_{hits}^{missing}"      },
//  { "nTracks"               , "N_{tracks}"              },
//
//  { "lbl_nee_failing"       , "# failing calo"          },
  
//  name                      axis                      rebin min max
//  { "lbl_diphoton_pt"       , "diphoton p_{t}"          , 1 , 0 , 5  },
//  { "lbl_photon_et"         , "photon E_{t} (GeV)"      , 1 , 0 , 10 },
  { "track_pt"              , "track p_{t}"             , 10, 0 , 10 },
  { "lbl_EB_leading_tower"  , "EB leading energy (GeV)" , 1 , 0 , 5  },
  { "lbl_EE_leading_tower"  , "EE leading energy (GeV)" , 1 , 0 , 10 },
  { "lbl_HB_leading_tower"  , "HB leading energy (GeV)" , 1 , 0 , 5  },
  { "lbl_HE_leading_tower"  , "HE leading energy (GeV)" , 1 , 0 , 5  },
  { "lbl_HFp_leading_tower" , "HF+ leading energy (GeV)", 1 , 0 , 10 },
  { "lbl_HFm_leading_tower" , "HF- leading energy (GeV)", 1 , 0 , 10 },
  
  { "track_dxy_from_bs"     , "|track, BS|_{xy} (cm)"   ,100, 0 , 0.5},
  { "nPixelClusters"        , "N_{clusters}^{pixel}"    , 1 , 0 , 100},
};

void compareLowHighAco()
{
  gStyle->SetOptStat(0);
  TFile *inFile = TFile::Open(inputPath.c_str());
  
  TCanvas *canvas = new TCanvas("canvas", "canvas", 2800, 1800);
  canvas->Divide(4, 4);
  
  int iCanvas=1;
  
  for(auto &[histName, xAxis, rebin, minX, maxX] : histParams){
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
    histLowAco->Rebin(rebin);
    
    histHighAco->SetLineColor(kRed);
    histHighAco->SetMarkerColor(kRed);
    histHighAco->SetMarkerStyle(20);
    histHighAco->SetMarkerSize(0.7);
    histHighAco->Rebin(rebin);
    
    histHighAco->SetTitle("");
    histHighAco->GetXaxis()->SetTitle(xAxis.c_str());
    histHighAco->GetXaxis()->SetTitleSize(0.07);
    
    gPad->SetBottomMargin(0.2);
    
    histHighAco->GetXaxis()->SetRangeUser(minX, maxX);
    
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
