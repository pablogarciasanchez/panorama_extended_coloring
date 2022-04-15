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

    // glm::vec3 orig(10,0,0);
    // glm::vec3 dir(-1,0,0);
    // glm::vec3 p1(2,-2,-2);
    // glm::vec3 p2(2,0,2);
    // glm::vec3 p3(2,2,-2);

    // glm::vec3 pos;
    // glm::vec2 hit;

    // float dist = 0;

    // if(glm::intersectRayTriangle(orig, dir, p1, p2, p3, hit, dist)){
    //     std::cout << "Hit: " << hit.x << ", " << hit.y << std::endl;
    //     std::cout << "Dist: " << dist << std::endl;
    // } else {
    //     std::cout << "No hit" << std::endl;
    // }

    // std::vector<glm::vec3> triangle = {p1, p2, p3};
    // glm::vec3 hit_point(0,0,0);

    // if(RayIntersectsTriangle(orig, dir, triangle, hit_point)){
    //     std::cout << "Hit_point: " << hit_point.x << ", " << hit_point.y << ", " << hit_point.z << std::endl;
    // } else {
    //     std::cout << "No hit" << std::endl;
    // }

    malla.calculatePanorama(SDM, X, 1, 4);

    

  return 0;
}