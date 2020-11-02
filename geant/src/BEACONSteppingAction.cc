#include "BEACONSteppingAction.hh"
#include "BEACONRunAction.hh"
#include "BEACONEventAction.hh"


#include "G4SteppingManager.hh"
#include "G4VProcess.hh"
#include "BEACONDetectorConstruction.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"


BEACONSteppingAction::BEACONSteppingAction(BEACONRunAction* run, BEACONEventAction* event)
:runAction(run), eventAction(event)
{ }


void BEACONSteppingAction::UserSteppingAction(const G4Step* aStep)
{
	const G4VPhysicalVolume* prevolume = aStep->GetPreStepPoint()->GetPhysicalVolume();   
   G4double EdepStep = aStep->GetTotalEnergyDeposit();
	//G4double EnonIondepStep = aStep->GetNonIonizingEnergyDeposit();
             
   if (prevolume->GetName()=="scintillator_1" || prevolume->GetName()=="scintillator_2" || prevolume->GetName()=="scintillator_3" || prevolume->GetName()=="scintillator_4") {
      runAction->AddEdep(EdepStep);
      //runAction->AddnonIonEdep(EnonIondepStep);
      eventAction->AddEdep(EdepStep);
      //eventAction->AddnonIonEdep(EnonIondepStep);
   }

}




