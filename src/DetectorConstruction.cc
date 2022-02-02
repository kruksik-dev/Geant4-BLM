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
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4NistManager.hh"
#include "PlaSD.hh"


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
    allutubeLogVol=0L;
    airtubeLogVol=0L;
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
    ConstructSDandField();

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
    ppy = man->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
}

G4VPhysicalVolume *DetectorConstruction::ConstructWorld()
{
    G4double worldX = 15*m;
    G4double worldY = 15*m;
    G4double worldZ = 15*m;
    G4Box* worldSolid = new G4Box("worldSolid",worldX,worldY,worldZ);
                           
    worldLogic = new G4LogicalVolume(worldSolid, vaccum,"worldLogic", 0,0,0);
    worldLogic->SetVisAttributes(G4VisAttributes::Invisible);
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLogic, "world", 0, false, 0);
    return worldPhys;
}

void DetectorConstruction::ConstructOutterTube()
{
    G4double radiusMin = 0 * mm;
    G4double radiusMax = 20 * mm;
    G4double length = 10.5 * m;

    G4Tubs *OutterTube = new G4Tubs("OutterTube", radiusMin, radiusMax, length, 0 * deg, 360 * deg);
    OutterTubeLogVol = new G4LogicalVolume(OutterTube, steel, "OutterTubeLogVol");

    G4VisAttributes *OutterTubeVisAtt = new G4VisAttributes(G4Colour::Gray());
    OutterTubeVisAtt->SetForceAuxEdgeVisible(true);
    OutterTubeVisAtt->SetForceSolid(false);
    OutterTubeLogVol->SetVisAttributes(OutterTubeVisAtt);

    G4ThreeVector pos(0, 0, 0);
 
    new G4PVPlacement(0, pos, OutterTubeLogVol, "OutterTubePhys", worldLogic, 0, 0);


}

void DetectorConstruction::ConstructInnerTube()
{
    G4double radiusMin = 0.0 * mm;
    G4double radiusMax = 18.5* mm;
    G4double length = 10.5 * m;

    G4Tubs *InnerTube = new G4Tubs("InnerTube", radiusMin, radiusMax, length, 0 * deg, 360 * deg);
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
    G4double radiusMin = 20 * mm;
    G4double radiusMax = 200 * mm;
    G4double length = 50 * mm;
    G4Tubs *MagnetTube = new G4Tubs("InnerTube", radiusMin, radiusMax, length, 0 * deg, 360 * deg);

    MagnetLogVol = new G4LogicalVolume(MagnetTube , steel, "MagnetLogVol");

    G4VisAttributes *MagnetVisAtt = new G4VisAttributes(G4Colour(64, 83, 85, 1));
    MagnetVisAtt->SetForceAuxEdgeVisible(true);
    MagnetVisAtt->SetForceSolid(true);
    MagnetLogVol->SetVisAttributes(MagnetVisAtt);

    G4ThreeVector pos(0, 0, 8650);
    new G4PVPlacement(0, pos, MagnetLogVol, "MagnetLogVolPhys", worldLogic, 0, 0, 1);

}

void DetectorConstruction::ConstructDetector()
{
    G4double radiusMinoutter = 0 * cm;
    G4double radiusMaxoutter = 3 * cm;
    G4double radiusMininner = 0 * cm;
    G4double radiusMaxinner = 2.7 * cm;
    G4double lengthoutter = 10.3 * cm;
    G4double lengthinnter = 10 * cm;

    G4Tubs *allutube = new G4Tubs("InnerTube", radiusMinoutter, radiusMaxoutter, lengthoutter, 0 * deg, 360 * deg);
    allutubeLogVol = new G4LogicalVolume(allutube, allu, "allutubeLogVol");

    G4VisAttributes *allutubeVisAtt = new G4VisAttributes(G4Colour(0.8, 0.3, 0.3, 1.));
    allutubeVisAtt->SetForceAuxEdgeVisible(true);
    allutubeVisAtt->SetForceSolid(false);
    allutubeLogVol->SetVisAttributes(allutubeVisAtt);



    G4Tubs *airtube = new G4Tubs("InnerTube", radiusMininner, radiusMaxinner, lengthinnter, 0 * deg, 360 * deg);
    airtubeLogVol = new G4LogicalVolume(airtube, air, "airtubeLogVol");

    G4VisAttributes *airtubeVisAtt = new G4VisAttributes(G4Colour(0.8, 0.3, 0.3, 1.));
    airtubeVisAtt->SetForceAuxEdgeVisible(false);
    airtubeVisAtt->SetForceSolid(false);
    airtubeLogVol->SetVisAttributes(airtubeVisAtt);
    new G4PVPlacement(0, G4ThreeVector(0, 0, 0), airtubeLogVol, "airPhys", allutubeLogVol, 0, 0);



    G4double radiusMin = 0.0 * cm;
    G4double radiusMax = 0.4 * cm;
    G4double length = 10 * cm;

    G4Tubs *Det = new G4Tubs("Det", radiusMin, radiusMax, length, 0 * deg, 360 * deg);
    DetLogVol = new G4LogicalVolume(Det, ppy, "Det");

    G4VisAttributes *DetVisAtt = new G4VisAttributes(G4Colour::Blue());
    DetVisAtt->SetForceAuxEdgeVisible(true);
    DetVisAtt->SetForceSolid(true);
    DetLogVol->SetVisAttributes(DetVisAtt);

    new G4PVPlacement(0, G4ThreeVector(0, 0, 0), DetLogVol, "PlasticPhys", airtubeLogVol, 0, 0);

    G4RotationMatrix *zRot = new G4RotationMatrix;
    zRot->rotateY(90 * deg);

     G4ThreeVector pos(0, 60, 9200);
     G4ThreeVector pos2(0, -60, 9200);

    new G4PVPlacement(zRot, pos, allutubeLogVol, "alluPhys", worldLogic, 0, 0);
    new G4PVPlacement(zRot, pos2, allutubeLogVol, "alluPhys", worldLogic, 0, 1);
}

void DetectorConstruction::ConstructSDandField()
{
    
    G4MultiFunctionalDetector *detector = new G4MultiFunctionalDetector("PlasticSensitiveDet");
    G4int depth = 2;
    G4VPrimitiveScorer *energyDepScorer = new G4PSEnergyDeposit("eDepo", depth);
    detector->RegisterPrimitive(energyDepScorer);
    DetLogVol->SetSensitiveDetector(detector);
    G4SDManager *SDmanager = G4SDManager::GetSDMpointer();
    SDmanager->AddNewDetector(detector);
    

    PlasticSD *PSD = new PlasticSD("PSD", "eDep", 2);
    //G4SDManager *SDmanager = G4SDManager::GetSDMpointer();
    SDmanager->AddNewDetector(PSD);
    DetLogVol->SetSensitiveDetector(PSD);
}