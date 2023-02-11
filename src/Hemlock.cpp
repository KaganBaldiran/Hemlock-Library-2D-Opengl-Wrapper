#include "Hemlock.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <vector>
#include <cmath>

#include <ft2build.h>
#include FT_FREETYPE_H

#define M_PI 3.14




glm::mat4 translate(const glm::vec3& translation)
{
    glm::mat4 translationMatrix(1.0f);
    translationMatrix[3][0] = translation.x;
    translationMatrix[3][1] = translation.y;
    translationMatrix[3][2] = translation.z;
    return translationMatrix;
}

struct Characterr {

    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
    GLuint Advance;    // Offset to advance to next glyph

    void SET(GLuint textureID, glm::ivec2 size, glm::ivec2 bearing, GLuint advance)
    {
        TextureID = textureID;
        Size = size;
        Bearing = bearing;
        Advance = advance;

    };

};

void Hemlock::InitializeRenderer(const char* Window_name , int window_width, int window_height, bool Enable_anti_aliasing){


    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    m_width = window_width, m_height = window_height;

    if (Enable_anti_aliasing)
    {
        glfwWindowHint(GLFW_SAMPLES, 4);

        glEnable(GL_MULTISAMPLE);
    }

    for (size_t i = 0; i < Windowhints.size(); i++)
    {
        glfwWindowHint(Windowhints[i]->first, Windowhints[i]->second);
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    m_window = glfwCreateWindow(m_width, m_height, Window_name, nullptr, nullptr);
    if (!m_window) {

        std::cerr << "Failed to create window with opengl context version: 4.6" << std::endl;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        m_window = glfwCreateWindow(m_width, m_height, Window_name, nullptr, nullptr);

        if (!m_window) {

            std::cerr << "Failed to create window with opengl context version: 4.5" << std::endl;

            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
            m_window = glfwCreateWindow(m_width, m_height, Window_name, nullptr, nullptr);

            if (!m_window) {

                std::cerr << "Failed to create window with opengl context version: 4.4" << std::endl;

                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                m_window = glfwCreateWindow(m_width, m_height, Window_name, nullptr, nullptr);

                if (!m_window) {
                
                    std::cerr << "Failed to create window with opengl context version: 4.3" << std::endl;

                    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
                    m_window = glfwCreateWindow(m_width, m_height, Window_name, nullptr, nullptr);

                    if (!m_window) {
                    
                        std::cerr << "Failed to create window with opengl context version: 4.2" << std::endl;

                        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
                        m_window = glfwCreateWindow(m_width, m_height, Window_name, nullptr, nullptr);

                        if (!m_window) {

                            std::cerr << "Failed to create window with opengl context version: 4.1" << std::endl;

                            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
                            m_window = glfwCreateWindow(m_width, m_height, Window_name, nullptr, nullptr);


                            if (!m_window) {

                                std::cerr << "Failed to create window with opengl context version: 4.0" << std::endl;

                                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                                m_window = glfwCreateWindow(m_width, m_height, Window_name, nullptr, nullptr);

                                if (!m_window) {

                                    std::cerr << "Failed to create window with opengl context version: 3.3" << std::endl;

                                    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                                    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
                                    m_window = glfwCreateWindow(m_width, m_height, Window_name, nullptr, nullptr);

                                    if (!m_window)
                                    {
                                        std::cerr << "Failed to create window" << std::endl;
                                        glfwTerminate();
                                        return;
                                    }
                                }
                            }

                        }
                    
                    }
                
                }

            }

        }
 
    }


    glfwMakeContextCurrent(m_window);

    
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return;
    }

    int major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    const float libversion = 1.1;

    std::cout << "Hemlock Library Version: " << libversion<<"\n";

    std::cout << "OpenGL version: " << major << "." << minor << std::endl;

    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    std::cout << "Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

Hemlock::~Hemlock() {

    for (HemlockTexture* texturet : m_textures)
    {
        delete texturet;
    }

    for(HemlockPrimitive* primitivet : primitives)
    {
        delete primitivet;
    }

    for (std::pair<WINDOWHINTS,bool> *windowhint : Windowhints)
    {
        delete windowhint;
    }

    for (std::pair<const GLchar, Characterr*> charac : Characters)
    {
        delete charac.second;
    }

    glDeleteProgram(m_program);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &tria_vbo);
    glDeleteBuffers(1, &rect_vbo);
    glDeleteVertexArrays(1, &m_vao);
    glDeleteVertexArrays(1, &rect_vao);
    glDeleteVertexArrays(1, &tria_vao);
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &colvao);
    glDeleteBuffers(1, &colvbo);
    glDeleteVertexArrays(1, &circle_vao);
    glDeleteBuffers(1, &circle_vbo);
    glDeleteBuffers(1, &circle_ibo);
    glDeleteBuffers(1, &crossebo);
    glDeleteBuffers(1, &crossvbo);
    glDeleteVertexArrays(1, &crossvao);

    std::cout << "All buffers are deleted!" << std::endl;

    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Hemlock::addTexture(const char* filename) {

    HemlockTexture *temp = new HemlockTexture(filename);
    *temp->ReturnTextureid() = m_textures.size();
    m_textures.push_back(temp);
    temp->SetTextureIndex(m_textures.size() - 1);
}

int Hemlock::GetLastTextureID()
{
    if (m_textures.size() > 0)
    {
        return m_textures.size() - 1;
    }
    else
    {
        return -10;
    }
    
}

HemlockTexture *Hemlock::GetTexture(size_t index)
{
    return m_textures.at(index);
}

