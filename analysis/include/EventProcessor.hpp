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
  /// \param outputPath Path to the output file (in case one wants to save selected events to a new tree)
  EventProcessor(string inputPath, string outputPath="");
  
  /// Default destructor
  ~EventProcessor();

  void AddEventToOutputTree(int iEvent);
  void SaveOutputTree();
  
  /// Returns number of events
  inline long long GetNevents() const { return eventTree->GetEntries(); }
  
  /// Returns Event object for given tree entry index
  shared_ptr<Event> GetEvent(int iEvent);
  
private:
  TTree *eventTree, *hltTree, *l1Tree;          ///< Input trees
  TTree *outEventTree, *outHltTree, *outL1Tree; ///< Output trees
  TDirectory *dirEvent, *dirHLT, *dirL1;        ///< Output directories
  TFile *outFile;                               ///< Output file
  
  shared_ptr<Event> currentEvent; ///< Pointer to the current event
  
  // Handles to variables stored in ntuple trees
  vector<int>    triggersLbL;
  
  vector<float> *mcEta              = nullptr;
  vector<float> *mcPhi              = nullptr;
  vector<float> *mcEt               = nullptr;
  vector<float> *mcE                = nullptr;
  vector<float> *mcPID              = nullptr;
  
  vector<float> *photonHoverE       = nullptr;
  vector<float> *photonSCEta        = nullptr;
  vector<float> *photonSCPhi        = nullptr;
  vector<float> *photonSCEt         = nullptr;
  vector<float> *photonSCE          = nullptr;
  vector<float> *photonSCEtaWidth   = nullptr;
  vector<float> *photonSCPhiWidth   = nullptr;
  
  vector<float> *towerEta           = nullptr;
  vector<float> *towerPhi           = nullptr;
  vector<float> *towerEnergy        = nullptr;
  vector<float> *towerEt            = nullptr;
  vector<float> *towerEnergyHad     = nullptr;
  vector<float> *towerEnergyEm      = nullptr;
  
  vector<int>   *generalTrackCharge = nullptr;
  vector<float> *generalTrackPt     = nullptr;
  vector<float> *generalTrackEta    = nullptr;
  vector<float> *generalTrackPhi    = nullptr;
  
  vector<int>   *electronCharge       = nullptr;
  vector<int>   *electronNmissing     = nullptr;
  vector<float> *electronPt           = nullptr;
  vector<float> *electronEta          = nullptr;
  vector<float> *electronPhi          = nullptr;
  vector<float> *electronHoverE       = nullptr;
  vector<float> *electronRelIsoWithEA = nullptr;
  vector<float> *electronDetaSeed     = nullptr;
  vector<float> *electronSCEta        = nullptr;
  vector<float> *electronSCEt         = nullptr;
  vector<float> *electronSCPhi        = nullptr;
  vector<float> *electronSCEn         = nullptr;
  vector<float> *electronChIso        = nullptr;
  vector<float> *electronPhoIso       = nullptr;
  vector<float> *electronNeuIso       = nullptr;

  vector<float> *L1EGeta              = nullptr;
  vector<float> *L1EGphi              = nullptr;
  vector<float> *L1EGet               = nullptr;
  
  /// Opens input trees and sets branches
  void SetupBranches(string inputPath, string outputPath);
  
  /// Creates output file and copies intput trees to it (without copying the entries)
  void SetupOutputTree(string outFileName);
};

#endif /* EventProcessor_hpp */
