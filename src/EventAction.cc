
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
	
	//SteppingAction::nrOfSec = 0;

	G4HCofThisEvent *hitsCollOfThisEvent = anEvent->GetHCofThisEvent();
	if (!hitsCollOfThisEvent){
		return;
	}

	G4SDManager * SDmanager = G4SDManager::GetSDMpointer();
	G4int plasticId = SDmanager->GetCollectionID("PSD/eDep");
	//std::cout << plasticId << std::endl;

	//G4THitsMap<G4double> *PlasticHitsCollection = static_cast<G4THitsMap<G4double> *>(hitsCollOfThisEvent->GetHC(plasticId));
	PlasticHitsCollection *plasticHC = (PlasticHitsCollection *)(hitsCollOfThisEvent->GetHC(plasticId));

	/*	
	std::map<G4int, G4double *> *PlasticColMap = PlasticHitsCollection->GetMap();
	std::map<G4int,G4double*>::iterator itr;
	for (itr = PlasticColMap->begin(); itr != PlasticColMap ->end(); itr++)
	{
		std::cout << (itr-> first) << " " << (*itr->second)/keV << std::endl;
	}

	 // #dodatkowe : for (auto it : *PlasticHitsCollection -> GetMap()){
		std::cout<<(it.first) << " " << *(it.second) << std::endl;
	}

	*/
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



