#include "malla3d.h"


Malla3D::Malla3D(){}


void Malla3D::calc_centroid(){
	float sum_x, sum_y, sum_z;
	sum_x = sum_y = sum_z = 0.0;
	
	for(int i = 0; i < vertexs.size(); i++){
		sum_x += vertexs[i].x;
		sum_y += vertexs[i].y;
		sum_z += vertexs[i].z;
	}

	sum_x /= vertexs.size();
	sum_y /= vertexs.size();
	sum_z /= vertexs.size();

	centroid.x = sum_x;
	centroid.y = sum_y;
	centroid.z = sum_z;
}

void Malla3D::calc_normals(){
	normals.clear();
	glm::vec3 v1, v2, v3;
	for(int i = 0; i < facesIndex.size(); i++){
		v1 = vertexs[facesIndex[i][0]];
		v2 = vertexs[facesIndex[i][1]];
		v3 = vertexs[facesIndex[i][2]];

		glm::vec3 cross_p = glm::cross((v2-v1), (v3-v1));

		cross_p = glm::normalize(cross_p);

		normals.push_back(cross_p);
	}
}

void Malla3D::calc_distance(){
	float dist;
	float max = glm::distance(vertexs[0],centroid);
	for(int i = 1; i < vertexs.size(); i++){
		dist = glm::distance(vertexs[i],centroid);
		if (dist > max){
			max = dist;
		}
	}

	d_max = max;
	radius = 2*d_max;
	height = 2*radius;
}

void Malla3D::scale_to_unit(){
	std::vector<glm::vec3> v_unit;

	for(int i = 0; i < vertexs.size(); i++){
		glm::vec3 v_orig = vertexs[i] - centroid;
		glm::vec3 v_scale = v_orig;
		v_scale.x = v_scale.x / d_max;
		v_scale.y = v_scale.y / d_max;
		v_scale.z = v_scale.z / d_max;

		v_unit.push_back(v_scale);
	}

	vertexs = v_unit;
	centroid.x = 0.0;
	centroid.y = 0.0;
	centroid.z = 0.0;
	calc_normals();
	calc_distance();

	std::cout << vertexs.size() << std::endl;
	std::cout << facesIndex.size() << std::endl;
	// std::cout << normals.size() << std::endl;
	// std::cout << centroid.x << ", " << centroid.y << ", " << centroid.z << std::endl;
	// std::cout << d_max << std::endl;
}

void Malla3D::rotate_mesh(Axis axis_rot, float angle){
	std::vector<glm::vec3> mesh_rotate;
	glm::vec3 rotate_vertex;
	switch (axis_rot)
	{
	case X:
		for(int i = 0; i < vertexs.size(); i++){
			rotate_vertex.x = vertexs[i].x;
			rotate_vertex.y = vertexs[i].y*cos(angle) - vertexs[i].z*sin(angle);
			rotate_vertex.z = vertexs[i].y*sin(angle) + vertexs[i].z*cos(angle);

			mesh_rotate.push_back(rotate_vertex);
		}
		break;

	case Y:
		for(int i = 0; i < vertexs.size(); i++){
			rotate_vertex.x = vertexs[i].x*cos(angle) - vertexs[i].z*sin(angle);
			rotate_vertex.y = vertexs[i].y;
			rotate_vertex.z = vertexs[i].x*sin(angle) + vertexs[i].z*cos(angle);

			mesh_rotate.push_back(rotate_vertex);
		}
		break;

	case Z:
		for(int i = 0; i < vertexs.size(); i++){
			rotate_vertex.x = vertexs[i].x*cos(angle) - vertexs[i].y*sin(angle);
			rotate_vertex.y = vertexs[i].x*sin(angle) + vertexs[i].y*cos(angle);
			rotate_vertex.z = vertexs[i].z;

			mesh_rotate.push_back(rotate_vertex);
		}
		break;
	}
	
	vertexs.clear();
	vertexs = mesh_rotate;
	calc_normals();
	calc_distance();
}

