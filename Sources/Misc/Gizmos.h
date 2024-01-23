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

class Gizmos {
public:
	struct display_opts {
		bool gizmo = true;
		bool basegrid = true;
		glm::vec3 m_gridcolor = glm::vec3(0.3f);
	} m_display;

public:
	Gizmos();
	~Gizmos();

	void RenderAll();
	void RenderGrid();
	void RenderGizmo();
	
	void RefreshGridColor();
private:
	

	std::shared_ptr<VertexArray>  m_VAO[2];
	std::shared_ptr<VertexBuffer> m_VBO[2];
	std::shared_ptr<IndexBuffer>  m_IBO[2];
	std::shared_ptr<Shader> m_shader[2];


};