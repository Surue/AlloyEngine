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

class System {
public:

	System(const std::vector<SystemExecutionFlags>& flags) {
		for (const auto systemExecutionFlags : flags) {
			AddFlag(systemExecutionFlags);
		}
	}
	
	virtual ~System() = default;

	bool HasFlag(SystemExecutionFlags f) const {
		return systemFlags_.test(static_cast<uint32_t>(f));
	}

	virtual void OnInit() {}
	
	virtual void OnUpdate() {}
	
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