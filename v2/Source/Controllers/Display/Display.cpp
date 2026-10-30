export module Eos.Controllers.Display;

import Eos.System.Graphics.Color;
import Eos.Types;


export namespace eos {

    /// \brief Driver del display.
	///
    class DisplayDriver {
        public:
			/// \brief Destructor
			///
    		virtual ~DisplayDriver() = default;

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

            /// \brief Obte el valor maxim de la coordinada X.
            /// \return El valor.
            /// \remarks El valor depen de l'orientacio del display.
            ///
            virtual Int16 getMaxX() const = 0;

            /// \brief Obte el valor maxim de la coordinada Y.
            /// \return El valor.
            /// \remarks El valor depen de l'orientacio del display.
            ///
            virtual Int16 getMaxY() const = 0;

            /// \brief Obte l'amplada fisica del display.
            /// \return El valor.
            ///
            virtual Int16 getWidth() const = 0;

            /// \brief Obte l'alçada fisica del display.
            /// \return El valor.
            ///
            virtual Int16 getHeight() const = 0;

            virtual void clear(Color color) = 0;
            virtual void setPixel(Int16 x, Int16 y, Color color) = 0;
            virtual void setHPixels(Int16 x, Int16 y, Int16 length, Color color) = 0;
            virtual void setVPixels(Int16 x, Int16 y, Int16 length, Color color) = 0;
            virtual void setPixels(Int16 x, Int16 y, Int16 width, Int16 height, Color color) = 0;
            virtual void setPixels(Int16 x, Int16 y, Int16 width, Int16 height, const Color *colors, Int16 colorPitch) = 0;
            virtual void setPixels(Int16 x, Int16 y, Int16 width, Int16 height, const void *colors, ColorFormat colorFormat, Int16 colorPitch) = 0;

            virtual void refresh() = 0;
    };

    /// \brief Buffer del display.
	///
	class DisplayBuffer: private NonCopyableClass {
		public:
			enum class Orientation: UInt8 {
				rotate0,
				rotate90,
				rotate180,
				rotate270,
				normal = rotate0
			};

		private:
			Int16 const _frameWidth;
			Int16 const _frameHeight;
			Int16 _maxX;
			Int16 _maxY;
			Orientation _orientation;

            void transform(Int16 &x, Int16 &y) const;
            void transform(Int16 &x1, Int16 &y1, Int16 &x2, Int16 &y2) const;

        protected:
            virtual void put(Int16 x, Int16 y, Color color) = 0;
            virtual void fill(Int16 x, Int16 y, Int16 width, Int16 height, Color color) = 0;
            virtual void copy(Int16 x, Int16 y, Int16 width, Int16 height, const Color *colors, Int16 colorPitch) = 0;
            virtual void copy(Int16 x, Int16 y, Int16 width, Int16 height, const void *colors, ColorFormat colorFormat, Int16 colorPitch) = 0;

		public:
			DisplayBuffer(Int16 frameWidth, Int16 frameHeight, Orientation orientation);
			virtual ~DisplayBuffer() = default;

            void setOrientation(Orientation orientation);

            inline Int16 getMaxX() const { return _maxX; }
            inline Int16 getMaxY() const { return _maxY; }
            inline Int16 getWidth() const { return _frameWidth; }
            inline Int16 getHeight() const { return _frameHeight; }
            virtual UInt8 *getBuffer() const = 0;

            void clear(Color color);
            void setPixel(Int16 x, Int16 y, Color color);
            inline void setHPixels(Int16 x, Int16 y, Int16 size, Color color) { setPixels(x, y, size, 1, color); }
            inline void setVPixels(Int16 x, Int16 y, Int16 size, Color color) { setPixels(x, y, 1, size, color); }
            void setPixels(Int16 x, Int16 y, Int16 width, Int16 height, Color color);
            void setPixels(Int16 x, Int16 y, Int16 width, Int16 height, const Color *colors, Int16 colorPitch);
            void setPixels(Int16 x, Int16 y, Int16 width, Int16 height, const void *colors, ColorFormat colorFormat, Int16 colorPitch);
	};
}
