#include "RendererAPI.h"

#include <glad/glad.h>

	std::unique_ptr<RendererAPI> RendererAPI::s_Instance = std::make_unique<RendererAPI>();
	std::unique_ptr<RendererAPI::UserData> RendererAPI::s_UserData = std::make_unique<UserData>();

	void MessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:         KGLOG(message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       KGLOG(message); return;
			case GL_DEBUG_SEVERITY_LOW:          KGLOG(message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: KGLOG(message); return;
		}
		
		KGLOG(false, "Unknown severity level!");
	}

	void RendererAPI::Init()
	{

	#ifdef HZ_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(MessageCallback, nullptr);
		
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
	#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);
		// Wireframe mode
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
	}

	void RendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void RendererAPI::BeginScene(PerspectiveCamera& camera)
	{
		s_UserData->ViewProj = camera.GetViewProjectionMatrix();
	}



	void RendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void RendererAPI::SetClearColor()
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	}


	void RendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RendererAPI::DrawPoints(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, uint32_t vertexCount)
	{
		shader->use();
		shader->setMat4("u_view_projection", s_UserData->ViewProj);
		vertexArray->Bind();
		glDrawArrays(GL_POINTS, 0, vertexCount);
	}

	void RendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount)
	{
		vertexArray->Bind();
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);

	}

	void RendererAPI::DrawLines(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, uint32_t vertexCount)
	{
		shader->use();
		shader->setMat4("u_view_projection", s_UserData->ViewProj);
		vertexArray->Bind();
		glDrawArrays(GL_LINES, 0, vertexCount);
	}

	void RendererAPI::DrawTriangles(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, uint32_t vertexCount)
	{
		shader->use();
		shader->setMat4("u_view_projection", s_UserData->ViewProj);
		vertexArray->Bind();
		glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	}

	void RendererAPI::DrawArraysInstanced(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, uint32_t vertexCount)
	{
		// ONLY FOR PATCHES OF 4
		shader->use();
		shader->setMat4("u_view_projection", s_UserData->ViewProj);
		vertexArray->Bind();
		glDrawArraysInstanced(GL_PATCHES, 0, 4, vertexCount);
	}

	void RendererAPI::DrawElementsInstanced(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount)
	{
		vertexArray->Bind();
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElementsInstanced(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0, vertexArray->GetInstancedCount());
	}

	void RendererAPI::SetLineWidth(float width)
	{
		glLineWidth(width);
	}

	void RendererAPI::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount)
	{
		shader->use();
		shader->setMat4("u_view_projection", s_UserData->ViewProj);
		DrawElementsInstanced(vertexArray);
	}

	void RendererAPI::SubmitElements(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount)
	{
		shader->use();
		shader->setMat4("u_view_projection", s_UserData->ViewProj);
		DrawIndexed(vertexArray);
	}
