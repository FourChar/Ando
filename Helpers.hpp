#ifndef HELPERS_HPP
#define HELPERS_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <string>
#include <locale>
#include <codecvt>

template <class Interface>
inline void SafeRelease(Interface **ppInterfaceToRelease) {
	if (*ppInterfaceToRelease != nullptr) {
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = nullptr;
	}
}

template <typename Facet>
struct deletable_facet : Facet {
	using Facet::Facet;
};

typedef std::wstring_convert<deletable_facet<std::codecvt<wchar_t, char, std::mbstate_t>>> stringConvertor;

#endif // HELPERS_HPP