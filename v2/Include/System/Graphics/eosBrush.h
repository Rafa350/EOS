#ifndef __eosBrush__
#define __eosBrush__


// EOS includes
//
#include "eos.h"
#include "System/eosPointers.h"
#include "System/Collections/eosDynamicArray.h"
#include "System/Graphics/eosColor.h"


#ifndef eosGraphics_MaxBrushes
#define eosGraphics_MaxBrushes 20
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
		typedef SharedPtr<Impl> ImplPtr;
		typedef DynamicArray<ImplPtr, eosGraphics_MaxBrushes, true> ImplPtrCache;

	private:
		static ImplPtrCache _implCache;
		ImplPtr _impl;

	private:
		ImplPtr makeImpl(BrushStyle stype, Color color);

	public:
		Brush();
		Brush(BrushStyle style, Color color);
		Brush(const Brush& brush);
		~Brush();

		Brush& operator = (const Brush& brush);
		bool operator == (const Brush& brush) const;
		inline bool operator != (const Brush& brush) const { return !(*this == brush); }

		Color getColor() const;
		BrushStyle getStyle() const;

		bool isNull() const;
	};

}


#endif // __eosBrush__
