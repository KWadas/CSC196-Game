#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include <iostream>
#include <vector>

using namespace std;

using vec2 = kiko::Vector2;

class Star
{
public:
	Star(const vec2& pos, const vec2& vel) :
		m_pos{ pos }, 
		m_vel{ vel }
	{}

	void Update(int width, int height)
	{
		m_pos += m_vel;
		if (m_pos.x >= width) m_pos.x = 0;
		if (m_pos.y >= height) m_pos.y = 0;
	}

	void Draw(kiko::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	vec2 m_pos;
	vec2 m_vel;
};



int main(int argc, char* argv[])
{
	kiko::Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("CSC196", 800, 600);

	kiko::InputSystem inputSystem;
	inputSystem.Initialize();

	bool quit = false;
	while (!quit)
	{
		inputSystem.Update();
		if (inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}
	}

	//kiko::seedRandom((unsigned int)time(nullptr));

	//kiko::Renderer renderer;
	//renderer.Initialize();
	//renderer.CreateWindow("CSC196", 800, 600);

	//vector<Star> stars;
	//for (int i = 0; i < 1000; i++) {
	//	vec2 pos(kiko::Vector2(kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight())));
	//	vec2 vel(kiko::randomf(1, 4), 0.0f);

	//	stars.push_back(Star(pos, vel));
	//}


	//while (true)
	//{
	//	renderer.SetColor(0, 0, 0, 0);
	//	renderer.BeginFrame();
	//	// draw
	//	vec2 vel(1.0f, 0.3f);

	//	for (auto& star : stars)
	//	{
	//		star.Update(renderer.GetWidth(), renderer.GetHeight());

	//		renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
	//		star.Draw(renderer);
	//	}

	//	//for (int i = 0; i < 1000; i++) {
	//	//	kiko::Vector2 pos(kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight()));
	//	//
	//	//	renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
	//	//	renderer.DrawPoint(pos.x, pos.y);
	//	//}


	//	renderer.EndFrame();
	//}

	return 0;
}
