#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Enemy.h"

#include <iostream>
#include <vector>
#include <thread>
#include <memory>

using namespace std;

using namespace kiko;//vec2 = kiko::Vector2;

class Star
{
public:
	Star(const vec2& pos, const vec2& vel) :
		m_pos{ pos }, 
		m_vel{ vel }
	{}

	void Update(int width, int height)
	{
		m_pos += m_vel * kiko::g_time.getDeltaTime();
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
	
	
	std::unique_ptr<int> up = std::make_unique<int>(10);

	kiko::g_memoryTracker.DisplayInfo();
	
	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");

	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("CSC196", 800, 600);

	//kiko::InputSystem inputSystem;
	kiko::g_inputSystem.Initialize();
	kiko::g_audioSystem.Initialize();
	kiko::g_audioSystem.AddAudio("shoot", "shoot.wav");

	//std::vector<kiko::vec2> points { {-10, 5}, { 10, 5 }, { 0, -5 }, { -10, 5 }};


	kiko::Model model;
	model.Load("ship.txt");

	kiko::vec2 v{5, 5};
	v.Normalize();

	vector<Star> stars;
	for (int i = 0; i < 10; i++) {
		vec2 pos(kiko::random(kiko::g_renderer.GetWidth()), kiko::random(kiko::g_renderer.GetHeight()));
		vec2 vel(kiko::randomf(100, 200), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	//constexpr float turnRate = kiko::DegreesToRadians(180.0f);

	kiko::Scene scene;
	unique_ptr<Player> player = make_unique<Player>(200, kiko::Pi, kiko::Transform{ {400, 300}, 0, 4 }, model);
	scene.Add(std::move(player));
	for (int i = 0; i < 50; i++)
	{
		unique_ptr<Enemy> enemy = make_unique<Enemy>( 300, kiko::Pi, kiko::Transform{ {kiko::random(800), kiko::random(600)}, kiko::randomf(kiko::TwoPi), 3}, model );
		scene.Add(std::move(enemy));
	}

	//Resource Manager?

	// main game loop
	bool quit = false;
	while (!quit)
	{
		kiko::g_time.Tick();
		kiko::g_audioSystem.Update();
		kiko::g_inputSystem.Update();

		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		if(kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			kiko::g_audioSystem.PlayOneShot("shoot");
		}

		//update game
		scene.Update(kiko::g_time.getDeltaTime());

		kiko::g_renderer.SetColor(0, 0, 0, 0);
		kiko::g_renderer.BeginFrame();
		// draw
		vec2 vel(1.0f, 0.3f);

		for (auto& star : stars)
		{
			star.Update(kiko::g_renderer.GetWidth(), kiko::g_renderer.GetHeight());
			
			kiko::g_renderer.SetColor(255, 255, 255, 255);

			star.Draw(kiko::g_renderer);

			
		}

		scene.Draw(kiko::g_renderer);
		kiko::g_renderer.EndFrame();

	}

	stars.clear();
	scene.RemoveAll();

	kiko::g_memoryTracker.DisplayInfo();

	return 0;
}
