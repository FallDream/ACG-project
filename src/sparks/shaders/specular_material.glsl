#include "material.glsl"

void SampleDirectionSpecular(Material mat, in vec3 normal, in vec3 in_dir, out vec3 v, out vec3 value) {
  v = 2 * dot(-in_dir, normal) * normal + in_dir;
  value = vec3(1.0); // brdf=1.0, pdf=1.0
}