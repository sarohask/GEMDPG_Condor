
#include "TrGEMPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Geantino.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include <TMath.h>
#include <fstream>

TrGEMPrimaryGeneratorAction::TrGEMPrimaryGeneratorAction(char* partName_) 
	: partName(partName_)
	{
  	G4int n_particle = 1;
  	G4ParticleDefinition* particlen = G4ParticleTable::GetParticleTable()-> FindParticle(partName);

  	std::string temp = partName;
  	if (temp == "neutron") eneRange = 12;
  	else if (temp == "gamma") eneRange = 5;
  	else if (temp == "e-") eneRange = 5;
  	else if (temp == "e+") eneRange = 12;
  	else if (temp == "alpha") eneRange = 12;
  	else if (temp == "mu-") eneRange = 12;
  	else throw;

  	fParticleGun  = new G4ParticleGun(particlen,n_particle);
  	
	}

TrGEMPrimaryGeneratorAction::~TrGEMPrimaryGeneratorAction()
	{
  	delete fParticleGun;
	}

void TrGEMPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
	{
  	G4double xxx,yyy;
  	G4double primaryEne;

  	// set direction
  	// neutron
  	//Parallel Direction
  	fParticleGun->SetParticleMomentumDirection((G4ThreeVector(0.,0.08715574274,0.99619469809))); 

  	//set position  
  	G4double gX = G4UniformRand()*10.-5.;
  	G4double gY = G4UniformRand()*10.-5.;
  	fParticleGun->SetParticlePosition(G4ThreeVector(gX,gY,-3.));
  
  	// set energy
  	// neutron
  	yyy=G4UniformRand();
  	
		
		primaryEne = TMath::Power(10, (yyy-1)*eneRange);		
  	fParticleGun->SetParticleEnergy(primaryEne*GeV);
  	
  	//create vertex   
  	fParticleGun->GeneratePrimaryVertex(anEvent);
  	
  	primPDG = fParticleGun->GetParticleDefinition()->GetPDGEncoding() ;
  	primEnergy = fParticleGun->GetParticleEnergy() ;
  	primPosX = fParticleGun->GetParticlePosition().x() ;
  	primPosY = fParticleGun->GetParticlePosition().y() ;
  	primPosZ = fParticleGun->GetParticlePosition().z() ;
  	//G4cout<<"Primary enrgy 1.............................................................. = "<<primaryEne<<G4endl;
    //G4cout<<"Primary enrgy 2............................................................ = "<<primEnergy<<G4endl;
  	TrGEMAnalysis::GetInstance()->SavePrimary(primEnergy, primPDG, primPosX, primPosY, primPosZ);
}



