#ifndef BEACONPhysicsList_h
#define BEACONPhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"
#include "G4IonConstructor.hh"

class BEACONPhysicsList: public G4VUserPhysicsList
{
public:
   BEACONPhysicsList();
   ~BEACONPhysicsList();
   
protected:
   // Construct particle and physics process
   void ConstructParticle();
   void ConstructIons();
   void ConstructProcess();
   void SetCuts();
   
protected:
   // these methods Construct particles 
   void ConstructBosons();
   void ConstructLeptons();
   void ConstructMesons();
   void ConstructBaryons();
	
protected:
	// these methods Construct physics processes and register them
   void ConstructGeneral();
   void ConstructEM();
   void AddStepMax();
};

#endif

