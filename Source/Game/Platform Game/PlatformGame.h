#pragma once
#include "Framework/Game.h"
#include "Framework/Event/EventManager.h"
#include "Renderer/Text.h"

class PlatformGame : public MEN::Game, MEN::IEventListener
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

	void OnAddPoints(const MEN::Event& event);
	void OnPlayerDead(const MEN::Event& event);

private:
	eState m_state = eState::Title;
	float m_spawnTimer = 0;
	float m_spawnTime = 3.0f;

	float m_stateTimer = 0;
};