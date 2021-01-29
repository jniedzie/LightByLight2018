import FWCore.ParameterSet.Config as cms

import sys
args =sys.argv[1:]
if len(args) < 2: 
   dataOrMC = "Data"
else: 
      dataOrMC = args[1]
print("Will run on %s" % dataOrMC)

process = cms.Process("TagProbe")
process.load('FWCore.MessageService.MessageLogger_cfi')
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    
PDFName = "expoPlusBkg"
if dataOrMC == "MC":
   PDFName = "expo"


EFFICIENCYSET =cms.PSet(
        DoubleEG2_1bin = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("ok_trg2","true"),
            UnbinnedVariables = cms.vstring("pair_acop"),
            BinnedVariables = cms.PSet(
                pass_EG5    = cms.vstring("true"),
                ok_elematch = cms.vstring("true"),
                ok_ID = cms.vstring("true"),
                # L1Et = cms.vdouble(2, 20),
                SCEt = cms.vdouble(2, 20),
                # abseta = cms.vdouble(0, 2.4),
                SCeta = cms.vdouble(-2.4, 2.4),
                pair_mass = cms.vdouble(4.0, 100.0),
                pair_pt   = cms.vdouble(0.0, 2.0),

            ),
         BinToPDFmap = cms.vstring(PDFName)
        ),
        DoubleEG2_EBEE = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("ok_trg2","true"),
            UnbinnedVariables = cms.vstring("pair_acop"),
            BinnedVariables = cms.PSet(
                pass_EG5    = cms.vstring("true"),
                ok_elematch = cms.vstring("true"),
                ok_ID = cms.vstring("true"),
                SCEt = cms.vdouble(2, 20),
                # L1Et = cms.vdouble(2, 20),
                # abseta = cms.vdouble(0, 1.5, 2.4),
                SCeta = cms.vdouble(0, 1.5, 2.4),
                pair_mass = cms.vdouble(4.0, 100.0),
                pair_pt   = cms.vdouble(0.0, 2.0),

            ),
         BinToPDFmap = cms.vstring(PDFName)
        ),
        DoubleEG2_abseta = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("ok_trg2","true"),
            UnbinnedVariables = cms.vstring("pair_acop"),
            BinnedVariables = cms.PSet(
                pass_EG5    = cms.vstring("true"),
                ok_elematch = cms.vstring("true"),
                ok_ID  = cms.vstring("true"),
                SCEt = cms.vdouble(2, 20),
                # L1Et = cms.vdouble(2, 20),
                # abseta = cms.vdouble(0, 0.5, 1, 1.5, 2, 2.4),
                #eta = cms.vdouble(-2.4, -2, -1.5, -1, -0.5, 0, 0.5, 1, 1.5, 2, 2.4),
                SCeta = cms.vdouble(-2.4, -2.3,-2.2,-2.1,-2, -1.5, -1, -0.5, 0, 0.5, 1, 1.5, 2, 2.1, 2.2, 2.3, 2.4),
                pair_mass = cms.vdouble(4.0, 100.0),
                pair_pt   = cms.vdouble(0.0, 2.0),

            ),
         BinToPDFmap = cms.vstring(PDFName)
        ),
        DoubleEG2_pt0 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("ok_trg2","true"),
            UnbinnedVariables = cms.vstring("pair_acop"),
            BinnedVariables = cms.PSet(
                pass_EG5    = cms.vstring("true"),
                ok_elematch = cms.vstring("true"),
                ok_ID = cms.vstring("true"),
                SCEt = cms.vdouble(2, 3, 4, 5, 6, 7, 10, 14, 20),
                # L1Et = cms.vdouble(2, 3, 4, 5, 6, 7, 10, 14, 20),
                # abseta = cms.vdouble(0, 1.5),
                SCeta = cms.vdouble(-1.5, 1.5),
                pair_mass = cms.vdouble(4.0, 100.0),
                pair_pt   = cms.vdouble(0.0, 2.0),

            ),
         BinToPDFmap = cms.vstring(PDFName)
        ),
        DoubleEG2_pt1 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("ok_trg2","true"),
            UnbinnedVariables = cms.vstring("pair_acop"),
            BinnedVariables = cms.PSet(
                pass_EG5    = cms.vstring("true"),
                ok_elematch = cms.vstring("true"),
                ok_ID = cms.vstring("true"),
                SCEt = cms.vdouble(2, 3, 4, 5, 6, 7, 10, 14, 20),
                # L1Et = cms.vdouble(2, 3.5, 5, 7, 12, 20),
                # abseta = cms.vdouble(1.5, 2.4),
                SCeta = cms.vdouble(1.5, 2.4),
                pair_mass = cms.vdouble(4.0, 100.0),
                pair_pt   = cms.vdouble(0.0, 2.0),

            ),
         BinToPDFmap = cms.vstring(PDFName)
        )
)
if dataOrMC == "Data":
   #inputfiles = "file:/eos/cms/store/group/phys_diffraction/lbyl_2018/analysis_emilien/efficienciesQED/efficienciesQED_data_QED_tnpEC_20201028/efficienciesQED_all.root"
   #inputfiles = "file:/eos/cms/store/group/phys_diffraction/lbyl_2018/analysis_ruchi/efficienciesQED/efficienciesQED_data_eleRecoIDTrigger_tnpEC_20201208_SingleEG3orEG5/efficienciesQED_Data.root"
   #inputfiles = "file:/eos/cms/store/group/phys_diffraction/lbyl_2018/analysis_ruchi/efficienciesQED/efficienciesQED_data_eleRecoIDTrigger_tnpEC_20210118_SingleEG3orEG5_SCEtadded/efficienciesQED_Data.root"
   inputfiles = "file:/eos/cms/store/group/phys_diffraction/lbyl_2018/analysis_ruchi/efficienciesQED/efficienciesQED_data_eleRecoIDTrigger_tnpEC_20210121_SingleEG3orEG5_eta2p1/efficienciesQED_Data.root"

