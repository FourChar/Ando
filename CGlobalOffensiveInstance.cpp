#include "CGlobalOffensiveInstance.hpp"
#include "CGlobalOffensiveEntityInfo.hpp"
#include "EGlobalOffensiveClientClassID.hpp"
#include "CGlobalOffensivePlayerEntity.hpp"

#include "Rect.hpp"
#include "Utils.hpp"

#include "MemoryBlock.hpp"

namespace ando {
	namespace process_specific {
		namespace CounterStrike {
			namespace GlobalOffensive {
				// Constructors & Destructors
				CInstance::CInstance(::std::shared_ptr<::ando::logger::ILogger> logger, ::std::shared_ptr<::ando::memory::CProcessHandler> processHandler, ::std::shared_ptr<::ando::overlay::OverlayInstance> targetInstance)
					: IBaseGameInstance(logger, processHandler, targetInstance) {
					this->setShared(new GameShared());
					this->initialize();
				}
				CInstance::CInstance(::std::shared_ptr<::ando::memory::CProcessHandler> processHandler, ::std::shared_ptr<::ando::overlay::OverlayInstance> targetInstance)
					: IBaseGameInstance(processHandler, targetInstance) {
					this->setShared(new GameShared());
					this->initialize();
				}
				CInstance::CInstance(::std::shared_ptr<::ando::overlay::OverlayInstance> targetInstance) : IBaseGameInstance(targetInstance) {
					this->setShared(new GameShared());
					this->initialize();
				}
				CInstance::CInstance() : IBaseGameInstance() {
					this->setShared(new GameShared());
					this->initialize();
				}

				CInstance::~CInstance() {

				}

				// Public Functions
				bool CInstance::worldToScreen(::ando::math::Vector3<float> from, ::ando::math::Vector2<float>& to) {
					::ando::math::Rect<float> screenRect;
					screenRect.setX(this->getTargetInstance()->getX<float>());
					screenRect.setY(this->getTargetInstance()->getY<float>());
					screenRect.setWidth(this->getTargetInstance()->getWidth<float>());
					screenRect.setHeight(this->getTargetInstance()->getHeight<float>());

					return ando::math::worldToScreen(this->getShared()->getViewMatrix(), from, to, screenRect);
				}

