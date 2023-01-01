#include "material.glsl"

void SampleDirectionMicrofacet(Material mat, in vec3 normal, in vec3 in_dir, out vec3 v, out float pdf) {
  // TODO
  v = 2 * dot(in_dir, normal) * normal - in_dir;
  pdf = 1.f;
}