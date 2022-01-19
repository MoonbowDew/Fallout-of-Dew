#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <memory>
#include "../Texture.h"
#include "../VertexBufferLayout.h"
#include "UVBuffer.h"

#include <string>
#include <iostream>
#include <sstream>

#include "../stb_image.h"

#define _USE_MATH_DEFINES
#include <math.h>



struct TextureData
{
	unsigned int textureID;
	int textureWidth;
	int textureHeight;
};

class GameObject
{
public:
	GameObject(glm::vec3 SpawnPoint, TextureData TXData, float TXNumber, float r = 1.0f, float g = 1.0f, float b = 1.0f, float alpha = 1.0f, float angle = 0.0f);
	glm::vec3 GetCurrentPosition();
	void SetCurrentPosition(glm::vec3 xPos);
	int GetXLength();
	int GetYLength();
	double GetYVelocity();

	int GetXBorder();
	int GetYBorder();


	void SetXPosition(float xPos);
	void SetYPosition(float yPos);
	void SetYVelocity(double yVel);

	//void LoadFrames(const char* filename);
	//void PlayFrames(Texture& spritetexture, VertexArray& rectangle, double deltatime);

	void Jump();
	void ChangeSize(float x, float y);

	void SetAlphaChannel(float alpha);

	void SetRotationAngle(float angle);

	void MoveLeft(float xPos);

	void MoveRight(float xPos);

	void SetSpriteResolution(float x, float y);

	void PrintCoords();

	void MoveUp(float yPos);

	inline unsigned int GetTextureID() { return m_textureID; }

	inline float GetAlphaChannel() { return m_alpha_channel; }
	inline float GetX() { return BottomLeft.x; }
	inline float GetY() { return BottomLeft.y; }
	inline float GetColorR() { return m_r; }
	inline float GetColorG() { return m_g; }
	inline float GetColorB() { return m_b; }
	inline float GetTXNumber() { return m_TXNumber; }
	inline float GetRotationAngle() { return m_rotation_angle; }

	inline glm::vec2 GetBottomLeft() { return BottomLeft; }
	inline glm::vec2 GetBottomRight() { return BottomRight; }
	inline glm::vec2 GetTopRight() { return TopRight; }
	inline glm::vec2 GetTopLeft() { return TopLeft; }
	inline float GetWidth() { return width; }
	inline float GetHeight() { return height; }
	
private:
	glm::vec3 m_SpawnPoint;
	glm::vec2 BottomLeft, BottomRight, TopRight, TopLeft;
	float width, height;

	//glm::vec4 m_Quat; // Quaterion

	unsigned int m_textureID;


	double m_YVelocity;



	//int m_XLength; // pixels
	//int m_YLength; // pixels
	//float m_borderX;
	//float m_borderY;
	float m_TXNumber;
	float m_r, m_g, m_b, m_alpha_channel;
	float m_rotation_angle;

	

	static int counter; // shows how many objs were created

	//for PlayFrames purposes
	//double anim_cursor = 0;
	//int current_frame_indx = 0;
	//int frames_count;
	//float speed = 0.005f;
	//std::vector<glm::vec4> frames;



};