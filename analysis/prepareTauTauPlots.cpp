//  prepareTauTauPlots.cpp
//  Created by Matthew Nickel on 21/05/2020.
// Based off of prepareBasicPlots.cpp created by Jeremi Niedziel

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"
#include "EventDisplay.hpp"
#include "Logger.hpp"

string configPath = "configs/preparePlots_default.md";
string outputPath = "results/basicPlots_test.root";

bool saveCalosFailingNEE = true;
bool saveTriphotonHists = true;
bool checkTriggers = false;

int nThreePhotonEvents = 0;


// Only those datasets will be analyzed
const vector<EDataset> datasetsToAnalyze = {
  kData,
};

vector<string> suffixes = {
  "all"
};

vector<tuple<string, int, double, double>> histParams = {
  // title                   nBins min   max
  {"dilepton_acoplanarity"       , 200 , 0   , 1.0   },
  {"lepton_pt"          , 100 , 0   , 100.0 },
  {"lepton_eta"         , 200   ,-2.4 , 2.4   },
  {"lepton_phi"         , 200   ,-4.0 , 4.0   },
  {"dilepton_mass"      , 2000  , 0   , 200.0 },
  {"dilepton_rapidity"  , 600   ,-2.4 , 2.4   },
  {"dilepton_pt"        , 500  , 0   , 10.0  },
  
  {"nTracks"                , 100 , 0   , 100   },
  {"track_pt"               , 5000, 0   , 100   },
  {"track_eta"              , 100 ,-3.5 , 3.5   },
  {"track_phi"              , 100 ,-3.5 , 3.5   },
  {"track_missing_hits"     , 50  , 0   , 50    },
  {"track_valid_hits"       , 50  , 0   , 50    },
  {"track_purity"           , 10  , 0   , 10    },
  {"track_charge"           , 4   ,-2   , 2     },
  {"track_chi2"             , 1000, 0   , 100   },
  {"track_dxy"              ,300000,-15  , 15    },
  {"track_dz"               ,100000,-50  , 50    },
  {"track_dxy_over_sigma"   , 1000, 0   , 100   },
  {"track_dz_over_sigma"    , 1000, 0   , 100   },
  
  {"track_dxy_from_bs"      ,300000,-15  , 15    },
  {"track_dz_from_bs"       ,100000,-50  , 50    },
  
  {"track_dxy_1_track"      ,300000,-15  , 15    },
  {"track_dxy_2_track"      ,300000,-15  , 15    },
  {"track_dxy_3_track"      ,300000,-15  , 15    },
  {"track_dxy_ge4_track"    ,300000,-15  , 15    },
  
  {"track_dz_1_track"       ,100000,-50  , 50    },
  {"track_dz_2_track"       ,100000,-50  , 50    },
  {"track_dz_3_track"       ,100000,-50  , 50    },
  {"track_dz_ge4_track"     ,100000,-50  , 50    },

  {"track_vx"               ,300000,-15  , 15    },
  {"track_vy"               ,300000,-15  , 15    },
  {"track_vz"               ,300000,-50  , 50    },
  
  
};

