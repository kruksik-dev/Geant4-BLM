
#ifndef PlaHit_h
#define PlaHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Threading.hh"


// Hit class for plastic scintillator

class PlasticHit : public G4VHit
{
public:
    PlasticHit(G4int copyNrVal);
    PlasticHit(const PlasticHit &);
    virtual ~PlasticHit();

    // operators
    const PlasticHit &operator=(const PlasticHit &);
    G4int operator==(const PlasticHit &) const;

    inline void *operator new(size_t);
    inline void operator delete(void *);

    // methods to handle data
    void Add(G4double energyDep, G4double trackLen, G4String volName, G4String partiName);

    // get methods
    G4double GetEdep();
    G4double GetTrackLength();
    G4int GetCopyNr();
    G4String GetVolumeName();
    G4String GetParticleName();
   

private:
    G4double eDep;        ///< Energy deposit in the sensitive volume
    G4double trackLength; ///< Track length in the  sensitive volume
    G4int copyNr;
    G4String volumeName;
    G4String particleName;
    
};

using PlasticHitsCollection = G4THitsCollection<PlasticHit>;
extern G4ThreadLocal G4Allocator<PlasticHit> *PlasticHitAllocator;

inline void *PlasticHit::operator new(size_t)
{
    if (!PlasticHitAllocator)
    {
        PlasticHitAllocator = new G4Allocator<PlasticHit>;
    }
    void *hit;
    hit = (void *)PlasticHitAllocator->MallocSingle();
    return hit;
}

inline void PlasticHit::operator delete(void *hit)
{
    if (!PlasticHitAllocator)
    {
        PlasticHitAllocator = new G4Allocator<PlasticHit>;
    }
    PlasticHitAllocator->FreeSingle((PlasticHit *)hit);
}

#endif