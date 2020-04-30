#ifndef TrGEMAnalysis_h
#define TrGEMAnalysis_h 1

#include "TrGEMHit.hh"
#include "TTree.h"
#include "TBranch.h"
#include "TFile.h"
#include "TH1.h"
#include "snprintf.h"

#include <iostream>
#include <fstream>

#include "globals.hh"
#include <vector>
#include <map>

using namespace std; 

class G4Run;
class G4Event;
class TFile;
class TTree;
class TString;

class TrGEMAnalysis 
	{
		public:
    	static TrGEMAnalysis* GetInstance();
    	~TrGEMAnalysis();
    	
    	void SetFileName(const G4String name);
    	void PrepareNewEvent();
    	void EndOfEvent();
    	void PrepareNewRun();
    	void EndOfRun();
    	void SavePrimary(G4double aPrimEnergy, G4int aPrimParticlePDG, G4double aPrimPositionX, G4double aPrimPositionY, G4double aPrimPositionZ);
			void SaveProcessQuantities(G4int    		anEventID,
	    													 G4int    		aParentID,
	    													 G4int    		aTrackID,
	    							  					 G4int    		aCharge,
	   														 G4double 		aGlobalTime,
	   														 G4int    		aPdgCode,
	   														 std::string 	aParticle,
	   														 G4double 		aKineticEnergy,
	   														 G4double 		aPositionX, 
	   														 G4double 		aPositionY, 
	   														 G4double 		aPositionZ,
	   														 G4double 		aMomentumDirectionX, 
	   														 G4double 		aMomentumDirectionY, 
	    													 G4double 		aMomentumDirectionZ,
	    													 G4double 		aTrackLength,
	    													 std::string 	aProcess,
	    													 std::string 	aVolume) ;

    	void SetValuesForInteractingEvents ( G4int evtNo, G4int hitTNo, G4int hitNo, TrGEMHit* hit);
    	void SetValuesForNonInteractingEvents(G4int evtNo, G4int hitTNo);
    	void SetKickStart(G4bool aKickstart) ;
    	bool GetKickStart()																										{ return aKickStart ;}
    	//inline void SetNumInteraction (G4int numInter) 												{ aNumInteraction_ = numInter; }
    	//inline G4int GetNumInteraction() 																			{ return aNumInteraction_; }
    	
  	private:
  		TrGEMAnalysis();
			static TrGEMAnalysis* singleton;
		
		public:
    	TFile*    		file;
    	TTree*    		tHits;
    	TTree*        tTrack;
    	TTree*        tEvent;
    	G4bool 				aKickStart ;
    	G4int					aNumInteraction_ ;
    	G4int 				eventCounter ;
    	G4String 			fileName;
    	G4int 				parentID_;
    	G4int 				eventID_;
    	G4int 				trackID_;
  		G4int		 			totNumHits_ ;
  		G4int					hitNum_ ;
  		G4int					pdgEncoding_;
  		G4int					charge_;
  		G4double 			eDep_;
  		G4double 			kineticEnergy_;
  		G4double 			positionX_ ;
  		G4double 			positionY_ ;
  		G4double 			positionZ_ ;
  		G4double			momDirectionX_ ; 
   		G4double			momDirectionY_ ; 
   		G4double			momDirectionZ_ ; 
   		G4double			momentumX_ ; 
   		G4double			momentumY_ ; 
   		G4double			momentumZ_ ;
   		G4int					stepNum_;
   		G4double			interLength_;
   		string		 		volName_;
  		string		 		processName_;
  		string		 		particName_;
  		
  		//tEvents  		
  		G4int 						primaryParticlePDG;
  		G4double 					primaryEnergy;
  		G4double 					primaryPositionX ;
  		G4double 					primaryPositionY ;
  		G4double 					primaryPositionZ ;
  		
  		// PROCESS quantities
      vector<G4int> 				eventID ;
      vector<G4int> 				parentID ;
      vector<G4int> 				trackID ;
      vector<G4int> 				charge ;
      vector<G4double> 			globalTime ;
      vector<G4int> 				pdgCode ;
      vector<string> 				particle ;
      vector<G4double> 			kineticEnergy ;
      vector<G4double> 			positionX ;
      vector<G4double> 			positionY ;
      vector<G4double> 			positionZ ;
      vector<G4double> 			momentumDirectionX ;
      vector<G4double> 			momentumDirectionY ;
      vector<G4double> 			momentumDirectionZ ;
      vector<G4double> 			trackLength ;
      vector<string> 				process ;
      vector<string> 				volume ;
	};

#endif 
