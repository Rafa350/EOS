module;


#include "eos.h"


export module Eos.System.Graphics.Transformation;


import Eos.System.Graphics.Point;


export namespace eos {

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


/// ----------------------------------------------------------------------
/// \brief    Contructor per defecte. Crea una matriu identitat.
///
eos::Transformation::Transformation() {

	identity();
}


/// ----------------------------------------------------------------------
/// \brief    Constructor copia.
/// \param    t: La transformacio a copiar.
///
eos::Transformation::Transformation(
    const Transformation &t) {

    memcpy(m, t.m, sizeof(Matrix));
    type = t.type;
}


/// ----------------------------------------------------------------------
/// \brief    Constructor. Creacio a partir dels seus components.
/// \param    m11: Component m11.
/// \param    m12: Component m12.
/// \param    m21: Component m21.
/// \param    m22: Component m22.
/// \param    tx: Component tx.
/// \param    ty: Component ty.
///
eos::Transformation::Transformation(
    int16_t m11,
    int16_t m12,
    int16_t m21,
    int16_t m22,
    int16_t tx,
    int16_t ty) {

	m[0][0] = m11;
	m[0][1] = m12;
	m[0][2] = 0;

	m[1][0] = m21;
	m[1][1] = m22;
	m[1][2] = 0;

	m[2][0] = tx;
	m[2][1] = ty;
	m[2][2] = 1;

	type = TypeUnknown;
}


/// ----------------------------------------------------------------------
/// \brief    Contructor. Creacio a partir d'una matriu.
/// \param    m: Matriu inicial.
///
eos::Transformation::Transformation(
	const Matrix &m) {

	memcpy(this->m, m, sizeof(Matrix));

	type = TypeUnknown;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza la transformacio amb la matriu identitat.
///
void eos::Transformation::identity() {

	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;

	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;

	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;

	type = TypeIdentity;
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una translacio a la matriu.
/// \param    tx: Component X de la translacio.
/// \param    ty: Component Y de la translacio.
///
void eos::Transformation::translate(
	int16_t tx,
	int16_t ty) {

	if (type == TypeIdentity) {

		m[2][0] = tx;
		m[2][1] = ty;

		type = TypeTranslation;
	}

	else {
		Matrix tm, rm;

		tm[0][0] = 1;
		tm[0][1] = 0;
		tm[0][2] = 0;

		tm[1][0] = 0;
		tm[1][1] = 1;
		tm[1][2] = 0;

		tm[2][0] = tx;
		tm[2][1] = ty;
		tm[2][2] = 1;

		combineType(type, type, TypeTranslation);
		combineMatrix(rm, tm, m);

		memcpy(m, rm, sizeof(Matrix));
	}
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un escalat respecte a un punt.
/// \param    sx: Escalat en el eix X.
/// \param    sy: Escalat en el eix Y.
/// \param    ox: Coordinada X de l'origen del escalat.
/// \param    oy: Coordinada Y de l'origen del escalat.
///
void eos::Transformation::scale(
	int16_t sx,
	int16_t sy,
	int16_t ox,
	int16_t oy) {

	Matrix sm, rm;

	sm[0][0] = sx;
	sm[0][1] = 0;
	sm[0][2] = 0;

	sm[1][0] = 0;
	sm[1][1] = sy;
	sm[1][2] = 0;

	if (ox == 0) // Optimitza el cas ox == 0
		sm[2][0] = 0;
	else
		sm[2][0] = (1 - sx) * ox;
	if (oy == 0) // Optimitza el cas yo == 0
		sm[2][1] = 0;
	else
		sm[2][1] = (1 - sy) * oy;
	sm[2][2] = 1;

	combineType(type, type, TypeScale);
	combineMatrix(rm, sm, m);

	memcpy(m, rm, sizeof(Matrix));
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una rotacio respecte a un punt.
/// \param    r: Angle de rotacio.
/// \param    ox: Coordinada X del centre de rotacio.
/// \param    oy: Coordinada Y del centre de rotacio.
///
void eos::Transformation::rotate(
	RotateTransformationAngle r,
	int16_t ox,
	int16_t oy) {

	combineType(type, type, TypeTranslation | TypeScale);
}


/// ----------------------------------------------------------------------
/// \bried    Combina amb un altre matriu.
/// \param    t: La transformacio per combinar.
///
void eos::Transformation::combine(
	const Transformation &t) {

	Matrix rm;

	combineType(type, type, t.type);
	combineMatrix(rm, t.m, m);

	memcpy(m, rm, sizeof(Matrix));
}


/// ----------------------------------------------------------------------
/// \brief    Aplica la tranasformacio a un punt.
/// \param    x: Coordinada X del punt.
/// \param    y: Coordinada Y del punt.
///
void eos::Transformation::apply(
	int16_t &x,
	int16_t &y) const {

	switch (type) {
		case TypeIdentity:
			break;

		case TypeTranslation:
			x += m[2][0];
			y += m[2][1];
			break;

		case TypeScale:
			x *= m[0][0];
			y *= m[1][1];
			break;

		case TypeTranslation | TypeScale:
			x *= m[0][0];
			x += m[2][0];
			y *= m[1][1];
			y += m[2][1];
			break;

		default: {
			int xx = x;
			x = xx * m[0][0] + y * m[1][0] + m[2][0];
			y = xx * m[0][1] + y * m[1][1] + m[2][1];
			break;
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Operador '='.
/// \param    t: La transformacio a asignar.
///
eos::Transformation& eos::Transformation::operator = (
    const Transformation &t) {

	memcpy(m, t.m, sizeof(Matrix));
	type = t.type;

    return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Operador '*'.
/// \param    t: La transformacio per multiplicar.
///
eos::Transformation eos::Transformation::operator *(
	const Transformation &t) const {

	Matrix rm;

	combineMatrix(rm, t.m, m);
	return Transformation(rm);
}


/// ----------------------------------------------------------------------
/// \brief    Operador '*='.
/// \param    t: La transformacio per multiplicar.
///
eos::Transformation& eos::Transformation::operator *=(
	const Transformation &t) {

	Matrix rm;

	combineMatrix(rm, t.m, m);
	memcpy(m, rm, sizeof(Matrix));
	type = TypeUnknown;

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Combina (Multiplica) dues matrius.
/// \param    dst: Destinacio del resultat.
/// \param    m1: Primera matriu a multiplicat.
/// \param    m2: Segona matriu a multiplicar.
/// \param    rm: Matriu resultat de l'operacio.
///
void eos::Transformation::combineMatrix(
	Matrix &rm,
	const Matrix &m1,
	const Matrix &m2) {

	for (int r = 0; r < 3; r++)
		for (int c = 0; c < 3; c++) {
			int sum = 0;
			for (int z = 0; z < 3; z++)
				sum += m1[r][z] * m2[z][c];
			rm[r][c] = sum;
	    }
}


/// ----------------------------------------------------------------------
/// \brief    Combina el tipus de matriu.
/// \param    dst: Destinacio del resultat.
/// \param    src1: Primer tipus a combinar.
/// \param    src: Segon tipus a combinar.
///
void eos::Transformation::combineType(
	MatrixType &dst,
	MatrixType src1,
	MatrixType src2) {

	if ((src1 == TypeUnknown) || (src2 == TypeUnknown))
		dst = TypeUnknown;

	else if (src1 == src2)
		dst = src1;

	else
		dst = src1 | src2;
}
