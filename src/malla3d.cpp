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

void Malla3D::rotate_mesh(float angle){
    std::vector<glm::vec3> mesh_rotate;
    glm::vec3 rotate_vertex;
    for(int i = 0; i < vertexs.size(); i++){
        rotate_vertex.x = vertexs[i].x;
        rotate_vertex.y = vertexs[i].y*cos(angle) - vertexs[i].z*sin(angle);
        rotate_vertex.z = vertexs[i].y*sin(angle) + vertexs[i].z*cos(angle);

        mesh_rotate.push_back(rotate_vertex);
        

    }
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
                                    std::vector<glm::vec3> inTridegree,
                                    glm::vec3& outIntersectionPoint){
    //const float EPSILON = 0.000000001;
    const float EPSILON = 0.0;
    glm::vec3 vertex0 = inTridegree[0];
    glm::vec3 vertex1 = inTridegree[1];
    glm::vec3 vertex2 = inTridegree[2];
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

glm::vec3 Malla3D::get_orig(Axis axis, float v, float angle, float precision){
    glm::vec3 orig;

    switch (axis)
    {
    case X:
        orig.x = centroid.x - height/2 + v * height/(B/precision);
        orig.y = centroid.y + radius * cos(angle);
        orig.z = centroid.z + radius * sin(angle);
        break;

    case Y:
        orig.x = centroid.x + radius * cos(angle);
        orig.y = centroid.y - height/2 + v * height/(B/precision);
        orig.z = centroid.z + radius * sin(angle);
        break;

    case Z:
        orig.x = centroid.x + radius * cos(angle);
        orig.y = centroid.y + radius * sin(angle);
        orig.z = centroid.z - height/2 + v * height/(B/precision);
        break;
    }

    // switch (axis)
    // {
    // case X:
    //     orig.x = centroid.x - height/2 + v * height/(B/precision);
    //     orig.y = centroid.y;
    //     orig.z = centroid.z;
    //     break;

    // case Y:
    //     orig.x = centroid.x;
    //     orig.y = centroid.y - height/2 + v * height/(B/precision);
    //     orig.z = centroid.z;
    //     break;

    // case Z:
    //     orig.x = centroid.x;
    //     orig.y = centroid.y;
    //     orig.z = centroid.z - height/2 + v * height/(B/precision);
    //     break;
    // }

    return orig;
}

glm::vec3 Malla3D::get_dir(Axis axis, float v, float angle){
    glm::vec3 dir;
    switch (axis)
    {
    case X:
        dir.x = 0.0;
        dir.y = -1 * radius * cos(angle);
        dir.z = -1 * radius * sin(angle);
        break;

    case Y:
        dir.x = -1 * radius * cos(angle);
        dir.y = 0.0;
        dir.z = -1 * radius * sin(angle);
        break;

    case Z:
        dir.x = -1 * radius * cos(angle);
        dir.y = -1 * radius * sin(angle);
        dir.z = 0.0;
        break;
    }

    // switch (axis)
    // {
    // case X:
    //     dir.x = 0.0;
    //     dir.y = radius * cos(angle);
    //     dir.z = radius * sin(angle);
    //     break;

    // case Y:
    //     dir.x = radius * cos(angle);
    //     dir.y = 0.0;
    //     dir.z = radius * sin(angle);
    //     break;

    // case Z:
    //     dir.x = radius * cos(angle);
    //     dir.y = radius * sin(angle);
    //     dir.z = 0.0;
    //     break;
    // }

    return glm::normalize(dir);
}

glm::vec2 Malla3D::get_start_end(bool start, float angle, float threshold){
    float div = 5 * (M_PI/180.0);
    float max_angle = 360 * (M_PI/180.0);

    float true_angle = 0;
    while(true_angle+(div/2) < angle){
        true_angle += div;
    }

    glm::vec2 point;

    if(start){
        if((true_angle - threshold*div) < 0){
            true_angle = max_angle + (true_angle - threshold*div);
        } else {
            true_angle = true_angle - threshold*div;
        }
    } else{
        true_angle = fmod((true_angle + threshold*div),max_angle);
    }

    point.x = radius * cos(true_angle);
    point.y = radius * sin(true_angle);

    // std::cout << "Angle: " << angle << std::endl;
    // if(start){
    //     std::cout << "Start Angle: ";
    // } else {
    //     std::cout << "End Angle: ";
    // }
    // std::cout << true_angle << std::endl;

    return point;
}

bool Malla3D::inside_sector(Axis axis, glm::vec2 p, float angle, float threshold){
    bool clockwise_start, clockwise_end, within_radius;
    glm::vec2 centroid_2d;
    switch (axis)
    {
    case X:
        centroid_2d.x = centroid.y;
        centroid_2d.y = centroid.z;
        break;
    case Y:
        centroid_2d.x = centroid.x;
        centroid_2d.y = centroid.z;
        break;
    case Z:
        centroid_2d.x = centroid.x;
        centroid_2d.y = centroid.y;
        break;
    }

    glm::vec2 p_rel = p - centroid_2d;

    glm::vec2 start = get_start_end(true, angle, threshold);
    glm::vec2 end = get_start_end(false, angle, threshold);

    clockwise_start = (-p_rel.x*start.y + p_rel.y*start.x > 0);
    clockwise_end = (-p_rel.x*end.y + p_rel.y*end.x > 0);
    within_radius = (p_rel.x*p_rel.x + p_rel.y*p_rel.y <= radius*radius);

    // std::cout << "Angulo: " << angle << std::endl;

    return clockwise_start && !clockwise_end && within_radius;
}

// void Malla3D::filter_faces_height(Axis axis, float v, float threshold){
//     float v_height = height/B;
//     float coord_axis;
//     bool salir = false;

//     std::vector<std::vector<int>> facesIndex_filter_temp;

//     for(int i = 0; i < facesIndex.size(); i++){
//         salir = false;
//         for(int j = 0; j < facesIndex[i].size() && !salir; j++){
//             switch (axis)
//             {
//             case X:
//                 coord_axis = vertexs[facesIndex[i][j]].x;
//                 break;

//             case Y:
//                 coord_axis = vertexs[facesIndex[i][j]].y;
//                 break;

//             case Z:
//                 coord_axis = vertexs[facesIndex[i][j]].z;
//                 break;  
//             }
            
//             if((coord_axis >= (v - threshold*v_height)) &&
//                (coord_axis <= (v + threshold*v_height))){
//                 facesIndex_filter_temp.push_back(facesIndex[i]);
//                 salir = true;
//             }

//             // std::cout << "Coord: " << coord_axis << std::endl;
//             // std::cout << "V min: " << v - threshold*v_height << std::endl;
//             // std::cout << "V max: " << v + threshold*v_height << std::endl;
//         }
//     }

//     //return facesIndex_filter_temp;
// }

// void Malla3D::filter_faces_angle(Axis axis, float angle, float threshold){
//     //float angle;
//     bool salir = false;
//     glm::vec2 point_sector;
    
//     std::vector<std::vector<int>> facesIndex_filter_temp;

//     for(int i = 0; i < facesIndex_filter_height.size(); i++){
//         salir = false;
//         for(int j = 0; j < facesIndex_filter_height[i].size() && !salir; j++){
//             switch (axis)
//             {
//             case X:
//                 point_sector.x = vertexs[facesIndex_filter_height[i][j]].y;
//                 point_sector.y = vertexs[facesIndex_filter_height[i][j]].z;
//                 break;

//             case Y:
//                 point_sector.x = vertexs[facesIndex_filter_height[i][j]].x;
//                 point_sector.y = vertexs[facesIndex_filter_height[i][j]].z;
//                 break;

//             case Z:
//                 point_sector.x = vertexs[facesIndex_filter_height[i][j]].x;
//                 point_sector.y = vertexs[facesIndex_filter_height[i][j]].y;
//                 break;  
//             }

//             // angle = atan(point_sector.y/point_sector.x);
//             // if(angle < 0){
//             //     angle = 2*M_PI + angle;
//             // }

//             //std::cout << "Angle: " << angle << " , " << angle * (180.0/M_PI) << std::endl;
            
//             if(inside_sector(axis,point_sector,angle,threshold)){
//                 facesIndex_filter_temp.push_back(facesIndex_filter_height[i]);
//                 salir = true;
//             }
//         }
//     }

//     //return facesIndex_filter_temp;

// }

// std::vector<float> Malla3D::feature_map(Map map, Axis axis, 
//                                         std::vector<glm::vec3> origins, 
//                                         std::vector<glm::vec3> directions){
//     std::vector<float> row;

//     int n_colisiones = 0;

//     float v;

//     switch (axis)
//     {
//     case X:
//         v = origins[0].x;
//         break;
    
//     case Y:
//         v = origins[0].y;
//         break;

//     case Z:
//         v = origins[0].z;
//         break;
//     }

//     // std::cout << v << std::endl;
//     // std::cout << origins[i].x << ", " << origins[i].y << ", " << origins[i].z << std::endl;
//     facesIndex_filter.clear();
//     facesIndex_filter = facesIndex;
//     filter_faces_height(axis, v, 2);
//     // std::vector<std::vector<int>> facesIndex_filter = facesIndex;
//     std::cout << "Filtrado de caras (alt): " << facesIndex_filter.size() << std::endl;

//     switch (map)
//     {
//     case SDM:
    
//         for(int i = 0; i < origins.size(); i++){
//             filter_faces_angle(axis,0,1);
//             std::cout << i << " Filtrado de caras (ang): " << facesIndex_filter.size() << std::endl;

//             omp_set_num_threads(10);
//             #pragma omp parallel for
//             for(int j = 0; j < facesIndex_filter.size(); j++){
//                 glm::vec3 hit_point;
//                 glm::vec2 hit;
//                 float dist;
//                 std::vector<glm::vec3> triangle_points;
//                 for(int k = 0; k < facesIndex_filter[j].size(); k++){
//                     triangle_points.push_back(vertexs[facesIndex_filter[j][k]]);
//                 }
//                 if(RayIntersectsTriangle(origins[i], directions[i], triangle_points, hit_point)){
//                     n_colisiones++;
//                 // if(glm::intersectRayTriangle(origins[i], directions[i], triangle_points[0], triangle_points[1], triangle_points[2], hit, dist)){
//                     //std::cout << hit_point.x << ", " << hit_point.y << ", " << hit_point.z << std::endl;
//                     //std::cout << dist << std::endl;
//                 } else {
//                     //std::cout << i << ", " << j << std::endl;
//                 }
//             }
//             std::cout << "Colisiones: " << n_colisiones << std::endl;
//             n_colisiones = 0;
//         }
//         break;
    
//     case NDM:
//         /* code */
//         break;
//     }
// }

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

        std::vector<std::vector<int>> facesIndex_height_temp;
        std::vector<std::vector<std::vector<int>>> facesIndex_height;
        std::vector<std::vector<int>> facesIndex_ang_temp;

        facesIndex_filter_mesh.clear();

        for(float v = 0; v < (B/precision); v++){

            v_height = get_height(axis,v,precision);

            v_length = height/(B/precision);

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
                        facesIndex_height_temp.push_back(facesIndex[i]);
                        salir = true;
                    }

                }
            }
            
            if(facesIndex_height_temp.size() > 0){
                std::cout << v*precision << " " << v_height << " Filtrado de caras (alt): " << facesIndex_height_temp.size() << std::endl;
            }

            //for(float u = 0; u < 2*(B/precision); u++){

                // angle = u*2*M_PI / (2*(B/precision));
                
                // facesIndex_ang_temp.clear();

                // // omp_set_num_threads(10);
                // // #pragma omp parallel for private(facesIndex_ang_temp)

                // for(int i = 0; i < facesIndex_height_temp.size(); i++){
                //     salir = false;
                //     for(int j = 0; j < facesIndex_height_temp[i].size() && !salir; j++){
                //         switch (axis)
                //         {
                //         case X:
                //             point_sector.x = vertexs[facesIndex_height_temp[i][j]].y;
                //             point_sector.y = vertexs[facesIndex_height_temp[i][j]].z;
                //             break;

                //         case Y:
                //             point_sector.x = vertexs[facesIndex_height_temp[i][j]].x;
                //             point_sector.y = vertexs[facesIndex_height_temp[i][j]].z;
                //             break;

                //         case Z:
                //             point_sector.x = vertexs[facesIndex_height_temp[i][j]].x;
                //             point_sector.y = vertexs[facesIndex_height_temp[i][j]].y;
                //             break;  
                //         }
                        
                //         if(inside_sector(axis,point_sector,angle,threshold)){
                //             facesIndex_ang_temp.push_back(facesIndex_height_temp[i]);
                //             salir = true;
                //         }
                //     }
                // }
                
                //std::cout << u*precision << " " << angle << " Filtrado de caras (ang): " << facesIndex_ang_temp.size() << std::endl;

                // facesIndex_height.push_back(facesIndex_height_temp);
            //}

            facesIndex_filter_mesh.push_back(facesIndex_height_temp);
            facesIndex_height.clear();
        }
    }

