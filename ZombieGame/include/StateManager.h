#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <functional>
#include <string>
#include "Game.h"
#include "EventManager.h"
#include <algorithm>
#include <chrono>

enum class StateType {
	 MainMenu=1, Game,Shop,Inventory, Paused, GameOver, Credits
};

class StateManager;
class BaseState {
	friend class StateManager; //state manager acceses items of base state
public:
	BaseState(StateManager* l_stateManager)
		:m_stateMgr(l_stateManager), m_transparent(false),
		m_transcendent(false) {}
	virtual ~BaseState() {}
	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Activate() = 0;
	virtual void Deactivate() = 0;
	virtual void Update(const sf::Time& l_time) = 0;
	virtual void Draw() = 0;
	void SetTransparent(const bool& l_transparent) {
		m_transparent = l_transparent;
	}
	bool IsTransparent()const { return m_transparent; }
	void SetTranscendent(const bool& l_transcendence) {
		m_transcendent = l_transcendence;
	}
	
		bool IsTranscendent()const { return m_transcendent; }
	StateManager* GetStateManager() { return m_stateMgr; }


protected:
	StateManager* m_stateMgr;
	bool m_transparent;
	bool m_transcendent;
};

//struct that holds pointers to important parts of the game
struct SharedContext {
	SharedContext() :window(nullptr), m_eventManager(nullptr) {}
	Game* window;
	EventManager* m_eventManager;
};

using StateContainer = std::vector<std::pair<StateType, BaseState*>>; //pair state type and pointer to baseState
using TypeContainer = std::vector<StateType>; //container with the states of the game
using StateFactory = std::unordered_map<StateType, std::function<BaseState* (void)>>; //map state with a function of void type in that state



class StateManager {
public:
	StateManager(SharedContext* l_shared);
	~StateManager();

	void Update(const sf::Time& l_time);
	void Draw();
	void ProcessRequests();
	SharedContext* GetContext();
	bool HasState(const StateType& l_type);
	void SwitchTo(const StateType& l_type);
	void Remove(const StateType& l_type);


private:
	// Methods.
	void CreateState(const StateType& l_type);
	void RemoveState(const StateType& l_type);

	template<class T>
	void RegisterState(const StateType& l_type) { //callback method
		m_stateFactory[l_type] = [this]() -> BaseState*
			{
				return new T(this);
			};
	}
	// Members.
	SharedContext* m_shared;
	StateContainer m_states;
	TypeContainer m_toRemove;
	StateFactory m_stateFactory;
};

#endif