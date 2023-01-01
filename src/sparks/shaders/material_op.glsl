#include "lambertian_material.glsl"
#include "specular_material.glsl"
#include "microfacet_conductor.glsl"
#include "microfacet_dielectric.glsl"

// value: bsdf / pdf * cosine (fore-shortening term)
void SampleDirection(in Material mat, in vec3 normal, in vec3 in_dir, out vec3 v, out float value) {
  if (mat.material_type == MATERIAL_TYPE_LAMBERTIAN) {
    SampleDirectionLambertian(mat, normal, in_dir, v, value);
  } else if (mat.material_type == MATERIAL_TYPE_SPECULAR) {
    SampleDirectionSpecular(mat, normal, in_dir, v, value);
  } else if (mat.material_type == MATERIAL_TYPE_MICROFACET_CONDUCTOR) {
    SampleDirectionMicrofacetConductor(mat, normal, in_dir, v, value);
  } else if (mat.material_type == MATERIAL_TYPE_MICROFACET_DIELECTRIC) {
    SampleDirectionMicrofacetDielectric(mat, normal, in_dir, v, value);
  } else {
    v = normal;
  }
}

// value: bsdf * cosine (fore_shortening term)
float EvalBRDF(in Material mat, in vec3 normal, in vec3 in_dir, in vec3 out_dir) {
  if (mat.material_type == MATERIAL_TYPE_LAMBERTIAN) {
    return max(0.f, dot(-in_dir, normal)) * INV_PI;
  } else if (mat.material_type == MATERIAL_TYPE_SPECULAR) {
    return max(0.f, dot(-in_dir, normal));
  } else if (mat.material_type == MATERIAL_TYPE_MICROFACET_CONDUCTOR) {
    return MicrofacetConductorEvalBRDF(mat, normal, in_dir, out_dir);
  } else if (mat.material_type == MATERIAL_TYPE_MICROFACET_DIELECTRIC) {
    return MicrofacetDielectricEvalBRDF(mat, normal, in_dir, out_dir);
  } else {
    return 0.f;
  }
}