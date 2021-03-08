#pragma once
#include <bitset>
#include <functional>

namespace alloy::ecs {

enum class SystemExecutionFlags : uint32_t {
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
	
	virtual void OnInit() = 0;
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
	System() {
		
	}

protected:
	void AddFlag(SystemExecutionFlags f) {
		systemFlags_.set(static_cast<int>(f));
	}

	void RemoveFlag(SystemExecutionFlags f) {
		systemFlags_.reset(static_cast<int>(f));
	}

	const std::bitset<static_cast<size_t>(SystemExecutionFlags::LENGTH)>& GetSystemFlag() const {
		return systemFlags_;
	}

private:
	std::bitset<static_cast<size_t>(SystemExecutionFlags::LENGTH)> systemFlags_;
};
} //namespace alloy::ecs