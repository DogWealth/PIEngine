#include<PIEngine.h>
#include "imgui/imgui.h"

class ExampleLayer : public PIEngine::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.28f, 1.28f, -0.72f, 0.72f), m_CameraPosition(0.f, 0.f, 0.f)
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

			void main()
			{
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			void main()
			{
				color = vec4(0.8, 0.2, 0.3, 1.0);
			}
		)";

		m_Shader.reset(new PIEngine::Shader(vertexSrc, fragmentSrc));
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


		PIEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		PIEngine::RenderCommand::Clear();

		m_Camera.SetRotation(m_CameraRotation);
		m_Camera.SetPosition(m_CameraPosition);


		PIEngine::Renderer::BeginScene(m_Camera);

		PIEngine::Renderer::Submit(m_VertexArray, m_Shader);

		PIEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
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
	float m_CameraRotationSpeed = 15.f;
	
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