void Malla3D::calculatePanorama(Map map, Axis axis, float precision, int power){
    std::vector<std::vector<float>> panorama;

    glm::vec3 direction;
    glm::vec3 origin;

    float v_height;

    int n_colisiones = 0;
    int n_colisiones_total = 0;

    std::vector<glm::vec3> colisiones;

    std::vector<std::vector<int>> facesIndex_height_filter;

    std::vector<std::vector<int>> facesIndex_control;

    std::set<int> colision_face;

    std::ofstream file, control, origfile;

    float dist_max;
    int ind_max;

    switch (axis)
    {
    case X:
        file.open("models/logX.obj");
        break;
    
    case Y:
        file.open("models/logY.obj");
        break;
    
    case Z:
        file.open("models/logZ.obj");
        break;
    }

    origfile.open("models/control/origin.obj");


    filter_faces(axis, precision);

    for(float i = 0; i < (B/precision); i++){
        std::vector<float> row(2*(B/precision), 0.0);
        panorama.push_back(row);
    }


    for(float v = 0; v < (B/precision); v++){

        // std::vector<float> row(2*(B/precision), 0);

        // panorama.push_back(row);

        //v_height = get_height(axis,v);

        //filter_faces_height(axis, v_height, 1);
        
        // facesIndex = facesIndex_filter_mesh[v];

        // export_obj("models/filter/" + std::to_string((int)v) + ".obj");

        // control.open("models/control/control_" + std::to_string((int)v) + ".obj");

        for(float u = 0; u < 2*(B/precision); u++){
            float angle = u*2*M_PI / (2*(B/precision));

            origin = get_orig(axis,v,angle,precision);
            direction = get_dir(axis,v,angle);
            // filter_faces_angle(axis,angle,1);
            

            // omp_set_num_threads(10);
            // #pragma omp parallel for

            //std::cout << v << " " << u << " " << facesIndex_filter_mesh[v].size() << std::endl;

            for(int j = 0; j < facesIndex_filter_mesh[v].size(); j++){
            //for(int j = 0; j < facesIndex.size(); j++){
                glm::vec3 hit_point;
                glm::vec2 hit;
                float dist;
                std::vector<glm::vec3> triangle_points;
                // std::cout << "Face ";
                //for(int k = 0; k < facesIndex[j].size(); k++){
                for(int k = 0; k < facesIndex_filter_mesh[v][j].size(); k++){
                    triangle_points.push_back(vertexs[facesIndex_filter_mesh[v][j][k]]);
                    // triangle_points.push_back(vertexs[facesIndex[j][k]]);
                    // std::cout << facesIndex_filter_mesh[v][u][j][k] << " ";
                }
                // for(int k = facesIndex_filter_mesh[v][j].size() - 1; k > 0; k--){
                //     triangle_points.push_back(vertexs[facesIndex_filter_mesh[v][j][k]]);
                // }
                // std::cout << "Face: " << facesIndex_filter[j][0] << " "
                // << facesIndex_filter[j][1] << " " << facesIndex_filter[j][2] 
                // << " " << std::endl;
                // std::cout << std::endl;
                if(RayIntersectsTriangle(origin, direction, triangle_points, hit_point)){
                //if(glm::intersectRayTriangle(origin, direction, triangle_points[0], triangle_points[1], triangle_points[2], hit, dist)){
                    n_colisiones++;
                    n_colisiones_total++;
                    colisiones.push_back(hit_point);
                
                    //std::cout << hit_point.x << ", " << hit_point.y << ", " << hit_point.z << std::endl;
                    //std::cout << dist << std::endl;
                } 
            }
            // std::cout << "Origin: " << origin.x << ", " << origin.y << ", " << origin.z << std::endl;
            // control << "v " << origin.x << " " << origin.y << " " << origin.z << std::endl;
            // for(float t = 0.0; t <= 2.0; t += 0.001){
            //     glm::vec3 aux = origin + direction * t;
            //     control << "v " << aux.x << " " << aux.y << " " << aux.z << std::endl;
            // }
            // float t = 2.0;
            // glm::vec3 aux = origin + direction * t;
            // origfile << "v " << aux.x << " " << aux.y << " " << aux.z << std::endl;
            // std::cout << "Direction: " << direction.x << ", " << direction.y << ", " << direction.z << std::endl;
            // std::cout << "Colisiones: " << v << " " << u << " " << n_colisiones << std::endl;
            std::cout << "Colisiones: " << v*precision << " " << u*precision << " " << n_colisiones << std::endl;
            dist_max = -1;
            ind_max = -1;
            if(n_colisiones > 0){
                for(int c = 0; c < colisiones.size(); c++){ 
                    float dist = glm::distance(colisiones[c],origin); 
                    dist = (radius - dist) / radius;
                    if((dist > dist_max) && (dist > 0)){
                        ind_max = c;
                        dist_max = dist;
                    }
                    // std::cout << dist << " " << radius << std::endl;
                }
                if((dist_max > 0) && (ind_max != -1)){
                    file << "v " << colisiones[ind_max].x << " " << colisiones[ind_max].y << " " << colisiones[ind_max].z << std::endl;
                    panorama[v][u] = dist_max;
                }
                // if(glm::distance(colisiones[0],origin) > radius){
                //     file << "v " << colisiones[0].x << " " << colisiones[0].y << " " << colisiones[0].z << std::endl;
                //     panorama[v][u] = glm::distance(colisiones[0],origin);
                //     facesIndex_control.push_back(facesIndex[point_face(colisiones[0])]);
                // }
            }
            // for(int c = 0; c < colisiones.size(); c++){
                // file << "v " << colisiones[c].x << " " << colisiones[c].y << " " << colisiones[c].z << std::endl;
                // std::cout << c << " (" << colisiones[c].x << " " << colisiones[c].y << " " << colisiones[c].z << ") " 
                // << glm::distance(colisiones[c],origin) << " " << point_face(colisiones[c]) << " [" 
                // << facesIndex[point_face(colisiones[c])][0]+1 << " " << facesIndex[point_face(colisiones[c])][1]+1 << " " 
                // << facesIndex[point_face(colisiones[c])][2]+1 << "] " << std::endl;
            // }
            
            for(auto it = colision_face.begin(); it != colision_face.end(); ++it){
                // std::cout << *it << std::endl;
            }
            n_colisiones = 0;
            colisiones.clear();
            colision_face.clear();
        }

        //std::vector<float> row = feature_map(map, axis, origins, directions);
        // control.close();
    }

    for(float i = 0; i < (B/precision); i++){
        //std::cout << i << std::endl;
        for(float j = 0; j < 2*(B/precision); j++){
            panorama[i][j] = (panorama[i][j] * 255);
            assert(panorama[i][j] <= 255.0 && panorama[i][j] >= 0.0);
        }

        // std::cout << std::endl;
        // float * p = panorama[i].data();
        // for(float j = 0; j < 2*(B/precision); j++){
        //     std::cout << *p << " ";
        //     ++p;
        // }
    }

    std::cout << "Colisiones: " << n_colisiones_total << std::endl;
    //facesIndex = facesIndex_control;
    
    // cv::Mat panorama_cv(B/precision, 2*(B/precision), CV_16U, panorama.data());

    cv::Mat panorama_cv(0, panorama[0].size(), CV_32F);

    for(int i = 0; i < panorama.size(); i++){
        cv::Mat row(1, panorama[i].size(), CV_32F, panorama[i].data());
        panorama_cv.push_back(row);
    }

    //std::cout << panorama_cv << std::endl;

    // cv::Mat panorama_norm;

    // cv::normalize(panorama_cv, panorama_norm, 0.0, 255.0, cv::NORM_MINMAX, CV_32F);

    std::string sdm_name;
    switch (axis)
    {
    case X:
        sdm_name = "png/SDMX.png";
        break;
    case Y:
        sdm_name = "png/SDMY.png";
        break;
    case Z:
        sdm_name = "png/SDMZ.png";
        break;
    }

    cv::imwrite(sdm_name, panorama_cv);

    // cv::Mat I = cv::imread("png/SDM.png", 0);

    // cv::namedWindow( "Display window", CV_WINDOW_NORMAL );// Create a window for display.
    // cv::imshow( "Display window", I ); 
    // cv::waitKey(0);

    // cv::imwrite("png/SDM_norm.png", panorama_norm);
}

