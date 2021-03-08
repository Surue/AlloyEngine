#pragma once

namespace alloy::ecs {

class ISystemInit {
public:
	virtual void OnInit() = 0;
};

class ISystemUpdate {
public:
	virtual void OnUpdate() = 0;
};

class ISystemDestroy {
public:
	virtual void OnDestroy() = 0;
};

class ISystemDraw {
public:
	virtual void OnDraw() = 0;
};

class System {
public:
	System() {
		
	}
};
} //namespace alloy::ecs