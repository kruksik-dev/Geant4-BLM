#include "G4String.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"


#include "PhysicsList.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"



int main(int argc, char** argv)
{

  G4RunManager * runManager = new G4RunManager; 
  runManager->SetUserInitialization(new DetectorConstruction());
  runManager->SetUserInitialization(new PhysicsList());
  runManager->SetUserAction(new PrimaryGeneratorAction());
  runManager->SetUserAction(new RunAction());
  runManager->SetUserAction(new EventAction());
  runManager->SetUserAction(new SteppingAction());
  runManager->Initialize();

  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  
  //wizualizacja 
  //G4VisManager* visManager = new G4VisExecutive;
  //visManager->Initialize();  
  

  //ui - terminal do wpisywania komend
  //G4UIExecutive* ui = new G4UIExecutive(argc, argv);
  
  
  if(argc == 1)
      UImanager->ApplyCommand("/control/execute ../vis.mac");
  else
  {
     G4String filename = argv[1];
     UImanager->ApplyCommand("/control/execute " + filename);
   }
  
  //ui->SessionStart();  
  delete runManager;
  return 0;
}


