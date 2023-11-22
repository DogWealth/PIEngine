#include "pipch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace PIEngine {
	Renderer::SceneData* Renderer::m_SceneData = new SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4 transform)
	{
		shader->Bind();
		auto openglShader = std::dynamic_pointer_cast<OpenGLShader>(shader);
		openglShader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		openglShader->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);

	}

}