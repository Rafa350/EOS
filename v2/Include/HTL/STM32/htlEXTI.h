#pragma once
#ifndef __STM32_htlEXTI__
#define __STM32_htlEXTI__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/STM32/htlGPIO.h"
#include "HTL/STM32/htlINT.h"


namespace htl {

	namespace exti {

		enum class LineID {
			_0,   // Px0
			_1,   // Px1
			_2,   // Px2
			_3,   // Px3
			_4,   // Px4
			_5,   // Px5
			_6,   // Px6
			_7,   // Px7
			_8,   // Px8
			_9,   // Px9
			_10,  // Px10
			_11,  // Px11
			_12,  // Px12
			_13,  // Px13
			_14,  // Px14
			_15,  // Px15
		};

		enum class Mode {
			none,
			interrupt,
			event,
			all
		};

		enum class Edge {
			rissing,
			falling,
			all
		};

		namespace internal {

			class Activator final {
				private:
					#if defined(EOS_PLATFORM_STM32G0)
					static constexpr uint32_t _rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR2);
					static constexpr uint32_t _rccEnablePos = RCC_APBENR2_SYSCFGEN_Pos;
					#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
					static constexpr uint32_t _rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
					static constexpr uint32_t _rccEnablePos = RCC_APB2ENR_SYSCFGEN_Pos;
					#endif
				private:
					static unsigned _activated;
				public:
					static void activate() {
						if (_activated == 0) {
							uint32_t *p = reinterpret_cast<uint32_t*>(_rccEnableAddr);
							*p |= 1 << _rccEnablePos;
							__DSB();
						}
						_activated++;
					}
					static void deactivate() {
						if (_activated == 1) {
							uint32_t *p = reinterpret_cast<uint32_t*>(_rccEnableAddr);
							*p &= ~(1 << _rccEnablePos);
							_activated--;
						}
					}
			};
		}

		class EXTILine {
			private:
				using Activator = internal::Activator;
			private:
				uint32_t const _lineNum;
			protected:
				inline void activate() {
					Activator::activate();
				}
				inline void deactivate() {
					Activator::deactivate();
				}
				void interruptService();
			public:
				EXTILine(LineID lineID);
				void initialize(htl::gpio::PortID portID, Mode mode, Edge edge);
				void deinitialize();
		};
		typedef EXTILine * EXTILineHandler;

		template <LineID lineID_>
		class EXTILineX final: public EXTILine {
			private:
				static EXTILineX _instance;
			public:
				EXTILineX(): EXTILine(lineID_) {}
				inline static void interruptHandler() {
					getHandler()->interruptService();
				}
				static constexpr EXTILineX * getHandler() {
					return &_instance;
				}
		};

		template <LineID lineID_>
		EXTILineX<lineID_> EXTILineX<lineID_>::_instance;

		using EXTILine0 = EXTILineX<LineID::_0>;
		using EXTILine1 = EXTILineX<LineID::_1>;
		using EXTILine2 = EXTILineX<LineID::_2>;
		using EXTILine3 = EXTILineX<LineID::_3>;
		using EXTILine4 = EXTILineX<LineID::_4>;
		using EXTILine5 = EXTILineX<LineID::_5>;
		using EXTILine6 = EXTILineX<LineID::_6>;
		using EXTILine7 = EXTILineX<LineID::_7>;
		using EXTILine8 = EXTILineX<LineID::_8>;
		using EXTILine9 = EXTILineX<LineID::_9>;
		using EXTILine10 = EXTILineX<LineID::_10>;
		using EXTILine11 = EXTILineX<LineID::_11>;
		using EXTILine12 = EXTILineX<LineID::_12>;
		using EXTILine13 = EXTILineX<LineID::_13>;
		using EXTILine14 = EXTILineX<LineID::_14>;
		using EXTILine15 = EXTILineX<LineID::_15>;
	}
}


#endif // __STM32_htlEXTI__
