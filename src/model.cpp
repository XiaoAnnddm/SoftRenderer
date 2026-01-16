#include "model.h"
#include <fstream>
#include <iostream>
#include <sstream>

Model::Model(const std::string &filename) {
  std::ifstream in;
  in.open(filename, std::ifstream::in);
  if (in.fail()) {
    std::cerr << "FAIL: MODEL_OPEN_FILENAME" << '\n';
    return;
  }

  std::string line;
  while (!in.eof()) {
    std::getline(in, line);
    std::istringstream iss(line.c_str());
    char trash;
    if (!line.compare(0, 2, "v ")) {
      iss >> trash;
      glm::vec3 v;
      for (int i : {0, 1, 2}) {
        iss >> v[i];
      }
      verts.push_back(v);
    } else if (!line.compare(0, 3, "vn ")) {
    } else if (!line.compare(0, 2, "f ")) {
      int f, t, n, cnt = 0;
      iss >> trash;
      while (iss >> f >> trash >> t >> trash >> n) {
        faces_vrt.push_back(--f);
        cnt++;
      }
      if (cnt != 3) {
        std::cerr << "Error: the obj file is supposed to be triangulated\n";
        return;
      }
    }
  }
  std::cout << "# v# " << nverts() << " f# " << nfaces() << '\n';
}

int Model::nverts() const { return verts.size(); }
int Model::nfaces() const { return faces_vrt.size() / 3; }

glm::vec3 Model::vert(const int i) const { return verts[i]; }

glm::vec3 Model::vert(const int iface, const int nthvert) const {
  return verts[faces_vrt[iface * 3 + nthvert]];
}
