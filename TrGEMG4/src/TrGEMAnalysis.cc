
#include "TrGEMHit.hh"
#include "TrGEMAnalysis.hh"

#include "G4UnitsTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Event.hh"
#include "G4Run.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4String.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"

#include <TROOT.h>
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>

#include <TVector3.h>

TrGEMAnalysis* TrGEMAnalysis::singleton = 0 ;

TrGEMAnalysis* TrGEMAnalysis::GetInstance() 
	{
		if ( singleton == 0 ) 
			{
    		static TrGEMAnalysis trGEMAnalysis;
    		singleton = &trGEMAnalysis;
  		}
  	return singleton;
	}

TrGEMAnalysis::~TrGEMAnalysis() 
	{}

TrGEMAnalysis::TrGEMAnalysis() 
	{
		file = 0;
	}
	
void TrGEMAnalysis::SetFileName(const G4String name)
	{
  	fileName = name;
	}

void TrGEMAnalysis::PrepareNewRun()
	{
		eventCounter = 0 ;
			
		fileName = fileName + ".root";
  	file = TFile::Open(fileName.c_str(),"RECREATE");
  	if(file) 
    	G4cout << "ROOT file " << fileName << " is created " << G4endl;
  	else 
  		{
    		G4cerr << "ROOT file has not been created!" << G4endl;
  		}
  	
  	/*tEvent = new TTree("Event","Run with awesome data") ;
  	tEvent->Branch("primaryEne",  &primaryEne,  "primaryEne/D");
  	tEvent->Branch("primaryPart", &primaryPart, "primaryPart/I");

  	tEvent->Branch("EleGap",    &eleGap,    "EleGap[4]/I");
  	tEvent->Branch("PosGap",    &posGap,    "PosGap[4]/I");
  	tEvent->Branch("ChargeGap", &chargeGap, "ChargeGap[4]/I");
  	tEvent->Branch("nElectron", &nElectron, "nElectron/I");
  	tEvent->Branch("nPositron", &nPositron, "nPositron/I");
  	tEvent->Branch("nGamma",    &nGamma,    "nGamma/I"   );
  	tEvent->Branch("nCharged",  &nCharged,  "nCharged/I" );*/
  	
  	// create tree and branch(es)
  	tHits = new TTree("HitsSteps", "Tree keeps output from G4Step Geant4 Simulation");
		tHits->Branch("EventID", &eventID_, "eventID_/I");
		tHits->Branch("ParentID", &parentID_, "parentID_/I");
		tHits->Branch("TrackID", &trackID_, "trackID_/I");
   	tHits->Branch("Edep", &eDep_);
   	tHits->Branch("KineticEnergy", &kineticEnergy_);
   	tHits->Branch("TotalNumHits", &totNumHits_, "totNumHits_/I");
   	tHits->Branch("HitNumber", &hitNum_);
   	tHits->Branch("PDG", &pdgEncoding_);
   	tHits->Branch("Charge", &charge_);
   	tHits->Branch("PositionX", &positionX_);
   	tHits->Branch("PositionY", &positionY_);
   	tHits->Branch("PositionZ", &positionZ_);
   	tHits->Branch("MomentumDirectionX", &momDirectionX_);
   	tHits->Branch("MomentumDirectionY", &momDirectionY_);
   	tHits->Branch("MomentumDirectionZ", &momDirectionZ_);
   	tHits->Branch("MomentumX", &momentumX_);
   	tHits->Branch("MomentumY", &momentumY_);
   	tHits->Branch("MomentumZ", &momentumZ_);
   	tHits->Branch("StepNumber", &stepNum_, "stepNum_/I");
   	tHits->Branch("InteractionLength", &interLength_);
   	tHits->Branch("VolumeName", &volName_);
   	tHits->Branch("ProcessName", &processName_);
   	tHits->Branch("ParticleName", &particName_);
   	tHits->Branch("NumberInteraction", &aNumInteraction_, "aNumInteraction_/I");
   	tHits->Branch("PrimaryEnergy",  &primaryEnergy);
  	tHits->Branch("PrimaryParticlePDGCode", &primaryParticlePDG, "primParticlePDG/I");
   	
   	// create tree and branch(es)
  	tEvent = new TTree("PrimaryEvent","Primary Event Information") ;
  	tEvent->Branch("PrimaryEnergy",  &primaryEnergy);
  	tEvent->Branch("PrimaryParticlePDGCode", &primaryParticlePDG, "primParticlePDG/I");
  	tEvent->Branch("PrimaryPositionX",  &primaryPositionX);
  	tEvent->Branch("PrimaryPositionY",  &primaryPositionY);
  	tEvent->Branch("PrimaryPositionZ",  &primaryPositionZ);
   	
   	//tracks created 
   	tTrack = new TTree("SecondaryTracks","Quantities related to secondaries that provide a signal") ;
   	tTrack->Branch("eventID",&eventID) ;
   	tTrack->Branch("parentID",&parentID) ;
   	tTrack->Branch("trackID",&trackID) ;
   	tTrack->Branch("charge",&charge) ;
   	tTrack->Branch("globalTime",&globalTime) ;
   	tTrack->Branch("pdgCode",&pdgCode) ;
   	tTrack->Branch("particle",&particle) ;
   	tTrack->Branch("kineticEnergy",&kineticEnergy) ;
   	tTrack->Branch("positionX",&positionX) ;
   	tTrack->Branch("positionY",&positionY) ;
   	tTrack->Branch("positionZ",&positionZ) ;
   	tTrack->Branch("momentumDirectionX",&momentumDirectionX) ;
   	tTrack->Branch("momentumDirectionY",&momentumDirectionY) ;
   	tTrack->Branch("momentumDirectionZ",&momentumDirectionZ) ;
   	tTrack->Branch("trackLength",&trackLength) ;
   	tTrack->Branch("process",&process) ;
   	tTrack->Branch("volume",&volume) ;
	}

