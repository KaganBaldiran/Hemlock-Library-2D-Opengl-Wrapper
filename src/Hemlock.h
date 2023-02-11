#pragma once
#include "Texture.h"
#include <vector>
#include <memory>
#include <map>


//Key codes to use for input handling 
#define KEY_UP 265
#define KEY_DOWN 264
#define KEY_LEFT 263
#define KEY_RIGHT 262
#define KEY_SPACE  32
#define KEY_LEFT_ALT 342
#define KEY_MOUSE_LEFT 0
#define KEY_MOUSE_RIGHT 1
#define KEY_LEFT_SHIFT 340
#define KEY_APOSTROPHE 39
#define KEY_COMMA 44
#define KEY_MINUS 45
#define KEY_PERIOD 46
#define KEY_SLASH 47
#define KEY_0 48
#define KEY_1 49
#define KEY_2 50
#define KEY_3 51
#define KEY_4 52
#define KEY_5 53
#define KEY_6 54
#define KEY_7 55
#define KEY_8 56
#define KEY_9 57
#define KEY_SEMICOLON 59
#define KEY_EQUAL 61
#define KEY_A 65
#define KEY_B 66
#define KEY_C 67
#define KEY_D 68
#define KEY_E 69
#define KEY_F 70
#define KEY_G 71
#define KEY_H 72
#define KEY_I 73
#define KEY_J 74
#define KEY_K 75
#define KEY_L 76
#define KEY_M 77
#define KEY_N 78
#define KEY_O 79
#define KEY_P 80
#define KEY_Q 81
#define KEY_R 82
#define KEY_S 83
#define KEY_T 84
#define KEY_U 85
#define KEY_V 86
#define KEY_W 87
#define KEY_X 88
#define KEY_Y 89
#define KEY_Z 90
#define KEY_LEFT_BRACKET 91
#define KEY_BACKSLASH 92
#define KEY_RIGHT_BRACKET 93
#define KEY_GRAVE_ACCENT 96
#define KEY_WORLD_1 161
#define KEY_WORLD_2 162
#define KEY_ESCAPE 256 
#define KEY_ENTER 257
#define KEY_TAB 258
#define KEY_BACKSPACE 259
#define KEY_INSERT 260
#define KEY_DELETE 261
#define KEY_PAGE_UP 266
#define KEY_PAGE_DOWN 267
#define KEY_HOME 268
#define KEY_END 269
#define KEY_CAPS_LOCK 280
#define KEY_SCROLL_LOCK 281
#define KEY_NUM_LOCK 282
#define KEY_PRINT_SCREEN 283
#define KEY_PAUSE 284
#define KEY_F1 290
#define KEY_F2 291
#define KEY_F3 292
#define KEY_F4 293
#define KEY_F5 294
#define KEY_F6 295
#define KEY_F7 296
#define KEY_F8 297
#define KEY_F9 298
#define KEY_F10 299
#define KEY_F11 300
#define KEY_F12 301
#define KEY_F13 302
#define KEY_F14 303
#define KEY_F15 304
#define KEY_F16 305
#define KEY_F17 306
#define KEY_F18 307
#define KEY_F19 308
#define KEY_F20 309
#define KEY_F21 310
#define KEY_F22 311
#define KEY_F23 312
#define KEY_F24 313
#define KEY_F25 314
#define KEY_KP_0 320
#define KEY_KP_1 321
#define KEY_KP_2 322
#define KEY_KP_3 323
#define KEY_KP_4 324
#define KEY_KP_5 325
#define KEY_KP_6 326
#define KEY_KP_7 327
#define KEY_KP_8 328
#define KEY_KP_9 329
#define KEY_KP_DECIMAL 330
#define KEY_KP_DIVIDE 331
#define KEY_KP_MULTIPLY 332
#define KEY_KP_SUBTRACT 333
#define KEY_KP_ADD 334
#define KEY_KP_ENTER 335
#define KEY_KP_EQUAL 336
#define KEY_LEFT_CONTROL 341
#define KEY_LEFT_SUPER 343
#define KEY_RIGHT_SHIFT 344
#define KEY_RIGHT_CONTROL 345
#define KEY_RIGHT_ALT 346
#define KEY_RIGHT_SUPER 347
#define KEY_MENU 348
#define KEY_LAST 348


