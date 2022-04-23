#include <iostream> 
#include <string>   
#include <cmath>    
#include <cstdlib>  
#include "malla3d.h"

int main() {
  std::cout << "OpenCV version: " << CV_VERSION << std::endl;

    Malla3D malla;

    malla.load_obj("models/214_izq_posicionado/214_izq_posicionado.obj");
    malla.export_obj("models/214_izq_posicionado/214_izq_posicionado_reduct.obj");

    // malla.load_obj("models/214_izq_posicionado/cubo.obj");
    // malla.export_obj("models/214_izq_posicionado/cubo_reduct.obj");

    malla.calculatePanorama(SDM, X, 0.5, 4);
    malla.calculatePanorama(SDM, Y, 0.5, 4);
    malla.calculatePanorama(SDM, Z, 0.5, 4);

    malla.calculatePanorama(NDM, X, 0.5, 4);
    malla.calculatePanorama(NDM, Y, 0.5, 4);
    malla.calculatePanorama(NDM, Z, 0.5, 4);

  return 0;
}