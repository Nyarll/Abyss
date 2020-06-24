#pragma once

// <class name		: PlayState>
// <update date		: 2020 / 06 / 02>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef PLAYSTATE_DEFINED
#define PLAYSTATE_DEFINED

#include "../IState.h"
#include "Component\DebugTools\Grid\Grid.h"

class GridFloor;

// <PlayState>
class PlayState : public IState
{
private:
	Entity m_mapGenerator = entt::null;

public:
	virtual void Initialize(GameContext& context)override;	// <初期化>

	virtual void Update(GameContext& context)override;		// <更新>
	virtual void Render(GameContext& context)override;		// <描画>

	static IState* Create()
	{
		return{ new PlayState };
	}

private:
	void CreateCamera();
	void CreateGameEntitys(GameContext& context);
	void CreateUI(GameContext& context);
	void RegisterTexture(GameContext& context);

	// <デバッグ用>
private:
	bool isWireframe = true;
	std::unique_ptr<GridFloor> m_gridFloor;

	void CreateDebugItems(GameContext& context);
	void SwitchingDebug();

	void DebugFunction();

	void DebugRender(GameContext& context, DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj);
};

#endif