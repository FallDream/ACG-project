#include "microfacet.glsl"
#include "material.glsl"
#include "fresnel.glsl"

void SampleDirectionMicrofacetDielectric(Material mat, in vec3 normal, in vec3 in_dir, out vec3 v, out float value) {
  float int_ior = mat.interior_ior;
  float ext_ior = mat.exterior_ior;
  float m_eta = int_ior / ext_ior;
  float m_inv_eta = ext_ior / int_ior;
  
  vec3 wi = -in_dir;

  // Step0: project into local frame
  vec3 local_x, local_y;
  local_coordinate(normal, local_x, local_y);
  vec3 local_wi = vec3(dot(wi, local_x), dot(wi, local_y), dot(wi, normal));

  float cos_theta_i = local_wi.z;

  // Scale alpha
  Material mat_scaled;
  float scale_factor = 1.2f - 0.2f * sqrt(abs(cos_theta_i));
  mat_scaled.alpha_u = mat.alpha_u * scale_factor;
  mat_scaled.alpha_v = mat.alpha_v * scale_factor;
  // Sample half vector
  vec3 local_m; float pdf;
  SampleMicrofacetDistirbution(mat_scaled, local_wi * sign(cos_theta_i), local_m, pdf);
  float cos_theta_t, eta_it, eta_ti;
  float F = fresnel(dot(local_wi, local_m), m_eta, cos_theta_t, eta_it, eta_ti);
  // Select the lobe to be sampled
  float rn1 = RandomFloat(), weight = 1.0f, eta;
  bool selected_r = false, selected_t = false;
  if (rn1 <= F) {
    selected_r = true;
    pdf *= F;
    eta = 1.f;
  } else {
    selected_t = true;
    pdf *= 1.0 - F;
    eta = eta_it;
  }
  float dwh_dwo = 0.f;
  vec3 local_wo;
  // Reflection sampling
  if (selected_r) {
    local_wo = 2 * dot(local_m, local_wi) * local_m - local_wi;
    weight *= mat.specular_reflectance;
    // Jacobian
    dwh_dwo = rcp(4.f * dot(local_wo, local_m));
  }
  // Transmission sampling
  if (selected_t) {
    local_wo = refract(local_wi, local_m, cos_theta_t, eta_ti);
    // Solid angle compression
    float factor = sqr(eta_ti);
    factor *= mat.specular_transmittance;
    weight *= factor;
    dwh_dwo = (sqr(eta) * dot(local_wo, local_m)) /
               sqr(dot(local_wi, local_m) + eta * dot(local_wo, local_m));
  }
  weight *= smith_g1(mat, local_wo, local_m);
  pdf *= abs(dwh_dwo);

  value = weight;
  v = local_x * local_wo.x + local_y * local_wo.y + normal * local_wo.z;
}

float MicrofacetDielectricEvalBRDF(in Material mat, in vec3 normal, in vec3 in_dir, in vec3 wo) {
  vec3 wi = -in_dir;

  vec3 local_x, local_y;
  local_coordinate(normal, local_x, local_y);
  vec3 local_wi = vec3(dot(wi, local_x), dot(wi, local_y), dot(wi, normal));
  vec3 local_wo = vec3(dot(wo, local_x), dot(wo, local_y), dot(wo, normal));

  float cos_theta_i = local_wi.z;
  float cos_theta_o = local_wo.z;

  float int_ior = mat.interior_ior;
  float ext_ior = mat.exterior_ior;
  float m_eta = int_ior / ext_ior;
  float m_inv_eta = ext_ior / int_ior;

  bool reflect = (cos_theta_i * cos_theta_o > 0.f);
  // Determine the relative index of refraction
  float eta, inv_eta;
  if (cos_theta_i > 0.f) {
    eta = m_eta;
    inv_eta = m_inv_eta;
  } else {
    inv_eta = m_eta;
    eta = m_inv_eta;
  }
  // Compute the half-vector
  float scale_wo = 1.0f;
  if (!reflect) {
    scale_wo = eta;
  }
  vec3 local_m = normalize(local_wi + local_wo * scale_wo);
  // Ensure that the half-vector points into the same hemisphere as the macrosurface normal
  if (local_m.z < 0) {
    local_m = -local_m;
  }
  float D = microfacet_eval(mat, local_m);
  float cos_theta_t, eta_it, eta_ti;
  float F = fresnel(dot(local_wi, local_m), m_eta, cos_theta_t, eta_it, eta_ti);
  float G = smith_G(mat, local_wi, local_wo, local_m);

  float value;
  if (reflect) {
    value = F * D * G / (4.f * abs(cos_theta_i));
    value *= mat.specular_reflectance;
  } else {
    float scale = sqr(inv_eta);
    value = abs((scale * (1.f - F) * D * G * eta * eta * dot(local_wi, local_m) * dot(local_wo, local_m)) /
                (cos_theta_i * sqr(dot(local_wi, local_m) + eta * dot(local_wo, local_m))));
    value *= mat.specular_transmittance;
  }
  return value;
}