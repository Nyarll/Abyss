#pragma once

// <class name		: Property>
// <update date		: 2020 / 05 / 25>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef PROPERTY_DEFINED
#define PROPERTY_DEFINED

#include <functional>

// <Property>
template <typename ObjectType>
struct Property
{
	std::function<ObjectType()> getter;
	std::function<void(const ObjectType& value)> setter;
	Property(
		const std::function<ObjectType()>& Getter,
		const std::function<void(const ObjectType&)>& Setter)
		:getter(Getter)
		, setter(Setter)
	{}
	void operator=(const ObjectType& value) { setter(value); }
	operator ObjectType()const { return getter(); }
	void operator+=(const ObjectType& value) { setter(getter() + value); }
	void operator-=(const ObjectType& value) { setter(getter() - value); }
	void operator*=(const ObjectType& value) { setter(getter() * value); }
	void operator/=(const ObjectType& value) { setter(getter() / value); }
	void operator%=(const ObjectType& value) { setter(getter() % value); }

	ObjectType operator*() const { return getter(); }
	ObjectType operator->() const { return getter(); }
};

#endif