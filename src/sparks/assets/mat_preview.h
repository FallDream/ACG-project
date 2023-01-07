namespace sparks{

void Scene::CreateMaterialPreviewScene() {
  AddTexture(Texture(1, 1, glm::vec4{1.0f}, SAMPLE_TYPE_LINEAR), "Pure White");
  AddTexture(Texture(1, 1, glm::vec4{0.0f}, SAMPLE_TYPE_LINEAR), "Pure Black");
  // SetCameraToWorld(glm::transpose(glm::mat4{-0.721367, -0.373123, -0.583445, 3.04068, -8.26273e-008, 0.842456, -0.538765, 3.17153, 0.692553, -0.388647, -0.60772, 3.20454, 0, 0, 0, 1}));
  SetCameraToWorld(glm::transpose(glm::mat4{-0.721367, -0.373123, 0.583445, 3.04068, -8.26273e-008, 0.842456, 0.538765, 3.17153, 0.692553, -0.388647, 0.60772, 3.20454, 0, 0, 0, 1}));
  float cur_fov = GetCamera().getfov();
  GetCamera().UpdateFov(35 - cur_fov);

  Texture ice_texture;
  Texture::Load("../../textures/ice.jpg", ice_texture);
  int ice_id = AddTexture(ice_texture, "ice");

  Material Specular{
    glm::vec3{1.0f},
    0,
    glm::vec3{0.f},
    MATERIAL_TYPE_SPECULAR
  };
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
  Material RoughDielectric{
    glm::vec3{1.f},  //albedo_color
    0, // albedo_texture_id 
    glm::vec3{0.f}, // emittance
    MATERIAL_TYPE_MICROFACET_DIELECTRIC,
    0.f, // eta
    0.f, //k
    0.1f, // alpha_u
    0.1f, // alpha_v
    1.5046f, // interior_ior
    1.000277f // exterior_ior
  };
  Material RoughRoughDielectric{
    glm::vec3{1.f},  //albedo_color
    0, // albedo_texture_id 
    glm::vec3{0.f}, // emittance
    MATERIAL_TYPE_MICROFACET_DIELECTRIC,
    0.f, // eta
    0.f, //k
    0.5f, // alpha_u
    0.5f, // alpha_v
    1.5046f, // interior_ior
    1.000277f // exterior_ior
  };
  Material Stand{
    glm::vec3{0.2f}, //albedo_color
    0,
    glm::vec3{0.f},
    MATERIAL_TYPE_LAMBERTIAN
  };
  // Material Floor {
  //   glm::vec3{0.325, 0.31, 0.25}, //albedo_color
  //   0,
  //   glm::vec3{0.f},
  //   MATERIAL_TYPE_LAMBERTIAN
  // };
  Material Floor {
    glm::vec3{1.0f}, //albedo_color
    ice_id,
    glm::vec3{0.f},
    MATERIAL_TYPE_SPECULAR
  };

  Material mat_to_use = RoughDielectric;

  // Floor
  AddBiiigRectangle(Floor, glm::transpose(glm::mat4{-1.88298, 1.9602, 2.50299e-007, -0.708772, -2.37623e-007, 1.18811e-007, -2.71809, 0, -1.9602, -1.88298, 8.90586e-008, -0.732108, 0, 0, 0, 1}));
  AddEntity(
      AcceleratedMesh({{{-1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}, // position, normal, tex
                       {{-1.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},   
                       {{1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
                       {{1.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}},
                      {0, 1, 2, 2, 1, 3}),
      Material{}, glm::mat4{1.0f});
  Mesh mesh1, mesh2, mesh3;
  Mesh::LoadObjFile(u8"../../models/matpreview_Mesh001.obj", mesh1);
  Mesh::LoadObjFile(u8"../../models/matpreview_Mesh002.obj", mesh2);
  Mesh::LoadObjFile(u8"../../models/matpreview_Mesh000.obj", mesh3);
  AddEntity(mesh1, mat_to_use, glm::transpose(glm::mat4{0.482906, 0, 0, 0.0571719, 0, 0.482906, 0, 0.213656, 0, 0, 0.482906, 0.0682078, 0, 0, 0, 1}));
  AddEntity(mesh2, mat_to_use, glm::transpose(glm::mat4{0.482906, 0, 0, 0.156382, 0, 0.482906, 0, 0.777229, 0, 0, 0.482906, 0.161698, 0, 0, 0, 1}));
  AddEntity(mesh3, Stand, glm::transpose(glm::mat4{0.482906, 0, 0, 0.110507, 0, 0.482906, 0, 0.494301, 0, 0, 0.482906, 0.126194, 0, 0, 0, 1}));
  Texture envmap;
  Texture::Load(u8"../../textures/envmap_matpreview.hdr", envmap);
  envmap.SetSampleType(SAMPLE_TYPE_LINEAR);
  envmap_id_ = AddTexture(envmap, "Clouds");
  envmap_to_world_ = glm::transpose(glm::mat4{-0.922278, 0, 0.386527, 0, 0, 1, 0, 0, -0.386527, 0, -0.922278, 1.17369, 0, 0, 0, 1});
}

}
