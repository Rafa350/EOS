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
		Null,
		Solid
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
		Brush(Color color);
		Brush(Color color, BrushStyle style);
		Brush(const Brush& brush);
		~Brush();

		Brush& operator = (const Brush& brush);
		bool operator == (const Brush& pen) const;
		bool operator != (const Brush& pen) const;

		Color getColor() const;
		BrushStyle getStyle() const;

		void setColor(const Color& color);
		void setStyle(BrushStyle style);
	};
}


#endif // __eosBrush__
