#ifndef CGLOBALOFFENSIVEENTITYINFO_HPP
#define CGLOBALOFFENSIVEENTITYINFO_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <memory>

namespace ando {
	namespace process_specific {
		namespace CounterStrike {
			namespace GlobalOffensive {
				class CEntityInfo {
				private:
					::std::uint32_t m_pEntity;
					::std::uint32_t m_nSerialNumber;
					::std::uint32_t m_pPrevious;
					::std::uint32_t m_pNext;

				public:
					CEntityInfo() {
						this->m_pEntity = this->m_nSerialNumber = this->m_pPrevious = this->m_pNext = 0;
					}

				public:
					::std::uint32_t getEntity() const {
						return this->m_pEntity;
					}
					::std::uint32_t getSerialNumber() const {
						return this->m_nSerialNumber;
					}
					::std::uint32_t getPrevious() const {
						return this->m_pPrevious;
					}
					::std::uint32_t getNext() const {
						return this->m_pNext;
					}

				public:
					void setEntity(const ::std::uint32_t m_pEntity) {
						this->m_pEntity = m_pEntity;
					}
					void setSerialNumber(const ::std::uint32_t m_nSerialNumber) {
						this->m_nSerialNumber = m_nSerialNumber;
					}
					void setPrevious(const ::std::uint32_t m_pPrevious) {
						this->m_pPrevious = m_pPrevious;
					}
					void setNext(const ::std::uint32_t m_pNext) {
						this->m_pNext = m_pNext;
					}
				};
			}
		}
	}
}

#endif // CGLOBALOFFENSIVEENTITYINFO_HPP