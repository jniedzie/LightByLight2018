
//string inputPathLowAco    = "../ntuples/ntuples_mc_lbl_sc_passingLbL_lowAco.root";
//string inputPathHighAco   = "../ntuples/ntuples_mc_lbl_sc_passingLbL_highAco.root";

string inputPathLowAco    = "../ntuples/ntuples_data_passingLbL_lowAco.root";
string inputPathHighAco   = "../ntuples/ntuples_data_passingLbL_highAco.root";

const int nPlotsPerCanvas = 12;

pair<double, double> getHistLimits(TTree *tree, string name)
{
  int nBins = 1000000;
  double xMin = -1000;
  double xMax = 1000;
  
  string histExpression = name+">>tmpHist("+to_string(nBins)+","+to_string(xMin)+","+to_string(xMax)+")";
  tree->Draw(histExpression.c_str(), "" , "goff");
  TH1 *hist = (TH1*)gDirectory->Get("tmpHist");
  
  if(!hist){
    cout<<"WARNING -- couldn't create a histogram from tree entries!!"<<endl;
    return make_pair(0,0);
  }
  
  double foundMin = -9999999;
  double foundMax =  9999999;
  
  for(int i=1; i<=hist->GetNbinsX(); i++){
    if(hist->GetBinContent(i) != 0){
      foundMin = hist->GetBinCenter(i);
      break;
    }
  }
  for(int i=hist->GetNbinsX(); i>0; i--){
    if(hist->GetBinContent(i) != 0){
      foundMax = hist->GetBinCenter(i);
      break;
    }
  }
  return make_pair(foundMin, foundMax);
}

bool drawHist(TTree *treeLowAco, TTree *treeHighAco, string name)
{
  auto [minLow , maxLow]  = getHistLimits(treeLowAco, name);
  auto [minHigh, maxHigh] = getHistLimits(treeLowAco, name);
  
  int nBins = 100;
  double xMin = min(minLow, minHigh);
  double xMax = max(maxLow, maxHigh);
  if(xMin < -9999 || xMax > 9999) return false;
  
  string histExpression = name+">>tmpHist("+to_string(nBins)+","+to_string(xMin)+","+to_string(xMax)+")";
  
  treeHighAco->Draw(histExpression.c_str(), "", "goff");
  TH1 *histHighAco = (TH1*)gDirectory->Get("tmpHist");
  
  if(!histHighAco){
    cout<<"WARNING -- couldn't create a histogram from tree entries!!"<<endl;
    return false;
  }
  
  histHighAco->SetLineColor(kRed);
  histHighAco->DrawNormalized();
  
  treeLowAco->Draw(histExpression.c_str(), "" , "goff");
  TH1 *histLowAco = (TH1*)gDirectory->Get("tmpHist");
  
  if(!histLowAco){
    cout<<"WARNING -- couldn't create a histogram from tree entries!!"<<endl;
    return false;
  }
  
  histLowAco->SetLineColor(kGreen);
  histLowAco->DrawNormalized("same");
  
  if(histLowAco->GetEntries()==0 && histHighAco->GetEntries()==0) return false;
  
  return true;
}

void compareLowHighAcoTrees()
{
  gStyle->SetOptStat(0);
  
  TFile *inFileLowAco   = TFile::Open(inputPathLowAco.c_str());
  TFile *inFileHighAco  = TFile::Open(inputPathHighAco.c_str());
  
  TTree *treeLowAco   = (TTree*)inFileLowAco->Get("ggHiNtuplizer/EventTree");
  TTree *treeHighAco  = (TTree*)inFileHighAco->Get("ggHiNtuplizer/EventTree");
  
  
  TObjArray *branches = treeLowAco->GetListOfBranches();

  int nBranches = branches->GetEntries();
  
  cout<<"N branches: "<<nBranches<<endl;
 
  
  int iCanvas=0;
  vector<TCanvas*> canvases;
  canvases.push_back(new TCanvas(("c"+to_string(iCanvas)).c_str(), ("c"+to_string(iCanvas)).c_str(), 2800, 1800));
  canvases.back()->Divide(4,3);
  int iPad=1;
  /*
  for(int i=0; i<nBranches; ++i){
    string name = branches->At(i)->GetName();
    if(name.find("pho") != string::npos) cout<<name<<endl;
  }
  */
  
  for(int i=0; i<nBranches; ++i){
    cout<<"\033[1G"<<"Processed "<<i<<"\\"<<nBranches<<" branches"<<flush;
    
    canvases.back()->cd(iPad);
  
    bool drawingOk = drawHist(treeLowAco, treeHighAco, branches->At(i)->GetName());
    if(!drawingOk) continue;
    
    iPad++;
    if(iPad > nPlotsPerCanvas){
      iPad=1;
      iCanvas++;
      canvases.push_back(new TCanvas(("c"+to_string(iCanvas)).c_str(), ("c"+to_string(iCanvas)).c_str(), 2800, 1800));
      canvases.back()->Divide(4,3);
    }
  }
  
  /*
  TH1D *histLow   = new TH1D("histLow", "histLow", 100, 0, 50);
  histLow->SetLineColor(kGreen);
  TH1D *histHigh  = new TH1D("histHigh", "histHigh", 100, 0, 50);
  histHigh->SetLineColor(kRed);
  
  vector<float> *energyLow            = nullptr;
  vector<float> *energyHigh           = nullptr;
  vector<float> *preshowerEnergyLow   = nullptr;
  vector<float> *preshowerEnergyHigh  = nullptr;
  
  treeLowAco->SetBranchAddress("phoE", &energyLow);
  treeLowAco->SetBranchAddress("phoE2nd", &preshowerEnergyLow);
  treeHighAco->SetBranchAddress("phoE", &energyHigh);
  treeHighAco->SetBranchAddress("phoE2nd", &preshowerEnergyHigh);
  
  for(int iEvent=0; iEvent<treeLowAco->GetEntries(); iEvent++){
    treeLowAco->GetEntry(iEvent);
    for(int iPhoton=0; iPhoton<energyLow->size(); iPhoton++){
      
      double value = energyLow->at(iPhoton)/preshowerEnergyLow->at(iPhoton);
      if(!isnormal(value)) continue;
      
      
      histLow->Fill(value);
    }
  }
  
  for(int iEvent=0; iEvent<treeHighAco->GetEntries(); iEvent++){
    treeHighAco->GetEntry(iEvent);
    for(int iPhoton=0; iPhoton<energyHigh->size(); iPhoton++){
      double value = energyHigh->at(iPhoton)/preshowerEnergyHigh->at(iPhoton);
      if(!isnormal(value)) continue;
      
      
      histHigh->Fill(value);
    }
  }

  canvases.back()->cd(1);
  histLow->DrawNormalized();
  histHigh->DrawNormalized("same");
  */
}
