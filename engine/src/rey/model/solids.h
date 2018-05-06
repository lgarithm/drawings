#pragma once

#include <vector>

#include <rey/linear/linear.hpp>

struct face_index {
    std::vector<unsigned short> vi;
};

struct index_model {
    std::vector<point3> vertices;
    std::vector<face_index> faces;
};

index_model cube(scalar_t r, const point3 &o);
std::vector<point3> at(const index_model &idx_m, const face_index &fi);
oframe localize(std::vector<point3> &vs);
