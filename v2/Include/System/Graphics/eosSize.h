#ifndef __eosSize__
#define __eosSize__


#include "eos.h"

#include <limits>


namespace eos {

	/// \brief Clase que representa un tamany
    ///
	class Size {
		private:
			int16_t _width;
			int16_t _height;

		public:
			static constexpr int16_t absoluteMaxWidth = std::numeric_limits<int16_t>::max();
            static constexpr int16_t absoluteMaxHeight = std::numeric_limits<int16_t>::max();
            static constexpr int16_t absoluteMinWidth = 0;
            static constexpr int16_t absoluteMinHeight = 0;

		public:
			Size();
			Size(int16_t width, int16_t height);
			Size(const Size &s);
			Size(const Size &&s);

			/// \brief Obte l'amplada.
			inline int16_t getWidth() const { return _width; }

			/// \brief Obte l'alçada.
			inline int16_t getHeight() const { return _height; }

			Size inflated(int16_t h, int16_t v) const;
			Size inflated(int16_t left, int16_t top, int16_t right, int16_t bottom) const;
			Size constrained(const Size &s) const;

			bool isEmpty() const;

			Size& operator = (const Size &s);

			bool operator == (const Size &s) const;
            inline bool operator != (const Size &s) const { return !(*this == s); }
	};
}


#endif // __eosSize__
