#include "EGlobalOffensiveClientClassID.hpp"

namespace ando {
	namespace process_specific {
		namespace CounterStrike {
			namespace GlobalOffensive {
				namespace Client {
					::std::string classIdToString(EClientClassID classId) {
						switch (classId) {
						case CAK47:				return "AK-47";
						case CDEagle:			return "DEagal";
						case CC4:				return "C4";
						case CCSPlayer:			return "Player";
						case CWeaponAug:		return "Aug";
						case CWeaponAWP:		return "AWP";
						case CWeaponBizon:		return "Bizon";
						case CWeaponFamas:		return "Famas";
						case CWeaponFiveSeven:	return "Five-Seven";
						case CWeaponG3SG1:		return "G3SG1";
						case CWeaponGalil:		return "Galil";
						case CWeaponGalilAR:	return "Galil-AR";
						case CWeaponGlock:		return "Glock";
						case CWeaponHKP2000:	return "HKP2000";
						case CWeaponM249:		return "M249";
						case CWeaponM3:			return "M3";
						case CWeaponM4A1:		return "M4A1";
						case CWeaponMAC10:		return "Mac-10";
						case CWeaponMag7:		return "Mag 7";
						case CWeaponMP5Navy:	return "MP5 Navy";
						case CWeaponMP7:		return "MP7";
						case CWeaponMP9:		return "MP9";
						case CWeaponNegev:		return "Negev";
						case CWeaponNOVA:		return "Nova";
						case CWeaponP228:		return "P228";
						case CWeaponP250:		return "P250";
						case CWeaponP90:		return "P90";
						case CWeaponSawedoff:	return "Sawed-Off";
						case CWeaponSCAR20:		return "Scar-20";
						case CWeaponScout:		return "Scout";
						case CWeaponSG550:		return "SG550";
						case CWeaponSG552:		return "SG552";
						case CWeaponSG556:		return "SG556";
						case CWeaponSSG08:		return "SSG08";
						case CWeaponTaser:		return "Taser";
						case CWeaponTec9:		return "Tec-9";
						case CWeaponTMP:		return "TMP";
						case CWeaponUMP45:		return "UMP-45";
						case CWeaponUSP:		return "USP";
						case CWeaponXM1014:		return "XM1014";
						}

						return "UNFINISHED";
					}
				}
			}
		}
	}
}