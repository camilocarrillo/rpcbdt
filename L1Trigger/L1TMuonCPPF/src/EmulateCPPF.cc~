
#include "L1Trigger/L1TMuonCPPF/interface/EmulateCPPF.h"

EmulateCPPF::EmulateCPPF(const edm::ParameterSet& iConfig, edm::ConsumesCollector&& iConsumes) :
  // rpcDigi_processors_(),
  recHit_processors_(),
  // rpcDigiToken_( iConsumes.consumes<RPCTag::digi_collection>(iConfig.getParameter<edm::InputTag>("recHitLabel")) ),
  recHitToken_(iConsumes.consumes<RPCRecHitCollection>(iConfig.getParameter<edm::InputTag>("recHitLabel")))
{
}

EmulateCPPF::~EmulateCPPF() {
}

void EmulateCPPF::process(
    const edm::Event& iEvent, const edm::EventSetup& iSetup,
    // l1t::CPPFDigiCollection& cppf_rpcDigi,
    l1t::CPPFDigiCollection& cppf_recHit
) {

  // Clear output collections
  // cppf_rpcDigi.clear();
  cppf_recHit.clear();

  // // Get the RPCDigis from the event
  // edm::Handle<RPCTag::digi_collection> rpcDigis;
  // iEvent.getByToken(rpcDigiToken_, rpcDigis);

  // _________________________________________________________________________________
  // Run the CPPF clusterization+coordinate conversion algo on RPCDigis and RecHits

  // For now, treat CPPF as single board
  // In the future, may want to treat the 4 CPPF boards in each endcap as separate entities

  // for (unsigned int iBoard = 0; iBoard < rpcDigi_processors_.size(); iBoard++) {
    // rpcDigi_processors_.at(iBoard).process( iSetup, rpcDigis, cppf_rpcDigi );
  // }
  for (unsigned int iBoard = 0; iBoard < recHit_processors_.size(); iBoard++) {
    recHit_processors_.at(iBoard).process( iEvent, iSetup, recHitToken_, cppf_recHit );
  }

  return;
} // End void EmulateCPPF::process()					   