//Forward declarations in order to avoid includes in the header file
typedef unsigned int GLuint;
typedef int GLint;
typedef float GLfloat;
typedef char GLchar;
typedef int WINDOWHINTS;
typedef short int int16;
typedef float kb_float;


#define WINDOW_RESIZEABLE 0x00020003
#define WINDOW_VISIBLE 0x00020004
#define WINDOW_DECORATED 0x00020005
#define WINDOW_AUTO_ICONIFY 0x00020006
#define WINDOW_FLOATING 0x00020007
#define WINDOW_MAXIMIZED 0x00020008
#define WINDOW_FOCUSED 0x00020001
#define WINDOW_ICONIFIED 0x00020002
#define WINDOW_CENTER_CURSOR 0x00020009
#define WINDOW_HOVERED 0x0002000B
#define WINDOW_FOCUS_ON_SHOW 0x0002000C
#define WINDOW_RED_BITS 0x00021001
#define WINDOW_GREEN_BITS 0x00021002
#define WINDOW_BLUE_BITS 0x00021003
#define WINDOW_ALPHA_BITS 0x00021003
#define WINDOW_DEPTH_BITS 0x00021005
#define WINDOW_STENCIL_BITS 0x00021006
#define WINDOW_ACCUM_GREEN_BITS 0x00021008
#define WINDOW_ACCUM_BLUE_BITS 0x00021009
#define WINDOW_ACCUM_ALPHA_BITS 0x0002100A
#define WINDOW_AUX_BUFFERS 0x0002100B
#define WINDOW_STEREO 0x0002100C
#define WINDOW_SAMPLES 0x0002100D
#define WINDOW_SRGB_CAPABLE 0x0002100E


class CollisionBox;

struct Characterr;
struct GLFWwindow;

struct FT_FaceRec_;
typedef struct FT_FaceRec_* FT_Face;

struct FT_LibraryRec_;
typedef struct FT_LibraryRec_* FT_Library;



class font : public OPENGL_TEXTURE_UNIT
{
public:

	FT_Face face;

};

class UserData
{
public:

	int texture_count;
	
};

//Main class which has all the rendering functions.
//Every instance of this class possesses a window and an opengl context.
class Hemlock {
public:

	~Hemlock();

	void InitializeRenderer(const char* Window_name, int window_width, int window_height, bool Enable_anti_aliasing);
	//Insert a new texture to the buffer to render.
	//Inserted textures are required to be rendered by DrawTexture function later on.
	void addTexture(const char* filename);
	//Gives the last inserted textures ID.
    //If there is no texture inserted , it returns -10.
	int GetLastTextureID();
	//Returns a pointer to the texture with the desired index number.
	//You can use the texture class specific functions using this pointer. 
	HemlockTexture *GetTexture(size_t index);
	//Initializes vertex and fragment shader along with buffers.
	//Needs to be initialized before doing any rendering. 
	void InitShaders();
	//Function with no use anymore.
	//Due to be deleted soon.
	void setScale(float scale);
	//Swaps buffers and polls events.
	//Other than swaping buffers thus rendering , it's also required to make context responsive.
	void render();
	//Clears the screen with desired color.
	void clearscreen(Vec4<float> color);
	//Isn't implemented yet
	void DrawLine(float x1, float y1, float x2, float y2, float thickness, Vec3<float> color);

	//Return a pointer to the shader program currently in use.
	GLuint *returnshader() { return &m_program; };

	//Internal function used to scale objects according the screen.
	Vec2<float> GetScreenRatio();
	
