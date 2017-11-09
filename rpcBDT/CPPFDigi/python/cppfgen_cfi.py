import FWCore.ParameterSet.Config as cms

demo = cms.EDAnalyzer('CPPFGen',
		      genParticlesLabel = cms.InputTag("genParticles"),
		      recHitLabel = cms.InputTag("rpcRecHits"),
                      cppfdigiLabel = cms.InputTag("simCppfDigis","recHit")                  
)

