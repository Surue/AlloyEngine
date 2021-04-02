#pragma once

#include <type_traits>
#include <typeinfo>
#include <cstddef>
#include <map>

//TODO Find namespace for pattern
namespace alloy {
class IService {

};
/**
 * TODO
 * 1. Should be an object with a life time
 * 2. Store real object to avoid de-referencing
 * 3. As their is inheritance typeid is working in run-time, find a compile time solution
 */
class ServiceLocator {
public:
	template<typename T>
	static T& Get() {
		static_assert(std::is_base_of<IService, T>::value, "Impossible to get from the ServiceLocator a class that doesn't inherit from IService");
		//TODO This is a fucking horrible trick
		return static_cast<T&>(*service_[typeid(T).hash_code()]); 
	}

	template<typename T>
	static void Provide(T* service) {
		static_assert(std::is_base_of<IService, T>::value, "Impossible to provide to the ServiceLocator a class that doesn't inherit from IService");
		//TODO Add security to check if the Service exist
		service_[typeid(T).hash_code()] = service;
	}
private:
	//TODO This is a fucking horrible trick
	inline static std::map<size_t, IService*> service_ = std::map<size_t, IService*>();
};
} //namespace alloy