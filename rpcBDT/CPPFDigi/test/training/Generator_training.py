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
#in_dir_name = '/eos/cms/store/group/dpg_rpc/comm_rpc/Sandbox/masegura/MinBias/CRAB3_OCT2017_MC_Generation/171011_150025/0000/'
in_dir_name = '/eos/cms/store/user/masegura/MinBias/CRAB3_OCT2017_MC_Generation/171109_180305/0000/'
#in_dir_name = '/eos/cms/store/mc/PhaseIFall16DR/SingleMu_Pt1To1000_FlatRandomOneOverPt/AODSIM/NoPUNZS_90X_upgrade2017_realistic_v6_C1-v1/130000/'
#in_dir_name = '/afs/cern.ch/user/m/masegura/CMSSW_9_2_5_patch2/src/L1Trigger/L1TMuonCPPF/test/'

#readFiles.extend( cms.untracked.vstring('file:'+in_dir_name+'4839F3F5-DB07-E711-9CA3-0025904B201E.root') )

#readFiles.extend( cms.untracked.vstring('file:'+in_dir_name+'SingleMuPt10_pythia8_cfi_py_GEN_SIM_DIGI.root') )


#readFiles.extend( cms.untracked.vstring('file:'+in_dir_name+'SingleMuPt10_pythia8_cfi_py_GEN_SIM_DIGI_11.root') )
#readFiles.extend( cms.untracked.vstring('file:'+in_dir_name+'SingleMuPt10_pythia8_cfi_py_GEN_SIM_DIGI_12.root') )
#readFiles.extend( cms.untracked.vstring('file:'+in_dir_name+'SingleMuPt10_pythia8_cfi_py_GEN_SIM_DIGI_13.root') )
#readFiles.extend( cms.untracked.vstring('file:'+in_dir_name+'SingleMuPt10_pythia8_cfi_py_GEN_SIM_DIGI_14.root') )
#readFiles.extend( cms.untracked.vstring('file:'+in_dir_name+'SingleMuPt10_pythia8_cfi_py_GEN_SIM_DIGI_15.root') )
#readFiles.extend( cms.untracked.vstring('file:'+in_dir_name+'SingleMuPt10_pythia8_cfi_py_GEN_SIM_DIGI_16.root') )
#readFiles.extend( cms.untracked.vstring('file:'+in_dir_name+'SingleMuPt10_pythia8_cfi_py_GEN_SIM_DIGI_17.root') )
#readFiles.extend( cms.untracked.vstring('file:'+in_dir_name+'SingleMuPt10_pythia8_cfi_py_GEN_SIM_DIGI_18.root') )
#readFiles.extend( cms.untracked.vstring('file:'+in_dir_name+'SingleMuPt10_pythia8_cfi_py_GEN_SIM_DIGI_19.root') )

iFile = 0
for in_file_name in subprocess.check_output(['ls', in_dir_name]).splitlines():
    if not ('.root' in in_file_name): continue
    iFile += 1
    readFiles.extend( cms.untracked.vstring('file:'+in_dir_name+in_file_name) )


process.load('rpcBDT.CPPFDigi.cppfgen_cfi')
process.TFileService = cms.Service("TFileService",
	fileName = cms.string("BDT_training.root")
)

process.p = cms.Path(process.demo)


