#include "malla3d.h"

/** @file main.cpp
 *  @brief Example of use of Malla3D
 * 	@author [Alejandro Manzanares Lemus](https://github.com/Alexmnzlms)
 * 
 */



int main(int argc, char * argv[]) {

	if(argc != 5){
		std::cout << "Wrong parameters" << std::endl;
		std::cout << "bin/panorama_extended [model name] [relive route to 3D model]"
		<< " [output folder PANORAMA extended] [output folder feature map]"  << std::endl;
		exit(-1);
	}

	std::string name = argv[1];
	std::string path = argv[2];
	std::string output_folder_pe = argv[3];
	std::string output_folder_fm = argv[4];

	std::cout << "Loading " << name << "\tPath: " << path << "..." << std::endl;

	Malla3D malla(name, path);

	if (malla.num_vertexs() > 0){
		std::cout << "Loaded " << malla.get_name() << std::endl;

		std::string rot_name = malla.get_name() + "_0";
		malla.set_name(rot_name);

		// malla.mesh_pose_norm();

		malla.calculate_panorama(SDM, X, 1, 4);
		malla.calculate_panorama(NDM, X, 1, 4);

		malla.calculate_panorama(SDM, Y, 1, 4);
		malla.calculate_panorama(NDM, Y, 1, 4);

		malla.calculate_panorama(SDM, Z, 1, 4);
		malla.calculate_panorama(NDM, Z, 1, 4);

		malla.combine_panorama(X,output_folder_pe,false);
		malla.combine_panorama(Y,output_folder_pe,false);
		malla.combine_panorama(Z,output_folder_pe,false);

		malla.concat_panorama(SDM,output_folder_fm,false);
		malla.concat_panorama(NDM,output_folder_fm,false);
		malla.concat_panorama(GNDM,output_folder_fm,false);

		int cont = 0;
		for(int ax = 0; ax < 3; ax++){
			std::cout << "Loading " << name << "\tPath: " << path << "..." << std::endl;

			Malla3D malla(name, path);

			std::cout << "Loaded " << malla.get_name() << std::endl;
			std::string orig_name = malla.get_name();

			int ind = 1;
			float angle = 15.0;
			for(float i = angle; i <= 180.0; i += angle, ind++){

				std::string rot_name = orig_name + "_" + std::to_string(cont);
				malla.set_name(rot_name);
				cont++;

				std::cout << "Rotando en el eje: " << axis_to_string((Axis)ax)
				<< " un angulo de: " << ind*angle << std::endl;
				std::cout << "ind " << ind << std::endl;
				std::cout << "angle " << angle << std::endl;

				malla.rotate_mesh((Axis)ax,angle*(M_PI/180.0));
				malla.calculate_panorama(SDM, X, 1, 4);
				malla.calculate_panorama(NDM, X, 1, 4);

				malla.calculate_panorama(SDM, Y, 1, 4);
				malla.calculate_panorama(NDM, Y, 1, 4);

				malla.calculate_panorama(SDM, Z, 1, 4);
				malla.calculate_panorama(NDM, Z, 1, 4);

				malla.combine_panorama(X,output_folder_pe,false);
				malla.combine_panorama(Y,output_folder_pe,false);
				malla.combine_panorama(Z,output_folder_pe,false);

				malla.concat_panorama(SDM,output_folder_fm,false);
				malla.concat_panorama(NDM,output_folder_fm,false);
				malla.concat_panorama(GNDM,output_folder_fm,false);			
			}
		}
	}
	return 0;
}