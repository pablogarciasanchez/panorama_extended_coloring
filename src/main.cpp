#include <iostream> 
#include <string>   
#include <cmath>    
#include <cstdlib>
#include "aux.h"
#include "malla3d.h"
#include "panorama.h"

int main(int argc, char * argv[]) {

	if(argc != 3){
		std::cout << "Wrong parameters" << std::endl;
		std::cout << "bin/panorama_extended [relive route to 3D model] [output folder]" << std::endl;
		exit(-1);
	}

	Malla3D malla;

	malla.load_obj(argv[1]);

	std::string output_folder = argv[2];

	malla.mesh_pose_norm(X,SDM,Z,output_folder,15);

	malla.calculate_panorama(SDM, X, 0.5, 4);
	malla.export_panorama(SDM,X,output_folder);
	malla.calculate_panorama(NDM, X, 0.5, 4);
	malla.export_panorama(NDM,X,output_folder);
	combine_panorama(X);

	malla.calculate_panorama(SDM, Y, 0.5, 4);
	malla.export_panorama(SDM,Y,output_folder);
	malla.calculate_panorama(NDM, Y, 0.5, 4);
	malla.export_panorama(NDM,Y,output_folder);
	combine_panorama(Y);

	malla.calculate_panorama(SDM, Z, 0.5, 4);
	malla.export_panorama(SDM,Z,output_folder);
	malla.calculate_panorama(NDM, Z, 0.5, 4);
	malla.export_panorama(NDM,Z,output_folder);
	combine_panorama(Z);
	
	return 0;
}