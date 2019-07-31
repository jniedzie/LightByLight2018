
const int maxNevents = 200000;

vector<tuple<string, int, string>> histParams = {
// file name                                 color       description
  {"ntuples_data_small_sample_merged.root"  , kOrange+2 , "Data"        },
  {"ntuples_mc_lbl_merged.root"             , kBlack    , "LbL MC"      },
  {"ntuples_mc_qed_sc_merged.root"          , kBlue     , "QED MC (SC)" },
};

void prepareHist(TH1D *hist, int color)
{
  hist->SetLineColor(color);
  hist->SetLineWidth(2);
  hist->SetTitle("");
  hist->GetYaxis()->SetTitle("# events");
  hist->GetYaxis()->SetTitleSize(0.06);
  hist->GetXaxis()->SetTitle("# tracks");
  hist->GetXaxis()->SetTitleSize(0.06);
  hist->Scale(1./hist->GetEntries());
  hist->GetXaxis()->SetRangeUser(0, 15);
  hist->GetYaxis()->SetRangeUser(1e-4, 1.0);
  hist->Sumw2(false);
}

void preparePad()
{
  gPad->SetLogy();
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);
}

void drawNtracks()
{
  TFile *inFile[histParams.size()];
  
  TCanvas *canvas = new TCanvas("N tracks", "n Tracks", 1000, 1000);
  canvas->Divide(2,2);
  
  gStyle->SetOptStat(0);
  TLegend *legend = new TLegend(0.5, 0.7, 0.9, 0.9 );
  map<string, pair<TH1D*, TH1D*>> hists;
  
  bool first = true;
  for(auto &[name, color, description] : histParams){
    cout<<"Processing "<<description<<" events"<<endl;
    
    
    auto inFile = TFile::Open(("ntuples/"+name).c_str());
    auto inTree = (TTree*)inFile->Get("ggHiNtuplizer/EventTree");
    
    int nTracks;
    vector<double> *trackPt;
    
    inTree->SetBranchAddress("ngenTrk", &nTracks);
    inTree->SetBranchAddress("gentrkPt", &trackPt);
    
    TH1D *nTrackHist       = new TH1D("nTracks", "nTracks", 100, 0, 100);
    TH1D *nTrackHighPtHist = new TH1D("nTracks pt >= 100 MeV", "nTracks pt >= 100 MeV", 100, 0, 100);
    TH1D *nTrackLowPtHist  = new TH1D("nTracks pt < 100 MeV", "nTracks pt < 100 MeV", 100, 0, 100);
    TH1D *trackPtHist      = new TH1D("Track pt", "Track pt", 500, 0, 5);
    
    for(int iEvent=0; iEvent<inTree->GetEntries(); iEvent++){
      if(iEvent%5000==0) cout<<"Processing event "<<iEvent<<endl;
      if(iEvent >= maxNevents) break;
      
      inTree->GetEntry(iEvent);
      nTrackHist->Fill(nTracks);
      
      for(int iTrack=0; iTrack<nTracks; iTrack++){
        trackPtHist->Fill(trackPt->at(iTrack));
        
        if(trackPt->at(iTrack) < 0.1) nTrackLowPtHist->SetBinContent(nTracks+1, nTrackLowPtHist->GetBinContent(nTracks+1)+1);
        else                          nTrackHighPtHist->SetBinContent(nTracks+1, nTrackHighPtHist->GetBinContent(nTracks+1)+1);
      }
    }
    
    prepareHist(nTrackHist, color);
    prepareHist(nTrackLowPtHist, color);
    prepareHist(nTrackHighPtHist, color);
    prepareHist(trackPtHist, color);
    
    canvas->cd(1); preparePad();
    nTrackHist->SetTitle("# tracks");
    nTrackHist->Draw(first ? "" : "same");
    
    canvas->cd(2); preparePad();
    trackPtHist->SetTitle("Track p_{T}");
    trackPtHist->SetLineWidth(1);
    trackPtHist->GetXaxis()->SetTitle("p_{T} (GeV)");
    trackPtHist->GetXaxis()->SetRangeUser(0, 1);
    trackPtHist->GetYaxis()->SetRangeUser(1e-6, 1);
    trackPtHist->Draw(first ? "" : "same");
    
    canvas->cd(3); preparePad();
    nTrackLowPtHist->SetTitle("# tracks, p_{T} < 100 MeV");
    nTrackLowPtHist->Draw(first ? "" : "same");
    
    canvas->cd(4); preparePad();
    nTrackHighPtHist->SetTitle("# tracks, p_{T} #geq 100 MeV");
    nTrackHighPtHist->Draw(first ? "" : "same");
    
    legend->AddEntry(nTrackHist, description.c_str(), "l");
    
    first = false;
  }
  
  canvas->cd(1); legend->Draw("same");
  canvas->cd(2); legend->Draw("same");
  canvas->cd(3); legend->Draw("same");
  canvas->cd(4); legend->Draw("same");
  
  canvas->SaveAs("plots/nTracks.pdf");
}
