#pragma once
#include "Sources/KingdomEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/integer.hpp>
#include "Sources/Renderer/VertexArray.h"
#include "Sources/Renderer/Buffer.h"
#include "Sources/Renderer/RendererAPI.h"
#include "Sources/Renderer/Shader.h"
#include "Sources/Renderer/Texture.h"
#include "Sources/lib/stb/stb_image.h"


class TerrainGenerator {
public:
	float m_HeightFactor;
public:
	TerrainGenerator();
	~TerrainGenerator();
	void Render();
private:
	glm::ivec2 m_gridSize;
	glm::vec2 m_terrainSize;
	int m_patchCount;
private:
	std::shared_ptr<VertexArray>  m_VAO;
	std::shared_ptr<VertexBuffer> m_VBO;
	std::shared_ptr<IndexBuffer>  m_IBO;
	std::shared_ptr<Shader>  m_shader;
	std::shared_ptr<Texture> m_heightmap;
	std::shared_ptr<Texture> m_heightmap_caves;
	std::shared_ptr<Texture> m_textures[2];
};

