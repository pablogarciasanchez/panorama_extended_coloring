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
#include <glm/gtx/vector_angle.hpp>
#include <omp.h>
#include <set>
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc.hpp>
#include "aux.h"


class Malla3D{
public:
	Malla3D();
	bool load_obj(const std::string path);
	void export_obj(const std::string path, bool filter = false);
	void rotate_mesh(Axis axis_rot, float angle);
	void calculate_panorama(Map map, Axis axis, float precision, int power = 4);
	void export_panorama(Map map, Axis axis, std::string output, bool extended = true);
	void mesh_pose_norm(Axis rot, Map map, Axis axis, std::string output, int angle_pass = 1,
						float precision = 1, int power = 4);
						
private:
	std::vector<glm::vec3> vertexs;
	std::vector<std::vector<int>> facesIndex;
	std::vector<std::vector<std::vector<int>>> facesIndex_filter;

	std::vector<std::vector<float>> panorama;
	std::vector<std::vector<float>> panorama_extended;

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

	bool point_in_triangle(glm::vec3 p, glm::vec3 f1, glm::vec3 f2, glm::vec3 f3);

	int point_face(glm::vec3 p);

	void filter_faces(Axis axis, float precision);

	bool RayIntersectsTriangle(glm::vec3 rayOrigin, 
								glm::vec3 rayVector, 
								glm::vec3 vertex0,
								glm::vec3 vertex1,
								glm::vec3 vertex2,
								glm::vec3& outIntersectionPoint);

	glm::vec3 get_orig(Axis axis, float v, float precision);
	glm::vec3 get_dir(Axis axis, float v, float angle);
	float get_height(Axis axis, float v, float precision);
	int get_sector(glm::vec2 point);
	int get_sector(float angle);

	float feature_map(Map map, Axis axis, float precision, float v, int power, 
						glm::vec3 origin, std::vector<glm::vec3> &colisiones,
						std::vector<int> &faces_hit);

	float compute_panorama_symetry();
} ;


#endif
