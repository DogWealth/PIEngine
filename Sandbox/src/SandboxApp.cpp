#include<PIEngine.h>
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public PIEngine::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.28f, 1.28f, -0.72f, 0.72f), m_CameraPosition(0.f, 0.f, 0.f), m_SquarePosition(0.f)
	{
		//vertex array
		m_VertexArray.reset(PIEngine::VertexArray::Create());
		//vertex buffer
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f,
		};
		std::shared_ptr<PIEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(PIEngine::VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			PIEngine::BufferLayout layout = {
			{PIEngine::ShaderDataType::Float3, "a_Position"}
			};

			vertexBuffer->SetLayout(layout);
		}
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		//index buffer
		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<PIEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(PIEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_Shader.reset(PIEngine::Shader::Create(vertexSrc, fragmentSrc));
	}

	void OnUpdate(PIEngine::Timestep timestep) override
	{
		PI_TRACE("Delta Time: {0}s, {1}ms", timestep.GetSeconds(), timestep.GetMilliseconds());

		if (PIEngine::Input::IsKeyPressed(PI_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * timestep;

		if (PIEngine::Input::IsKeyPressed(PI_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * timestep;

		if (PIEngine::Input::IsKeyPressed(PI_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * timestep;

		if (PIEngine::Input::IsKeyPressed(PI_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * timestep;

		if (PIEngine::Input::IsKeyPressed(PI_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * timestep;

		if (PIEngine::Input::IsKeyPressed(PI_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * timestep;
		/************************************************/
		if (PIEngine::Input::IsKeyPressed(PI_KEY_J))
			m_SquarePosition.x -= m_SquareMoveSpeed * timestep;

		if (PIEngine::Input::IsKeyPressed(PI_KEY_L))
			m_SquarePosition.x += m_SquareMoveSpeed * timestep;

		if (PIEngine::Input::IsKeyPressed(PI_KEY_I))
			m_SquarePosition.y -= m_SquareMoveSpeed * timestep;

		if (PIEngine::Input::IsKeyPressed(PI_KEY_K))
			m_SquarePosition.y += m_SquareMoveSpeed * timestep;


		PIEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		PIEngine::RenderCommand::Clear();

		m_Camera.SetRotation(m_CameraRotation);
		m_Camera.SetPosition(m_CameraPosition);


		PIEngine::Renderer::BeginScene(m_Camera);

		glm::mat4 transform = glm::translate(glm::mat4(1.f), m_SquarePosition);
		glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(0.2f));

		std::dynamic_pointer_cast<PIEngine::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int i = -1; i < 2; i++)
		{
			glm::vec3 pos(i * 0.5f, 0.0f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.f), pos) * scale;

			PIEngine::Renderer::Submit(m_VertexArray, m_Shader, transform);
		}

		PIEngine::Renderer::Submit(m_VertexArray, m_Shader, transform);

		PIEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(PIEngine::Event& event) override
	{
	}


private:
	std::shared_ptr<PIEngine::Shader> m_Shader;
	std::shared_ptr<PIEngine::VertexArray> m_VertexArray;

	PIEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.f;

	float m_CameraMoveSpeed = 1.f;
	float m_CameraRotationSpeed = 150.f;

	glm::vec3 m_SquarePosition;
	float m_SquareMoveSpeed = 1.f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.4f };
	
};

class Sandbox : public PIEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

PIEngine::Application* PIEngine::CreatApplication()
{
	return new Sandbox();
}
