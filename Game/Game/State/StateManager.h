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

	// <���݂̃X�e�[�g>
	std::unique_ptr<IState>	m_activeState;
	// <���̃X�e�[�g>
	StateID					m_nextStateID;
	// <�X�e�[�g�쐬�p>
	FactoryMethod			m_stateFactoryMethods[StateID::NUM_STATES];

public:
	StateManager();
	~StateManager();

	// <�X�e�[�g�o�^>
	void Register(StateID _stateID, FactoryMethod _factoryMethod);
	// <�J�n�X�e�[�g�ݒ�>
	void SetStartState(GameContext& context, StateID _start);
	// <���݂̃X�e�[�g�X�V>
	void UpdateActiveState(GameContext& context);
	// <���݂̃X�e�[�g�`��>
	void RenderActiveState(GameContext& context);

	// <�X�e�[�g�ύX�v��>
	void RequestState(StateID _stateID);

	// <���݃A�N�e�B�u�ȃX�e�[�g���擾>
	IState& GetActiveState()
	{
		return *m_activeState;
	}

private:
	// <�V�[���ύX>
	void ChangeState(GameContext& context, StateID _stateID);
};

#endif