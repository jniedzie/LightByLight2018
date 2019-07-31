//  prepareAcoplanarityPlots.cpp
//
//  Created by Jeremi Niedziela on 31/07/2019.

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"

string configPath = "configs/efficiencies.md";

vector<tuple<string, EDataset>> dataTypes = {
  { "Data"  , kData     },
  { "LbL"   , kMClbl    },
  { "QED"   , kMCqedSC  },
  { "CEP"   , kMCcep    },
};

vector<tuple<string, int, double, double>> histParams = {
  // title                     nBins min   max
  {"acoplanarity"             , 200 , 0   , 1.0 },
};

void fillHistograms(const unique_ptr<EventProcessor> &events,
                    const map<string, TH1D*> &hists,
                    string datasetName)
{
  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
    if(iEvent%10000==0) cout<<"Processing event "<<iEvent<<endl;
    if(iEvent >= config.params["maxEvents"]) break;
    
    // Add all necessary selection criteria here
    // ...
    
    auto event = events->GetEvent(iEvent);
    auto photons = event->GetGoodPhotonSCs();
    
    if(photons.size() != 2) continue;

    hists.at("acoplanarity"+datasetName)->Fill(physObjectProcessor.GetAcoplanarity(*photons[0], *photons[1]));
  }
}

int main()
{
  config = ConfigManager(configPath);
  
  map<string, TH1D*> hists;
  
  TFile *outFile = new TFile("results/acoplanarity.root", "recreate");
  
  for(auto &[datasetName, datasetEnum] : dataTypes){
    for(auto &[histName, nBins, min, max] : histParams){
      hists[histName+datasetName] = new TH1D((histName+datasetName).c_str(), (histName+datasetName).c_str(), nBins, min, max);
    }
    
    cout<<"Creating "<<datasetName<<" plots"<<endl;
    
    unique_ptr<EventProcessor> events(new EventProcessor(datasetEnum));
    fillHistograms(events, hists, datasetName);
    
    outFile->cd();
    for(auto &[name, hist] : hists) hist->Write();
  }
  
  outFile->Close();
  
}
