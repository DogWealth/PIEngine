#include "pipch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>
namespace PIEngine {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case PIEngine::ShaderDataType::None:	return GL_FLOAT;
		case PIEngine::ShaderDataType::Float:	return GL_FLOAT;
		case PIEngine::ShaderDataType::Float2:	return GL_FLOAT;
		case PIEngine::ShaderDataType::Float3:	return GL_FLOAT;
		case PIEngine::ShaderDataType::Float4:	return GL_FLOAT;
		case PIEngine::ShaderDataType::Mat3:	return GL_FLOAT;
		case PIEngine::ShaderDataType::Mat4:	return GL_FLOAT;
		case PIEngine::ShaderDataType::Int:		return GL_INT;
		case PIEngine::ShaderDataType::Int3:	return GL_INT;
		case PIEngine::ShaderDataType::Int4:	return GL_INT;
		case PIEngine::ShaderDataType::Bool:	return GL_BOOL;
		}

		PI_CORE_ASSERT(false, "Unkonwn ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> vertexBuffer)
	{
		PI_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
		
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();


		for (const auto& element : vertexBuffer->GetLayout()) //返回的layout是const属性，调用begin()和end()也要是const限定
		{
			static uint32_t index = 0;
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(ShaderDataType::Float3),
				element.Normalized ? GL_TRUE : GL_FALSE,
				vertexBuffer->GetLayout().GetStride(),
				(const void*)element.Offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}