void Hemlock::InitShaders()
{
    
    if (!m_program)
    {

        const char* vertexSource = R"(
    #version 330 core

    in vec2 position;
    in vec2 texcoord;

    in vec4 vertexdata;
    
    out vec2 Texcoord;

    uniform mat4 transform;
    uniform int modev;

    uniform int instance_count;

    uniform vec2 offsets[100];

    uniform vec4 texturerect;

   void main() 
   {

    if(modev == 0)
    {
      Texcoord = vertexdata.zw;
      vec4 pos = vec4(vertexdata.xy, 0.0, 1.0);
      gl_Position = transform * pos;
      
    }

    else if(modev == 1)
    {
      Texcoord = vertexdata.zw;
      vec4 pos = vec4(vertexdata.xy, 0.0, 1.0);
      gl_Position = transform * pos ;

    }
    else if(modev == 2)
    {
     Texcoord = vertexdata.zw;
     vec4 pos = vec4(vertexdata.xy, 0.0, 1.0);
     gl_Position = pos;
    }
    else if(modev == 3)
    {

      vec4 pos = vec4(position, 0.0, 1.0);
      gl_Position = pos ;

    }
    
    else if(modev == 4)
    {
      Texcoord = vec2(vertexdata.z + texturerect.x , vertexdata.w + texturerect.y) * vec2(texturerect.z,texturerect.w);
      vec4 pos = vec4(vertexdata.xy, 0.0, 1.0);
      gl_Position = transform * pos ;
      
    }
    else if(modev == 5)
    {

      vec4 pos = vec4(position.xy, 0.0, 1.0);
      gl_Position = transform * pos ;

    }
    
      
    }

  )";

        const char* fragmentSource = R"(
    #version 330 core
    in vec2 Texcoord;
    out vec4 outColor;
    uniform sampler2D tex;
    uniform sampler2D color;
    uniform int modef;
    uniform vec4 colorpr;


    
    void main() {
    
    if(modef == 0)
    {
      outColor = texture(tex, Texcoord);
    }
    else if(modef == 1)
    {
      
      outColor = colorpr;
    }

    else if(modef == 2)
    {
      vec4 sampled = vec4(1.0, 1.0, 1.0, texture(tex, Texcoord).r);
      outColor = colorpr * sampled;
    }
    

    

  }
)";




        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, nullptr);
        glCompileShader(vertexShader);

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
        glCompileShader(fragmentShader);


        // Check shader errors
        GLint status;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
        if (status != GL_TRUE) {
            char buffer[512];
            glGetShaderInfoLog(vertexShader, 512, nullptr, buffer);
            std::cerr << "Failed to compile vertex shader: " << buffer << std::endl;
            return;
        }
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
        if (status != GL_TRUE) {
            char buffer[512];
            glGetShaderInfoLog(fragmentShader, 512, nullptr, buffer);
            std::cerr << "Failed to compile fragment shader: " << buffer << std::endl;
            return;
        }

        // Link the shaders
        m_program = glCreateProgram();
        glAttachShader(m_program, vertexShader);
        glAttachShader(m_program, fragmentShader);
        glLinkProgram(m_program);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);


        glGetProgramiv(m_program, GL_LINK_STATUS, &status);
        if (status != GL_TRUE) {
            char buffer[512];
            glGetProgramInfoLog(m_program, 512, nullptr, buffer);
            std::cerr << "Failed to link program: " << buffer << std::endl;
            return;
        }


        // Specify the layout 
        GLint posAttrib = glGetAttribLocation(m_program, "position");
        glEnableVertexAttribArray(posAttrib);
        glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

        GLint texAttrib = glGetAttribLocation(m_program, "texcoord");
        glEnableVertexAttribArray(texAttrib);
        glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));


        m_transformLocation = glGetUniformLocation(m_program, "transform");

        colorpr = glGetUniformLocation(m_program, "colorpr");

        drawmodef = glGetUniformLocation(m_program, "modef");
        drawmodev = glGetUniformLocation(m_program, "modev");

        std::cout << "Shaders are initialized!" << std::endl;


        //Loading the buffer for rectangle
        float rectangle_vertices[] = {
            // positions      // texture coordinates
             0.5f,  0.5f,    1.0f, 0.0f, // top right
             0.5f, -0.5f,    1.0f, 1.0f, // bottom right
            -0.5f, -0.5f,    0.0f, 1.0f, // bottom left
            -0.5f,  0.5f,    0.0f, 0.0f  // top left
        };

        glGenVertexArrays(1, &rect_vao);

        glBindVertexArray(rect_vao);
        // Create the vbo 
        glGenBuffers(1, &rect_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, rect_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle_vertices), rectangle_vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);



        //Loading the buffer for triangle
        float triangle_vertices[] = {
            // positions      // texture coordinates
             0.0f,  0.5f,    1.0f, 0.0f, // top right
             0.5f,  0.0f,    1.0f, 1.0f, // bottom right
            -0.5f,  0.0f,    0.0f, 1.0f, // bottom left
        };

        int datasize = sizeof(triangle_vertices);
        int buffersize;

        glGenVertexArrays(1, &tria_vao);

        glBindVertexArray(tria_vao);

        glGenBuffers(1, &tria_vbo);

        glBindBuffer(GL_ARRAY_BUFFER, tria_vbo);

        glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);


        // Create the vertex data
        float vertices[] = {
            // positions      // texture coordinates
             0.5f,  0.5f,    1.0f, 0.0f, // top right
             0.5f, -0.5f,    1.0f, 1.0f, // bottom right
            -0.5f, -0.5f,    0.0f, 1.0f, // bottom left
            -0.5f,  0.5f,    0.0f, 0.0f  // top left
        };


        // Create the vbo 
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);


        glGenVertexArrays(1, &colvao);
        glGenBuffers(1, &colvbo);



        glGenVertexArrays(1, &circle_vao);
        glBindVertexArray(circle_vao);
        glGenBuffers(1,&circle_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, circle_vbo);
        glGenBuffers(1, &circle_ibo);

        glGenBuffers(1, &crossvbo);
        glGenVertexArrays(1, &crossvao);
        glGenBuffers(1, &crossebo);

        //glCullFace(GL_CW);
    }
}

