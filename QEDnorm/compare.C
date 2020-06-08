void compare(const char* histname) {
   TFile *_file0 = new TFile("output.root");
   TFile *_file1 = new TFile("outputData.root");
   TH1F *histmc = (TH1F*) _file0->Get(histname); TH1F *histdata = (TH1F*) _file1->Get(histname); 
   histmc->SetLineColor(kBlack); histdata->SetLineColor(kRed);
   histmc->SetMarkerColor(kBlack); histdata->SetMarkerColor(kRed);
   TCanvas *c1 = new TCanvas();
   histmc->DrawNormalized(); histdata->DrawNormalized("same");
}
