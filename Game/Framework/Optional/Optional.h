#pragma once

// <class name		: Optional>
// <update date		: 2020 / 06 / 09>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef ISTATE_DEFINED
#define ISTATE_DEFINED

#include <new>
#include <type_traits>
#include <functional>

template <typename T>
class Optional
{
private:
	// <�f�[�^ : T�^�����郁�������m��>
	typename std::aligned_storage<sizeof(T), __alignof(T)>::type data;
	// <�f�[�^�ւ̃|�C���^>
	mutable T* pData;

public:
	// <���Optional>
	Optional(std::nullptr_t it) :data(), pData(nullptr) {}
	// <���g����>
	Optional(const T& it) :data(), pData(new(&data)T(it)) {}

	// <�R�s�[�R���X�g���N�^>
	Optional(const Optional<T>& it) :data(), pData(it ? new(&data) T(*it) : nullptr) {}
	// <���[�u�R���X�g���N�^>
	Optional(Optional<T>&& it)noexcept : data(), pData(it ? new(&data) T(std::move(*it)) : nullptr) {}

	// <�����t��>
	template<typename ...Args>
	Optional(Args ...args) : data(), pData(new(&data) T(args...)) {}

	// <�f�X�g���N�^>
	~Optional()
	{
		if (pData)
			pData->~T();
	}

	// <������Z�q (��)>
	Optional<T> operator=(std::nullptr_t it) {
		if (pData) pData->~T();
		pData = nullptr;
		return *this;
	}
	// <������Z�q�R�s�[>
	Optional<T> operator=(const Optional& it) {
		if (pData) pData->~T();
		pData = it ? new(&data) T(*it) : nullptr;
		return *this;
	}
	// <������Z�q���[�u>
	Optional<T> operator=(Optional&& it) {
		if (pData) pData->~T();
		pData = it ? new(&data) T(std::move(*it)) : nullptr;
		return *this;
	}

	// <�l�擾>
	T& operator*() const { return *pData; }
	// <�l�擾>
	T* operator->() const { return pData; }
	// <�l�����邩�m�F>
	operator bool() const { return pData != nullptr; }
	// ��
	bool operator==(const Optional& it) const { return pData == it.pData; }
	// ��
	bool operator!=(const Optional& it) const { return pData != it.pData; }
	// <��łȂ���Ύ��s>
	template <typename Func>
	void ifPresent(Func func) const { if (pData) func(*pData); }
	// <��łȂ���Ύ��s�����ʂ�Ԃ�>
	template <typename Func>
	Optional<T> map(Func func) const
	{
		if (pData) return func(*pData);
		else return nullptr;
	}
	// <true�ł���΂��̂܂܁Afalse�ł���΋��Ԃ�>
	template <typename Func>
	Optional<T> filter(Func func) const
	{
		if (pData)
			if (func(*pData))
				return *this;
		return nullptr;
	}
	// <�l�擾 or �f�t�H���g�l>
	const T& orElse(const T& els) const { return pData ? *pData : els; }
	// <�l�擾 or �f�t�H���g�l�����֐�>
	template <typename Func>
	T orElseGet(Func func) const
	{
		if (pData) return *pData;
		else return func();
	}
};

#endif