bool Malla3D::load_obj(const std::string path){
	std::vector< unsigned int > vertexIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::ifstream file;
	std::string line;
	std::string header;
	std::string face_line;
	std::string face;
	std::string delimiter = "/";
	file.open(path);

	if( !file.is_open() ){
		std::cout << "Impossible to open the file !" << std::endl;
		return false;
	}

	while(std::getline(file,line)){
		//std::cout << line << std::endl;
		file >> header;
		//std::cout << header << std::endl;
		if(header == "v"){
			// std::cout << header << line << std::endl;
			glm::vec3 vertex;
			file >> vertex.x;
			file >> vertex.y;
			file >> vertex.z;
			vertexs.push_back(vertex);
		} else if (header == "f"){
			std::string vertex1, vertex2, vertex3;
			std::vector<int> vertexIndex;
			file >> face_line;
			vertex1 = face_line.substr(0, face_line.find(delimiter));
			vertexIndex.push_back(std::stoi(vertex1)-1);

			file >> face_line;
			vertex2 = face_line.substr(0, face_line.find(delimiter));
			vertexIndex.push_back(std::stoi(vertex2)-1);

			file >> face_line;
			vertex3 = face_line.substr(0, face_line.find(delimiter));
			vertexIndex.push_back(std::stoi(vertex3)-1);

			facesIndex.push_back(vertexIndex);
		}
	}

	// for(int i = 0; i < vertexIndices.size(); i++){
	//     unsigned int vertexIndex = vertexIndices[i];
	//     //std::cout << vertexIndices[i] << std::endl;
	//     glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
	//     vertexs.push_back(vertex);
	// }

	// for(int i = 0; i < vertexs.size(); i++){
	//     std::cout << vertexs[i].x << ", " << vertexs[i].y << ", " << vertexs[i].z << std::endl;
	// }

	// for(int i = 0; i < facesIndex.size(); i++){
	//     std::cout << facesIndex[i][0] << ", " << facesIndex[i][1] << ", " << facesIndex[i][2] << std::endl;
	// }

	calc_centroid();
	calc_normals();
	calc_distance();

	std::cout << vertexs.size() << std::endl;
	std::cout << facesIndex.size() << std::endl;
	// std::cout << normals.size() << std::endl;
	// std::cout << centroid.x << ", " << centroid.y << ", " << centroid.z << std::endl;
	// std::cout << d_max << std::endl;

	scale_to_unit();

	return true;
}

void Malla3D::export_obj(const std::string path, bool filter){
	std::ofstream file;
	file.open(path);

	for(int i = 0; i < vertexs.size(); i++){
		file << "v " << vertexs[i][0] << " " << vertexs[i][1] << " " << vertexs[i][2] << std::endl;
	}

	if(filter){
		// for(int j = 0; j < facesIndex_filter.size(); j++){
		//     file << "f " << facesIndex_filter[j][0]+1 << " " 
		//     << facesIndex_filter[j][1]+1 << " " << facesIndex_filter[j][2]+1 
		//     << std::endl;
		// }
	} else {
		for(int j = 0; j < facesIndex.size(); j++){
			file << "f " << facesIndex[j][0]+1 << " " 
			<< facesIndex[j][1]+1 << " " << facesIndex[j][2]+1 
			<< std::endl;
		}
	}
	

	file.close();
}

bool Malla3D::RayIntersectsTriangle(glm::vec3 rayOrigin, 
									glm::vec3 rayVector, 
									glm::vec3 vertex0,
									glm::vec3 vertex1,
									glm::vec3 vertex2,
									glm::vec3& outIntersectionPoint){
	const float EPSILON = 0.00000001;
	glm::vec3 edge1, edge2, h, s, q;
	float a,f,u,v;
	edge1 = vertex1 - vertex0;
	edge2 = vertex2 - vertex0;
	h = glm::cross(rayVector,edge2);
	a = glm::dot(edge1,h);

	if (a > -EPSILON && a < EPSILON){
		return false;
	}

	f = 1.0/a;
	s = rayOrigin - vertex0;
	u = f * glm::dot(s,h);

	if (u < 0.0 || u > 1.0){
		return false;
	}

	q = glm::cross(s,edge1);
	v = f * glm::dot(rayVector,q);

	if (v < 0.0 || u + v > 1.0){
		return false;
	}
		
	float t = f * glm::dot(edge2,q);

	if (t > EPSILON){
		outIntersectionPoint = rayOrigin + rayVector * t;
		return true;
	}
	else{
		return false;
	}
		
}

