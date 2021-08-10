#ifndef __PIC32_halI2CTpl__
#define __PIC32_halI2CTpl__


namespace eos {

    enum class I2cChannel {
        channel1 = HAL_I2C_CHANNEL_1,
        channel2 = HAL_I2C_CHANNEL_2,
        channel3 = HAL_I2C_CHANNEL_3,
        channel4 = HAL_I2C_CHANNEL_4,
        channel5 = HAL_I2C_CHANNEL_5
    };

    template <I2cChannel channel>
    class I2cAdapter {

    };
}


#endif // __PIC32_halI2CTpl__

