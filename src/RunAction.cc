
#include "RunAction.hh"
#include "G4Run.hh"
#include "SteppingAction.hh"

RunAction::RunAction(): G4UserRunAction()
{ 
    timer = new G4Timer;
}


RunAction::~RunAction()
{
     delete timer;
}

void RunAction::BeginOfRunAction(const G4Run* run)
{ 
    G4cout << "### Run " << run->GetRunID() << " start, "<< G4endl;
    timer-> Start();


}


void RunAction::EndOfRunAction(const G4Run* run)
{
    timer -> Stop();
    G4cout << "number of event = " << run->GetNumberOfEvent() << " " << *timer << G4endl;
}



