#include "lambertian_material.glsl"

void SampleDirection(in Material mat, in vec3 normal, out vec3 v, out float pdf) {
  if (mat.material_type == MATERIAL_TYPE_LAMBERTIAN) {
    SampleDirectionLambertian(mat, normal, v, pdf);
  }
}

float EvalBRDF(in Material mat, in vec3 normal, in vec3 in_dir, in vec3 out_dir) {
  if (mat.material_type == MATERIAL_TYPE_LAMBERTIAN) {
    return INV_PI;
  } 
}