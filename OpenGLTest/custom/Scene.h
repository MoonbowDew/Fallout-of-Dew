#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../VertexBuffer.h"
#include "../VertexBufferLayout.h"
#include "../Texture.h"
#include "../custom/GameObject.h"
#include "../custom/Background.h"
#include "../custom/FrameBuffer.h"

#include <memory>
#include <map>
#include <iostream>

	struct VecPosition
	{
		float x;
		float y;
		float z;
		//float w;
	
	};
	
	struct VecColor
	{
		float r;
		float g;
		float b;
		float a;
	};
	
	struct VecTexCoord
	{
		float x;
		float y;
	};
	
	
	struct Vertex
	{
		VecPosition position;
		VecColor color;
		VecTexCoord texCoord;
		float texID;
	};

	class Scene 
	{
	public:
		Scene();
		~Scene();

		void OnUpdate(GLFWwindow* window, float deltaTime);
		void OnRender(GLFWwindow* window);
		std::array<Vertex, 4> CreateObject(glm::vec2 BottomLeft, glm::vec2 BottomRight, glm::vec2 TopRight, glm::vec2 TopLeft, float angle, float texID, float r, float g, float b, float alpha);
		void FillVBO(std::vector<std::shared_ptr <GameObject>> GameObjectsArray, Vertex* arr);
		
	private:
		glm::mat4 m_Proj, m_View;
		glm::mat4 m_VP;

		TextureData RD1TXData, RustyBarTXData, FloorTXData, /*BGImageTXData,*/ netTXData, mouseCursorTXData, blackVeilTXData, FogBlocksTXData, BGBlocksTXData, RustyPipeTXData, metalSupBlocksTXData;
		//GameObject * RustyBar, * Floor, *BGImage,* net, * mouseCursor, * blackVeil;

		std::shared_ptr <GameObject> RD1, mouseCursor, blackVeil;
		std::shared_ptr <GameObject> RustyBar, Floor, RustyPipe;

		double starttime, endtime, delta;

		std::vector<std::shared_ptr <GameObject>> FogBlocks;
		std::vector<std::shared_ptr <GameObject>> BGBlocks;
		std::vector<std::shared_ptr <GameObject>> netBlocks;
		std::vector<std::shared_ptr <GameObject>> metalSupBlocks;
		std::vector<std::shared_ptr <GameObject>> floorAndSeilingBlocks;

		std::vector<std::shared_ptr <GameObject>> GameObjectsArray;

		std::vector<std::shared_ptr <GameObject>> collideObjs;
		std::unique_ptr <Shader> m_Shader;
		std::unique_ptr <Shader> m_ShaderFB;

		//std::unique_ptr <IndexBuffer> m_IndexBuffer;
		//std::unique_ptr <Shader> m_Shader_Instances;
		//std::unique_ptr <Shader> m_Shader_Instances_net;
		//std::unique_ptr <FrameBuffer> FramebufferBlack;
	};