void TrGEMAnalysis::PrepareNewEvent()
	{
  	//Reset variables relative to this event
  	parentID_ = -1;
  	eventID_ = 0;
    totNumHits_ = 0;
    hitNum_ = 0;
    eDep_ = 0.0;
    //pdgEncoding_ = 0 ;
    //charge_ = 9999 ;
    kineticEnergy_ = 0.0 ;
    positionX_ = 0.0 ;
    positionY_ = 0.0 ;
    positionZ_ = 0.0;
    momDirectionX_ = 0.0 ; 
   	momDirectionY_ = 0.0 ; 
   	momDirectionZ_ = 1.0 ; 
   	momentumX_ = 0.0 ; 
   	momentumY_ = 0.0 ; 
   	momentumZ_ = 0.0 ;
   	stepNum_ = -1.0 ;
   	interLength_ = 0.0 ;
   	aNumInteraction_ = 0;
   
   	// Clearing of the vectors, ready for coming event
   	eventID.clear() ;
   	charge.clear() ;
   	parentID.clear() ;
  	trackID.clear() ;
   	globalTime.clear() ;
   	pdgCode.clear() ;
   	particle.clear() ;
   	kineticEnergy.clear() ;
   	positionX.clear() ;
   	positionY.clear() ;
   	positionZ.clear() ;
   	momentumDirectionX.clear() ;
   	momentumDirectionY.clear() ;
   	momentumDirectionZ.clear() ; 
   	trackLength.clear() ;
   	process.clear() ;
   	volume.clear() ;
 	}

void TrGEMAnalysis::EndOfEvent()
	{
  	tHits->Fill() ;
  	tEvent->Fill();
  	tTrack->Fill();
	}

void TrGEMAnalysis::EndOfRun()
	{
  	// Writing and closing the ROOT file
  	G4cout << "ROOT: files writing..." << G4endl;
  	file->Write();
  	G4cout << "ROOT: files closing..." << G4endl;
  	file->Close();
  	G4cout << "ROOT: files closed..." << G4endl;
  	delete file ;
	}

void TrGEMAnalysis::SavePrimary(G4double aPrimEnergy, G4int aPrimParticlePDG, G4double aPrimPositionX, G4double aPrimPositionY, G4double aPrimPositionZ)
	{
  	primaryEnergy = aPrimEnergy / MeV;
  	primaryParticlePDG = aPrimParticlePDG;
  	primaryPositionX = aPrimPositionX ;
  	primaryPositionY = aPrimPositionY ;
  	primaryPositionZ = aPrimPositionZ ;
  	//G4cout<<"Analysis enrgy.............................................................. = "<<primaryEnergy<<G4endl;
	}
	
