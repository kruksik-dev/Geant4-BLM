#include "DetectorConstruction.hh"
#include "G4PVPlacement.hh" 
#include "G4SystemOfUnits.hh" 
#include "G4VisAttributes.hh"
#include "G4Material.hh"
#include "G4Box.hh" 
#include "G4Tubs.hh" 
#include "G4ThreeVector.hh" 
#include "globals.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4SDManager.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4NistManager.hh"
#include "G4SubtractionSolid.hh"

DetectorConstruction::DetectorConstruction()
{
    worldLogic = 0L;
    vaccum = 0L;
    OutterTubeLogVol=0L;
    InnerTubeLogVol = 0L;
    MagnetLogVol = 0L;
    steel = 0L;
    air =0L;
    allu=0L;
    alluboxLogVol=0L;
    airboxLogVol=0L;
    DetLogVol=0L;
    man = G4NistManager::Instance();
}

DetectorConstruction::~DetectorConstruction() 
{
    if(worldLogic != 0L)
        delete worldLogic;

    if (OutterTubeLogVol != 0L)
        delete OutterTubeLogVol;

    if (MagnetLogVol != 0L)
        delete MagnetLogVol;
}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
    DeffAllMats();
    G4VPhysicalVolume *worldPhys = ConstructWorld();
    ConstructOutterTube();
    ConstructInnerTube();
    ConstructMagnet();
    ConstructDetector();

    return worldPhys;
}

void DetectorConstruction::DeffAllMats()
{
    vaccum = new G4Material("GalacticVacuum", 1., 1.01 * g / mole,
                                        CLHEP::universe_mean_density,
                                        kStateGas, 3.e-18 * pascal, 2.73 * kelvin);

    steel = man->FindOrBuildMaterial("G4_STAINLESS-STEEL");
    air = man->FindOrBuildMaterial("G4_AIR");
    allu = man->FindOrBuildMaterial("G4_Al");
    ppy = man->FindOrBuildMaterial("G4_POLYPROPYLENE");
}

G4VPhysicalVolume *DetectorConstruction::ConstructWorld()
{
    G4double worldX = 5*m;
    G4double worldY = 5*m;
    G4double worldZ = 5*m;
    G4Box* worldSolid = new G4Box("worldSolid",worldX,worldY,worldZ);
                           
    worldLogic = new G4LogicalVolume(worldSolid, air,"worldLogic", 0,0,0);
    worldLogic->SetVisAttributes(G4VisAttributes::Invisible);
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLogic, "world", 0, false, 0);
    return worldPhys;
}

void DetectorConstruction::ConstructOutterTube()
{
    G4double radiusMin = 0.92 * cm;
    G4double radiusMax = 1 * cm;
    G4double length = 1.3025 * m;

    G4Tubs *OutterTube = new G4Tubs("OutterTube", radiusMin, radiusMax, length / 2., 0 * deg, 360 * deg);
    OutterTubeLogVol = new G4LogicalVolume(OutterTube, steel, "OutterTubeLogVol");

    G4VisAttributes *OutterTubeVisAtt = new G4VisAttributes(G4Colour::Blue());
    OutterTubeVisAtt->SetForceAuxEdgeVisible(true);
    OutterTubeVisAtt->SetForceSolid(false);
    OutterTubeLogVol->SetVisAttributes(OutterTubeVisAtt);

    G4ThreeVector pos(0, 0, 0);
 
    new G4PVPlacement(0, pos, OutterTubeLogVol, "OutterTubePhys", worldLogic, 0, 0);


}

void DetectorConstruction::ConstructInnerTube()
{
    G4double radiusMin = 0.0 * cm;
    G4double radiusMax = 0.92 * cm;
    G4double length = 1.3025 * m;

    G4Tubs *InnerTube = new G4Tubs("InnerTube", radiusMin, radiusMax, length / 2., 0 * deg, 360 * deg);
    InnerTubeLogVol = new G4LogicalVolume(InnerTube, vaccum, "InnerTubeLogVol");

    G4VisAttributes *InnerTubeVisAtt = new G4VisAttributes(G4Colour::Red());
    InnerTubeVisAtt->SetForceAuxEdgeVisible(false);
    InnerTubeVisAtt->SetForceSolid(false);
    InnerTubeLogVol->SetVisAttributes(InnerTubeVisAtt);

    G4ThreeVector pos(0, 0, 0);
    new G4PVPlacement(0, pos, InnerTubeLogVol, "InnerTubePhys", OutterTubeLogVol, 0, 0);
}