glm::vec3 Malla3D::get_orig(Axis axis, float v, float precision){
	glm::vec3 orig;

	switch (axis)
	{
	case X:
		orig.x = centroid.x - height/2 + v * height/(B/precision);
		orig.y = centroid.y;
		orig.z = centroid.z;
		break;

	case Y:
		orig.x = centroid.x;
		orig.y = centroid.y - height/2 + v * height/(B/precision);
		orig.z = centroid.z;
		break;

	case Z:
		orig.x = centroid.x;
		orig.y = centroid.y;
		orig.z = centroid.z - height/2 + v * height/(B/precision);
		break;
	}

	return orig;
}

glm::vec3 Malla3D::get_dir(Axis axis, float v, float angle){
	glm::vec3 dir;
	
	switch (axis)
	{
	case X:
		dir.x = 0.0;
		dir.y = radius * cos(angle);
		dir.z = radius * sin(angle);
		break;

	case Y:
		dir.x = radius * cos(angle);
		dir.y = 0.0;
		dir.z = radius * sin(angle);
		break;

	case Z:
		dir.x = radius * cos(angle);
		dir.y = radius * sin(angle);
		dir.z = 0.0;
		break;
	}

	return glm::normalize(dir);
}

float Malla3D::get_height(Axis axis, float v, float precision){
	float h;

	switch (axis)
	{
	case X:
		h = centroid.x - height/2 + v * height/(B/precision);
		break;

	case Y:
		h = centroid.y - height/2 + v * height/(B/precision);
		break;

	case Z:
		h = centroid.z - height/2 + v * height/(B/precision);
		break;
	}

	return h;
}

int Malla3D::get_sector(glm::vec2 point){
	int sector = -1;
	float x = point.x;
	float y = point.y;

	if(x >= 0 && y >= 0){
		sector = 1;
	} else if(x < 0 && y >= 0){
		sector = 2;
	} else if(x < 0 && y < 0){
		sector = 3;
	} else if(x >= 0 && y < 0){
		sector = 4;
	}

	return sector;
}

int Malla3D::get_sector(float angle){
	int sector = -1;
	float x = radius * cos(angle);
	float y = radius * sin(angle);

	if(x >= 0 && y >= 0){
		sector = 1;
	} else if(x < 0 && y >= 0){
		sector = 2;
	} else if(x < 0 && y < 0){
		sector = 3;
	} else if(x >= 0 && y < 0){
		sector = 4;
	}

	return sector;
}

bool Malla3D::point_in_triangle(glm::vec3 p, glm::vec3 f1, glm::vec3 f2, glm::vec3 f3){
	bool point_in = true;

	f1 -= p;
	f2 -= p;
	f3 -= p;

	glm::vec3 u = glm::cross(f2,f3);
	glm::vec3 v = glm::cross(f3,f1);
	glm::vec3 w = glm::cross(f1,f2);

	if(glm::dot(u,v) < 0.0){
		point_in = false;
	}

	if(glm::dot(u,w) < 0.0){
		point_in = false;
	}

	return point_in;
}

