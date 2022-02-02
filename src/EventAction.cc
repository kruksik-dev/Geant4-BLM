
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "PlaHit.hh"
#include "RunAction.hh"





EventAction::EventAction()
{
	outputFile = OutputRoot::GetInstance();
	outputFile->CreateFile("PlasticOutput.root");
	output.open("outputlogs.csv");
}
 
EventAction::~EventAction()
{
	outputFile->SaveOutput();
	output.close();
}


void EventAction::BeginOfEventAction(const G4Event* anEvent)
{

}
 

void EventAction::EndOfEventAction(const G4Event* anEvent)
{
	
	G4HCofThisEvent *hitsCollOfThisEvent = anEvent->GetHCofThisEvent();
    	if(!hitsCollOfThisEvent)
       	 return;

	G4SDManager* SDmanager = G4SDManager::GetSDMpointer();
	G4int collID = SDmanager->GetCollectionID("PlasticSensitiveDet/eDepo");

	G4THitsMap<G4double> *myPassMap = dynamic_cast<G4THitsMap<G4double> *>(hitsCollOfThisEvent->GetHC(collID));
	G4int eventID = anEvent->GetEventID();

	int limit = 2;
	for (int i; i != limit; ++i)
	{
		if ((*myPassMap)[i] != 0L)
		{
			G4double Edepo = *((*myPassMap)[i]);
			std::cout << "Primitve" << " " << eventID << "  " << Edepo << std::endl;
			
		}
	}

	G4int plasticId = SDmanager->GetCollectionID("PSD/eDep");
	PlasticHitsCollection *plasticHC = (PlasticHitsCollection *)(hitsCollOfThisEvent->GetHC(plasticId));




	
	int eventId = anEvent -> GetEventID();
	if(eventId%10000 == 0){
		std::cout << "Currently run " << eventId << " particle from pool" << std::endl;
	}
	

	G4int nrOfDetectors = plasticHC->entries();
	for(G4int i=0; i!=nrOfDetectors;i++){
		G4int moduleIndex = (*plasticHC)[i] ->GetCopyNr();
		G4double energyDep = (*plasticHC)[i] -> GetEdep();
		G4String volumeName = (*plasticHC)[i]->GetVolumeName();
		G4String particleName = (*plasticHC)[i]->GetParticleName();
		std::cout << eventId << " " << moduleIndex << " " << energyDep / keV << " " << volumeName << " " << particleName << std::endl;
		//output << eventId <<" " <<  moduleIndex << " " << energyDep / keV << " " << trackLength << " " << volumeName << " " << particleName << std::endl;
		output << eventId << "," << moduleIndex << "," << energyDep / keV << "," << volumeName << "," << particleName << std::endl;
		outputFile->AddPlasticHit(eventId, moduleIndex, energyDep /keV );
	}
}



