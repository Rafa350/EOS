#ifndef __htlSPI__
#define	__htlSPI__


// EOS includes
//
#include "HTL/htl.h"


#if defined(EOS_PLATFORM_PIC32MX) || defined(EOS_PLATFORM_PIC32MZ)
	#include "HTL/PIC32/htlSPI.h"

#elif defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32F1) || \
	defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
	#include "HTL/STM32/htlSPI.h"

#elif defined(EOS_PLATFORM_MSP432)
    #include "HTL/MSP432/htlSPI.h"

#endif


namespace htl {

	class ISPI {
		protected:
			virtual ~ISPI() = default;

		public:
			virtual void write8(uint8_t data) = 0;
			virtual void write16(uint16_t data) = 0;
	};

	typedef ISPI *SPIHandler;

	template <typename spi_>
	class SPI final: public ISPI {
		private:
			SPI() = default;
			SPI(const SPI &) = delete;
			SPI(const SPI &&) = delete;

			SPI & operator = (const SPI &) = delete;
			SPI & operator = (const SPI &&) = delete;

		public:
			static SPIHandler instance() {
				static SPI spi;
				return &spi;
			}

			void write8(uint8_t data) override {
				spi_::write8(data);
			}

			void write16(uint16_t data) override {
				spi_::write16(data);
			}
	};

	template <typename spi_>
	SPIHandler getSPI() {
		return SPI<spi_>::instance();
	}
}


#endif // __htlSPI__

