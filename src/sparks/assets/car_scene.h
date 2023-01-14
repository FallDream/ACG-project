namespace sparks {

void Scene::CreateCarScene() {
  // SetCameraToWorld(glm::transpose(glm::mat4{-0.872027, 0.135655, 0.470284, -8.83707, 0, 0.960826, -0.277154, 5.8377, -0.489459, -0.241685, -0.837865, 14.6207, 0, 0, 0, 1}));
  // SetCameraToWorld(glm::transpose(glm::mat4{-0.872027, 0.135655, -0.470284, -8.83707, 0, 0.960826, 0.277154, 5.8377, -0.489459, -0.241685, 0.837865, 14.6207, 0, 0, 0, 1}));
  float cur_fov = GetCamera().getfov();
  GetCamera().UpdateFov(35 - cur_fov);

  glm::mat4 car_matrix = glm::inverse(glm::transpose(glm::mat4{-0.872027, 0.135655, -0.470284, -8.83707, 0, 0.960826, 0.277154, 5.8377, -0.489459, -0.241685, 0.837865, 14.6207, 0, 0, 0, 1}));
  glm::mat4 rot{1.0f};
  glm::rotate(rot, glm::radians(30.f), glm::vec3(1.0f, 0.0f, 0.0f));
  car_matrix = car_matrix * rot;
  car_matrix = glm::translate(car_matrix, glm::vec3(0, -5, -15.0));

  SetGlobalTransformForNew(car_matrix);

  Texture envmap;
  Texture::Load(u8"../../textures/sky.hdr", envmap);
  envmap.SetSampleType(SAMPLE_TYPE_LINEAR);
  envmap_id_ = AddTexture(envmap, "env");
  // envmap_to_world_ = glm::transpose(glm::mat4{-0.922278, 0, 0.386527, 0, 0, 1, 0, 0, -0.386527, 0, -0.922278, 1.17369, 0, 0, 0, 1});

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
  GroundBsdf.albedo_color = glm::vec3{0.07074, 0.07074, 0.07074};

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

  // Mesh Ground;
  // Mesh::LoadObjFile(u8"../../models/Car_Mesh034.obj", Ground);
  // AddEntity(Ground, GroundBsdf, glm::mat4{1.0f});

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

  // Mesh ;
  // Mesh::LoadObjFile(u8"../../models/Car_Mesh0.obj", );
  // AddEntity(, Bsdf, glm::mat4{1.0f});

  /* Piano Start Here */

  ResetGlobalTransformForNew();

  Texture PianoTexture;
  int piano_tex_id = Texture::Load(u8"../../textures/Nero.png", PianoTexture);

  Material PianoBsdf;
  PianoBsdf.material_type = MATERIAL_TYPE_MICROFACET_DIELECTRIC;
  PianoBsdf.albedo_texture_id = piano_tex_id;
  PianoBsdf.alpha_u = 0.f;
  PianoBsdf.alpha_v = 0.f;
  PianoBsdf.interior_ior = 1.5f;
  PianoBsdf.exterior_ior = 1.0f;

  Mesh PianoMesh;
  Mesh::LoadObjFile(u8"../../models/Piano.obj", PianoMesh);

  glm::mat4 piano_transform{1.0f};
  piano_transform = glm::rotate(piano_transform, glm::radians(40.f), glm::vec3(0.0, 1.0, 0.0));
  piano_transform = glm::scale(piano_transform, glm::vec3(0.02f, 0.02f, 0.02f));
  piano_transform = glm::translate(piano_transform, glm::vec3(80.0f, 0.0f, -300.0f));

  AddEntity(PianoMesh, PianoBsdf, piano_transform);

  /* Ground */
  Material WorldGroundBsdf;
  WorldGroundBsdf.material_type = MATERIAL_TYPE_SPECULAR;
  AddEntity(AcceleratedMesh({{{-10.0f, 0.0f, 10.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
                             {{-10.0f, 0.0f, -10.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 10.0f}},
                             {{10.0f, 0.0f, 10.0f}, {0.0f, 1.0f, 0.0f}, {10.0f, 0.0f}},
                             {{10.0f, 0.0f, -10.0f}, {0.0f, 1.0f, 0.0f}, {10.0f, 10.0f}}},
                            {0, 1, 2, 2, 1, 3}),
      WorldGroundBsdf, glm::mat4{1.0f});

}


} // end namespace sparks