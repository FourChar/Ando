#include "CGlobalOffensiveInstance.hpp"

#include "Rect.hpp"
#include "Utils.hpp"

#include "MemoryBlock.hpp"

namespace ando {
	namespace process_specific {
		namespace CounterStrike {
			// Constructors & Destructors
			CGlobalOffensiveInstance::CGlobalOffensiveInstance(::std::shared_ptr<::ando::logger::ILogger> logger, ::std::shared_ptr<::ando::memory::IProcessHandler> processHandler, ::std::shared_ptr<::ando::overlay::OverlayInstance> targetInstance)
				: IBaseGameInstance(logger, processHandler, targetInstance) {
				this->setShared(new CGlobalOffensiveShared());
				this->initialize();
			}
			CGlobalOffensiveInstance::CGlobalOffensiveInstance(::std::shared_ptr<::ando::memory::IProcessHandler> processHandler, ::std::shared_ptr<::ando::overlay::OverlayInstance> targetInstance)
				: IBaseGameInstance(processHandler, targetInstance) {
				this->setShared(new CGlobalOffensiveShared());
				this->initialize();
			}
			CGlobalOffensiveInstance::CGlobalOffensiveInstance(::std::shared_ptr<::ando::overlay::OverlayInstance> targetInstance) : IBaseGameInstance(targetInstance) {
				this->setShared(new CGlobalOffensiveShared());
				this->initialize();
			}
			CGlobalOffensiveInstance::CGlobalOffensiveInstance() : IBaseGameInstance() {
				this->setShared(new CGlobalOffensiveShared());
				this->initialize();
			}
			
			CGlobalOffensiveInstance::~CGlobalOffensiveInstance() {

			}

			// Public Functions
			bool CGlobalOffensiveInstance::worldToScreen(::ando::math::Vector3<float> from, ::ando::math::Vector2<float>& to) {
				::ando::math::Rect<float> screenRect;
				screenRect.setX(this->getTargetInstance()->getX<float>());
				screenRect.setY(this->getTargetInstance()->getY<float>());
				screenRect.setWidth(this->getTargetInstance()->getWidth<float>());
				screenRect.setHeight(this->getTargetInstance()->getHeight<float>());

				return ando::math::worldToScreen(this->getShared()->getViewMatrix(), from, to, screenRect);
			}

