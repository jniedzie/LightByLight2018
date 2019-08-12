##  Efficiencies config

### Max number of events to analyze
maxEvents: 99999999999

### Criteria to match calo tower with photon SC for neutral exclusivity
maxDeltaEtaEB:  0.15
maxDeltaPhiEB:  0.7
maxDeltaEtaEE:  0.15
maxDeltaPhiEE:  0.4

### Don't look at towers that are in very noisy region of EE
maxEtaEEtower:      2.3

### Charged exclusivity cuts (GeV)
trackMinPt:              0.1 
diphotonMaxPt:      1.0 

### Max ΔR for matching for reco+ID efficiency
maxDeltaR:              0.3

### Photon ID cuts:
photonMinEt:                            2.0
photonMaxEta:                         2.3
photonMaxHoverEbarrel:          0.04596
photonMaxHoverEendcap:       0.0590
photonMaxEtaWidthBarrel:       0.0106
photonMaxEtaWidthEndcap:    0.0272

### Electron ID cuts:
electronMinPt:                            2.0
electronMaxEta:                         2.3
electronMaxNmissingHits:         1
electronMaxHoverEbarrel:          0.02
electronMaxHoverEendcap:       0.02
electronMaxDetaSeedBarrel:      0.03
electronMaxDetaSeedEndcap:   0.03

### Exclude transition region between calo barrel and endcap
ecalCrackMin: 1.4442
ecalCrackMax: 1.566

### Exclude hole in ECal (HEM issue, only in negative part of EE)
ecalHEMmin:  -1.5
ecalHEMmax: -1.0
 
