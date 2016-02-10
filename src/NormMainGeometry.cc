#include "NormMainGeometry.hh"
#include "NormMainGeometryRealWorld.hh"

using namespace normgeometry;

G4VUserDetectorConstruction* NormMainGeometry::create() {
  G4VUserDetectorConstruction* theGeometry = new NormMainGeometryRealWorld;
  return theGeometry;
}