				// Protected Functions
				void CInstance::initialize() {
					this->getLogger()->log(::ando::logger::ELogLevel::LOG_DEBUG, "{CGlobalOffensiveInstance::initialize} Initializing!");

					if (this->hasProcessHandler()) {
						this->getLogger()->log(::ando::logger::ELogLevel::LOG_DEBUG, "{CGlobalOffensiveInstance::initialize} Initializing!");

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

					this->getOffsetHandler()->addOffset("GlobalVars", 0xA69140);
					this->getOffsetHandler()->addOffset("LocalPlayer", 0xAADFFC);
					this->getOffsetHandler()->addOffset("ViewMatrix", 0x4A7C0B4);
					this->getOffsetHandler()->addOffset("WeaponTable", 0x4ED1810);

					this->getOffsetHandler()->addOffset("EntityList", 0x4A8A654);
					this->getOffsetHandler()->addOffset("EntityList:MaxUsedServerIndex", 0x24);

					this->getOffsetHandler()->addOffset("RadarBase", 0x4EBF34C);
					this->getOffsetHandler()->addOffset("RadarBase:Pointer", 0x00000054);

					this->getOffsetHandler()->addOffset("ClientState", 0x5A32FC);
					this->getOffsetHandler()->addOffset("ClientState:GetState", 0x100);
					this->getOffsetHandler()->addOffset("ClientState:GetLocalPlayer", 0x178);
					this->getOffsetHandler()->addOffset("ClientState:GetMapDirectory", 0x180);
					this->getOffsetHandler()->addOffset("ClientState:GetMap", 0x284);
					this->getOffsetHandler()->addOffset("ClientState:GetMaxPlayers", 0x308);
					this->getOffsetHandler()->addOffset("ClientState:IsHLTV", 0x4CC4);
					this->getOffsetHandler()->addOffset("ClientState:GetViewAngles", 0x4D0C);
					this->getOffsetHandler()->addOffset("ClientState:GetPlayerInfo", 0x523C);

					this->getOffsetHandler()->addOffset("PlayerResource", 0x2ECAD5C);
					this->getOffsetHandler()->addOffset("PlayerResource:Name", 0x09E0);
					this->getOffsetHandler()->addOffset("PlayerResource:Ping", 0x0AE4);
					this->getOffsetHandler()->addOffset("PlayerResource:Kills", 0x0BE8);
					this->getOffsetHandler()->addOffset("PlayerResource:Assists", 0x0CEC);
					this->getOffsetHandler()->addOffset("PlayerResource:Deaths", 0x0DF0);
					this->getOffsetHandler()->addOffset("PlayerResource:IsConnected", 0x0EF4);
					this->getOffsetHandler()->addOffset("PlayerResource:Team", 0x0F38);
					this->getOffsetHandler()->addOffset("PlayerResource:PendingTeam", 0x103C);
					this->getOffsetHandler()->addOffset("PlayerResource:IsAlive", 0x1140);
					this->getOffsetHandler()->addOffset("PlayerResource:Health", 0x1184);
					this->getOffsetHandler()->addOffset("PlayerResource:Armor", 0x183C);
					this->getOffsetHandler()->addOffset("PlayerResource:Score", 0x1940);
					this->getOffsetHandler()->addOffset("PlayerResource:CompetitiveRanking", 0x1A44);
					this->getOffsetHandler()->addOffset("PlayerResource:CompetitiveWins", 0x1B48);
					this->getOffsetHandler()->addOffset("PlayerResource:Clan", 0x4120);

					this->getOffsetHandler()->addOffset("Entity:Index", 0x64);
					this->getOffsetHandler()->addOffset("Entity:IsDormant", 0xE9);
					this->getOffsetHandler()->addOffset("Entity:Team", 0xF0);
					this->getOffsetHandler()->addOffset("Entity:Health", 0xFC);
					this->getOffsetHandler()->addOffset("Entity:Flags", 0x100);
					this->getOffsetHandler()->addOffset("Entity:ViewOffset", 0x104);
					this->getOffsetHandler()->addOffset("Entity:Velocity", 0x110);
					this->getOffsetHandler()->addOffset("Entity:Origin", 0x134);
					this->getOffsetHandler()->addOffset("Entity:LifeState", 0x25B);
					this->getOffsetHandler()->addOffset("Entity:IsSpotted", 0x939);
					this->getOffsetHandler()->addOffset("Entity:SpottedByMask", 0x97C);
					this->getOffsetHandler()->addOffset("Entity:BoneMatrix", 0x2698);
					this->getOffsetHandler()->addOffset("Entity:Owner", 0x29BC);
					this->getOffsetHandler()->addOffset("Entity:ViewPunchAngle", 0x3010);
					this->getOffsetHandler()->addOffset("Entity:AimPunchAngle", 0x301C);
					this->getOffsetHandler()->addOffset("Entity:AimPunchAngleVelocity", 0x3028);
					this->getOffsetHandler()->addOffset("Entity:InReload", 0x3245);
					this->getOffsetHandler()->addOffset("Entity:IsScoped", 0x389C);
					this->getOffsetHandler()->addOffset("Entity:IsDefusing", 0x38A4);
					this->getOffsetHandler()->addOffset("Entity:ShotsFired", 0xA2C0);
					this->getOffsetHandler()->addOffset("Entity:FlashMaxAlpha", 0xA304);
					this->getOffsetHandler()->addOffset("Entity:FlashDuration", 0xA308);
					this->getOffsetHandler()->addOffset("Entity:HasHelmet", 0xB23C);
					this->getOffsetHandler()->addOffset("Entity:Armor", 0xB248);
					this->getOffsetHandler()->addOffset("Entity:HasDefuser", 0xB258);
					this->getOffsetHandler()->addOffset("Entity:CrosshairId", 0xB2B4);
				}

				void CInstance::processUpdate() {
					/*if (this->getShared()->_getGlobalVars().mustUpdate()) {
						auto relativeAddress = this->getOffsetHandler()->getRelativeAddress(this->clientModule->getBaseAddress(), this->getShared()->_getGlobalVars().getName());
						if (relativeAddress != this->clientModule->getBaseAddress()) {
							auto pointer = this->getProcessHandler()->getReader()->readLong(relativeAddress);
							if (pointer != NULL) {
								this->getMutex().lock();
								this->getProcessHandler()->getReader()->read(pointer, &this->getShared()->_getGlobalVars().getData());

								if ((this->getShared()->_getGlobalVars().getData().getTickCount() > 0) &&
									(this->getShared()->_getGlobalVars().getData().getMaxClients() <= 0)) {
									this->getLogger()->log(ando::logger::ELogLevel::LOG_CRITICAL, "Invalid %s (0x%.8X)!", this->getShared()->_getGlobalVars().getName().c_str(), (relativeAddress - this->clientModule->getBaseAddress()));
								}
								this->getMutex().unlock();
							}
							else {
								this->getLogger()->log(ando::logger::ELogLevel::LOG_CRITICAL, "Invalid %s (0x%.8X)!", this->getShared()->_getGlobalVars().getName().c_str(), (relativeAddress - this->clientModule->getBaseAddress()));
							}
					}*/

					{ // GlobalVars
						auto relativeAddress = this->getOffsetHandler()->getRelativeAddress(this->clientModule->getBaseAddress(), "GlobalVars");
						if (relativeAddress != this->clientModule->getBaseAddress()) {
							auto pointer = this->getProcessHandler()->getReader()->readLong(relativeAddress);
							if (pointer != NULL) {
								this->getMutex().lock();
								this->getProcessHandler()->getReader()->read(pointer, &this->getShared()->getGlobalVars());

								if ((this->getShared()->getGlobalVars().getTickCount() > 0) &&
									(this->getShared()->getGlobalVars().getMaxClients() <= 0)) {
									this->getLogger()->log(ando::logger::ELogLevel::LOG_CRITICAL, "Invalid %s (0x%.8X)!", "GlobalVars", (relativeAddress - this->clientModule->getBaseAddress()));
								}
								this->getMutex().unlock();
							}
							else {
								this->getLogger()->log(ando::logger::ELogLevel::LOG_CRITICAL, "Invalid %s (0x%.8X)!", "GlobalVars", (relativeAddress - this->clientModule->getBaseAddress()));
							}
						}
					}
					{ // LocalPlayer
						auto relativeAddress = this->getOffsetHandler()->getRelativeAddress(this->clientModule->getBaseAddress(), "LocalPlayer");
						if (relativeAddress != this->clientModule->getBaseAddress()) {
							auto pointer = this->getProcessHandler()->getReader()->readLong(relativeAddress);
							if (pointer != NULL) {
								this->getMutex().lock();
								this->readEntityFromAddress(pointer, &this->getShared()->getLocalPlayer());

								if ((this->getShared()->getLocalPlayer().getIndex() >= 0) &&
									(this->getShared()->getLocalPlayer().getTeam() < 0 || this->getShared()->getLocalPlayer().getTeam() > 3)) {
									this->getLogger()->log(ando::logger::ELogLevel::LOG_CRITICAL, "Invalid %s (0x%.8X)!", "LocalPlayer", (relativeAddress - this->clientModule->getBaseAddress()));
								}
								this->getMutex().unlock();
							}
							else {
								this->getLogger()->log(ando::logger::ELogLevel::LOG_CRITICAL, "Invalid %s (0x%.8X)!", "LocalPlayer", (relativeAddress - this->clientModule->getBaseAddress()));
							}
						}
					}
					{ // PlayerResource
						auto relativeAddress = this->getOffsetHandler()->getRelativeAddress(this->clientModule->getBaseAddress(), "PlayerResource");
						if (relativeAddress != this->clientModule->getBaseAddress()) {
							auto pointer = this->getProcessHandler()->getReader()->readLong(relativeAddress);
							if (pointer != NULL) {
								auto block = ::std::make_unique<memory::MemoryBlock>(this->getProcessHandler(), pointer, this->getOffsetHandler()->getOffsetByName("PlayerResource:CompetitiveWins"));

								if (block->readSection()) {
									::std::size_t index = 0;
									::ando::process_specific::CounterStrike::GlobalOffensive::CPlayerResource playerResource;

									::ando::process_specific::CounterStrike::GlobalOffensive::CScoreboardPlayer *player;
									while ((player = playerResource.getScoreboardPlayer(index)) != nullptr) {
										::std::uintptr_t stringPointer = 0;
										block->getAt((index * 0x4) + this->getOffsetHandler()->getOffsetByName("PlayerResource:Name"), &stringPointer, 4);

										player->m_szName = this->getProcessHandler()->getReader()->readString(stringPointer);

										block->getAt((index * 0x4) + this->getOffsetHandler()->getOffsetByName("PlayerResource:Ping"), &player->m_iPing);
										block->getAt((index * 0x4) + this->getOffsetHandler()->getOffsetByName("PlayerResource:Kills"), &player->m_iKills);
										block->getAt((index * 0x4) + this->getOffsetHandler()->getOffsetByName("PlayerResource:Assists"), &player->m_iAssists);
										block->getAt((index * 0x4) + this->getOffsetHandler()->getOffsetByName("PlayerResource:Deaths"), &player->m_iDeaths);
										block->getAt((index * 0x4) + this->getOffsetHandler()->getOffsetByName("PlayerResource:IsConnected"), &player->m_bConnected);
										block->getAt((index * 0x4) + this->getOffsetHandler()->getOffsetByName("PlayerResource:Team"), &player->m_iTeam);
										block->getAt((index * 0x4) + this->getOffsetHandler()->getOffsetByName("PlayerResource:PendingTeam"), &player->m_iPendingTeam);
										block->getAt((index * 0x4) + this->getOffsetHandler()->getOffsetByName("PlayerResource:IsAlive"), &player->m_bAlive);
										block->getAt((index * 0x4) + this->getOffsetHandler()->getOffsetByName("PlayerResource:Health"), &player->m_iHealth);
										block->getAt((index * 0x4) + this->getOffsetHandler()->getOffsetByName("PlayerResource:Armor"), &player->m_iArmor);
										block->getAt((index * 0x4) + this->getOffsetHandler()->getOffsetByName("PlayerResource:Score"), &player->m_iScore);
										block->getAt((index * 0x4) + this->getOffsetHandler()->getOffsetByName("PlayerResource:CompetitiveRanking"), &player->m_iCompetitiveRanking);
										block->getAt((index * 0x4) + this->getOffsetHandler()->getOffsetByName("PlayerResource:CompetitiveWins"), &player->m_iCompetitiveWins);

										index++;
									}

									this->getMutex().lock();
									this->getShared()->getPlayerResource() = playerResource;
									this->getMutex().unlock();
								}
							}
						}
					}
					{ // ViewMatrix
						auto relativeAddress = this->getOffsetHandler()->getRelativeAddress(this->clientModule->getBaseAddress(), "ViewMatrix");
						if (relativeAddress != this->clientModule->getBaseAddress()) {
							this->getMutex().lock();
							this->getProcessHandler()->getReader()->read(relativeAddress, this->getShared()->getViewMatrix().getData(), 4 * 4 * sizeof(float));
							this->getMutex().unlock();
						}
						else {
							this->getLogger()->log(ando::logger::ELogLevel::LOG_CRITICAL, "Invalid %s (0x%.8X)!", "ViewMatrix", (relativeAddress - this->clientModule->getBaseAddress()));
						}
					}

					{ // EntityList
						::std::vector<::std::shared_ptr<::ando::process_specific::CounterStrike::GlobalOffensive::CBaseEntity>> entityList;

						::std::uint32_t currentHolder = this->getOffsetHandler()->getRelativeAddress(this->clientModule->getBaseAddress(), "EntityList");

						CEntityInfo entry;
						while (currentHolder != NULL) {
							if (!this->getProcessHandler()->getReader()->read<CEntityInfo>(currentHolder, &entry, sizeof(CEntityInfo)))
								break;

							currentHolder = entry.getNext();

							if (entry.getNext() == entry.getPrevious())
								break;
							if (entry.getEntity() == NULL)
								continue;

							auto entity = ::std::make_shared<::ando::process_specific::CounterStrike::GlobalOffensive::CBaseEntity>();

							if (!this->readEntityFromAddress(entry.getEntity(), entity.get()))
								continue;

							if (entity == nullptr)
								continue;

							switch (entity->getClassId()) {
								case Client::EClientClassID::CCSPlayer: {
									if (entity->isDead())
										continue;
									if (entity->isDormant())
										continue;
									if ((entity->getHealth() <= 0) || (entity->getHealth() > 100))
										continue;

									auto player = static_cast<CPlayerEntity *>(entity.get());

									player->scoreboardPlayer = this->getShared()->getPlayerResource().getScoreboardPlayer(entity->getIndex());

									break;
								}

								case Client::EClientClassID::CPlantedC4:
								case Client::EClientClassID::CC4: {
									if (entity->isDormant())
										continue;

									break;
								}
								default: {
									continue;
								}
							}

							entityList.emplace_back(entity);
						}

						this->getMutex().lock();
						this->getEntityList() = entityList;
						this->getMutex().unlock();
					}
				}

				::std::shared_ptr<::ando::process_specific::CounterStrike::GlobalOffensive::CBaseEntity> CInstance::readEntityFromIndex(::std::size_t index) {
					DWORD_PTR baseAddress = this->getProcessHandler()->getReader()->readLong(this->getOffsetHandler()->getRelativeAddress(this->clientModule->getBaseAddress(), "EntityList") + (index * 0x10));
					if (baseAddress == 0)
						return nullptr;

					auto entity = ::std::make_shared<::ando::process_specific::CounterStrike::GlobalOffensive::CBaseEntity>();
					if (!this->readEntityFromAddress(baseAddress, entity.get()))
						return nullptr;

					return entity;
				}

				bool CInstance::readEntityFromAddress(::std::uintptr_t baseAddress, ::ando::process_specific::CounterStrike::GlobalOffensive::CBaseEntity *entity) {
					// ClassId
					{
						auto IClientNetworkable = this->getProcessHandler()->getReader()->readLong(baseAddress + 0x8);
						auto secondFunction = this->getProcessHandler()->getReader()->readLong(IClientNetworkable + (0x4 * 2));
						auto movEax = this->getProcessHandler()->getReader()->readLong(secondFunction + 0x1);

						this->getProcessHandler()->getReader()->read(movEax + 0x14, &entity->m_iClassId);
					}

					// Index
					this->getProcessHandler()->getReader()->read(this->getOffsetHandler()->getRelativeAddress(baseAddress, "Entity:Index"), &entity->m_iIndex);

					// BoneMatrix
					{
						auto m_pBones = this->getProcessHandler()->getReader()->readLong(this->getOffsetHandler()->getRelativeAddress(baseAddress, "Entity:BoneMatrix"));

						if (!this->getProcessHandler()->getReader()->read(m_pBones, entity->getBoneManager().getBoneMatrixArray().data(), (3 * 4) * sizeof(float) * 100))
							return false;
					}

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
						auto blockOffset = this->getOffsetHandler()->getOffsetByName("Entity:Owner");
						auto blockSize = this->getOffsetHandler()->getOffsetByName("Entity:IsDefusing") - blockOffset + sizeof(entity->m_bIsDefusing);

						auto block = ::std::make_unique<memory::MemoryBlock>(this->getProcessHandler(), baseAddress, blockSize, blockOffset);
						if (!block->readSection())
							return false;

						block->getAt(blockOffset, &entity->m_hOwner, 4);
						block->getAt(this->getOffsetHandler()->getOffsetByName("Entity:ViewPunchAngle"), entity->m_viewPunchAngle.getXData(), 8);
						block->getAt(this->getOffsetHandler()->getOffsetByName("Entity:AimPunchAngle"), entity->m_aimPunchAngle.getXData(), 8);
						block->getAt(this->getOffsetHandler()->getOffsetByName("Entity:AimPunchAngleVelocity"), entity->m_aimPunchAngleVel.getXData(), 8);
						block->getAt(this->getOffsetHandler()->getOffsetByName("Entity:InReload"), &entity->m_bInReload, 1);
						block->getAt(this->getOffsetHandler()->getOffsetByName("Entity:IsScoped"), &entity->m_bIsScoped, 1);
						block->getAt(this->getOffsetHandler()->getOffsetByName("Entity:IsDefusing"), &entity->m_bIsDefusing, 1);
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
}