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
#### here original was 0.0106, but we may need to make it more loose:
photonMaxEtaWidthBarrel:       0.0106
photonMaxEtaWidthEndcap:    0.0272

### Electron ID cuts:
electronMinPt:                            2.0
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
 
 ### Calorimeter noise thresolds (GeV)
noiseThresholdEB:        0.8
noiseThresholdEE:        3.7
noiseThresholdHB:        2.9
noiseThresholdHE:        2.5
noiseThresholdHFp:      7.3
noiseThresholdHFm:     7.6


### eta dependant EE noise thresholds (GeV)
doNoiseEEetaDependant:    1
noiseEEetaStep: 0.1
noiseEEetaMin: 1.5
noiseEEetaMax: 3.0

noiseThresholdEE_1.5:   9.61
noiseThresholdEE_1.6:   1.5
noiseThresholdEE_1.7:   1.2
noiseThresholdEE_1.8:   1.5
noiseThresholdEE_1.9:   1.5
noiseThresholdEE_2.0:   1.8
noiseThresholdEE_2.1:   2.11
noiseThresholdEE_2.2:   4.41
noiseThresholdEE_2.3:   7.91
noiseThresholdEE_2.4:   9.21
noiseThresholdEE_2.5:   9.71
noiseThresholdEE_2.6:   9.91
noiseThresholdEE_2.7:   10.01
noiseThresholdEE_2.8:   10.01
noiseThresholdEE_2.9:   10.01
noiseThresholdEE_3.0:   10.01
