#ifndef WARP_H_
#define WARP_H_

#include "constants.glsl"
#include "math.glsl"

void square_to_uniform_disk_concentric(vec2 sampled, out vec2 v) {
  float r = safe_sqrt(sampled.y);
  float x = sampled.x * 2 * PI;
  float s = sin(x);
  float c = cos(x);
  v = vec2(c * r, s * r);
}

void square_to_cosine_hemisphere(in vec2 sampled, out vec3 v) {
  // sample projected solid angle
  vec2 p;
  square_to_uniform_disk_concentric(sampled, p);
  float z = safe_sqrt(1.f - dot(p, p));
  v = vec3(p.x, p.y, z);
}

float square_to_cosine_hemisphere_pdf(in vec3 v) {
  return v.z * INV_PI;
}

#endif