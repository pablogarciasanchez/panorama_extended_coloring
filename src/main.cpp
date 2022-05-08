#include "malla3d.h"

/** @file main.cpp
 *  @brief Example of use of Malla3D
 * 	@author [Alejandro Manzanares Lemus](https://github.com/Alexmnzlms)
 * 
 */



int main(int argc, char * argv[]) {

	if(argc != 4){
		std::cout << "Wrong parameters" << std::endl;
		std::cout << "bin/panorama_extended [model name] [relive route to 3D model]"
		<< " [output folder PANORAMA extended]"  << std::endl;
		exit(-1);
	}

	std::string name = argv[1];
	std::string path = argv[2];
	std::string output_folder_pe = argv[3];

	std::cout << "Loading " << name << "\tPath: " << path << "..." << std::endl;

	Malla3D malla(name, path);

	std::cout << "Loaded " << malla.get_name() << std::endl;

	

	malla.mesh_pose_norm(X,SDM,Z,15);

	malla.calculate_panorama(SDM, X, 0.5, 4);
	malla.calculate_panorama(NDM, X, 0.5, 4);

	malla.combine_panorama(X,output_folder_pe,false);

	malla.calculate_panorama(SDM, Y, 0.5, 4);
	malla.calculate_panorama(NDM, Y, 0.5, 4);

	malla.combine_panorama(Y,output_folder_pe,false);

	malla.calculate_panorama(SDM, Z, 0.5, 4);
	malla.calculate_panorama(NDM, Z, 0.5, 4);

	malla.combine_panorama(Z,output_folder_pe,false);

	malla.concat_panorama(SDM,output_folder_pe,false);
	malla.concat_panorama(NDM,output_folder_pe,false);
	malla.concat_panorama(GNDM,output_folder_pe,false);
	
	return 0;
}