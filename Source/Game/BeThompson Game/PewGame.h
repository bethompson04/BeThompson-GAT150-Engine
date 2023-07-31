#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"

class PewGame : public MEN::Game
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		GameBoss,
		GameBossEnd,
		PlayerDeadStart,
		PlayerDead,
		GameOverStart,
		GameOver
	};
public:


	// Inherited VIA Game
	virtual bool Initialize() override;
	virtual void Shutdown() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw(MEN::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }
private:
	eState m_state = eState::Title;
	float m_spawnTimer = 0;
	float m_spawnTime = 3.0f;

	float m_stateTimer = 0;

	std::shared_ptr<MEN::Font> m_font;
	std::shared_ptr<MEN::Font> m_fontBig;

	std::unique_ptr<MEN::Text> m_scoreText;
	std::unique_ptr<MEN::Text> m_livesText;
	std::unique_ptr<MEN::Text> m_titleText;
	std::unique_ptr<MEN::Text> m_gameOverText;
};