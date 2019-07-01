#include "eos.h"
#include "System/Graphics/eosTransformation.h"
#include "string.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor per defecte. Crea una matriu identitat.
///
Transformation::Transformation() {

	identity();
}


/// ----------------------------------------------------------------------
/// \brief Constructor copia.
/// \param[in] t: La transformacio a copiar.
///
Transformation::Transformation(
    const Transformation &t) {

    memcpy(m, t.m, sizeof(Matrix));
}


/// ----------------------------------------------------------------------
/// \brief Constructor. Creacio a partir dels seus components.
/// \param[in] m11: Component m11.
/// \param[in] m12: Component m12.
/// \param[in] m21: Component m21.
/// \param[in] m22: Component m22.
/// \param[in] tx: Component tx.
/// \param[in] ty: Component ty.
///
Transformation::Transformation(
    int m11,
    int m12,
    int m21,
    int m22,
    int tx,
    int ty) {

	m[0][0] = m11;
	m[0][1] = m12;
	m[0][2] = 0;

	m[1][0] = m21;
	m[1][1] = m22;
	m[1][2] = 0;

	m[2][0] = tx;
	m[2][1] = ty;
	m[2][2] = 1;
}


/// ----------------------------------------------------------------------
/// \brief Contructor. Creacio a partir d'una matriu.
/// \param[in] m: Matriu inicial.
///
Transformation::Transformation(
	const Matrix &m) {

	memcpy(this->m, m, sizeof(Matrix));
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza la transformacio amb la nmatriu identitat.
///
void Transformation::identity() {

	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;

	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;

	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
}


/// ----------------------------------------------------------------------
/// \brief Afegeix una translacio a la matriu.
/// \param[in] tx: Component X de la translacio.
/// \param[in] ty: Component Y de la translacio.
///
void Transformation::translate(
	int tx,
	int ty) {

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

	multiply(rm, tm, m);
	memcpy(m, rm, sizeof(Matrix));
}


/// ----------------------------------------------------------------------
/// \brief Afegeix una escalat a la matriu.
/// \param[in] sx: Escalat en el eix X.
/// \param[in] sy: Escalat en el eix Y.
///
void Transformation::scale(
	int sx,
	int sy) {

	Matrix sm, rm;

	sm[0][0] = sx;
	sm[0][1] = 0;
	sm[0][2] = 0;

	sm[1][0] = 0;
	sm[1][1] = sy;
	sm[1][2] = 0;

	sm[2][0] = 0;
	sm[2][1] = 0;
	sm[2][2] = 1;

	multiply(rm, sm, m);
	memcpy(m, rm, sizeof(Matrix));
}


/// ----------------------------------------------------------------------
/// \brief Afegeix un escalat respecte a un punt.
/// \param[in] sx: Escalat en el eix X.
/// \param[in] sy: Escalat en el eix Y.
/// \param[in] ox: Coordinada X de l'origen del escalat.
/// \param[in] oy: Coordinada Y de l'origen del escalat.
///
void Transformation::scale(
	int sx,
	int sy,
	int ox,
	int oy) {

	Matrix sm, rm;

	sm[0][0] = sx;
	sm[0][1] = 0;
	sm[0][2] = 0;

	sm[1][0] = 0;
	sm[1][1] = sy;
	sm[1][2] = 0;

	sm[2][0] = (1 - sx) + ox;
	sm[2][1] = (1 - sy) + oy;
	sm[2][2] = 1;

	multiply(rm, sm, m);
	memcpy(m, rm, sizeof(Matrix));
}


void Transformation::rotate(
	RotateTransformationAngle r) {

}


void Transformation::rotate(
	RotateTransformationAngle r,
	int ox,
	int oy) {

}


/// ----------------------------------------------------------------------
/// \bried Combina amb un altre matriu.
/// \param[in] t: La transformacio per combinar.
///
void Transformation::combine(
	const Transformation &t) {

	Matrix rm;

	multiply(rm, t.m, m);
	memcpy(m, rm, sizeof(Matrix));
}


/// ----------------------------------------------------------------------
/// \brief Aplica la tranasformacio a un punt.
/// \param x: Coordinada X del punt.
/// \param y: Coordinada Y del punt.
///
void Transformation::apply(
	int &x,
	int &y) {

	int xx = x;
	x = xx * m[0][0] + y * m[1][0] + m[2][0];
	y = xx * m[0][1] + y * m[1][1] + m[2][1];
}


/// ----------------------------------------------------------------------
/// \brief Operador '*'.
/// \param[in] t: La transformacio a asignar.
///
Transformation & Transformation::operator = (
    const Transformation &t) {

	memcpy(m, t.m, sizeof(Matrix));
    return *this;
}


/// ----------------------------------------------------------------------
/// \brief Operador '*'.
/// \param[in] t: La transformacio per multiplicar.
///
Transformation Transformation::operator *(
	const Transformation &t) {

	Matrix rm;

	multiply(rm, t.m, m);
	return Transformation(rm);
}


/// ----------------------------------------------------------------------
/// \brief Operador '*='.
/// \param[in] t: La transformacio per multiplicar.
///
Transformation& Transformation::operator *=(
	const Transformation &t) {

	Matrix rm;

	multiply(rm, t.m, m);
	memcpy(m, rm, sizeof(Matrix));

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief Multiplica dues matrius.
/// \param dst: Destinacio del resultat.
/// \param m1: Primera matriu a multiplicat.
/// \param m2: Segona matriu a multiplicar.
/// \param rm: Matriu resultat de l'operacio.
///
void Transformation::multiply(
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
