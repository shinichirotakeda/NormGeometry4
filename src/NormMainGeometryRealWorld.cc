#include "NormMainGeometryRealWorld.hh"

#include "GeometryNorm.hh"

#include "AHG4MaterialManager.hh"
#include "AHG4MaterialProperty.hh"

#include "globals.hh"
#include "G4SystemOfUnits.hh"

#include "G4Element.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4SDManager.hh"
#include "G4UserLimits.hh"
#include "G4RotationMatrix.hh"

#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;
using namespace normgeometry;

NormMainGeometryRealWorld::NormMainGeometryRealWorld()
  : constructed(false) , World_Logical(0) , World_Physical(0) {
}

G4VPhysicalVolume* NormMainGeometryRealWorld::Construct() {
  Initialize();
  return World_Physical;
}

void NormMainGeometryRealWorld::Initialize() {
  if (!constructed) {
      constructed = true;
      DefineMaterials();
      SetupGeometry();
    }
}

void NormMainGeometryRealWorld::SetupGeometry() {

  AHG4MaterialManager* mmanager = AHG4MaterialManager::GetAHG4MaterialManager();
  AHG4Material* air = mmanager->instantiate("Air");
  // AHG4Material* steel = mmanager->instantiate("Steel");

  // World ///////////////////////
  G4double World_xSize = 10000.0*mm;
  G4double World_ySize = 10000.0*mm;
  G4double World_zSize = 10000.0*mm;
  G4Box* World_Solid = new G4Box("World_Solid", World_xSize*0.5, World_ySize*0.5, World_zSize*0.5);
  World_Logical = new G4LogicalVolume(World_Solid, air, "World_Logical");
  World_Physical = new G4PVPlacement(0, G4ThreeVector(), World_Logical, "World_Physical", 0, false, 0);

  // Norm //////////////////////////
  // G4double Norm_xSize = 1500.0*mm;
  // G4double Norm_ySize = 1500.0*mm;
  // G4double Norm_zSize = 1500.0*mm;
  G4double Norm_xPos = 0.0*mm;
  G4double Norm_yPos = 0.0*mm;
  G4double Norm_zPos = 0.0*mm;
  G4RotationMatrix* em1_rot = new G4RotationMatrix;
  // em1_rot->rotateY(-90.0*deg);

  GeometryNorm* Norm_Geometry = new GeometryNorm();
  G4LogicalVolume* Norm_Logical = Norm_Geometry->Construct();
  new G4PVPlacement(em1_rot, G4ThreeVector(Norm_xPos,Norm_yPos,Norm_zPos), Norm_Logical, "Norm", World_Logical, false, 0);

}
