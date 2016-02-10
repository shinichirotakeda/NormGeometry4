#ifndef NormMainGeometryRealWorld_HH
#define NormMainGeometryRealWorld_HH

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VUserParallelWorld.hh"

namespace normgeometry {

class NormMainGeometryRealWorld : public G4VUserDetectorConstruction {

public:
  NormMainGeometryRealWorld();
  virtual ~NormMainGeometryRealWorld() {}

  virtual G4VPhysicalVolume* Construct();
  void Initialize();

private:
  void DefineMaterials() {};
  void SetupGeometry();

  G4int constructed;
  G4LogicalVolume* World_Logical;
  G4VPhysicalVolume* World_Physical;

};

}
#endif
