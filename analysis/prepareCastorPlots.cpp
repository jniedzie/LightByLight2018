//  prepareShowerShapePlots.cpp
//
//  Created by Jeremi Niedziela on 30/07/2019.

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"
#include "Logger.hpp"
#include <fstream>

ofstream outfile("test_energy.dat");

int run;
int ls;
int evtnb;
float photon_Et;
float photon_Eta;
float photon_Phi;
float photon_SCEt;
float photon_SCEta;
float photon_SCPhi;
float photon_SwissCross;
float photon_EtaWidth;
float photon_HoverE;
float photon_SigmaIEtaIEta;
float photon_SeedTime;
int ok_neuexcl;
int ok_zdcexcl;
int ok_chexcl;


/// initialise tree
void InitTree(TTree *tr) {
  tr->Branch("run",       &run,         "run/I");
  tr->Branch("ls",        &ls,          "ls/I");
  tr->Branch("evtnb",     &evtnb,       "evtnb/I");
  tr->Branch("photon_Et",           &photon_Et,           "photon_Et/F");
  tr->Branch("photon_Eta",          &photon_Eta,          "photon_Eta/F");
  tr->Branch("photon_Phi",          &photon_Phi,          "photon_Phi/F");
  tr->Branch("photon_SCEt",         &photon_SCEt,         "photon_SCEt/F");
  tr->Branch("photon_SCEta",        &photon_SCEta,        "photon_SCEta/F");
  tr->Branch("photon_SCPhi",        &photon_SCPhi,        "photon_SCPhi/F");
  tr->Branch("photon_SwissCross",   &photon_SwissCross,   "photon_SwissCross/F");
  tr->Branch("photon_EtaWidth",     &photon_EtaWidth,     "photon_EtaWidth/F");
  tr->Branch("photon_HoverE",       &photon_HoverE,       "photon_HoverE/F");
  tr->Branch("photon_SigmaIEtaIEta",&photon_SigmaIEtaIEta,"photon_SigmaIEtaIEta/F");
  tr->Branch("photon_SeedTime",     &photon_SeedTime,     "photon_SeedTime/F");
  tr->Branch("ok_neuexcl",          &ok_neuexcl,          "ok_neuexcl/I");
  tr->Branch("ok_zdcexcl",          &ok_zdcexcl,          "ok_zdcexcl/I");
  tr->Branch("ok_chexcl",           &ok_chexcl,           "ok_chexcl/I");
}

// reset all variables
void ResetVars() {
  run =-999;
  ls=-999;
  evtnb =-999;
  photon_Et = -999;
  photon_Eta = -999;
  photon_Phi = -999;
  photon_SCEt = -999;
  photon_SCEta = -999;
  photon_SCPhi = -999;
  photon_SwissCross = -999;
  photon_EtaWidth = -999;
  photon_HoverE = -999;
  photon_SigmaIEtaIEta = -999;
  photon_SeedTime = -999;
  ok_neuexcl = -999;
  ok_zdcexcl = -999;
  ok_chexcl  = -999;
}
 

vector<tuple<string, int, double, double>> histParams = {
  // title                     nBins min   max
  {"nCastor"                  , 100 , 0   , 100},
  {"eTotCastor"               , 100 , 0.  , 100.},
  {"eEmCastor"                , 100 , 0.  , 100.},
  {"eHadCastor"               , 100 , 0.  , 100.},
  {"eTotCastor0"             , 100 , 0.  , 200.},
  {"eTotCastor1"             , 100 , 0.  , 200.},
  {"eTotCastor2"             , 100 , 0.  , 200.},
  {"eTotCastor3"             , 100 , 0.  , 200.},
  {"eTotCastor4"             , 100 , 0.  , 200.},
  {"eTotCastor5"             , 100 , 0.  , 200.},
  {"eTotCastor6"             , 100 , 0.  , 200.},
  {"eTotCastor7"             , 100 , 0.  , 200.},
  {"eTotCastor8"             , 100 , 0.  , 200.},
  {"eTotCastor9"             , 100 , 0.  , 200.},
  {"eTotCastor10"             , 100 , 0.  , 200.},
  {"eTotCastor11"             , 100 , 0.  , 200.},
  {"eTotCastor12"             , 100 , 0.  , 200.},
  {"eTotCastor13"             , 100 , 0.  , 200.},
  {"eTotCastor14"             , 100 , 0.  , 200.},
  {"eTotCastor15"             , 100 , 0.  , 200.},
};

vector<tuple<string, int, double, double, int, double, double>> histParams2D = {
  // title         nBinsX minX   maxX   nBinsY minY  maxY
  {"leadingCastorTowerEtaPhi" , 100 , -3.14 , 3.14 , 100 , -6.6 , -5.2 },
  {"eTotPhiCastor" , 100 , -3.14 , 3.14 , 100 , 0. , 100. },

};

double getSwisscross(shared_ptr<PhysObject> photon)
{
  double E4 = photon->GetEnergyCrystalTop() +
  photon->GetEnergyCrystalBottom() +
  photon->GetEnergyCrystalLeft() +
  photon->GetEnergyCrystalRight();
  
  double swissCross = 1 - (E4/photon->GetEnergyCrystalMax());
  
  if(E4 < 0){
    Log(1)<<"WARNING -- swiss cross cannot be calculated. The event will pass this selection automatically!!\n";
    swissCross = -999999;
  }
  
  return swissCross;
}

