#pragma once

// <class name		: StateManager>
// <update date		: 2020 / 05 / 26>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef STATEMANAGER_DEFINED
#define STATEMANAGER_DEFINED

class GameContext;
class IState;

// <StateManager>
class StateManager final
{
public:
	enum StateID
	{
		NONE = -1,
		TITLE,
		//PLAY,
		//RESOULT,

		NUM_STATES
	};

private:
	using FactoryMethod = IState*(*)();

	// <現在のステート>
	std::unique_ptr<IState>	m_activeState;
	// <次のステート>
	StateID					m_nextStateID;
	// <ステート作成用>
	FactoryMethod			m_stateFactoryMethods[StateID::NUM_STATES];

public:
	StateManager();
	~StateManager();

	// <ステート登録>
	void Register(StateID _stateID, FactoryMethod _factoryMethod);
	// <開始ステート設定>
	void SetStartState(GameContext& context, StateID _start);
	// <現在のステート更新>
	void UpdateActiveState(GameContext& context);
	// <現在のステート描画>
	void RenderActiveState(GameContext& context);

	// <ステート変更要求>
	void RequestState(StateID _stateID);

	// <現在アクティブなステートを取得>
	IState& GetActiveState()
	{
		return *m_activeState;
	}

private:
	// <シーン変更>
	void ChangeState(GameContext& context, StateID _stateID);
};

#endif