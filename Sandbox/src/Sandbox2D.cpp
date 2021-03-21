#include "Sandbox2D.h"

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true) { }

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = Heirloom::Texture2D::Create("assets/textures/Checkerboard.png");
	m_Logo = Heirloom::Texture2D::Create("assets/textures/logo.png");
}

void Sandbox2D::OnDetach() {}

void Sandbox2D::OnUpdate(const Heirloom::Timestep ts)
{
	m_CameraController.Update(ts);
	
	Heirloom::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
	Heirloom::RenderCommand::Clear();

	Heirloom::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Heirloom::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, m_SquareColor);
	Heirloom::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, m_SquareColor);
	Heirloom::Renderer2D::DrawQuad({0.2f, 0.5f, -0.1f}, {10.0f, 10.0f}, m_CheckerboardTexture);
	Heirloom::Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f}, m_Logo);

	Heirloom::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
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
