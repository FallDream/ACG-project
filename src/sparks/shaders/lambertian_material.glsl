#include "material.glsl"
#include "random.glsl"
#include "warp.glsl"

void SampleDirectionLambertian(Material mat, in vec3 normal, out vec3 v, out float pdf) {
  vec2 rn = RandomPair();
  vec3 dir_local;
  square_to_cosine_hemisphere(rn, dir_local);
  pdf = square_to_cosine_hemisphere_pdf(dir_local);
  vec3 local_x, local_y;
  local_coordinate(normal, local_x, local_y);
  v = local_x * dir_local.x + local_y * dir_local.y + normal * dir_local.z;
}