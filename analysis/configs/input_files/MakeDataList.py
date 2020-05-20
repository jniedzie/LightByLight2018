
f = open("TauTau_Input_List.txt","a")

for i in [1,2]:
	for j in range(1,501):
		f.write("/eos/cms/store/group/phys_diffraction/lbyl_2018/HIForward_Reco/ntuples/ntuples_data_tracker_branches/HIForward/ntuples_data_lbl_tracker_branches/200317_103751/000{}/data_HiForestAOD_{}-{}.root\n".format(j/1000, i,j))

f.close()
