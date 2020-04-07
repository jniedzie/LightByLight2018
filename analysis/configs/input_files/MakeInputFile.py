import sys


runfile = sys.argv[2]
config = "/afs/cern.ch/user/m/mnickel/private/LightByLight2018/analysis/configs/efficiencies.md"
input_file = sys.argv[1]
ending = input_file[180:]

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
