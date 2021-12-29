#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4NistManager.hh"  
#include "G4Material.hh" 


class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    DetectorConstruction(); //konstuktor
    virtual ~DetectorConstruction(); //destruktor
    void DeffAllMats();
    virtual G4VPhysicalVolume* Construct();
    

  private : 
    G4LogicalVolume *worldLogic;
    G4LogicalVolume *OutterTubeLogVol;
    G4LogicalVolume *InnerTubeLogVol;
    G4LogicalVolume *MagnetLogVol;
    G4LogicalVolume *alluboxLogVol;
    G4LogicalVolume *airboxLogVol;
    G4LogicalVolume * DetLogVol;
    G4VPhysicalVolume *ConstructWorld();

    G4Material *air;
    G4Material *vaccum;
    G4Material *steel;
    G4Material *allu;
    G4Material *ppy;
    G4NistManager *man;
    void ConstructOutterTube();
    void ConstructInnerTube();
    void ConstructMagnet();
    void ConstructDetector();
};

#endif
