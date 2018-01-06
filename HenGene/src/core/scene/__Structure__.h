
#pragma once

class Pipeline
{
	render();
	renderScene(renderPass);
};

class Scene
{
	// Logic
	struct Entity;			// Groups data into one unit
	
	struct Component;		// Stores a collection of data

	template<typename ...Components>
	class System;			// Processes data in form of components

	// Render
	class Camera;

	enum RenderPass;

	template<typename ...Components>
	struct Node;			// Renders a specific component

	struct Layer;			// Stores a collection of nodes
};




struct ComponentPosition
{
	World * m_world;
	LengthVec m_pos;
};
struct ComponentMovement
{
	SpeedVec m_vel;
	AccelerationVec m_acc;
};
struct ComponentWorld		// One system can process this component, and one renderer can render it
{
	std::string m_name;
};