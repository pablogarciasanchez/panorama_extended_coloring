#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED
#include <vector>
#include <glm/glm.hpp>
#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <glm/gtx/intersect.hpp>
#include <omp.h>

enum Axis {X, Y, Z};
enum Map {SDM, NDM};

class Malla3D{
public:
   Malla3D();
   bool load_obj(const std::string path);
   void rotate_mesh(float angle);
   void calculatePanorama(Map map, Axis axis, float precision, int power);

private:
   std::vector<glm::vec3> vertexs;
   std::vector<std::vector<int>> facesIndex;
   std::vector<glm::vec3> normals;
   glm::vec3 centroid;
   double d_max;
   double height;
   double radius;
   int B = 180;

   void calc_normals();
   void calc_centroid();
   void calc_distance();
   void scale_to_unit();

   std::vector<std::vector<int>> filter_faces(Axis axis, float v, float trheshold);

   bool RayIntersectsTriangle(glm::vec3 rayOrigin, 
                              glm::vec3 rayVector, 
                              std::vector<glm::vec3> inTriangle,
                              glm::vec3& outIntersectionPoint);

   glm::vec3 get_orig(Axis axis, float v, int degree);
   glm::vec3 get_dir(Axis axis, int degree);
   std::vector<float> feature_map(Map map, 
                                 Axis axis, 
                                 std::vector<glm::vec3> directions, 
                                 std::vector<glm::vec3> origins);
} ;


#endif
