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
            Transformation(const Transformation &t);
            Transformation(int m11, int m12, int m21, int m22, int tx, int ty);
			void translate(int tx, int ty);
			void scale(int sx, int sy);
			void scale(int sx, int sy, int ox, int oy);
			void rotate(int r);
			void rotate(int r, int ox, int oy);
			void combine(const Transformation &t);
			void apply(int &x, int &y);
            
            Transformation& operator = (const Transformation &t);
            Transformation& operator & ()
            
            int getM11() const { return m[0][0]; }
            int getM12() const { return m[0][1]; }
            int getM21() const { return m[1][0]; }
            int getM22() const { return m[1][1]; }
            int getTx() const { return m[2][0]; }
            int getTy() const { return m[2][1]; }
	};
}


#endif // __eosTransformation__
