
#include "TrGEMSensitiveDetector.hh"
#include "TrGEMAnalysis.hh"

#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "G4RunManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
#include "G4ios.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include <iostream>

TrGEMSensitiveDetector::TrGEMSensitiveDetector(G4String name)
	:G4VSensitiveDetector(name), kickStart(false), numInteraction(0), interLength(0.0)
	{
  	collectionName.insert("TrGEMHitsCollection"); 	
	}

TrGEMSensitiveDetector::~TrGEMSensitiveDetector()
	{}

void TrGEMSensitiveDetector::Initialize(G4HCofThisEvent* HCE)
	{
		hitsCollection = new TrGEMHitsCollection( SensitiveDetectorName, collectionName[0] );
		static int HCID = -1;
    
    if(HCID<0)
    	{ 
    		HCID = G4SDManager::GetSDMpointer()->GetCollectionID( collectionName[0] );
    	}
    HCE->AddHitsCollection( HCID, hitsCollection );
	}

G4bool TrGEMSensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* )
	{
  	G4double edep = 0.0;
		int numUp =0;
		int numBottom = 0;
  	//We get now the energy deposited by this step
    edep = step->GetTotalEnergyDeposit() ;
   	G4double nonionedep = step->GetNonIonizingEnergyDeposit() ;
   	edep -= nonionedep ;
   	  
		G4StepPoint *lastPoint = step->GetPostStepPoint();
		G4Track* track = step->GetTrack();
  		
   	G4int trackIndex=track->GetTrackID();
  	G4int parentIndex = track->GetParentID();
  	
  	string particleName = track->GetDynamicParticle()->GetParticleDefinition()->GetParticleName();
  	
  	G4int pdg = track->GetParticleDefinition()->GetPDGEncoding();
  	G4int chargePart = track->GetParticleDefinition()->GetPDGCharge();
  	G4TouchableHandle touchable = step->GetPreStepPoint()->GetTouchableHandle();
   	string volName = touchable->GetVolume(0)->GetName();
   	eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID() ;
   	G4String processName = lastPoint->GetProcessDefinedStep()->GetProcessName();
  	G4int stepNumber = track->GetCurrentStepNumber();
  	
  	if (parentIndex == 0 && trackIndex == 1) 
  		{	
  			if (volName == "FakeTop" || volName == "FakeBottom")
  				{ 
  					interLength = track->GetTrackLength();
  				} 
  		}
  	
  	if (step->GetSecondary()->size()>0 && trackIndex == 1 && parentIndex == 0 )
  		{
  			if (volName == "FakeTop")													numUp = step->GetSecondary()->size();
  			if (volName == "FakeBottom")											numBottom = step->GetSecondary()->size();
  			
    		numInteraction = max (numUp, numBottom);
  		}
  	else { numInteraction = 0;}
  	
  	//Seconadary
  	if (volName == "GasGap1" || volName == "GasGap2" || volName == "GasGap3" || volName == "GasGap4")
  		{
  			if( track->GetParentID() > 0 )
   				{
      			eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID() ;
      			parentID = track->GetParentID() ; 
      			trackID = track->GetTrackID() ;
      			charge = track->GetParticleDefinition()->GetPDGCharge() ;
      			globalTime = track->GetGlobalTime() ;
      			pdgCode = track->GetParticleDefinition()->GetPDGEncoding() ;
      			particle = track->GetDynamicParticle()->GetDefinition()->GetParticleName() ;
      			kineticEnergy = track->GetVertexKineticEnergy() ;
      			positionX = track->GetVertexPosition().x() ;
      			positionY = track->GetVertexPosition().y() ;
      			positionZ = track->GetVertexPosition().z() ;
      			momentumDirectionX = track->GetVertexMomentumDirection().x() ; 
      			momentumDirectionY = track->GetVertexMomentumDirection().y() ; 
      			momentumDirectionZ = track->GetVertexMomentumDirection().z() ;
      			trackLength = track->GetTrackLength();
      			process = track->GetCreatorProcess()->GetProcessName() ;
      			volume = track->GetLogicalVolumeAtVertex()->GetName() ;
      			TrGEMAnalysis::GetInstance()->SaveProcessQuantities( eventID, parentID, trackID, charge, globalTime, pdgCode, particle, 		
    																												 kineticEnergy, positionX, positionY, positionZ, momentumDirectionX, 
    																												 momentumDirectionY, momentumDirectionZ, trackLength, process,volume) ;
   				}
   		}
  	
  	G4String genprocess;
  	if(track->GetCreatorProcess()!=0 ) 
  		{
    		const G4VProcess * genproc=track->GetCreatorProcess();  
    		genprocess = genproc->GetProcessName();
    		//G4cout<<parentIndex<<"...."<<trackIndex<<"...."<<particleName<<"...."<<volName<<"...."<<(*step->GetSecondaryInCurrentStep()).size()<<G4endl;
    		//TrGEMAnalysis::GetInstance()->SaveProcessQuantities( eventID, parentID, trackID, charge, globalTime, pdgCode, particle, 		
    																												 //kineticEnergy, positionX, positionY, positionZ, momentumDirectionX, 
    																												// momentumDirectionY, momentumDirectionZ, trackLength, process,volume) ;
  		}
  	
		TrGEMHit *aHit = new TrGEMHit();
		aHit->SetKineticEnergy(track->GetDynamicParticle()->GetKineticEnergy());
    aHit->SetParentID(parentIndex);
    aHit->SetTrackID(trackIndex);		
    aHit->SetEdep(edep);
    aHit->SetPDG(pdg);
    aHit->SetCharge(chargePart);
    aHit->SetStepNumber(stepNumber);
    aHit->SetInterLength(interLength);
    aHit->SetPos(lastPoint->GetPosition());
    aHit->SetMomentumDirection(lastPoint->GetMomentumDirection());
    aHit->SetMomentum(lastPoint->GetMomentum());
    aHit->SetVolume(volName);
    aHit->SetProcessName(processName);
    aHit->SetParticleName(particleName);
    aHit->SetNumInteraction(numInteraction) ;
    
    hitsCollection->insert(aHit);
    return true;	
	}
	
void TrGEMSensitiveDetector::EndOfEvent(G4HCofThisEvent*)
	{}

