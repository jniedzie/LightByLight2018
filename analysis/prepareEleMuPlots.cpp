

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"
#include "EventDisplay.hpp"
#include "Logger.hpp"

  string configPath = "configs/preparePlots_default.md";
  string outputPath = "Output/basicPlots_test.root";

bool saveCalosFailingNEE = true;
//bool saveTriphotonHists = true;
//bool checkTriggers = false;

//int nThreePhotonEvents = 0;


// Only those datasets will be analyzed
 const vector<EDataset> datasetsToAnalyze = {
   kData,
};

vector<string> suffixes = {
  "all"
};

vector<tuple<string, int, double, double>> histParams = {
 
   // title                   nBins min   max
  {"dilepton_acoplanarity"       , 4000 , 0   , 1.0   },
  {"lepton_pt"          , 100 , 0   , 100.0 },
  {"lepton_eta"         , 200   ,-2.4 , 2.4   },
  {"lepton_phi"         , 200   ,-4.0 , 4.0   },
 // {"dilepton_mass"      , 10  , 0   , 25.0 },
 // {"dilepton_rapidity"  , 600   ,-2.4 , 2.4   },
 // {"dilepton_pt"        , 20  , 0   , 15.0  },
};



//bool endsWith(const std::string &mainStr, const std::string &toMatch)
//{
 // if(mainStr.size() >= toMatch.size() &&
   //  mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
   // return true;
  //else
   // return false;
//}

///Muon
void fillMuonHists(Event &event, const map<string, TH1D*> &hists, string datasetName, string suffix="")
{
  for(auto muon : event.GetPhysObjects(EPhysObjType::kMuon)){
    hists.at("lepton_pt_" +suffix+datasetName)->Fill(muon->GetPt());
    hists.at("lepton_eta_"+suffix+datasetName)->Fill(muon->GetEta());
    hists.at("lepton_phi_"+suffix+datasetName)->Fill(muon->GetPhi());
    
  }
}



//Copy from dimuon
//void fillEleMuHists(Event &event, const map<string, TH1D*> &hists, string datasetName, string suffix="")
//{
   
  //TLorentzVector elemu = physObjectProcessor.GetEleMu(*event.GetPhysObjects(EPhysObjType::kMuon)[0],
   //                                                     *event.GetPhysObjects(EPhysObjType::kElectron)[0]);

  
 // hists.at("dilepton_mass_"     +suffix+datasetName)->Fill(elemu.M());
 // hists.at("dilepton_rapidity_" +suffix+datasetName)->Fill(elemu.Rapidity());
  //hists.at("dilepton_pt_"       +suffix+datasetName)->Fill(elemu.Pt());

//}

void fillTauTauHistograms(Event &event, const map<string, TH1D*> &hists, EDataset dataset, vector<string> suffix_list)
{
  string name = datasetName.at(dataset);
  int cutThrough=0;

  double aco = physObjectProcessor.GetAcoplanarity(*event.GetPhysObjects(EPhysObjType::kMuon)[0],
                                                   *event.GetPhysObjects(EPhysObjType::kElectron)[0]);

  for(string suffix : suffix_list){
    if(suffix != "") suffix += "_";
    hists.at("dilepton_acoplanarity_"+suffix+name)->Fill(aco);
    fillMuonHists(  event, hists, name, suffix);
//    fillDimuonHists(event, hists, name, suffix);
//    fillTracksHists(    event, hists, dataset, suffix);
  }
}


/// Creates histograms, cut through and event counters for given dataset name, for each
///// histogram specified in `histParams` vector.


void InitializeHistograms(map<string, TH1D*> &hists, string datasetType, string suffix="")
{
  if(suffix != "") suffix = "_" + suffix;

  for(auto &[histName, nBins, min, max] : histParams){
    string title = histName + suffix + "_" + datasetType;

    if(hists.find(title) != hists.end()) continue;
    hists[title] = new TH1D(title.c_str(), title.c_str(), nBins, min, max);
  }
}


int main(int argc, char* argv[])
{
  if(argc != 5){
    cout<<"This app requires 4 parameters.\n";
    cout<<"./prepareBasicPlots configPath inputPath outputPath datasetName[Data|QED_SC|QED_SL|LbL|CEP]\n";
    exit(0);
  }
  cout<<"Reading input arguments"<<endl;

  string inputPath = "";
  string sampleName = "";

  //if(argc == 5){
  configPath = argv[1];
  inputPath  = argv[2];
  outputPath = argv[3];
  sampleName = argv[4];
  //}
  cout<<"Config: "<<configPath<<endl;
  cout<<"Input: "<<inputPath<<endl;
  cout<<"Output: "<<outputPath<<endl;
  cout<<"Sample name: "<<sampleName<<endl;


  config = ConfigManager(configPath);

  map<string, TH1D*> hists;
  TFile *outFile = new TFile(outputPath.c_str(), "recreate");


 //if (endsWith(inputPath, "root")){
   // cout << "root file" << endl;
    EDataset dataset = nDatasets;

    if(sampleName == "Data")    dataset = kData;
    if(sampleName == "QED_SC")  dataset = kMCqedSC;
    if(sampleName == "QED_SL")  dataset = kMCqedSL;
    if(sampleName == "LbL")     dataset = kMClbl;
    if(sampleName == "CEP")     dataset = kMCcep;
    cout<<"test1"<<endl;
    auto events = make_unique<EventProcessor>(inputPath, dataset);

    for(string suffix : suffixes){
      InitializeHistograms(hists, sampleName, suffix);
      cout<<"test2"<<endl;
    }


    if(dataset == nDatasets){
      Log(0)<<"ERROR -- unknown dataset name provided: "<<sampleName<<"\n";
      exit(0);
    }
    
    for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
      if(iEvent%10 == 0)  Log(0)<<"Processing event "<<iEvent<<"\n";
      //if(iEvent%10000 == 0) Log(0)<<"Processing event "<<iEvent<<"\n";
      if(iEvent >= config.params("maxEvents")) break;
      cout<<"test3"<<endl;
      auto event = events->GetEvent(iEvent);
      cout<<"test4"<<endl;
      fillTauTauHistograms(*event, hists, dataset, suffixes);
      //fillDimuonHists(*event, hists, dataset);
    }

  cout << "Writing Histograms" <<endl;
  outFile->cd();
  for(auto &[histName, hist] : hists) hist->Write();


  outFile->Close();
  cout << "Finished" << endl;
}


   
