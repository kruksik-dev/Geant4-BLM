#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();
    virtual void GeneratePrimaries(G4Event*);

  private:
		
    G4ParticleGun* particleGun;
    G4ParticleTable* particleTable;
    void GenerateNeutronIncident(G4Event *anEvent);
    G4ThreeVector GenerateHalfIsotropicDirection();
    void SetUpDefault();

};


#endif 

