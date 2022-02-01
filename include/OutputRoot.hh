#ifndef OutputRoot_H
#define OutputRoot_H 1
#include "G4RootAnalysisManager.hh"

class OutputRoot
{
public:
    static OutputRoot *GetInstance()
    {
        if (instance)
            return instance;
        else
        {
            instance = new OutputRoot();
            return instance;
        }
    }
    void SaveOutput();
    void CreateFile(G4String filename);
    void AddPlasticHit(int eventId, int detectorId, double enDep);

private:
    OutputRoot();
    static OutputRoot *instance;
    G4RootAnalysisManager *rootManager;
    void CreatePlasticTuple();
    int PlasticDetTupleId;
};

#endif
