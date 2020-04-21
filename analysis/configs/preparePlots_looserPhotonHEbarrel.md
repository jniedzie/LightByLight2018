##  Efficiencies config

### Verbosity level (0: critical errors only, 1: errors and warnings, 2: full debug log):
verbosityLevel: 0

### Max number of events to analyze
maxEvents: 9999999

### Criteria to match calo tower with photon SC for neutral exclusivity
maxDeltaEtaEB:  0.15
maxDeltaPhiEB:  0.7
maxDeltaEtaEE:  0.15
maxDeltaPhiEE:  0.4

### Don't look at towers that are in very noisy region of EE
maxEtaEEtower:      2.4

### Charged exclusivity cuts (GeV)
maxNtracks:                             0
trackMinPt:                               0.5 
trackMaxEta:                            2.4
trackMaxDxy:                           999999
trackMaxXYdistanceFromBS:  999999
trackMaxDxyOverSigma:         999999
trackMaxDz:                             999999
trackMaxZdistanceFromBS:    999999
trackMaxDzOverSigma:           999999
trackMinNvalidHits:                  3
trackMaxChi2:                          999999

### Pixel cuts
maxNpixelRecHits:                  999999

### Pixel track cuts
maxNpixelTracks:                    0
pixelTrackMinPt:                      0.05
pixelTrackMaxEta:                   2.4
pixelTrackMinNvalidHits:         3
pixelTrackMaxChi2:                 999999

### ZDC cuts
maxZDCenergy:                       999999
maxTotalZDCenergy:                999999

### Max ΔR for matching for reco+ID efficiency
maxDeltaR:              0.3

### Photon ID cuts:
photonMinEt:                            2.0
photonMaxEta:                         2.4
photonMaxHoverEbarrel:          0.1
photonMaxHoverEendcap:       0.0590
photonMaxEtaWidthBarrel:       0.0106
photonMaxEtaWidthEndcap:    0.0272
photonMinSwissCross:             0.005
diphotonMaxPt:                        1.0
diphotonMaxRapidity:               9999999
diphotonMinMass:                    5.0
diphotonMaxAco:                     0.01
photonRejectConverted:           1

### Electron ID cuts:
electronMinPt:                            2.0
electronMaxEta:                         2.4
electronMaxNmissingHits:         1
electronMaxHoverE_Barrel:         0.005
electronMaxHoverE_Endcap:      0.005
electronMaxDetaSeedBarrel:      0.1
electronMaxDetaSeedEndcap:   0.1
electronMaxChargedIsoBarrel:    0.1
electronMaxChargedIsoEndcap: 0.1
electronMaxPhotonIsoBarrel:      0.3
electronMaxPhotonIsoEndcap:   0.3
electronMaxNeutralIsoBarrel:      0.07
electronMaxNeutralIsoEndcap:   0.07
dielectronMaxPt:                        1.0
dielectronMinMass:                    5.0
dielectronMaxRapidity:               2.4

### Exclude transition region between calo barrel and endcap
ecalCrackMin: 1.4442
ecalCrackMax: 1.566

### Exclude hole in ECal (HEM issue, only in negative part of EE)
ecalHEMmin:  -1.5
ecalHEMmax: -1.0
 
### Calorimeter noise thresolds (GeV)
noiseThresholdEB:        2.0
noiseThresholdEE:        7.6
noiseThresholdHB:        2.8
noiseThresholdHE:        2.4
noiseThresholdHFp:      12.0
noiseThresholdHFm:     12.0


### eta dependant EE noise thresholds (GeV)
doNoiseEEetaDependant:    0
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
