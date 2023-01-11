#include "material.glsl"
#include "microfacet.glsl"
#include "math.glsl"
#include "fresnel.glsl"

// For microfacet material, emittance[0] will be the roughness
void SampleDirectionMicrofacetConductor(Material mat, in vec3 normal, in vec3 in_dir, out vec3 v, out vec3 bsdf_by_pdf) {
  vec3 wi = -in_dir;

  // Step0: project into local frame
  vec3 local_x, local_y;
  local_coordinate(normal, local_x, local_y);
  vec3 local_wi = vec3(dot(wi, local_x), dot(wi, local_y), dot(wi, normal));

  float cos_theta_i = local_wi.z;
  float pdf;
  // sample half-vector
  vec3 local_m;
  SampleMicrofacetDistirbution(mat, local_wi, local_m, pdf);
  // perfect specular based on half vector m
  vec3 local_wo = 2 * dot(local_m, local_wi) * local_m - local_wi; 
  // Not valid
  if (local_wo.z < 0.f || pdf == 0.f) {
    pdf = 0.f;
  }
  vec2 eta_c = vec2(mat.eta, mat.k);
  vec3 weight = vec3(smith_g1(mat, local_wo, local_m));
  // Jacobian of half-direction mapping
  pdf /= 4.f * dot(local_wo, local_m);
  // Fresnel Factor
  float F = fresnel_conductor(dot(local_wi, local_m), eta_c);

  weight *= mat.specular_reflectance;
  
  bsdf_by_pdf = F * weight;
  // Project back to local coordinate system
  v = local_x * local_wo.x + local_y * local_wo.y + normal * local_wo.z;
}

vec3 MicrofacetConductorEvalBRDF(in Material mat, in vec3 normal, in vec3 in_dir, in vec3 wo) {
  vec3 wi = -in_dir;

  // Step0: project into local frame
  vec3 local_x, local_y;
  local_coordinate(normal, local_x, local_y);
  vec3 local_wi = vec3(dot(wi, local_x), dot(wi, local_y), dot(wi, normal));  
  vec3 local_wo = vec3(dot(wo, local_x), dot(wo, local_y), dot(wo, normal));
  vec3 H = normalize(local_wi + local_wo);

  // NDF
  float D = microfacet_eval(mat, H);
  // Smith shadowing masking
  float G = smith_G(mat, local_wi, local_wo, H);
  float result = D * G / (4.f * local_wi.z);
  // Fresnel
  vec2 eta_c = vec2(mat.eta, mat.k);
  float F = fresnel_conductor(dot(local_wi, H), eta_c); 
  vec3 result1 = vec3(result) * mat.specular_reflectance;
  return F * result1;
}