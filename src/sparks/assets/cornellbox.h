#include "sparks/assets/scene.h"
#include "sparks/assets/material.h"
#include "sparks/assets/mesh.h"

#include <iostream>

namespace sparks {
void Scene::CreateCornellBox() {
  // Texture envmap;
  // Texture::Load(u8"../../textures/envmap_clouds_4k.hdr", envmap);
  // envmap.SetSampleType(SAMPLE_TYPE_LINEAR);
  // envmap_id_ = AddTexture(envmap, "Clouds");

  SetCameraToWorld(glm::mat4{1.0f});
  SetGlobalTransformForNew(glm::inverse(glm::transpose(glm::mat4{-1., 0., 0., 0., 0., 1., 0., 1., 0., 0., 1., 6.8, 0., 0., 0., 1.})));
  float cur_fov = GetCamera().getfov();
  GetCamera().UpdateFov(35 - cur_fov);

  // Adapted from Cornell Box on RenderingResources
  Material leftwall_brdf{glm::vec3{0.63f, 0.065f, 0.05f}, 0, glm::vec3{0.f}, MATERIAL_TYPE_LAMBERTIAN};
  Material rightwall_brdf{glm::vec3{0.14f, 0.45f, 0.091f}, 0, glm::vec3{0.f}, MATERIAL_TYPE_LAMBERTIAN};
  Material other_brdf{glm::vec3{0.725f, 0.71f, 0.68f}, 0, glm::vec3{0.f}, MATERIAL_TYPE_LAMBERTIAN};
  Material light_brdf{glm::vec3{0.0f}, 0, glm::vec3{17.f, 12.f, 4.f}, MATERIAL_TYPE_EMISSION};
  Material specular{glm::vec3{0.725f, 0.71f, 0.68f}, 0, glm::vec3{0.f}, MATERIAL_TYPE_SPECULAR};
  Material mf_conductor{glm::vec3{0.725f, 0.71f, 0.68f}, 0, glm::vec3{0.f}, 
                        MATERIAL_TYPE_MICROFACET_CONDUCTOR, 0.46094, 2.97035};

  // Mitsuba are row major while glm are column-major, do a transpose for matracis
  // Camera orientation in sparks and Mitsuba are different, flip [2][2]

  // AddRectangle(leftwall_brdf, glm::transpose(glm::mat4{-4.37114e-008, 8.74228e-008, -2, -1, 1, 3.82137e-015, -8.74228e-008, 1, 0, -1, -4.37114e-008, 0, 0, 0, 0, 1}));
  // AddRectangle(rightwall_brdf, glm::transpose(glm::mat4{4.37114e-008, -1.74846e-007, 2, 1, 1, 3.82137e-015, -8.74228e-008, 1, 3.82137e-015, 1, 2.18557e-007, 0, 0, 0, 0, 1}));
  
  // // Floor
  // AddRectangle(other_brdf, glm::transpose(glm::mat4{-4.37114e-008, 1, 4.37114e-008, 0, 0, -8.74228e-008, 2, 0, 1, 4.37114e-008, 1.91069e-015, 0, 0, 0, 0, 1}));
  // Ceiling
  // AddRectangle(other_brdf, glm::transpose(glm::mat4{-1, 7.64274e-015, -1.74846e-007, 0, 8.74228e-008, 8.74228e-008, -2, 2, 0, -1, -4.37114e-008, 0, 0, 0, 0, 1}));
  // BackWall
  // AddRectangle(other_brdf, glm::transpose(glm::mat4{1.91069e-015, 1, 1.31134e-007, 0, 1, 3.82137e-015, -8.74228e-008, 1, -4.37114e-008, 1.31134e-007, -2, -1, 0, 0, 0, 1}));
  // // ShortBox
  // AddCube(other_brdf, glm::transpose(glm::mat4{0.0851643, 0.289542, 1.31134e-008, 0.328631, 3.72265e-009, 1.26563e-008, -0.3, 0.3, -0.284951, 0.0865363, 5.73206e-016, 0.374592, 0, 0, 0, 1}));
  // // TallBox
  // AddCube(mf_conductor, glm::transpose(glm::mat4{0.286776, 0.098229, -2.29282e-015, -0.335439, -4.36233e-009, 1.23382e-008, -0.6, 0.6, -0.0997984, 0.282266, 2.62268e-008, -0.291415, 0, 0, 0, 1}));
  // Light
  // AddRectangle(light_brdf, glm::transpose(glm::mat4{0.235, -1.66103e-008, -7.80685e-009, -0.005, -2.05444e-008, 3.90343e-009, -0.0893, 1.98, 2.05444e-008, 0.19, 8.30516e-009, -0.03, 0, 0, 0, 1}));

  Material DiffuseBSDF;
  DiffuseBSDF.material_type = MATERIAL_TYPE_LAMBERTIAN;
  DiffuseBSDF.albedo_color = glm::vec3(0.5f);

  Material LampBSDF;
  LampBSDF.material_type = MATERIAL_TYPE_MICROFACET_CONDUCTOR;
  LampBSDF.alpha_u = LampBSDF.alpha_v = 0.25;
  LampBSDF.eta = 2.8656;  /* 2.8656, 2.11918, 1.94008 */
  LampBSDF.k = 3.03233;  /* 3.03233, 2.05611, 1.61629 */

  Material WoodBSDF;
  WoodBSDF.material_type = MATERIAL_TYPE_LAMBERTIAN;
  WoodBSDF.albedo_color = glm::vec3(0.32963, 0.257976, 0.150292);
  
  Material GlassBSDF;
  GlassBSDF.material_type = MATERIAL_TYPE_MICROFACET_DIELECTRIC;
  GlassBSDF.interior_ior = 1.5;
  GlassBSDF.exterior_ior = 1;
  GlassBSDF.alpha_u = GlassBSDF.alpha_v = 0.f;

  Material Light0002;
  Light0002.material_type = MATERIAL_TYPE_EMISSION;
  Light0002.emittance = glm::vec3(523.258, 523.258, 523.258) * glm::vec3(9.5 / 8.0, 6.7 / 8.0, 5.0 / 8.0);

  Material Light0003;
  Light0003.material_type = MATERIAL_TYPE_EMISSION;
  Light0003.emittance = glm::vec3(12048.2, 8605.84, 6196.21);

  Material Specular{
    glm::vec3{1.0f},
    0,
    glm::vec3{0.f},
    MATERIAL_TYPE_SPECULAR
  };

  Texture wall_tex;
  Texture::Load(u8"../../textures/brick.jpg", wall_tex);
  int wall_tex_id = AddTexture(wall_tex, "wall");

  Texture pic;
  Texture::Load(u8"../../textures/pic.jpg", pic);
  int picture_tex_id = AddTexture(pic, "picture");

  // Texture envmap;
  // Texture::Load(u8"../../textures/envmap_clouds_4k.hdr", envmap);
  // envmap.SetSampleType(SAMPLE_TYPE_LINEAR);
  // envmap_id_ = AddTexture(envmap, "Clouds");

  Material DiffuseTexBSDF;
  DiffuseTexBSDF.material_type = MATERIAL_TYPE_LAMBERTIAN;
  DiffuseTexBSDF.albedo_color = glm::vec3(1.f);
  DiffuseTexBSDF.albedo_texture_id = wall_tex_id;

  Material PictureBSDF;
  PictureBSDF.material_type = MATERIAL_TYPE_LAMBERTIAN;
  PictureBSDF.albedo_color = glm::vec3(1.f);
  PictureBSDF.albedo_texture_id = picture_tex_id;

  // glm::mat4 room_trans = glm::inverse(glm::transpose(glm::mat4{-0.00500708, -0.00467005, -0.999977, 16.2155, 0, 0.999989, -0.00467011, 4.05167, 0.999987, -2.34659e-005, -0.00502464, 0.0114864, 0, 0, 0, 1}));
  glm::mat4 room_trans = glm::inverse(glm::transpose(glm::mat4{-0.00500708, -0.00467005, 0.999977, 16.2155, 0, 0.999989, 0.00467011, 4.05167, 0.999987, -2.34659e-005, 0.00502464, 0.0114864, 0, 0, 0, 1}));
  // room_trans = glm::scale(room_trans, glm::vec3{0.5f});
  SetGlobalTransformForNew(room_trans);

  Mesh Lamp_0001;
  Mesh::LoadObjFile(u8"../../models/Room_Mesh007.obj", Lamp_0001);
  AddEntity(Lamp_0001, LampBSDF, glm::mat4{1.f});

  Mesh Diffuse_0001;
  Mesh::LoadObjFile(u8"../../models/Room_Mesh004.obj", Diffuse_0001);
  AddEntity(Diffuse_0001, DiffuseBSDF, glm::mat4{1.f});

  AddRectangle(Light0002, glm::transpose(glm::mat4{-1.20536e-008, 0.275755, 1.20536e-008, -2.48161, 0, -6.64767e-009, 0.152081, 6, 0.275754, 1.20536e-008, 5.2688e-016, 2.5894, 0, 0, 0, 1}));

  AddRectangle(Light0003, glm::transpose(glm::mat4{-0.0101082, 0.067068, 0.00138972, -2.69082, -0.0610016, -0.0070995, -0.00842772, 5.10417, -0.0282857, -0.00865658, 0.0176788, -3.77057, 0, 0, 0, 1}));
  // AddRectangle(Light0003, glm::transpose(glm::mat4{-0.0101082, 0.067068, 0.00138972, -2.69082 * 2, -0.0610016, -0.0070995, -0.00842772, 5.10417 * 2, -0.0282857, -0.00865658, 0.0176788, -3.77057 * 2, 0, 0, 0, 1 * 2}) / 2.0f);

  Mesh Lamp_0002;
  Mesh::LoadObjFile(u8"../../models/Room_Mesh001.obj", Lamp_0002);
  AddEntity(Lamp_0002, LampBSDF, glm::mat4{1.f});

  Mesh Lamp_0003;
  Mesh::LoadObjFile(u8"../../models/Room_Mesh005.obj", Lamp_0003);
  AddEntity(Lamp_0003, LampBSDF, glm::mat4{1.f});

  Mesh Diffuse_0004;
  Mesh::LoadObjFile(u8"../../models/Room_Mesh008.obj", Diffuse_0004);
  AddEntity(Diffuse_0004, DiffuseBSDF, glm::mat4{1.f});

  Mesh Glass;
  Mesh::LoadObjFile(u8"../../models/Room_Mesh002.obj", Glass);
  AddEntity(Glass, GlassBSDF, glm::mat4{1.f});

  Mesh Diffuse_0005;
  Mesh::LoadObjFile(u8"../../models/Room_Mesh011.obj", Diffuse_0005);
  AddEntity(Diffuse_0005, DiffuseBSDF, glm::mat4{1.f});

  Mesh Diffuse_0006;
  Mesh::LoadObjFile(u8"../../models/Room_Mesh003.obj", Diffuse_0006);
  AddEntity(Diffuse_0006, DiffuseBSDF, glm::mat4{1.f});

  Mesh Diffuse_0007;
  Mesh::LoadObjFile(u8"../../models/Room_Mesh009.obj", Diffuse_0007);
  AddEntity(Diffuse_0007, DiffuseBSDF, glm::mat4{1.f});

  Mesh Diffuse_0008;
  Mesh::LoadObjFile(u8"../../models/Room_Mesh006.obj", Diffuse_0008);
  AddEntity(Diffuse_0008, DiffuseBSDF, glm::mat4{1.f});

  Mesh Wood;
  Mesh::LoadObjFile(u8"../../models/Room_Mesh000.obj", Wood);
  AddEntity(Wood, WoodBSDF, glm::mat4{1.f});

  Mesh Diffuse_0009;
  Mesh::LoadObjFile(u8"../../models/Room_Mesh010.obj", Diffuse_0009);
  AddEntity(Diffuse_0009, DiffuseBSDF, glm::mat4{1.f});

  AddEntity(
      AcceleratedMesh({{{-3.9f, 0.0f, -4.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // position, normal, tex
                       {{-3.9f, 0.0f, 4.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},   
                       {{-3.9f, 8.0f, -4.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
                       {{-3.9f, 8.0f, 4.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}},
                      {0, 1, 2, 2, 1, 3}),
      DiffuseTexBSDF, glm::mat4{1.0f});

  AddEntity(
    AcceleratedMesh({{{-3.8f, 4.0f, -2.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}, // position, normal, tex
                      {{-3.8f, 4.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},   
                      {{-3.8f, 6.0f, -2.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
                      {{-3.8f, 6.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}},
                    {0, 1, 2, 2, 1, 3}),
    PictureBSDF, glm::mat4{1.0f});

  AddEntity(Mesh::Sphere(glm::vec3(-3.0f, 2.5f, -2.5f), 0.5f), Specular);

  // Mesh ;
  // Mesh::LoadObjFile(u8"../../models/Room_Mesh0.obj", );
  // AddEntity(, BSDF, glm::mat4{1.f});

  glm::mat4 car_matrix = glm::inverse(glm::transpose(glm::mat4{-0.872027, 0.135655, -0.470284, -8.83707, 0, 0.960826, 0.277154, 5.8377, -0.489459, -0.241685, 0.837865, 14.6207, 0, 0, 0, 1}));
  car_matrix = glm::scale(car_matrix, glm::vec3(0.3f));
  car_matrix = glm::translate(car_matrix, glm::vec3(-0.5f, -7.0f, 8.0f));
  SetGlobalTransformForNew(car_matrix);

  Material CarPaintBsdf {
    glm::vec3{1.0f}, // albedo
    0, // texture id
    glm::vec3{0.f}, // emittance,
    MATERIAL_TYPE_MICROFACET_CONDUCTOR,
    1.65746, // eta  /*1.65746, 0.880369, 0.521229*/,
    9.22387, // k  /* 9.22387, 6.26952, 4.837 */,
    0.1f,  // alpha u
    0.1f,  // alpha v
    glm::vec3{0.06f, 0.18f, 0.02f}, // specular_reflectance
    0.f, // interior_ior not used
    glm::vec3{1.0f}, // specular_transmittance
    0.f // exterior_ior not used
  };

  Material WindowGlassBsdf;
  // WindowGlassBsdf.material_type = MATERIAL_TYPE_SPECULAR;
  WindowGlassBsdf.material_type = MATERIAL_TYPE_MICROFACET_DIELECTRIC;
  WindowGlassBsdf.alpha_u = 0.f;
  WindowGlassBsdf.alpha_v = 0.f;
  WindowGlassBsdf.interior_ior = 1.5f;
  WindowGlassBsdf.exterior_ior = 1.0f;

  Material ChromeBsdf;
  ChromeBsdf.material_type = MATERIAL_TYPE_MICROFACET_CONDUCTOR;
  ChromeBsdf.alpha_u = ChromeBsdf.alpha_v = 0.1f;
  ChromeBsdf.eta = 4.36968; /* 4.36968, 2.9167, 1.6547 */
  ChromeBsdf.k = 5.20643; /* 5.20643, 4.23136, 3.75495 */

  Material BlackRubberBsdf;
  BlackRubberBsdf.material_type = MATERIAL_TYPE_MICROFACET_DIELECTRIC; /* rough plastic */
  BlackRubberBsdf.alpha_u = BlackRubberBsdf.alpha_v = 0.4f;
  BlackRubberBsdf.interior_ior = 1.5f;
  BlackRubberBsdf.exterior_ior = 1.0f;
  BlackRubberBsdf.albedo_color = glm::vec3{0.028991, 0.028991, 0.028991};
  /*			
      <boolean name="nonlinear" value="true" />
			<rgb name="diffuse_reflectance" value="0.028991, 0.028991, 0.028991" />
  */

  Material SteelBsdf;
  SteelBsdf.material_type = MATERIAL_TYPE_MICROFACET_CONDUCTOR;

  Material WhiteRubberBsdf;
  WhiteRubberBsdf.material_type = MATERIAL_TYPE_LAMBERTIAN;
  WhiteRubberBsdf.albedo_color = glm::vec3{0.578596, 0.578596, 0.578596};

  Material GroundBsdf;
  GroundBsdf.material_type = MATERIAL_TYPE_LAMBERTIAN;
  GroundBsdf.albedo_color = glm::vec3{0.17074, 0.17074, 0.17074};

  Material BlackBsdf;
  BlackBsdf.material_type = MATERIAL_TYPE_LAMBERTIAN;
  BlackBsdf.albedo_color = glm::vec3{0.f};

  Material LeatherBsdf;
  LeatherBsdf.material_type = MATERIAL_TYPE_MICROFACET_DIELECTRIC; /* rough plastic */
  LeatherBsdf.alpha_u = LeatherBsdf.alpha_v = 0.4f;
  LeatherBsdf.interior_ior = 1.5f;
  LeatherBsdf.exterior_ior = 1.0f;
  LeatherBsdf.albedo_color = glm::vec3{0.417004, 0.403278, 0.391924};
  /*
  		<boolean name="nonlinear" value="true" />
			<rgb name="diffuse_reflectance" value="0.417004, 0.403278, 0.391924" />
  */
  
  Material Leather2Bsdf;
  Leather2Bsdf.material_type = MATERIAL_TYPE_MICROFACET_DIELECTRIC; /* rough plastic */
  Leather2Bsdf.alpha_u = Leather2Bsdf.alpha_v = 0.3f;
  Leather2Bsdf.interior_ior = 1.5f;
  Leather2Bsdf.exterior_ior = 1.0f;
  Leather2Bsdf.albedo_color = glm::vec3{0.612066, 0.612066, 0.612066};
  /*
  <boolean name="nonlinear" value="true" />
  <rgb name="diffuse_reflectance" value="0.612066, 0.612066, 0.612066" />
  */

  Material InnerBodyBsdf;
  InnerBodyBsdf.material_type = MATERIAL_TYPE_LAMBERTIAN;
  InnerBodyBsdf.albedo_color = glm::vec3{0.028991, 0.028991, 0.028991};

  Material DashBsdf;
  DashBsdf.material_type = MATERIAL_TYPE_MICROFACET_DIELECTRIC; /* rough plastic*/
  DashBsdf.alpha_u = DashBsdf.alpha_v = 0.1f;
  DashBsdf.interior_ior = 1.5f;
  DashBsdf.exterior_ior = 1.0f;
  DashBsdf.albedo_color = glm::vec3{0.434446, 0.434446, 0.434446};
  /*
  <boolean name="nonlinear" value="true" />
  <rgb name="diffuse_reflectance" value="0.434446, 0.434446, 0.434446" />
  */

  Material CabinBsdf;
  CabinBsdf.material_type = MATERIAL_TYPE_LAMBERTIAN;
  CabinBsdf.albedo_color = glm::vec3{0.531049, 0.531049, 0.531049};

  Mesh BlackRubber_0001;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh032.obj", BlackRubber_0001);
  AddEntity(BlackRubber_0001, BlackRubberBsdf, glm::mat4{1.0f});

  Mesh WhiteRubber_0001;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh025.obj", WhiteRubber_0001);
  AddEntity(WhiteRubber_0001, WhiteRubberBsdf, glm::mat4{1.0f});

  Mesh Chrome_0001;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh031.obj", Chrome_0001);
  AddEntity(Chrome_0001, ChromeBsdf, glm::mat4{1.0f});

  Mesh Chrome_0002;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh022.obj", Chrome_0002);
  AddEntity(Chrome_0002, ChromeBsdf, glm::mat4{1.0f});

  Mesh Ground;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh034.obj", Ground);
  AddEntity(Ground, GroundBsdf, glm::mat4{1.0f});

  Mesh InnerBody_0001;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh048.obj", InnerBody_0001);
  AddEntity(InnerBody_0001, InnerBodyBsdf, glm::mat4{1.0f});

  Mesh Steel_0001;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh030.obj", Steel_0001);
  AddEntity(Steel_0001, SteelBsdf, glm::mat4{1.0f});

  Mesh Chrome_0003;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh040.obj", Chrome_0003);
  AddEntity(Chrome_0003, ChromeBsdf, glm::mat4{1.0f});

  Mesh Leather;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh023.obj", Leather);
  AddEntity(Leather, LeatherBsdf, glm::mat4{1.0f});

  Mesh Steel_0002;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh015.obj", Steel_0002);
  AddEntity(Steel_0002, SteelBsdf, glm::mat4{1.0f});

  Mesh Steel_0003;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh038.obj", Steel_0003);
  AddEntity(Steel_0003, SteelBsdf, glm::mat4{1.0f});

  Mesh Leather2;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh027.obj", Leather2);
  AddEntity(Leather2, Leather2Bsdf, glm::mat4{1.0f});

  Mesh Steel_0004;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh036.obj", Steel_0004);
  AddEntity(Steel_0004, SteelBsdf, glm::mat4{1.0f});
  
  Mesh Steel_0005;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh054.obj", Steel_0005);
  AddEntity(Steel_0005, SteelBsdf, glm::mat4{1.0f});

  Mesh Steel_0006;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh026.obj", Steel_0006);
  AddEntity(Steel_0006, SteelBsdf, glm::mat4{1.0f});

  Mesh Chrome_0004;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh028.obj", Chrome_0004);
  AddEntity(Chrome_0004, ChromeBsdf, glm::mat4{1.0f});

  Mesh CarPaint_0001;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh046.obj", CarPaint_0001);
  AddEntity(CarPaint_0001, CarPaintBsdf, glm::mat4{1.0f});

  Mesh InnerBody_0002;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh019.obj", InnerBody_0002);
  AddEntity(InnerBody_0002, InnerBodyBsdf, glm::mat4{1.0f});

  Mesh WindowGlass_0001;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh017.obj", WindowGlass_0001);
  AddEntity(WindowGlass_0001, WindowGlassBsdf, glm::mat4{1.0f});

  Mesh BlackRubber_0002;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh014.obj", BlackRubber_0002);
  AddEntity(BlackRubber_0002, BlackRubberBsdf, glm::mat4{1.0f});

  Mesh WhiteRubber_0002;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh013.obj", WhiteRubber_0002);
  AddEntity(WhiteRubber_0002, WhiteRubberBsdf, glm::mat4{1.0f});

  Mesh Chrome_0005;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh035.obj", Chrome_0005);
  AddEntity(Chrome_0005, ChromeBsdf, glm::mat4{1.0f});

  Mesh Chrome_0006;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh042.obj", Chrome_0006);
  AddEntity(Chrome_0006, ChromeBsdf, glm::mat4{1.0f});

  Mesh Black_0001;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh029.obj", Black_0001);
  AddEntity(Black_0001, BlackBsdf, glm::mat4{1.0f});

  Mesh Steel_0007;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh018.obj", Steel_0007);
  AddEntity(Steel_0007, SteelBsdf, glm::mat4{1.0f});

  Mesh Chrome_0007;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh024.obj", Chrome_0007);
  AddEntity(Chrome_0007, ChromeBsdf, glm::mat4{1.0f});

  Mesh Chrome_0008;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh041.obj", Chrome_0008);
  AddEntity(Chrome_0008, ChromeBsdf, glm::mat4{1.0f});

  Mesh CarPaint_0002;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh044.obj", CarPaint_0002);
  AddEntity(CarPaint_0002, CarPaintBsdf, glm::mat4{1.0f});

  Mesh Steel_0008;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh045.obj", Steel_0008);
  AddEntity(Steel_0008, SteelBsdf, glm::mat4{1.0f});

  Mesh Steel_0009;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh058.obj", Steel_0009);
  AddEntity(Steel_0009, SteelBsdf, glm::mat4{1.0f});

  Mesh CarPaint_0003;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh047.obj", CarPaint_0003);
  AddEntity(CarPaint_0003, CarPaintBsdf, glm::mat4{1.0f});

  Mesh Chrome_0009;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh021.obj", Chrome_0009);
  AddEntity(Chrome_0009, ChromeBsdf, glm::mat4{1.0f});

  Mesh Steel_0010;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh037.obj", Steel_0010);
  AddEntity(Steel_0010, SteelBsdf, glm::mat4{1.0f});

  Mesh Steel_0011;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh049.obj", Steel_0011);
  AddEntity(Steel_0011, SteelBsdf, glm::mat4{1.0f});

  Mesh Steel_0012;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh050.obj", Steel_0012);
  AddEntity(Steel_0012, SteelBsdf, glm::mat4{1.0f});

  Mesh Steel_0013;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh043.obj", Steel_0013);
  AddEntity(Steel_0013, SteelBsdf, glm::mat4{1.0f});

  Mesh Steel_0014;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh051.obj", Steel_0014);
  AddEntity(Steel_0014, SteelBsdf, glm::mat4{1.0f});

  Mesh Steel_0015;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh052.obj", Steel_0015);
  AddEntity(Steel_0015, SteelBsdf, glm::mat4{1.0f});

  Mesh Chrome_0010;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh053.obj", Chrome_0010);
  AddEntity(Chrome_0010, ChromeBsdf, glm::mat4{1.0f});

  Mesh Steel_0016;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh033.obj", Steel_0016);
  AddEntity(Steel_0016, SteelBsdf, glm::mat4{1.0f});

  Mesh Steel_0017;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh055.obj", Steel_0017);
  AddEntity(Steel_0017, SteelBsdf, glm::mat4{1.0f});

  Mesh CarPaint_0004;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh060.obj", CarPaint_0004);
  AddEntity(CarPaint_0004, CarPaintBsdf, glm::mat4{1.0f});

  Mesh Dash;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh059.obj", Dash);
  AddEntity(Dash, DashBsdf, glm::mat4{1.0f});

  Mesh Black_0002;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh020.obj", Black_0002);
  AddEntity(Black_0002, BlackBsdf, glm::mat4{1.0f});

  Mesh Cabin;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh061.obj", Cabin);
  AddEntity(Cabin, CabinBsdf, glm::mat4{1.0f});

  Mesh CarPaint_0005;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh062.obj", CarPaint_0005);
  AddEntity(CarPaint_0005, CarPaintBsdf, glm::mat4{1.0f});

  Mesh CarPaint_0006;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh012.obj", CarPaint_0006);
  AddEntity(CarPaint_0006, CarPaintBsdf, glm::mat4{1.0f});

  Mesh WindowGlass_0002;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh016.obj", WindowGlass_0002);
  AddEntity(WindowGlass_0002, WindowGlassBsdf, glm::mat4{1.0f});

  Mesh Steel_0018;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh011.obj", Steel_0018);
  AddEntity(Steel_0018, SteelBsdf, glm::mat4{1.0f});

  Mesh Steel_0019;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh010.obj", Steel_0019);
  AddEntity(Steel_0019, SteelBsdf, glm::mat4{1.0f});

  Mesh Steel_0020;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh007.obj", Steel_0020);
  AddEntity(Steel_0020, SteelBsdf, glm::mat4{1.0f});

  Mesh Steel_0021;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh006.obj", Steel_0021);
  AddEntity(Steel_0021, SteelBsdf, glm::mat4{1.0f});

  Mesh WindowGlass_0003;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh004.obj", WindowGlass_0003);
  AddEntity(WindowGlass_0003, WindowGlassBsdf, glm::mat4{1.0f});

  Mesh WindowGlass_0004;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh003.obj", WindowGlass_0004);
  AddEntity(WindowGlass_0004, WindowGlassBsdf, glm::mat4{1.0f});

  Mesh Steel_0022;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh005.obj", Steel_0022);
  AddEntity(Steel_0022, SteelBsdf, glm::mat4{1.0f});

  Mesh InnerBody_0003;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh039.obj", InnerBody_0003);
  AddEntity(InnerBody_0003, InnerBodyBsdf, glm::mat4{1.0f});

  Mesh Chrome_0011;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh057.obj", Chrome_0011);
  AddEntity(Chrome_0011, ChromeBsdf, glm::mat4{1.0f});

  Mesh Steel_0023;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh009.obj", Steel_0023);
  AddEntity(Steel_0023, SteelBsdf, glm::mat4{1.0f});

  Mesh Steel_0024;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh008.obj", Steel_0024);
  AddEntity(Steel_0024, SteelBsdf, glm::mat4{1.0f});

  Mesh Steel_0025;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh056.obj", Steel_0025);
  AddEntity(Steel_0025, SteelBsdf, glm::mat4{1.0f});

  Mesh Steel_0026;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh002.obj", Steel_0026);
  AddEntity(Steel_0026, SteelBsdf, glm::mat4{1.0f});

  Mesh Steel_0027;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh001.obj", Steel_0027);
  AddEntity(Steel_0027, SteelBsdf, glm::mat4{1.0f});

  Mesh Steel_0028;
  Mesh::LoadObjFile(u8"../../models/Car_Mesh000.obj", Steel_0028);
  AddEntity(Steel_0028, SteelBsdf, glm::mat4{1.0f});

  ResetGlobalTransformForNew();

  // Mat Preview
  // glm::mat4 mat_matrix = glm::inverse(glm::transpose(glm::mat4{-0.721367, -0.373123, 0.583445, 3.04068, -8.26273e-008, 0.842456, 0.538765, 3.17153, 0.692553, -0.388647, 0.60772, 3.20454, 0, 0, 0, 1}));
  // glm::mat4 mat_matrix{1.f};
  // mat_matrix = glm::scale(mat_matrix, glm::vec3(0.2f));
  // mat_matrix = glm::translate(mat_matrix, glm::vec3(0.f, 0.f, -5.f));
  // SetGlobalTransformForNew(mat_matrix);
  // // ResetGlobalTransformForNew();
  Material RoughMetal{
    glm::vec3{1.f},  //albedo_color
    0, // albedo_texture_id 
    glm::vec3{0.f}, // emittance
    MATERIAL_TYPE_MICROFACET_CONDUCTOR,
    0.200438, // eta
    3.91295, //k
    0.1f, // alpha_u
    0.1f // alpha_v
  };
  Material Stand{
    glm::vec3{0.2f}, //albedo_color
    0,
    glm::vec3{0.f},
    MATERIAL_TYPE_LAMBERTIAN
  };
  // // glm::mat4 
  // Mesh mesh1, mesh2, mesh3;
  // Mesh::LoadObjFile(u8"../../models/matpreview_Mesh001.obj", mesh1);
  // Mesh::LoadObjFile(u8"../../models/matpreview_Mesh002.obj", mesh2);
  // Mesh::LoadObjFile(u8"../../models/matpreview_Mesh000.obj", mesh3);
  // // AddEntity(mesh1, Specular, glm::transpose(glm::mat4{0.482906, 0, 0, 0.0571719, 0, 0.482906, 0, 0.213656, 0, 0, 0.482906, 0.0682078, 0, 0, 0, 1}));
  // // AddEntity(mesh2, Specular, glm::transpose(glm::mat4{0.482906, 0, 0, 0.156382, 0, 0.482906, 0, 0.777229, 0, 0, 0.482906, 0.161698, 0, 0, 0, 1}));
  // // AddEntity(mesh3, Stand, glm::transpose(glm::mat4{0.482906, 0, 0, 0.110507, 0, 0.482906, 0, 0.494301, 0, 0, 0.482906, 0.126194, 0, 0, 0, 1}));
  // AddEntity(mesh1, Specular, glm::transpose(glm::mat4{1.f}));
  // AddEntity(mesh2, Specular, glm::transpose(glm::mat4{1.f}));
  // AddEntity(mesh3, Stand, glm::transpose(glm::mat4{1.f}));
}




} // end namespace sparks