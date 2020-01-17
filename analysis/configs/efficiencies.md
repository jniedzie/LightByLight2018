##  Efficiencies config

### Max number of events to analyze
maxEvents: 1000000000

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
#### here original was 0.0106, but we may need to make it more loose:
photonMaxEtaWidthBarrel:       0.0106
photonMaxEtaWidthEndcap:    0.0272

### Electron ID cuts:
electronMinPt:                            5.0
electronMaxEta:                         2.3
electronMaxNmissingHits:         1
electronMaxHoverE_Barrel:         0.005
electronMaxHoverE_Endcap:      0.005
electronMaxDetaSeedBarrel:      0.1
electronMaxDetaSeedEndcap:   0.1
electronMaxChargedIsoBarrel:    0.1
electronMaxChargedIsoEndcap: 0.1
electronMaxPhotonIsoBarrel:      0.035
electronMaxPhotonIsoEndcap:   0.035
electronMaxNeutralIsoBarrel:      0.07
electronMaxNeutralIsoEndcap:   0.07

### Exclude transition region between calo barrel and endcap
ecalCrackMin: 1.4442
ecalCrackMax: 1.566

### Exclude hole in ECal (HEM issue, only in negative part of EE)
ecalHEMmin:  -1.5
ecalHEMmax: -1.0
 
