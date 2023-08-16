#include "PewGame.h"
#include "Player.h"
#include "Enemy.h"
#include "MultiShotEnemy.h"
#include "Boss.h"
#include "Rock.h"

#include "Core/Core.h"

#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"


bool PewGame::Initialize()
{
	//m_font = MEN::g_resourceManager.Get<MEN::Font>("ArcadeClassic.ttf", 25);

	//m_fontBig = MEN::g_resourceManager.Get<MEN::Font>("ArcadeClassic.ttf", 50);

	m_scoreText = std::make_unique<MEN::Text>(GET_RESOURCE(MEN::Font, "ArcadeClassic.ttf", 25));

	m_livesText = std::make_unique<MEN::Text>(GET_RESOURCE(MEN::Font, "ArcadeClassic.ttf", 25));
	

	m_titleText = std::make_unique<MEN::Text>(GET_RESOURCE(MEN::Font,"ArcadeClassic.ttf", 50));
	m_titleText->Create(MEN::g_renderer, "UHHH BEN ASTEROID", MEN::Color{1, 1, 1, 1});
	
	m_gameOverText = std::make_unique<MEN::Text>(GET_RESOURCE(MEN::Font, "ArcadeClassic.ttf", 50));
	m_gameOverText->Create(MEN::g_renderer, "GAMER OVER", MEN::Color{1, 1, 1, 1});

	MEN::g_audioSystem.AddAudio("pew", "Pew.wav");
	MEN::g_audioSystem.AddAudio("music", "arcade-music-loop.wav");

	m_scene = std::make_unique<MEN::Scene>();

	m_state = eState::Title;

	// music by joshuaempyre on freesound.org
	MEN::g_audioSystem.PlayOneShot("music", true);



	return false;
}

void PewGame::Shutdown()
{
}

