#ifndef __eosTransformation__
#define __eosTransformation__


#include "eos.h"
#include "System/Graphics/eosPoint.h"


namespace eos {

	enum class RotateTransformationAngle: uint8_t {
		r0,
		r90,
		r180,
		r270
	};

	class Transformation {
		private:
			typedef int Matrix[3][3];
			typedef uint8_t MatrixType;

		private:
		    constexpr static MatrixType TypeIdentity = 0;
		    constexpr static MatrixType TypeTranslation = 1;
		    constexpr static MatrixType TypeScale = 2;
		    constexpr static MatrixType TypeUnknown = 4;

		private:
			Matrix m;
			MatrixType type;

		private:
			Transformation(const Matrix &m);
			static void combineMatrix(Matrix &dst, const Matrix &src1, const Matrix &src2);
			static void combineType(MatrixType &dst, MatrixType src1, MatrixType src2);

		public:
			Transformation();
            Transformation(const Transformation &t);
            Transformation(int m11, int m12, int m21, int m22, int tx, int ty);
            void identity();
			void translate(int tx, int ty);
			inline void translate(const Point &t) { translate(t.getX(), t.getY()); }
			void scale(int sx, int sy, int ox, int oy);
			inline void scale(int sx, int sy) { scale(sx, sy, 0, 0); }
			inline void scale(int sx, int sy, const Point &o) { scale(sx, sy, o.getX(), o.getY()); }
			void rotate(RotateTransformationAngle r, int ox, int oy);
			inline void rotate(RotateTransformationAngle r) { rotate(r, 0, 0); }
			inline void rotate(RotateTransformationAngle r, const Point &o) { rotate(r, o.getX(), o.getY()); }
			void combine(const Transformation &t);
			void apply(int &x, int &y) const;
			Point apply(const Point &p) const;

            Transformation& operator = (const Transformation &t);
            Transformation operator * (const Transformation &t) const;
            Transformation& operator *= (const Transformation &t);

            inline int getM11() const { return m[0][0]; }
            inline int getM12() const { return m[0][1]; }
            inline int getM21() const { return m[1][0]; }
            inline int getM22() const { return m[1][1]; }
            inline int getTx() const { return m[2][0]; }
            inline int getTy() const { return m[2][1]; }
	};
}


#endif // __eosTransformation__