	//Returns a pointer to the primitive with the desired index number.
	//You can use the primitive class specific functions using this pointer. 
	HemlockPrimitive* GetPrimitive(size_t index);
	//Insert a new primitive to the buffer to render.
	//Inserted primitives are required to be rendered by respective primitive rendering functions later on.
	void AddPrimitive(int Primitive_Type, Vec4<float> color);
	//Gives the last inserted primitives ID.
	//If there is no primitive inserted , it returns -10.
	int GetLastPrimitiveID();
	//Renders the triangle primitive with the desired index number.
	//The triangle that is drawn possesses attributes(size,position,color,rotation) of the triangle with the index given.
	void drawTriangle(size_t primitive_index);
	//Renders the texture with the desired index number.
	//The texture that is drawn possesses attributes(size,position,color,rotation) of the texture with the index given.
	void DrawTexture(size_t texture_index);
	//Renders the texture with the desired index number. Also crops the texture according to the rect data given in.
	//The texture that is drawn possesses attributes(size,position,color,rotation) of the texture with the index given.
	//Might be useful for 2D atlas animations.
	void DrawTextureRect(size_t texture_index , Vec4<float> rect);

	//void DrawCross(size_t primitive_index);
	
	//Sets the given image as the window icon
	void SetWindowIcon(const char* filepath);
	
	//Renders the rectangle with the desired index number.
	//The rectangle that is drawn possesses attributes(size,position,color,rotation) of the rectangle with the index given.
	void drawRectangle(size_t primitive_index);
	//Isnt implemented yet.
	void DrawInstancedRectangles();

	void DrawFrame(size_t primitive_index, Vec4<float> color);

	//Visualize the collision box on the screen.
	//Use returnshader() function for shader argument
	void VisualizeCollisionBox(CollisionBox* Collisionbox,Vec4<float> color);

	//Renders the circle with the desired index number.
	//The circle that is drawn possesses attributes(size,position,color,rotation) of the rectangle with the index given.
	void drawCircle(int16 vertices_count , size_t primitive_index);

