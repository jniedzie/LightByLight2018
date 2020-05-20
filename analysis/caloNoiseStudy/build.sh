source /cvmfs/sft.cern.ch/lcg/releases/LCG_94/gcc/8.2.0/x86_64-slc6/setup.sh

g++ getCaloNoiseHistograms.cpp -o getCaloNoiseHistograms `root-config --libs` `root-config --cflags`
