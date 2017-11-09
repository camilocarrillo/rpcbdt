// Class for RPC trigger primitives sent from CPPF to EMTF
// Author Alejandro Segura -- Universidad de los Andes

#ifndef DataFormats_L1TMuon_CPPFDigi_h
#define DataFormats_L1TMuon_CPPFDigi_h

#include "DataFormats/MuonDetId/interface/RPCDetId.h"

// For CPPFDigiCollection
#include "DataFormats/MuonData/interface/MuonDigiCollection.h"
#include "DataFormats/Common/interface/RangeMap.h"
#include "DataFormats/Common/interface/ClonePolicy.h"
#include "DataFormats/Common/interface/OwnVector.h"

#include <iostream>
#include <cstdint>
#include <iosfwd>
#include <stdint.h>

namespace l1t {
  
  class CPPFDigi{
    
  public:

    CPPFDigi() :
    bx(-99), phi_int(-99), theta_int(-99), emtf_sector(-99), valid(-99), 
      first_strip(-99), cluster_size(-99), station(-99), phi_glob(-99), theta_glob(-99)
      {};
    
    explicit CPPFDigi( const RPCDetId& _rpcId, int _bx, int _phi_int, int _theta_int,
    		       int _emtf_sector, int _valid, int _first_strip, int _cluster_size,
    		       int _station, float _phi_glob, float _theta_glob
    		       );

    virtual ~CPPFDigi() {};
    
    virtual CPPFDigi* clone() const;
    
    CPPFDigi( const RPCDetId& rpcId, int _bx );
    
    bool operator==(const CPPFDigi& cppf) const;
    
    
    RPCDetId RPCId()   const { return rpcId; }
    int BX()           const { return bx; }
    int Phi_int()      const { return phi_int; }
    int Theta_int()    const { return theta_int; }
    int EMTF_sector()  const { return emtf_sector; } 
    int Valid()        const { return valid; }
    int First_strip()  const { return first_strip; }
    int Cluster_size() const { return cluster_size; }
    int Station()      const { return station; }
    float Phi_glob()   const { return phi_glob; }
    float Theta_glob() const { return theta_glob; }
    
  private:

    RPCDetId rpcId;   // RPC detector ID
    int bx;           // Bunch crossing, signed, centered at 0
    int phi_int;      // Local integer phi value within an EMTF sector, represents 1/15 degree
    int theta_int;    // Integer theta value in EMTF scale, represents 36.5/32 degree
    int emtf_sector;  // EMTF sector, 1 - 6 in each endcap
    int valid;     
    int first_strip;  // Lowest-numbered strip in the cluster
    int cluster_size; // Number of strips in the cluster
    int station;
    float phi_glob;   // Global phi coordinate in degrees, from -180 to 180
    float theta_glob; // Global theta coordinate in degrees, from 0 to 90
  
  }; // End of class CPPFDigi

  // Define a collection of CPPFDigis
  typedef std::vector<CPPFDigi> CPPFDigiCollection;

} // End of namespace l1t

#endif /* #define DataFormats_L1TMuon_CPPFDigi_h */

/// The ostream operator
std::ostream & operator<<(std::ostream & o, const l1t::CPPFDigi& cppf);
