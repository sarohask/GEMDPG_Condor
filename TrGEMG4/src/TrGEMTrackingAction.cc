
#include "TrGEMTrackingAction.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "G4RunManager.hh"
#include "TrGEMAnalysis.hh"

TrGEMTrackingAction::TrGEMTrackingAction() 
	: eventID(0), parentID(0), trackID(0), charge(0), globalTime(0.), pdgCode(0), particle(""), kineticEnergy(0.), positionX(0.), positionY(0.), positionZ(0.),
   	momentumDirectionX(0.), momentumDirectionY(0.), momentumDirectionZ(0.), trackLength(0.0), process(""), volume(""), trackStart(false)
	{;}

TrGEMTrackingAction::~TrGEMTrackingAction()
	{;}

void TrGEMTrackingAction::PreUserTrackingAction(const G4Track* aTrack) 
	{}

void TrGEMTrackingAction::PostUserTrackingAction(const G4Track* aTrack)
	{
		//trackStart = TrGEMAnalysis::GetInstance()->GetKickStart();
		
		if( aTrack->GetParentID() > 0 )
   		{
   			//G4cout<<"trackstart.............= "<<trackStart<<G4endl;
      	eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID() ;
      
      	parentID = aTrack->GetParentID() ;
      	 
      	trackID = aTrack->GetTrackID() ;
      	
      	charge = aTrack->GetParticleDefinition()->GetPDGCharge() ;
      
      	globalTime = aTrack->GetGlobalTime() ;
      
      	pdgCode = aTrack->GetParticleDefinition()->GetPDGEncoding() ;
      	
      	particle = aTrack->GetDynamicParticle()->GetDefinition()->GetParticleName() ;
     
      	kineticEnergy = aTrack->GetVertexKineticEnergy() ;
      
      	positionX = aTrack->GetVertexPosition().x() ;
      	
      	positionY = aTrack->GetVertexPosition().y() ;
      	
      	positionZ = aTrack->GetVertexPosition().z() ;
     
      	momentumDirectionX = aTrack->GetVertexMomentumDirection().x() ; 
      	
      	momentumDirectionY = aTrack->GetVertexMomentumDirection().y() ; 
      	
      	momentumDirectionZ = aTrack->GetVertexMomentumDirection().z() ;
      	
      	trackLength = aTrack->GetTrackLength();
      	
      	process = aTrack->GetCreatorProcess()->GetProcessName() ;
      
      	volume = aTrack->GetLogicalVolumeAtVertex()->GetName() ;
   		}
   		
		//TrGEMAnalysis::GetInstance()->SaveProcessQuantities( eventID, parentID, trackID, charge, globalTime, pdgCode, particle, 		
    																										//		 kineticEnergy, positionX, positionY, positionZ, momentumDirectionX, 
    																										//		 momentumDirectionY, momentumDirectionZ, trackLength, process,volume) ;
    							
	}
