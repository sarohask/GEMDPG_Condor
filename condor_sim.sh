#!/bin/sh

hostname

mkdir build
cd build

cmake -DGeant4_DIR=/usr/local/geant4/lib/Geant4-10.0.4/ ../TrGEMG4
make

./TrGEMG4 e- test_e-_0 100 

