import FWCore.ParameterSet.Config as cms

import sys
args =sys.argv[1:]
if len(args) < 2:
  dataOrMC = "Data" # Data, QED_SC, QED_SL
else:
  dataOrMC = args[1]
print "Will run on ", dataOrMC

process = cms.Process("TagProbe")
process.load('FWCore.MessageService.MessageLogger_cfi')
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    
PDFName = "expoPlusBkg"
if (dataOrMC == "QED_SC") or (dataOrMC == "QED_SL"):
   PDFName = "expo"

print("Setting efficiency sets")

EFFICIENCYSET =cms.PSet(
        eff = cms.PSet(
#            EfficiencyCategoryAndState = cms.vstring("doubleEG2","true","matched","true"),
            EfficiencyCategoryAndState = cms.vstring("matched","true"),
            UnbinnedVariables = cms.vstring("acoplanarity"),
            BinnedVariables = cms.PSet(
                SCEt = cms.vdouble(2, 20),
                # pt = cms.vdouble(0, 20),
                abseta = cms.vdouble(0, 2.3),
            ),
         BinToPDFmap = cms.vstring(PDFName)
        ),
        effVsEta = cms.PSet(
#            EfficiencyCategoryAndState = cms.vstring("doubleEG2","true","matched","true"),
            EfficiencyCategoryAndState = cms.vstring("matched","true"),
            UnbinnedVariables = cms.vstring("acoplanarity"),
            BinnedVariables = cms.PSet(
                # pt = cms.vdouble(0, 20),
                SCEt = cms.vdouble(2, 20),
                abseta = cms.vdouble(0, 0.5, 1, 1.5, 2, 2.3),
            ),
         BinToPDFmap = cms.vstring(PDFName)
        ),
        effVsPt_lowEta = cms.PSet(
#          EfficiencyCategoryAndState = cms.vstring("doubleEG2","true","matched","true"),
          EfficiencyCategoryAndState = cms.vstring("matched","true"),
            UnbinnedVariables = cms.vstring("acoplanarity"),
            BinnedVariables = cms.PSet(
                # pt = cms.vdouble(0, 2, 3, 4, 5, 6, 7, 10, 14, 20),
                SCEt = cms.vdouble(2, 3, 4, 5, 6, 7, 10, 14, 20),
                abseta = cms.vdouble(0, 1.2),
            ),
         BinToPDFmap = cms.vstring(PDFName)
        ),
        effVsPt_highEta = cms.PSet(
#          EfficiencyCategoryAndState = cms.vstring("doubleEG2","true","matched","true"),
          EfficiencyCategoryAndState = cms.vstring("matched","true"),
            UnbinnedVariables = cms.vstring("acoplanarity"),
            BinnedVariables = cms.PSet(
                # pt = cms.vdouble(0, 2, 3, 4, 5, 6, 7, 10, 14, 20),
                SCEt = cms.vdouble(2, 3, 4, 5, 6, 7, 10, 14, 20),
#                SCEt = cms.vdouble(2, 3.5, 5, 7, 10, 20),
                abseta = cms.vdouble(1.2, 2.3),
            ),
         BinToPDFmap = cms.vstring(PDFName)
        )
)

print("Setting process")

process.tagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    InputFileNames = cms.vstring("file:/afs/cern.ch/work/j/jniedzie/private/efficienciesQED.root"),
    InputDirectoryName = cms.string("triggerTree_%s" % (dataOrMC)),
    InputTreeName = cms.string("tree"),
    OutputFileName = cms.string("triggerEfficiencyQED_%s.root" % (dataOrMC)),
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
#                         diMass           = cms.vstring("diele Mass", "0", "20.0", "GeV/c^{2}"),
#                         diPt             = cms.vstring("diele Pt", "0", "20.0", "GeV/c"),
#                         diRap            = cms.vstring("diele y", "-3", "3", ""),
                         acoplanarity     = cms.vstring("acoplanarity", "0", "0.06", ""),
#                         pt               = cms.vstring("Probe p_{T}", "0.0", "20", "GeV/c"),
#                         eta              = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
                         SCEt             = cms.vstring("SCEt", "0.0", "20", "GeV/c"),
#                         SCEta            = cms.vstring("Probe SC #eta", "-2.4", "2.4", ""),
                         abseta           = cms.vstring("abseta", "0", "2.4", ""),
#                         tag_pt           = cms.vstring("Tag p_{T}", "0", "20", "GeV/c^{2}"),
    ),
    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
    Categories = cms.PSet(
#                        doubleEG2 = cms.vstring("doubleEG2", "dummy[true=1,false=0]"),
                        matched = cms.vstring("matched", "dummy[true=1,false=0]"),

    ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
        # Nominal
	    expoPlusBkg = cms.vstring(
		    "Exponential::signal(acoplanarity, decaySig[-6.8e2,-1e4,-250])",
	    	"Exponential::backgroundPass(acoplanarity, decayBkgPass[-80,-249,-10])",
          # "Exponential::backgroundFail(acoplanarity, decayBkgFail[-1000,-1e4,-10])",
		    "Exponential::backgroundFail(acoplanarity, decayBkgPass)",
	    	"efficiency[0.9,0.,1]",
		    "signalFractionInPassing[0.9]",
    	),    
        # Nominal
	    expo = cms.vstring(
		    "Exponential::signal(acoplanarity, decaySig[-6.8e2,-1e4,0])",
	    	"Uniform::backgroundPass(acoplanarity)",
	    	"Uniform::backgroundFail(acoplanarity)",
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
