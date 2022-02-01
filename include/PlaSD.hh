
#ifndef PlaSD_h
#define PlaSD_h 1

#include "G4VSensitiveDetector.hh"
#include "PlaHit.hh"
#include <vector>

class G4Step;
class G4HCofThisEvent;

class PlasticSD : public G4VSensitiveDetector
{
public:
    PlasticSD(const G4String &name,
          const G4String &hitsCollectionName,
          G4int depthVal);
    virtual ~PlasticSD();

    // methods from base class
    virtual void Initialize(G4HCofThisEvent *hitCollection);
    virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory *history);

private:
    PlasticHitsCollection *hitsCollection;
    G4int depth;

    G4double GetEnergyDeposit(G4Step *step);
    G4int GetCopyNr(G4Step *step);
    G4String GetVolumeName(G4Step *step);
    G4String GetParticleName(G4Step *step);
  
};

#endif
