#ifndef __eosTransformation__
#define __eosTransformation__


#include "eos.h"


namespace eos {

	class Transformation {
		private:
			typedef int Matrix[3][3];

		private:
			Matrix m;

		private:
			static void initialize(Matrix &dst);
			static void copy(Matrix &dst, const Matrix &src);
			static void multiply(Matrix &dst, const Matrix &src1, const Matrix &src2);

		public:
			Transformation();
			void setTranslation(int tx, int ty);
			void setScale(int sx, int sy);
			void setScale(int sx, int sy, int ox, int oy);
			void setRotate(int r);
			void setRotate(int r, int ox, int oy);
			void combine(const Transformation &t);
			void apply(int &x, int &y);
	};
}


#endif // __eosTransformation__
