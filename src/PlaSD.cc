
#include "PlaSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4Track.hh"

PlasticSD::PlasticSD(const G4String &name,
             const G4String &hitsCollectionName,
             G4int depthVal) : G4VSensitiveDetector(name)
{
    collectionName.insert(hitsCollectionName);
    hitsCollection = 0L;
    depth = depthVal;
}

PlasticSD::~PlasticSD()
{
}

void PlasticSD::Initialize(G4HCofThisEvent *hce)
{
    hitsCollection = new PlasticHitsCollection(SensitiveDetectorName, collectionName[0]);
    //last - check

    auto hitsCollId = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    hce->AddHitsCollection(hitsCollId, hitsCollection);
}

G4bool PlasticSD::ProcessHits(G4Step *step, G4TouchableHistory *)
{
    G4double edep = GetEnergyDeposit(step);
    G4int copyNr = GetCopyNr(step);
    G4String volumename = GetVolumeName(step);
    G4String particlename = GetParticleName(step);


    if (edep == 0.)
        return false;

    G4int hitsNr = hitsCollection->entries();
    G4bool moduleAlreadyHit = false;
    for (G4int i = 0; i < hitsNr; i++)
    {
        G4int moduleCopyNr = (*hitsCollection)[i]->GetCopyNr();
        if (copyNr == moduleCopyNr)
        {
            (*hitsCollection)[i]->Add(edep, volumename, particlename);
            moduleAlreadyHit = true;
            break;
        }
    }

    if (!moduleAlreadyHit)
    {
        PlasticHit *aHit = new PlasticHit(copyNr);
        aHit->Add(edep, volumename, particlename);
        hitsCollection->insert(aHit);
    }
    return true;
}

G4double PlasticSD::GetEnergyDeposit(G4Step *step)
{
    return step->GetTotalEnergyDeposit();
}


G4int PlasticSD::GetCopyNr(G4Step *step)
{
    G4int voulmeNr =
        step->GetPreStepPoint()->GetTouchable()->GetCopyNumber(depth);
    return voulmeNr;
}

G4String PlasticSD::GetVolumeName(G4Step *step)
{
    G4Track *theTrack = step->GetTrack();
    G4String volumeName = theTrack->GetVolume()->GetName();
    return volumeName;
}

G4String PlasticSD::GetParticleName(G4Step *step)
{
    G4Track *theTrack = step->GetTrack();
    G4String particlename = theTrack->GetDefinition()->GetParticleName();
    return particlename;
}


