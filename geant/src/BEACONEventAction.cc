#include "BEACONEventAction.hh"
#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4UnitsTable.hh"

BEACONEventAction::BEACONEventAction()
:drawFlag("none"),printModulo(10000)
{

}


BEACONEventAction::~BEACONEventAction()
{
  //delete eventMessenger;
}


void BEACONEventAction::BeginOfEventAction(const G4Event* evt)
{          
 TotalEnergyDeposit = 0.;
 TotalNonIonizingEnergyDeposit = 0.;
}


void BEACONEventAction::EndOfEventAction(const G4Event* evt)
{

}