			// Protected Functions
			void CGlobalOffensiveInstance::initialize() {
				this->getLogger()->log(::ando::logger::ELogLevel::LOG_DEBUG, "{CGlobalOffensiveInstance::initialize} Initializing!");

				if (this->hasProcessHandler()) {
					this->clientModule = this->getProcessHandler()->getModuleByName("client.dll");
					this->engineModule = this->getProcessHandler()->getModuleByName("engine.dll");

					if (this->clientModule) {
						this->getLogger()->log(::ando::logger::ELogLevel::LOG_DEBUG, "{CGlobalOffensiveInstance::initialize} Found \"%s\": 0x%.8X (Size: 0x%.8X)",
							this->clientModule->getModuleName().c_str(),
							this->clientModule->getBaseAddress(),
							this->clientModule->getSize());
					}
					else
						this->getLogger()->log(::ando::logger::ELogLevel::LOG_WARNING, "{CGlobalOffensiveInstance::initialize} Unable to find \"client.dll\"!");

					if (this->engineModule) {
						this->getLogger()->log(::ando::logger::ELogLevel::LOG_DEBUG, "{CGlobalOffensiveInstance::initialize} Found \"%s\": 0x%.8X (Size: 0x%.8X)",
							this->engineModule->getModuleName().c_str(),
							this->engineModule->getBaseAddress(),
							this->engineModule->getSize());
					}
					else
						this->getLogger()->log(::ando::logger::ELogLevel::LOG_WARNING, "{CGlobalOffensiveInstance::initialize} Unable to find \"engine.dll\"!");
				}
				else {
					this->getLogger()->log(::ando::logger::ELogLevel::LOG_WARNING, "{CGlobalOffensiveInstance::initialize} No ::ando::memory::IProcessHandler instance!");
				}

				this->getLogger()->log(::ando::logger::ELogLevel::LOG_DEBUG, "{CGlobalOffensiveInstance::initialize} Adding Offsets!");

				this->getOffsetHandler()->addOffset("GlobalVars", 0x00AA13A0);
				this->getOffsetHandler()->addOffset("LocalPlayer", 0x00AAD704);
				this->getOffsetHandler()->addOffset("ViewMatrix", 0x04AC2424);
				this->getOffsetHandler()->addOffset("PlayerResource", 0x04AF0ADC);
				this->getOffsetHandler()->addOffset("RadarBase", 0x04F0560C);
				this->getOffsetHandler()->addOffset("WeaponTable", 0x04F17A1C);

				this->getOffsetHandler()->addOffset("ClientState", 0x005CB524);
				this->getOffsetHandler()->addOffset("ClientState:GetState", 0x100);
				this->getOffsetHandler()->addOffset("ClientState:GetLocalPlayer", 0x178);
				this->getOffsetHandler()->addOffset("ClientState:GetMapDirectory", 0x180);
				this->getOffsetHandler()->addOffset("ClientState:GetMap", 0x284);
				this->getOffsetHandler()->addOffset("ClientState:GetViewAngles", 0x4D0C);
				this->getOffsetHandler()->addOffset("ClientState:GetPlayerInfo", 0x523C);

				this->getOffsetHandler()->addOffset("EntityList", 0x04AD0884);
				this->getOffsetHandler()->addOffset("EntityList:MaxUsedServerIndex", 0x24);

				this->getOffsetHandler()->addOffset("PlayerResource:Name", 0x09D8);
				this->getOffsetHandler()->addOffset("PlayerResource:Ping", this->getOffsetHandler()->getOffsetByName("PlayerResource:Name") + ((ANDO_COUNTERSTRIKE_GLOBALOFFENSIVE_MAX_PLAYERS + 1) * 4));
				this->getOffsetHandler()->addOffset("PlayerResource:Kills", this->getOffsetHandler()->getOffsetByName("PlayerResource:Ping") + ((ANDO_COUNTERSTRIKE_GLOBALOFFENSIVE_MAX_PLAYERS + 1) * 4));
				this->getOffsetHandler()->addOffset("PlayerResource:Assists", this->getOffsetHandler()->getOffsetByName("PlayerResource:Kills") + ((ANDO_COUNTERSTRIKE_GLOBALOFFENSIVE_MAX_PLAYERS + 1) * 4));
				this->getOffsetHandler()->addOffset("PlayerResource:Deaths", this->getOffsetHandler()->getOffsetByName("PlayerResource:Assists") + ((ANDO_COUNTERSTRIKE_GLOBALOFFENSIVE_MAX_PLAYERS + 1) * 4));
				this->getOffsetHandler()->addOffset("PlayerResource:IsConnected", this->getOffsetHandler()->getOffsetByName("PlayerResource:Deaths") + ((ANDO_COUNTERSTRIKE_GLOBALOFFENSIVE_MAX_PLAYERS + 1) * 4));
				this->getOffsetHandler()->addOffset("PlayerResource:Team", this->getOffsetHandler()->getOffsetByName("PlayerResource:IsConnected") + ((ANDO_COUNTERSTRIKE_GLOBALOFFENSIVE_MAX_PLAYERS + 1) * 1) + 3);
				this->getOffsetHandler()->addOffset("PlayerResource:PendingTeam", this->getOffsetHandler()->getOffsetByName("PlayerResource:Team") + ((ANDO_COUNTERSTRIKE_GLOBALOFFENSIVE_MAX_PLAYERS + 1) * 4));
				this->getOffsetHandler()->addOffset("PlayerResource:IsAlive", this->getOffsetHandler()->getOffsetByName("PlayerResource:PendingTeam") + ((ANDO_COUNTERSTRIKE_GLOBALOFFENSIVE_MAX_PLAYERS + 1) * 4));
				this->getOffsetHandler()->addOffset("PlayerResource:Health", this->getOffsetHandler()->getOffsetByName("PlayerResource:IsAlive") + ((ANDO_COUNTERSTRIKE_GLOBALOFFENSIVE_MAX_PLAYERS + 1) * 1) + 3);
				this->getOffsetHandler()->addOffset("PlayerResource:CompetitiveRanking", 0x1A44);
				this->getOffsetHandler()->addOffset("PlayerResource:CompetitiveWins", 0x1B48);

				this->getOffsetHandler()->addOffset("Entity:Index", 0x64);
				this->getOffsetHandler()->addOffset("Entity:IsDormant", 0xE9);
				this->getOffsetHandler()->addOffset("Entity:Team", 0xF0);
				this->getOffsetHandler()->addOffset("Entity:Health", 0xFC);
				this->getOffsetHandler()->addOffset("Entity:Flags", 0x100);
				this->getOffsetHandler()->addOffset("Entity:ViewOffset", 0x104);
				this->getOffsetHandler()->addOffset("Entity:Velocity", 0x110);
				this->getOffsetHandler()->addOffset("Entity:Origin", 0x134);
				this->getOffsetHandler()->addOffset("Entity:LifeState", 0x25B);
				this->getOffsetHandler()->addOffset("Entity:ViewPunchAngle", 0x3010);
				this->getOffsetHandler()->addOffset("Entity:AimPunchAngle", 0x301C);
				this->getOffsetHandler()->addOffset("Entity:AimPunchAngleVelocity", 0x3028);
				this->getOffsetHandler()->addOffset("Entity:InReload", 0x3245);
				this->getOffsetHandler()->addOffset("Entity:IsScoped", 0x389C);
				this->getOffsetHandler()->addOffset("Entity:IsDefusing", 0x38A4);
				this->getOffsetHandler()->addOffset("Entity:ShotsFired", 0xA2C0);
				this->getOffsetHandler()->addOffset("Entity:FlashMaxAlpha", 0xA304);
				this->getOffsetHandler()->addOffset("Entity:FlashDuration", 0xA308);
				this->getOffsetHandler()->addOffset("Entity:HasHelmet", 0xA9FC);
				this->getOffsetHandler()->addOffset("Entity:Armor", 0xAA04);
				this->getOffsetHandler()->addOffset("Entity:HasDefuser", 0xAA14);
			}

