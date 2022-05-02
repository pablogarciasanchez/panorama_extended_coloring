#include <iostream> 
#include <string>   
#include <cmath>    
#include <cstdlib>
#include "malla3d.h"
#include "panorama.h"

/** @file main.cpp
 *  @brief Example of use of Malla3D
 * 	@author [Alejandro Manzanares Lemus](https://github.com/Alexmnzlms)
 * 
 */

int main(int argc, char * argv[]) {

	if(argc != 3){
		std::cout << "Wrong parameters" << std::endl;
		std::cout << "bin/panorama_extended [relive route to 3D model] [output folder]" << std::endl;
		exit(-1);
	}

	Malla3D malla(argv[1]);

	std::string output_folder = argv[2];

	malla.mesh_pose_norm(X,SDM,Z,output_folder,15);

	malla.calculate_panorama(SDM, X, 0.5, 4);
	malla.export_panorama(SDM,X,output_folder);
	malla.calculate_panorama(NDM, X, 0.5, 4);
	malla.export_panorama(NDM,X,output_folder);
	combine_panorama(X,output_folder);

	malla.calculate_panorama(SDM, Y, 0.5, 4);
	malla.export_panorama(SDM,Y,output_folder);
	malla.calculate_panorama(NDM, Y, 0.5, 4);
	malla.export_panorama(NDM,Y,output_folder);
	combine_panorama(Y,output_folder);

	malla.calculate_panorama(SDM, Z, 0.5, 4);
	malla.export_panorama(SDM,Z,output_folder);
	malla.calculate_panorama(NDM, Z, 0.5, 4);
	malla.export_panorama(NDM,Z,output_folder);
	combine_panorama(Z,output_folder);
	
	return 0;
}