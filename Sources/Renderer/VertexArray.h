#pragma once
#include "Sources/KingdomEngine.h"
#include "Buffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer, bool isInstanced = false);
	void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
	uint32_t GetInstancedCount() { return m_InstancedCount; }

	const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
	const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
private:
	uint32_t m_RendererID;
	uint32_t m_VertexBufferIndex = 0;
	std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;

	uint32_t m_InstancedCount = 0;
};


