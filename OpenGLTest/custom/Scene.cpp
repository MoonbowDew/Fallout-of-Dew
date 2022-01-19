#pragma once


#include "Scene.h"
#include "../Renderer.h"
#include "../custom/Physics.h"
#include <array>
#include <algorithm> 

#define BATCH_RENDERING
#define MAX_TEXTURES 32
#define MAX_OBJECTS 1000


    // 6/21/2021 section; Batch rendering

    TextureData LoadTexture(const std::string& path)
    {
        int w, h, bits;
        unsigned int textureID;
        stbi_set_flip_vertically_on_load(1);
        auto* pixels = stbi_load(path.c_str(), &w, &h, &bits, STBI_rgb_alpha);
        if (!pixels)
            std::cerr << "Cannot load file image %s\nSTB Reason: %s\n", path, stbi_failure_reason();


        

        glGenTextures(1, &textureID);

        //GLenum err = glGetError();
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);



        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        //glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
        glBindTexture(GL_TEXTURE_2D, 0);



        if (pixels)
            stbi_image_free(pixels);

        return { textureID, w, h };
    }



     std::array<Vertex, 4> Scene::CreateObject(glm::vec2 BottomLeft, glm::vec2 BottomRight, glm::vec2 TopRight, glm::vec2 TopLeft, float angle, float texID, float r = 1.0f, float g = 1.0f, float b = 1.0f, float alpha = 1.0f)
    {
        Vertex v1;

        //glm::mat4 model1(1.f); // 2. create Identity_matrix
        ////model1 = glm::translate(model1, glm::vec3(spawnX + 0.0f, spawnY + 0.0f, 0.0f));
        //if(angle != 0.0f)
        //    model1 = glm::rotate(model1, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
        //glm::mat4 mvp1 = m_VP * model1;
        //glm::vec4 RDQuaterion1 = mvp1 * glm::vec4(spawnX + 0.0f, spawnY + 0.0f, 0.0f, 1.0);

        //v1.position = { RDQuaterion1.x, RDQuaterion1.y, RDQuaterion1.z, RDQuaterion1.w };
        v1.position = { BottomLeft.x, BottomLeft.y, 0.0f };
        v1.color = { r, g, b, alpha };
        v1.texCoord = { 0.0f, 0.0f };
        v1.texID = { texID }; // 0.0f will be reserved for no object

        //glm::mat4 model2(1.f); // 2. create Identity_matrix
        ////model2 = glm::translate(model2, glm::vec3(spawnX + width, spawnY + 0.0f, 0.0f));
        //if (angle != 0.0f)
        //    model2 = glm::rotate(model2, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
        //glm::mat4 mvp2 = m_VP * model2;
        //glm::vec4 RDQuaterion2 = mvp2 * glm::vec4(spawnX + width, spawnY + 0.0f, 0.0f, 1.0);

        Vertex v2;

        //v2.position = { RDQuaterion2.x, RDQuaterion2.y, RDQuaterion2.z, RDQuaterion2.w };
        v2.position = { BottomRight.x, BottomRight.y, 0.0f };
        v2.color = { r, g, b, alpha };
        v2.texCoord = { 1.0f, 0.0f };
        v2.texID = { texID };

        //glm::mat4 model3(1.f); // 2. create Identity_matrix
        ////model3 = glm::translate(model3, glm::vec3(spawnX + width, spawnY + height, 0.0f));
        //if (angle != 0.0f)
        //    model3 = glm::rotate(model3, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
        //glm::mat4 mvp3 = m_VP * model3;
        //glm::vec4 RDQuaterion3 = mvp3 * glm::vec4(spawnX + width, spawnY + height, 0.0f, 1.0);


        Vertex v3;

        //v3.position = { RDQuaterion3.x, RDQuaterion3.y, RDQuaterion3.z, RDQuaterion3.w };
        v3.position = { TopRight.x, TopRight.y, 0.0f };
        v3.color = { r, g, b, alpha };
        v3.texCoord = { 1.0f, 1.0f };
        v3.texID = { texID };

        //glm::mat4 model4(1.f); // 2. create Identity_matrix
        ////model4 = glm::translate(model4, glm::vec3(spawnX + 0.0f, spawnY + height, 0.0f));
        //if (angle != 0.0f)
        //    model4 = glm::rotate(model4, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
        //glm::mat4 mvp4 = m_VP * model4;
        //glm::vec4 RDQuaterion4 = mvp4 * glm::vec4(spawnX + 0.0f, spawnY + height, 0.0f, 1.0);

        Vertex v4;

        //v4.position = { RDQuaterion4.x, RDQuaterion4.y, RDQuaterion4.z, RDQuaterion4.w };
        v4.position = { TopLeft.x, TopLeft.y, 0.0f };
        v4.color = { r, g, b, alpha };
        v4.texCoord = { 0.0f, 1.0f };
        v4.texID = { texID };


        return { v1, v2, v3, v4 };
    }

    static float SmoothStep(float x)
    {
        float min = std::min(1.0f, x);
        float max = std::max(0.0f, min);

        float result = (max * max) * (3 - 2 * max);
        return result;
    }

    // section end
    Scene::Scene()
        : m_Proj(glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
        m_VP(m_Proj * m_View),


        RD1TXData(LoadTexture("res/textures/dew.png")), RustyBarTXData(LoadTexture("res/textures/image 36_1.png")), FloorTXData(LoadTexture("res/textures/image 20.jpg")), /*BGImageTXData(LoadTexture("res/textures/image 70.jpg")),*/
        netTXData(LoadTexture("res/textures/image 37.png")), mouseCursorTXData(LoadTexture("res/textures/image 348.png")), blackVeilTXData(LoadTexture("res/textures/LevelMap.png")), 
        FogBlocksTXData(LoadTexture("res/textures/FogBoxAlpha4.png")), BGBlocksTXData(LoadTexture("res/textures/image 70.jpg")), RustyPipeTXData(LoadTexture("res/textures/RustyPipe1.png")),
        metalSupBlocksTXData(LoadTexture("res/textures/MetalSupport.png")),

        RD1(std::make_shared<GameObject>(glm::vec3(300, 500, 0), RD1TXData, 1.0f)), // 300 500 0
        mouseCursor(std::make_shared<GameObject>(glm::vec3(960, 540, 0), mouseCursorTXData, 4.0f)),
        blackVeil(std::make_shared<GameObject>(glm::vec3(0, 0, 0), blackVeilTXData, 0.0f)),
        RustyBar(std::make_shared<GameObject>(glm::vec3(845, 495, 0), RustyBarTXData, 2.0f)),
        Floor(std::make_shared<GameObject>(glm::vec3(147, 407, 0), FloorTXData, 3.0f)),
        RustyPipe(std::make_shared<GameObject>(glm::vec3(1085, 407, 0), RustyPipeTXData, 8.0f, 0.5f, 0.5f, 0.5f)),
        
        starttime(0), endtime(0), delta(0)
        
	{

        //change default texture size
        RD1->SetSpriteResolution(100, 100);
        //RD1->SetRotationAngle(90);
        blackVeil->SetSpriteResolution(1920, 1080);
        Floor->SetSpriteResolution(940, 10);


        //collideObjs.reserve(10); // better change to standard 2 (RustyBar and Floor)
        FogBlocks.reserve(400); // allocate 200 slots for fog elements
        BGBlocks.reserve(8); // allocate 200 slots for fog elements
        GameObjectsArray.reserve(450); // allocate 200 slots for fog elements
        //FogBlocks.resize(200, nullptr); // allocate 200 slots for fog elements

        for (float y = 420.0f; y < 900.0f; y += 160.0f /*10*/) // 3 
        {
            for (float x = 200.0f; x < 900; x += 600.0f /*10*/) // 2 
            {
                metalSupBlocks.push_back((std::make_shared<GameObject>(glm::vec3(x, y, 0), metalSupBlocksTXData, 9.0f, 0.5f, 0.5f, 0.5f)));
                //metalSupBlocks.back()->SetSpriteResolution(80, 80);
            }
        }


        for (float y = 360.0f; y < 800.0f; y += 40.0f /*10*/) // 11 (400);
        {
            for (float x = 100.0f; x < 1540; x += 40.0f /*10*/) // 40 (1600); - 6 = 34 + 2 = 36
            {
                FogBlocks.push_back((std::make_shared<GameObject>(glm::vec3(x, y, 0), FogBlocksTXData, 6.0f, 1.0f, 1.0f, 1.0f, 1.0f)));
                FogBlocks.back()->SetSpriteResolution(80, 80);
            }
        }

        //for (float y = 520.0f; y < 920.0f; y += 40.0f /*10*/) // 10 (800); 80
        //{
        //    for (float x = 1460.0f; x < 1860; x += 40.0f /*10*/) // 10 (1600);
        //    {
        //        FogBlocks.push_back((std::make_shared<GameObject>(glm::vec3(x, y, 0), FogBlocksTXData)));
        //        //FogBlocks.back()->ChangeSize(10, 10);
        //    }
        //}

        for (int y = 0.0f; y < 1000.0f; y += 250.0f)
        {
            for (int x = 0.0f; x < 1920.0f; x += 960.0f)
            {
                BGBlocks.push_back((std::make_shared<GameObject>(glm::vec3(x, y, 0), BGBlocksTXData, 7.0f, 0.5f, 0.5f, 0.5f)));
            }
        }

        for (int y = 520.0f; y < 680.0f; y += 40.0f) // 4 (160)
        {
            for (int x = 1085.0f; x < 1205.0f; x += 40.0f) // 3 (120)
            {
                netBlocks.push_back((std::make_shared<GameObject>(glm::vec3(x, y, 0), netTXData, 5.0f, 0.5f, 0.5f, 0.5f)));
            }
        }

        floorAndSeilingBlocks.push_back(std::make_shared<GameObject>(glm::vec3(147, 780, 0), FloorTXData, 3.0f, 1.0f, 1.0f, 1.0f, 0.0f)); // потолок над Дью
        floorAndSeilingBlocks.back()->SetSpriteResolution(610, 10);



        collideObjs.push_back(RustyBar);
        collideObjs.push_back(Floor);
        collideObjs.push_back(floorAndSeilingBlocks.back());

        //array Section
        GameObjectsArray.insert(GameObjectsArray.begin(), BGBlocks.begin(), BGBlocks.end());
        GameObjectsArray.insert(GameObjectsArray.begin() + BGBlocks.size(), netBlocks.begin(), netBlocks.end());
        GameObjectsArray.insert(GameObjectsArray.begin() + BGBlocks.size() + netBlocks.size(), metalSupBlocks.begin(), metalSupBlocks.end());
        GameObjectsArray.push_back(RustyPipe);
        GameObjectsArray.push_back(RustyBar);
        GameObjectsArray.push_back(blackVeil);
        GameObjectsArray.push_back(RD1);
        GameObjectsArray.push_back(Floor);
        GameObjectsArray.insert(GameObjectsArray.begin() + 5 + BGBlocks.size() + netBlocks.size() + metalSupBlocks.size(), floorAndSeilingBlocks.begin(), floorAndSeilingBlocks.end());
        GameObjectsArray.insert(GameObjectsArray.begin() + 5 + BGBlocks.size() + netBlocks.size() + metalSupBlocks.size() + floorAndSeilingBlocks.size(), FogBlocks.begin(), FogBlocks.end());
        GameObjectsArray.push_back(mouseCursor);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        

        m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
        m_Shader->Bind();
        m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        m_Shader->SetUniform1iv("u_Texture", MAX_TEXTURES);
        

	}
	Scene::~Scene()
	{
        std::cout << "ALL CLEANED" << std::endl;
	}

    int angleToRot = 0;

	void Scene::OnUpdate(GLFWwindow* window, float deltaTime)
	{
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            RD1->Jump();
        }

        // Strafe left
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            RD1->MoveLeft(5.0f);
        }

        // Strafe right
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            RD1->MoveRight(5.0f);
        }

        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
            RD1->ChangeSize(-9, -9);
        }

        if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
            RD1->ChangeSize(9, 9);
        }

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            RD1->SetRotationAngle(angleToRot+=3);
        }

        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            RD1->SetRotationAngle(angleToRot-=3);
        }

        // affect Dew with gravity
        Gravity(RD1, RD1->GetYVelocity());

        for (auto & obj : collideObjs)
        {
             if (CheckCollision(RD1, obj))
            {
                float tmp2 = RD1->GetX() - (obj->GetX() + obj->GetXLength());
                //std::cout << "COLLISION!!!" << std::endl;
                RD1->SetYVelocity(0);
                //float tmp1 = RD1->GetYLength() + RD1->GetY() - obj->GetY();
                if( 0 < (RD1->GetYLength() + RD1->GetY() - obj->GetY()) && (RD1->GetYLength() + RD1->GetY() - obj->GetY()) < 7) // остановка при ударе о потолок
                    RD1->MoveUp(- 5.5);

                //float tmp2 = RD1->GetXLength() + RD1->GetX() - obj->GetX();
                else if ((0.0 <= (RD1->GetXLength() + RD1->GetX() - obj->GetX()) && (RD1->GetXLength() + RD1->GetX() - obj->GetX()) <= 10.0)) // остановка при ударе о стену справа
                    RD1->MoveLeft(5.0f);
                
                else if(-5.5 <= RD1->GetX() - (obj->GetX() + obj->GetXLength()) && RD1->GetX() - (obj->GetX() + obj->GetXLength()) <= 5.5) // остановка при ударе о стену справа
                    RD1->MoveRight(5.0f);

                //if ((0 < (RD1->GetBottomLeft().y - obj->GetY()) && (RD1->GetBottomLeft().y - obj->GetY()) < 7) ||
                //    (0 < (RD1->GetBottomRight().y - obj->GetY()) && (RD1->GetBottomRight().y - obj->GetY()) < 7) ||
                //    (0 < (RD1->GetTopRight().y - obj->GetY()) && (RD1->GetTopRight().y - obj->GetY()) < 7) ||
                //    (0 < (RD1->GetTopLeft().y - obj->GetY()) && (RD1->GetTopLeft().y - obj->GetY()) < 7)) // остановка при ударе о потолок
                //    RD1->MoveUp(-5.5);

                ////float tmp2 = RD1->GetXLength() + RD1->GetX() - obj->GetX();
                //else if ((0 < (RD1->GetBottomLeft().x - obj->GetX()) && (RD1->GetBottomLeft().x - obj->GetX()) <= 10) ||
                //    (0 < (RD1->GetBottomRight().x - obj->GetX()) && (RD1->GetBottomRight().x - obj->GetX()) <= 10) ||
                //    (0 < (RD1->GetTopRight().x - obj->GetX()) && (RD1->GetTopRight().x - obj->GetX()) <= 10) ||
                //    (0 < (RD1->GetTopLeft().x - obj->GetX()) && (RD1->GetTopLeft().x - obj->GetX()) <= 10))  // остановка при ударе о стену справа
                //    RD1->MoveLeft(5.0f);

                //else if ((-5.5 < (RD1->GetBottomLeft().x - obj->GetX()) && (RD1->GetBottomLeft().x - obj->GetX()) <= 5.5) ||
                //    (-5.5 < (RD1->GetBottomRight().x - obj->GetX()) && (RD1->GetBottomRight().x - obj->GetX()) <= 5.5) ||
                //    (-5.5 < (RD1->GetTopRight().x - obj->GetX()) && (RD1->GetTopRight().x - obj->GetX()) <= 5.5) ||
                //    (-5.5 < (RD1->GetTopLeft().x - obj->GetX()) && (RD1->GetTopLeft().x - obj->GetX()) <= 5.5)) // остановка при ударе о стену справа
                //    RD1->MoveRight(5.0f);
            }
        }

        // Fog of War behavior
        auto it = FogBlocks.begin();

        while (it != std::end(FogBlocks)) {
            // Do some stuff
            if (CheckCollision(RD1, *it))
            {
                (*it)->SetAlphaChannel((*it)->GetAlphaChannel() - (delta*60)); // instead of SmoothStep function
                if( (*it)->GetAlphaChannel() <= 0)
                    it = FogBlocks.erase(it);
                else ++it;
            }

            else
            {
                (*it)->SetAlphaChannel(1.0f);
                ++it;
            }
        }

        // replace cursor with image
        double xpos = 0.0;
        double ypos = 0.0;
        glfwGetCursorPos(window, &xpos, &ypos);
        //std::cout << xpos << " " << ypos << std::endl;
        mouseCursor->SetXPosition(xpos);
        mouseCursor->SetYPosition(1080.0f - ypos);
        //mouseCursor->PrintCoords();

	}
    
    void BindTextures(std::vector<std::shared_ptr <GameObject>> GameObjectsArray)
    {
        for (int i = 0; i < GameObjectsArray.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + GameObjectsArray[i]->GetTXNumber() + 1);
            glBindTexture(GL_TEXTURE_2D, GameObjectsArray[i]->GetTextureID());
        }
    }

    void Scene::FillVBO(std::vector<std::shared_ptr <GameObject>> GameObjectsArray, Vertex* arr)
    {
        for (int i = 0; i < GameObjectsArray.size(); i++) // 8 bg objs
        {
            auto tmp = CreateObject(GameObjectsArray[i]->GetBottomLeft(), GameObjectsArray[i]->GetBottomRight(), GameObjectsArray[i]->GetTopRight(), GameObjectsArray[i]->GetTopLeft(), GameObjectsArray[i]->GetRotationAngle(),
                GameObjectsArray[i]->GetTXNumber(), GameObjectsArray[i]->GetColorR(), GameObjectsArray[i]->GetColorG(), GameObjectsArray[i]->GetColorB(), GameObjectsArray[i]->GetAlphaChannel());

            memcpy(arr + (tmp.size() * i), tmp.data(), tmp.size() * sizeof(Vertex));
        }
    }


	void Scene::OnRender(GLFWwindow* window)
	{

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT);

        starttime = glfwGetTime();

        const size_t MaxQuadCount = MAX_OBJECTS/*3217*/;
        const size_t MaxVertexCount = MaxQuadCount * 4;
        const size_t MaxIndexCount = MaxQuadCount * 6;

        Vertex vertices[MaxVertexCount]; // (background tiles) + nets (12) + cursor, RD1, RustyBar, Floor, blackVeil; 17 obs * 4 vert = 68

        unsigned int indices[MaxIndexCount];
        unsigned int offset = 0;
        for (size_t i = 0; i < MaxIndexCount; i += 6)
        {
            indices[i + 0] = 0 + offset;
            indices[i + 1] = 1 + offset;
            indices[i + 2] = 2 + offset;

            indices[i + 3] = 2 + offset;
            indices[i + 4] = 3 + offset;
            indices[i + 5] = 0 + offset;

            offset += 4;
        }

        std::unique_ptr<VertexArray> VAO = std::make_unique<VertexArray>();
        VAO->Bind();
        std::unique_ptr<VertexBuffer> VBO = std::make_unique<VertexBuffer>(nullptr, sizeof(Vertex) * MaxVertexCount); // buffer capability is 1000 quads (4000 Vertices), 
        //VBO->Bind();
        std::unique_ptr<IndexBuffer> IB = std::make_unique<IndexBuffer>(indices, MaxIndexCount); // fix arguments, 
        IB->Bind();


        glEnableVertexArrayAttrib(VBO->GetID(), 0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));

        glEnableVertexArrayAttrib(VBO->GetID(), 1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));

        glEnableVertexArrayAttrib(VBO->GetID(), 2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texCoord));

        glEnableVertexArrayAttrib(VBO->GetID(), 3);
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texID));

        glm::mat4 model(1.f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        //model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        //model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        //model = glm::rotate(model, glm::radians(40.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 mvp = m_Proj * m_View * model;

        BindTextures(GameObjectsArray);

        FillVBO(GameObjectsArray, vertices);


        //std::cout << sizeof(vertices) << std::endl; // showing stack overflow
        

        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", mvp);


        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glDrawElements(GL_TRIANGLES, IB->GetCount(), GL_UNSIGNED_INT, nullptr);


        endtime = glfwGetTime();
        delta = endtime - starttime;
	}
