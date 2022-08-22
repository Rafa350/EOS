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

            virtual void displayOn() = 0;
            virtual void displayOff() = 0;

            /// \brief Selecciona l'orientacio de la imatge
            ///
            virtual void setOrientation(DisplayOrientation orientation) = 0;

            /// \brief Obte el valor maxim de la coordinada X.
            /// \return El valor.
            /// \remarks El valor depen de l'orientacio del display.
            ///
            virtual int getMaxX() const = 0;

            /// \brief Obte el valor maxim de la coordinada Y.
            /// \remarks El valor depen de l'orientacio del display.
            /// \return El valor.
            ///
            virtual int getMaxY() const = 0;

            /// \brief Obte l'amplada del display.
            /// \return El valor.
            ///
            virtual int getWidth() const = 0;

            /// \brief Obte l'alçada del display.
            /// \return El valor.
            ///
            virtual int getHeight() const = 0;

            virtual void clear(Color color) = 0;
            virtual void setPixel(int x, int y, Color color) = 0;
            virtual void setHPixels(int x, int y, int length, Color color) = 0;
            virtual void setVPixels(int x, int y, int length, Color color) = 0;
            virtual void setPixels(int x, int y, int width, int height, Color color) = 0;
            virtual void setPixels(int x, int y, int width, int height, const Color *colors, int colorPitch) = 0;
            virtual void setPixels(int x, int y, int width, int height, const void *colors, ColorFormat colorFormat, int colorPitch) = 0;

            virtual void refresh() = 0;
    };

}


#endif // __eosDisplayDriver__