void TrGEMAnalysis::SaveProcessQuantities( G4int    anEventID,
	    										 								 G4int    aParentID,
	    																		 G4int    aTrackID,
	    							  										 G4int    aCharge,
	   																			 G4double aGlobalTime,
	   																			 G4int    aPdgCode,
	   																			 string 	aParticle,
	   																			 G4double aKineticEnergy,
	   																			 G4double aPositionX, 
	   																			 G4double aPositionY, 
	   																			 G4double aPositionZ,
	   																			 G4double aMomentumDirectionX, 
	   																			 G4double aMomentumDirectionY, 
	    																		 G4double aMomentumDirectionZ,
	    																		 G4double aTrackLength,
	    																		 string 	aProcess,
	    																		 string 	aVolume ) 
	{
		eventID								.push_back(anEventID) ;
    charge								.push_back(aCharge) ;
    parentID							.push_back(aParentID) ;
    trackID								.push_back(aTrackID) ;
    globalTime    				.push_back(aGlobalTime) ;
    pdgCode       				.push_back(aPdgCode) ;
    particle      				.push_back(aParticle) ;
    kineticEnergy 				.push_back(aKineticEnergy) ;
    positionX							.push_back(aPositionX) ;
    positionY							.push_back(aPositionY) ;
    positionZ							.push_back(aPositionZ) ;
    momentumDirectionX		.push_back(aMomentumDirectionX) ;
    momentumDirectionY		.push_back(aMomentumDirectionY) ;
    momentumDirectionZ		.push_back(aMomentumDirectionZ) ;
    trackLength						.push_back(aTrackLength);
    process								.push_back(aProcess) ;
    volume								.push_back(aVolume) ;    
	}
	
void TrGEMAnalysis::SetValuesForInteractingEvents( G4int evtNo, G4int hitTNo, G4int hitNo, TrGEMHit* hit)
	{
		//G4cout<<"begin of Annalysis set for interaction,........"<<G4endl;
    eventID_ = evtNo;
    parentID_ = hit->GetParentID();
    trackID_ = hit->GetTrackID();
    totNumHits_ = hitTNo;
    hitNum_ = hitNo+1;
    eDep_ = hit->GetEdep();
    pdgEncoding_ = hit->GetPDG();
    charge_ = hit->GetCharge();
    kineticEnergy_ = hit->GetKineticEnergy() ;
    positionX_ = hit->GetPos().getX() ;
    positionY_ = hit->GetPos().getY() ;
    positionZ_ = hit->GetPos().getZ() ;
    momDirectionX_ = hit->GetMomentumDirection().getX() ; 
   	momDirectionY_ = hit->GetMomentumDirection().getY() ; 
   	momDirectionZ_ = hit->GetMomentumDirection().getZ() ; 
   	momentumX_ = hit->GetMomentum().getX() ; 
   	momentumY_ = hit->GetMomentum().getY() ; 
   	momentumZ_ = hit->GetMomentum().getZ() ;
   	stepNum_ = hit->GetStepNumber();
   	interLength_ = hit->GetInterLength();
   	volName_ = hit->GetVolume();
   	particName_ = hit->GetParticleName();	
   	processName_ = hit->GetProcessName();
   	aNumInteraction_ = hit->GetNumInteraction() ;
	}

void TrGEMAnalysis::SetValuesForNonInteractingEvents(G4int evtNo, G4int hitTNo)
	{
		//G4cout<<"begin of Annalysis set for non-interaction,........"<<G4endl;
		parentID_ = 0;
  	eventID_ = evtNo;
    totNumHits_ = hitTNo;
    hitNum_ = 0;
    eDep_ = 0.0;
   // pdgEncoding_ = 0 ;
   // charge_ = 9999 ;
    kineticEnergy_ = 0.0 ;
    positionX_ = 0.0 ;
    positionY_ = 0.0 ;
    positionZ_ = 0.0;
    momDirectionX_ = 0.0 ; 
   	momDirectionY_ = 0.0 ; 
   	momDirectionZ_ = 1.0 ; 
   	momentumX_ = 0.0 ; 
   	momentumY_ = 0.0 ; 
   	momentumZ_ = 0.0 ;
   	stepNum_ = -1.0 ;
   	aNumInteraction_ = 0;
	}

void TrGEMAnalysis::SetKickStart(G4bool someKickStart) 
	{
		aKickStart = someKickStart ;
	}
	


	
