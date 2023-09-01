#include "PlatformGame.h"

#include "Core/Core.h"

#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"

bool PlatformGame::Initialize()
{
	m_scene = std::make_unique<MEN::Scene>();

	m_state = eState::Title;

	// music by joshuaempyre on freesound.org
	//MEN::g_audioSystem.PlayOneShot("music", true);

	

	// Add Events
	EVENT_SUBSCRIBE("OnAddPoints", PlatformGame::OnAddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", PlatformGame::OnPlayerDead);

	return false;
}

void PlatformGame::Shutdown()
{
}

void PlatformGame::Update(float deltaTime)
{
	switch (m_state)
	{
	case PlatformGame::eState::Title:
	{
		m_scene->Load("Scenes/title.json");

		m_scene->Initialize();

		if (MEN::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
		}
	}
		break;
	case PlatformGame::eState::StartGame:
	{

		m_state = eState::StartLevel;
	}
	break;
	case PlatformGame::eState::StartLevel:
	{
		m_scene->RemoveAll(false);

		m_scene->Load("Scenes/PlatformScene.json");
		m_scene->Load("Scenes/tilemap.json");

		m_scene->Initialize();

		//auto coin = INSTANTIATE(Actor, "Coin");
		//coin->transform.position = { 700, 100 };


		//auto coin2 = INSTANTIATE(Actor, "Coin");
		//coin2->transform.position = { 950, 100 };

		//coin->Initialize();
		//coin2->Initialize();

		MEN::g_audioSystem.AddAudio("attack", "Audio/woosh.wav");
		MEN::g_audioSystem.AddAudio("collect", "Audio/collect.wav");
	

		m_state = eState::Game;
	}
	break;
	case PlatformGame::eState::Game:
		if (lives <= 0)
		{
			m_state = eState::GameOver;
		}
		break;
	case PlatformGame::eState::PlayerDeadStart:
		m_state = eState::PlayerDead;
		break;

	case PlatformGame::eState::PlayerDead:
		lives--;
		m_state = eState::StartLevel;
		break;
	case PlatformGame::eState::GameOverStart:

		break;
	case PlatformGame::eState::GameOver:
		m_stateTimer = 2;
		m_stateTimer -= deltaTime;
		if (m_stateTimer <= 0)
		{
			m_scene->RemoveAll(false);
			if (MEN::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
			{
				m_state = eState::Title;
			}
		}
		break;
	}
	m_scene->Update(deltaTime);
}

void PlatformGame::Draw(MEN::Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void PlatformGame::OnAddPoints(const MEN::Event& event)
{
	m_score += std::get<int>(event.data);
}

void PlatformGame::OnPlayerDead(const MEN::Event& event)
{
	m_lives--;
	m_state = eState::PlayerDeadStart;
}