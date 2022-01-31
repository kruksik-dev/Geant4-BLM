#include "PlaHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4VPhysicalVolume.hh"
#include <iomanip>

G4ThreadLocal G4Allocator<PlasticHit> *PlasticHitAllocator = 0;

PlasticHit::PlasticHit(G4int copyNrVal) : G4VHit()
{
    eDep = 0.;
    trackLength = 0.;
    copyNr = copyNrVal;
    volumeName = "";
    particleName = "";

}

PlasticHit::~PlasticHit(){}

PlasticHit::PlasticHit(const PlasticHit &right) : G4VHit()
{
    eDep = right.eDep;
    trackLength = right.trackLength;
    copyNr = right.copyNr;
    volumeName = right.volumeName;
    particleName = right.particleName;

}

const PlasticHit &PlasticHit::operator=(const PlasticHit &right)
{
    eDep = right.eDep;
    trackLength = right.trackLength;
    copyNr = right.copyNr;
    volumeName = right.volumeName;
    particleName = right.particleName;
    
    return *this;
}

G4int PlasticHit::operator==(const PlasticHit &right) const
{
    return (this == &right) ? 1 : 0;
}

void PlasticHit::Add(G4double energyDep, G4double trackLen, G4String volName, G4String partiName)
{
    eDep += energyDep;
    trackLength += trackLen;
    volumeName = volName;
    particleName = partiName;

}

G4double PlasticHit::GetEdep()
{
    return eDep;
}

G4double PlasticHit::GetTrackLength()
{
    return trackLength;
}

G4int PlasticHit::GetCopyNr()
{
    return copyNr;
}

G4String PlasticHit::GetVolumeName()
{
    return volumeName;
}
G4String PlasticHit::GetParticleName()
{
    return particleName;
}

