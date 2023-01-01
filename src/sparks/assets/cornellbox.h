#include "sparks/assets/scene.h"
#include "sparks/assets/material.h"

#include <iostream>

namespace sparks {
void Scene::CreateCornellBox() {
  AddTexture(Texture(1, 1, glm::vec4{1.0f}, SAMPLE_TYPE_LINEAR), "Pure White");
  AddTexture(Texture(1, 1, glm::vec4{0.0f}, SAMPLE_TYPE_LINEAR), "Pure Black");
  // Texture envmap;
  // Texture::Load(u8"../../textures/envmap_clouds_4k.hdr", envmap);
  // envmap.SetSampleType(SAMPLE_TYPE_LINEAR);
  // envmap_id_ = AddTexture(envmap, "Clouds");

  // Adapted from Cornell Box on RenderingResources
  Material leftwall_brdf{glm::vec3{0.63f, 0.065f, 0.05f}, 0, glm::vec3{0.f}, MATERIAL_TYPE_LAMBERTIAN};
  Material rightwall_brdf{glm::vec3{0.14f, 0.45f, 0.091f}, 0, glm::vec3{0.f}, MATERIAL_TYPE_LAMBERTIAN};
  Material other_brdf{glm::vec3{0.725f, 0.71f, 0.68f}, 0, glm::vec3{0.f}, MATERIAL_TYPE_LAMBERTIAN};
  Material light_brdf{glm::vec3{0.0f}, 0, glm::vec3{17.f, 12.f, 4.f}, MATERIAL_TYPE_EMISSION};
  Material specular{glm::vec3{0.725f, 0.71f, 0.68f}, 0, glm::vec3{0.f}, MATERIAL_TYPE_SPECULAR};
  Material mf_conductor{glm::vec3{0.725f, 0.71f, 0.68f}, 0, glm::vec3{0.f}, 
                        MATERIAL_TYPE_MICROFACET_CONDUCTOR, 0.46094, 2.97035};

  // Mitsuba are row major while glm are column-major, do a transpose for matracis
  // Camera orientation in sparks and Mitsuba are different, flip [2][2]
  SetCameraToWorld(glm::transpose(glm::mat4{-1., 0., 0., 0., 0., 1., 0., 1., 0., 0., 1., 6.8, 0., 0., 0., 1.}));
  float cur_fov = GetCamera().getfov();
  GetCamera().UpdateFov(19.5 - cur_fov);

  AddRectangle(leftwall_brdf, glm::transpose(glm::mat4{-4.37114e-008, 8.74228e-008, -2, -1, 1, 3.82137e-015, -8.74228e-008, 1, 0, -1, -4.37114e-008, 0, 0, 0, 0, 1}));
  AddRectangle(rightwall_brdf, glm::transpose(glm::mat4{4.37114e-008, -1.74846e-007, 2, 1, 1, 3.82137e-015, -8.74228e-008, 1, 3.82137e-015, 1, 2.18557e-007, 0, 0, 0, 0, 1}));
  
  // Floor
  AddRectangle(other_brdf, glm::transpose(glm::mat4{-4.37114e-008, 1, 4.37114e-008, 0, 0, -8.74228e-008, 2, 0, 1, 4.37114e-008, 1.91069e-015, 0, 0, 0, 0, 1}));
  // Ceiling
  AddRectangle(other_brdf, glm::transpose(glm::mat4{-1, 7.64274e-015, -1.74846e-007, 0, 8.74228e-008, 8.74228e-008, -2, 2, 0, -1, -4.37114e-008, 0, 0, 0, 0, 1}));
  // BackWall
  AddRectangle(other_brdf, glm::transpose(glm::mat4{1.91069e-015, 1, 1.31134e-007, 0, 1, 3.82137e-015, -8.74228e-008, 1, -4.37114e-008, 1.31134e-007, -2, -1, 0, 0, 0, 1}));
  // ShortBox
  AddCube(other_brdf, glm::transpose(glm::mat4{0.0851643, 0.289542, 1.31134e-008, 0.328631, 3.72265e-009, 1.26563e-008, -0.3, 0.3, -0.284951, 0.0865363, 5.73206e-016, 0.374592, 0, 0, 0, 1}));
  // TallBox
  AddCube(mf_conductor, glm::transpose(glm::mat4{0.286776, 0.098229, -2.29282e-015, -0.335439, -4.36233e-009, 1.23382e-008, -0.6, 0.6, -0.0997984, 0.282266, 2.62268e-008, -0.291415, 0, 0, 0, 1}));
  // Light
  AddRectangle(light_brdf, glm::transpose(glm::mat4{0.235, -1.66103e-008, -7.80685e-009, -0.005, -2.05444e-008, 3.90343e-009, -0.0893, 1.98, 2.05444e-008, 0.19, 8.30516e-009, -0.03, 0, 0, 0, 1}));
}




} // end namespace sparks