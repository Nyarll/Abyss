#pragma once

// <namespace name  : ECS (Entity Component System)>
// <update date		: 2020 / 05 / 20>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef ECM_DEFINES
#define ECM_DEFINES

// <EntityComponentSystem>

// <include>
#ifndef REGISTRY_INCLUDE
#define REGISTRY_INCLUDE

#include <vector>
#include <memory>
#include <utility>
#include <typeinfo>

#endif

namespace ECS
{
	// <ID定義>
	using _ID = unsigned int;

	using Entity = _ID;
	using _ComponentID = _ID;

	// <Entity管理>
	using _Entities = std::vector<Entity>;

	// <Deleter Interface>
	struct _DeleterBase
	{
		virtual ~_DeleterBase() {}
	};

	// <Deleter>
	template <typename ObjectType>
	struct _Deleter : public _DeleterBase
	{
		std::unique_ptr<ObjectType>	obj;
		_Deleter(std::unique_ptr<ObjectType>&& deletePtr): obj(std::move(deletePtr)) {}
	};

	// <コンポーネント管理>
	struct _SparseSet
	{
		std::vector<std::unique_ptr<_DeleterBase>> _components;	// <コンポーネント>
		_Entities _packed;										// <コンポーネントを持っているエンティティ>

		std::size_t info;										// <コンポーネント情報>
	};

	using _Components = std::vector<_SparseSet>;
}


namespace ECS
{
	// <class name	: Registry>
	// <summary		: EntityComponentSystem本体>
	// <update date	: 2020 / 05 / 20>
	// <author		: Nyarll>
	class Registry
	{
	private:
		_Entities _entities;

		_Components _pools;

	public:
		// <コンストラクタ>
		Registry() {}
		// <デストラクタ>
		~Registry()
		{
			Clear();
		}

	public:

		// <Entity生成>
		Entity Create()
		{ 
			Entity entity = _entities.size();

			_entities.push_back(entity);

			return entity;
		}

		// <コンポーネント登録> : void Emplace( Entity ID )
		template <typename ComponentType>
		void Emplace(const Entity& entity)
		{
			const std::type_info& info = typeid(ComponentType);
			// <1つ以上コンポーネントが登録されている場合>
			if (_pools.size() > 0)
			{
				for (int i = 0; i < _pools.size(); i++)
				{
					// <既に登録されていた場合>
					if (info.hash_code() == _pools[i].info)
					{
						_pools[i]._packed.push_back(entity);
						if (_pools[i]._components.size() < (entity + 1))
						{
							_pools[i]._components.resize(entity);
						}
						_pools[i]._components.push_back(std::make_unique<_Deleter<ComponentType>>(std::make_unique<ComponentType>()));
						return;
					}
				}
			}
			// <登録されていない新規コンポーネントだった場合>
			{
				_SparseSet set;
				_pools.push_back(std::move(set));
				int n = _pools.size() - 1;
				_pools[n].info = typeid(ComponentType).hash_code();
				_pools[n]._packed.push_back(entity);
				if (_pools[n]._components.size() < (entity + 1))
				{
					_pools[n]._components.resize(entity);
				}
				_pools[n]._components.push_back(std::make_unique<_Deleter<ComponentType>>(std::make_unique<ComponentType>()));
				
			}
		}

		// < <ComponentType> Componentを持つEntityのみ呼び出す> : each( function )
		template <typename ComponentType, typename Func>
		void Each(Func func)
		{
			const std::type_info& info = typeid(ComponentType);

			int i = 0;
			for (auto& sparse_set : _pools)
			{
				if (info.hash_code() == sparse_set.info)
				{
					break;
				}
				i++;
			}

			if (_pools.size() == i)return;	// <登録されていない>

			for (auto& entity : _pools[i]._packed)
			{
				auto& c = _pools[i]._components[entity];
				func(entity, *(dynamic_cast<_Deleter<ComponentType>*>(c.get())->obj));
			}
		}

		void Clear()
		{
			_pools.clear();
			_entities.clear();
		}
	};
}

#endif