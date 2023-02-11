#include "Texture.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


HemlockTexture::HemlockTexture(const char* filename){

    static int texture_count = 0;

    int channels;
    unsigned char* pixels = stbi_load(filename, &m_width, &m_height, &channels, STBI_rgb_alpha);
    if (!pixels) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        return;
    }

    //this->desrect = desrect;

    // Create the texture and bind it
    glGenTextures(1, &m_tex);
    glBindTexture(GL_TEXTURE_2D, m_tex);

    
    // Set the texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    
    stbi_image_free(pixels);

    texture_count++;
    
    x_pos = 0.0f, y_pos = 0.0f, m_scale = 1.0f;
}



HemlockTexture::~HemlockTexture() {

    glDeleteTextures(1, &m_tex);
}

void HemlockTexture::bind(GLenum textureUnit) {
    
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, m_tex);
}

void HemlockTexture::setScale(float scale) {
    m_scale = scale;
}

void HemlockTexture::setpos_x(float xpos)
{
    x_pos = xpos;
}

void HemlockTexture::setpos_y(float ypos)
{
    y_pos = ypos;
}

void HemlockTexture::update_destrect(rect desrect)
{
    this->desrect = &desrect;
}

void HemlockTexture::rotate(float degrees)
{
    m_rotation = degrees;
}

float HemlockTexture::get_pos_x()
{
    return x_pos;
}

float HemlockTexture::get_pos_y()
{
    return y_pos;
}

float HemlockTexture::get_scale()
{
    return m_scale;
}

float HemlockTexture::get_rotation()
{
    return m_rotation;
}

rect* HemlockTexture::GetCollisionBox()
{
    return newpositionrect;
}

rect* HemlockTexture::get_desrectm()
{
    return desrect;
}



int HemlockTexture::get_width()
{
    return m_width;
}

int HemlockTexture::get_height()
{
    return m_height;
}

int* HemlockTexture::ReturnTextureid()
{
    return &textureid;
}


HemlockPrimitive::~HemlockPrimitive()
{
    //delete newpositionrect;
}

int HemlockPrimitive::GetPrimitiveType()
{
    return primitive_type;
}

void HemlockPrimitive::SetPrimitivePosition(Vec2<float> position)
{
    x_pos = position.x;
    y_pos = position.y;
}

void HemlockPrimitive::SetPrimitiveScale(float scale)
{
    m_scale = scale;
}

void HemlockPrimitive::SetPrimitiveScaleRatio(float width_scale, float height_scale)
{
    scale_ratio.x = width_scale;
    scale_ratio.y = height_scale;
}

void HemlockPrimitive::SetPrimitiveColor(Vec4<float> color)
{
    pr_color = color;
}

void HemlockPrimitive::Rotate(float degrees)
{
    m_rotation = degrees;
}

Vec2<float> HemlockPrimitive::GetPosition()
{
    return { x_pos, y_pos };
}

float HemlockPrimitive::GetScale()
{
    return m_scale;
}

float HemlockPrimitive::GetRotation()
{
    return m_rotation;
}

Vec2<float> HemlockPrimitive::GetScaleRatio()
{
    return scale_ratio;
}

void OPENGL_TEXTURE_UNIT::SetTextureIndex(int index)
{
    texture_index = index;
}

int OPENGL_TEXTURE_UNIT::GetTextureIndex()
{
    return texture_index;
}

CollisionBox::CollisionBox()
{
    
}

CollisionBox::~CollisionBox()
{
   
}

void CollisionBox::SetCollisionBox(float x, float y, float width, float height,Vec2<float> screenratio)
{
    collisionbox.x = x;
    collisionbox.y = y;
    collisionbox.width = screenratio.x * width;
    collisionbox.height = screenratio.y * height;

}





