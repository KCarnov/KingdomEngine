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
#include <bitset>


class SpaceshipBlueprint
{
public:
	SpaceshipBlueprint();
	~SpaceshipBlueprint();
	void Render();
private:
	void Init();
	
	void PropagateMarchingSquare();

private:
	glm::ivec2 grid = glm::ivec2(7, 7);

	int* g_vertex;
	int* c_vertex;

	glm::vec2 gridSize = glm::vec2(128);
	int m_count;
	// Rendering
	std::shared_ptr<VertexArray>  m_VAO;
	std::shared_ptr<VertexBuffer> m_VBO;
	std::shared_ptr<IndexBuffer>  m_IBO;
	std::shared_ptr<Shader>  m_shader;
	std::shared_ptr<Texture> m_textures[2];

};