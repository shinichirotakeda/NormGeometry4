#include <sstream>

#include "GeometryNorm.hh"
#include "GeometryComptonCamera.hh"

#include "AHG4MaterialManager.hh"
#include "G4SystemOfUnits.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trap.hh"
#include "G4SubtractionSolid.hh"
#include "G4RotationMatrix.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

using namespace normgeometry;

G4LogicalVolume* GeometryNorm::Construct() {

  const bool surfaceCheck = false;

  G4double margin = 0.1*mm;

  // Instantiate "!!LOCAL!!" Material //////
  AHG4MaterialManager* mmanager = AHG4MaterialManager::GetAHG4MaterialManager();
  AHG4Material* air = mmanager->instantiate("Air");
  std::string matname;
  AHG4MaterialProperty* p;
  matname = "Norm.Aluminium";
  p = mmanager->RetrieveProperty("Aluminium");
  mmanager->registerMaterial(matname, *p);
  AHG4Material* aluminium = mmanager->instantiate(matname);

  // Local World //////////////////////
  G4double LocalWorld_xSize = 1500.0*mm;
  G4double LocalWorld_ySize = 1500.0*mm;
  G4double LocalWorld_zSize = 1500.0*mm;
  G4VSolid* LocalWorld_Solid = new G4Box("LocalWorld_Solid", LocalWorld_xSize*0.5, LocalWorld_ySize*0.5, LocalWorld_zSize*0.5);
  G4LogicalVolume* LocalWorld_Logical = new G4LogicalVolume(LocalWorld_Solid, air, "LocalWorld_Logical");



  //CC Case hyoumen ga 0.0mm

  ///// CC Case /////////////////////////
  ///// CCCaseFrontBoard /////////////////////////
  G4double CCCaseFrontBoard_xSize = 206.0*mm;
  G4double CCCaseFrontBoard_ySize = 190.0*mm;
  G4double CCCaseFrontBoard_zSize = 1.0*mm;
  G4VSolid* CCCaseFrontBoard_Solid = new G4Box("CCCaseFrontBoard_Solid", CCCaseFrontBoard_xSize*0.5, CCCaseFrontBoard_ySize*0.5, CCCaseFrontBoard_zSize*0.5);
  G4LogicalVolume* CCCaseFrontBoard_Logical = new G4LogicalVolume(CCCaseFrontBoard_Solid, aluminium, "CCCaseFrontBoard_Logical");
  G4double CCCaseFrontBoard_xPos = 0.0*mm;
  G4double CCCaseFrontBoard_yPos = 0.0*mm;
  G4double CCCaseFrontBoard_zPos = -CCCaseFrontBoard_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(CCCaseFrontBoard_xPos, CCCaseFrontBoard_yPos, CCCaseFrontBoard_zPos), CCCaseFrontBoard_Logical, "CCCaseFrontBoard", LocalWorld_Logical, false, 0, surfaceCheck);
  ///// CCCaseAlumiFrame /////////////////////////
  G4double CCCaseAlumiFrame_xSize = 194.0*mm;
  G4double CCCaseAlumiFrame_ySize = 190.0*mm;
  G4double CCCaseAlumiFrame_zSize = 20.0*mm;
  G4VSolid* CCCaseAlumiFrameBody_Solid = new G4Box("CCCaseAlumiFrameBody_Solid", CCCaseAlumiFrame_xSize*0.5, CCCaseAlumiFrame_ySize*0.5, CCCaseAlumiFrame_zSize*0.5);
  G4double CCCaseAlumiFrameHole_xSize = 194.0*mm;
  G4double CCCaseAlumiFrameHole_ySize = 178.0*mm;
  G4double CCCaseAlumiFrameHole_zSize = 20.0*mm;
  G4VSolid* CCCaseAlumiFrameHole_Solid = new G4Box("CCCaseAlumiFrameHole_Solid", CCCaseAlumiFrameHole_xSize*0.5, CCCaseAlumiFrameHole_ySize*0.5, CCCaseAlumiFrameHole_zSize*0.5+margin);
  G4VSolid* CCCaseAlumiFrame_Solid = new G4SubtractionSolid("CCCaseAlumiFrame_Solid", CCCaseAlumiFrameBody_Solid, CCCaseAlumiFrameHole_Solid, 0, G4ThreeVector(0.0*mm, 0.0*mm, 0.0*mm));
  G4LogicalVolume* CCCaseAlumiFrame_Logical = new G4LogicalVolume(CCCaseAlumiFrame_Solid, aluminium, "CCCaseAlumiFrame_Logical");
  G4double CCCaseAlumiFrame_xPos = 0.0*mm;
  G4double CCCaseAlumiFrame_yPos = 0.0*mm;
  G4double CCCaseAlumiFrame_zPos = -CCCaseFrontBoard_zSize - CCCaseAlumiFrame_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(CCCaseAlumiFrame_xPos, CCCaseAlumiFrame_yPos, CCCaseAlumiFrame_zPos), CCCaseAlumiFrame_Logical, "CCCaseAlumiFrame", LocalWorld_Logical, false, 0, surfaceCheck);
  ///// CC Case Dodai B /////////////////////////
  G4double CCCaseDodaiB_xSize = 194.0*mm;
  G4double CCCaseDodaiB_ySize = 190.0*mm;
  G4double CCCaseDodaiB_zSize = 10.0*mm;
  G4VSolid* CCCaseDodaiB_Solid = new G4Box("CCCaseDodaiB_Solid", CCCaseDodaiB_xSize*0.5, CCCaseDodaiB_ySize*0.5, CCCaseDodaiB_zSize*0.5);
  G4LogicalVolume* CCCaseDodaiB_Logical = new G4LogicalVolume(CCCaseDodaiB_Solid, aluminium, "CCCaseDodaiB_Logical");
  G4double CCCaseDodaiB_xPos = 0.0*mm;
  G4double CCCaseDodaiB_yPos = 0.0*mm;
  G4double CCCaseDodaiB_zPos = -CCCaseFrontBoard_zSize - 194.0*mm - CCCaseDodaiB_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(CCCaseDodaiB_xPos, CCCaseDodaiB_yPos, CCCaseDodaiB_zPos), CCCaseDodaiB_Logical, "CCCaseDodaiB", LocalWorld_Logical, false, 0, surfaceCheck);
  ///// CCCaseRearBoard /////////////////////////
  G4double CCCaseRearBoard_xSize = 206.0*mm;
  G4double CCCaseRearBoard_ySize = 190.0*mm;
  G4double CCCaseRearBoard_zSize = 1.0*mm;
  G4VSolid* CCCaseRearBoard_Solid = new G4Box("CCCaseRearBoard_Solid", CCCaseRearBoard_xSize*0.5, CCCaseRearBoard_ySize*0.5, CCCaseRearBoard_zSize*0.5);
  G4LogicalVolume* CCCaseRearBoard_Logical = new G4LogicalVolume(CCCaseRearBoard_Solid, aluminium, "CCCaseRearBoard_Logical");
  G4double CCCaseRearBoard_xPos = 0.0*mm;
  G4double CCCaseRearBoard_yPos = 0.0*mm;
  G4double CCCaseRearBoard_zPos = -CCCaseFrontBoard_zSize - 310.0*mm - CCCaseRearBoard_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(CCCaseRearBoard_xPos, CCCaseRearBoard_yPos, CCCaseRearBoard_zPos), CCCaseRearBoard_Logical, "CCCaseRearBoard", LocalWorld_Logical, false, 0, surfaceCheck);
  ///// CC Case Dodai A /////////////////////////
  G4double CCCaseDodaiA_xSize = 6.0*mm;
  G4double CCCaseDodaiA_ySize = 190.0*mm;
  G4double CCCaseDodaiA_zSize = 310.0*mm;
  G4VSolid* CCCaseDodaiA_Solid = new G4Box("CCCaseDodaiA_Solid", CCCaseDodaiA_xSize*0.5, CCCaseDodaiA_ySize*0.5, CCCaseDodaiA_zSize*0.5);
  G4LogicalVolume* CCCaseDodaiA_Logical = new G4LogicalVolume(CCCaseDodaiA_Solid, aluminium, "CCCaseDodaiA_Logical");
  G4double CCCaseDodaiA_xPos = -97.0*mm - CCCaseDodaiA_xSize*0.5;
  G4double CCCaseDodaiA_yPos = 0.0*mm;
  G4double CCCaseDodaiA_zPos = -CCCaseFrontBoard_zSize - CCCaseDodaiA_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(CCCaseDodaiA_xPos, CCCaseDodaiA_yPos, CCCaseDodaiA_zPos), CCCaseDodaiA_Logical, "CCCaseDodaiA", LocalWorld_Logical, false, 0, surfaceCheck);
  ///// CC Case MIO Board Base /////////////////////////
  G4double CCCaseMIOBoardBase_xSize = 6.0*mm;
  G4double CCCaseMIOBoardBase_ySize = 190.0*mm;
  G4double CCCaseMIOBoardBase_zSize = 310.0*mm;
  G4VSolid* CCCaseMIOBoardBase_Solid = new G4Box("CCCaseMIOBoardBase_Solid", CCCaseMIOBoardBase_xSize*0.5, CCCaseMIOBoardBase_ySize*0.5, CCCaseMIOBoardBase_zSize*0.5);
  G4LogicalVolume* CCCaseMIOBoardBase_Logical = new G4LogicalVolume(CCCaseMIOBoardBase_Solid, aluminium, "CCCaseMIOBoardBase_Logical");
  G4double CCCaseMIOBoardBase_xPos = 97.0*mm + CCCaseMIOBoardBase_xSize*0.5;
  G4double CCCaseMIOBoardBase_yPos = 0.0*mm;
  G4double CCCaseMIOBoardBase_zPos = -CCCaseFrontBoard_zSize - CCCaseMIOBoardBase_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(CCCaseMIOBoardBase_xPos, CCCaseMIOBoardBase_yPos, CCCaseMIOBoardBase_zPos), CCCaseMIOBoardBase_Logical, "CCCaseMIOBoardBase", LocalWorld_Logical, false, 0, surfaceCheck);
  ///// CCCaseSideBoardA /////////////////////////
  G4double CCCaseSideBoardA_xSize = 206.0*mm;
  G4double CCCaseSideBoardA_ySize = 1.0*mm;
  G4double CCCaseSideBoardA_zSize = 312.0*mm;
  G4VSolid* CCCaseSideBoardA_Solid = new G4Box("CCCaseSideBoardA_Solid", CCCaseSideBoardA_xSize*0.5, CCCaseSideBoardA_ySize*0.5, CCCaseSideBoardA_zSize*0.5);
  G4LogicalVolume* CCCaseSideBoardA_Logical = new G4LogicalVolume(CCCaseSideBoardA_Solid, aluminium, "CCCaseSideBoardA_Logical");
  G4double CCCaseSideBoardA_xPos = 0.0*mm;
  G4double CCCaseSideBoardA_yPos = -95.0*mm - CCCaseSideBoardA_ySize*0.5;
  G4double CCCaseSideBoardA_zPos = -CCCaseSideBoardA_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(CCCaseSideBoardA_xPos, CCCaseSideBoardA_yPos, CCCaseSideBoardA_zPos), CCCaseSideBoardA_Logical, "CCCaseSideBoardA", LocalWorld_Logical, false, 0, surfaceCheck);
  ///// CCCaseSideBoardB /////////////////////////
  G4double CCCaseSideBoardB_xSize = 206.0*mm;
  G4double CCCaseSideBoardB_ySize = 1.0*mm;
  G4double CCCaseSideBoardB_zSize = 312.0*mm;
  G4VSolid* CCCaseSideBoardB_Solid = new G4Box("CCCaseSideBoardB_Solid", CCCaseSideBoardB_xSize*0.5, CCCaseSideBoardB_ySize*0.5, CCCaseSideBoardB_zSize*0.5);
  G4LogicalVolume* CCCaseSideBoardB_Logical = new G4LogicalVolume(CCCaseSideBoardB_Solid, aluminium, "CCCaseSideBoardB_Logical");
  G4double CCCaseSideBoardB_xPos = 0.0*mm;
  G4double CCCaseSideBoardB_yPos = 95.0*mm + CCCaseSideBoardB_ySize*0.5;
  G4double CCCaseSideBoardB_zPos = -CCCaseSideBoardB_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(CCCaseSideBoardB_xPos, CCCaseSideBoardB_yPos, CCCaseSideBoardB_zPos), CCCaseSideBoardB_Logical, "CCCaseSideBoardB", LocalWorld_Logical, false, 0, surfaceCheck);


  // Base Frame
  G4double BaseFrameBody_xSize = 165.0*mm;
  G4double BaseFrameBody_ySize = 126.0*mm;
  G4double BaseFrameBody_zSize = 64.9*mm;
  G4VSolid* BaseFrameBody_Solid = new G4Box("BaseFrameBody_Solid", BaseFrameBody_xSize*0.5, BaseFrameBody_ySize*0.5, BaseFrameBody_zSize*0.5);
  G4double BaseFrameHole1_xSize = 151.0*mm;
  G4double BaseFrameHole1_ySize = 126.0*mm;
  G4double BaseFrameHole1_zSize = 53.0*mm;
  G4VSolid* BaseFrameHole1_Solid = new G4Box("BaseFrameHole1_Solid", BaseFrameHole1_xSize*0.5, BaseFrameHole1_ySize*0.5 + margin, BaseFrameHole1_zSize*0.5);
  G4double BaseFrameHole2_xSize = 127.0*mm;
  G4double BaseFrameHole2_ySize = 126.0*mm;
  G4double BaseFrameHole2_zSize = 11.7*mm;
  G4VSolid* BaseFrameHole2_Solid = new G4Box("BaseFrameHole2_Solid", BaseFrameHole2_xSize*0.5, BaseFrameHole2_ySize*0.5 + margin, BaseFrameHole2_zSize*0.5 + margin);
  G4VSolid* BaseFrame_Solid = BaseFrameBody_Solid;
  G4double BaseFrameHole1_xPos = 0.0*mm;
  G4double BaseFrameHole1_yPos = 0.0*mm;
  G4double BaseFrameHole1_zPos = BaseFrameBody_zSize*0.5 - 0.2*mm - BaseFrameHole1_zSize*0.5;
  BaseFrame_Solid = new G4SubtractionSolid("BaseFrame_Solid", BaseFrame_Solid, BaseFrameHole1_Solid, 0, G4ThreeVector(BaseFrameHole1_xPos, BaseFrameHole1_yPos, BaseFrameHole1_zPos));
  G4double BaseFrameHole2_xPos = 0.0*mm;
  G4double BaseFrameHole2_yPos = 0.0*mm;
  G4double BaseFrameHole2_zPos = -BaseFrameBody_zSize*0.5 + BaseFrameHole2_zSize*0.5;
  BaseFrame_Solid = new G4SubtractionSolid("BaseFrame_Solid", BaseFrame_Solid, BaseFrameHole2_Solid, 0, G4ThreeVector(BaseFrameHole2_xPos, BaseFrameHole2_yPos, BaseFrameHole2_zPos));
  G4LogicalVolume* BaseFrame_Logical = new G4LogicalVolume(BaseFrame_Solid, aluminium, "BaseFrame_Logical");
  G4double BaseFrame_xPos = 0.0*mm;
  G4double BaseFrame_yPos = 0.0*mm;
  G4double BaseFrame_zPos = CCCaseDodaiB_zPos + CCCaseDodaiB_zSize*0.5 + BaseFrameBody_zSize*0.5;
  // G4double BaseFrame_zPos = ComptonCamera_zPos - 59.9*mm - BaseFrameBody_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(BaseFrame_xPos, BaseFrame_yPos, BaseFrame_zPos), BaseFrame_Logical, "BaseFrame", LocalWorld_Logical, false, 0, surfaceCheck);


  // Compton Camera //////////////////
  GeometryComptonCamera* ComptonCamera_Geometry = new GeometryComptonCamera();
  G4LogicalVolume* ComptonCamera_Logical = ComptonCamera_Geometry->Construct();
  G4double ComptonCamera_xPos = 0.0*mm;
  G4double ComptonCamera_yPos = 0.0*mm;
  G4double ComptonCamera_zPos = BaseFrame_zPos + BaseFrameBody_zSize*0.5 + 59.9*mm;
  // G4double ComptonCamera_zPos = -109.9*mm;
  new G4PVPlacement(0, G4ThreeVector(ComptonCamera_xPos, ComptonCamera_yPos, ComptonCamera_zPos), ComptonCamera_Logical, "ComptonCamera", LocalWorld_Logical, false, 0, surfaceCheck);

  return LocalWorld_Logical;
}
