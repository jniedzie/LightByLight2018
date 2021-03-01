import FWCore.ParameterSet.Config as cms

import sys
args =sys.argv[1:]
if len(args) < 2: 
   dataOrMC = "Data"
else: 
      dataOrMC = args[1]
print "Will run on ", dataOrMC

process = cms.Process("TagProbe")
process.load('FWCore.MessageService.MessageLogger_cfi')
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    
PDFName = "nompdf"

EFFICIENCYSET =cms.PSet(
        phoreco_1bin = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("nPho_notag","true","ok_ID","true"),
            UnbinnedVariables = cms.vstring("probetkAco"),
            BinnedVariables = cms.PSet(
                pass_EG5 = cms.vstring("true"),
                probetkMinDpt = cms.vdouble(2, 20),
                probetkEta = cms.vdouble(-2.1, 2.1),
            ),
         BinToPDFmap = cms.vstring(PDFName)
        ),
        phoreco_EBEE = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("nPho_notag","true","ok_ID","true"),
            UnbinnedVariables = cms.vstring("probetkAco"),
            BinnedVariables = cms.PSet(
                pass_EG5 = cms.vstring("true"),
                probetkMinDpt = cms.vdouble(2, 20),
                probetkEta = cms.vdouble(0, 1.5, 2.1),
            ),
         BinToPDFmap = cms.vstring(PDFName)
        ),
        phoreco_abseta = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("nPho_notag","true","ok_ID","true"),
            UnbinnedVariables = cms.vstring("probetkAco"),
            BinnedVariables = cms.PSet(
                pass_EG5 = cms.vstring("true"),
                probetkMinDpt = cms.vdouble(2, 20),
                probetkEta = cms.vdouble(-2.4, -2.3, -2.2, -2.1, -2, -1.5, -1, -0.5, 0, 0.5, 1, 1.5, 2, 2.1, 2.2, 2.3, 2.4),
            ),
         BinToPDFmap = cms.vstring(PDFName)
        ),
        phoreco_pt0 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("nPho_notag","true","ok_ID","true"),
            UnbinnedVariables = cms.vstring("probetkAco"),
            BinnedVariables = cms.PSet(
                pass_EG5 = cms.vstring("true"),
                probetkMinDpt = cms.vdouble(2, 4, 6, 8, 20),
                probetkEta = cms.vdouble(-1.5, 1.5),
            ),
         BinToPDFmap = cms.vstring(PDFName)
        ),
        phoreco_pt1 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("nPho_notag","true","ok_ID","true"),
            UnbinnedVariables = cms.vstring("probetkAco"),
            BinnedVariables = cms.PSet(
                pass_EG5 = cms.vstring("true"),
                probetkMinDpt = cms.vdouble(2, 4, 6, 8, 20),
                probetkEta = cms.vdouble(1.5, 2.1),
            ),
         BinToPDFmap = cms.vstring(PDFName)
        )
)

if dataOrMC == "Data":
   inputfiles = "file:/eos/cms/store/group/phys_diffraction/lbyl_2018/analysis_ruchi/efficienciesQED/photonEfficienciesQED_data_deta_dphi_cuts_20210219/DataAll_deta_dphi_cuts.root"
else:
   inputfiles = "file:/eos/cms/store/group/phys_diffraction/lbyl_2018/analysis_ruchi/efficienciesQED/photonEfficienciesQED_mc_qed_sc_deta_dphi_cuts_20210219/QED_SC_efficiency_all_deta_dphi_cuts.root" #starlight eta 2.1 file


process.tagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    InputFileNames = cms.vstring(inputfiles),
    InputDirectoryName = cms.string("tnpQED"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("tnp_Ana_%s_photonRecoID_EG5.root" % ( dataOrMC)),
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
                         probetkAco       = cms.vstring("Probe-tag aco", "0.0", "0.5", ""),
                         probetkPt        = cms.vstring("Probe p_{T}", "0.0", "2", "GeV/c"),
                         probetkMinDpt    = cms.vstring("p_{T}^{e} - p_{T}^{tk}", "2.0", "20", "GeV/c"),
                         probetkEta       = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
                         phoSCEt_notag    = cms.vstring("Photon Et", "-1000", "20", "GeV/c")
    ),
    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
    Categories = cms.PSet(
                        nPho_notag    = cms.vstring("nPho_notag", "dummy[true=1,false=0]"),
                        ok_photon     = cms.vstring("ok_photon", "dummy[true=1,false=0]"),
                        ok_ID         = cms.vstring("ok_ID", "dummy[true=1,false=0]"),
                        ok_probeTrk   = cms.vstring("ok_probeTrk", "dummy[true=1,false=0]"),
                        pass_EG5      = cms.vstring("pass_EG5", "dummy[true=1,false=0]"),

    ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
        # Nominal
	    nompdf = cms.vstring(
          "EXPR::signal('1./pow(probetkAco-asig,2)',{probetkAco, asig[-3.3e-2]})",#,-8e-2,-2e-2]})",
	    	"Exponential::backgroundFail(probetkAco, decayBkgF[-4.6,-2,-6])",
          # "Exponential::backgroundFail(diAcop, decayBkgFail[-1000,-1e4,-10])",
          "Exponential::backgroundPass(probetkAco, decayBkgP[-4.6,-2,-6])",
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
