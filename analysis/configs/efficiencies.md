##  Efficiencies config

### Max number of events to analyze
maxEvents: 100000

### Eta cut for gen particles and photon superclusters for MC efficiency estimation
maxEta: 2.4

### Et (GeV) cut for gen particles and photon superclusters for MC efficiency estimation
minEt: 2 

### Criteria to reject photons coming from e.g. pi0 decays (by shower shape)
maxEtaWidthBarrel:  0.02
maxEtaWidthEndcap:  0.06

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

 
