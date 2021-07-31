#ifndef __eosSize__
#define __eosSize__


#include "eos.h"


namespace eos {

	/// \brief Clase que representa un tamany
    ///
	class Size {
		private:
			int _width;
			int _height;

		public:
			Size();
			Size(int width, int height);
			Size(const Size& s);
			Size(const Size&& s);

			/// \brief Obte l'amplada.
			inline int getWidth() const { return _width; }

			/// \brief Obte l'alçada.
			inline int getHeight() const { return _height; }

			Size inflated(int h, int v) const;
			Size inflated(int left, int top, int right, int bottom) const;
			Size constrained(const Size& s) const;

			bool isEmpty() const;

			Size& operator = (const Size& s);

			bool operator == (const Size& s) const;
            inline bool operator != (const Size& s) const { return !(*this == s); }
	};
}


#endif // __eosSize__
