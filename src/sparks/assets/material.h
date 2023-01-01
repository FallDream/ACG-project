#pragma once
#include "cstdint"
#include "glm/glm.hpp"

namespace sparks {

enum MaterialType : int {
  MATERIAL_TYPE_LAMBERTIAN = 0,
  MATERIAL_TYPE_SPECULAR = 1,
  MATERIAL_TYPE_TRANSMISSIVE = 2,
  MATERIAL_TYPE_PRINCIPLED = 3,
  MATERIAL_TYPE_EMISSION = 4,
  MATERIAL_TYPE_MICROFACET = 5
};

struct Material {
  glm::vec3 albedo_color{0.8f};
  int albedo_texture_id{0};
  glm::vec3 emittance{0.0f};
  MaterialType material_type{MATERIAL_TYPE_LAMBERTIAN};
};
}  // namespace sparks
