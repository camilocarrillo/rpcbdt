#ifndef rpcBDT_CPPFGen_h
#define rpcBDT_CPPFGen_h

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "Geometry/RPCGeometry/interface/RPCRoll.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"

#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"
#include "DataFormats/L1TMuon/interface/CPPFDigi.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/L1TMuon/interface/CPPFDigi.h"
#include "DataFormats/Common/interface/Handle.h"

#include "CondFormats/RPCObjects/interface/RPCMaskedStrips.h"
#include "CondFormats/RPCObjects/interface/RPCDeadStrips.h"
#include "CondFormats/Serialization/interface/Serializable.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "L1Trigger/L1TMuonEndCap/interface/TrackTools.h"

#include<boost/cstdint.hpp>
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TLorentzVector.h"

class CPPFGen : public edm::EDAnalyzer {
  
   public:
	explicit CPPFGen(const edm::ParameterSet&);
	~CPPFGen();
        edm::ESHandle <RPCGeometry> rpcGeom;
        virtual void beginRun(const edm::Run&, const edm::EventSetup&);
        virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
         

   private:

	virtual void beginJob() override;

   const edm::EDGetTokenT<std::vector<reco::GenParticle>> genParToken_;   
   const edm::EDGetTokenT<RPCRecHitCollection> recHitToken_;
   const edm::EDGetTokenT<l1t::CPPFDigiCollection> cppfDigiToken_;


   Int_t NMuons;
   Float_t Muon_pt; 
   Int_t NRechits;
   Int_t NMatchMuons;
   //Rechits variables
   Int_t Rec_station1;
   float Rec_phi1;
   Int_t Rec_station2;
   float Rec_phi2;
   Int_t Rec_station3;
   float Rec_phi3;
   Int_t Rec_station4;
   float Rec_phi4;
   //Cppfdigis variables 
   Int_t NCPPFDigis;
   Int_t Cppf_phi1;
   Int_t Cppf_phi2;
   Int_t Cppf_phi3;
   Int_t Cppf_phi4;
   Int_t Deltaphi12;
   Int_t Deltaphi23;
   Int_t Deltaphi34;
   Int_t Cppf_theta1;
   Int_t Cppf_theta2;
   Int_t Cppf_theta3;
   Int_t Cppf_theta4;
   Int_t Deltatheta12;
   Int_t Deltatheta23;
   Int_t Deltatheta34;
   Float_t Cppf_Gphi1;
   Float_t Cppf_Gphi2;
   Float_t Cppf_Gphi3;
   Float_t Cppf_Gphi4;
   Int_t rawId1;
   Int_t rawId2;
   Int_t rawId3;
   Int_t rawId4;
   Int_t strip1;
   Int_t strip2;
   Int_t strip3;
   Int_t strip4;
   Int_t cluster_size1;	
   Int_t cluster_size2;	
   Int_t cluster_size3;	
   Int_t cluster_size4;	

   Int_t pt_1530_1;
   Int_t pt_815_1;
   Int_t pt_48_1;
   Int_t pt_14_1;

   Float_t dpt_1530_1;
   Float_t dpt_815_1;
   Float_t dpt_48_1;
   Float_t dpt_14_1;

  
   Int_t pt_1530_2;
   Int_t pt_815_2;
   Int_t pt_48_2;
   Int_t pt_14_2;

   Float_t dpt_1530_2;
   Float_t dpt_815_2;
   Float_t dpt_48_2;
   Float_t dpt_14_2;
   //TVectors

   //TVectors
   TVector3 Muon_Gen;

   //Histos and trees
   TTree* tree_;
   TH1D* Deltaphi1_rechit;
   TH1D* Deltaphi2_rechit;
   TH1D* Deltaphi3_rechit;
   TH1D* Deltaphi4_rechit;



};


#endif


