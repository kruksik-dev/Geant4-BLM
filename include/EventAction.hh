
#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include <fstream>
#include "OutputRoot.hh"


class EventAction : public G4UserEventAction
{
  public:
    EventAction();
    virtual ~EventAction();
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);
	void CountandPrintEff();
    
  private:
	
    OutputRoot* outputFile;
    std::ofstream output;
};

#endif
