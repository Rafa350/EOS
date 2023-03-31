#ifndef __eosTransformation__
#define __eosTransformation__


#include "eos.h"
#include "System/Graphics/eosPoint.h"


namespace eos {

    /// \brief Angle de rotacio
    ///
	enum class RotateTransformationAngle: uint8_t {
		r0,
		r90,
		r180,
		r270
	};

	/// \brief Implementa un numero en notacio fixa.
	///
	class Fixed {
		private:
		    const int factor = 1024;
			int value;
	};

	/// \brief Clase que representa una transformacio 2D
	//
	class Transformation {
		private:
			typedef int16_t Matrix[3][3];
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
            Transformation(int16_t m11, int16_t m12, int16_t m21, int16_t m22, int16_t tx, int16_t ty);

            void identity();

			void translate(int16_t tx, int16_t ty);
			inline void translate(const Point &t) { translate(t.getX(), t.getY()); }

			void scale(int16_t sx, int16_t sy, int16_t ox, int16_t oy);
			inline void scale(int16_t sx, int16_t sy) { scale(sx, sy, 0, 0); }
			inline void scale(int16_t sx, int16_t sy, const Point &o) { scale(sx, sy, o.getX(), o.getY()); }

			void rotate(RotateTransformationAngle r, int16_t ox, int16_t oy);
			inline void rotate(RotateTransformationAngle r) { rotate(r, 0, 0); }
			inline void rotate(RotateTransformationAngle r, const Point &o) { rotate(r, o.getX(), o.getY()); }

			void combine(const Transformation &t);
			void apply(int16_t &x, int16_t &y) const;
			Point apply(const Point &p) const;

            Transformation& operator = (const Transformation &t);
            Transformation operator * (const Transformation &t) const;
            Transformation& operator *= (const Transformation &t);

            inline int16_t getM11() const { return m[0][0]; }
            inline int16_t getM12() const { return m[0][1]; }
            inline int16_t getM21() const { return m[1][0]; }
            inline int16_t getM22() const { return m[1][1]; }
            inline int16_t getTx() const { return m[2][0]; }
            inline int16_t getTy() const { return m[2][1]; }
	};
}


#endif // __eosTransformation__
