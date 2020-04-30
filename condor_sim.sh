#!/bin/sh

hostname

mkdir build
cd build

cmake -DGeant4_DIR=/usr/local/geant4/lib/Geant4-10.0.4/ ../TrGEMG4
make

./TrGEMG4 neutron test_n_0 10000 