			void CGlobalOffensiveInstance::processUpdate() {
				{ // GlobalVars
					this->getMutex().lock();
					auto pointer = this->getProcessHandler()->getReader()->readLong(this->getOffsetHandler()->getRelativeAddress(this->clientModule->getBaseAddress(), "GlobalVars"));
					this->getProcessHandler()->getReader()->read(pointer, &this->getShared()->getGlobalVars());
					this->getMutex().unlock();
				}
				{ // LocalPlayer
					this->getMutex().lock();
					auto pointer = this->getProcessHandler()->getReader()->readLong(this->getOffsetHandler()->getRelativeAddress(this->clientModule->getBaseAddress(), "LocalPlayer"));
					this->readEntityFromAddress(pointer, &this->getShared()->getLocalPlayer());
					this->getMutex().unlock();
				}
				{ // ViewMatrix
					this->getMutex().lock();
					this->getProcessHandler()->getReader()->read(this->getOffsetHandler()->getRelativeAddress(this->clientModule->getBaseAddress(), "ViewMatrix"), this->getShared()->getViewMatrix().getData(), 4 * 4 * sizeof(float));
					this->getMutex().unlock();
				}

				{ // EntityList
					::std::vector<::std::shared_ptr<::ando::process_specific::CounterStrike::CGlobalOffensiveBaseEntity>> entityList;

					for (::std::size_t i = 1; i < this->getShared()->getGlobalVars().getMaxClients(); i++) {
						auto entity = this->readEntityFromIndex(i);
						if (entity == nullptr)
							continue;
						if (entity->isDormant())
							continue;
						if (((entity->getTeam() != 2) && (entity->getTeam() != 3)) || (i > 64)) {
							entityList.emplace_back(entity);
							continue;
						}

						// We know it's a player here
						if (entity->isDead())
							continue;
						if ((entity->getHealth() <= 0) || (entity->getHealth() > 100))
							continue;

						entityList.emplace_back(entity);
					}

					this->getMutex().lock();
					this->getEntityList() = entityList;
					this->getMutex().unlock();
				}
			}

			::std::shared_ptr<::ando::process_specific::CounterStrike::CGlobalOffensiveBaseEntity> CGlobalOffensiveInstance::readEntityFromIndex(::std::size_t index) {
				DWORD_PTR baseAddress = this->getProcessHandler()->getReader()->readLong(this->getOffsetHandler()->getRelativeAddress(this->clientModule->getBaseAddress(), "EntityList") + (index * 0x10));
				if (baseAddress == 0)
					return nullptr;

				auto entity = ::std::make_shared<::ando::process_specific::CounterStrike::CGlobalOffensiveBaseEntity>();
				if (!this->readEntityFromAddress(baseAddress, entity.get()))
					return nullptr;

				return entity;
			}
			
