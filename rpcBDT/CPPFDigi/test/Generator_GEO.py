import FWCore.ParameterSet.Config as cms
#import FWCore.Utilities.FileUtils as FileUtils

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('Demo')
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
	limit = cms.untracked.int32(-1)
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.EventContent.EventContent_cff')
#process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
#process.load('Configuration.Geometry.GeometryDB_cff')
process.load('Configuration.Geometry.GeometryExtended2016_cff')
process.load('Configuration.Geometry.GeometryExtended2016Reco_cff')



process.source = cms.Source("PoolSource",
	fileNames = cms.untracked.vstring(
	#'file:/afs/cern.ch/user/m/masegura/CMSSW_9_2_5_patch2/src/L1Trigger/L1TMuonCPPF/test/SingleMuPt10_pythia8_cfi_py_GEN_SIM_DIGI_GEO.root',
	'file:/afs/cern.ch/user/m/masegura/CMSSW_9_2_5_patch2/src/L1Trigger/L1TMuonCPPF/test/SingleMuPt10_pythia8_cfi_py_GEN_SIM_DIGI_GEO.root',
	)

)

process.load('UserCodes.CPPFDigi.cppfgen_cfi')
process.TFileService = cms.Service("TFileService",
	fileName = cms.string("BDT_trainning_GEO.root")
)

process.p = cms.Path(process.demo)

