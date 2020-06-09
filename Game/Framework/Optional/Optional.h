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
	// <データ : T型が入るメモリを確保>
	typename std::aligned_storage<sizeof(T), __alignof(T)>::type data;
	// <データへのポインタ>
	mutable T* pData;

public:
	// <空のOptional>
	Optional(std::nullptr_t it) :data(), pData(nullptr) {}
	// <中身入り>
	Optional(const T& it) :data(), pData(new(&data)T(it)) {}

	// <コピーコンストラクタ>
	Optional(const Optional<T>& it) :data(), pData(it ? new(&data) T(*it) : nullptr) {}
	// <ムーブコンストラクタ>
	Optional(Optional<T>&& it)noexcept : data(), pData(it ? new(&data) T(std::move(*it)) : nullptr) {}

	// <引数付き>
	template<typename ...Args>
	Optional(Args ...args) : data(), pData(new(&data) T(args...)) {}

	// <デストラクタ>
	~Optional()
	{
		if (pData)
			pData->~T();
	}

	// <代入演算子 (空)>
	Optional<T> operator=(std::nullptr_t it) {
		if (pData) pData->~T();
		pData = nullptr;
		return *this;
	}
	// <代入演算子コピー>
	Optional<T> operator=(const Optional& it) {
		if (pData) pData->~T();
		pData = it ? new(&data) T(*it) : nullptr;
		return *this;
	}
	// <代入演算子ムーブ>
	Optional<T> operator=(Optional&& it) {
		if (pData) pData->~T();
		pData = it ? new(&data) T(std::move(*it)) : nullptr;
		return *this;
	}

	// <値取得>
	T& operator*() const { return *pData; }
	// <値取得>
	T* operator->() const { return pData; }
	// <値があるか確認>
	operator bool() const { return pData != nullptr; }
	// ＝
	bool operator==(const Optional& it) const { return pData == it.pData; }
	// ≠
	bool operator!=(const Optional& it) const { return pData != it.pData; }
	// <空でなければ実行>
	template <typename Func>
	void ifPresent(Func func) const { if (pData) func(*pData); }
	// <空でなければ実行し結果を返す>
	template <typename Func>
	Optional<T> map(Func func) const
	{
		if (pData) return func(*pData);
		else return nullptr;
	}
	// <trueであればそのまま、falseであれば空を返す>
	template <typename Func>
	Optional<T> filter(Func func) const
	{
		if (pData)
			if (func(*pData))
				return *this;
		return nullptr;
	}
	// <値取得 or デフォルト値>
	const T& orElse(const T& els) const { return pData ? *pData : els; }
	// <値取得 or デフォルト値生成関数>
	template <typename Func>
	T orElseGet(Func func) const
	{
		if (pData) return *pData;
		else return func();
	}
};

#endif