void DetectorConstruction::ConstructMagnet()
{
    G4double radiusMin = 1* cm;
    G4double radiusMax = 10 * cm;
    G4double length = 10 * cm;
    G4Tubs *MagnetTube = new G4Tubs("InnerTube", radiusMin, radiusMax, length / 2., 0 * deg, 360 * deg);

    MagnetLogVol = new G4LogicalVolume(MagnetTube , steel, "MagnetLogVol");

    G4VisAttributes *MagnetVisAtt = new G4VisAttributes(G4Colour::Green());
    MagnetVisAtt->SetForceAuxEdgeVisible(true);
    MagnetVisAtt->SetForceSolid(true);
    MagnetLogVol->SetVisAttributes(MagnetVisAtt);

    G4ThreeVector pos(0, 0, 248.75);
    new G4PVPlacement(0, pos, MagnetLogVol, "MagnetLogVolPhys", worldLogic, 0, 0,1);

}

void DetectorConstruction::ConstructDetector()
{

    G4double alluboxX = 10.3 * cm;
    G4double alluboxY = 3 * cm;
    G4double alluboxZ = 3 * cm;

    G4Box *allubox = new G4Box("allubox", alluboxX, alluboxY, alluboxZ);
    alluboxLogVol = new G4LogicalVolume(allubox, allu, "alluboxLogVol");

    G4VisAttributes *alluboxVisAtt = new G4VisAttributes(G4Colour(0.8, 0.3, 0.3, 1.));
    alluboxVisAtt->SetForceAuxEdgeVisible(true);
    alluboxVisAtt->SetForceSolid(false);
    alluboxLogVol->SetVisAttributes(alluboxVisAtt);

    G4double airgapboxX = 10 * cm;
    G4double airgapboxY = 2.7 * cm;
    G4double airgapboxZ = 2.7 * cm;

    G4Box *airbox = new G4Box("airbox", airgapboxX, airgapboxY, airgapboxZ);
    airboxLogVol = new G4LogicalVolume(airbox, air, "airboxLogVol");

    G4VisAttributes *airboxVisAtt = new G4VisAttributes(G4Colour(0.8, 0.3, 0.3, 1.));
    airboxVisAtt->SetForceAuxEdgeVisible(true);
    airboxVisAtt->SetForceSolid(false);
    airboxLogVol->SetVisAttributes(airboxVisAtt);

    G4ThreeVector pos(0, 50, 428.75);
    new G4PVPlacement(0, pos, alluboxLogVol, "alluPhys", worldLogic, 0, 0);
    new G4PVPlacement(0, G4ThreeVector(0,0,0), airboxLogVol, "airPhys", alluboxLogVol, 0, 0);

    G4ThreeVector pos2(0, -50, 428.75);
    new G4PVPlacement(0, pos2, alluboxLogVol, "alluPhys", worldLogic, 0, 0);
    new G4PVPlacement(0, G4ThreeVector(0, 0, 0), airboxLogVol, "airPhys", alluboxLogVol, 0, 0);

    G4double radiusMin = 0.0 * cm;
    G4double radiusMax = 0.2 * cm;
    G4double length = 5 * cm;

    G4Tubs *Det = new G4Tubs("Det", radiusMin, radiusMax, length / 2., 0 * deg, 360 * deg);
    DetLogVol = new G4LogicalVolume(Det, ppy, "Det");

    G4VisAttributes *DetVisAtt = new G4VisAttributes(G4Colour::Blue());
    DetVisAtt->SetForceAuxEdgeVisible(true);
    DetVisAtt->SetForceSolid(true);
    DetLogVol->SetVisAttributes(DetVisAtt);

    G4RotationMatrix *zRot = new G4RotationMatrix;
    zRot->rotateY(90 * deg);
    new G4PVPlacement(zRot, G4ThreeVector(0, 0, 0), DetLogVol, "airPhys", airboxLogVol, 0, 0);
}
