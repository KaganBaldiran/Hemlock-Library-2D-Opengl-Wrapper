Hello if you came all the way here to use my humble renderer , you are a legend!!

Anyways you can link the library respectively with the include and lib directories

For your projects debug mode , link Hemlockd.lib

In order the final exe file to work , don't forget to place the dll files found here in the same directory with the exe file!!


Here is a demo so that you can get to learn how to initialize everything to get to work!!


- Kağan Baldıran


#include "Hemlock.h"
#include "Presets.h"
#include <iostream>
#include <bitset>
#include <cmath>
#include <string>
#include <time.h>
#include <random>

#define MAINCHARACTER 0
#define PHOTOTEXTURE 2
#define RECTA 0
#define TRIA 1


int main() {

	//Initialize systems
	Hemlock renderer;

	renderer.SetWindowHint(WINDOW_RESIZEABLE, true);

	renderer.SetWindowHint(WINDOW_VISIBLE, true);

	renderer.InitializeRenderer("HELLO_WORLD", 1500, 1000, true);

	renderer.SetWindowIcon("C:\\Users\\Isengard\\Desktop\\icon.png");

	renderer.InitShaders();

	renderer.InitTextRendering();

	
	//Add textures , primitives and fonts
	renderer.addTexture("C:\\Users\\kbald\\Desktop\\Projects\\SDL2 PROJECTS\\VS_sdl2_projects\\Hemlock_lib\\x64\\Release\\gamechar.png");

	renderer.addTexture("C:\\Users\\kbald\\Desktop\\Projects\\SDL2 PROJECTS\\VS_sdl2_projects\\Hemlock_lib\\x64\\Release\\gamechar.png");

	renderer.addTexture("C:\\Users\\kbald\\Desktop\\Projects\\SDL2 PROJECTS\\VS_sdl2_projects\\Hemlock_lib\\x64\\Release\\In case you needed this today_.jpg");
	//renderer.addTexture("gamechar.png");

	//renderer.addTexture("gamechar.png");

	//renderer.addTexture("In case you needed this today_.jpg");

	renderer.AddPrimitive(RECTANGLE, { 1.0f,0.0f,0.0f,1.0f });

	renderer.AddPrimitive(CIRCLE, { 1.0f,0.0f,0.0f,1.0f });

	renderer.AddPrimitive(CIRCLE, { 0.0f,1.0f,1.0f,1.0f });

	slider slider;

	slider.InitSlider(0, 1, { 0.0f,0.0f }, { 3.2f,0.4f }, 5.0f, { 10.0f,60.0f }, &renderer);



	renderer.Loadfont("C:\\Users\\kbald\\Desktop\\Projects\\SDL2 PROJECTS\\VS_sdl2_projects\\Hemlock_lib\\x64\\Release\\ShortBaby-Mg2w.ttf", 48);

	//renderer.Loadfont("ShortBaby-Mg2w.ttf", 48);
	
	HemlockPrimitive* colrect = renderer.GetPrimitive(0);

	HemlockTexture* texturerect = renderer.GetTexture(2);

	float tex3_scale = 0.5f;

	//Set their attributes
	renderer.GetTexture(MAINCHARACTER)->setScale(tex3_scale);
	renderer.GetTexture(MAINCHARACTER + 1)->setScale(1.0f);
	renderer.GetTexture(MAINCHARACTER + 1)->setpos_y(-0.2f);


	renderer.GetTexture(PHOTOTEXTURE)->setpos_y(-0.3f);
	renderer.GetTexture(PHOTOTEXTURE)->setpos_x(0.6f);

	colrect->SetPrimitivePosition({ 0.6f,0.9f });

	colrect->SetPrimitiveScaleRatio(0.3f, 1.0f);

	//colrect->SetPrimitiveScale(0.4f);
	renderer.SetPrimitiveAttrib(2, { 1000,800 });

	float xpos = 0.5f;
	float ypos = 0.5f;

	float fps = 60;
	float speed_ind = (fps / 1000) * 0.5f;
	float rotation = 0.0f;

	std::bitset<1> mouseloop(0);
	Vec2<double> starting_point = { NULL, NULL };

	Vec2<int> winsize;

	srand(time(NULL));


	//Create and bind collision boxes
	CollisionBox colbox;
	CollisionBox texbox;

	CollisionBox TheNewest;

	colbox.SetCollisionBox(colrect->GetPosition().x, colrect->GetPosition().y, (colrect->GetScale() * colrect->GetScaleRatio().x * 1.0f), (colrect->GetScale() * colrect->GetScaleRatio().y * 1.0f), renderer.GetScreenRatio());

	colbox.BindCollisionBox<HemlockPrimitive>(colrect);
	colbox.BindCollisionBox<HemlockTexture>(texturerect);

	TheNewest.BindCollisionBox<HemlockPrimitive>(renderer.GetPrimitive(0));

	std::cout << "X: " << colrect->GetCollusionBox()->x << std::endl;
	std::cout << "Y: " << colrect->GetCollusionBox()->y << std::endl;
	std::cout << "WIDTH: " << colrect->GetCollusionBox()->width << std::endl;
	std::cout << "HEIGHT: " << colrect->GetCollusionBox()->height << std::endl;


	colbox.SetCollisionBox<HemlockTexture>(texturerect, renderer.GetScreenRatio());

	while (!renderer.WindowShouldClose())
	{
		renderer.framebuffer_size_recall();

		if (renderer.SetFps(fps).first)
		{
			renderer.GetTexture(MAINCHARACTER)->rotate(rotation);

			if (renderer.IsKeyPressed(KEY_LEFT_SHIFT))
			{
				speed_ind *= 2;
			}
			if (renderer.IsKeyPressed(KEY_RIGHT))
			{
				xpos += speed_ind;
			}

			if (renderer.IsKeyPressed(KEY_LEFT))
			{
				xpos -= speed_ind;
			}

			if (renderer.IsKeyPressed(KEY_UP))
			{
				ypos += speed_ind;
			}

			if (renderer.IsKeyPressed(KEY_DOWN))
			{
				ypos -= speed_ind;
			}
			if (renderer.IsKeyPressed(KEY_SPACE) && !renderer.IsKeyPressed(KEY_LEFT_ALT))
			{
				rotation += 1.0f;
			}
			if (renderer.IsKeyPressed(KEY_SPACE) && renderer.IsKeyPressed(KEY_LEFT_ALT))
			{
				rotation -= 1.0f;
			}

			renderer.GetTexture(MAINCHARACTER)->setpos_x(xpos / fps);
			renderer.GetTexture(MAINCHARACTER)->setpos_y(ypos / fps);

			if (renderer.IsMouseButtonPressed(KEY_MOUSE_LEFT) && mouseloop[0] == 0)
			{

				starting_point.x = renderer.GetMousePosScreencords().x;
				starting_point.y = renderer.GetMousePosScreencords().y;

				mouseloop.set(0, 1);

			}

			if (mouseloop[0] == 1)
			{

				float distance = sqrt(pow((starting_point.x - renderer.GetMousePosScreencords().x), 2) + pow(starting_point.y - renderer.GetMousePosScreencords().y, 2));

				if (distance != 0.0f)
				{
					tex3_scale = distance / 100.0f;
				}
				else
				{
					tex3_scale = tex3_scale;
				}

				renderer.GetTexture(MAINCHARACTER)->setScale(tex3_scale);

			}

			if (renderer.IsMouseButtonPressed(KEY_MOUSE_RIGHT) && mouseloop[0] == 1)
			{
				starting_point = { 0,0 };
				mouseloop.set(0, 0);

			}

			speed_ind = (1000 / fps) * 0.5f;

			static int clickcount = 0;

			
			//colbox.SetCollisionBox(colrect->GetPosition().x, colrect->GetPosition().y, (colrect->GetScale() * colrect->GetScaleRatio().x * 1.0f)+1.0f, (colrect->GetScale() * colrect->GetScaleRatio().y * 1.0f)+1.0f, renderer.GetScreenRatio());

			//colbox.SetCollisionBox(texturerect->get_pos_x(), texturerect->get_pos_y(), (texturerect->get_scale() * 1.0f)+0.1f, (texturerect->get_scale() * 1.0f)+0.1f, renderer.GetScreenRatio());




			renderer.GetPrimitive(0)->SetPrimitivePosition({(float)renderer.GetMousePosGLcords().x,(float)renderer.GetMousePosGLcords().y });

			TheNewest.SetCollisionBox(renderer.GetPrimitive(0), renderer.GetScreenRatio());

			rect* cb = renderer.GetPrimitive(0)->GetCollusionBox();
			rect* tb = renderer.GetTexture(2)->GetCollisionBox();

			if ((renderer.CheckCollisionBoxCursor<HemlockTexture>(&colbox, {0.0f,0.0f}) || renderer.CheckCollisionBoxCursor<HemlockPrimitive>(&TheNewest, {0.0f,0.0f})) && renderer.IsMouseButtonPressed(KEY_MOUSE_LEFT))
			{
				renderer.GetPrimitive(0)->SetPrimitiveColor({ 0.3f,0.8f,0.5f,1.0f });

				clickcount++;

			}

			if (renderer.CheckCollisionBoxBox(&colbox, &TheNewest))
			{

				std::cout << "Collided" << "\n";

			}

			

			//std::cout << "MOUSE CORDS IN GL x: " <<renderer.GetMousePosGLcords().x <<" y: "<<renderer.GetMousePosGLcords().y << std::endl;
			

			renderer.clearscreen({ 0.0f,0.0f,0.0f,1.0f });

			//renderer.drawCircle(64, 1);

			renderer.DrawTexture(MAINCHARACTER);

			renderer.DrawTexture(PHOTOTEXTURE);

			//renderer.DrawTextureRect(PHOTOTEXTURE, { 0.4f , 0.0f , 0.6f,0.6f });

			renderer.RenderText("current fps: ", -0.95f, 0.9f, 0.001f, { 1.0f, 0.8f, 0.2f });

		    renderer.RenderText(std::to_string((int)ceil(renderer.SetFps(fps).second)), -0.70f, 0.9f, 0.001f, { 1.0f, 0.8f, 0.2f });

			renderer.RenderText("CLICK COUNT: ", -0.95f, -0.9f, 0.001f, { 1.0f, 0.8f, 0.2f });

			renderer.RenderText("CLICK  INSIDE  THE  BOX", texturerect->get_pos_x() - 0.35f, texturerect->get_pos_y() + 0.57, 0.001f, {1.0f, 0.8f, 0.2f});

			//std::cout << texturerect->get_scale() << " " << texturerect->get_scale() << std::endl;

			renderer.RenderText(std::to_string(clickcount), -0.60f, -0.9f, 0.001f, {1.0f, 0.8f, 0.2f});

			//colbox.VisualizeCollisionBox({ 1.0f,0.0f,0.0f,1.0f },*renderer.returnshader());

			renderer.VisualizeCollisionBox(&colbox, { 1.0f,0.0f,0.0f,1.0f });

			renderer.drawRectangle(0);

			renderer.VisualizeCollisionBox(&TheNewest, { 0.0f,1.0f,0.0f,1.0f });

			
			//renderer.drawCircle(64, 2);
			
			//slider.DrawSlider();

			//renderer.DrawFrame(8, { 1.0f,0.0f,0.3f,1.0f });

			renderer.render();

			renderer.GetPrimitive(0)->SetPrimitiveColor({ 1.0f,0.0f,0.0f,1.0f });

		}

	}


	return 0;
}
