#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Scene.h"
#include "PewGame.h"
#include "Renderer/Texture.h"

#include "Framework/Emitter.h"
#include "Renderer/ParticleSystem.h"

#include "Player.h"
#include "Enemy.h"

#include <iostream>
#include <vector>
#include <thread>
#include <cassert>

using namespace std;

// *================================================== STAR CLASS
class Star
{
public:
	Star(const MEN::Vector2& pos, const MEN::Vector2& vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void UpdatePos()
	{
		m_pos += m_vel * MEN::g_time.GetDeltaTime();
	}

	void WrapCheck(int width, int height)
	{
		if (m_pos.x >= width )m_pos.x = 0;
		if (m_pos.y >= height )m_pos.y = 0;
	}

	void Draw(MEN::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	MEN::Vector2 m_pos;
	MEN::Vector2 m_vel;
};

// *================================================== MAIN

int main(int argc, char* argv[])
{
	


	INFO_LOG("Start Successful!");

	MEN::MemoryTracker::Initialize();
	MEN::seedRandom((unsigned int)time(nullptr));
	MEN::setFilePath("assets");

	MEN::g_renderer.Initialize();
	MEN::g_renderer.CreateWindow("CSC196", 800, 600);

	MEN::g_inputSystem.Initialize();
	MEN::g_audioSystem.Initialize();

	shared_ptr<MEN::Texture> texture = make_shared<MEN::Texture>();
	texture->Create(MEN::g_renderer, "bing.jpg");

	unique_ptr<PewGame> game = make_unique<PewGame>();
	game->Initialize();
	// Vector2 Model

	MEN::vec2 v(5, 5);
	v.Normalize();

// Star loop
	vector<Star> starSystem;
	for (int i = 0; i < 1000; i++)
	{
		MEN::Vector2 pos(MEN::random(MEN::g_renderer.GetWidth()), MEN::random(MEN::g_renderer.GetHeight()));
		MEN::Vector2 vel(MEN::randomf(1, 4), 0.0f);

		starSystem.push_back(Star(pos, vel));
	}

// Main Game Loop
	bool quit = false;
	while (!quit)
	{
//Timer
 		MEN::g_time.Tick();

//Input Checks
		MEN::g_inputSystem.Update();
		if (MEN::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		if (MEN::g_inputSystem.GetMouseButtonDown(0))
		{
			std::cout << "mouse pressed" << endl;
			MEN::vec2 pos = MEN::g_inputSystem.GetMousePosition();
			std::cout << pos.x << " " << pos.y << endl;
		}

		if (MEN::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !MEN::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			MEN::g_audioSystem.PlayOneShot("pew");
			std::cout << "pew pew" << endl;
		}

		game->Update(MEN::g_time.GetDeltaTime());
		MEN::g_particleSystem.Update(MEN::g_time.GetDeltaTime());

		MEN::g_renderer.SetColor(0, 0, 0, 0);
		MEN::g_renderer.BeginFrame();

// DRAW
		MEN::Vector2 vel(1.0f, 0.3f);

		MEN::g_renderer.SetColor(255, 255, 255, 255);

		//for (auto& star : starSystem)
		//{
		//	star.UpdatePos();
		//	star.WrapCheck(MEN::g_renderer.GetWidth(), MEN::g_renderer.GetHeight());
		//	star.Draw(MEN::g_renderer);
		//}
		
		MEN::g_particleSystem.Draw(MEN::g_renderer);
		game->Draw(MEN::g_renderer);
		MEN::g_renderer.DrawTexture(texture.get(), 200.0f, 200.0f, 0.0f);

		MEN::g_renderer.EndFrame();
	}
	return 0;
}