
#ifndef TrGEMSensitiveDetector_h
#define TrGEMSensitiveDetector_h 1

#include "TrGEMHit.hh"
#include "G4VSensitiveDetector.hh"

using namespace std;

class G4Step;
class G4HCofThisEvent;

class TrGEMSensitiveDetector : public G4VSensitiveDetector

	{
   	public:
      TrGEMSensitiveDetector(G4String SDname);
      ~TrGEMSensitiveDetector();

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step *, G4TouchableHistory *);
    	void EndOfEvent(G4HCofThisEvent *);

    private:
     	TrGEMHitsCollection *hitsCollection;
     	G4bool 							kickStart ;
     	G4int								numInteraction;
     	G4int 							eventID  ;
      G4int 							parentID  ; 
      G4int 							trackID  ;
      G4int 							charge  ;
      G4double 						globalTime ;
      G4int 							pdgCode  ;
      string 							particle  ;
      G4double 						kineticEnergy  ;
      G4double 						positionX  ;
      G4double 						positionY ;
      G4double 						positionZ  ;
      G4double 						momentumDirectionX  ; 
      G4double 						momentumDirectionY  ; 
      G4double 						momentumDirectionZ  ;
      G4double 						trackLength ;
      string 							process  ;
      string							volume  ;
      G4double 						interLength ;
	};

#endif
