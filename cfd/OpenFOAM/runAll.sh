#!/bin/bash

# ./runCase.sh mesh/blockMesh/01_Basic
# ./runCase.sh mesh/blockMesh/02_Basic_Half
# ./runCase.sh mesh/blockMesh/03_Basic_2D
# ./runCase.sh mesh/blockMesh/04_Graded
# ./runCase.sh mesh/blockMesh/05_Graded_Half

# ./runCase.sh mesh/snappyHexMesh/01_Basic  
# ./runCase.sh mesh/snappyHexMesh/02a_RefinementRegion
# ./runCase.sh mesh/snappyHexMesh/02b_RefinementRegion
# ./runCase.sh mesh/snappyHexMesh/03_GeometryRefinement
# ./runCase.sh mesh/snappyHexMesh/04_AllRefinements
# ./runCase.sh mesh/snappyHexMesh/05_BoundaryLayer
# ./runCase.sh mesh/snappyHexMesh/06_Parallel

./runCase.sh incompressible/simpleFoam/01_Basic_2D
./runCase.sh incompressible/simpleFoam/02_Force_Coefs_2D
./runCase.sh incompressible/simpleFoam/03_Validation_2D
./runCase.sh incompressible/simpleFoam/04_Basic_3D
./runCase.sh incompressible/simpleFoam/05_Force_Coefs_3D
./runCase.sh incompressible/simpleFoam/06_Force_Coefs_Half_3D