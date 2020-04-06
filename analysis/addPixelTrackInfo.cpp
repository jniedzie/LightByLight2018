//  addPixelTrackInfo.cpp
//
//  Created by Jeremi Niedziela on 03/04/2020.

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"

bool storeHLTtrees = false;

int main(int argc, char* argv[])
{
  if(argc != 5){
    cout<<"./addPixelTrackInfo inputPath secondaryInputPath outputPath datasetName[Data|QED_SC|QED_SL|LbL|CEP]"<<endl;
    exit(0);
  }
  
  cout<<"Starting addPixelTrackInfo"<<endl;
  
  string inFilePath = argv[1];
  string secondaryInputPath = argv[2];
  vector<string> outFilePaths = { argv[3] };
  string sampleName = argv[4];
  
  config = ConfigManager("configs/applySelections.md");
  cout<<"Config created"<<endl;
  
  EDataset dataset = nDatasets;
  if(sampleName == "Data")    dataset = kData;
  if(sampleName == "QED_SC")  dataset = kMCqedSC;
  if(sampleName == "QED_SL")  dataset = kMCqedSL;
  if(sampleName == "LbL")     dataset = kMClbl;
  if(sampleName == "CEP")     dataset = kMCcep;
  
  cout<<"Loading events...";
  auto events = make_unique<EventProcessor>(inFilePath, dataset, outFilePaths, secondaryInputPath);
  cout<<" done!"<<endl;
  
  // Loop over events
  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
    if(iEvent==config.params("maxEvents")) break;
    if(iEvent%1000 == 0) cout<<"Processing event "<<iEvent<<endl;

    events->AddEventToOutputTree(iEvent, outFilePaths[0], storeHLTtrees);
  }
  
  cout<<"Saving output trees"<<endl;
  for(string outFilePath : outFilePaths) events->SaveOutputTree(outFilePath);
  
  return 0;
}
