import FWCore.ParameterSet.Config as cms
import subprocess
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



readFiles = cms.untracked.vstring()
process.source = cms.Source("PoolSource",
        fileNames = readFiles,
)
in_dir_name = '/afs/cern.ch/user/m/masegura/CMSSW_9_2_5_patch2/src/L1Trigger/L1TMuonCPPF/test/'

readFiles.extend( cms.untracked.vstring('file:'+in_dir_name+'SingleMuPt10_pythia8_cfi_py_GEN_SIM_DIGI_2.root') )

#iFile = 0
#for in_file_name in subprocess.check_output(['ls', in_dir_name]).splitlines():
#    if not ('.root' in in_file_name): continue
#    iFile += 1
#    readFiles.extend( cms.untracked.vstring('file:'+in_dir_name+in_file_name) )


process.load('UserCodes.CPPFDigi.cppfgen_cfi')
process.TFileService = cms.Service("TFileService",
	fileName = cms.string("BDT_trainning_GEO.root")
)

process.p = cms.Path(process.demo)


