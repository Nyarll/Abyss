#pragma once

// <class name		: Item>
// <update date		: 2020 / 08 / 14>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef ITEM_DEFINED
#define ITEM_DEFINED

class Item
{
private:
	Entity m_owner = entt::null;
	entt::DefaultRegistry* registry;

public:
	void SetEntity(Entity entity)
	{
		m_owner = entity;
	}

	void SetRegistry(entt::DefaultRegistry* _registry)
	{
		registry = _registry;
	}

	// <ƒvƒŒƒCƒ„[‚ª‚Ô‚Â‚©‚Á‚½‚Æ‚«>
	void OnHitPlayer();
};

#endif