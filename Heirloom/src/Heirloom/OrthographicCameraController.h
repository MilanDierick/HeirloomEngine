#pragma once
#include "Core/Timestep.h"
#include "Heirloom/Events/ApplicationEvent.h"
#include "Heirloom/Events/Event.h"
#include "Heirloom/Events/MouseEvent.h"
#include "Heirloom/Renderer/OrthographicCamera.h"

namespace Heirloom
{
	class OrthographicCameraController
	{
	public:
		explicit OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(const float zoomLevel) { m_ZoomLevel = zoomLevel; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition     = {0.0f, 0.0f, 0.0f};
		float m_CameraRotation         = 0.0f;
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};
}
