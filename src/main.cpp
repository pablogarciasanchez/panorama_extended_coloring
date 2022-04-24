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
	
	// malla.load_obj("models/214_izq_posicionado/cube.obj");
	// malla.export_obj("models/214_izq_posicionado/cube_reduct.obj");

	malla.calculatePanorama(SDM, X, 0.5, 4);
	malla.calculatePanorama(NDM, X, 0.5, 4);
	combine_panorama(X);

	malla.calculatePanorama(SDM, Y, 0.5, 4);
	malla.calculatePanorama(NDM, Y, 0.5, 4);
	combine_panorama(Y);

	malla.calculatePanorama(SDM, Z, 0.5, 4);
	malla.calculatePanorama(NDM, Z, 0.5, 4);
	combine_panorama(Z);
	

	return 0;
}