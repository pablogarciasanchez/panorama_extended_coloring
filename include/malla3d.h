#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED
#include <vector>
#include <glm/glm.hpp>
#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>

class Malla3D{
public:
   Malla3D();
   bool load_obj(const std::string path);
   void rotate_mesh(float angle);

private:
   void calc_normals();
   void calc_centroid();
   void calc_distance();
   void scale_to_unit();
   
   std::vector<glm::vec3> vertexs;
   std::vector<std::vector<int>> facesIndex;
   glm::vec3 centroid;
   std::vector<glm::vec3> normals;
   double d_max;
} ;


#endif
