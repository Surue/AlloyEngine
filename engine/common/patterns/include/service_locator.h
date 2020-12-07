#pragma once

#include <type_traits>

namespace alloy {
template<class T, class NullT>
class ServiceLocator {
	static_assert(std::is_base_of<T, NullT>::value, "TNull has to be a subtype of T");
public:
	static void Initialize() {
		service_ = &nullService_;
	}

	static T& Get() { return *service_; }

	static void Assign(T* service) {
		if (!service) {
			service_ = &nullService_;
		}
		else {
			service_ = service;
		}
	}
private:
	static T* service_;
	static NullT nullService_;
};

template <class T, class NullT> NullT ServiceLocator<T, NullT> ::nullService_;
template <class T, class NullT> T* ServiceLocator<T, NullT> ::service_ = &ServiceLocator<T, NullT>::nullService_;
} //namespace alloy