void PewGame::Update(float deltaTime)
{
	switch (m_state)
	{
	case PewGame::eState::Title:
		if (MEN::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
   			m_state = eState::StartGame;
		}
		break;
	case PewGame::eState::StartGame:
	{
		m_score = 0;
		m_lives = 3;

		m_state = eState::StartLevel;
	}
	break;
	case PewGame::eState::StartLevel:
	{
		bossIsPresent = false;

		m_scene->RemoveAll();

		for (int i = 0; i < 3; i++)
		{
			std::unique_ptr<Rock> rock = std::make_unique<Rock>(10.0f, MEN::Transform{{MEN::random(800), MEN::random(900)}, 0, 5});
			rock->tag = "Rock";
			rock->m_game = this;
			m_scene->Add(std::move(rock));
		}
// Create Player
		std::unique_ptr<Player> player = std::make_unique<Player>(10.0f, MEN::pi, MEN::Transform{{ 400, 300 }, 0, 1.5});
		player->tag = "Player";
		player->m_game = this;

	// Add Components
		auto renderComponent = CREATE_CLASS(SpriteComponent);
		renderComponent->m_texture = GET_RESOURCE(MEN::Texture, "ship.png", MEN::g_renderer);
		player->AddComponent(std::move(renderComponent));

		auto physicsComponent = CREATE_CLASS(EnginePhysicsComponent);
		player->AddComponent(std::move(physicsComponent));

		auto collisionComponent = CREATE_CLASS(CircleCollisionComponent);
		collisionComponent->m_radius = 30.0f;
		player->AddComponent(std::move(collisionComponent));

		player->Initialize();
		m_scene->Add(std::move(player));

		m_state = eState::Game;
	}
	break;
	case PewGame::eState::Game:
		if ((m_score - (m_bossesBeaten * 2000) >= 2000))
		{
			m_state = PewGame::eState::GameBoss;
			bossIsPresent = false;
		}

		m_spawnTimer += deltaTime;
		if (m_spawnTimer >= m_spawnTime)
		{
// Reset spawn timer and randomize which enemy type spawns (~75% normal, ~25% multishot)
			m_spawnTimer = 0;
			int choice = MEN::random(4);
			std::cout << choice << std::endl;
			if (choice == 1 || choice == 2 || choice == 3)
			{
// Create Enemy 1
				std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(MEN::randomf(200.0f), MEN::pi, MEN::Transform{{MEN::random(800), MEN::random(900)}, MEN::randomf(), 1});
				enemy->tag = "Enemy";
				enemy->m_game = this;

				std::unique_ptr<MEN::SpriteComponent> component = std::make_unique<MEN::SpriteComponent>();
				component->m_texture = GET_RESOURCE(MEN::Texture, "ship.png", MEN::g_renderer);
				enemy->AddComponent(std::move(component));

				auto collisionComponent = std::make_unique<MEN::CircleCollisionComponent>();
				collisionComponent->m_radius = 30.0f;
				enemy->AddComponent(std::move(collisionComponent));

				enemy->Initialize();
				m_scene->Add(std::move(enemy));

				
			}
			else {
// Create Enemy 2
				std::unique_ptr<MultiShotEnemy> enemy = std::make_unique<MultiShotEnemy>(MEN::randomf(200.0f), MEN::pi, MEN::Transform{{MEN::random(800), MEN::random(900)}, MEN::randomf(), 1});
				enemy->tag = "Enemy";
				enemy->m_game = this;

				std::unique_ptr<MEN::SpriteComponent> component = std::make_unique<MEN::SpriteComponent>();
				component->m_texture = GET_RESOURCE(MEN::Texture, "ship.png", MEN::g_renderer);
				enemy->AddComponent(std::move(component));

				auto collisionComponent = std::make_unique<MEN::CircleCollisionComponent>();
				collisionComponent->m_radius = 30.0f;
				enemy->AddComponent(std::move(collisionComponent));

				enemy->Initialize();
				m_scene->Add(std::move(enemy));

				
			}
		}
		break;
	case PewGame::eState::GameBoss:
	{
		if (!bossIsPresent)
		{
// Create Boss
			std::unique_ptr<Boss> boss = std::make_unique<Boss>(10, MEN::randomf(200.0f), MEN::pi, MEN::Transform{{MEN::random(800), MEN::random(900)}, MEN::randomf(), 3});
			boss->tag = "Enemy";
			boss->m_game = this;

			std::unique_ptr<MEN::SpriteComponent> component = std::make_unique<MEN::SpriteComponent>();
			component->m_texture = GET_RESOURCE(MEN::Texture, "ship.png", MEN::g_renderer);
			boss->AddComponent(std::move(component));

			auto collisionComponent = std::make_unique<MEN::CircleCollisionComponent>();
			collisionComponent->m_radius = 30.0f;
			boss->AddComponent(std::move(collisionComponent));

			boss->Initialize();
			m_scene->Add(std::move(boss));

			bossIsPresent = true;
			std::cout << "Boss Spawned!" << std::endl;
		}
	}
	break;
	case PewGame::eState::GameBossEnd:
		m_stateTimer = 5;
		m_stateTimer -= deltaTime;
		if (m_stateTimer <= 0)
		{
			m_scene->RemoveAll();
			m_state = eState::StartLevel;
		}
		break;
	case PewGame::eState::PlayerDeadStart:
		m_stateTimer = 3;
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::PlayerDead;
		break;

	case PewGame::eState::PlayerDead:
		m_stateTimer -= deltaTime;
		if (m_stateTimer <= 0)
		{
			m_state = eState::StartLevel;
			m_lives -= 1;
		}
		break;
	case PewGame::eState::GameOverStart:

		break;
	case PewGame::eState::GameOver:
		m_stateTimer = 3;
		m_stateTimer -= deltaTime;
		if (m_stateTimer <= 0)
		{
			m_scene->RemoveAll();
			m_state = eState::Title;
		}
		break;
	}

	m_livesText->Create(MEN::g_renderer, "Lives " + std::to_string(m_lives), MEN::Color{1, 1, 0.5f, 1});
	m_scoreText->Create(MEN::g_renderer, std::to_string(m_score), MEN::Color{ 1,1,0.5f,1 });
	m_scene->Update(deltaTime);
}

void PewGame::Draw(MEN::Renderer& renderer)
{
	if (m_state == eState::Title)
	{
		m_titleText->Draw(renderer, 300, 300);
	}
	if (m_state == eState::GameOver)
	{
		m_gameOverText->Draw(renderer, 400, 300);
	}
	m_scene->Draw(renderer);
	m_scoreText->Draw(renderer, 40, 40);
	m_livesText->Draw(renderer, 40, 80);
 }
