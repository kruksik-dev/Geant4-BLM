#include "OutputRoot.hh"

OutputRoot::OutputRoot()
{
    rootManager = G4RootAnalysisManager::Instance();

    rootManager->SetFirstNtupleId(0);
}

void OutputRoot::CreateFile(G4String filename)
{
    rootManager->OpenFile(filename);
    PlasticDetTupleId = 0;
    CreatePlasticTuple();
}
void OutputRoot::SaveOutput()
{
    rootManager->Write();
    rootManager->CloseFile();
}

void OutputRoot::CreatePlasticTuple()
{
    rootManager->CreateNtuple("Plastic_Info", "Energy deposit in Plastic");
    rootManager->CreateNtupleIColumn("eventId");
    rootManager->CreateNtupleIColumn("detectorId");
    rootManager->CreateNtupleDColumn("energyDep");
    rootManager->FinishNtuple();
}

void OutputRoot::AddPlasticHit(int eventId, int detectorId, double enDep)
{
    int cloId = 0;
    rootManager->FillNtupleIColumn(PlasticDetTupleId, cloId, eventId);
    rootManager->FillNtupleIColumn(PlasticDetTupleId, ++cloId, detectorId);
    rootManager->FillNtupleDColumn(PlasticDetTupleId, ++cloId, enDep);
    rootManager->AddNtupleRow(PlasticDetTupleId);
}
OutputRoot *OutputRoot::instance = 0;
