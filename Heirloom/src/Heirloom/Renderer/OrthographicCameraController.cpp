#include "hlpch.h"
#include "OrthographicCameraController.h"
#include "Heirloom/Core/Application.h"
#include "Heirloom/Core/Input.h"
#include "Heirloom/Core/KeyCodes.h"

Heirloom::OrthographicCameraController::OrthographicCameraController(const float aspectRatio, const bool rotation)
	: m_AspectRatio(aspectRatio),
	  m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
	  m_Rotation(rotation)
{
	Input::MouseScrolledEvent += HL_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolledEvent);
	Application::Get().GetWindow().WindowResizedEvent += HL_BIND_EVENT_FN(OrthographicCameraController::OnWindowResizedEvent);
}

void Heirloom::OrthographicCameraController::OnUpdate(const Timestep ts)
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

void Heirloom::OrthographicCameraController::OnMouseScrolledEvent(const MouseScrolledEventArgs eventArgs)
{
	m_ZoomLevel -= eventArgs.YOffset * 0.25f;
	m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
}

void Heirloom::OrthographicCameraController::OnWindowResizedEvent(const WindowResizedEventArgs eventArgs)
{
	m_AspectRatio = static_cast<float>(eventArgs.Width) / static_cast<float>(eventArgs.Height);
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
}
