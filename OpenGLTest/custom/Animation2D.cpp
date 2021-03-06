#include "Animation2D.h"
#include "../VertexArray.h"

#include <string>
#include <sstream>

#include <GL/glew.h>

Animation2D::Animation2D(const char* filename)
	: anim_cursor(0),
	current_frame_indx(0),
	speed(0.05f)
{
	FILE* fp = nullptr;
	const int bufferlen = 255;
	char line[bufferlen];

	fopen_s(&fp, filename, "r");

	if (fp == nullptr)
	{
		printf("erorr in reading animation file \n");
	}
	else
	{
		while (fgets(line, bufferlen, fp))
		{
			vector<int> result;

			stringstream ss(line);
			string token;
			while (getline(ss, token, ','))
			{
				result.push_back(stoi(token));
			}

			glm::vec4 frame = glm::vec4(result[0], result[1], result[2], result[3]);
			frames.push_back(frame);
		}
	}

	frames_count = (int)frames.size();

	fclose(fp);
}

Animation2D::~Animation2D()
{
}

void Animation2D::play(Texture& spritetexture, VertexArray& VA, VertexBuffer& VB, double deltatime)
{
	anim_cursor += deltatime;

	if (anim_cursor > speed)
	{
		current_frame_indx = (current_frame_indx + 1) % frames_count;
		anim_cursor = 0;
	}

	glm::vec4 frame = frames[current_frame_indx];

	// normalization
	frame.x /= spritetexture.GetWidth();
	frame.y /= spritetexture.GetHeight();
	frame.z /= spritetexture.GetWidth();
	frame.w /= spritetexture.GetHeight();

	vector<glm::vec2> uv;

	uv = {
		glm::vec2(frame.x,frame.y),
		glm::vec2(frame.x, frame.y + frame.w),
		glm::vec2(frame.x + frame.z, frame.y),

		glm::vec2(frame.x + frame.z, frame.y),
		glm::vec2(frame.x, frame.y + frame.w),
		glm::vec2(frame.x + frame.z, frame.y + frame.w)
	};

	//glBindVertexArray(rectangle.VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, rectangle.UVBO);

	/*{ //realocation for memory
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), &uv[0], GL_DYNAMIC_DRAW);
	}*/


	// best practice to send data to gpu memory..
	void* gpubuffer = nullptr;
	gpubuffer = glMapBufferRange(GL_ARRAY_BUFFER, 0, 6 * sizeof(glm::vec2), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
	memcpy(gpubuffer, uv.data(), 6 * sizeof(glm::vec2));
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Animation2D::set_animation_speed(float newspeed)
{
	speed = newspeed;
}
