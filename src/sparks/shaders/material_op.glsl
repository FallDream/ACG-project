#include "lambertian_material.glsl"
#include "specular_material.glsl"
#include "microfacet_conductor.glsl"
#include "microfacet_dielectric.glsl"

// value: bsdf / pdf * cosine (fore-shortening term)
void SampleDirection(in Material mat, in vec3 normal, in vec3 in_dir, out vec3 v, out vec3 value) {
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
vec3 EvalBRDF(in Material mat, in vec3 normal, in vec3 in_dir, in vec3 out_dir) {
  if (mat.material_type == MATERIAL_TYPE_LAMBERTIAN) {
    return vec3(max(0.f, dot(out_dir, normal)) * INV_PI);
  } else if (mat.material_type == MATERIAL_TYPE_SPECULAR) {
    return vec3(1.0); // no fresnel, reflect all radiance?
  } else if (mat.material_type == MATERIAL_TYPE_MICROFACET_CONDUCTOR) {
    return MicrofacetConductorEvalBRDF(mat, normal, in_dir, out_dir);
  } else if (mat.material_type == MATERIAL_TYPE_MICROFACET_DIELECTRIC) {
    return MicrofacetDielectricEvalBRDF(mat, normal, in_dir, out_dir);
  } else {
    return vec3(0.f);
  }
}