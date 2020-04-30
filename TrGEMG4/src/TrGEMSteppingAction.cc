
#include "G4TouchableHistory.hh"
#include "G4Step.hh"
#include "G4HCofThisEvent.hh"
#include "G4HCtable.hh"
#include "G4UnitsTable.hh"
#include "G4VProcess.hh"
#include <string>
#include <sstream>
#include <iostream>

#include "TrGEMSteppingAction.hh"
#include "TrGEMAnalysis.hh"

#include "G4SteppingManager.hh"

TrGEMSteppingAction::TrGEMSteppingAction() 
	: G4UserSteppingAction(), stepManager(0)
	{}

TrGEMSteppingAction::~TrGEMSteppingAction() 
	{}
	
void TrGEMSteppingAction::SetSteppingManagerPointer(G4SteppingManager *stepManager)
	{}

void TrGEMSteppingAction::UserSteppingAction(const G4Step* aStep)
	{
   	//const G4StepPoint* endPoint = aStep->GetPostStepPoint();
  	//const G4VProcess* process   = endPoint->GetProcessDefinedStep();
  	//G4double edep(0.) ;
   	//edep = aStep->GetTotalEnergyDeposit() ;
  	//const G4String processName = stepManager->GetfCurrentProcess()->GetProcessName() ;
  	//incident neutron
  	//if (aStep->GetTrack()->GetTrackID() == 1) 
  		//{ 
    	//	G4double trackl = aStep->GetTrack()->GetTrackLength();
    		//G4double time   = aStep->GetTrack()->GetLocalTime();      		
  		//}    
	}


