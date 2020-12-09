#pragma once
#include "Heirloom/Input.h"

namespace Heirloom
{
	class WindowsInput final : public Input
	{
	protected:
		bool IsKeyPressedImpl(int keycode) override;

		bool IsMouseButtonPressedImpl(int button) override;
		std::pair<float, float> GetMousePositionImpl() override;
		bool GetMouseXImpl() override;
		bool GetMouseYImpl() override;
	};
}
