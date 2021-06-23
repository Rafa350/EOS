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

            /// \brief Deiniciaialitza el driver.
            ///
            virtual void shutdown() = 0;

            virtual void displayOn() = 0;
            virtual void displayOff() = 0;

            /// \brief Selecciona l'orientacio de la imatge
            ///
            virtual void setOrientation(DisplayOrientation orientation) = 0;

            /// \brief Obte l'amplada de la imatge
            /// \return El valor de l'amplada en pixels.
            ///
            virtual int getImageWidth() const = 0;

            /// \brief Obte l'alçada de la imatge
            /// \return El valor de l'alçada en pixels.
            ///
            virtual int getImageHeight() const = 0;

            virtual void clear(Color color) = 0;
            virtual void setPixel(int x, int y, Color color) = 0;
            virtual void setHPixels(int x, int y, int length, Color color) = 0;
            virtual void setVPixels(int x, int y, int length, Color color) = 0;
            virtual void setPixels(int x, int y, int width, int height, Color color) = 0;
            virtual void setPixels(int x, int y, int width, int height, const Color *colors, int pitch) = 0;

            virtual void writePixels(int x, int y, int width, int height, const void *pixels, ColorFormat format, int dx, int dy, int pitch) = 0;
            virtual void readPixels(int x, int y, int width, int height, void *pixels, ColorFormat format, int dx, int dy, int pitch) = 0;

            virtual void vScroll(int delta, int x, int y, int width, int height) = 0;
            virtual void hScroll(int delta, int x, int y, int width, int height) = 0;
            virtual void refresh() = 0;
    };

}


#endif // __eosDisplayDriver__
