
#pragma once

#include "asset/AssetRef.h"
#include "render/allegro/Sprite.h"
#include "ui/Mouse.h"

#include <functional>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <string>
#include <unordered_set>
#include <unordered_map>

namespace ui
{
	namespace gui
	{
		// Stores the generic widget data
		struct Header
		{
			std::string m_name;
		};
		// Stores what the widget will be doing every tick
		struct Logic
		{
			std::function<void(const glm::vec2 &)> m_process;
		};
		// Stores how the widget will be rendered to the screen
		struct Render
		{
			std::function<void(const glm::vec2 &)> m_render;
			glm::vec2 m_offset;
			bool m_visible = true;
		};

		// Stores the relative position between the parent and child widget
		struct Position
		{
			bool m_automatic = true;	// If true, position will be automatically updated
			glm::vec2 m_pos{};
		};
		// Stores the size of the widget, as well as size limits
		struct Size
		{
			bool m_automatic = true;	// If true, size will be automatically updated
			glm::vec2 m_size{};
			glm::vec2 m_minSize{ 0.0f };
			glm::vec2 m_maxSize{ std::numeric_limits<float>::max() };
		};

		// Stores the relations between widgets
		struct Family
		{
			std::string m_parent;
			std::unordered_set<std::string> m_children;
		};
		// Stores the dynamics between widgets
		struct Group
		{
			std::string m_leader;
			std::unordered_set<std::string> m_members;
		};

		// Stores a link to another widget, forcing the widgets together
		// Links may only be formed directly between parents and children, or directly among siblings
		struct Link
		{
			enum class Location
			{
				TOP_LEFT, TOP, TOP_RIGHT,
				LEFT_TOP, RIGHT_TOP,
				LEFT, CENTER, RIGHT,
				LEFT_BOTTOM, RIGHT_BOTTOM,
				BOTTOM_LEFT, BOTTOM, BOTTOM_RIGHT
			};

			std::string m_target;
			Location m_location = Location::TOP_LEFT;
		};
		// Stores the padding between widget links
		struct Border
		{
			glm::vec4 m_inner{}; // format: left, right, top, bottom
			glm::vec4 m_outer{}; // format: left, right, top, bottom
		};

		// Stores assets the widget may need
		struct Assets
		{
			template<typename Asset> using AssetMap = std::unordered_map<std::string, Asset>;

			AssetMap<std::string> m_scripts;
			AssetMap<asset::Ref<render::allegro::Sprite>> m_sprites;
		};

		// Stores the current state of the widget
		struct State
		{
			bool m_bool = false;
			float m_float = 0.0f;
			std::string m_string;
		};
		// Stores the current activation states
		struct Activation
		{
			bool m_locked = false;	// If true, user may not interact with widget
			bool m_hovered = false;	// If true, user hovers mouse over widget
			int m_key = -1;			// The keyboard button required to activate widget (button id)
			int m_mask = 0;			// The keyboard modifiers required to activate widget (bitfield)
			mouse::Button m_button = mouse::Button::NONE;
		};
	}
}