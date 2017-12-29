
#include "EventQueue.h"

#include "logic/event/Events.h"

#include <allegro5/display.h>
#include <plog/Log.h>
#include <unordered_set>

namespace
{
	std::unordered_set<ALLEGRO_EVENT_SOURCE*> sources;

	auto convert(unsigned int mouseButton)
	{
		using ui::mouse::Button;
		static const Button AL_TO_HEN[] = { Button::LEFT, Button::RIGHT, Button::MIDDLE, Button::MIDDLE };
		return mouseButton < 4u ? AL_TO_HEN[mouseButton] : Button::NONE;
	}
}

logic::event::EventQueue::EventQueue()
{
	m_handle = al_create_event_queue();
}
logic::event::EventQueue::~EventQueue()
{
	if (m_handle != nullptr)
		al_destroy_event_queue(m_handle);
}

void logic::event::EventQueue::update(const EventBus & bus)
{
	ALLEGRO_EVENT event;
	while (al_get_next_event(m_handle, &event))
	{
		switch (event.type)
		{
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			bus.post(DisplayClose{});
			break;
		case ALLEGRO_EVENT_DISPLAY_RESIZE:
			al_acknowledge_resize(event.display.source);
			bus.post(DisplayResize{ { event.display.width, event.display.height } });
			break;
		case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
			bus.post(DisplaySwitchOut{});
			break;
		case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
			bus.post(DisplaySwitchIn{});
			break;

		case ALLEGRO_EVENT_KEY_DOWN:
			bus.post(KeyPress{ event.keyboard.keycode, event.keyboard.modifiers });
			break;
		case ALLEGRO_EVENT_KEY_UP:
			bus.post(KeyRelease{ event.keyboard.keycode, event.keyboard.modifiers });
			break;
		case ALLEGRO_EVENT_KEY_CHAR:
			bus.post(KeyRelease{ event.keyboard.unichar, event.keyboard.modifiers });
			break;

		case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
			bus.post(MouseEnterDisplay{});
			break;
		case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
			bus.post(MouseLeaveDisplay{});
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			bus.post(MousePress{
				convert(event.mouse.button), event.mouse.pressure,
				{ event.mouse.x, event.mouse.y }, { event.mouse.z, event.mouse.w }
			});
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			bus.post(MouseRelease{
				convert(event.mouse.button), event.mouse.pressure,
				{ event.mouse.x, event.mouse.y }, { event.mouse.z, event.mouse.w }
			});
			break;
		case ALLEGRO_EVENT_MOUSE_AXES:
			bus.post(MouseMove{
				{ event.mouse.x, event.mouse.y }, { event.mouse.z, event.mouse.w },
				{ event.mouse.dx, event.mouse.dy }, { event.mouse.dz, event.mouse.dw }
			});
			break;
		case ALLEGRO_EVENT_MOUSE_WARPED:
			break;

		case ALLEGRO_EVENT_TIMER:
			break;

		default:
			LOG_WARNING << "Unhandled Allegro event type detected: " << event.type;
		}
	}
}

bool logic::event::EventQueue::add(ALLEGRO_EVENT_SOURCE * source)
{
	if (m_handle == nullptr || source == nullptr)
		return false;
	if (sources.find(source) != sources.end())
	{
		LOG_WARNING << "Attempted to add an event source which has already been added";
		return false;
	}

	al_register_event_source(m_handle, source);
	sources.emplace(source);
	return true;
}
bool logic::event::EventQueue::remove(ALLEGRO_EVENT_SOURCE * source)
{
	if (m_handle == nullptr || source == nullptr || sources.find(source) == sources.end())
		return false;

	al_unregister_event_source(m_handle, source);
	sources.erase(source);
	return true;
}
