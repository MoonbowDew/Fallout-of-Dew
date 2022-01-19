#pragma once
#include "GameObject.h"



	GameObject::GameObject(glm::vec3 SpawnPoint, /*const void* VertexData,*/ TextureData TXData, float TXNumber, float r, float g, float b, float alpha, float angle)
		: m_SpawnPoint(SpawnPoint), BottomLeft(SpawnPoint.x, SpawnPoint.y), BottomRight(SpawnPoint.x + TXData.textureWidth, SpawnPoint.y),
		TopRight(SpawnPoint.x + TXData.textureWidth, SpawnPoint.y + TXData.textureHeight), TopLeft(SpawnPoint.x, SpawnPoint.y + TXData.textureHeight), width (BottomRight.x - BottomLeft.x), height(TopLeft.y - BottomLeft.y), m_textureID(TXData.textureID), m_YVelocity(0),
		m_TXNumber(TXNumber),
		m_r(r), m_g(g), m_b(b), m_alpha_channel(alpha), m_rotation_angle(angle)
	{
		//std::cout << "Object " << counter++ << " is created" << std::endl;

	}

	int GameObject::counter = 0;

	glm::vec3 GameObject::GetCurrentPosition()
	{
		return glm::vec3(BottomLeft, 0.0f);
	}	

	void GameObject::SetCurrentPosition(glm::vec3 newVec3)
	{
		BottomLeft.x = newVec3.x;
		BottomLeft.y = newVec3.y;
	}

	void GameObject::PrintCoords()
	{
		std::cout << "BottomLeft: " << BottomLeft.x << " " << BottomLeft.y << "\n"
			<< "BottomRight: " << BottomRight.x << " " << BottomRight.y << "\n"
			<< "TopRight: " << TopRight.x << " " << TopRight.y << "\n"
			<< "TopLeft: " << TopLeft.x << " " << TopLeft.y << "\n"
			<< "Width: " << width << " "  << "\n"
			<< "Height: " << height << " " << "\n\n";
	}

	int GameObject::GetXLength()
	{
		return BottomRight.x - BottomLeft.x;
	}

	int GameObject::GetYLength()
	{
		return TopLeft.y - BottomLeft.y;
	}

	int GameObject::GetXBorder()
	{
		return BottomRight.x - BottomLeft.x;
	}

	int GameObject::GetYBorder()
	{
		return TopLeft.y - BottomLeft.y;
	}

	void GameObject::MoveLeft(float xPos)
	{
		BottomLeft.x -= xPos;
		BottomRight.x -= xPos;
		TopRight.x -= xPos;
		TopLeft.x -= xPos;
	}

	void GameObject::MoveRight(float xPos)
	{
		BottomLeft.x += xPos;
		BottomRight.x += xPos;
		TopRight.x += xPos;
		TopLeft.x += xPos;
	}

	void GameObject::MoveUp(float yPos)
	{
		BottomLeft.y += yPos;
		BottomRight.y += yPos;
		TopRight.y += yPos;
		TopLeft.y += yPos;
	}

	void GameObject::SetSpriteResolution(float x, float y) // fixed 6/29/2021 8:12 pm
	{
		float widthTmp = x / width;
		float heightTmp = y / height;
		width = width * widthTmp;
		height = height * heightTmp;
		//BottomLeft.x *= ratioX;
		BottomRight.x = BottomLeft.x + width;
		TopRight.x = BottomLeft.x + width;
		//TopLeft.x = widthTmp;

		//BottomLeft.y *= ratioY;
		//BottomRight.y = BottomLeft.y;
		TopRight.y = BottomLeft.y + height;
		TopLeft.y = BottomLeft.y + height;
	}



	void GameObject::SetXPosition(float xPos)// fixed 6 / 29 / 2021 6:38 pm
	{
		BottomLeft.x = xPos;
		BottomRight.x = xPos + width;
		TopRight.x = xPos + width;
		TopLeft.x = xPos;
	}

	void GameObject::SetYPosition(float yPos) // fixed 6/29/2021 6:39 pm
	{
		BottomLeft.y = yPos;
		BottomRight.y = BottomLeft.y;
		TopRight.y = BottomLeft.y + height;
		TopLeft.y = BottomLeft.y + height;

	}
	
	
	double GameObject::GetYVelocity()
	{
		return m_YVelocity;
	}
	
	void GameObject::SetYVelocity(double yVel)
	{
		m_YVelocity = yVel;
	}
	
	void GameObject::Jump()
	{
		m_YVelocity = 420;
	}

	void GameObject::SetAlphaChannel(float alpha)
	{
		m_alpha_channel = alpha;
	}

	void GameObject::ChangeSize(float x, float y) // fixed 6/29/2021 8:04 pm
	{

		double rads = m_rotation_angle * M_PI / 180;
		double rads90 = (m_rotation_angle+90) * M_PI / 180;
		width = width + x;
		height = height + y;


		BottomRight.x = BottomLeft.x + width * std::cos(rads);
		BottomRight.y = BottomLeft.y + height * std::sin(rads);

		TopLeft.x = BottomLeft.x + width * std::cos(rads90);
		TopLeft.y = BottomLeft.y + height * std::sin(rads90);

		TopRight.x = BottomRight.x + (TopLeft.x - BottomLeft.x); // сложение абсолютных с относительными
		TopRight.y = TopLeft.y + (BottomRight.y - BottomLeft.y);

	}

	void GameObject::SetRotationAngle(float angle) // // fixed 6/30/2021 11:51 am
	{
		m_rotation_angle = angle;
		//this->PrintCoords();
		glm::vec2 ElementCenter((std::abs(TopLeft.x) + std::abs(BottomRight.x)) / 2,
			( std::abs(TopRight.y) + std::abs(BottomLeft.y) ) / 2); // центр квадрата при любом повороте
		//float widthTmp = std::sqrt(std::pow((BottomRight.x - BottomLeft.x), 2.0) + std::pow((BottomRight.y - BottomLeft.y), 2.0));
		//float heightTmp = widthTmp;
		//coords before rotation:
		float HalfWidth = width / 2;
		float HalfHeight = height / 2;
		glm::vec2 BottomLeftNoRotaion(ElementCenter.x - HalfWidth, ElementCenter.y - HalfHeight);
		glm::vec2 BottomRightNoRotaion(ElementCenter.x + HalfWidth, ElementCenter.y - HalfHeight);
		glm::vec2 TopRightNoRotaion(ElementCenter.x + HalfWidth, ElementCenter.y + HalfHeight);
		glm::vec2 TopLeftNoRotaion(ElementCenter.x - HalfWidth, ElementCenter.y + HalfHeight);

		//glm::vec2 PivotPoint(BottomLeft.x - width/2, BottomLeft.y - height/ 2);
		double rads = angle * M_PI / 180;
		// translate to origin
		glm::vec2 BottomLeftInit = glm::vec2(-HalfWidth, -HalfHeight);
		glm::vec2 BottomRightInit = glm::vec2(BottomLeftInit.x + width, BottomLeftInit.y);
		glm::vec2 TopRightInit = glm::vec2(BottomLeftInit.x + width, BottomLeftInit.y + height);
		glm::vec2 TopLeftInit = glm::vec2(BottomLeftInit.x, BottomLeftInit.y + height);

		//rotate
		long tmp1 = BottomLeftInit.x * std::cos(rads) - BottomLeftInit.y * std::sin(rads);
		long tmp2 = BottomLeftInit.x * std::sin(rads) + BottomLeftInit.y * std::cos(rads);

		BottomLeftInit.x = tmp1;
		BottomLeftInit.y = tmp2;

		tmp1 = BottomRightInit.x * std::cos(rads) - BottomRightInit.y * std::sin(rads);
		tmp2 = BottomRightInit.x * std::sin(rads) + BottomRightInit.y * std::cos(rads);

		BottomRightInit.x = tmp1;
		BottomRightInit.y = tmp2;

		tmp1 = TopRightInit.x * std::cos(rads) - TopRightInit.y * std::sin(rads);
		tmp2 = TopRightInit.x * std::sin(rads) + TopRightInit.y * std::cos(rads);

		TopRightInit.x = tmp1;
		TopRightInit.y = tmp2;

		tmp1 = TopLeftInit.x * std::cos(rads) - TopLeftInit.y * std::sin(rads);
		tmp2 = TopLeftInit.x * std::sin(rads) + TopLeftInit.y * std::cos(rads);

		TopLeftInit.x = tmp1;
		TopLeftInit.y = tmp2;



		//BottomLeft = BottomLeftInit;
		//BottomRight = BottomRightInit;
		//TopRight =TopRightInit;
		//TopLeft = TopLeftInit;

		BottomLeft = BottomLeftNoRotaion;
		BottomRight = BottomRightNoRotaion;
		TopRight = TopRightNoRotaion;
		TopLeft = TopLeftNoRotaion;

		//BottomLeft += glm::vec2(std::abs(BottomLeftInit.x) - 50, std::abs(BottomLeftInit.y) - 50);
		//BottomRight += glm::vec2(std::abs(BottomRightInit.x) - 50, std::abs(BottomRightInit.y) - 50);
		//TopRight += glm::vec2(std::abs(TopRightInit.x) - 50, std::abs(TopRightInit.y) - 50);
		//TopLeft += glm::vec2(std::abs(TopLeftInit.x) - 50, std::abs(TopLeftInit.y) - 50);

		//std::cout << "BottomLeft: " << BottomLeft.x << " " << BottomLeft.y << std::endl; // works unless you're using q instead of e
		//std::cout << "BottomRight: " << BottomRight.x << " " << BottomRight.y << std::endl;
		//std::cout << "widthTmp: " << widthTmp << " " << std::endl;
		//std::cout << "heightTmp: " << heightTmp << " " << std::endl;


		BottomLeft += BottomLeftInit + glm::vec2(HalfWidth, HalfHeight);
		BottomRight +=  BottomRightInit + glm::vec2(-HalfWidth, HalfHeight);
		TopRight += TopRightInit + glm::vec2(-HalfWidth, -HalfHeight);
		TopLeft += TopLeftInit + glm::vec2(HalfWidth, -HalfHeight);

		//width = widthTmp;
		//height = heightTmp;
		
		//width = std::abs((BottomRightInit.x - HalfWidth) * 2);
		//height = std::abs((TopRightInit.x - HalfHeight) * 2);


	}

	//void GameObject::LoadFrames(const char* filename)
	//{
	//	FILE* fp = nullptr;
	//	const int bufferlen = 255;
	//	char line[bufferlen];

	//	fopen_s(&fp, filename, "r");

	//	if (fp == nullptr)
	//	{
	//		printf("erorr in reading animation file \n");
	//	}
	//	else
	//	{
	//		while (fgets(line, bufferlen, fp))
	//		{
	//			std::vector<int> result;

	//			std::stringstream ss(line);
	//			std::string token;
	//			while (getline(ss, token, ','))
	//			{
	//				result.push_back(stoi(token));
	//			}

	//			glm::vec4 frame = glm::vec4(result[0], result[1], result[2], result[3]);
	//			frames.push_back(frame);
	//		}
	//	}

	//	frames_count = (int)frames.size();

	//	fclose(fp);
	//}

	//void GameObject::PlayFrames(Texture& spritetexture, VertexArray& rectangle, double deltatime)
	//{
	//	anim_cursor += deltatime;

	//	if (anim_cursor > speed)
	//	{
	//		current_frame_indx = (current_frame_indx + 1) % frames_count;
	//		anim_cursor = 0;
	//	}

	//	glm::vec4 frame = frames[current_frame_indx];

	//	// normalization
	//	frame.x /= spritetexture.GetWidth();
	//	frame.y /= spritetexture.GetHeight();
	//	frame.z /= spritetexture.GetWidth();
	//	frame.w /= spritetexture.GetHeight();

	//	std::vector<glm::vec2> uv;

	//	uv = {
	//		glm::vec2(frame.x,frame.y),
	//		//glm::vec2(frame.x, frame.y + frame.w),
	//		glm::vec2(frame.x + frame.z, frame.y),

	//		//glm::vec2(frame.x + frame.z, frame.y),
	//		glm::vec2(frame.x + frame.z, frame.y + frame.w),
	//		glm::vec2(frame.x, frame.y + frame.w)

	//	};

	//	this->m_VAO->Bind();
	//	this->m_UVBO->Bind();

	//	/*{ //realocation for memory
	//		glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec2), &uv[0], GL_DYNAMIC_DRAW);
	//	}*/


	//	// best practice to send data to gpu memory..
	//	void* gpubuffer = nullptr;
	//	gpubuffer = glMapBufferRange(GL_ARRAY_BUFFER, 0, 4 * sizeof(glm::vec2), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
	//	memcpy(gpubuffer, uv.data(), 4 * sizeof(glm::vec2));
	//	glUnmapBuffer(GL_ARRAY_BUFFER);
	//	this->m_UVBO->Unbind();
	//}

	