int Malla3D::point_face(glm::vec3 p){
	int face = -1;
	bool salir = false;
	for(int i = 0; i < facesIndex.size() && !salir; i++){
		glm::vec3 f1 = vertexs[facesIndex[i][0]];
		glm::vec3 f2 = vertexs[facesIndex[i][1]];
		glm::vec3 f3 = vertexs[facesIndex[i][2]];
		if(point_in_triangle(p,f1,f2,f3)){
			salir = true;
			face = i;
		}
	}

	return face;
}

	void Malla3D::filter_faces(Axis axis, float precision){
		float v_height;

		float threshold = 0.5;

		float v_length;

		bool salir = false;

		float coord_axis;

		float angle;

		glm::vec2 point_sector;
		glm::vec2 point_angle;

		std::vector<int> facesIndex_height_temp;
		std::vector<int> facesIndex_ang_temp;
		std::vector<std::vector<int>> facesIndex_height;

		facesIndex_filter.clear();

		for(float v = 0; v < (B/precision); v++){

			v_height = get_height(axis,v,precision);

			v_length = height/(B/precision);
			//v_length = height/B;

			facesIndex_height.clear();
			facesIndex_height_temp.clear();
			
			for(int i = 0; i < facesIndex.size(); i++){
				salir = false;
				for(int j = 0; j < facesIndex[i].size() && !salir; j++){
					switch (axis)
					{
					case X:
						coord_axis = vertexs[facesIndex[i][j]].x;
						break;

					case Y:
						coord_axis = vertexs[facesIndex[i][j]].y;
						break;

					case Z:
						coord_axis = vertexs[facesIndex[i][j]].z;
						break;  
					}
					
					if((coord_axis >= (v_height - threshold*v_length)) &&
						(coord_axis <= (v_height + threshold*v_length))){
						facesIndex_height_temp.push_back(i);
						salir = true;
					}
				}
			}

			for(int sector = 1; sector <= 4; sector++){
				facesIndex_ang_temp.clear();

				for(int i = 0; i < facesIndex_height_temp.size(); i++){
					salir = false;
					for(int j = 0; j < facesIndex[facesIndex_height_temp[i]].size() && !salir; j++){
						switch (axis)
						{
						case X:
							point_sector.x = vertexs[facesIndex[facesIndex_height_temp[i]][j]].y;
							point_sector.y = vertexs[facesIndex[facesIndex_height_temp[i]][j]].z;
							break;

						case Y:
							point_sector.x = vertexs[facesIndex[facesIndex_height_temp[i]][j]].x;
							point_sector.y = vertexs[facesIndex[facesIndex_height_temp[i]][j]].z;
							break;

						case Z:
							point_sector.x = vertexs[facesIndex[facesIndex_height_temp[i]][j]].x;
							point_sector.y = vertexs[facesIndex[facesIndex_height_temp[i]][j]].y;
							break;  
						}

						if(get_sector(point_sector) == sector){
							facesIndex_ang_temp.push_back(facesIndex_height_temp[i]);
							salir = true;
						}
					}
				}

				facesIndex_height.push_back(facesIndex_ang_temp);
				// if(facesIndex_ang_temp.size() > 0){
				// 	std::cout << sector << " " << v*precision << " " << v_height  
				// 	<< "    \t Filtrado de caras (sec): " << facesIndex_ang_temp.size() << std::endl;
				// }
			}

			
			// if(facesIndex_height_temp.size() > 0){
			// 	std::cout << v*precision << " " << v_height << "\t Filtrado de caras: " << facesIndex_height_temp.size() << std::endl;
			// }

			facesIndex_filter.push_back(facesIndex_height);
		}
	}

float Malla3D::feature_map(Map map, Axis axis, float precision, float v, int power, glm::vec3 origin, 
							std::vector<glm::vec3> &colisiones, std::vector<int> &faces_hit){

	float feature_value = 0.0;

	float dist;
	float dist_max = -1;
	float ind_max = -1;

	glm::vec3 ray;
	glm::vec3 normal;

	for(int c = 0; c < colisiones.size(); c++){ 
		dist = glm::distance(colisiones[c],origin); 
		if((dist > dist_max) && (dist > 0)){
			ind_max = c;
			dist_max = dist;
		}
	}

	assert(ind_max != -1);

	switch (map)
	{
	case SDM:
		assert(dist_max >= 0);
		feature_value = dist_max;
		
		break;

	case NDM:
		ray = colisiones[ind_max] - get_orig(axis,v,precision);
		ray = glm::normalize(ray);
		normal = normals[faces_hit[ind_max]];
		feature_value = glm::angle(ray,normal);
		feature_value = cos(feature_value);
		feature_value = std::abs(feature_value);
		feature_value = std::pow(feature_value,power);
		break;
	}
	

	assert(feature_value >= 0 && feature_value <= 1.0);
	return feature_value;
}


