#include "Sandbox2D.h"

#include "Heirloom/Profiler/Instrumentation.h"

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(640.0f / 480.0f, false) { }

void Sandbox2D::OnAttach()
{
	HL_PROFILE_FUNCTION()

	m_BackgroundTexture = Heirloom::Texture2D::Create("assets/textures/Checkerboard.png");
	m_Logo              = Heirloom::Texture2D::Create("assets/textures/logo.png");
}

void Sandbox2D::OnDetach() {}

void Sandbox2D::OnUpdate(const Heirloom::Timestep ts)
{
	HL_PROFILE_FUNCTION()

	m_CameraController.Update(ts);

	Heirloom::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
	Heirloom::RenderCommand::Clear();

	Heirloom::Renderer2D::BeginScene(m_CameraController.GetCamera());

	// Heirloom::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, m_SquareColor);
	// Heirloom::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, m_SquareColor);
	Heirloom::Renderer2D::DrawRotatedQuad({0.0f, 0.0f, -0.1f}, {5.0f, 5.0f}, glm::radians(45.0f), m_BackgroundTexture, 10.0f, {1.0f, 0.9f, 0.9f, 1.0f});
	Heirloom::Renderer2D::DrawQuad({0.0f, 0.8f}, {1.0f, 1.0f}, m_Logo);

	Heirloom::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	HL_PROFILE_FUNCTION()

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", value_ptr(m_SquareColor));
	ImGui::End();

	ImGui::SetNextWindowPos(ImVec2(10, 10));
	ImGui::Begin("main", nullptr,
	             ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SetWindowFontScale(2.0);
	ImGui::Text("%.0f FPS", ImGui::GetIO().Framerate);
	ImGui::End();
}
