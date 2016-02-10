#ifndef NORMGEOMETRY_NormMainGeometry_HH
#define NORMGEOMETRY_NormMainGeometry_HH

#include "VANLGeometry.hh"

class G4VUserDetectorConstruction;

namespace normgeometry {

class NormMainGeometry : public anlgeant4::VANLGeometry {

  DEFINE_ANL_MODULE(NormMainGeometry, 1.0);

public:
  NormMainGeometry() {}
  virtual ~NormMainGeometry() {}

  G4VUserDetectorConstruction* create();
};

}

#endif
