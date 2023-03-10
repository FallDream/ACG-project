#include "sparks/assets/material.h"

#include "grassland/grassland.h"
#include "sparks/assets/scene.h"
#include "sparks/assets/texture.h"
#include "sparks/util/util.h"

namespace sparks {

namespace {
std::unordered_map<std::string, MaterialType> material_name_map{
    {"lambertian", MATERIAL_TYPE_LAMBERTIAN},
    {"specular", MATERIAL_TYPE_SPECULAR},
    {"transmissive", MATERIAL_TYPE_TRANSMISSIVE},
    {"principled", MATERIAL_TYPE_PRINCIPLED},
    {"emission", MATERIAL_TYPE_EMISSION},
    {"microfacet_conductor", MATERIAL_TYPE_MICROFACET_CONDUCTOR},
    {"microfacet_dielectric", MATERIAL_TYPE_MICROFACET_DIELECTRIC}};
}

Material NewMaterial(Scene *scene, const tinyxml2::XMLElement *material_element)
{
  Material mat{};
  if (!material_element) {
    return mat;
  }

  mat.albedo_color = glm::vec3{1.0f};

  auto child_element = material_element->FirstChildElement("albedo");
  if (child_element) {
    mat.albedo_color = StringToVec3(child_element->FindAttribute("value")->Value());
  }

  child_element = material_element->FirstChildElement("albedo_texture");
  if (child_element) {
    std::string path = child_element->FindAttribute("value")->Value();
    Texture albedo_texture(1, 1);
    if (Texture::Load(path, albedo_texture)) {
      mat.albedo_texture_id =
          scene->AddTexture(albedo_texture, PathToFilename(path));
    }
  }

  child_element = material_element->FirstChildElement("emission");
  if (child_element) {
    mat.emittance = StringToVec3(child_element->FindAttribute("value")->Value());
  }

  child_element = material_element->FirstChildElement("emission_strength");
  if (child_element) {
    // emission_strength =
    //     std::stof(child_element->FindAttribute("value")->Value());
    mat.emittance *= std::stof(child_element->FindAttribute("value")->Value());
  }

  // child_element = material_element->FirstChildElement("alpha");
  // if (child_element) {
  //   alpha = std::stof(child_element->FindAttribute("value")->Value());
  // }

  mat.material_type =
      material_name_map[material_element->FindAttribute("type")->Value()];
  return mat;
}

}  // namespace sparks
