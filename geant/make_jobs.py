import numpy as np
from random import random
from random import randint



base_dir='/vol/astro7/lofar/kmulrey/sim/beacon/'
run_dir='/vol/astro7/lofar/kmulrey/sim/beacon/run/'


def write_file(energy, zenith, azimuth):

    filename=run_dir+'_zhaires_'+energy+'_'+zenith+'_'+azimuth+'.q'
    outfile=open(filename,'w')

    outfile.write('#! /bin/bash\n')
    outfile.write('#SBATCH --time=2-00:00:00\n')
    
    outfile.write('use geant\n')
    outfile.write('G4WORKDIR={0}/beacon_simulation/geant/\n')
    outfile.write('. /vol/optcoma/geant4_9.6_install/share/Geant4-9.6.4/geant4make/geant4make.sh\n')
    outfile.write('cd {0}/beacon_simulation/geant/\n'.format(base_dir))
    outfile.write('./BEACON_simulation {0} {1} {2}\n'.format(energy,zenith, azimuth))
    
    
    
energy=[16.5,17.0,17.5,18.0,18.5,19.0]
azimuth=[-100,-25,-50,-75,0,100,25,50,75]
zenith=[0,10,20,30,40,50,60,70,80,90]


        

for e in np.arange(len(energy)):
    for z in np.arange(len(zenith)):
        for a in np.arange(len(azimuth)):

            write_file('10000',0, zenith[0], energy[0], seed+1,'proton')






