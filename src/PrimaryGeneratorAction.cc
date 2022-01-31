#include "PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "Randomize.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction()
{
    particleGun = new G4ParticleGun();
    particleTable = G4ParticleTable::GetParticleTable();
	  SetUpDefault();
	

}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

void PrimaryGeneratorAction::SetUpDefault()

{

	
	G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
	particleGun->SetParticleDefinition(particle);
	particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,0.0*cm));
	particleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
	particleGun->SetParticleEnergy(500.0*keV);
	


}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{	
    GenerateNeutronIncident(anEvent);
    
}	

void PrimaryGeneratorAction::GenerateNeutronIncident(G4Event* anEvent)
{
 
	G4ParticleDefinition* particle = particleTable->FindParticle("e-");
  //G4ParticleDefinition *particle = particleTable->FindParticle("e-");
  particleGun->SetParticleDefinition(particle);
  //particleGun->SetParticlePosition(G4ThreeVector(0.0 * m, 0.0 * m, -10.4 * m));
  particleGun->SetParticlePosition(G4ThreeVector(0.0 * m, -60.0 * mm, 9.2 * m));
  particleGun->SetParticleMomentumDirection(G4ThreeVector(0.0, 0., 1));
  //particleGun->SetParticleMomentumDirection(G4ThreeVector(0.001, 0., 1));
  particleGun->SetParticleEnergy(1200.0 * keV);
  particleGun->GeneratePrimaryVertex(anEvent);
}

G4ThreeVector PrimaryGeneratorAction::GenerateHalfIsotropicDirection()
{
  G4double randomPhi = G4UniformRand() * 2. * M_PI;
  G4double randomCosTheta = G4UniformRand() * 2. - 1.;
  G4double randomTheta = acos(randomCosTheta);
  G4double x = sin(randomTheta) * sin(randomPhi);
  G4double y = sin(randomTheta) * cos(randomPhi);
  G4double z = cos(randomTheta);
  return G4ThreeVector(x, y, z);
}


