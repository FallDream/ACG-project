#pragma once
#include "cstdint"
#include "glm/glm.hpp"
#include "sparks/assets/util.h"

namespace sparks {

enum MaterialType : int {
  MATERIAL_TYPE_LAMBERTIAN = 0,
  MATERIAL_TYPE_SPECULAR = 1,
  MATERIAL_TYPE_TRANSMISSIVE = 2,
  MATERIAL_TYPE_PRINCIPLED = 3,
  MATERIAL_TYPE_EMISSION = 4,
  MATERIAL_TYPE_MICROFACET_CONDUCTOR = 5,
  MATERIAL_TYPE_MICROFACET_DIELECTRIC = 6
};

class Scene;

struct Material {
  glm::vec3 albedo_color{0.8f};
  int albedo_texture_id{0};
  glm::vec3 emittance{0.0f};
  MaterialType material_type{MATERIAL_TYPE_LAMBERTIAN};
  float eta{0.0f};
  float k{1.0f};
  float alpha_u{0.1f};
  float alpha_v{0.1f};
  float interior_ior{1.5046f}; // for bk7
  float exterior_ior{1.000277f}; // for air
  float specular_reflectance{1.f};
  float specular_transmittance{1.f};
  Material() = default;
  explicit Material(const glm::vec3 &albedo);
  Material(Scene *scene, const tinyxml2::XMLElement *material_element);
};

}  // namespace sparks
