#pragma once
#include "PIEngine/Renderer/OrthographicCamera.h"
#include "PIEngine/Core/Timestep.h"

#include "PIEngine/Events/ApplicationEvent.h"
#include "PIEngine/Events/MouseEvent.h"

namespace PIEngine
{
	class OrthographicCamera;
	class Timestep;

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		void SetZoomLevel(float level) { m_ZoomLevel = level; }
		float GetZoomLevel() const { return m_ZoomLevel; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation = false;

		glm::vec3 m_CameraPosition = { 0.f, 0.f, 0.f };
		float m_CameraRotation = 0.f;

		float m_CameraTranslationSpeed = 1.f;
		float m_CameraRotationSpeed = 150.f;
	};
}

