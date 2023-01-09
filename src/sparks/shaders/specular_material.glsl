#include "material.glsl"

void SampleDirectionSpecular(Material mat, in vec3 normal, in vec3 in_dir, out vec3 v, out float value) {
  v = 2 * dot(in_dir, normal) * normal - in_dir;
  value = 1.0; // brdf=1.0, pdf=1.0
}