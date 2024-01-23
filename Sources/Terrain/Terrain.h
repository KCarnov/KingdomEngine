#pragma once
#include "Sources/KingdomEngine.h"
#include <glm/glm.hpp>
#include "Sources/Renderer/VertexArray.h"
#include "Sources/Renderer/Buffer.h"
#include "Sources/Renderer/RendererAPI.h"
#include "Sources/Renderer/Shader.h"
#include "Sources/lib/stb/stb_image.h"
//#define WIDTH = 512
class Terrain {

public:
	Terrain(float w, float h);
	~Terrain();
	//struct VertexMesh {
	//	glm::vec3 position;
	//	glm::vec3 color;
	//};
	struct VertexMesh {
		float altitude;
		float angle;
	};
	void GenerateTerrain();
	void GenerateTerrain_v2();
	void GenerateIndex();
	float GetVBOCount() { return m_VBOT->GetSize(); }
	std::shared_ptr<VertexArray> GetTerrainVAO() { return m_VAOT; }
	std::shared_ptr<Shader> GetTerrainShader() { return myshaderT; }
	float getheight(const float& x, const float& z);
	float getheight2(const float& x, const float& z);

	VertexMesh* gridmesh2;
	uint32_t* m_indices2;
private:

	int getindex(const float& x, const float& z);
	float getheight_first(uint32_t x, uint32_t z);
	float WIDTH = 12.0f;
	float HEIGHT = 12.0f;
	float DX = WIDTH / 2;
	float DZ = HEIGHT / 2;
	float yScale = 32.0f / 256.0f, yShift = 0.0f;


	VertexMesh* gridmesh;
	uint32_t* m_indices;

	std::shared_ptr<VertexArray>  m_VAOT;
	std::shared_ptr<VertexBuffer> m_VBOT;
	std::shared_ptr<IndexBuffer>  m_IBOT;
	std::shared_ptr<Shader> myshaderT;
	unsigned char* data;
	int m_nChannels;
};