	//Initializes text rendering mode.
	//Should be initialized after shaders are initialized.
	void InitTextRendering();
	//Load an external font file to render.
	//Currently only one font can be rendered at a time.
	//Will be updated.
	void Loadfont(const char* filename, int pixelsize);
	//Render a custom text on the screen.
	//UniCode isn't on currently.
	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, Vec3<float> color);

	//Returns a pointer to the window thats currently in use.
	GLFWwindow *return_window();
	//Detects if the key given is pressed at the moment.
	//If it's the case returns 1. If not returns 0.
	bool IsKeyPressed(int key);
	//Detects if the mouse button given is pressed at the moment.
	//If it's the case returns 1. If not returns 0.
	bool IsMouseButtonPressed(int button);
	//Detects if the mouse button given is released at the moment.
	//If it's the case returns 1. If not returns 0.
	bool IsMouseButtonReleased(int button);
	//Maximizes the window and the contex to maximum monitor size.
	void MaximizeWindow();
	//Returns two double values corresponding to the current mouse position in screen coordinates.
	Vec2<double> GetMousePosScreencords();
	//Returns two double values corresponding to the current mouse position in OPENGLs native world coordinates.
	Vec2<double> GetMousePosGLcords();
	//
	Vec2<float> Screen2WorldCoords(Vec2<float> Screencords);
	//Clamps the fps at desired value.
	//First value returns '1' value desired times a second.
	//Second value returns the current fps. 
	std::pair<bool,float> SetFps(int fps);
	//Detects changes on window size and scales the opengl context accordingly.
	void framebuffer_size_recall();
	//Checks the current window and if it's requested to be closed by the user , returns a flag.
	//Can be used to keep the main loop going.
	int WindowShouldClose();
	//Returns two int values corresponding to the window width and height respectively.
	Vec2<int> GetWindowSize();

	
	//Set the scale of the texture with desired index.
	void SetTextureAttrib(size_t texture_index, long float scale);
	//Set the position of the texture with desired index.Set by screen coordinates.
	void SetTextureAttrib(size_t texture_index, Vec2<float> position);
	//Set the rotation of the texture with desired index.
	void SetTextureAttrib(size_t texture_index, float rotation);


	//Set the scale of the primitive with desired index.
	void SetPrimitiveAttrib(size_t primitive_index, long float scale);
	//Set the position of the primitive with desired index.Set by screen coordinates.
	void SetPrimitiveAttrib(size_t primitive_index, Vec2<float> position);
	//Set the rotation of the primitive with desired index.
	void SetPrimitiveAttrib(size_t primitive_index, float rotation);

	//Checks collision between a collision box and mouse cursor.
	//Returns true if they collide.
	template<typename T>
	inline bool CheckCollisionBoxCursor(CollisionBox* colboxtocheck, Vec2<float> improveboxscale)
	{
		if (typeid(T).name() == typeid(HemlockPrimitive).name())
		{
			HemlockPrimitive* box = GetPrimitive(colboxtocheck->GetEntityId());

			CollisionBox colbox_to_check = *colboxtocheck;
			
			colbox_to_check.BindCollisionBox(box);

			rect* tb = GetPrimitive(colbox_to_check.GetEntityId())->GetCollusionBox();

			if ((GetMousePosGLcords().x < (tb->x + ((tb->width + improveboxscale.x) / 2))) && (GetMousePosGLcords().x > (tb->x - ((tb->width + improveboxscale.x) / 2))))
			{

				if ((GetMousePosGLcords().y < (tb->y + ((tb->height + improveboxscale.y) / 2))) && (GetMousePosGLcords().y > (tb->y - ((tb->height + improveboxscale.y) / 2))))
				{

					return true;

				}
			}
		}

		if (typeid(T).name() == typeid(HemlockTexture).name())
		{
			HemlockTexture* button = GetTexture(colboxtocheck->GetEntityId());

			CollisionBox colbox_to_check = *colboxtocheck;

			colbox_to_check.BindCollisionBox(button);

			rect* tb = GetTexture(colbox_to_check.GetEntityId())->GetCollisionBox();

			if ((GetMousePosGLcords().x < (tb->x + (tb->width / 2))) && (GetMousePosGLcords().x > (tb->x - (tb->width / 2))))
			{

				if ((GetMousePosGLcords().y < (tb->y + (tb->height / 2))) && (GetMousePosGLcords().y > (tb->y - (tb->height / 2))))
				{

					return true;

				}
			}
		}


		return false;
	};

	//Checks collison between two collision boxes.
	//Returns true if they collide.
	bool CheckCollisionBoxBox(CollisionBox* colboxtocheck1, CollisionBox* colboxtocheck2);
	
	//Sets attributes of the window.
	//Should be called before the window is created.
	int SetWindowHint(WINDOWHINTS hint,bool value);


private:

	GLint m_rotation;
	GLuint m_program;
	GLuint m_vbo;
	GLuint m_vao;
	GLint m_transformLocation;
	GLFWwindow* m_window;

	float m_scale;
	GLint m_xPosLocation;
	GLint m_yPosLocation;
	GLfloat m_x_y_ratio;
	GLfloat t_width;
	GLfloat t_height;
	int m_width;
	int m_height;
	

	std::vector<HemlockTexture*> m_textures;
	std::vector<HemlockPrimitive*> primitives;

	std::vector<std::pair<WINDOWHINTS,bool>*> Windowhints;

	GLuint drawmodef;
	GLuint drawmodev;

	//Font rendering
	std::map<GLchar, Characterr*> Characters;
	GLuint VAO, VBO;
	GLuint rect_vbo, rect_vao , tria_vbo , tria_vao , circle_vao , circle_vbo , circle_ibo;
	GLuint colvbo, colvao , crossvbo , crossvao , crossebo;
	FT_Library ft;
	FT_Face face;
	font fontt;
	

	GLuint colorpr;


	UserData userdata;


};



