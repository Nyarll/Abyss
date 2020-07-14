#include "StateManager.h"

#include "IState.h"

extern void ExitGame();

StateManager::StateManager()
	:m_activeState(nullptr)
	,m_nextStateID(StateID::NONE)
{
	for (int i = 0; i < StateID::NUM_STATES; i++)
	{
		m_stateFactoryMethods[i] = nullptr;
	}
}

StateManager::~StateManager()
{
	m_activeState.reset();
}

void StateManager::Register(StateID _stateID, FactoryMethod _factoryMethod)
{
	assert(_stateID >= 0 && _stateID < StateID::NUM_STATES && "Error : Invalid scene ID.");
	assert(_factoryMethod && "Error : Generation function is not specified.");

	if ((!(_stateID >= 0 && _stateID < StateID::NUM_STATES)) || (!(_factoryMethod)))
	{
		ExitGame();
		return;
	}

	m_stateFactoryMethods[_stateID] = _factoryMethod;
}

void StateManager::SetStartState(GameContext & context, StateID _start)
{
	assert(_start >= 0 && _start < StateID::NUM_STATES && "Error : Invalid scene ID.");

	ChangeState(context, _start);
}

void StateManager::UpdateActiveState(GameContext & context)
{
	assert(m_activeState && "Error : There are no active scenes.");

	if (m_nextStateID != StateID::NONE)
	{
		ChangeState(context, m_nextStateID);
		m_nextStateID = StateID::NONE;
	}
	m_activeState->Update(context);
}

void StateManager::RenderActiveState(GameContext & context)
{
	assert(m_activeState && "Error : There are no active scenes.");

	m_activeState->Render(context);
}

void StateManager::RequestState(StateID _stateID)
{
	assert(_stateID >= 0 && _stateID < StateID::NUM_STATES && "Error : Invalid scene ID.");

	m_nextStateID = _stateID;
}

void StateManager::ChangeState(GameContext & context, StateID _stateID)
{
	assert(_stateID >= 0 && _stateID < StateID::NUM_STATES && "Error : Invalid scene ID.");
	assert(m_stateFactoryMethods[_stateID] && "Error : Generation function is not specified.");

	if (m_activeState != nullptr)
	{
		m_activeState->Finalize(context);
		m_activeState.reset();
	}

	m_activeState.reset(m_stateFactoryMethods[_stateID]());
	m_activeState->Initialize(context);
}
