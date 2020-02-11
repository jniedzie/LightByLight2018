void drawLowMassDielectrons()
{
  TFile *inFile = TFile::Open("../results/basicPlots.root");
  
  TH1D *mInvData = (TH1D*)inFile->Get("qed_dielectron_mass_low_no_cuts_Data");
  
  mInvData->Rebin(3);
  
  mInvData->SetMarkerStyle(20);
  mInvData->SetMarkerSize(0.3);
  mInvData->SetMarkerColor(kBlack);
  mInvData->SetLineColor(kBlack);
  
  mInvData->Draw("pe");
//  mInvData->GetXaxis()->SetRangeUser(0, 2);
  
  vector<double> masses = {0.1349770, 0.547862, 0.78265, 0.95778, 1.019461, 0.497611, 3.096900, 3.686097, 4.039, 10.02326, 10.3552, 10.5794, 10.8899, 10.9929 };
  
  vector<TLine*> lines;
  
  for(double mass : masses){
    lines.push_back(new TLine(mass, 15, mass, 140));
    lines.back()->SetLineColor(kViolet);
    lines.back()->Draw();
  }
  
}
