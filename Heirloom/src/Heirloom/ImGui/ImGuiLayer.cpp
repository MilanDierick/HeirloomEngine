#include "hlpch.h"
#include "ImGuiLayer.h"

#include "glad/glad.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "GLFW/glfw3.h"
#include "Heirloom/Application.h"
#include "Heirloom/KeyCodes.h"
#include "Platform/Windows/ImGuiGLFWBindings.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Heirloom
{
	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") { }

	ImGuiLayer::~ImGuiLayer() { }

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// TODO: Temporary code, needs to use Heirloom key codes
		io.KeyMap[ImGuiKey_Tab]         = HL_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow]   = HL_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow]  = HL_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow]     = HL_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow]   = HL_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp]      = HL_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown]    = HL_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home]        = HL_KEY_HOME;
		io.KeyMap[ImGuiKey_End]         = HL_KEY_END;
		io.KeyMap[ImGuiKey_Insert]      = HL_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete]      = HL_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace]   = HL_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space]       = HL_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter]       = HL_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape]      = HL_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = HL_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A]           = HL_KEY_A;
		io.KeyMap[ImGuiKey_C]           = HL_KEY_C;
		io.KeyMap[ImGuiKey_V]           = HL_KEY_V;
		io.KeyMap[ImGuiKey_X]           = HL_KEY_X;
		io.KeyMap[ImGuiKey_Y]           = HL_KEY_Y;
		io.KeyMap[ImGuiKey_Z]           = HL_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach() { }

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io      = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize   = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		const float time = static_cast<float>(glfwGetTime());
		io.DeltaTime     = _Mtx_timed > 0.0 ? time - m_Time : 1.0f - 60.0f;
		m_Time           = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(HL_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(HL_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(HL_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(HL_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(HL_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(HL_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(HL_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(HL_BIND_EVENT_FN(ImGuiLayer::OnWindowResizedEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io                      = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io                      = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io                 = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;

		io.KeyCtrl  = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt   = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io                 = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io       = ImGui::GetIO();
		const int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
		{
			io.AddInputCharacter(static_cast<unsigned int>(keycode));
		}

		return false;
	}

	bool ImGuiLayer::OnWindowResizedEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io                = ImGui::GetIO();
		io.DisplaySize             = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}
}
