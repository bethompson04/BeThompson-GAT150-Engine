#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"

#include "Pyshics/PhysicsSystem.h"

#include "PlatformGame.h"

#include <iostream>
#include <vector>
#include <thread>
#include <cassert>

#include <array>
#include <functional>

using namespace std;

// *=================================================== FUNCTIONS


// *================================================== MAIN

int main(int argc, char* argv[])
{
	MEN::Factory::Instance().Register<MEN::SpriteComponent>("SpriteComponent");


	INFO_LOG("Initializing Engine.");

	MEN::MemoryTracker::Initialize();
	MEN::seedRandom((unsigned int)time(nullptr));
	MEN::setFilePath("Assets/Platformer");

	MEN::g_renderer.Initialize();
	MEN::g_renderer.CreateWindow("CSC196", 800, 600);

	MEN::g_inputSystem.Initialize();
	MEN::g_audioSystem.Initialize();

	unique_ptr<PlatformGame> game = make_unique<PlatformGame>();
	game->Initialize();

	MEN::vec2 v(5, 5);
	v.Normalize();

	// PhysicsSystem
	MEN::PhysicsSystem::Instance().Initialize();

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

		MEN::g_particleSystem.Update(MEN::g_time.GetDeltaTime());
		MEN::PhysicsSystem::Instance().Update(MEN::g_time.GetDeltaTime());

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
		game->Draw(MEN::g_renderer);

		MEN::g_renderer.SetColor(255, 255, 255, 255);

		MEN::g_particleSystem.Draw(MEN::g_renderer);
		//MEN::g_renderer.DrawTexture(texture.get(), 200.0f, 200.0f, 0.0f);

		MEN::g_renderer.EndFrame();
	}
	return 0;
}