#pragma once
#include <stdint.h>
#include <iostream>


#define KGLOG(x) std::cout << x << std::endl;
#define KGLOG3(v) std::cout << v.x << "," << v.y << "," << v.z << std::endl;


template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T, typename ... Args>
constexpr Scope<T> CreateScope(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}
