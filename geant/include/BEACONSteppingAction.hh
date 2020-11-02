#ifndef BEACONSteppingAction_h
#define BEACONSteppingAction_h 1

#include "G4UserSteppingAction.hh"

class BEACONRunAction;
class BEACONEventAction;


class BEACONSteppingAction : public G4UserSteppingAction
{
public:
   BEACONSteppingAction(BEACONRunAction*, BEACONEventAction*);
   ~BEACONSteppingAction() {};
   
   void UserSteppingAction(const G4Step*);
   
private:
   BEACONRunAction*    runAction;
   BEACONEventAction*  eventAction;
};


#endif
