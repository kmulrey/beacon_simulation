#ifndef BEACONRunAction_h
#define BEACONRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;
class BEACONDetectorConstruction;
class BEACONPrimaryGeneratorAction;

class BEACONRunAction : public G4UserRunAction
{
  public:
    BEACONRunAction(BEACONDetectorConstruction*, BEACONPrimaryGeneratorAction*);
   ~BEACONRunAction();

  public:
    void BeginOfRunAction(const G4Run*);
    void   EndOfRunAction(const G4Run*);
        
    void AddEdep(G4double val)     { edep += val;}
    void AddnonIonEdep(G4double val)     { nonionedep += val;}
                                  
  private:
    G4double        edep, nonionedep;
    BEACONDetectorConstruction*   detector;
    BEACONPrimaryGeneratorAction* primary;
};

#endif

