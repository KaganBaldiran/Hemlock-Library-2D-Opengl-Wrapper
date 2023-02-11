#pragma once
#include <bitset>
#include <iostream>
#define TRIANGLE 1
#define RECTANGLE 2
#define CIRCLE 3

//Forward declarations in order to avoid includes in the header file
typedef unsigned int GLuint;
typedef int GLint;
typedef float GLfloat;
typedef char GLchar;
typedef unsigned int GLenum;


class OPENGL_TEXTURE_UNIT;
class HemlockTexture;
class HemlockPrimitive;
class CollisionBox;

template<typename type_n>
struct Vec2
{
	type_n x;
	type_n y;
};

class rect
{
public:

	float x, y;
	float width, height;

};






template<typename type_n>
struct Vec3
{
	type_n x;
	type_n y;
	type_n z;

};

template<typename type_n>
struct Vec4
{
	type_n x;
	type_n y;
	type_n z;
	type_n w;
};

class OPENGL_TEXTURE_UNIT
{
public:

	void SetTextureIndex(int index);
	int GetTextureIndex();

private:

	int texture_index;

};

class HemlockTexture: public OPENGL_TEXTURE_UNIT{
public:

	HemlockTexture(const char* filename);
	~HemlockTexture();

	void bind(GLenum textureUnit);
	void setScale(float scale);
	void setpos_x(float xpos);
	void setpos_y(float ypos);
	void update_destrect(rect desrect);
	void rotate(float degrees);
	float get_pos_x();
	float get_pos_y();
	float get_scale();
	float get_rotation();
	rect* GetCollisionBox();
	rect *get_desrectm();
	int get_width();
	int get_height();

	int* ReturnTextureid();
	
	rect* newpositionrect;

private:

	float m_ratio;
	GLuint m_tex;
	float x_pos;
	float y_pos;
	int m_width;
	int m_height;
	float m_scale;
	float m_rotation = 0;
	rect *desrect;

	int textureid;
	
	
};

class HemlockPrimitive {

public:

	HemlockPrimitive(int primitive_type , Vec4<float> color):primitive_type(primitive_type),scale_ratio({1.0f,1.0f}), x_pos(0.0f), y_pos(0.0f), pr_color(color), m_scale(1.0f), newpositionrect(new rect){};
	
	~HemlockPrimitive();

	int GetPrimitiveType();
	Vec4<float> GetColor() { return pr_color; };


	void SetPrimitivePosition(Vec2<float> position);
	void SetPrimitiveScale(float scale);
	void SetPrimitiveScaleRatio(float width_scale , float height_scale);
	void SetPrimitiveColor(Vec4<float> color);
	void Rotate(float degrees);

	int* ReturnPrimitiveid() { return &primitive_id; };

	Vec2<float> GetPosition();
	float GetScale();
	float GetRotation();
	Vec2 <float> GetScaleRatio();

	rect* GetCollusionBox() { return newpositionrect; };

    rect* newpositionrect;

private:

	int primitive_type;
	Vec4<float> pr_color;

	float x_pos;
	float y_pos;
	int m_width;
	int m_height;
	float m_scale;
	float m_rotation = 0;
	Vec2<float> scale_ratio;

	Vec4<float> *Primitive_Rect;

	int primitive_id;


};


class CollisionBox
{
public:

	CollisionBox();
	~CollisionBox();
	//Avaluate the collision box.
	//For screenratio argument , use GetScreenRatio() function.
	void SetCollisionBox(float x, float y, float width, float height, Vec2<float> screenratio);

	//Get a pointer to the rect that holds the box data
	rect* GetCollisionRect() { return &collisionbox; };

	int GetEntityId() { return entity_id; };

	//Avaluate the collision box.
	//For screenratio argument , use GetScreenRatio() function.
	template<typename entitytype>
	inline void SetCollisionBox(entitytype* pointer_to_object , Vec2<float> screenratio)
	{

		HemlockPrimitive* tempp;
		if (typeid(pointer_to_object).name() == typeid(tempp).name())
		{
			
			tempp = (HemlockPrimitive*)pointer_to_object;

			float ratiox = tempp->GetScaleRatio().y / tempp->GetScaleRatio().x;
			float ratioy = tempp->GetScaleRatio().x / tempp->GetScaleRatio().y;

			if (tempp->GetScaleRatio().x > tempp->GetScaleRatio().y)
			{
				std::cout << "SCALE RATIO Y: " << tempp->GetScaleRatio().y << " SCALE RATIO X: " << tempp->GetScaleRatio().x << std::endl;
				SetCollisionBox(tempp->GetPosition().x, tempp->GetPosition().y, (tempp->GetScale() * 1.0f ), (tempp->GetScale() * 1.0f / ratioy ), screenratio);

			}
			if (tempp->GetScaleRatio().x < tempp->GetScaleRatio().y)
			{
				SetCollisionBox(tempp->GetPosition().x, tempp->GetPosition().y, (tempp->GetScale() * 1.0f / ratiox), (tempp->GetScale() * 1.0f ), screenratio);

			}
			if (tempp->GetScaleRatio().x == tempp->GetScaleRatio().y)
			{
				SetCollisionBox(tempp->GetPosition().x, tempp->GetPosition().y, (tempp->GetScale() * 1.0f ), (tempp->GetScale() * 1.0f), screenratio);

			}

			
			
			
		}

		HemlockTexture* tempt;
		if (typeid(pointer_to_object).name() == typeid(tempt).name())
		{

			tempt = (HemlockTexture*)pointer_to_object;
			SetCollisionBox(tempt->get_pos_x(), tempt->get_pos_y(), (tempt->get_scale() * 1.0f) , (tempt->get_scale() * 1.0f) , screenratio);

		}

	};

	//Assign the collision box to an entity.
	//After binding , controls are set via respective entity
	template<typename entitytype>
	inline int BindCollisionBox(entitytype* pointer_to_object)
	{
		static unsigned int box_id = 0;

		HemlockPrimitive* tempp;
		if (typeid(pointer_to_object).name() == typeid(tempp).name())
		{

			tempp = (HemlockPrimitive*)pointer_to_object;
			tempp->newpositionrect = &collisionbox;

			unsigned int idtemp = box_id;

			box_id++;

			entity_id = *tempp->ReturnPrimitiveid();

			return idtemp;

		}

		HemlockTexture* tempt;
		if (typeid(pointer_to_object).name() == typeid(tempt).name())
		{

			tempt = (HemlockTexture*)pointer_to_object;
			tempt->newpositionrect = &collisionbox;

			unsigned int idtemp = box_id;

			box_id++;

			entity_id = *tempt->ReturnTextureid();

			return idtemp;

		}
		else
		{
			return -1;
		}
	}


private:

	rect collisionbox;
	int entity_id;

};





