##  Efficiencies config

### Max number of events to analyze
maxEvents: 100000

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
photonMaxHoverE:                   0.04
photonMaxEtaWidthBarrel:       0.02
photonMaxEtaWidthEndcap:    0.06

### Exclude transition region between calo barrel and endcap
ecalCrackMin: 1.4442
ecalCrackMax: 1.566
 
