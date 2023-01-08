#ifndef LIGHT_H__
#define LIGHT_H__
#include "cmath"
namespace sparks {
struct Light {
  uint32_t index;
  float area;
};

inline float GetLightArea(const std::vector<Vertex> &vertices, const glm::mat4 &to_world) {
  // two offset vectors
  glm::vec4 a(vertices[1].position - vertices[0].position, 0.f);
  glm::vec4 b(vertices[2].position - vertices[0].position, 0.f);
  a = to_world * a;
  b = to_world * b;
  return glm::length(glm::cross(glm::vec3(a), glm::vec3(b)));
}

}  // namespace sparks
#endif