void Hemlock::setScale(float scale) {

    m_scale = scale;
}

void Hemlock::render() {
    
	glfwSwapBuffers(m_window);
	glfwPollEvents();

	glBufferData(GL_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW);

	glUseProgram(0);
}

void Hemlock::clearscreen(Vec4<float> color)
{
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT);
}

GLFWwindow *Hemlock::return_window()
{
    return m_window;
}







bool Hemlock::IsKeyPressed(int key)
{
    
    if (glfwGetKey(m_window, key) == GLFW_PRESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Hemlock::IsMouseButtonPressed(int button)
{
    if (glfwGetMouseButton(m_window, button) == GLFW_PRESS)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

bool Hemlock::IsMouseButtonReleased(int button)
{
    if (glfwGetMouseButton(m_window, button) == GLFW_RELEASE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Hemlock::MaximizeWindow()
{
    glfwMaximizeWindow(m_window);
}

Vec2<double> Hemlock::GetMousePosScreencords()
{
    Vec2<double> xy;
    glfwGetCursorPos(m_window, &xy.x, &xy.y);
    return xy;
}

Vec2<double> Hemlock::GetMousePosGLcords()
{
    Vec2<double> temp;
    temp.x = (GetMousePosScreencords().x * (2.0f / GetWindowSize().x) - 1);
    temp.y = ( - (GetMousePosScreencords().y * (2.0f / GetWindowSize().y) - 1));
    return temp;
}

Vec2<float> Hemlock::Screen2WorldCoords(Vec2<float> Screencords)
{
    Vec2<float> worldcords = { NULL,NULL };

    worldcords.x = (2.0f / GetWindowSize().x) * Screencords.x;

    worldcords.y = (2.0f / GetWindowSize().y) * Screencords.y;


    if (Screencords.y == (GetWindowSize().y / 2.0f))
    {
        worldcords.y = 0.0f;
    }
    else
    {
        worldcords.y = -(worldcords.y - 1.0f);
    }

    if (Screencords.x == (GetWindowSize().x / 2.0f))
    {
        worldcords.x = 0.0f;
    }
    else
    {
        worldcords.x = (worldcords.x - 1.0f) - 1.0f;
    }

    worldcords.x += 1.0f;


    return worldcords;
}

std::pair<bool, float> Hemlock::SetFps(int fps)
{
    const double targetFrameRate = fps;
    const double targetFrameTime = 1.0 / targetFrameRate;

    const double currentTime = glfwGetTime();
    static double previousTime = currentTime;
    const double elapsedTime = currentTime - previousTime;

    static double currentFps = 0;
    
    if (elapsedTime >= targetFrameTime)
    {
        previousTime = currentTime;

        currentFps = 1.0 / elapsedTime;
        //std::cout << "Current FPS: " << currentFps << std::endl;

        return { true,currentFps };
    }
    else 
    { 
        return { false,currentFps };
    }

    
}

void Hemlock::framebuffer_size_recall()
{
    Vec2<int> winsize;
    glfwGetWindowSize(m_window, &winsize.x, &winsize.y);
    glViewport(0, 0, winsize.x, winsize.y);
}

int Hemlock::WindowShouldClose()
{
    return glfwWindowShouldClose(m_window);
}

Vec2<int> Hemlock::GetWindowSize()
{
    Vec2<int> winsize;
    glfwGetWindowSize(m_window, &winsize.x, &winsize.y);
    return winsize;
}

void Hemlock::SetTextureAttrib(size_t texture_index, long float scale)
{
    HemlockTexture* text = GetTexture(texture_index);

    text->setScale(scale);

}

void Hemlock::SetTextureAttrib(size_t texture_index, Vec2<float> position )
{
    HemlockTexture* text = GetTexture(texture_index);

    Vec2<float> temp = Screen2WorldCoords(position);

    text->setpos_x(temp.x);

    text->setpos_y(temp.y);
}

void Hemlock::SetTextureAttrib(size_t texture_index, float rotation)
{
    HemlockTexture* text = GetTexture(texture_index);

    text->rotate(rotation);

}

void Hemlock::SetPrimitiveAttrib(size_t primitive_index, long float scale)
{
    HemlockPrimitive* priv = GetPrimitive(primitive_index);

    priv->SetPrimitiveScale(scale);
}

void Hemlock::SetPrimitiveAttrib(size_t primitive_index, Vec2<float> position)
{
    HemlockPrimitive* priv = GetPrimitive(primitive_index);

    priv->SetPrimitivePosition(Screen2WorldCoords(position));
}

void Hemlock::SetPrimitiveAttrib(size_t primitive_index, float rotation)
{
    HemlockPrimitive* priv = GetPrimitive(primitive_index);

    priv->Rotate(rotation);

}



bool Hemlock::CheckCollisionBoxBox(CollisionBox* colboxtocheck1, CollisionBox* colboxtocheck2)
{
    Vec4<float> cb1 = { colboxtocheck1->GetCollisionRect()->x + (colboxtocheck1->GetCollisionRect()->width / 2) ,
                            colboxtocheck1->GetCollisionRect()->x - (colboxtocheck1->GetCollisionRect()->width / 2) ,
                            colboxtocheck1->GetCollisionRect()->y + (colboxtocheck1->GetCollisionRect()->height / 2) ,
                            colboxtocheck1->GetCollisionRect()->y - (colboxtocheck1->GetCollisionRect()->height / 2) };


    Vec4<float> cb2 = { colboxtocheck2->GetCollisionRect()->x + (colboxtocheck2->GetCollisionRect()->width / 2) ,
                        colboxtocheck2->GetCollisionRect()->x - (colboxtocheck2->GetCollisionRect()->width / 2) ,
                        colboxtocheck2->GetCollisionRect()->y + (colboxtocheck2->GetCollisionRect()->height / 2) ,
                        colboxtocheck2->GetCollisionRect()->y - (colboxtocheck2->GetCollisionRect()->height / 2) };


    if ((cb1.x >= cb2.y && cb1.x <= cb2.x) || (cb1.y >= cb2.y && cb1.y <= cb2.x) || (cb2.x >= cb1.y && cb2.x <= cb1.x) || (cb2.y >= cb1.y && cb2.y <= cb1.x))
    {
        if ((cb1.z >= cb2.w && cb1.z <= cb2.w) || (cb1.w >= cb2.w && cb1.w <= cb2.z) || (cb2.z >= cb1.w && cb2.z <= cb1.z) || (cb2.w >= cb1.w && cb2.w <= cb1.z))
        {

            return true;

        }

    }

    return false;
}

int Hemlock::SetWindowHint(WINDOWHINTS hint, bool value)
{
    std::pair<WINDOWHINTS, bool>* temp = new std::pair<WINDOWHINTS, bool>(hint, value);
    Windowhints.push_back(temp);
    return Windowhints.size() - 1;
}





void Hemlock::DrawLine(float x1, float y1, float x2, float y2, float thickness, Vec3<float> color)
{
    // Set the line thickness
    glLineWidth(thickness);

    // Set the line color
    glUniform3f(glGetUniformLocation(m_program, "color"), color.x, color.y, color.z);

    // Set up the vertex data for the line
    float vertices[] = { x1, y1, x2, y2 };
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set up the vertex attribute for the line
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Draw the line
    glDrawArrays(GL_LINES, 0, 2);
}

Vec2<float> Hemlock::GetScreenRatio()
{
    Vec2<int> winsize;
    glfwGetWindowSize(m_window, &winsize.x, &winsize.y);

    float ratio_minmax = NULL;

    float aspectRatios_wh = static_cast<float>(winsize.x) / static_cast<float>(winsize.y);

    float aspectRatios_hw = static_cast<float>(winsize.y) / static_cast<float>(winsize.x);


    float ratio_minmax_x = NULL, ratio_minmax_y = NULL;

    if (m_height > m_width)
    {
        ratio_minmax_x = aspectRatios_hw;
        ratio_minmax_y = 1.0f;

    }
    if (m_height < m_width)
    {
        ratio_minmax_x = aspectRatios_hw;
        ratio_minmax_y = 1.0f;

    }
    if (m_height == m_width)
    {
        ratio_minmax_x = 1.0f;
        ratio_minmax_y = 1.0f;
    }

    return Vec2<float>{ratio_minmax_x, ratio_minmax_y};
}



HemlockPrimitive* Hemlock::GetPrimitive(size_t index)
{
    return primitives.at(index);
}

void Hemlock::AddPrimitive(int Primitive_Type,Vec4<float> color)
{
    HemlockPrimitive *temp = new HemlockPrimitive(Primitive_Type,color);
    *temp->ReturnPrimitiveid() = primitives.size();
    primitives.push_back(temp);
}

int Hemlock::GetLastPrimitiveID()
{
    if (primitives.size() > 0)
    {
        return primitives.size() - 1;
    }
    else
    {
        return -10;
    }
    
}





void Hemlock::drawTriangle(size_t primitive_index)
{

    HemlockPrimitive* primitive = primitives.at(primitive_index);

    if (primitive->GetPrimitiveType() == TRIANGLE)
    {
        glBindBuffer(GL_ARRAY_BUFFER, tria_vbo);

        glUseProgram(m_program);

        glUniform1i(drawmodef, 1);
        glUniform1i(drawmodev, 1);

        glBindVertexArray(tria_vao);

        GLint vertexdata = glGetAttribLocation(m_program, "vertexdata");

        glVertexAttribPointer(vertexdata, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

        glEnableVertexAttribArray(vertexdata);


        glm::mat4 transformation = glm::mat4(1.0f);

        
        transformation = glm::translate(transformation, glm::vec3(primitive->GetPosition().x, primitive->GetPosition().y, 1.0f));

        //translate to origin
        transformation = glm::translate(transformation, -glm::vec3(glm::vec2{0.0f,0.0f}, 1.0f));

        
        transformation = glm::scale(transformation, glm::vec3(GetScreenRatio().x, GetScreenRatio().y, 1.0f));

        

        if (m_height > m_width)
        {
            transformation = glm::scale(transformation, glm::vec3(0.5f, 0.5f, 1.0f));
        }

        
        transformation = glm::scale(transformation, glm::vec3(primitive->GetScale(), primitive->GetScale(), 1.0f));

        transformation = glm::rotate(transformation, glm::radians(primitive->GetRotation()), glm::vec3(0.0f, 0.0f, 1.0f));

        
        //translate back to its position
        transformation = glm::translate(transformation, glm::vec3(glm::vec2{ 0.0f,0.0f }, 1.0f));


        glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, glm::value_ptr(transformation));

        glUniform4f(colorpr, primitive->GetColor().x, primitive->GetColor().y, primitive->GetColor().z, primitive->GetColor().w);


        //Draw
        glDrawArrays(GL_TRIANGLES, 0, 4);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

    }
    else
    {
        return;
    }

}

void Hemlock::DrawTexture(size_t texture_index)
{
	HemlockTexture* texture = m_textures.at(texture_index);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glUseProgram(m_program);

	glUniform1i(drawmodef, 0);
	glUniform1i(drawmodev, 0);

    glBindVertexArray(m_vao);

    
    GLint vertexdata = glGetAttribLocation(m_program, "vertexdata");

    glVertexAttribPointer(vertexdata, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

    glEnableVertexAttribArray(vertexdata);


	m_scale = texture->get_scale();

    //std::cout << "scale: " << texture->get_scale() << std::endl;

	float aspect_ratio_hw = (float)texture->get_height() / (float)texture->get_width();

	float aspect_ratio_wh = (float)texture->get_width() / (float)texture->get_height();

	float ratio_minmax = NULL;

	float aspectRatios_wh = static_cast<float>(m_width) / static_cast<float>(m_height);

	float aspectRatios_hw = static_cast<float>(m_height) / static_cast<float>(m_width);



	//std::cout << "texture " << i << ": " << texture->get_rotation() << std::endl;



	if (texture->get_height() > texture->get_width())
	{
		ratio_minmax = glm::max(aspect_ratio_hw, aspect_ratio_wh);
	}
	if (texture->get_height() <= texture->get_width())
	{
		ratio_minmax = glm::min(aspect_ratio_hw, aspect_ratio_wh);
	}


	float texture_width = (2.0f * (float)texture->get_width()) / (float)m_width;
	float texture_height = (2.0f * (float)texture->get_height()) / (float)m_height;

	glm::mat4 transform = glm::mat4(1.0f);


	glm::vec2 position(0.0f, 0.0f);


	float angle = 45.0f;

	glm::vec3 axis(0.0f, 0.0f, 1.0f);


	glm::mat4 rotation = glm::mat4(1.0f);


    rotation = glm::translate(rotation, glm::vec3(texture->get_pos_x(), texture->get_pos_y(), 1.0f));


	rotation = glm::translate(rotation, -glm::vec3(position, 1.0f));

	float ratio_minmax_x = NULL, ratio_minmax_y = NULL;

	if (m_height > m_width)
	{
		ratio_minmax_x = aspectRatios_hw;
		ratio_minmax_y = aspectRatios_hw;

	}
	if (m_height < m_width)
	{
		ratio_minmax_x = aspectRatios_hw;
		ratio_minmax_y = 1.0f;

	}

	rotation = glm::scale(rotation, glm::vec3(GetScreenRatio().x, GetScreenRatio().y, 1.0f));

	if (m_height > m_width)
	{
		rotation = glm::scale(rotation, glm::vec3(0.5f, 0.5f, 1.0f));
	}

	rotation = glm::rotate(rotation, glm::radians(texture->get_rotation()), (glm::vec3)axis);

	rotation = glm::scale(rotation, glm::vec3(m_scale, m_scale, 1.0f));

	rotation = glm::scale(rotation, glm::vec3(1.0f, ratio_minmax, 1.0f));

	// Translate to its original position
	rotation = glm::translate(rotation, glm::vec3(position, 1.0f));

	//std::cout << "texture ratio " << texture_index << ": " << ratio_minmax << std::endl;

	GLfloat aspectRatio = m_width / m_height;
	//glm::mat4 mat_projection = glm::ortho(-1.0f, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);

	float x = 0.5f;
	float y = 0.5f;

	transform = rotation * transform;


	glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, glm::value_ptr(rotation));


	float ratio_temp = ((float)texture->get_width() / (float)texture->get_height());


	char name[] = "tex";
	glUniform1i(glGetUniformLocation(m_program, name), texture->GetTextureIndex());
	texture->bind(GL_TEXTURE0+texture->GetTextureIndex());

    
	//Draw
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glBindTexture(GL_TEXTURE_2D, 0);

    glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

    

}

void Hemlock::DrawTextureRect(size_t texture_index, Vec4<float> rect)
{

    HemlockTexture* texture = m_textures.at(texture_index);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glUseProgram(m_program);

    glUniform1i(drawmodef, 0);
    glUniform1i(drawmodev, 4);

    glUniform4f(glGetUniformLocation(m_program, "texturerect"), rect.x, rect.y, rect.z, rect.w);

    glBindVertexArray(m_vao);


    GLint vertexdata = glGetAttribLocation(m_program, "vertexdata");

    glVertexAttribPointer(vertexdata, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

    glEnableVertexAttribArray(vertexdata);


    m_scale = texture->get_scale();

    //std::cout << "scale: " << texture->get_scale() << std::endl;

    float aspect_ratio_hw = (float)texture->get_height() / (float)texture->get_width();

    float aspect_ratio_wh = (float)texture->get_width() / (float)texture->get_height();

    float ratio_minmax = NULL;

    float aspectRatios_wh = static_cast<float>(m_width) / static_cast<float>(m_height);

    float aspectRatios_hw = static_cast<float>(m_height) / static_cast<float>(m_width);



    //std::cout << "texture " << i << ": " << texture->get_rotation() << std::endl;



    if (texture->get_height() > texture->get_width())
    {
        ratio_minmax = glm::max(aspect_ratio_hw, aspect_ratio_wh);
    }
    if (texture->get_height() <= texture->get_width())
    {
        ratio_minmax = glm::min(aspect_ratio_hw, aspect_ratio_wh);
    }


    float texture_width = (2.0f * (float)texture->get_width()) / (float)m_width;
    float texture_height = (2.0f * (float)texture->get_height()) / (float)m_height;

    glm::mat4 transform = glm::mat4(1.0f);


    glm::vec2 position(0.0f, 0.0f);


    float angle = 45.0f;

    glm::vec3 axis(0.0f, 0.0f, 1.0f);


    glm::mat4 rotation = glm::mat4(1.0f);


    rotation = glm::translate(rotation, glm::vec3(texture->get_pos_x(), texture->get_pos_y(), 1.0f));


    rotation = glm::translate(rotation, -glm::vec3(position, 1.0f));

    float ratio_minmax_x = NULL, ratio_minmax_y = NULL;

    if (m_height > m_width)
    {
        ratio_minmax_x = aspectRatios_hw;
        ratio_minmax_y = aspectRatios_hw;

    }
    if (m_height < m_width)
    {
        ratio_minmax_x = aspectRatios_hw;
        ratio_minmax_y = 1.0f;

    }

    rotation = glm::scale(rotation, glm::vec3(GetScreenRatio().x, GetScreenRatio().y, 1.0f));

    if (m_height > m_width)
    {
        rotation = glm::scale(rotation, glm::vec3(0.5f, 0.5f, 1.0f));
    }

    rotation = glm::rotate(rotation, glm::radians(texture->get_rotation()), (glm::vec3)axis);

    rotation = glm::scale(rotation, glm::vec3(m_scale, m_scale, 1.0f));

    rotation = glm::scale(rotation, glm::vec3(1.0f, ratio_minmax, 1.0f));

    // Translate to its original position
    rotation = glm::translate(rotation, glm::vec3(position, 1.0f));

    //std::cout << "texture ratio " << texture_index << ": " << ratio_minmax << std::endl;

    GLfloat aspectRatio = m_width / m_height;
    //glm::mat4 mat_projection = glm::ortho(-1.0f, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);

    float x = 0.5f;
    float y = 0.5f;

    transform = rotation * transform;


    glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, glm::value_ptr(rotation));


    float ratio_temp = ((float)texture->get_width() / (float)texture->get_height());


    char name[] = "tex";
    glUniform1i(glGetUniformLocation(m_program, name), texture->GetTextureIndex());
    texture->bind(GL_TEXTURE0 + texture->GetTextureIndex());


    //Draw
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glBindTexture(GL_TEXTURE_2D, 0);

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Hemlock::SetWindowIcon(const char* filepath)
{
    GLFWimage images;
    images.pixels = stbi_load(filepath, &images.width, &images.height, 0, 4);
    glfwSetWindowIcon(m_window, 1, &images);
    stbi_image_free(images.pixels);

}

void Hemlock::drawRectangle(size_t primitive_index)
{
    HemlockPrimitive* primitive = primitives.at(primitive_index);

    if (primitive->GetPrimitiveType() == RECTANGLE)
    {
        //glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, rect_vbo);

        glUseProgram(m_program);

        glUniform1i(drawmodef, 1);
        glUniform1i(drawmodev, 1);

        glBindVertexArray(rect_vao);

        // Allocate memory for the VBO and upload the vertex data
        //glBufferData(GL_ARRAY_BUFFER, dataSize, rectangle_vertices, GL_DYNAMIC_DRAW);

        GLint vertexdata = glGetAttribLocation(m_program, "vertexdata");

        glVertexAttribPointer(vertexdata, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

        glEnableVertexAttribArray(vertexdata);

        //glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &buffersize);
       
        glm::vec2 position(0.0f, 0.0f);

        
        glm::mat4 transformation = glm::mat4(1.0f);

        glm::mat4 projection = glm::mat4(1.0f);

        projection = glm::ortho(-1, 1, -1, 1, 1, -1);

        glm::mat4 move = glm::mat4(1.0f);

        glm::mat4 custom = glm::mat4(1.0f);
        
        move = glm::translate(move, glm::vec3(primitive->GetPosition().x, primitive->GetPosition().y, 1.0f));

        custom = translate(glm::vec3(primitive->GetPosition().x, primitive->GetPosition().y, 1.0f));

        //translate to center
        transformation = glm::translate(transformation, -glm::vec3(position, 1.0f));



        glm::mat4 screenratio = glm::mat4(1.0f);

        screenratio = glm::scale(screenratio, glm::vec3(GetScreenRatio().x, GetScreenRatio().y, 1.0f));



        if (m_height > m_width)
        {
            transformation = glm::scale(transformation, glm::vec3(0.5f, 0.5f, 1.0f));
        }
        
        transformation = glm::rotate(transformation, glm::radians(primitive->GetRotation()), glm::vec3(0.0f, 0.0f, 1.0f));

        //Scale by only a single value
        transformation = glm::scale(transformation, glm::vec3(primitive->GetScale(), primitive->GetScale(), 1.0f));
        

        //Scale by the ratio given in
        transformation = glm::scale(transformation, glm::vec3(primitive->GetScaleRatio().x, primitive->GetScaleRatio().y, 1.0f));



        //translate back to its position
        transformation = glm::translate(transformation, glm::vec3(position, 1.0f));

        
        glm::mat4 final_trans = move * screenratio * transformation;
        

        glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, glm::value_ptr(final_trans));



        glUniform4f(colorpr, primitive->GetColor().x, primitive->GetColor().y, primitive->GetColor().z, primitive->GetColor().w);

        //std::cout << "Buffer size: " << buffersize << std::endl;

        
        //Draw
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    else
    {
        return;
    }
}

void Hemlock::DrawInstancedRectangles()
{
    glUseProgram(m_program);

    glUniform1i(drawmodef, 3);
    glUniform1i(drawmodev, 3);

    // Create the vertex data
    float vertices[] = {
        // positions      // texture coordinates
         0.5f,  0.5f,    1.0f, 0.0f, // top right
         0.5f, -0.5f,    1.0f, 1.0f, // bottom right
        -0.5f, -0.5f,    0.0f, 1.0f, // bottom left
        -0.5f,  0.5f,    0.0f, 0.0f  // top left
    };

    int datasize = sizeof(vertices);
    int buffersize;





}

void Hemlock::DrawFrame(size_t primitive_index, Vec4<float> color)
{

    static bool bufferloaded = false;
    //primitive* primitive = primitives.at(primitive_index);

    glUseProgram(m_program);

    glUniform1i(glGetUniformLocation(m_program, "modev"), 1);
    glUniform1i(glGetUniformLocation(m_program, "modef"), 1);

    glUniform4f(glGetUniformLocation(m_program, "colorpr"), color.x, color.y, color.z, color.w);

    glBindVertexArray(crossvao);

    glBindBuffer(GL_ARRAY_BUFFER,crossvbo);

    
    float* vertices;
    int* indices;

    static int sizeofind = NULL;

    if (!bufferloaded)
    {
        //std::cout << "HERE INSIDE" << std::endl;

       /* float vertices1[] = {
              0.6f, 0.6f,  //top right corner of rectangle 1
              0.6f, -0.6f,   // bottom right corner of rectangle 1
             -0.6f, -0.6f,   // bottom left corner of rectangle 1
             -0.6f, 0.6f, // top left corner of rectangle 1

              0.5f, 0.5f,   // top right corner of rectangle 2
              0.5f, -0.5f,   // bottom right corner of rectangle 2
             -0.5f, -0.5f,   // bottom left corner of rectangle 2
             -0.5f, 0.5f  // top left corner of rectangle 2
        };

        int indices1[] = {
        0, 1, 4,
        1, 5, 4,
        1, 2, 5,
        2, 6, 5,
        2, 3, 6,
        3, 7, 6,
        3, 0, 7,
        0, 4, 7,
        }; */
        
        float vertices1[] = {
          0.0f, 0.5f,  // vertex 0
       0.35f, 0.35f,  // vertex 1
    0.5f, 0.0f,  // vertex 2
    0.35f, -0.35f,  // vertex 3
    0.0f, -0.5f,  // vertex 4
    -0.35f, -0.35f,  // vertex 5
    -0.5f, 0.0f,  // vertex 6
    -0.35f, 0.35f  // vertex 7
        };

        unsigned int indices1[] = {
            0, 1, 2,
            0, 2, 3,
            0, 3, 4,
            0, 4, 5,
            0, 5, 6,
            0, 6, 7,
            0, 7, 1
        };
        
       // vertices = vertices1;
        //indices = indices1;

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, crossebo);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

        sizeofind = sizeof(indices1) / sizeof(unsigned int);

        bufferloaded = true;
    }

   if (bufferloaded)
   {
       glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, crossebo);
   }
    

    GLint vertexdata = glGetAttribLocation(m_program, "vertexdata");

    glVertexAttribPointer(vertexdata, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    glEnableVertexAttribArray(vertexdata);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glDrawElements(GL_TRIANGLE_FAN, sizeofind, GL_UNSIGNED_INT, 0);

   
    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glUseProgram(0);


}

void Hemlock::VisualizeCollisionBox(CollisionBox *Collisionbox,Vec4<float> color)
{

    GLint shaderprogram = m_program;

    glUseProgram(shaderprogram);

    glUniform1i(glGetUniformLocation(shaderprogram, "modev"), 3);
    glUniform1i(glGetUniformLocation(shaderprogram, "modef"), 1);

    glUniform4f(glGetUniformLocation(shaderprogram, "colorpr"), color.x, color.y, color.z, color.w);


    glBindVertexArray(colvao);

    glBindBuffer(GL_ARRAY_BUFFER, colvbo);

    rect* cb = Collisionbox->GetCollisionRect();

    float vertex_array[] = {

        (cb->x + (cb->width / 2)) , (cb->y - (cb->height / 2)),
        (cb->x + (cb->width / 2)) , (cb->y + (cb->height / 2)),
        (cb->x - (cb->width / 2)) , (cb->y + (cb->height / 2)),
        (cb->x - (cb->width / 2)) , (cb->y - (cb->height / 2))

    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_array), vertex_array, GL_STATIC_DRAW);

    GLint posAttrib = glGetAttribLocation(shaderprogram, "position");

    glEnableVertexAttribArray(posAttrib);

    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);


    glDrawArrays(GL_LINE_LOOP, 0, 4);

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glUseProgram(0);



}

void Hemlock::drawCircle(int16 vertices_count, size_t primitive_index)
{
    HemlockPrimitive* primitive = primitives.at(primitive_index);

    if (primitive->GetPrimitiveType() == CIRCLE)
    {
        const int NUM_SEGMENTS = vertices_count;
        const float RADIUS = 0.5f;
        static int segment_counter = 0;

        std::vector<float> circle_vertices;

        std::vector<GLuint> indices;

   
        glUseProgram(m_program);

        glUniform1i(drawmodef, 1);
        glUniform1i(drawmodev, 1);

        
        
        glBindVertexArray(circle_vao); 

        glBindBuffer(GL_ARRAY_BUFFER, circle_vbo);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, circle_ibo);

        
   
        if (NUM_SEGMENTS != segment_counter)
        {
            
            segment_counter = NUM_SEGMENTS;

            float angleStep = 2.0f * M_PI / NUM_SEGMENTS;
            for (int i = 0; i <= NUM_SEGMENTS; i++) {

                float x = RADIUS * cosf(i * angleStep);
                float y = RADIUS * sinf(i * angleStep);
                circle_vertices.push_back(x);
                circle_vertices.push_back(y);

                
            }

           
            for (int i = 0; i <NUM_SEGMENTS; ++i) {
                indices.push_back(0);
                indices.push_back(i + 1);
                indices.push_back(i + 2 > NUM_SEGMENTS ? 1 : i + 2);
            }

            glBufferData(GL_ARRAY_BUFFER, circle_vertices.size() * sizeof(float), circle_vertices.data(), GL_DYNAMIC_DRAW);
            
           
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices, GL_DYNAMIC_DRAW);

          
        }

    
        GLint vertexdata = glGetAttribLocation(m_program, "vertexdata");

        glVertexAttribPointer(vertexdata, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

        glEnableVertexAttribArray(vertexdata);
        
  
        glm::vec2 position(0.0f, 0.0f);


        glm::mat4 transformation = glm::mat4(1.0f);

        glm::mat4 projection = glm::mat4(1.0f);

        projection = glm::ortho(-1, 1, -1, 1, 1, -1);

        glm::mat4 move = glm::mat4(1.0f);

        glm::mat4 custom = glm::mat4(1.0f);

        move = glm::translate(move, glm::vec3(primitive->GetPosition().x, primitive->GetPosition().y, 1.0f));

        custom = translate(glm::vec3(primitive->GetPosition().x, primitive->GetPosition().y, 1.0f));

        //translate to center
        transformation = glm::translate(transformation, -glm::vec3(position, 1.0f));

        glm::mat4 screenratio = glm::mat4(1.0f);

        screenratio = glm::scale(screenratio, glm::vec3(GetScreenRatio().x, GetScreenRatio().y, 1.0f));



        if (m_height > m_width)
        {
            transformation = glm::scale(transformation, glm::vec3(0.5f, 0.5f, 1.0f));
        }

        transformation = glm::rotate(transformation, glm::radians(primitive->GetRotation()), glm::vec3(0.0f, 0.0f, 1.0f));

        //Scale by only a single value
        transformation = glm::scale(transformation, glm::vec3(primitive->GetScale(), primitive->GetScale(), 1.0f));


        //Scale by the ratio given in
        transformation = glm::scale(transformation, glm::vec3(primitive->GetScaleRatio().x, primitive->GetScaleRatio().y, 1.0f));



        //translate back to its position
        transformation = glm::translate(transformation, glm::vec3(position, 1.0f));

        glm::mat4 final_trans = move * screenratio * transformation;


        glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, glm::value_ptr(final_trans));

        glUniform4f(glGetUniformLocation(m_program, "colorpr"), primitive->GetColor().x, primitive->GetColor().y, primitive->GetColor().z, primitive->GetColor().w);


        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        glDrawArrays(GL_TRIANGLE_FAN, 0, vertices_count+1);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glUseProgram(0);
        //glDisableClientState(vertexdata);

    }
    else
    {
        return;
    }
}

void Hemlock::InitTextRendering()
{
    
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
}

void Hemlock::Loadfont(const char* filename, int pixelsize)
{
    if (!fontt.face)
    {

        if (FT_New_Face(ft, filename, 0, &fontt.face))
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

        // Set size to load glyphs as
        FT_Set_Pixel_Sizes(fontt.face, 0, pixelsize);

        // Disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // Load first 128 characters of ASCII set
        for (GLubyte c = 0; c < 128; c++)
        {
            // Load character glyph 
            if (FT_Load_Char(fontt.face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // Generate texture
            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                fontt.face->glyph->bitmap.width,
                fontt.face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                fontt.face->glyph->bitmap.buffer
            );
            // Set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // Now store character for later use
            Characterr* character = new Characterr;
            character->SET(
                texture,
                glm::ivec2(fontt.face->glyph->bitmap.width, fontt.face->glyph->bitmap.rows),
                glm::ivec2(fontt.face->glyph->bitmap_left, fontt.face->glyph->bitmap_top),
                fontt.face->glyph->advance.x
            );

            Characters.insert(std::pair<const GLchar, Characterr*>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        // Destroy FreeType once we're finished
        FT_Done_Face(fontt.face);
        FT_Done_FreeType(ft);

        // Configure VAO/VBO for texture quads
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

        GLint vertexdata = glGetAttribLocation(m_program, "vertexdata");

        glVertexAttribPointer(vertexdata, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

        glEnableVertexAttribArray(vertexdata);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        fontt.SetTextureIndex(m_textures.size() - 1);

    }
}

void Hemlock::RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, Vec3<float> color)
{
    
    if (fontt.face)
    {

        glUseProgram(m_program);

        glUniform1i(glGetUniformLocation(m_program, "modev"), 2);
        glUniform1i(glGetUniformLocation(m_program, "modef"), 2);

        glUniform4f(glGetUniformLocation(m_program, "colorpr"), color.x, color.y, color.z, 1.0f);

        //glm::mat4 screenratiomat = glm::mat4(1.0f);

        //screenratiomat = glm::scale(screenratiomat, glm::vec3(GetScreenRatio().x, GetScreenRatio().y, 1.0f));

        //glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, glm::value_ptr(screenratiomat));

        //glActiveTexture(GL_TEXTURE1);

        glBindVertexArray(VAO);

        // Iterate through all characters
        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++)
        {
            Characterr ch = *Characters[*c];

            GLfloat xpos = x + ch.Bearing.x * scale;
            GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

            GLfloat w = ch.Size.x * scale;
            GLfloat h = ch.Size.y * scale;
            // Update VBO for each character
            GLfloat vertices[6][4] = {
                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos,     ypos,       0.0, 1.0 },
                { xpos + w, ypos,       1.0, 1.0 },

                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos + w, ypos,       1.0, 1.0 },
                { xpos + w, ypos + h,   1.0, 0.0 }
            };
            // Render glyph texture over quad

            glBindTexture(GL_TEXTURE_2D, ch.TextureID);

            // Update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // Render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);

            glBindTexture(GL_TEXTURE_2D, 0);
            // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64
        }
        glBindVertexArray(0);
        glUseProgram(0);
    }
    
}


