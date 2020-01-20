//  prepareAcoplanarityPlots.cpp
//
//  Created by Jeremi Niedziela on 31/07/2019.

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"

string configPath = "configs/efficiencies.md";
string outputPath = "results/basicPlots.root";

// Only those datasets will be analyzed
const vector<EDataset> datasetsToAnalyze = {
//  kData,
  kData_SingleEG3,
//  kData_recoEff,
//  kData_triggerEff,
  //  kMCqedSC,
  kMCqedSC_SingleEG3,
//  kMCqedSC_recoEff,
//  kMCqedSC_triggerEff,
//    kMCqedSL,
//  kMClbl,
//  kMCcep
};

vector<tuple<string, int, double, double>> histParams = {
  // title                   nBins min   max
  {"acoplanarity"           , 200 , 0   , 1.0   },
  {"nTracks"                , 100 , 0   , 100   },
  {"nTracks_pt_geq_100_MeV" , 100 , 0   , 100   },
  {"nTracks_pt_lt_100_MeV"  , 100 , 0   , 100   },
  {"track_pt"               , 500 , 0   , 5     },
};

void fillHistograms(const unique_ptr<EventProcessor> &events,
                    const map<string, TH1D*> &hists,
                    string datasetName)
{
  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
    if(iEvent%10000==0) cout<<"Processing event "<<iEvent<<endl;
    if(iEvent >= config.params("maxEvents")) break;
    
    auto event = events->GetEvent(iEvent);
    
    // Add all necessary selection criteria here
    // ...
    
    if(!event->HasDoubleEG2Trigger()) continue;
    if(event->HasAdditionalTowers()) continue;
    if(event->GetNchargedTracks() != 0) continue;
    
    auto photons = event->GetGoodPhotons();
    
    if(photons.size() == 2){
      double aco = physObjectProcessor.GetAcoplanarity(*photons[0], *photons[1]);
      hists.at("acoplanarity"+datasetName)->Fill(aco);
    }
    
    int nTracks = event->GetNgeneralTracks();
    
    hists.at("nTracks"+datasetName)->Fill(nTracks);
    
    for(int iTrack=0; iTrack<nTracks; iTrack++){
      double trackPt = event->GetGeneralTrack(iTrack)->GetPt();
      
      hists.at("track_pt"+datasetName)->Fill(trackPt);
      
      
      int iBin = nTracks+1;
      if(trackPt < 0.1){
        hists.at("nTracks_pt_lt_100_MeV"+datasetName)->SetBinContent(iBin, hists.at("nTracks_pt_lt_100_MeV"+datasetName)->GetBinContent(iBin)+1);
      }
      else{
        hists.at("nTracks_pt_geq_100_MeV"+datasetName)->SetBinContent(iBin, hists.at("nTracks_pt_geq_100_MeV"+datasetName)->GetBinContent(iBin)+1);
      }
    }
  }
}

int main()
{
  config = ConfigManager(configPath);
  
  map<string, TH1D*> hists;
  
  TFile *outFile = new TFile(outputPath.c_str(), "recreate");
  
  for(auto dataset : datasetsToAnalyze){
    string title = datasetName.at(dataset);
    
    for(auto &[histName, nBins, min, max] : histParams){
      
      hists[histName+title] = new TH1D((histName+title).c_str(),
                                       (histName+title).c_str(), nBins, min, max);
    }
    
    cout<<"Creating "<<title<<" plots"<<endl;
    
    auto events = make_unique<EventProcessor>(inFileNames.at(dataset));
    fillHistograms(events, hists, title);
    
    outFile->cd();
    for(auto &[name, hist] : hists) hist->Write();
  }
  
  outFile->Close();
  
}
