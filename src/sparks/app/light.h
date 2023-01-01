#ifndef LIGHT_H__
#define LIGHT_H__
#include "cmath"
namespace sparks {
struct Light {
  uint32_t index;
  float area;
};

inline float GetLightArea(const glm::mat4 &to_world) {
  // two offset vectors
  glm::vec4 a(0.0f, 2.0f, 0.0f, 0.0f);
  glm::vec4 b(2.0f, 0.0f, 0.0f, 0.0f);
  a = to_world * a;
  b = to_world * b;
  float cos = dot(a, b);
  return length(a) * length(b) * std::sqrt(1.0 - cos * cos);
}

}  // namespace sparks
#endif
