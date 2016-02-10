#ifndef GeometryNORM_HH
#define GeometryNORM_HH

#include "globals.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;

namespace normgeometry {

class GeometryNorm {

public:
  GeometryNorm() {}
  virtual ~GeometryNorm() {}

  G4LogicalVolume* Construct();

private:

  void DefineMaterials() {};
  void SetupGeometry() {};
};

}

#endif

