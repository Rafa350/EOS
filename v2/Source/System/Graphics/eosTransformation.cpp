#include "eos.h"
#include "System/Graphics/eosTransformation.h"
#include "string.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Contructor per defecte. Crea una matriu identitat.
///
Transformation::Transformation() {

	identity();
}


/// ----------------------------------------------------------------------
/// \brief    Constructor copia.
/// \param    t: La transformacio a copiar.
///
Transformation::Transformation(
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

	type = TypeUnknown;
}


/// ----------------------------------------------------------------------
/// \brief    Contructor. Creacio a partir d'una matriu.
/// \param    m: Matriu inicial.
///
Transformation::Transformation(
	const Matrix &m) {

	memcpy(this->m, m, sizeof(Matrix));

	type = TypeUnknown;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza la transformacio amb la matriu identitat.
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

	type = TypeIdentity;
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una translacio a la matriu.
/// \param    tx: Component X de la translacio.
/// \param    ty: Component Y de la translacio.
///
void Transformation::translate(
	int tx,
	int ty) {

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
void Transformation::rotate(
	RotateTransformationAngle r,
	int ox,
	int oy) {

	combineType(type, type, TypeTranslation | TypeScale);
}


/// ----------------------------------------------------------------------
/// \bried    Combina amb un altre matriu.
/// \param    t: La transformacio per combinar.
///
void Transformation::combine(
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
void Transformation::apply(
	int &x,
	int &y) const {

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
Transformation& Transformation::operator = (
    const Transformation &t) {

	memcpy(m, t.m, sizeof(Matrix));
	type = t.type;

    return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Operador '*'.
/// \param    t: La transformacio per multiplicar.
///
Transformation Transformation::operator *(
	const Transformation &t) const {

	Matrix rm;

	combineMatrix(rm, t.m, m);
	return Transformation(rm);
}


/// ----------------------------------------------------------------------
/// \brief    Operador '*='.
/// \param    t: La transformacio per multiplicar.
///
Transformation& Transformation::operator *=(
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
void Transformation::combineMatrix(
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
void Transformation::combineType(
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
