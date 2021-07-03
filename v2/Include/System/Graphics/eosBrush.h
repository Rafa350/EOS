#ifndef __eosBrush__
#define __eosBrush__


// EOS includes
//
#include "eos.h"
#include "System/eosPointers.h"
#include "System/Graphics/eosColor.h"


#ifndef eosGraphics_MaxBrushes
#define eosGraphics_MaxBrushes 10
#endif


namespace eos {

	enum class BrushStyle: uint8_t {
		null,
		solid,
		linearGradient,
		radialGradient
	};

	class Brush {
	private:
		struct Impl;
		typedef SharedPtr<Impl> PImpl;

	private:
		PImpl _pImpl;

	private:
		PImpl allocate();

	public:
		Brush();
		Brush(BrushStyle style, Color color);
		Brush(const Brush &brush);
		~Brush();

		Brush& operator = (const Brush &brush);
		bool operator == (const Brush &brush) const;
		bool operator != (const Brush &brush) const { return !(*this == brush); }

		Color getColor() const;
		BrushStyle getStyle() const;

		Color getColor(uint8_t gX, uint8_t gY) const;
		Color getColor(uint8_t gR) const;

		bool isNull() const;
	};

}


#endif // __eosBrush__
