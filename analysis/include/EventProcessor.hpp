//  EventProcessor.hpp
//
//  Created by Jeremi Niedziela on 22/07/2019.

#ifndef EventProcessor_hpp
#define EventProcessor_hpp

#include "Helpers.hpp"
#include "Event.hpp"

/// This class keeps a link to input ROOT trees and creates Event class objects when moving
/// to next event.
class EventProcessor {
public:
  /// Default constructor.
  /// \param inputPath Path to the file
  /// \param outputPaths Paths to the output files, in case one wants to save selected events to a new tree(s)
  EventProcessor(string inputPath, vector<string> outputPaths = {});
  
  /// Default destructor
  ~EventProcessor();

  /// Add event with number iEvent to output tree in file outFileName
  void AddEventToOutputTree(int iEvent, string outFileName, bool saveHLTtree=true);
  
  /// Save file with name outFileName
  void SaveOutputTree(string outFileName);
  
  /// Returns number of events
  inline long long GetNevents() const { return eventTree->GetEntries(); }
  
  /// Returns Event object for given tree entry index
  shared_ptr<Event> GetEvent(int iEvent);
  
private:
  TTree *eventTree, *hltTree, *l1Tree;                      ///< Input trees
  map<string, TTree*> outEventTree, outHltTree, outL1Tree;  ///< Output trees
  map<string, TDirectory*> dirEvent, dirHLT, dirL1;         ///< Output directories
  map<string, TFile*> outFile;                              ///< Output files
  
  shared_ptr<Event> currentEvent; ///< Pointer to the current event
  
  // Handles to variables stored in ntuple trees
  vector<int>    triggersLbL;
  
  vector<float> *mcEta                  = nullptr;
  vector<float> *mcPhi                  = nullptr;
  vector<float> *mcEt                   = nullptr;
  vector<float> *mcE                    = nullptr;
  vector<float> *mcPID                  = nullptr;
  
  vector<float> *photonHoverE           = nullptr;
  vector<float> *photonSCEta            = nullptr;
  vector<float> *photonSCPhi            = nullptr;
  vector<float> *photonSCEt             = nullptr;
  vector<float> *photonSCE              = nullptr;
  vector<float> *photonSCEtaWidth       = nullptr;
  vector<float> *photonSCPhiWidth       = nullptr;
  
  vector<float> *photonEmax             = nullptr;
  vector<float> *photonEtop             = nullptr;
  vector<float> *photonEbottom          = nullptr;
  vector<float> *photonEleft            = nullptr;
  vector<float> *photonEright           = nullptr;
  vector<bool>  *photonIsConverted      = nullptr;
  
  vector<float> *towerEta               = nullptr;
  vector<float> *towerPhi               = nullptr;
  vector<float> *towerEnergy            = nullptr;
  vector<float> *towerEt                = nullptr;
  vector<float> *towerEnergyHad         = nullptr;
  vector<float> *towerEnergyEm          = nullptr;
  
  vector<int>   *generalTrackCharge     = nullptr;
  vector<float> *generalTrackPt         = nullptr;
  vector<float> *generalTrackEta        = nullptr;
  vector<float> *generalTrackPhi        = nullptr;
  vector<int>   *generalTrackValidHits  = nullptr;
  vector<int>   *generalTrackMissingHits= nullptr;
  vector<int>   *generalTrackPurity     = nullptr;
  vector<float> *generalTrackChi2       = nullptr;
  vector<float> *generalTrackDxy        = nullptr;
  vector<float> *generalTrackDz         = nullptr;
  vector<float> *generalTrackDxyErr     = nullptr;
  vector<float> *generalTrackDzErr      = nullptr;
  vector<float> *generalTrackVertexX    = nullptr;
  vector<float> *generalTrackVertexY    = nullptr;
  vector<float> *generalTrackVertexZ    = nullptr;
  
  vector<int>   *electronCharge         = nullptr;
  vector<int>   *electronNmissing       = nullptr;
  vector<float> *electronPt             = nullptr;
  vector<float> *electronEta            = nullptr;
  vector<float> *electronPhi            = nullptr;
  vector<float> *electronHoverE         = nullptr;
  vector<float> *electronRelIsoWithEA   = nullptr;
  vector<float> *electronDetaSeed       = nullptr;
  vector<float> *electronSCEta          = nullptr;
  vector<float> *electronSCEt           = nullptr;
  vector<float> *electronSCPhi          = nullptr;
  vector<float> *electronSCEn           = nullptr;
  vector<float> *electronChIso          = nullptr;
  vector<float> *electronPhoIso         = nullptr;
  vector<float> *electronNeuIso         = nullptr;


  vector<int>   *muonCharge         = nullptr;
//  vector<int>   *muonNmissing       = nullptr;
  vector<float> *muonPt             = nullptr;
  vector<float> *muonEta            = nullptr;
  vector<float> *muonPhi            = nullptr;
//  vector<float> *muonHoverE         = nullptr;
//  vector<float> *muonRelIsoWithEA   = nullptr;
//  vector<float> *muonDetaSeed       = nullptr;
//  vector<float> *muonSCEta          = nullptr;
//  vector<float> *muonSCEt           = nullptr;
//  vector<float> *muonSCPhi          = nullptr;
//  vector<float> *muonSCEn           = nullptr;
  vector<float> *muonChIso          = nullptr;
  vector<float> *muonPhoIso         = nullptr;
  vector<float> *muonNeuIso         = nullptr;

  vector<float> *L1EGeta                = nullptr;
  vector<float> *L1EGphi                = nullptr;
  vector<float> *L1EGet                 = nullptr;
  
  map<EPhysObjType, int> nPhysObjects;     ///< Stores number of physics objects
  unsigned short int nL1EGs;
  
  
  /// Opens input trees and sets branches
  void SetupBranches(string inputPath, vector<string> outputPaths);
  
  /// Creates output file and copies intput trees to it (without copying the entries)
  void SetupOutputTree(string outFileName);
};

#endif /* EventProcessor_hpp */
