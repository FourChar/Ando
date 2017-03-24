#ifndef GO_GLOBALVARS_HPP
#define GO_GLOBALVARS_HPP

#ifdef _MSC_VER
#pragma once
#endif

namespace ando {
	namespace process_specific {
		namespace CounterStrike {
			class CGlobalOffensiveInstance;

			class CGlobalOffensiveGlobalVars {
				friend CGlobalOffensiveInstance;

			private:
				float realTime;
				__int32 frameCount;
				float absoluteFrameCount;
				__int32 _unknown;
				float currentTime;
				float frameTime;
				unsigned __int32 maxClients;
				__int32 tickCount;
				float intervalPerTick;
				float interpolationAmount;

			public:
				float getRealTime() { return this->realTime; }
				__int32 getFrameCount() { return this->frameCount; }
				float getAbsoluteFrameCount() { return this->absoluteFrameCount; }
				float getCurrentTime() { return this->currentTime; }
				float getFrameTime() { return this->frameTime; }
				unsigned __int32 getMaxClients() { return this->maxClients; }
				__int32 getTickCount() { return this->tickCount; }
				float getIntervalPerTick() { return this->intervalPerTick; }
				float getInterpolationAmount() { return this->interpolationAmount; }
			};
		}
	}
}

#endif // GO_CBASEPLAYER_HPP