			bool CGlobalOffensiveInstance::readEntityFromAddress(::std::uint64_t baseAddress, ::ando::process_specific::CounterStrike::CGlobalOffensiveBaseEntity *entity) {
				// ClassId
				{
					auto IClientNetworkable = this->getProcessHandler()->getReader()->readLong(baseAddress + 0x8);
					auto secondFunction = this->getProcessHandler()->getReader()->readLong(IClientNetworkable + (0x4 * 2));
					auto movEax = this->getProcessHandler()->getReader()->readLong(secondFunction + 0x1);

					this->getProcessHandler()->getReader()->read(movEax + 0x14, &entity->m_iClassId);
				}

				// Index
				this->getProcessHandler()->getReader()->read(this->getOffsetHandler()->getRelativeAddress(baseAddress, "Entity:Index"), &entity->m_iIndex);

				// 0x00E9 - 0x25C
				{
					auto blockOffset = this->getOffsetHandler()->getOffsetByName("Entity:IsDormant");
					auto blockSize = this->getOffsetHandler()->getOffsetByName("Entity:LifeState") - blockOffset + sizeof(entity->m_lifeState);

					auto block = ::std::make_unique<memory::MemoryBlock>(this->getProcessHandler(), baseAddress, blockSize, blockOffset);

					if (!block->readSection())
						return false;

					block->getAt(blockOffset, &entity->m_bDormant, 1);
					block->getAt(this->getOffsetHandler()->getOffsetByName("Entity:Team"), &entity->m_iTeamNum, 4);
					block->getAt(this->getOffsetHandler()->getOffsetByName("Entity:Health"), &entity->m_iHealth, 4);
					block->getAt(this->getOffsetHandler()->getOffsetByName("Entity:Flags"), &entity->m_fFlags, 4);
					block->getAt(this->getOffsetHandler()->getOffsetByName("Entity:ViewOffset"), entity->m_vecViewOffset.getXData(), 12);
					block->getAt(this->getOffsetHandler()->getOffsetByName("Entity:Velocity"), entity->m_vecVelocity.getXData(), 12);
					block->getAt(this->getOffsetHandler()->getOffsetByName("Entity:Origin"), entity->m_vecOrigin.getXData(), 12);
					block->getAt(this->getOffsetHandler()->getOffsetByName("Entity:LifeState"), &entity->m_lifeState, 1);
				}

				// 0x3010 - 0x38A8
				{
					auto blockOffset = this->getOffsetHandler()->getOffsetByName("Entity:ViewPunchAngle");
					auto blockSize = this->getOffsetHandler()->getOffsetByName("Entity:IsDefusing") - blockOffset + sizeof(entity->m_bIsDefusing);

					auto block = ::std::make_unique<memory::MemoryBlock>(this->getProcessHandler(), baseAddress, blockSize, blockOffset);

					if (!block->readSection())
						return false;

					block->getAt(blockOffset, entity->m_viewPunchAngle.getXData(), 8);
					block->getAt(this->getOffsetHandler()->getOffsetByName("Entity:AimPunchAngle"), entity->m_aimPunchAngle.getXData(), 8);
					block->getAt(this->getOffsetHandler()->getOffsetByName("Entity:AimPunchAngleVelocity"), entity->m_aimPunchAngleVel.getXData(), 8);
					block->getAt(this->getOffsetHandler()->getOffsetByName("Entity:InReload"), &entity->m_bInReload, 1);
					block->getAt(this->getOffsetHandler()->getOffsetByName("Entity:IsScoped"), &entity->m_bIsScoped, 1);
					block->getAt(this->getOffsetHandler()->getOffsetByName("Entity:IsDefused"), &entity->m_bIsDefusing, 1);
				}

				// 0xA2C0 - 0xAA18
				{
					auto blockOffset = this->getOffsetHandler()->getOffsetByName("Entity:ShotsFired");
					auto blockSize = this->getOffsetHandler()->getOffsetByName("Entity:HasDefuser") - blockOffset + sizeof(entity->m_bHasDefuser);

					auto block = ::std::make_unique<memory::MemoryBlock>(this->getProcessHandler(), baseAddress, blockSize, blockOffset);

					if (!block->readSection())
						return false;

					block->getAt(blockOffset, &entity->m_iShotsFired, 4);
					block->getAt(this->getOffsetHandler()->getOffsetByName("Entity:FlashMaxAlpha"), &entity->m_flFlashMaxAlpha, 4);
					block->getAt(this->getOffsetHandler()->getOffsetByName("Entity:FlashDuration"), &entity->m_flFlashDuration, 4);
					block->getAt(this->getOffsetHandler()->getOffsetByName("Entity:HasHelmet"), &entity->m_bHasHelmet, 1);
					block->getAt(this->getOffsetHandler()->getOffsetByName("Entity:Armor"), &entity->m_ArmorValue, 4);
					block->getAt(this->getOffsetHandler()->getOffsetByName("Entity:HasDefuser"), &entity->m_bHasDefuser, 1);
				}

				return true;
			}
		}
	}
}