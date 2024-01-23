#include "TerrainGenerator.h"

TerrainGenerator::TerrainGenerator()
{
	glPatchParameteri(GL_PATCH_VERTICES, 4);

	//- terrain
	m_VAO = std::make_shared<VertexArray>();
	m_VAO->Bind();
	m_VBO = std::make_shared<VertexBuffer>(0); // empty buffer
	m_VAO->AddVertexBuffer(m_VBO);

	// --- Shaders ----
	m_shader = std::make_shared<Shader>(
		"Ressources/shaders/terrain/terrain_vs.glsl",
		"Ressources/shaders/terrain/terrain_fs.glsl",
		"Ressources/shaders/terrain/terrain_tcs.glsl",
		"Ressources/shaders/terrain/terrain_tes.glsl");
		// TO DO: Le geometry shader est dans shader.cpp ...
	m_shader->use();

	m_heightmap = std::make_shared<Texture>("Ressources/heightmaps/terrain-heightmap-01-cave.png");
	m_heightmap_caves = std::make_shared<Texture>("Ressources/heightmaps/terrain-heightmap-01-cave.png");
	m_textures[0] = std::make_shared<Texture>("Ressources/textures/4.jpg");

	m_terrainSize.x = m_heightmap->GetWidth();
	m_terrainSize.y = m_heightmap->GetHeight();
	m_gridSize = glm::ivec2(128, 128);
	m_patchCount = m_gridSize.x * m_gridSize.y;


	m_shader->setInt("u_heightmap", 0);
	m_shader->setInt("texture2", 1);
	m_shader->setInt("u_heightmap_caves", 2);
}

TerrainGenerator::~TerrainGenerator()
{
}

void TerrainGenerator::Render()
{
	m_heightmap->BindTexture(0);
	m_textures[0]->BindTexture(1);
	m_heightmap_caves->BindTexture(2);
	m_shader->use();

	m_shader->setInt2("gridSize", m_gridSize);
	m_shader->setVec2("terrainSize", m_terrainSize);
	m_shader->setFloat("u_HeightFactor", m_HeightFactor);

	RendererAPI::DrawArraysInstanced(m_shader, m_VAO, m_patchCount);
}


