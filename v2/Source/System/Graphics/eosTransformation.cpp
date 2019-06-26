#include "eos.h"
#include "System/Graphics/eosTransformation.h"
#include "string.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor per defecte. Crea una matriu identitat.
///
Transformation::Transformation() {

	initialize(m);
}


/// ----------------------------------------------------------------------
/// \brief Constructor copia.
/// \param[in] t: La transformacio a copiar.
///
Transformation::Transformation(
    const Transformation &t) {
   
    copy(m, t.m);
}


/// ----------------------------------------------------------------------
/// \brief Constructor. Crea la matriu per components.
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
        
	dst[0][0] = m11;
	dst[0][1] = m12;
	dst[0][2] = 0;

	dst[1][0] = m21;
	dst[1][1] = m22;
	dst[1][2] = 0;

	dst[2][0] = tx;
	dst[2][1] = ty;
	dst[2][2] = 1;
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
	copy(m, rm);
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
	copy(m, rm);
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
	copy(m, rm);
}


/// ----------------------------------------------------------------------
/// \bried Combina amb un altre matriu.
/// \param[in] t: La transformacio per combinar.
///
void Transformation::combine(
	const Transformation &t) {

	Matrix rm;

	multiply(rm, t.m, m);
	copy(m, rm);
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
/// \brief Inicialitza una matriu a matriu identitat.
/// \param dst: La matriu a inicialitzar.
///
void Transformation::initialize(
	Matrix &dst) {

	dst[0][0] = 1;
	dst[0][1] = 0;
	dst[0][2] = 0;

	dst[1][0] = 0;
	dst[1][1] = 1;
	dst[1][2] = 0;

	dst[2][0] = 0;
	dst[2][1] = 0;
	dst[2][2] = 1;
}


/// ----------------------------------------------------------------------
/// \brief Copia una matriu en un altre.
/// \param dst: Destinacio de la copia.
/// \param src: Origen de la copia.
///
void Transformation::copy(
	Matrix &dst,
	const Matrix &src) {

    memcpy(&dst, &src, sizeof(Matrix));
	/*for (int r = 0; r < 3; r++)
		for (int c = 0; c < 3; c++)
			dst[r][c] = src[r][c];*/
}


/// ----------------------------------------------------------------------
/// \brief Multiplica dues matrius.
/// \param dst: Destinacio del resultat.
/// \param src1: Primera matriu a multiplicat.
/// \param src2: Segona matriu a multiplicar.
///
void Transformation::multiply(
	Matrix &dst,
	const Matrix &src1,
	const Matrix &src2) {

	for (int r = 0; r < 3; r++)
		for (int c = 0; c < 3; c++) {
			int sum = 0;
			for (int z = 0; z < 3; z++)
				sum += src1[r][z] * src2[z][c];
			dst[r][c] = sum;
	    }
}


/// ----------------------------------------------------------------------
/// \brief Operador d'asignacio.
/// \param[in] t: La transformacio a asignar.
///
Transformation & Transformation::operator = (
    const Transformation &t) {
    
    copy(m, t.m);    
    return *this;
}
