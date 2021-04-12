// Author: Milan Dierick
// Created: 02/03/2021 8:27 PM
// Solution: HeirloomEngine

#pragma once
#include <functional>
#include <array>

#define HL_MAX_EVENT_LISTENERS 32

struct HL_API EventArgs
{
};

template <typename EventArgsType = EventArgs, typename EventCallbackFunc = std::function<void(EventArgsType)>>
class HL_API EventNew
{
public:
	EventNew<EventArgsType, EventCallbackFunc>& operator+=(EventCallbackFunc eventCallbackFunc);

	void Invoke(EventArgsType eventArgs);

private:
	std::array<EventCallbackFunc, HL_MAX_EVENT_LISTENERS> m_EventListeners = {};
	size_t m_EventListenerCount                                            = 0;
};

template <typename EventArgsType, typename EventCallbackFunc>
EventNew<EventArgsType, EventCallbackFunc>& EventNew<EventArgsType, EventCallbackFunc>::operator+=(
	EventCallbackFunc eventCallbackFunc)
{
	HL_CORE_ASSERT(m_EventListenerCount + 1 < HL_MAX_EVENT_LISTENERS,
				   "Failed registering an event listener, only {0} listeners per event are supported!",
				   HL_MAX_EVENT_LISTENERS);

	m_EventListeners[m_EventListenerCount] = eventCallbackFunc;
	++m_EventListenerCount;

	return *this;
}

template <typename EventArgsType, typename EventCallbackFunc>
void EventNew<EventArgsType, EventCallbackFunc>::Invoke(EventArgsType eventArgs)
{
	for (size_t index = 0; index < m_EventListenerCount; ++index) m_EventListeners[index](eventArgs);
}
