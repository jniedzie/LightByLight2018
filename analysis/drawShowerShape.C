
vector<tuple<string, int, string>> histParams = {
// name    color       description
  {"Data" , kViolet+2 , "Data"        },
  {"LbL"  , kBlack    , "LbL MC"      },
  {"QED"  , kBlue     , "QED MC (SC)" },
};

void prepareHist(TH1D *hist, int color)
{
  hist->SetLineColor(color);
  hist->SetTitle("");
  hist->GetYaxis()->SetTitle("# events");
  hist->GetYaxis()->SetTitleSize(0.06);
  hist->GetXaxis()->SetTitle("#sigma_{i#etai#eta}");
  hist->GetXaxis()->SetTitleSize(0.06);
}

void preparePad()
{
  gPad->SetLogy();
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);
}

void drawShowerShape()
{
  TFile *inFile = TFile::Open("results/showerShape.root");
  
  TCanvas *canvas = new TCanvas("Shower shape", "Shower shape", 1000, 500);
  canvas->Divide(2,1);
  gStyle->SetOptStat(0);
  TLegend *legend = new TLegend(0.5, 0.7, 0.9, 0.9 );
  map<string, pair<TH1D*, TH1D*>> hists;
  
  bool first = true;
  for(auto &[name, color, description] : histParams){
    hists[name] = make_pair((TH1D*)inFile->Get(("showerShapeBarrel"+name).c_str()),
                            (TH1D*)inFile->Get(("showerShapeEndcap"+name).c_str()));
    
    prepareHist(hists[name].first, color);
    prepareHist(hists[name].second, color);
    
    canvas->cd(1); preparePad();
    hists[name].first->DrawNormalized(first ? "" : "same");
    
    canvas->cd(2); preparePad();
    hists[name].second->DrawNormalized(first ? "" : "same");

    first = false;
    
    legend->AddEntry(hists[name].first, description.c_str(), "l");
  }
  
  canvas->cd(1); legend->Draw("same");
  canvas->cd(2); legend->Draw("same");
  
  canvas->SaveAs("plots/showerShape.pdf");
}
