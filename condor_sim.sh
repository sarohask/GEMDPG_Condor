#!/bin/sh

hostname

#pinpoint to root location
source /cvmfs/sft.cern.ch/lcg/releases/LCG_87/ROOT/6.08.02/x86_64-centos7-gcc62-opt/bin/thisroot.sh

mkdir build
cd build

cmake -DGeant4_DIR=/usr/local/geant4/lib/Geant4-10.0.4/ ../TrGEMG4
make

./TrGEMG4 e- test_e-_0 100 

