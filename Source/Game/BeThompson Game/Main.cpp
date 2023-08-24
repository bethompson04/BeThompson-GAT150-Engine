#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "PewGame.h"

#include "Player.h"
#include "Enemy.h"

#include "Pyshics/PhysicsSystem.h"

#include <iostream>
#include <vector>
#include <thread>
#include <cassert>

#include <array>
#include <functional>

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

// *=================================================== FUNCTIONS

void print(int i)
{
	std::cout << i << std::endl;
}

int add(int i1, int i2)
{
	return i1 + i2;
}

int sub(int i1, int i2)
{
	return i1 - i2;
}

class A
{
public:
	int add(int i1, int i2)
	{
		return i1 + i2;
	}
};

union Data
{
	int i;
	bool b;
	char c[6];
};


// *================================================== MAIN

int main(int argc, char* argv[])
{
	Data data;
	data.i = 0;
	cout << data.b << endl;



	void (*func_ptr)(int) = &print;
	func_ptr(5);

	int (*op_ptr)(int, int);
	op_ptr = sub;

	cout << op_ptr(5, 3) << endl;

	std::function<int(int, int)> op;
	op = add;
	cout << op(6, 6) << endl;

	A a;
	op = std::bind(&A::add, &a, std::placeholders::_1, std::placeholders::_2);
	cout << op(6, 7) << endl;

	MEN::Factory::Instance().Register<MEN::SpriteComponent>("SpriteComponent");


	INFO_LOG("Initializing Engine.");

	MEN::MemoryTracker::Initialize();
	MEN::seedRandom((unsigned int)time(nullptr));
	MEN::setFilePath("assets");

	MEN::g_renderer.Initialize();
	MEN::g_renderer.CreateWindow("CSC196", 800, 600);

	MEN::g_inputSystem.Initialize();
	MEN::g_audioSystem.Initialize();

	unique_ptr<PewGame> game = make_unique<PewGame>();
	game->Initialize();
	// Vector2 Model

	MEN::vec2 v(5, 5);
	v.Normalize();

	// PhysicsSystem
	MEN::PhysicsSystem::Instance().Initialize();

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
		MEN::Vector2 vel(1.0f, 0.3f);

		game->Draw(MEN::g_renderer);

		MEN::g_renderer.SetColor(255, 255, 255, 255);
		
		MEN::g_particleSystem.Draw(MEN::g_renderer);
		//MEN::g_renderer.DrawTexture(texture.get(), 200.0f, 200.0f, 0.0f);

		MEN::g_renderer.EndFrame();
	}
	return 0;
}