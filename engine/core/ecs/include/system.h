#pragma once
#include <bitset>
#include <functional>
#include <iostream>

namespace alloy::ecs {

enum class SystemExecutionFlags : uint32_t { //TODO Use a type
	INIT = 0,
	UPDATE,
	DRAW,
	DESTROY,
	LENGTH
};

template<SystemExecutionFlags  T>
class ISystemExecutionFunction {
public:
	ISystemExecutionFunction() = default;
	virtual ~ISystemExecutionFunction() = default;
protected:
	void SetFlag(const std::function<void(SystemExecutionFlags)> flagUpdaterFunction) {
		flagUpdaterFunction(T);
	}

private:
};

class ISystemInit : ISystemExecutionFunction<SystemExecutionFlags::INIT>{
public:
	ISystemInit(const std::function<void(SystemExecutionFlags)> flagUpdaterFunction) {
		SetFlag(flagUpdaterFunction);
	}
	
	virtual void OnInit(){}
};

class ISystemUpdate : ISystemExecutionFunction<SystemExecutionFlags::UPDATE> {
public:
	ISystemUpdate(const std::function<void(SystemExecutionFlags)> flagUpdaterFunction) {
		SetFlag(flagUpdaterFunction);
	}
	
	virtual void OnUpdate() = 0;
};

class ISystemDestroy : ISystemExecutionFunction<SystemExecutionFlags::DESTROY> {
public:
	ISystemDestroy(const std::function<void(SystemExecutionFlags)> flagUpdaterFunction) {
		SetFlag(flagUpdaterFunction);
	}
	
	virtual void OnDestroy() = 0;
};

class ISystemDraw : ISystemExecutionFunction<SystemExecutionFlags::DRAW> {
public:
	ISystemDraw(const std::function<void(SystemExecutionFlags)> flagUpdaterFunction) {
		SetFlag(flagUpdaterFunction);
	}
	
	virtual void OnDraw() = 0;
};

class System {
public:
	System(std::vector<SystemExecutionFlags> vec) {
		for (const auto systemExecutionFlags : vec) {
			AddFlag(systemExecutionFlags);
		}
	}

	bool HasFlag(SystemExecutionFlags f) const {
		return systemFlags_.test(static_cast<uint32_t>(f));
	}

	virtual void OnInit() {
		std::cout << "Parent Init()\n";
	}
	virtual void OnUpdate() {
		std::cout << "Parent Update()\n";
	}
	virtual void OnDraw() {}
	virtual void OnDestroy() {}

	const std::bitset<static_cast<size_t>(SystemExecutionFlags::LENGTH)>& GetSystemFlag() const {
		return systemFlags_;
	}

protected:
	void AddFlag(SystemExecutionFlags f) {
		systemFlags_.set(static_cast<int>(f));
	}

	void RemoveFlag(SystemExecutionFlags f) {
		systemFlags_.reset(static_cast<int>(f));
	}

private:
	std::bitset<static_cast<size_t>(SystemExecutionFlags::LENGTH)> systemFlags_;
};
} //namespace alloy::ecs