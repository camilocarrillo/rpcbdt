#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TVector3.h"
#include "TLorentzVector.h"
#include <ios>
#include "rpcBDT/CPPFDigi/interface/CPPFGen.h"

using namespace edm;
using namespace std;

CPPFGen::CPPFGen(const edm::ParameterSet& iConfig) :
  genParToken_(consumes<std::vector<reco::GenParticle>>(iConfig.getParameter<InputTag>("genParticlesLabel"))),
  recHitToken_(consumes<RPCRecHitCollection>(iConfig.getParameter<InputTag>("recHitLabel"))),
  cppfDigiToken_(consumes<l1t::CPPFDigiCollection>(iConfig.getParameter<InputTag>("cppfdigiLabel"))){
 
  ofstream features;
  ofstream target;
 
  features.open("bdt_training_features.csv", std::ofstream::trunc);
  features << 
                "Deltaphi12" << "," << "Deltaphi23" << "," << "Deltaphi34" << "," <<
		"Deltaphi34" << "," <<
                "Cppf_theta3" << "," << 
                "cluster_size1" << "," << "cluster_size2" << "," << "cluster_size3" << "," << "cluster_size4" << // "," <<
  
 
/*      
  "Cppf_phi1" << "," << "Cppf_phi2" << "," << "Cppf_phi3" << "," << "Cppf_phi4" << "," <<
  "Cppf_theta1" << "," << "Cppf_theta2" << "," << "Cppf_theta3" << "," << "Cppf_theta4" << "," <<
  "cluster_size1" << "," << "cluster_size2" << "," << "cluster_size3" << "," << "cluster_size4" << "," <<
  "Deltaphi12" << "," << "Deltaphi23" << "," << "Deltaphi34" << "," <<
  "Deltatheta12" << "," << "Deltatheta23" << "," << "Deltatheta34" << //"," <<
	//"," <<

  "Cppf_Gphi1" << "," << "Rec_phi1" << "," << "rawId1" <<  "," << "strip1" << "," <<
    "Cppf_Gphi2" << "," << "Rec_phi2" << "," << "rawId2" <<  "," << "strip2" << "," <<
    "Cppf_Gphi3" << "," << "Rec_phi3" << "," << "rawId3" <<  "," << "strip3" << "," <<
    "Cppf_Gphi4" << "," << "Rec_phi4" << "," << "rawId4" <<  "," << "strip4" <<
*/
    endl;
  features.close();
  //Target	 
  target.open("bdt_training_target.csv", std::ofstream::trunc);
  target << 
  "Muon_pt" <<
   endl;
  target.close();
   
}

CPPFGen::~CPPFGen(){
}

