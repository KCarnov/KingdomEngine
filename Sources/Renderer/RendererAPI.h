#pragma once
#include <glm/glm.hpp>
#include "VertexArray.h"
#include "Sources/KingdomEngine.h"
#include "Sources/Renderer/Shader.h"
#include "Sources/Renderer/PerspectiveCamera.h"
class RendererAPI 
{
public:
	static void Init();
	static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

	static void BeginScene(PerspectiveCamera& camera);
	
	static void SetClearColor(const glm::vec4& color);
	static void SetClearColor();
	static void Clear();

	static void DrawPoints(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, uint32_t vertexCount);
	static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount = 0);
	static void DrawLines(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, uint32_t vertexCount);
	static void DrawTriangles(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, uint32_t vertexCount);
	static void DrawArraysInstanced(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, uint32_t vertexCount);

	static void DrawElementsInstanced(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount = 0);
	static void SetLineWidth(float width);

	static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount = 0);
	static void SubmitElements(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount);
	static std::unique_ptr<RendererAPI> s_Instance;

	struct UserData {
		glm::mat4 ViewProj;
	};

	static std::unique_ptr<UserData> s_UserData;
};