else:
   #inputfiles = "file:/eos/cms/store/group/phys_diffraction/lbyl_2018/analysis_ruchi/efficienciesQED/efficienciesQED_mc_qed_sc_QED_tnpEC_20201123/efficienciesQED_all.root"
   #inputfiles = "file:/eos/cms/store/group/phys_diffraction/lbyl_2018/analysis_ruchi/efficienciesQED/efficienciesQED_mc_qed_sc_eleRecoIDTrigger_tnpEC_20210118_SingleEG3orEG5_SCEtadded/efficienciesQED_MCSC.root" #superchic file
   #inputfiles = "file:/eos/cms/store/group/phys_diffraction/lbyl_2018/analysis_ruchi/efficienciesQED/efficienciesQED_mc_qed_sl_eleRecoIDTrigger_tnpEC_20210118_SingleEG3orEG5_SCEtadded/efficienciesQED_MCSL.root" #starlight file
   #inputfiles = "file:/eos/cms/store/group/phys_diffraction/lbyl_2018/analysis_ruchi/efficienciesQED/efficienciesQED_mc_qed_sc_eleRecoIDTrigger_tnpEC_20210121_SingleEG3orEG5_eta2p1/efficienciesQED_MCSC.root" #superchic eta 2.1 file
   inputfiles = "file:/eos/cms/store/group/phys_diffraction/lbyl_2018/analysis_ruchi/efficienciesQED/efficienciesQED_mc_qed_sl_eleRecoIDTrigger_tnpEC_20210121_SingleEG3orEG5_eta2p1/efficienciesQED_MCSL.root" #starlight eta 2.1 file


process.tagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    InputFileNames = cms.vstring(inputfiles),
    InputDirectoryName = cms.string("tnpQED"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("tnp_Ana_%s_trig_EG5_eta2p1.root" % ( dataOrMC)),
    #numbrer of CPUs to use for fitting
    NumCPU = cms.uint32(4),
    # specifies whether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    binnedFit = cms.bool(False),
    #binsForFit = cms.uint32(30),
    binsForMassPlots = cms.uint32(30),
    SaveWorkspace = cms.bool(False),
    
    # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
    Variables = cms.PSet(
                         pair_mass        = cms.vstring("diele Mass", "4.0", "100.0", "GeV/c^{2}"), 
                         pair_pt          = cms.vstring("diele Pt", "0", "20.0", "GeV/c"), 
                         pair_y           = cms.vstring("diele y", "-3", "3", ""), 
                         pair_acop        = cms.vstring("diele acop", "0", "0.06", ""), 
                         SCEt             = cms.vstring("Probe SC E_{T}", "0.0", "20", "GeV/c"),
                         SCeta            = cms.vstring("Probe SC #eta", "-2.4", "2.4", ""),
                         L1Et             = cms.vstring("Probe E_{T}", "0.0", "20", "GeV/c"),
                         L1Eta            = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
                         # abseta         = cms.vstring("Probe |#eta|", "0", "2.4", ""),
                         tag_pt           = cms.vstring("Tag p_{T}", "0", "20", "GeV/c^{2}"),
    ),
    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
    Categories = cms.PSet(
                        pass_EG5    = cms.vstring("pass_EG5", "dummy[true=1,false=0]"),
                        ok_trg2     = cms.vstring("ok_trg2", "dummy[true=1,false=0]"),
                        ok_elematch = cms.vstring("ok_elematch", "dummy[true=1,false=0]"),
                        ok_ID       = cms.vstring("ok_ID", "dummy[true=1,false=0]"),

    ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
        # Nominal
	    expoPlusBkg = cms.vstring(
		    "Exponential::signal(pair_acop, decaySig[-6.8e2,-1e4,-250])",
	    	"Exponential::backgroundPass(pair_acop, decayBkgPass[-80,-249,-10])",
          # "Exponential::backgroundFail(pair_acop, decayBkgFail[-1000,-1e4,-10])",
		    "Exponential::backgroundFail(pair_acop, decayBkgPass)",
	    	"efficiency[0.9,0.,1]",
		    "signalFractionInPassing[0.9]",
    	),    
        # Nominal
	    expo = cms.vstring(
		    "Exponential::signal(pair_acop, decaySig[-6.8e2,-1e4,0])",
	    	"Uniform::backgroundPass(pair_acop)",
	    	"Uniform::backgroundFail(pair_acop)",
	    	"efficiency[0.9,0.,1]",
		    "signalFractionInPassing[0.9]",
    	),    
    ),

    # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
    Efficiencies = EFFICIENCYSET 
)

process.fitness = cms.Path(
    process.tagProbeFitTreeAnalyzer
)
