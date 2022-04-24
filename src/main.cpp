#include <iostream> 
#include <string>   
#include <cmath>    
#include <cstdlib>
#include "aux.h"
#include "malla3d.h"
#include "panorama.h"

int main() {
	std::cout << "OpenCV version: " << CV_VERSION << std::endl;

	Malla3D malla;

	malla.load_obj("models/214_izq_posicionado/214_izq_posicionado.obj");
	malla.export_obj("models/214_izq_posicionado/214_izq_posicionado_reduct.obj");

	// malla.load_obj("models/214_izq_posicionado/214_izq_posicionado_simple.obj");
	// malla.export_obj("models/214_izq_posicionado/214_izq_posicionado_simple_reduct.obj");
	
	// malla.load_obj("models/214_izq_posicionado/moto_simple_1.obj");
	// malla.export_obj("models/214_izq_posicionado/moto_simple_1_reduct.obj");

	malla.calculate_panorama(SDM, X, 1, 4);
	malla.export_panorama(SDM,X);
	malla.calculate_panorama(NDM, X, 0.5, 4);
	malla.export_panorama(NDM,X);
	combine_panorama(X);

	malla.calculate_panorama(SDM, Y, 0.5, 4);
	malla.export_panorama(SDM,Y);
	malla.calculate_panorama(NDM, Y, 0.5, 4);
	malla.export_panorama(NDM,Y);
	combine_panorama(Y);

	malla.calculate_panorama(SDM, Z, 0.5, 4);
	malla.export_panorama(SDM,Z);
	malla.calculate_panorama(NDM, Z, 0.5, 4);
	malla.export_panorama(NDM,Z);
	combine_panorama(Z);
	
	malla.mesh_pose_norm(SDM,X,1);

	return 0;
}