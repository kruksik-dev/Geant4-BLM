
#include "SteppingAction.hh"
#include "G4SteppingManager.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4String.hh"
#include <iostream>
#include "G4SystemOfUnits.hh"

SteppingAction::SteppingAction():G4UserSteppingAction()
{

}

SteppingAction::~SteppingAction() {}


void SteppingAction::UserSteppingAction(const G4Step* theStep)
{
    G4Track *theTrack = theStep->GetTrack();
    G4String volumeName = theTrack->GetVolume()->GetName();
    if (volumeName == "OutterTubePhys")
    {
        auto secondaries = theStep->GetSecondaryInCurrentStep();
        nrOfSec += secondaries->size();
       
    }

}

void SteppingAction::PrintStep(const G4Step* theStep)
{
    G4Track* theTrack = theStep->GetTrack();
    G4String processName = theStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    G4String particleName = theTrack->GetDefinition()->GetParticleName();
    G4double energy = theTrack->GetKineticEnergy();
    G4String volumeName = theTrack -> GetVolume()->GetName();
    G4double deltaEn = theStep ->GetDeltaEnergy();
    G4int trackID = theTrack->GetTrackID();

    std::cout << " TrackID : " << trackID
              << " particle : " << particleName
              << " process : " << processName
              << " part energy : " << energy / MeV
              << " delta en : " << deltaEn
              << " volume name : " << volumeName << std::endl;
}


int SteppingAction::nrOfSec=0;