void CPPFGen::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  
  //Get the gen level information
  Handle<vector<reco::GenParticle>> genParHandle;
  iEvent.getByToken(genParToken_,genParHandle);
  //Get the rechit 
  Handle<RPCRecHitCollection> recHits;
  iEvent.getByToken(recHitToken_, recHits);
  //Get the CPPFDigi 
  Handle<l1t::CPPFDigiCollection> SimCppfDigis;
  iEvent.getByToken(cppfDigiToken_, SimCppfDigis);
  
  //File for output
  ofstream features;
  ofstream target;
  features.open("bdt_training_features.csv", std::ios_base::app);
  target.open("bdt_training_target.csv", std::ios_base::app);
 
  
  
  
  if(genParHandle.isValid()){
    
    NMuons = 0;
    
    for (auto& gen_iter : *genParHandle){
      // For Muons -13
      if(gen_iter.pdgId() == -13){
	
	NMuons++;
        Muon_pt = 0;
        Muon_Gen.SetXYZ(gen_iter.p4().x(), gen_iter.p4().y(), gen_iter.p4().z());
	Muon_pt = sqrt(pow(Muon_Gen.Px(), 2)+ pow(Muon_Gen.Py(),2));
//        cout << " Muon_pt " << Muon_pt << endl; 
	
        //Matching routine
        Float_t min_deltaR1 = 0.4;
        Float_t min_deltaR2 = 0.4;
        Float_t min_deltaR3 = 0.4;
        Float_t min_deltaR4 = 0.4;
        int NRechits1 = 0;
	int NRechits2 = 0;
        int NRechits3 = 0;
        int NRechits4 = 0;
 
        bool match = false;
	NRechits = 0;
	
        Rec_station1=Rec_station2=Rec_station3=Rec_station4 = 0;
        Rec_phi1 = Rec_phi2 = Rec_phi3 = Rec_phi4 = 0.;
  //      cout << " Rec hit processor ---------------- " << endl; 

        for (auto& rechit_it : *recHits){
      
        RPCDetId rpcId = rechit_it.rpcId();	
        int station = rpcId.station();
        int region = rpcId.region();
	const RPCRoll* roll = rpcGeom->roll(rpcId);
	const BoundPlane& rollSurface = roll->surface();
	LocalPoint lPos = rechit_it.localPosition();
	GlobalPoint gPos = rollSurface.toGlobal(lPos);
	TVector3 pos(gPos.x(),gPos.y(),gPos.z());
	
        
		//Rechits in the endcaps
	  if((region == -1) || (region == 1)){
 	  
//          std::cout << " Delta R " << Muon_Gen.DeltaR(pos) << " Global_EMTFPhi " << 
	    //emtf::rad_to_deg(gPos.phi().value()) << " Station " << station << std::endl;
	  
	    if((station == 1) && (Muon_Gen.DeltaR(pos) < min_deltaR1)){
	      min_deltaR1 = Muon_Gen.DeltaR(pos);
	      Rec_station1 = station;
	      Rec_phi1 = emtf::rad_to_deg(gPos.phi().value());
	      NRechits1 = 1;
  //            cout << " Found station: " << station << endl; 
	    } 
	    if((station == 2) && (Muon_Gen.DeltaR(pos) < min_deltaR2)){
	      min_deltaR2 = Muon_Gen.DeltaR(pos);
	      Rec_station2 = station;
	      Rec_phi2 = emtf::rad_to_deg(gPos.phi().value());
	      NRechits2 = 1;
    //          cout << " Found station: " << station << endl; 
	    } 
	    if((station == 3) && (Muon_Gen.DeltaR(pos) < min_deltaR3)){
	      min_deltaR3 = Muon_Gen.DeltaR(pos);
	      Rec_station3 = station;
	      Rec_phi3 = emtf::rad_to_deg(gPos.phi().value());
	      NRechits3 = 1;
      //        cout << " Found station: " << station << endl; 
	    } 
	    if((station == 4) && (Muon_Gen.DeltaR(pos) < min_deltaR4)){
	      min_deltaR4 = Muon_Gen.DeltaR(pos);
	      Rec_station4 = station;
	      Rec_phi4 = emtf::rad_to_deg(gPos.phi().value());
	      NRechits4 = 1;
        //      cout << " Found station: " << station << endl; 
	    } 

	   }
	    
	}


          //End of loop over RecHits
	NRechits = NRechits1 + NRechits2 + NRechits3 + NRechits4;
	if(NRechits > 0) match = true; 
/*
	cout << " NRechits " << NRechits  
	     << " Rec_station1 " << Rec_station1 << " GlobalEMTFPhi " << Rec_phi1  
	     << " Rec_station2 " << Rec_station2 << " GlobalEMTFPhi " << Rec_phi2 
	     << " Rec_station3 " << Rec_station3 << " GlobalEMTFPhi " << Rec_phi3 
	     << " Rec_station4 " << Rec_station4 << " GlobalEMTFPhi " << Rec_phi4 << endl; 
*/	
        // if there is a matched with at least one rechit...	
 	if(match){


	  if(SimCppfDigis.isValid()){
	    
//	    cout << " CPPF processor ---------------- " << endl; 
	    
            NCPPFDigis = 0; 
            int NCPPFDigis1  = 0;    
            int NCPPFDigis2  = 0;    
            int NCPPFDigis3  = 0;    
            int NCPPFDigis4  = 0;    
            Cppf_phi1 = Cppf_phi2 = Cppf_phi3 = Cppf_phi4 = 0;
            Deltaphi12 = Deltaphi23 = Deltaphi34 = 0;
            Cppf_theta1 = Cppf_theta2 = Cppf_theta3 = Cppf_theta4 = 0;
	    Deltatheta12 = Deltatheta23 = Deltatheta34 = 0;
            Cppf_Gphi1 = Cppf_Gphi2 = Cppf_Gphi3 = Cppf_Gphi4 = 0.;
            rawId1 = rawId2 = rawId3 = rawId4 = 0;
            strip1 = strip2 = strip3 = strip4 = 0;
            cluster_size1 = cluster_size2 = cluster_size3 = cluster_size4 = 0;
	    pt_1530_1 = pt_815_1 = pt_48_1 = pt_14_1 = -511;
	    dpt_1530_1 = dpt_815_1 = dpt_48_1 = dpt_14_1 = -511.;
	    pt_1530_2 = pt_815_2 = pt_48_2 = pt_14_2 = -511;
	    dpt_1530_2 = dpt_815_2 = dpt_48_2 = dpt_14_2 = -511.;

             
	    for(auto& SimCppfDigi : *SimCppfDigis){ 
	      const RPCDetId& rpcId = SimCppfDigi.RPCId();
 	      int RawId = rpcId.rawId();
              //int rpcstation = rpcId.station();
 	      int Cppf_station = SimCppfDigi.Station();	
	      int Cluster_size =  SimCppfDigi.Cluster_size();
	      int Cppf_Itheta = SimCppfDigi.Theta_int();
	      int Cppf_Iphi = SimCppfDigi.Phi_int(); 
	      //float Cppf_Gtheta = SimCppfDigi.Theta_glob(); 
	      float Cppf_Gphi = SimCppfDigi.Phi_glob();
	      int Strip = SimCppfDigi.First_strip();
	      //int EMTFSector = SimCppfDigi.EMTF_sector(); 
	      
	      // Find the CPPFDigis Asociated with the rechits
	      
//	      cout << " Angle of CPPFDigi " << " Cppf_Gphi " << Cppf_Gphi << " Cppf_station " << Cppf_station <<endl;
	      
	      if ((Cppf_Gphi == Rec_phi1) && (Cppf_station == Rec_station1)){
                Cppf_phi1 = Cppf_Iphi;
                Cppf_theta1 = Cppf_Itheta;
                cluster_size1 = Cluster_size;
		Cppf_Gphi1 = Cppf_Gphi;
                rawId1 = RawId;
                strip1 = Strip; 
//		cout << " Cppf_phi1 " << Cppf_phi1 << " Cppf_theta1 " << Cppf_theta1 << " cluster_size1 " << cluster_size1 <<
//		  " Cppf_Gphi1 " << Cppf_Gphi1 << " Rec_phi1 " << Rec_phi1 << " rawId1 " << rawId1 << 
//		  " strip1 " << strip1 << endl;
	        NCPPFDigis1 = 1;   	
	      }
 //		else cout << " No found in 1 " << endl; 
	      if ((Cppf_Gphi == Rec_phi2) && (Cppf_station == Rec_station2)){
                Cppf_phi2 = Cppf_Iphi;
                Cppf_theta2 = Cppf_Itheta;
                cluster_size2 = Cluster_size;
                Cppf_Gphi2 = Cppf_Gphi;
                rawId2 = RawId;
                strip2 = Strip;
   //             cout << " Cppf_phi2 " << Cppf_phi2 << " Cppf_theta2 " << Cppf_theta2 << " cluster_size2 " << cluster_size2 <<
//		  " Cppf_Gphi2 " << Cppf_Gphi2 << " Rec_phi2 " << Rec_phi2 << " rawId2 " << rawId2 <<
//		  " strip2 " << strip2 << endl;
	        NCPPFDigis2 = 1;   	
	      }
 //		else cout << " No found in 2 " << endl; 
	      if ((Cppf_Gphi == Rec_phi3) && (Cppf_station == Rec_station3)){
                Cppf_phi3 = Cppf_Iphi;
                Cppf_theta3 = Cppf_Itheta;
                cluster_size3 = Cluster_size;
                Cppf_Gphi3 = Cppf_Gphi;
                rawId3 = RawId;
                strip3 = Strip;
   //             cout << " Cppf_phi3 " << Cppf_phi3 << " Cppf_theta3 " << Cppf_theta3 << " cluster_size3 " << cluster_size3 <<
//		  " Cppf_Gphi3 " << Cppf_Gphi3 << " Rec_phi3 " << Rec_phi3 << " rawId3 " << rawId3 <<
//		  " strip3 " << strip3 << endl;
	        NCPPFDigis3 = 1;   	
	      }
 //		else cout << " No found in 3 " << endl; 
              if ((Cppf_Gphi == Rec_phi4) && (Cppf_station == Rec_station4)){
                Cppf_phi4 = Cppf_Iphi;
                Cppf_theta4 = Cppf_Itheta;
                cluster_size4 = Cluster_size;
                Cppf_Gphi4 = Cppf_Gphi;
                rawId4 = RawId;
                strip4 = Strip;
   //             cout << " Cppf_phi4 " << Cppf_phi4 << " Cppf_theta4 " << Cppf_theta4 << " cluster_size4 " << cluster_size4 <<
//		  " Cppf_Gphi4 " << Cppf_Gphi4 << " Rec_phi4 " << Rec_phi4 << " rawId4 " << rawId4 <<
//		  " strip2 " << strip4 << endl;
	        NCPPFDigis4 = 1;   	
	      }
 //		else cout << " No found in 4 " << endl;
		
	
              int invalidphi = -511;
	      int invalidtheta = -511;  
		//Deltaphi information 
	      if ((Cppf_phi1 > 0 ) && (Cppf_phi2 > 0)) { Deltaphi12 = Cppf_phi1-Cppf_phi2;}
              else Deltaphi12 = invalidphi;
	      if ((Cppf_phi2 > 0 ) && (Cppf_phi3 > 0)) { Deltaphi23 = Cppf_phi2-Cppf_phi3;}
              else Deltaphi23 = invalidphi;
	      if ((Cppf_phi3 > 0 ) && (Cppf_phi4 > 0)) { Deltaphi34 = Cppf_phi3-Cppf_phi4;}
              else Deltaphi34 = invalidphi;
		//Deltatheta information
	      if ((Cppf_theta1 > 0 ) && (Cppf_theta2 > 0)) {Deltatheta12 = Cppf_theta1-Cppf_theta2;}
	      else Deltatheta12 = invalidtheta;
	      if ((Cppf_theta2 > 0 ) && (Cppf_theta3 > 0)) {Deltatheta23 = Cppf_theta2-Cppf_theta3;}
	      else Deltatheta23 = invalidtheta;
	      if ((Cppf_theta3 > 0 ) && (Cppf_theta4 > 0)) {Deltatheta34 = Cppf_theta3-Cppf_theta4;}
	      else Deltatheta34 = invalidtheta;

              
//	      cout << " Deltaphi12 " << Deltaphi12 << " Deltaphi23 " << Deltaphi23 << " Deltaphi34 " << Deltaphi34 << endl;  
//	      cout << " Deltatheta12 " << Deltatheta12 << " Deltatheta23 " << Deltatheta23 << " Deltatheta34 " << Deltatheta34 << endl;  
		Int_t deltaphi1 = abs(Deltaphi12);
                Float_t ddeltaphi1 = abs(Cppf_Gphi1-Cppf_Gphi2);
		Int_t deltaphi2 = abs(Deltaphi34);
                Float_t ddeltaphi2 = abs(Cppf_Gphi3-Cppf_Gphi4);

		if((Muon_pt >= 1.) && (Muon_pt < 4.))	{
             //    cout << deltaphi1 << " "<< Cppf_phi1  << " " << Cppf_phi2   <<  endl;
		 pt_14_1 = deltaphi1;
		 dpt_14_1 = ddeltaphi1; 
		 pt_14_2 = deltaphi2;
		 dpt_14_2 = ddeltaphi2; 
              //   Deltaphi1_rechit->Fill(ddeltaphi);
		}
		else if((Muon_pt >= 4.) && (Muon_pt < 8.))	{
		 pt_48_1 = deltaphi1;
		 dpt_48_1 = ddeltaphi1; 
		 pt_48_2 = deltaphi2;
		 dpt_48_2 = ddeltaphi2; 
                // Deltaphi2_rechit->Fill(ddeltaphi);
		}
		else if((Muon_pt >= 8.) && (Muon_pt < 15.))	{
		 pt_815_1 = deltaphi1;
		 dpt_815_1 = ddeltaphi1; 
		 pt_815_2 = deltaphi2;
		 dpt_815_2 = ddeltaphi2; 
                 //Deltaphi3_rechit->Fill(ddeltaphi);
		}
		else if((Muon_pt >= 15.) && (Muon_pt < 31.))	{
		 pt_1530_1 = deltaphi1;
		 dpt_1530_1 = ddeltaphi1; 
		 pt_1530_2 = deltaphi2;
		 dpt_1530_2 = ddeltaphi2; 
                // Deltaphi4_rechit->Fill(ddeltaphi);
		}
	      
	    }//Loop over CPPFDigis
	    NCPPFDigis = NCPPFDigis1 + NCPPFDigis2 + NCPPFDigis3 + NCPPFDigis4; 
	   
	    //Possible cuts ::::::::::::::::::::
            //if(cluster_size1 > 1) continue;
	    if(NCPPFDigis < 4) continue;       // Exactly 4 hits 
            //if((Muon_pt < 50.) || (Muon_pt > 70.)) continue;
            //:::::::::::::::::::::::::::::::::::::
  //          cout << " ---------------------- Final CPPFDigis ------------------- " << endl;
//	    cout << NCPPFDigis << endl; 
 //	      cout << " ---------------Final event -------------- " << endl;
	      
/*	      cout << 
                Cppf_phi1 << "," << Cppf_phi2 << "," << Cppf_phi3 << "," << Cppf_phi4 << "," << 
                Cppf_theta1 << "," << Cppf_theta2 << "," << Cppf_theta3 << "," << Cppf_theta4 << "," <<
		cluster_size1 << "," << cluster_size2 << "," << cluster_size3 << "," << cluster_size4 << "," << 
		Deltaphi12 << "," << Deltaphi23 << "," << Deltaphi34 << "," << 
		Deltatheta12 << "," << Deltatheta23 << "," << Deltatheta34 << "," <<
                Muon_pt << 
		//"," << 
		//Control
		
		Cppf_Gphi1 << "," << Rec_phi1 << "," << rawId1  << "," << strip1 << "," << 
		Cppf_Gphi2 << "," << Rec_phi2 << "," << rawId2  << "," << strip2 << "," <<
		Cppf_Gphi3 << "," << Rec_phi3 << "," << rawId3  << "," << strip3 << "," <<
		Cppf_Gphi4 << "," << Rec_phi4 << "," << rawId4  << "," << strip4  <<
		
		endl;
	      */
	      features << 
                Deltaphi12 << "," << Deltaphi23 << "," << Deltaphi34 << "," <<
		Deltaphi34 << "," <<
                Cppf_theta3 << "," << 
                cluster_size1 << "," << cluster_size2 << "," << cluster_size3 << "," << cluster_size4 << // "," <<
                

		//Cppf_phi1 << "," << Cppf_phi2 << "," << Cppf_phi3 << "," << Cppf_phi4 << "," <<
                //Cppf_theta1 << "," << Cppf_theta2 << "," << Cppf_theta3 << "," << Cppf_theta4 << "," <<
                //Deltatheta12 << "," << Deltatheta23 << "," << Deltatheta34 <<  "," << 
		//"," <<
                //Control


                /*
                Cppf_Gphi1 << "," << Rec_phi1 << "," << rawId1  << "," << strip1 << "," <<
                Cppf_Gphi2 << "," << Rec_phi2 << "," << rawId2  << "," << strip2 << "," <<
                Cppf_Gphi3 << "," << Rec_phi3 << "," << rawId3  << "," << strip3 << "," <<
                Cppf_Gphi4 << "," << Rec_phi4 << "," << rawId4  << "," << strip4  <<
		*/
                endl;
	       target << 
                Muon_pt << 
	        endl; 
	      //Tree filling
	       tree_->Fill();
	      
	  } //CPPFDigi isValid
	}// Matching between muon and the some Rechit  
	
		
	/*******************************************/
	
      } // if the particle is one MUON
      
    } // for loop over genlevel particles
    
    
  } //Genlevel isValid
  
  
  features.close();
  target.close();
  
} //End class

