#include "osal/osalMemory.h"
#include "FreeRTOS.h"


/// ----------------------------------------------------------------------
/// \brief Obte un bloc de memoria.
/// \param size: Tamany del bloc de memoria.
/// \param p: Adressa del bloc de memoria obtingut.
/// \return Resultat de l'operacio.
///
uint8_t osalMemoryAlloc(
	unsigned size,
	void **p) {

#ifdef OSAL_CHECK_PARAMETERS
	if (size == 0)
		return OSAL_STATUS_ERROR_PARAMETER;
	if (p == NULL)
		return OSAL_STATUS_ERROR_PARAMETER;
#endif

    *p = pvPortMalloc(size);
    if (*p == NULL)
    	return OSAL_STATUS_ERROR_MEMORY;

    return OSAL_STATUS_OK;
}


/// ----------------------------------------------------------------------
/// \brief Allivera un bloc de memoria.
/// \param p: Adressa del bloc de memoria.
/// \return Resultat de l'operacio.
///
uint8_t osalMemoryFree(
	void *p) {

#ifdef OSAL_CHECK_PARAMETERS
	if (p == NULL)
		return OSAL_STATUS_ERROR_PARAMETER;
#endif

	vPortFree(p);

	return OSAL_STATUS_OK;
}
