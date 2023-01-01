#ifndef MAT_H_
#define MAT_H_

struct Material {
  vec3 albedo_color;
  int albedo_texture_id;
  vec3 emittance; 
  uint material_type;
  float eta;
  float k;
  float alpha_u;
  float alpha_v;
  float interior_ior;
  float exterior_ior;
  float specular_reflectance;
  float specular_transmittance;
};

#define MATERIAL_TYPE_LAMBERTIAN 0
#define MATERIAL_TYPE_SPECULAR 1
#define MATERIAL_TYPE_TRANSMISSIVE 2
#define MATERIAL_TYPE_PRINCIPLED 3
#define MATERIAL_TYPE_EMISSION 4
#define MATERIAL_TYPE_MICROFACET_CONDUCTOR 5
#define MATERIAL_TYPE_MICROFACET_DIELECTRIC 6

#endif