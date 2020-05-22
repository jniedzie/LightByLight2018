# MC data at /eos/cms/store/group/phys_top/gkrintir/LbL/GammaGamma2MuMu_GENSIM_woPtCut_PbPb5TeV_v1/crab_GammaGamma2MuMu_GENSIM_woPtCut/200317_235208/0000/
# Real Data at /eos/cms/store/group/phys_diffraction/lbyl_2018/HIForward_Reco/ntuples/ntuples_data_tracker_branches/HIForward/ntuples_data_lbl_tracker_branches/200317_103751/0000/data_HiForestAOD_1-1.root


import sys


runfile = sys.argv[2]
config = "/afs/cern.ch/user/m/mnickel/private/LightByLight2018/analysis/configs/efficiencies.md"
input_file = sys.argv[1]
ending = input_file[(input_file.find("HiForestAOD") + len("HiForestAOD")):]

sig_mu = "/eos/user/m/mnickel/TauTau/data/data_sig_mu"
mu_ele = "/eos/user/m/mnickel/TauTau/data/data_mu_ele"
mu_mu = "/eos/user/m/mnickel/TauTau/data/data_mu_mu"

f = open(runfile,"a")
f.write( config + "\n")
f.write( input_file+ "\n")
f.write( sig_mu + ending+ "\n")
f.write( mu_ele + ending + "\n")
f.write( mu_mu + ending + "\n")
f.close()
