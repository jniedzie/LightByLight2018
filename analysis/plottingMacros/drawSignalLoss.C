#include "plotStyle.h"

void drawSignalLoss(){
  TFile f("../missed_photons.root");
  TTree* tree;
  tree = (TTree*)f.Get("output_tree");
 // TLeaf* bxidLeaf = (TLeaf*) tree->GetLeaf("bxid");

  int nPho;

  int nTrk;
  float trkPt[99];
  float trkEta[99];
  float trkPhi[99];

  int nMissPho;
  float missedPhotonEta[2];
  float missedPhotonPhi[2];

  tree->SetBranchAddress("nPho",&nPho);

  tree->SetBranchAddress("nTrk",&nTrk);
  tree->SetBranchAddress("trkPt",&trkPt);
  tree->SetBranchAddress("trkEta",&trkEta);
  tree->SetBranchAddress("trkPhi",&trkPhi);

  tree->SetBranchAddress("nMissPho",&nMissPho);
  tree->SetBranchAddress("missedPhotonEta",&missedPhotonEta);
  tree->SetBranchAddress("missedPhotonPhi",&missedPhotonPhi);

  TH1F* pt = new TH1F("",";p_{T} [GeV];Entries",50,0.0,10.0);
  TH2F* etaPt = new TH2F("",";#eta;p_{T} [GeV]",30,-2.4,2.4,30,0.0,10.0);
  TH2F* etaPhi = new TH2F("",";#eta;#phi [rad]",30,-2.4,2.4,30,-3.15,3.15);
  TH2F* nPhoTrk = new TH2F("",";N_{#gamma};N_{track}",4,3,7,4,1,5);
  TH2F* missedPhotonEtaPhi = new TH2F("",";#eta;#phi [rad]",20,-2.5,2.5,20,-3.15,3.15);

  for(int i = 0; i < tree->GetEntries(); i++){
    tree->GetEntry(i);

    for(int j = 0; j < nTrk; j++){
      pt->Fill(trkPt[j]);
      etaPt->Fill(trkEta[j],trkPt[j]);
      etaPhi->Fill(trkEta[j],trkPhi[j]);
    }

    for(int j = 0; j < nMissPho; j++)
      missedPhotonEtaPhi->Fill(missedPhotonEta[j],missedPhotonPhi[j]);

    nPhoTrk->Fill(nPho,nTrk);
  }

  TCanvas* c1 = new TCanvas();

  pt->Draw("hist e");
  c1->SaveAs("figures/trkPt.png");

  etaPt->Draw("colz");
  c1->SaveAs("figures/trkEtaPt.png");

  etaPhi->Draw("colz");
  c1->SaveAs("figures/trkEtaPhi.png");

  //c1->SetLogz();

  nPhoTrk->Draw("colz");
  c1->SaveAs("figures/nPhoTrk.png");

  missedPhotonEtaPhi->Draw("colz");
  c1->SaveAs("figures/missedPhotonEtaPhi.png");
}
