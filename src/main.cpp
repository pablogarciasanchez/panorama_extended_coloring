#include "aux.h"
#include "malla3d.h"
#include "panorama.h"

/** @file main.cpp
 *  @brief Example of use of Malla3D
 * 	@author [Alejandro Manzanares Lemus](https://github.com/Alexmnzlms)
 * 
 */

int main(int argc, char * argv[]) {

	if(argc != 4){
		std::cout << "Wrong parameters" << std::endl;
		std::cout << "bin/panorama_extended [relive route to 3D model] " 
		<< "[output folder feature map] [output folder PANORAMA extended]" 
		<< std::endl;
		exit(-1);
	}

	Malla3D malla(argv[1]);

	std::string output_folder_fm = argv[2];
	std::string output_folder_pe = argv[3];

	malla.mesh_pose_norm(X,SDM,Z,output_folder_fm,15);

	malla.calculate_panorama(SDM, X, 0.5, 4);
	malla.export_panorama(SDM,X,output_folder_fm);
	malla.calculate_panorama(NDM, X, 0.5, 4);
	malla.export_panorama(NDM,X,output_folder_fm);
	combine_panorama(X,output_folder_fm,output_folder_pe);

	malla.calculate_panorama(SDM, Y, 0.5, 4);
	malla.export_panorama(SDM,Y,output_folder_fm);
	malla.calculate_panorama(NDM, Y, 0.5, 4);
	malla.export_panorama(NDM,Y,output_folder_fm);
	combine_panorama(Y,output_folder_fm,output_folder_pe);

	malla.calculate_panorama(SDM, Z, 0.5, 4);
	malla.export_panorama(SDM,Z,output_folder_fm);
	malla.calculate_panorama(NDM, Z, 0.5, 4);
	malla.export_panorama(NDM,Z,output_folder_fm);
	combine_panorama(Z,output_folder_fm,output_folder_pe);

	concat_panorama(SDM,output_folder_fm,output_folder_pe);
	concat_panorama(NDM,output_folder_fm,output_folder_pe);
	concat_panorama(GNDM,output_folder_fm,output_folder_pe);
	
	return 0;
}