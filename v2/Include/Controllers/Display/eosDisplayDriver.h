#pragma once
#ifndef __eosDisplayDriver__
#define __eosDisplayDriver__


// EOS includes
//
#include "eos.h"
#include "Controllers/Display/eosDisplayOrientation.h"
#include "System/Graphics/eosColor.h"


namespace eos {

	/// \brief Interficie del driver del display.
	///
    class IDisplayDriver {
        public:
			/// \brief Destructor
			///
    		virtual ~IDisplayDriver() = default;

    		/// \brief Inicialitza el driver.
    		///
            virtual void initialize() = 0;

            /// \brief Desinicialitza el driver.
            ///
            virtual void deinitialize() = 0;

            /// \brief Activa el display
            ///
            virtual void enable() = 0;

            /// \brief Desactiva el display
            ///
            virtual void disable() = 0;

            /// \brief Selecciona l'orientacio de la imatge
            ///
            virtual void setOrientation(DisplayOrientation orientation) = 0;

            /// \brief Obte el valor maxim de la coordinada X.
            /// \return El valor.
            /// \remarks El valor depen de l'orientacio del display.
            ///
            virtual int16_t getMaxX() const = 0;

            /// \brief Obte el valor maxim de la coordinada Y.
            /// \return El valor.
            /// \remarks El valor depen de l'orientacio del display.
            ///
            virtual int16_t getMaxY() const = 0;

            /// \brief Obte l'amplada fisica del display.
            /// \return El valor.
            ///
            virtual int16_t getWidth() const = 0;

            /// \brief Obte l'alçada fisica del display.
            /// \return El valor.
            ///
            virtual int16_t getHeight() const = 0;

            virtual void clear(Color color) = 0;
            virtual void setPixel(int16_t x, int16_t y, Color color) = 0;
            virtual void setHPixels(int16_t x, int16_t y, int16_t length, Color color) = 0;
            virtual void setVPixels(int16_t x, int16_t y, int16_t length, Color color) = 0;
            virtual void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, Color color) = 0;
            virtual void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, const Color *colors, int16_t colorPitch) = 0;
            virtual void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, const void *colors, ColorFormat colorFormat, int16_t colorPitch) = 0;

            virtual void refresh() = 0;
    };

}


#endif // __eosDisplayDriver__