bool endsWith(const std::string &mainStr, const std::string &toMatch)
{
   if(mainStr.size() >= toMatch.size() &&
   mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
   return true;
   else
   return false;
}

void fillMuonHists(Event &event, const map<string, TH1D*> &hists, string datasetName, string suffix="")
{
  for(auto muon : event.GetPhysObjects(kMuon)){
    hists.at("lepton_pt_" +suffix+datasetName)->Fill(muon->GetPt());
    hists.at("lepton_eta_"+suffix+datasetName)->Fill(muon->GetEta());
    hists.at("lepton_phi_"+suffix+datasetName)->Fill(muon->GetPhi());
  }
}

void fillDimuonHists(Event &event, const map<string, TH1D*> &hists, string datasetName, string suffix="")
{
  
  TLorentzVector dimuon = physObjectProcessor.GetDimuon(*event.GetPhysObjects(kMuon)[0],
                                                                *event.GetPhysObjects(kMuon)[1]);
  
  hists.at("dilepton_mass_"     +suffix+datasetName)->Fill(dimuon.M());
  hists.at("dilepton_rapidity_" +suffix+datasetName)->Fill(dimuon.Rapidity());
  hists.at("dilepton_pt_"       +suffix+datasetName)->Fill(dimuon.Pt());
  
}


void fillTracksHists(Event &event, const map<string, TH1D*> &hists, EDataset dataset, string suffix="")
{
  string name = datasetName.at(dataset);
  
  int nTracks = (int)event.GetPhysObjects(kGeneralTrack).size();
  
  hists.at("nTracks_"+suffix+name)->Fill(nTracks);
  
  
  for(auto track : event.GetPhysObjects(kGeneralTrack)){
    double trackPt = track->GetPt();
    hists.at("track_pt_"+suffix+name)->Fill(trackPt);
    hists.at("track_eta_"+suffix+name)->Fill(track->GetEta());
    hists.at("track_phi_"+suffix+name)->Fill(track->GetPhi());
    
    hists.at("track_missing_hits_"  + suffix + name)->Fill(track->GetNmissingHits());
    hists.at("track_valid_hits_"    + suffix + name)->Fill(track->GetNvalidHits());
    hists.at("track_purity_"        + suffix + name)->Fill(track->GetPurity());
    hists.at("track_charge_"        + suffix + name)->Fill(track->GetCharge());
    hists.at("track_chi2_"          + suffix + name)->Fill(track->GetChi2());
    hists.at("track_dxy_"           + suffix + name)->Fill(track->GetDxy());
    
    hists.at("track_dxy_from_bs_"   + suffix + name)->Fill(track->GetXYdistanceFromBeamSpot(dataset));
    hists.at("track_dz_from_bs_"    + suffix + name)->Fill(track->GetZdistanceFromBeamSpot(dataset));
    
    if(nTracks==1){
      hists.at("track_dxy_1_track_" + suffix + name)->Fill(track->GetDxy());
      hists.at("track_dz_1_track_"  + suffix + name)->Fill(track->GetDz());
    }
    if(nTracks==2){
      hists.at("track_dxy_2_track_" + suffix + name)->Fill(track->GetDxy());
      hists.at("track_dz_2_track_"  + suffix + name)->Fill(track->GetDz());
    }
    if(nTracks==3){
      hists.at("track_dxy_3_track_" + suffix + name)->Fill(track->GetDxy());
      hists.at("track_dz_3_track_"  + suffix + name)->Fill(track->GetDz());
    }
    if(nTracks>=4){
      hists.at("track_dxy_ge4_track_" + suffix + name)->Fill(track->GetDxy());
      hists.at("track_dz_ge4_track_"  + suffix + name)->Fill(track->GetDz());
    }
    
    hists.at("track_dz_"            + suffix + name)->Fill(track->GetDz());
    hists.at("track_dxy_over_sigma_"+ suffix + name)->Fill(fabs(track->GetDxy()/track->GetDxyErr()));
    hists.at("track_dz_over_sigma_" + suffix + name)->Fill(fabs(track->GetDz()/track->GetDzErr()));
    hists.at("track_vx_"            + suffix + name)->Fill(track->GetVertexX());
    hists.at("track_vy_"            + suffix + name)->Fill(track->GetVertexY());
    hists.at("track_vz_"            + suffix + name)->Fill(track->GetVertexZ());
  }
  
}

void fillTauTauHistograms(Event &event, const map<string, TH1D*> &hists, EDataset dataset, vector<string> suffix_list)
{
  string name = datasetName.at(dataset);
  int cutThrough=0;
  
  double aco = physObjectProcessor.GetAcoplanarity(*event.GetPhysObjects(kMuon)[0],
                                                   *event.GetPhysObjects(kMuon)[1]);
  for(string suffix : suffix_list){
  if(suffix != "") suffix += "_";  
  hists.at("dilepton_acoplanarity_"+suffix+name)->Fill(aco);
  fillMuonHists(  event, hists, name, suffix);
  fillDimuonHists(event, hists, name, suffix);
  fillTracksHists(    event, hists, dataset, suffix);
  }
}

/// Creates histograms, cut through and event counters for given dataset name, for each
/// histogram specified in `histParams` vector.
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
  if(argc != 1 && argc != 5){
    cout<<"This app requires 0 or 4 parameters.\n";
    cout<<"./prepareBasicPlots configPath inputPath outputPath datasetName[Data|QED_SC|QED_SL|LbL|CEP]\n";
    exit(0);
  }

  string inputPath = "";
  string sampleName = "";
 
  if(argc == 5){
    configPath = argv[1];
    inputPath  = argv[2];
    outputPath = argv[3];
    sampleName = argv[4];
  }

  config = ConfigManager(configPath);

  map<string, TH1D*> hists;
  TFile *outFile = new TFile(outputPath.c_str(), "recreate");
  
  
  if(inputPath==""){
    for(auto dataset : datasetsToAnalyze){
      for(string suffix : suffixes){
        InitializeHistograms(hists, datasetName.at(dataset), suffix);
      }
    }
    

    for(auto dataset : datasetsToAnalyze){
      string name = datasetName.at(dataset);
      
      Log(0)<<"Creating "<<name<<" plots\n";


      auto events = make_unique<EventProcessor>(inFileNames.at(dataset), dataset);

      for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
        if(iEvent%1000 == 0)  Log(1)<<"Processing event "<<iEvent<<"\n";
        if(iEvent%10000 == 0) Log(0)<<"Processing event "<<iEvent<<"\n";
        if(iEvent >= config.params("maxEvents")) break;
        
        auto event = events->GetEvent(iEvent);


        
 
        fillTauTauHistograms(*event, hists, dataset, suffixes);
      }
      
      outFile->cd();
      for(auto &[histName, hist] : hists){
        if(histName.find(name) != string::npos) hist->Write();
      }
    }
  }

  else{
    if (endsWith(inputPath, "root")){
		cout << "root file" << endl;
		EDataset dataset = nDatasets;
		   
		if(sampleName == "Data")    dataset = kData;
		if(sampleName == "QED_SC")  dataset = kMCqedSC;
		if(sampleName == "QED_SL")  dataset = kMCqedSL;
		if(sampleName == "LbL")     dataset = kMClbl;
		if(sampleName == "CEP")     dataset = kMCcep;
		   
		auto events = make_unique<EventProcessor>(inputPath, dataset);

		for(string suffix : suffixes){
		  InitializeHistograms(hists, sampleName, suffix);
		}
		

		if(dataset == nDatasets){
		  Log(0)<<"ERROR -- unknown dataset name provided: "<<sampleName<<"\n";
		  exit(0);
		}
		
		for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
		  if(iEvent%1000 == 0)  Log(1)<<"Processing event "<<iEvent<<"\n";
		  if(iEvent%10000 == 0) Log(0)<<"Processing event "<<iEvent<<"\n";
		  if(iEvent >= config.params("maxEvents")) break;
		  
		  auto event = events->GetEvent(iEvent);
		  
		  fillTauTauHistograms(*event, hists, dataset, suffixes);
		}
	}
    if (endsWith(inputPath, "txt")){
		cout << "txt file" << endl;
		EDataset dataset = nDatasets;
		   
		if(sampleName == "Data")    dataset = kData;
		if(sampleName == "QED_SC")  dataset = kMCqedSC;
		if(sampleName == "QED_SL")  dataset = kMCqedSL;
		if(sampleName == "LbL")     dataset = kMClbl;
		if(sampleName == "CEP")     dataset = kMCcep;
		ifstream file(inputPath);
		string inputFile;
		while(getline(file, inputFile)){
			auto events = make_unique<EventProcessor>(inputFile, dataset);

			for(string suffix : suffixes){
			  InitializeHistograms(hists, sampleName, suffix);
			}
			

			if(dataset == nDatasets){
			  Log(0)<<"ERROR -- unknown dataset name provided: "<<sampleName<<"\n";
			  exit(0);
			}
			
			for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
			  if(iEvent%1000 == 0)  Log(1)<<"Processing event "<<iEvent<<"\n";
			  if(iEvent%10000 == 0) Log(0)<<"Processing event "<<iEvent<<"\n";
			  if(iEvent >= config.params("maxEvents")) break;
			  
			  auto event = events->GetEvent(iEvent);
			  
			  // run this here just to save electron cut flow hist
			  fillTauTauHistograms(*event, hists, dataset, suffixes);
			}
		}
	}
	if (!(endsWith(inputPath, "txt")) && !(endsWith(inputPath, "root"))){
		cout << "not valid input file" << endl;
		exit(0);
		}
	
    cout << "Writing Histograms" <<endl;
    outFile->cd();
    for(auto &[histName, hist] : hists) hist->Write();
  }

  outFile->Close();
  cout << "Finished" << endl;
}