void CPPFGen::beginRun(const edm::Run& run, const edm::EventSetup& iSetup){
 // edm::ESHandle<RPCGeometry> rpcGeom;
  iSetup.get<MuonGeometryRecord>().get(rpcGeom);
}

void CPPFGen::beginJob(){
 
//  Service<TFileService> fs;
//  Deltaphi1_rechit = fs->make<TH1D>("Deltaphi1_rechit", "Deltaphi1_rechit", 100, 0., 10.);
//  Deltaphi2_rechit = fs->make<TH1D>("Deltaphi2_rechit", "Deltaphi2_rechit", 100, 0., 10.);
//  Deltaphi3_rechit = fs->make<TH1D>("Deltaphi3_rechit", "Deltaphi3_rechit", 100, 0., 10.);
//  Deltaphi4_rechit = fs->make<TH1D>("Deltaphi4_rechit", "Deltaphi4_rechit", 100, 0., 10.);


   Service<TFileService> fs;
  tree_ = fs->make<TTree>("tree","tree");
  
  //tree_->Branch("NMuons", &NMuons, "NMUons/S");
  tree_->Branch("NRechits", &NRechits, "NRechits/S");
  tree_->Branch("NCPPFDigis", &NCPPFDigis, "NCPPFDigis/S");
  tree_->Branch("Cppf_phi1", &Cppf_phi1, "Cppf_phi1/S");
  tree_->Branch("Cppf_theta1", &Cppf_theta1, "Cppf_theta1/S");
  tree_->Branch("cluster_size1", &cluster_size1, "cluster_size1/S");
  tree_->Branch("Cppf_phi2", &Cppf_phi2, "Cppf_phi2/S");
  tree_->Branch("Cppf_theta2", &Cppf_theta2, "Cppf_theta2/S");
  tree_->Branch("cluster_size2", &cluster_size2, "cluster_size2/S");
  tree_->Branch("Cppf_phi3", &Cppf_phi3, "Cppf_phi3/S");
  tree_->Branch("Cppf_theta3", &Cppf_theta3, "Cppf_theta3/S");
  tree_->Branch("cluster_size3", &cluster_size3, "cluster_size3/S");
  tree_->Branch("Cppf_phi4", &Cppf_phi4, "Cppf_phi4/S");
  tree_->Branch("Cppf_theta4", &Cppf_theta4, "Cppf_theta4/S");
  tree_->Branch("cluster_size4", &cluster_size4, "cluster_size4/S");
  tree_->Branch("Deltaphi12", &Deltaphi12, "Deltaphi12/S");
  tree_->Branch("Deltaphi23", &Deltaphi23, "Deltaphi23/S");
  tree_->Branch("Deltaphi34", &Deltaphi34, "Deltaphi34/S");
  tree_->Branch("Deltatheta12", &Deltatheta12, "Deltatheta12/S");
  tree_->Branch("Deltatheta23", &Deltatheta23, "Deltatheta23/S");
  tree_->Branch("Deltatheta34", &Deltatheta34, "Deltatheta34/S");
  tree_->Branch("Muon_pt", &Muon_pt, "Muon_pt/F");
  tree_->Branch("pt_14_1", &pt_14_1, "pt_14_1/S");
  tree_->Branch("pt_48_1", &pt_48_1, "pt_48_1/S");
  tree_->Branch("pt_815_1", &pt_815_1, "pt_815_1/S");
  tree_->Branch("pt_1530_1", &pt_1530_1, "pt_1530_1/S");
  tree_->Branch("dpt_14_1", &dpt_14_1, "dpt_14_1/F");
  tree_->Branch("dpt_48_1", &dpt_48_1, "dpt_48_1/F");
  tree_->Branch("dpt_815_1", &dpt_815_1, "dpt_815_1/F");
  tree_->Branch("dpt_1530_1", &dpt_1530_1, "dpt_1530_1/F");
 
  tree_->Branch("pt_14_2", &pt_14_2, "pt_14_2/S");
  tree_->Branch("pt_48_2", &pt_48_2, "pt_48_2/S");
  tree_->Branch("pt_815_2", &pt_815_2, "pt_815_2/S");
  tree_->Branch("pt_1530_2", &pt_1530_2, "pt_1530_2/S");
  tree_->Branch("dpt_14_2", &dpt_14_2, "dpt_14_2/F");
  tree_->Branch("dpt_48_2", &dpt_48_2, "dpt_48_2/F");
  tree_->Branch("dpt_815_2", &dpt_815_2, "dpt_815_2/F");
  tree_->Branch("dpt_1530_2", &dpt_1530_2, "dpt_1530_2/F");
    
  return;
}

//define this as a plug-in
DEFINE_FWK_MODULE(CPPFGen);

