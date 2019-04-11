void produceCaloTowerTree()
{
  TFile *inFile = TFile::Open("HiForestAOD_check_AOD_1.root");
  TTree *inTree = (TTree*)inFile->Get("ggHiNtuplizer/EventTree");
  
//  vector<float> *CaloTower_hadE;
//  inTree->SetBranchAddress("CaloTower_hadE",&CaloTower_hadE);
  
  inTree->SetBranchStatus("*",0);
  inTree->SetBranchStatus("CaloTower_hadE",1);
  inTree->SetBranchStatus("CaloTower_emE",1);
  inTree->SetBranchStatus("CaloTower_e",1);
  inTree->SetBranchStatus("CaloTower_et",1);
  inTree->SetBranchStatus("CaloTower_eta",1);
  inTree->SetBranchStatus("CaloTower_phi",1);
  
  //Create a new file + a clone of old tree in new file
  TFile *outFile = new TFile("caloTowersTree.root","recreate");
  outFile->mkdir("ggHiNtuplizer");
  outFile->cd("ggHiNtuplizer");
  TTree *outTree = inTree->CloneTree();
  
  outFile->Write();
}
