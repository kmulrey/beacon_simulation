#ifndef BEACONDetectorConstruction_h
#define BEACONDetectorConstruction_h 1

class G4LogicalVolume;
class G4VPhysicalVolume;

#include "G4VUserDetectorConstruction.hh"

class BEACONDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	
   BEACONDetectorConstruction();
   ~BEACONDetectorConstruction();
	
   G4VPhysicalVolume* Construct();
	
private:
   
   // Logical volumes
   //
   G4LogicalVolume* world_log;
	G4LogicalVolume* cover_log;
   G4LogicalVolume* cavity_log;
   G4LogicalVolume* scintillator_log_1;
   G4LogicalVolume* scintillator_log_2;
   G4LogicalVolume* scintillator_log_3;
   G4LogicalVolume* scintillator_log_4;
	
   // Physical volumes
   //
   G4VPhysicalVolume* world_phys;
   G4VPhysicalVolume* cover_phys;
   G4VPhysicalVolume* cavity_phys;
   G4VPhysicalVolume* scintillator_phys_1;
   G4VPhysicalVolume* scintillator_phys_2;
   G4VPhysicalVolume* scintillator_phys_3;
   G4VPhysicalVolume* scintillator_phys_4;
   
};

#endif
