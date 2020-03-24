import sys


runfile = sys.argv[2]
ending = sys.argv[1] + ".root"
config = "/afs/cern.ch/user/m/mnickel/private/LightByLight2018/analysis/configs/efficiencies.md"
input_file = "/eos/cms/store/group/phys_heavyions/rchudasa/lbyl_2018/data_ntuples/HIForward/ntuples_data_new/200105_192027/0000/data_HiForestAOD_1-"

sig_mu = "/eos/user/m/mnickel/TauTau/data/data_sig_mu_1-"
mu_ele = "/eos/user/m/mnickel/TauTau/data/data_mu_ele_1-"
mu_mu = "/eos/user/m/mnickel/TauTau/data/data_mu_mu_1-"

f = open(runfile,"a")
f.write( config + "\n")
f.write( input_file+ ending + "\n")
f.write( sig_mu + ending+ "\n")
f.write( mu_ele + ending + "\n")
f.write( mu_mu + ending + "\n")
f.close()
