#include "malla3d.h"

/** @file main.cpp
 *  @brief Example of use of Malla3D
 * 	@author [Alejandro Manzanares Lemus](https://github.com/Alexmnzlms)
 * 
 */


void panorama(Malla3D& malla, std::string output_folder_pe, std::string output_folder_fm){
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

int main(int argc, char * argv[]) {

	srand (time(NULL));

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
		std::string orig_name = malla.get_name();
		malla.set_name(rot_name);

		// malla.mesh_pose_norm();

		int rot_angle_x1 = rand() % 11 + 5;
		int rot_angle_x2 = rand() % 11 + 5;
		int rot_angle_z1 = rand() % 11 + 5;
		int rot_angle_z2 = rand() % 11 + 5;

		float rot_radians_x1 = float(rot_angle_x1) * (M_PI/180.0);
		float rot_radians_x2 = 2*M_PI - (float(rot_angle_x2) * (M_PI/180.0));
		float rot_radians_z1 = float(rot_angle_z1) * (M_PI/180.0);
		float rot_radians_z2 = 2*M_PI - (float(rot_angle_z2) * (M_PI/180.0));

		
		Malla3D malla_x1(malla);
		rot_name = orig_name + "_16";
		malla_x1.set_name(rot_name);
		Malla3D malla_x2(malla);
		rot_name = orig_name + "_17";
		malla_x2.set_name(rot_name);
		Malla3D malla_z1(malla);
		rot_name = orig_name + "_18";
		malla_z1.set_name(rot_name);
		Malla3D malla_z2(malla);
		rot_name = orig_name + "_19";
		malla_z2.set_name(rot_name);

		std::cout << "Rotando en el eje X:" << rot_radians_x1 * (180.0/M_PI) << std::endl;
		malla_x1.rotate_mesh(X,rot_radians_x1);
		std::cout << "Rotando en el eje X:" << rot_radians_x2 * (180.0/M_PI)<< std::endl;
		malla_x2.rotate_mesh(X,rot_radians_x2);
		std::cout << "Rotando en el eje Z:" << rot_radians_z1 * (180.0/M_PI)<< std::endl;
		malla_z1.rotate_mesh(Z,rot_radians_z1);
		std::cout << "Rotando en el eje Z:" << rot_radians_z2 * (180.0/M_PI)<< std::endl;
		malla_z2.rotate_mesh(Z,rot_radians_z2);

		panorama(malla_x1,output_folder_pe,output_folder_fm);
		panorama(malla_x2,output_folder_pe,output_folder_fm);
		panorama(malla_z1,output_folder_pe,output_folder_fm);
		panorama(malla_z2,output_folder_pe,output_folder_fm);

		// panorama(malla,output_folder_pe,output_folder_fm);

		// int cont = 1;
		// for(int i = 0; i < 3; i++){
		// 	Malla3D malla_rot(malla);
		// 	std::string rot_name;

		// 	int rot_angle_y = rand() % 180 + 1;
		// 	float rot_radians_y = float(rot_angle_y) * (M_PI/180.0);
		// 	std::cout << "Rotando en el eje Y:" << rot_angle_y << std::endl;
		// 	malla_rot.rotate_mesh(Y,rot_radians_y);
		// 	rot_name = orig_name + "_" + std::to_string(cont);
		// 	malla_rot.set_name(rot_name);
		// 	cont++;

		// 	int rot_angle_x1 = rand() % 11 + 5;
		// 	int rot_angle_x2 = rand() % 11 + 5;
		// 	int rot_angle_z1 = rand() % 11 + 5;
		// 	int rot_angle_z2 = rand() % 11 + 5;

		// 	float rot_radians_x1 = float(rot_angle_x1) * (M_PI/180.0);
		// 	float rot_radians_x2 = 2*M_PI - (float(rot_angle_x2) * (M_PI/180.0));
		// 	float rot_radians_z1 = float(rot_angle_z1) * (M_PI/180.0);
		// 	float rot_radians_z2 = 2*M_PI - (float(rot_angle_z2) * (M_PI/180.0));

			
		// 	Malla3D malla_x1(malla_rot);
		// 	rot_name = orig_name + "_" + std::to_string(cont);
		// 	malla_x1.set_name(rot_name);
		// 	cont++;
		// 	Malla3D malla_x2(malla_rot);
		// 	rot_name = orig_name + "_" + std::to_string(cont);
		// 	malla_x2.set_name(rot_name);
		// 	cont++;
		// 	Malla3D malla_z1(malla_rot);
		// 	rot_name = orig_name + "_" + std::to_string(cont);
		// 	malla_z1.set_name(rot_name);
		// 	cont++;
		// 	Malla3D malla_z2(malla_rot);
		// 	rot_name = orig_name + "_" + std::to_string(cont);
		// 	malla_z2.set_name(rot_name);
		// 	cont++;

		// 	std::cout << "Rotando en el eje X:" << rot_radians_x1 * (180.0/M_PI) << std::endl;
		// 	malla_x1.rotate_mesh(X,rot_radians_x1);
		// 	std::cout << "Rotando en el eje X:" << rot_radians_x2 * (180.0/M_PI)<< std::endl;
		// 	malla_x2.rotate_mesh(X,rot_radians_x2);
		// 	std::cout << "Rotando en el eje Z:" << rot_radians_z1 * (180.0/M_PI)<< std::endl;
		// 	malla_z1.rotate_mesh(Z,rot_radians_z1);
		// 	std::cout << "Rotando en el eje Z:" << rot_radians_z2 * (180.0/M_PI)<< std::endl;
		// 	malla_z2.rotate_mesh(Z,rot_radians_z2);

		// 	panorama(malla_rot,output_folder_pe,output_folder_fm);
		// 	panorama(malla_x1,output_folder_pe,output_folder_fm);
		// 	panorama(malla_x2,output_folder_pe,output_folder_fm);
		// 	panorama(malla_z1,output_folder_pe,output_folder_fm);
		// 	panorama(malla_z2,output_folder_pe,output_folder_fm);

		// 	// malla.export_obj("214_Izq.obj");
		// 	// malla_rot.export_obj("214_Izq_rot.obj");
		// 	// malla_x1.export_obj("214_Izq_x1.obj");
		// 	// malla_x2.export_obj("214_Izq_x2.obj");
		// 	// malla_z1.export_obj("214_Izq_z1.obj");
		// 	// malla_z2.export_obj("214_Izq_z2.obj");

			
		// }
		
	}
	return 0;
}