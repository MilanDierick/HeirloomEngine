#include "hlpch.h"
#include "OrthographicCameraController.h"

#include "Heirloom/Input.h"
#include "Heirloom/KeyCodes.h"

Heirloom::OrthographicCameraController::OrthographicCameraController(const float aspectRatio, const bool rotation)
	: m_AspectRatio(aspectRatio),
	  m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
	  m_Rotation(rotation) { }

void Heirloom::OrthographicCameraController::OnUpdate(Timestep ts)
{
	if (Input::IsKeyPressed(HL_KEY_A))
		m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
	else if (Input::IsKeyPressed(HL_KEY_D))
		m_CameraPosition.x += m_CameraTranslationSpeed * ts;

	if (Input::IsKeyPressed(HL_KEY_W))
		m_CameraPosition.y += m_CameraTranslationSpeed * ts;
	else if (Input::IsKeyPressed(HL_KEY_S))
		m_CameraPosition.y -= m_CameraTranslationSpeed * ts;

	if (m_Rotation)
	{
		if (Input::IsKeyPressed(HL_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Input::IsKeyPressed(HL_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		m_Camera.SetRotation(m_CameraRotation);
	}

	m_Camera.SetPosition(m_CameraPosition);

	m_CameraTranslationSpeed = m_ZoomLevel;
}

void Heirloom::OrthographicCameraController::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseScrolledEvent>(HL_BIND_EVENT_FN(Heirloom::OrthographicCameraController::OnMouseScrolled));
	dispatcher.Dispatch<WindowResizeEvent>(HL_BIND_EVENT_FN(Heirloom::OrthographicCameraController::OnWindowResized));
}

bool Heirloom::OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
{
	m_ZoomLevel -= e.GetYOffset() * 0.25f;
	m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return false;
}

bool Heirloom::OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
{
	m_AspectRatio = static_cast<float>(e.GetWidth()) / static_cast<float>(e.GetHeight());
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return false;
}