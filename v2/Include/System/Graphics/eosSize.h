#ifndef __eosSize__
#define __eosSize__


#include "eos.h"
#include "System/Graphics/eosThickness.h"


namespace eos {

	/// \brief Clase que representa un tamany
	class Size {
		private:
			int width;
			int height;

		public:
			Size();
			Size(int width, int height);
			Size(const Size &s);

			/// \brief Obte l'amplada.
			inline int getWidth() const { return width; }

			/// \brief Obte l'al�ada.
			inline int getHeight() const { return height; }

			Size inflate(int dw, int dh) const;
			Size inflate(const Thickness &t) const;
			Size deflate(const Thickness &t) const;

			bool isEmpty() const;

			bool operator==(const Size &s) const;
            bool operator!=(const Size &s) const;
	};
}


#endif // __eosSize__
