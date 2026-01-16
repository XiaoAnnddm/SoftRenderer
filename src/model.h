#pragma once

#include <string>
#include <vector>

#include <glm/vec3.hpp>

class Model {
private:
  std::vector<glm::vec3> verts = {};
  std::vector<int> faces_vrt = {};

public:
  Model(const std::string &filename);

  int nverts() const;
  int nfaces() const;

  glm::vec3 vert(const int i) const;
  glm::vec3 vert(const int iface, const int nthvert) const;
};