unsigned int convertPhiToIndex(double phi){
  vector<double> possiblePhiValues = {-2.95,-2.55,-2.16,-1.77,-1.37,-0.98,-0.59,-0.20,0.20,0.59,0.98,1.37,1.77,2.16,2.55,2.95};

  for(unsigned int index = 0; index < possiblePhiValues.size(); index++)
    if(fabs(possiblePhiValues[index]-phi) < 0.2)
      return index;

  return -1;
}

void fillHistograms(const unique_ptr<EventProcessor> &events,
                    const map<string, TH1D*> &hists,
                    const map<string, TH2D*> &hists2D,
                    string datasetName, TTree* tr)
{
  set<int> phiValues;

  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
    if(iEvent%10000==0) Log(0)<<"Processing event "<<iEvent<<"\n";
    if(iEvent >= config.params("maxEvents")) break;

    auto event = events->GetEvent(iEvent);
    ResetVars();  
    run = event->GetRunNumber();
    ls = event->GetLumiSection();
    evtnb = event->GetEventNumber();

    // Check that event passes cuts
    
    // Triggers and exclusivity
    //    if(!event->HasDoubleEG2Trigger()) continue;
    //    if(event->HasChargedTracks()) continue;
    //    if(event->HasAdditionalTowers()) continue;

    double temp_energy = 0.0;
    double temp_eta;
    double temp_phi;
    double isTower = false;

    for(auto castor : event->GetPhysObjects(EPhysObjType::kCastor)){
      hists.at("eHadCastor"+datasetName)->Fill(castor->GetEnergyHad());
      hists.at("eEmCastor"+datasetName)->Fill(castor->GetEnergyEm());
      hists.at("eTotCastor"+datasetName)->Fill(castor->GetEnergy());
      hists2D.at("eTotPhiCastor"+datasetName)->Fill(castor->GetPhi(),castor->GetEnergy());
      hists.at("eTotCastor"+to_string(convertPhiToIndex(castor->GetPhi()))+datasetName)->Fill(castor->GetEnergy());

      //phiValues.insert(floor(castor->GetPhi()*10000));

      //outfile << castor->GetEnergy() << std::endl;
      if(castor->GetEnergy() > temp_energy){
        temp_eta = castor->GetEta();
        temp_phi = castor->GetPhi();
        temp_energy = castor->GetEnergy();
        //Log(0) << temp_phi << "\t" << convertPhiToIndex(temp_phi) << "\n";
        isTower = true;

      }
    }

    if(isTower){
      hists2D.at("leadingCastorTowerEtaPhi"+datasetName)->Fill(temp_phi,temp_eta);
    }
  }//event

  //for(auto s : phiValues)
  //  Log(0) << s/10000.0 << "\n";
} // fill histogram

map<string, TH1D*> init1Dhists(string name)
{
  map<string, TH1D*> hists;
  for(auto params : histParams){
    string title = get<0>(params)+name;
    hists[title] = new TH1D(title.c_str(), title.c_str(), get<1>(params), get<2>(params), get<3>(params));
  }
  return hists;
}

map<string, TH2D*> init2Dhists(string name)
{
  map<string, TH2D*> hists;
  
  for(auto params : histParams2D){
    string title = get<0>(params)+name;
    hists[title] = new TH2D(title.c_str(), title.c_str(),
                            get<1>(params), get<2>(params), get<3>(params),
                            get<4>(params), get<5>(params), get<6>(params));
  }
  return hists;
}

int main(int argc, char* argv[])
{
  if(argc != 5){
    Log(0)<<"This app requires 4 parameters.\n";
    Log(0)<<"./getEfficienciesData configPath sampleName inputPath outputPath\n";
    exit(0);
  }
  
  // read input arguments
  string configPath  = argv[1];
  string sampleName  = argv[2];
  string inputPath   = argv[3];
  string outputPath  = argv[4];
  
  // create config manager
  config = ConfigManager(configPath);
  EDataset dataset;
  
  // load events from input file
  if(sampleName == "Data")          dataset = kData;
  else if(sampleName == "QED_SC")   dataset = kMCqedSC;
  else if(sampleName == "QED_SL")   dataset = kMCqedSL;
  else if(sampleName == "LbL")      dataset = kMClbl;
  else if(sampleName == "CEP")      dataset = kMCcep;
  else{
    Log(0)<<"Unrecognised sample name: "<<sampleName<<"!!\n";
    exit(0);
  }
  
  auto events = make_unique<EventProcessor>(inputPath, dataset);
  
  TFile *outFile = TFile::Open(outputPath.c_str(), "recreate");
  TTree *photonIDVars = new TTree("photonIDVars_tree","");
  InitTree(photonIDVars);

  // fill histograms
  map<string, TH1D*> hists = init1Dhists(sampleName);
  map<string, TH2D*> hists2D = init2Dhists(sampleName);
  fillHistograms(events, hists, hists2D, sampleName,photonIDVars );
  
  // save output files
  //TFile *outFile = new TFile(outputPath.c_str(), "recreate");
  outFile->cd();
  outFile->Write();
  for(auto hist : hists)    hist.second->Write();
  for(auto hist : hists2D)  hist.second->Write();
  outFile->Close();
}
