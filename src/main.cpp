#include <iostream> 
#include <string>   
#include <cmath>    
#include <cstdlib>  
#include "malla3d.h"
#include <opencv2/core.hpp>

int main() {
  std::cout << "OpenCV version: " << CV_VERSION << std::endl;

    Malla3D malla;

    malla.load_obj("models/214_izq_posicionado/214_izq_posicionado.obj");

  return 0;
}