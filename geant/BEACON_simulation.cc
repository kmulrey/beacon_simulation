
#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "BEACONDetectorConstruction.hh"
#include "BEACONPhysicsList.hh"
#include "BEACONPrimaryGeneratorAction.hh"

#include "BEACONRunAction.hh"
#include "BEACONEventAction.hh"
#include "BEACONSteppingAction.hh"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <stdlib.h>     /* atof */



using namespace std;

int main(int argc,char** argv)
{
   // Construct the default run manager
   //s
    
    
   G4RunManager* runManager = new G4RunManager;
   
   // set mandatory initialization classes
   //
    
    
   BEACONDetectorConstruction* detector = new BEACONDetectorConstruction;
   runManager->SetUserInitialization(detector);
  
   //
   G4VUserPhysicsList* physics = new BEACONPhysicsList;
   runManager->SetUserInitialization(physics);
	
   // set mandatory user action class
   //
  
   BEACONPrimaryGeneratorAction* gen_action = new BEACONPrimaryGeneratorAction();


   runManager->SetUserAction(gen_action);
	 
	// set user action classes
   
	BEACONRunAction*   run;
	BEACONEventAction* event;
	
	runManager->SetUserAction(run = new BEACONRunAction(detector,gen_action));
	runManager->SetUserAction(event = new BEACONEventAction());
	//runManager->SetUserAction(new VGCTrackingAction(gen_action,run,histo));
	runManager->SetUserAction(new BEACONSteppingAction(run, event));
   
   // Initialize G4 kernel
   //
   runManager->Initialize();
   
   // Get the pointer to the UI manager and set verbosities
   //
   G4UImanager* UI = G4UImanager::GetUIpointer();
   
   UI->ApplyCommand("/control/verbose 0");
	UI->ApplyCommand("/run/verbose 0"); 
	UI->ApplyCommand("/event/verbose 0"); 
	UI->ApplyCommand("/tracking/verbose 0");
   UI->ApplyCommand("/process/verbose 0");
   
	if (argc==4)   // batch mode
   {
       
      char* E = argv[1];
      char* Z = argv[2];
      char* A = argv[3];
       
       string az;
       string zen;
       string en;
       
       stringstream ss;
       ss<<A;
       ss>>az;
       ss.clear();

       ss<<Z;
       ss>>zen;
       ss.clear();

       ss<<E;
       ss>>en;
       ss.clear();

       
       float prim_energy;//=stof(en);
       float prim_zenith;//=stof(zen);
       float prim_azimuth;//=stof(az);
       ss<<en;
       ss>>prim_energy;
       ss.clear();
       
       ss<<zen;
       ss>>prim_zenith;
       ss.clear();
       
       ss<<az;
       ss>>prim_azimuth;
       ss.clear();
       
       
    
    
       
       string dir( "/vol/astro7/lofar/kmulrey/sim/beacon/zhaires_sims/" );
       string outdir("/vol/astro7/lofar/kmulrey/sim/beacon/results/");
       string inFile=dir + "footprint_" + en+"_" + zen+"_" + az + ".grdpcles.txt";
       cout <<inFile<<endl;
       string outFile=outdir + "deposit_" + en+"_" + zen+"_" + az + ".txt";
       cout <<outFile<<endl;

       
      
      string line;
      ifstream myfile(inFile.c_str());
      //ifstream myfile(cstr);

       
       
       
      //double penergy, zenith, azimuth;
      if (myfile.is_open())
      {
          cout<<"running event"<<endl;
         getline (myfile,line); //header
         getline (myfile,line); //header

         //istringstream iss(line);
         //int evtno, pid;
         
         //iss >> evtno >> pid >> penergy >> zenith >> azimuth;
         
         double shower_axis_x = sin(prim_zenith)*cos(prim_azimuth);
         double shower_axis_y = sin(prim_zenith)*sin(prim_azimuth);
         
         const int nobins=200;
         
         double TotalArea[nobins]={0};
         double DepositedEnergyTotal[nobins]={0};
         double DepositedEnergyGamma[nobins]={0};
         double DepositedEnergyElecPosi[nobins]={0};
         double DepositedEnergyMuons[nobins]={0};
         double DepositedEnergyHadrons[nobins]={0};
         for (int i=0; i<nobins; i++) {
            TotalArea[i]=25*3.14159265*((i+1)*(i+1)-i*i); //m^2
            DepositedEnergyTotal[i]=0;
            DepositedEnergyGamma[i]=0;
            DepositedEnergyElecPosi[i]=0;
            DepositedEnergyMuons[i]=0;
            DepositedEnergyHadrons[i]=0;
         }
         //while ( getline (myfile,line) )
         for (int i=0; i<1000; i++)
         {
            getline (myfile,line);
            istringstream iss(line);
            //int cors_id, id;
            //double px, py, pz, x, y, t, w;
            //iss >> cors_id >> id >> px >> py >> pz >> x >> y >> t >> w;
             double id, penergy, rad, polar, Ux, Uy, Uz,x,y;
            iss >> id >> penergy >> rad >> polar >> Ux >> Uy >> Uz;
             x=pow(10,rad)*cos(polar);
             y=pow(10,rad)*sin(polar);
             double w=1;
             double energy = pow(10,penergy);// penergy*GeV;
                           //double part_zen= -1*((3.14159/180)*prim_zenith-acos(Uz/sqrt(Ux*Ux+Uy*Uy+Uz*Uz)));
                           // double part_az=(3.14159/180)*prim_azimuth-atan(Uy/Uz);
             double part_zen=3.14159-acos(Uz/sqrt(Ux*Ux+Uy*Uy+Uz*Uz));
             double part_az=atan(Uy/Ux);
            
            double R2 = x*x+y*y;
            double inner = x*shower_axis_x + y*shower_axis_y;
            double AxisDist = sqrt(R2-inner*inner);
            int DistBin = AxisDist/500; // bin 0 = 0-5 m, bin 1 = 5-10m, etc.
            //double energy = sqrt(px*px+py*py+pz*pz)*GeV;
            cout<<pcode<<"  "<<energy*pow(10,3)<<"  "<<x<<"  "<< y<<"   "<<DistBin<<"  "<<(180/3.14159)*part_zen<<"  "<<prim_zenith<<"  "<<(180/3.14159)*part_az<<"  "<<prim_azimuth<<endl;
            G4String nextParticle="ignore";
            if (id==1) {nextParticle="gamma";}
            if (id==2) {nextParticle="e+";}
            if (id==3) {nextParticle="e-";}
            if (id==5) {nextParticle="mu+";}
            if (id==6) {nextParticle="mu-";}
            if (id==13) {nextParticle="neutron";}
            if (id==14) {nextParticle="proton";}
            
            if (nextParticle!="ignore" && DistBin<nobins) {
               cout << nextParticle << " at " << AxisDist/100. << " m (bin " << DistBin << "), " << energy << " GeV" << endl;
               // GeV BUG !!! : gen_action->SetNewParticle(nextParticle,zenith,azimuth,energy*GeV);
               //gen_action->SetNewParticle(nextParticle,zenith,azimuth,energy);
               gen_action->SetNewParticle(nextParticle,part_zen,part_az,energy);

               runManager->BeamOn(1); //this gives the particle a random position in an area of 2.25 m^2
               double Deposit = w*(event->GetEnergyDeposit());    // what is w ? Weight, from thinning? (AC)
               G4cout << "Deposit: " << Deposit<< G4endl;
               DepositedEnergyTotal[DistBin]+=Deposit;
                  if (id==1) { DepositedEnergyGamma[DistBin]+=Deposit; }
                  else if (id==2 || id==3) { DepositedEnergyElecPosi[DistBin]+=Deposit; }
                  else if (id==5 || id==6) { DepositedEnergyMuons[DistBin]+=Deposit; }
                  else if (id==13 || id==14) { DepositedEnergyHadrons[DistBin]+=Deposit; }
            }
         }
         myfile.close();
         //cout << "Bin   Total (Gev)  Gamma(%)   ElecPosi(%) Muons(%) Hadrons(%)" << endl;
         ofstream myfile(outFile.c_str());
         //ofstream myfile(cstr_out);

         for (int i=0; i<nobins; i++) {
            //We put all particles in a distance ring into an area of 2.25 m^2
            //Correct particle density is achieved by applying a factor 2.25/A_ellipse
            //A "ring" is in fact an ellipse, which has Area A_ellipse=A_ring/cos(zenith)
            
            // (AC): What is actually written out here??
            // Deposited energy in MeV? Then the 2.25 cos theta / totalarea doesnt make sense?
            // or energy density in MeV / m^2 ? It seems MeV / m^2, I would say, as then
            // the area correction factor is right.
            // The comparison is with LORA MeV in detector, however...
             
            myfile << i << "     " << 2.25*cos(prim_zenith)*DepositedEnergyTotal[i]/TotalArea[i] << "    " << int(100.*DepositedEnergyGamma[i]/DepositedEnergyTotal[i])
               << "   " << int(100.*DepositedEnergyElecPosi[i]/DepositedEnergyTotal[i]) 
               << "   " << int(100.*DepositedEnergyMuons[i]/DepositedEnergyTotal[i])
            << "   " << int(100.*DepositedEnergyHadrons[i]/DepositedEnergyTotal[i]) << endl;
         
         }
          
          
         myfile.close();
      }
      else{
          cout<<"can't open file"<<endl;
      }
       
   }
   
    else{
        cout<<"Pease enter [log10(energy)] [zenith]  [azimuth]"<<endl;
    }

   delete runManager;
   
   return 0;
}