void Malla3D::calculate_panorama(Map map, Axis axis, float precision, int power){
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	begin = std::chrono::steady_clock::now();

	panorama.clear();
	panorama_extended.clear();
	
	glm::vec3 direction;
	glm::vec3 origin;

	int n_colisiones = 0;

	std::vector<glm::vec3> colisiones;
	std::vector<int> face_hit;

	filter_faces(axis, precision);

	end = std::chrono::steady_clock::now();
	std::cout << "Face filtering"
	<< "\t Time: " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;

	begin = std::chrono::steady_clock::now();

	for(float i = 0; i < (B/precision); i++){
		std::vector<float> row(2*(B/precision), 0.0);
		std::vector<float> row_ext(2*(B/precision)*1.5, 0.0);
		panorama.push_back(row);
		panorama_extended.push_back(row_ext);
	}

	for(float v = 0; v < (B/precision); v++){

		for(float u = 0; u < 2*(B/precision); u++){
			float angle = u*2*M_PI / (2*(B/precision));
			int s = get_sector(angle) - 1;

			origin = get_orig(axis,v,precision);
			direction = get_dir(axis,v,angle);

			for(int j = 0; j < facesIndex_filter[v][s].size(); j++){
				glm::vec3 hit_point;
				glm::vec2 hit;
				float dist;
				// std::vector<glm::vec3> triangle_points;
				glm::vec3 t1 = vertexs[facesIndex[facesIndex_filter[v][s][j]][0]];
				glm::vec3 t2 = vertexs[facesIndex[facesIndex_filter[v][s][j]][1]];
				glm::vec3 t3 = vertexs[facesIndex[facesIndex_filter[v][s][j]][2]];
				
				// for(int k = 0; k < facesIndex[facesIndex_filter[v][s][j]].size(); k++){
				// 	triangle_points.push_back(vertexs[facesIndex[facesIndex_filter[v][s][j]][k]]);  
				// }

				if(RayIntersectsTriangle(origin, direction, t1, t2, t3, hit_point)){
					n_colisiones++;
					colisiones.push_back(hit_point);
					face_hit.push_back(facesIndex_filter[v][s][j]);
				} 
			}
			
			if(n_colisiones > 0){
				panorama[v][u] = feature_map(map, axis, precision, v, power, origin, colisiones, face_hit);
			}
			
			n_colisiones = 0;
			colisiones.clear();
			face_hit.clear();
		}
		
	}

	for(int i = 0; i < panorama.size(); i++){
		for(int j = 0; j < panorama[i].size(); j++){
			panorama[i][j] = (panorama[i][j] * 255);
			assert(panorama[i][j] <= 255.0 && panorama[i][j] >= 0.0);
		}
	}

	int max = 2*(B/precision);
	for(int i = 0; i < panorama_extended.size(); i++){
		for(int j = 0; j < panorama_extended[i].size(); j++){
			panorama_extended[i][j] = panorama[i][j%max];
		}
	}

	end = std::chrono::steady_clock::now();
	std::cout << "Map: " <<  map_to_string(map)
	<< "\t Time: " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;
}

void Malla3D::export_panorama(Map map, Axis axis, std::string output, bool extended){
	cv::Mat panorama_cv;

	if(extended){
		panorama_cv = cv::Mat(0, panorama_extended[0].size(), CV_32F);

		for(int i = panorama_extended.size()-1; i >= 0; i--){
			cv::Mat row(1, panorama_extended[i].size(), CV_32F, panorama_extended[i].data());
			panorama_cv.push_back(row);
		}
	} else {
		panorama_cv = cv::Mat(0, panorama[0].size(), CV_32F);

		for(int i = panorama.size()-1; i >= 0; i--){
			cv::Mat row(1, panorama[i].size(), CV_32F, panorama[i].data());
			panorama_cv.push_back(row);
		}
	}
	

	std::string feature_map_name, laplacian_name;

	switch (map)
	{
	case SDM:
		feature_map_name = map_to_string(SDM);
		break;
	case NDM:
		feature_map_name = map_to_string(NDM);
		laplacian_name = "GNDM";
		break;
	}

	switch (axis)
	{
	case X:
		feature_map_name += "_X.png";
		laplacian_name += "_X.png";
		break;
	case Y:
		feature_map_name += "_Y.png";
		laplacian_name += "_Y.png";
		break;
	case Z:
		feature_map_name += "_Z.png";
		laplacian_name += "_Z.png";
		break;
	}

	if(map == NDM){
		cv::Mat laplace;
		cv::Laplacian(panorama_cv, laplace, CV_32F, 1);
		cv::imwrite(output + laplacian_name, laplace);
	} 
		
	cv::imwrite(output + feature_map_name, panorama_cv);
	
	
	// cv::Mat I = cv::imread(feature_map_name, 0);
	// cv::namedWindow( "Display window", CV_WINDOW_NORMAL );// Create a window for display.
	// cv::imshow( "Display window", I ); 
	// cv::waitKey(0);
}

