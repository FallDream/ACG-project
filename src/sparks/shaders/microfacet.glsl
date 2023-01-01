#ifndef MICROFACET_H_
#define MICROFACET_H_

#include "random.glsl"
#include "math.glsl"
#include "warp.glsl"

// struct MicrofacetDistribution{
//   float alpha_u;
//   float alpha_v;
// };

float smith_g1(Material mat, in vec3 v, in vec3 m) {
  float xy_alpha_2 = sqr(mat.alpha_u * v.x) + sqr(mat.alpha_v * v.y);
  float tan_theta_alpha_2 = xy_alpha_2 / sqr(v.z);

  float result = 2.f/ (1.f + sqrt(1.f + tan_theta_alpha_2));
  // perpendicular - no shadowing / masking
  if (xy_alpha_2 == 0) {
    result = 1.f;
  }
  // Ensure consistent orientation
  if (dot(v, m) * v.z <= 0.f) {
    result = 0.f;
  }
  return result;
}

float smith_G(Material mat, in vec3 wi, in vec3 wo, in vec3 m) {
  return smith_g1(mat, wi, m) * smith_g1(mat, wo, m);
}

// m is in local coordinate system
float microfacet_eval(Material mat, in vec3 m) {
  float alpha_uv = mat.alpha_u * mat.alpha_v;
  float cos_theta = m.z;
  float cos_theta_2 = cos_theta * cos_theta;
  
  float result = rcp(PI * alpha_uv * 
                     sqr(sqr(m.x / mat.alpha_u) + sqr(m.y / mat.alpha_v) + sqr(m.z)));

  if (result * cos_theta > 1e-20) {
    return result;
  } else {
    return 0.f;
  }
}

void SampleMicrofacetDistirbution(in Material mat, in vec3 wi, out vec3 m, out float pdf) {
  // sample a half-vector
  
  // Step1: stretch in coming direction
  vec3 wi_p = normalize(vec3(mat.alpha_u * wi.x, mat.alpha_v * wi.y, wi.z));
  float sin_theta_p = safe_sqrt(wi_p.x * wi_p.x + wi_p.y * wi_p.y);
  float cos_theta_p = wi_p.z;
  float sin_phi_p, cos_phi_p;
  sincos_phi(wi_p, sin_phi_p, cos_phi_p);
  // Step2: sample for alpha=1 case
  // Use GGX here
  vec2 rn = RandomPair();
  vec2 p;
  square_to_uniform_disk_concentric(rn, p);
  float s = 0.5f * (1.f + cos_theta_p);
  p.y = (1 - s) * safe_sqrt(1.f - p.x * p.x) + s * p.y;
  // Project onto chosen hemisphere
  float x = p.x, y = p.y, z = safe_sqrt(1.f - dot(p, p));
  float norm = 1.0 / (sin_theta_p * y + cos_theta_p * z);
  vec2 slope = vec2(cos_theta_p * y - sin_theta_p * z, x) * norm;
  // Step3: Rotate and Unstretch
  slope = vec2((cos_phi_p * slope.x - sin_phi_p * slope.y) * mat.alpha_u,
               (sin_phi_p * slope.x + cos_phi_p * slope.y) * mat.alpha_v);
  // Step4: Compute normal and pdf
  m = normalize(vec3(-slope.x, -slope.y, 1));
  pdf = microfacet_eval(mat, m) * smith_g1(mat, wi, m) * abs(dot(wi, m)) / wi.z;
}










#endif