#ifndef __HAL_I2C_H
#define	__HAL_I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

    
typedef void (*I2CInterruptCallback)(unsigned id);

void halI2CMasterInitialize(unsigned moduleId, unsigned baudRate, I2CInterruptCallback callback, void *param);
void halI2CMasterStart(unsigned moduleId);
bool halI2CMasterIsBusIdle(unsigned moduleId);


#ifdef	__cplusplus
}
#endif

#endif

