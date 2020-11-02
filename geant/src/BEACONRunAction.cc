#include "BEACONRunAction.hh"
#include "BEACONDetectorConstruction.hh"
#include "BEACONPrimaryGeneratorAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"

#include "Randomize.hh"
#include <iomanip>


BEACONRunAction::BEACONRunAction(BEACONDetectorConstruction* det, BEACONPrimaryGeneratorAction* kin)
:detector(det), primary(kin)
{ }


BEACONRunAction::~BEACONRunAction()
{ }


void BEACONRunAction::BeginOfRunAction(const G4Run* aRun)
{  

  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  edep = 0.;
  nonionedep = 0.; 
}

void BEACONRunAction::EndOfRunAction(const G4Run* aRun)
{ 

}

