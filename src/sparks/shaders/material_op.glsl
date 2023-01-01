#include "lambertian_material.glsl"
#include "specular_material.glsl"
#include "microfacet_material.glsl"

void SampleDirection(in Material mat, in vec3 normal, in vec3 in_dir, out vec3 v, out float pdf) {
  if (mat.material_type == MATERIAL_TYPE_LAMBERTIAN) {
    SampleDirectionLambertian(mat, normal, v, pdf);
  } else if (mat.material_type == MATERIAL_TYPE_SPECULAR) {
    SampleDirectionSpecular(mat, normal, in_dir, v, pdf);
  } else if (mat.material_type == MATERIAL_TYPE_MICROFACET) {
    SampleDirectionMicrofacet(mat, normal, in_dir, v, pdf);
  } else {
    v = normal;
  }
}

float EvalBRDF(in Material mat, in vec3 normal, in vec3 in_dir, in vec3 out_dir) {
  if (mat.material_type == MATERIAL_TYPE_LAMBERTIAN) {
    return INV_PI;
  } else if (mat.material_type == MATERIAL_TYPE_SPECULAR) {
    return 1.f;
  } else if (mat.material_type == MATERIAL_TYPE_MICROFACET) {
    // TODO
  }
}