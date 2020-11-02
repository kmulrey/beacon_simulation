#ifndef LORAPhysicsList_h
#define LORAPhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"
#include "G4IonConstructor.hh"

class LORAPhysicsList: public G4VUserPhysicsList
{
public:
   LORAPhysicsList();
   ~LORAPhysicsList();
   
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

