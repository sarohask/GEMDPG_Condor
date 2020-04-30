#ifndef TRGEMTRACKINGACTION_H
#define TRGEMTRACKINGACTION_H 1

#include "globals.hh"
#include "G4UserTrackingAction.hh"

using namespace std;

class TrGEMTrackingAction : public G4UserTrackingAction
	{
   	public:
      TrGEMTrackingAction() ;
      virtual ~TrGEMTrackingAction() ;

      virtual void PreUserTrackingAction(const G4Track*) ;
      virtual void PostUserTrackingAction(const G4Track*) ;

   	private:
      G4int 				eventID ;
      G4int 				parentID ;
      G4int 				trackID ;
      G4int 				charge ;
      G4double 			globalTime ;
      G4int    			pdgCode ;
      G4double 			kineticEnergy ;
      G4double 			positionX ;
      G4double 			positionY ;
      G4double 			positionZ ;
      G4double 			momentumDirectionX ;
      G4double 			momentumDirectionY ;
      G4double 			momentumDirectionZ ;
      G4double 			trackLength ;
      string 				particle ;
      string 				process ;
      string 				volume ;
      G4bool 				trackStart ;
	};

#endif