float Malla3D::compute_panorama_symetry(){
	float height_sym = panorama.size();
	float width_sym = panorama[0].size();
	float m = 0.4 * height_sym;
	float n = 0.1 * width_sym;
	// std::cout << "m,n: " << m << "," << n << std::endl;
	// std::cout << "0.4,0.1: " << height_sym << "," << width_sym << std::endl;

	float sym = 0;
	float sym_diff = 0;
	int index_up, index_down;

	std::vector<float> sumas;
	
	for(int w = 0; w < width_sym; w++){
		sym = 0;
		for(int h = (height_sym/2 - m); h <= (height_sym/2 + m); h++){
			sym_diff = 0;
			for(int x = 1; x <= n; x++){
				index_up = w+x;
				index_down = w-x;
				if(index_down < 0){
					index_down = (int)(width_sym + index_down);
				}
				if(index_up > (int)width_sym){
					index_up = index_up % (int)width_sym;
				}

				// std::cout << "w-x,h,w+x: " << w << "-" << x << "," << h << "," << w << "+" << x << std::endl;
				// std::cout << "w-x,h,w+x: " << index_down << "," << h << "," << index_up << std::endl;
				// std::cout <<  panorama[h][index_down] << " " << panorama[h][index_up] << std::endl;
				sym_diff += abs(panorama[h][index_down] - panorama[h][index_up]);
				// std::cout << x << " " << abs(panorama[h][index_down] - panorama[h][index_up]) << "->" << suma << std::endl;
			}
			sym_diff = (1/n) * sym_diff;
			sym += sym_diff;
		}
		
		sym = (1/(2*m)) * sym;
		sym = 1.0 - sym;
		//std::cout << w << "\tSuma: " << sym << std::endl;
		sumas.push_back(sym);
	}

	float max = -1000000.0;
	for(int i = 0; i < sumas.size(); i++){
		if(max < sumas[i]){
			max = sumas[i];
		}
	}
	return max;
}

void Malla3D::mesh_pose_norm(Axis rot, Map map, Axis axis, std::string output, 
							int angle_pass, float precision, int power){
	assert(angle_pass != 0);
	float angle = angle_pass * (M_PI/180.0);;
	std::vector<float> syms;
	float sym_max = -1000000;
	int ind_max = -1;
	std::vector<glm::vec3> vertexs_aux(vertexs);

	int ind = 0;
	for(float i = 0; i <= 180; i+=angle_pass, ind++){
		std::cout << "Rotation angle: " << i << " " << ind * angle << std::endl;
		calculate_panorama(map,axis,precision,power);
		float sym = compute_panorama_symetry();
		syms.push_back(sym);
		std::cout << "Symmetry value: " << sym << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;
		export_panorama(map,axis,output,false);
		rotate_mesh(rot,angle);
	}

	for(int j = 0; j < syms.size(); j++){
		if(sym_max < syms[j]){
			sym_max = syms[j];
			ind_max = j;
		}
	}

	std::cout << "Max sym rot angle: " << ind_max*angle_pass << std::endl;
	std::cout << "-----------------------------------------------" << std::endl;
	vertexs = vertexs_aux;
	if(ind_max*angle_pass != 0){
		rotate_mesh(rot,ind_max*angle_pass*(M_PI/180.0));
	}
}

