OPENFOAM = openfoam2206

################################################################################

all: meshing incompressible compressible

################################################################################

meshing: blockMesh snappyHexMesh cfMesh

blockMesh:
	$(OPENFOAM) ./runCase.sh meshing/blockMesh/01_Basic/
	$(OPENFOAM) ./runCase.sh meshing/blockMesh/02_Graded/
	$(OPENFOAM) ./runCase.sh meshing/blockMesh/03_Graded_Half/

snappyHexMesh:
	$(OPENFOAM) ./runCase.sh meshing/snappyHexMesh/01_Basic/
	$(OPENFOAM) ./runCase.sh meshing/snappyHexMesh/02a_RefinementRegion/
	$(OPENFOAM) ./runCase.sh meshing/snappyHexMesh/02b_RefinementRegion/
	$(OPENFOAM) ./runCase.sh meshing/snappyHexMesh/03_GeometryRefinement/
	$(OPENFOAM) ./runCase.sh meshing/snappyHexMesh/04_BoundaryLayerMesh/
	$(OPENFOAM) ./runCase.sh meshing/snappyHexMesh/05_AllRefinements/
	$(OPENFOAM) ./runCase.sh meshing/snappyHexMesh/06_Parallel/

cfMesh:
	$(OPENFOAM) ./runCase.sh meshing/cfMesh/cartesianMesh/01_Basic/
	$(OPENFOAM) ./runCase.sh meshing/cfMesh/cartesianMesh/02_Refinement/
	$(OPENFOAM) ./runCase.sh meshing/cfMesh/cartesianMesh/03_Boundary_Layer/
	$(OPENFOAM) ./runCase.sh meshing/cfMesh/tetMesh/01_Basic/
	$(OPENFOAM) ./runCase.sh meshing/cfMesh/tetMesh/02_Refinement/
	$(OPENFOAM) ./runCase.sh meshing/cfMesh/tetMesh/03_Boundary_Layer/

################################################################################

incompressible: pimpleFoam simpleFoam

pimpleFoam:
	$(OPENFOAM) ./runCase.sh incompressible/pimpleFoam/01_Basic/
	$(OPENFOAM) ./runCase.sh incompressible/pimpleFoam/02_MovingMesh/

simpleFoam:
	$(OPENFOAM) ./runCase.sh incompressible/simpleFoam/01_Basic/
	$(OPENFOAM) ./runCase.sh incompressible/simpleFoam/02_Force_Coefs/
	$(OPENFOAM) ./runCase.sh incompressible/simpleFoam/03_Half/
	$(OPENFOAM) ./runCase.sh incompressible/simpleFoam/04_tetMesh/

################################################################################

compressible: rhoPimpleFoam rhoSimpleFoam sonicFoam

rhoPimpleFoam:
	$(OPENFOAM) ./runCase.sh compressible/rhoPimpleFoam/01_Laminar/

rhoSimpleFoam:
	$(OPENFOAM) ./runCase.sh compressible/rhoSimpleFoam/01_Laminar/
	$(OPENFOAM) ./runCase.sh compressible/rhoSimpleFoam/02_Turbulent/
	$(OPENFOAM) ./runCase.sh compressible/rhoSimpleFoam/03_Force_Coefs/
	$(OPENFOAM) ./runCase.sh compressible/rhoSimpleFoam/04_Vorticity/
	$(OPENFOAM) ./runCase.sh compressible/rhoSimpleFoam/05_Mapping/
	$(OPENFOAM) ./runCase.sh compressible/rhoSimpleFoam/06_tetMesh/

sonicFoam:
	$(OPENFOAM) ./runCase.sh compressible/sonicFoam/01_Laminar/

################################################################################

clean:
	$(OPENFOAM) ./cleanRunDir.sh
