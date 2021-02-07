#pragma once

#define USE_REMOTERY = true
#include <lib/Remotery.h>

#define BeginProfiling(name){ rmt_BeginCPUSample(name, 0);}
#define EndProfiling(name){ rmt_EndCPUSample(); }

namespace alloy {
class Profiler {
public:
	Profiler() {
		rmt_CreateGlobalInstance(&remotery_);
	}

	~Profiler() {
		rmt_DestroyGlobalInstance(remotery_);
	}

	void BeginProfile(rmtU32 name) {
	}

	void EndProfile() {
	}

private:
	Remotery* remotery_;
};
}
