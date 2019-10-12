#ifndef __eosSize__
#define __eosSize__


#include "eos.h"


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

			/// \brief Obte l'alçada.
			inline int getHeight() const { return height; }

			Size inflated(int h, int v) const;
			Size inflated(int left, int top, int right, int bottom) const;
			Size constrained(const Size &s) const;

			bool isEmpty() const;

			bool operator==(const Size &s) const;
            bool operator!=(const Size &s) const;
	};
}


#endif // __eosSize__
