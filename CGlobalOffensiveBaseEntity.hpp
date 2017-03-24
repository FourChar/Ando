#ifndef GO_CBASEPLAYER_HPP
#define GO_CBASEPLAYER_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include "IBaseAndoEntity.hpp"

#include "Vector2.hpp"
#include "Vector3.hpp"

namespace ando {
	namespace process_specific {
		namespace CounterStrike {
			class CGlobalOffensiveInstance;

			class CGlobalOffensiveBaseEntity : public IBaseAndoEntity {
				friend CGlobalOffensiveInstance;

			private:
				__int32 m_iClassId;
				__int32 m_iIndex;
				__int32 m_iHealth;
				__int32 m_iTeamNum;
				__int32 m_ArmorValue;
				__int32 m_fFlags;
				__int32 m_iShotsFired;

				::ando::math::Vector3<float> m_vecViewOffset;
				::ando::math::Vector3<float> m_vecVelocity;
				::ando::math::Vector3<float> m_vecOrigin;
				::ando::math::Vector2<float> m_aimPunchAngle;
				::ando::math::Vector2<float> m_aimPunchAngleVel;
				::ando::math::Vector2<float> m_viewPunchAngle;

				float m_flFlashMaxAlpha;
				float m_flFlashDuration;

				bool m_bDormant;
				bool m_bHasHelmet;
				bool m_bHasDefuser;
				bool m_bInReload;
				bool m_bIsDefusing;
				bool m_bIsScoped;
				bool m_bSpotted;
				bool m_lifeState;

			public:
				CGlobalOffensiveBaseEntity &operator =(const CGlobalOffensiveBaseEntity &rhs) {
					this->m_iClassId = rhs.m_iClassId;
					this->m_iIndex = rhs.m_iIndex;
					this->m_iHealth = rhs.m_iHealth;
					this->m_iTeamNum = rhs.m_iTeamNum;
					this->m_ArmorValue = rhs.m_ArmorValue;
					this->m_fFlags = rhs.m_fFlags;
					this->m_iShotsFired = rhs.m_iShotsFired;

					this->m_vecViewOffset = rhs.m_vecViewOffset;
					this->m_vecVelocity = rhs.m_vecVelocity;
					this->m_vecOrigin = rhs.m_vecOrigin;
					this->m_aimPunchAngle = rhs.m_aimPunchAngle;
					this->m_aimPunchAngleVel = rhs.m_aimPunchAngleVel;
					this->m_viewPunchAngle = rhs.m_viewPunchAngle;

					this->m_flFlashMaxAlpha = rhs.m_flFlashMaxAlpha;
					this->m_flFlashDuration = rhs.m_flFlashDuration;

					this->m_bDormant = rhs.m_bDormant;
					this->m_bHasHelmet = rhs.m_bHasHelmet;
					this->m_bHasDefuser = rhs.m_bHasDefuser;
					this->m_bInReload = rhs.m_bInReload;
					this->m_bIsDefusing = rhs.m_bIsDefusing;
					this->m_bIsScoped = rhs.m_bIsScoped;
					this->m_bSpotted = rhs.m_bSpotted;
					this->m_lifeState = rhs.m_lifeState;
				}

			public:
				__int32 getClassId() { return this->m_iClassId; }
				__int32 getIndex() { return this->m_iIndex; }
				__int32 getHealth() { return this->m_iHealth; }
				__int32 getTeam() { return this->m_iTeamNum; }
				__int32 getArmor() { return this->m_ArmorValue; }
				__int32 getFlags() { return this->m_fFlags; }
				__int32 getShotsFired() { return this->m_iShotsFired; }

				::ando::math::Vector3<float> getViewOffset() { return this->m_vecViewOffset; }
				::ando::math::Vector3<float> getVelocity() { return this->m_vecVelocity; }
				::ando::math::Vector3<float> getOrigin() { return this->m_vecOrigin; }
				::ando::math::Vector3<float> getEyeOrigin() { return (this->m_vecOrigin + this->m_vecViewOffset); }
				::ando::math::Vector2<float> getAimPunchAngle() { return this->m_aimPunchAngle; }
				::ando::math::Vector2<float> getAimPunchAngleVelocity() { return this->m_aimPunchAngleVel; }
				::ando::math::Vector2<float> getViewPunchAngle() { return this->m_viewPunchAngle; }

				float getFlashMaxAlpha() { return this->m_flFlashMaxAlpha; }
				float getFlashDuration() { return this->m_flFlashDuration; }

				bool isDormant() { return this->m_bDormant; }
				bool hasHelmet() { return this->m_bHasHelmet; }
				bool hasDefuser() { return this->m_bHasDefuser; }
				bool isReloading() { return this->m_bInReload; }
				bool isDefusing() { return this->m_bIsDefusing; }
				bool isScoped() { return this->m_bIsScoped; }
				bool isSpotted() { return this->m_bSpotted; }
				bool isDead() { return this->m_lifeState; }
			};
		}
	}
}

#endif // GO_CBASEPLAYER_HPP