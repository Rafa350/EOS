module;


#include "hardware.h"


export module Eos.Hardware.GPIO;


export import Eos.Hardware.GPIO.__TYPES;

import Eos.Bits;
import Eos.Hardware.GPIO.__ACTIVATOR;
import Eos.Hardware.GPIO.__INITIALIZER;
import Eos.Hardware.GPIO.__PLATFORM_TRAITS;
import Eos.Hardware.GPIO.__PORT_TRAITS;
import Eos.Hardware.GPIO.__PIN_TRAITS;
import Eos.Hardware.GPIO.__UTILS;
import Eos.Hardware.Interrupts;
import Eos.Types;


export namespace eos::hardware::gpio {

    /// \brief   Gestiona un port del GPIO
    /// \tparam  portId_ El identificador del port.
    ///
    template <PortID portId_>
    class GPIOPort final: private StaticClass<GPIOPort<portId_>> {
        public:
            static constexpr auto portId = portId_;

        private:
            using PortTraits = internal::PortTraits<portId_>;
            using Activator = internal::Activator<portId_>;
            using Initializer = internal::PortInitializer<portId_>;

        private:
            static constexpr auto _gpioAddr = PortTraits::gpioAddr;

        public:
            static inline void initInput(PinMask mask, PullUpDown pupd) {
                Activator::activate(mask);
                Initializer::initInput(mask, pupd);
            }

            static inline void initOutput(PinMask mask, OutputType type, PullUpDown pupd, Speed speed = Speed::medium) {
                Activator::activate(mask);
                Initializer::initOutput(mask, type, pupd, speed);
            }

            static inline void set(PinMask mask) {
                reinterpret_cast<GPIO_TypeDef*>(_gpioAddr)->BSRR = mask;
            }

            static inline void clear(PinMask mask) {
                reinterpret_cast<GPIO_TypeDef*>(_gpioAddr)->BSRR = mask << 16;
            }

            static inline void toggle(PinMask mask) {
                auto i = eos::hardware::interrupts::Irq::getInterruptState();
                eos::hardware::interrupts::Irq::disableInterrupts();
                reinterpret_cast<GPIO_TypeDef*>(_gpioAddr)->ODR ^= mask;
                eos::hardware::interrupts::Irq::restoreInterrupts(i);
            }

            static inline uint16_t read(PinMask mask) {
                return reinterpret_cast<GPIO_TypeDef*>(_gpioAddr)->IDR & (uint16_t) mask;
            }

            static inline void write(PinMask mask, uint16_t state) {
                reinterpret_cast<GPIO_TypeDef*>(_gpioAddr)->BSRR = ((~state & mask) << 16) | (state & mask);
            }

            static inline void lock() {

            }
    };

    /// \brief   Gestiona un pin del GPIO
    /// \tparam  portId_ El identificador del port.
    /// \tparam  pinId_  El identificador del pin.
    ///
    template <PortID portId_, PinID pinId_>
    class GPIOPin final: private StaticClass<GPIOPin<portId_, pinId_>> {
        public:
            static constexpr auto portID = portId_;
            static constexpr auto pinID = pinId_;

        private:
            using PortTraits = internal::PortTraits<portId_>;
            using PinTraits = internal::PinTraits<pinId_>;
            using Activator = internal::Activator<portId_>;
            using Initializer = internal::PinInitializer<portId_, pinId_>;

        private:
            static constexpr auto _mask = PinMask(1 << PinTraits::bit);
            static constexpr auto _gpioAddr = PortTraits::gpioAddr;

        public:
            static inline void initInput(PullUpDown pupd) {
                Activator::activate(_mask);
                Initializer::initInput(pupd);
            }

            static inline void initOutput(OutputType type, PullUpDown pupd, Speed speed, bool state) {
                Activator::activate(_mask);
                Initializer::initOutput(type, pupd, speed, state);
            }

            static inline void initAlternate(OutputType outputType, PullUpDown pupd, Speed speed, AlternateFunction af) {
                Activator::activate(_mask);
                Initializer::initAlternate(outputType, pupd, speed, af);
            }

            static inline void initAnalogic() {
                Activator::activate(_mask);
                Initializer::initAnalogic();
            }

            static inline void deinitialize() {
                Initializer::deinitialize();
                Activator::deactivate(_mask);
            }

            static inline void set() {
                reinterpret_cast<GPIO_TypeDef*>(_gpioAddr)->BSRR = _mask;
            }

            static inline void clear() {
                reinterpret_cast<GPIO_TypeDef*>(_gpioAddr)->BSRR = _mask << 16;
            }

            static inline void toggle() {
                auto i = eos::hardware::interrupts::Irq::getInterruptState();
                eos::hardware::interrupts::Irq::disableInterrupts();
                reinterpret_cast<GPIO_TypeDef*>(_gpioAddr)->ODR ^= _mask;
                eos::hardware::interrupts::Irq::restoreInterrupts(i);
            }

            static inline void write(bool state) {
                reinterpret_cast<GPIO_TypeDef*>(_gpioAddr)->BSRR = state ? _mask : _mask << 16;
            }

            static inline bool read() {
                return (reinterpret_cast<GPIO_TypeDef*>(_gpioAddr)->IDR & _mask) != 0;
            }

            static inline void lock() {
                reinterpret_cast<GPIO_TypeDef*>(_gpioAddr)->LCKR = (1 << 16) | _mask;
                reinterpret_cast<GPIO_TypeDef*>(_gpioAddr)->LCKR = (0 << 16) | _mask;
                reinterpret_cast<GPIO_TypeDef*>(_gpioAddr)->LCKR = (1 << 16) | _mask;
                auto dummy = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr)->LCKR;
            }
    };
    

    /// brief Clase que representa un port.
    ///
    class PortDevice: private NonCopyableClass {
        private:
            virtual void initInputImpl(PinMask mask, PullUpDown pupd) const = 0;
            virtual void initOutputImpl(PinMask mask, OutputType type, PullUpDown pupd, Speed speed = Speed::medium) const = 0;
            virtual void deinitializeImpl() const = 0;

            virtual void setImpl(PinMask mask) const = 0;
            virtual void clearImpl(PinMask mask) const = 0;
            virtual void toggleImpl(PinMask mask) const = 0;
            virtual uint16_t readImpl(PinMask mask) const = 0;
            virtual void writeImpl(PinMask mask, uint16_t state) const = 0;

        protected:
            PortDevice() = default;

        public:
            inline void initInput(PinMask mask, PullUpDown pupd) const {
                initInputImpl(mask, pupd);
            }

            inline void initOutput(PinMask mask, OutputType type, PullUpDown pupd, Speed speed = Speed::medium) const {
                initOutputImpl(mask, type, pupd, speed);
            }

            inline void deinitialize() const {
                deinitializeImpl();
            }

            inline void set(PinMask mask) const {
                setImpl(mask);
            }

            inline void set(PinBit bit) const {
                setImpl(PinMask(bit));
            }

            inline void clear(PinMask mask) const {
                clearImpl(mask);
            }

            inline void clear(PinBit bit) const {
                clearImpl(PinMask(bit));
            }

            inline void toggle(PinMask mask) const {
                toggleImpl(mask);
            }

            inline void toggle(PinBit bit) const {
                toggleImpl(PinMask(bit));
            }

            inline uint16_t read() const {
                return readImpl(PinMask(0xFF));
            }

            inline bool read(PinBit bit) const {
                return readImpl(PinMask(bit)) != 0;
            }

            inline void write(PinMask mask, uint16_t state) const {
                writeImpl(mask, state);
            }

            inline void write(PinBit bit, bool state) const {
                writeImpl(PinMask(bit), state ? 1 << bit : 0);
            }
    };

    /// brief Clase que representa un port.
    ///
    template <PortID portId_>
    class PortDeviceX final: public PortDevice {
        public:
            static constexpr auto portID = portId_;

        private:
            using Port = GPIOPort<portId_>;

        private:
            static PortDeviceX _instance;

        public:
            static constexpr PortDeviceX *pInst = &_instance;
            static constexpr PortDeviceX &rInst = _instance;

        private:
            PortDeviceX() = default;

            void initInputImpl(PinMask mask, PullUpDown pupd) const override {
                Port::initInput(mask, pupd);
            }

            void initOutputImpl(PinMask mask, OutputType type, PullUpDown pupd, Speed speed = Speed::medium) const {
                Port::initOutptut(mask, type, pupd, speed);
            }

            void setImpl(PinMask mask) const override {
                Port::set(mask);
            }

            void clearImpl(PinMask mask) const override {
                Port::clear(mask);
            }

            void toggleImpl(PinMask mask) const override {
                Port::toggle(mask);
            }

            uint16_t readImpl(PinMask mask) const override {
                return Port::read(mask);
            }

            void writeImpl(PinMask mask, uint16_t state) const override {
                Port::write(mask, state);
            }
    };
    template <PortID portId_>
    PortDeviceX<portId_> PortDeviceX<portId_>::_instance;

#ifdef GPIOA_BASE
    using PortA = PortDeviceX<PortID::portA>;
#endif
#ifdef GPIOB_BASE
    using PortB = PortDeviceX<PortID::portB>;
#endif
#ifdef GPIOC_BASE
    using PortC = PortDeviceX<PortID::portC>;
#endif
#ifdef GPIOD_BASE
    using PortD = PortDeviceX<PortID::portD>;
#endif
#ifdef GPIOE_BASE
    using PortE = PortDeviceX<PortID::portE>;
#endif
#ifdef GPIOF_BASE
    using PortF = PortDeviceX<PortID::portF>;
#endif
#ifdef GPIOG_BASE
    using PortG = PortDeviceX<PortID::portG>;
#endif
#ifdef GPIOH_BASE
    using PortH = PortDeviceX<PortID::portH>;
#endif
#ifdef GPIOI_BASE
    using PortI = PortDeviceX<PortID::portI>;
#endif
#ifdef GPIOJ_BASE
    using PortJ = PortDeviceX<PortID::portJ>;
#endif
#ifdef GPIOK_BASE
    using PortK = PortDeviceX<PortID::portK>;
#endif


    /// brief Clase que representa un pin individual.
    ///
    class PinDevice: private NonCopyableClass {
        private:
            virtual void initInputImpl(PullUpDown pupd) const = 0;
            virtual void initOutputImpl(OutputType type, PullUpDown pupd, Speed speed, bool state) const = 0;
            virtual void initAlternateImpl(OutputType outputType, PullUpDown pupd, Speed speed, AlternateFunction af) const = 0;
            virtual void initAnalogicImpl() const = 0;
            virtual void deinitializeImpl() const = 0;

            virtual void setImpl() const = 0;
            virtual void clearImpl() const = 0;
            virtual void toggleImpl() const = 0;
            virtual void writeImpl(bool state) const = 0;
            virtual bool readImpl() const = 0;

        protected:
            constexpr PinDevice() = default;

        public:
            inline void initInput(PullUpDown pupd) const {
                initInputImpl(pupd);
            }

            inline void initOutput(OutputType type, PullUpDown pupd, Speed speed, bool state) const {
                initOutputImpl(type, pupd, speed, state);
            }

            inline void initAlternate(OutputType type, PullUpDown pupd, Speed speed, AlternateFunction af) const {
                initAlternateImpl(type, pupd, speed, af);
            }

            inline void initAnalogic() const {
                initAnalogicImpl();
            }

            inline void deinitialize() const {
                deinitializeImpl();
            }

            inline void set() const {
                setImpl();
            }

            inline void clear() const {
                clearImpl();
            }

            inline void toggle() const {
                toggleImpl();
            }

            inline void write(bool state) const {
                writeImpl(state);
            }

            inline bool read() const {
                return readImpl();
            }
    };


    /// brief Clase/Template que representa un pin individual especific.
    ///
    template <PortID portId_, PinID pinId_>
    class PinDeviceX final: public PinDevice {
        public:
            static constexpr auto portID = portId_;
            static constexpr auto pinID = pinId_;

        private:
            using Pin = GPIOPin<portId_, pinId_>;

        private:
            static PinDeviceX _instance;

        public:
            static constexpr PinDeviceX *pInst = &_instance;
            static constexpr PinDeviceX &rInst = _instance;

        private:
            constexpr PinDeviceX() = default;

            void initInputImpl(PullUpDown pupd) const override {
                Pin::initInput(pupd);
            }

            void initOutputImpl(OutputType type, PullUpDown pupd, Speed speed, bool state) const override {
                Pin::initOutput(type, pupd, speed, state);
            }

            void initAlternateImpl(OutputType type, PullUpDown pupd, Speed speed, AlternateFunction af) const override {
                Pin::initAlternate(type, pupd, speed, af);
            }

            void initAnalogicImpl() const override {
                Pin::initAnalogic();
            }

            void deinitializeImpl() const override {
                Pin::deinitialize();
            }

            void setImpl() const override {
                Pin::set();
            }

            void clearImpl() const override {
                Pin::clear();
            }

            void toggleImpl() const override {
                Pin::toggle();
            }

            void writeImpl(bool state) const override {
                Pin::write(state);
            }

            bool readImpl() const override {
                return Pin::read();
            }
    };
    template <PortID portId_, PinID pinId_>
    PinDeviceX<portId_, pinId_> PinDeviceX<portId_, pinId_>::_instance;

#ifdef GPIOA_BASE
    using PinA0 = PinDeviceX<PortID::portA, PinID::pin0>;
    using PinA1 = PinDeviceX<PortID::portA, PinID::pin1>;
    using PinA2 = PinDeviceX<PortID::portA, PinID::pin2>;
    using PinA3 = PinDeviceX<PortID::portA, PinID::pin3>;
    using PinA4 = PinDeviceX<PortID::portA, PinID::pin4>;
    using PinA5 = PinDeviceX<PortID::portA, PinID::pin5>;
    using PinA6 = PinDeviceX<PortID::portA, PinID::pin6>;
    using PinA7 = PinDeviceX<PortID::portA, PinID::pin7>;
    using PinA8 = PinDeviceX<PortID::portA, PinID::pin8>;
    using PinA9 = PinDeviceX<PortID::portA, PinID::pin9>;
    using PinA10 = PinDeviceX<PortID::portA, PinID::pin10>;
    using PinA11 = PinDeviceX<PortID::portA, PinID::pin11>;
    using PinA12 = PinDeviceX<PortID::portA, PinID::pin12>;
    using PinA13 = PinDeviceX<PortID::portA, PinID::pin13>;
    using PinA14 = PinDeviceX<PortID::portA, PinID::pin14>;
    using PinA15 = PinDeviceX<PortID::portA, PinID::pin15>;
#endif
#ifdef GPIOB_BASE
    using PinB0 = PinDeviceX<PortID::portB, PinID::pin0>;
    using PinB1 = PinDeviceX<PortID::portB, PinID::pin1>;
    using PinB2 = PinDeviceX<PortID::portB, PinID::pin2>;
    using PinB3 = PinDeviceX<PortID::portB, PinID::pin3>;
    using PinB4 = PinDeviceX<PortID::portB, PinID::pin4>;
    using PinB5 = PinDeviceX<PortID::portB, PinID::pin5>;
    using PinB6 = PinDeviceX<PortID::portB, PinID::pin6>;
    using PinB7 = PinDeviceX<PortID::portB, PinID::pin7>;
    using PinB8 = PinDeviceX<PortID::portB, PinID::pin8>;
    using PinB9 = PinDeviceX<PortID::portB, PinID::pin9>;
    using PinB10 = PinDeviceX<PortID::portB, PinID::pin10>;
    using PinB11 = PinDeviceX<PortID::portB, PinID::pin11>;
    using PinB12 = PinDeviceX<PortID::portB, PinID::pin12>;
    using PinB13 = PinDeviceX<PortID::portB, PinID::pin13>;
    using PinB14 = PinDeviceX<PortID::portB, PinID::pin14>;
    using PinB15 = PinDeviceX<PortID::portB, PinID::pin15>;
#endif
#ifdef GPIOC_BASE
    typedef PinDeviceX<PortID::portC, PinID::pin0> PinC0;
    typedef PinDeviceX<PortID::portC, PinID::pin1> PinC1;
    typedef PinDeviceX<PortID::portC, PinID::pin2> PinC2;
    typedef PinDeviceX<PortID::portC, PinID::pin3> PinC3;
    typedef PinDeviceX<PortID::portC, PinID::pin4> PinC4;
    typedef PinDeviceX<PortID::portC, PinID::pin5> PinC5;
    typedef PinDeviceX<PortID::portC, PinID::pin6> PinC6;
    typedef PinDeviceX<PortID::portC, PinID::pin7> PinC7;
    typedef PinDeviceX<PortID::portC, PinID::pin8> PinC8;
    typedef PinDeviceX<PortID::portC, PinID::pin9> PinC9;
    typedef PinDeviceX<PortID::portC, PinID::pin10> PinC10;
    typedef PinDeviceX<PortID::portC, PinID::pin11> PinC11;
    typedef PinDeviceX<PortID::portC, PinID::pin12> PinC12;
    typedef PinDeviceX<PortID::portC, PinID::pin13> PinC13;
    typedef PinDeviceX<PortID::portC, PinID::pin14> PinC14;
    typedef PinDeviceX<PortID::portC, PinID::pin15> PinC15;
#endif
#ifdef GPIOD_BASE
    typedef PinDeviceX<PortID::portD, PinID::pin0> PinD0;
    typedef PinDeviceX<PortID::portD, PinID::pin1> PinD1;
    typedef PinDeviceX<PortID::portD, PinID::pin2> PinD2;
    typedef PinDeviceX<PortID::portD, PinID::pin3> PinD3;
    typedef PinDeviceX<PortID::portD, PinID::pin4> PinD4;
    typedef PinDeviceX<PortID::portD, PinID::pin5> PinD5;
    typedef PinDeviceX<PortID::portD, PinID::pin6> PinD6;
    typedef PinDeviceX<PortID::portD, PinID::pin7> PinD7;
    typedef PinDeviceX<PortID::portD, PinID::pin8> PinD8;
    typedef PinDeviceX<PortID::portD, PinID::pin9> PinD9;
    typedef PinDeviceX<PortID::portD, PinID::pin10> PinD10;
    typedef PinDeviceX<PortID::portD, PinID::pin11> PinD11;
    typedef PinDeviceX<PortID::portD, PinID::pin12> PinD12;
    typedef PinDeviceX<PortID::portD, PinID::pin13> PinD13;
    typedef PinDeviceX<PortID::portD, PinID::pin14> PinD14;
    typedef PinDeviceX<PortID::portD, PinID::pin15> PinD15;
#endif
#ifdef GPIOE_BASE
    typedef PinDeviceX<PortID::portE, PinID::pin0> PinE0;
    typedef PinDeviceX<PortID::portE, PinID::pin1> PinE1;
    typedef PinDeviceX<PortID::portE, PinID::pin2> PinE2;
    typedef PinDeviceX<PortID::portE, PinID::pin3> PinE3;
    typedef PinDeviceX<PortID::portE, PinID::pin4> PinE4;
    typedef PinDeviceX<PortID::portE, PinID::pin5> PinE5;
    typedef PinDeviceX<PortID::portE, PinID::pin6> PinE6;
    typedef PinDeviceX<PortID::portE, PinID::pin7> PinE7;
    typedef PinDeviceX<PortID::portE, PinID::pin8> PinE8;
    typedef PinDeviceX<PortID::portE, PinID::pin9> PinE9;
    typedef PinDeviceX<PortID::portE, PinID::pin10> PinE10;
    typedef PinDeviceX<PortID::portE, PinID::pin11> PinE11;
    typedef PinDeviceX<PortID::portE, PinID::pin12> PinE12;
    typedef PinDeviceX<PortID::portE, PinID::pin13> PinE13;
    typedef PinDeviceX<PortID::portE, PinID::pin14> PinE14;
    typedef PinDeviceX<PortID::portE, PinID::pin15> PinE15;
#endif
#ifdef GPIOF_BASE
    typedef PinDeviceX<PortID::portF, PinID::pin0> PinF0;
    typedef PinDeviceX<PortID::portF, PinID::pin1> PinF1;
    typedef PinDeviceX<PortID::portF, PinID::pin2> PinF2;
    typedef PinDeviceX<PortID::portF, PinID::pin3> PinF3;
    typedef PinDeviceX<PortID::portF, PinID::pin4> PinF4;
    typedef PinDeviceX<PortID::portF, PinID::pin5> PinF5;
    typedef PinDeviceX<PortID::portF, PinID::pin6> PinF6;
    typedef PinDeviceX<PortID::portF, PinID::pin7> PinF7;
    typedef PinDeviceX<PortID::portF, PinID::pin8> PinF8;
    typedef PinDeviceX<PortID::portF, PinID::pin9> PinF9;
    typedef PinDeviceX<PortID::portF, PinID::pin10> PinF10;
    typedef PinDeviceX<PortID::portF, PinID::pin11> PinF11;
    typedef PinDeviceX<PortID::portF, PinID::pin12> PinF12;
    typedef PinDeviceX<PortID::portF, PinID::pin13> PinF13;
    typedef PinDeviceX<PortID::portF, PinID::pin14> PinF14;
    typedef PinDeviceX<PortID::portF, PinID::pin15> PinF15;
#endif
#ifdef GPIOG_BASE
    typedef PinDeviceX<PortID::portG, PinID::pin0> PinG0;
    typedef PinDeviceX<PortID::portG, PinID::pin1> PinG1;
    typedef PinDeviceX<PortID::portG, PinID::pin2> PinG2;
    typedef PinDeviceX<PortID::portG, PinID::pin3> PinG3;
    typedef PinDeviceX<PortID::portG, PinID::pin4> PinG4;
    typedef PinDeviceX<PortID::portG, PinID::pin5> PinG5;
    typedef PinDeviceX<PortID::portG, PinID::pin6> PinG6;
    typedef PinDeviceX<PortID::portG, PinID::pin7> PinG7;
    typedef PinDeviceX<PortID::portG, PinID::pin8> PinG8;
    typedef PinDeviceX<PortID::portG, PinID::pin9> PinG9;
    typedef PinDeviceX<PortID::portG, PinID::pin10> PinG10;
    typedef PinDeviceX<PortID::portG, PinID::pin11> PinG11;
    typedef PinDeviceX<PortID::portG, PinID::pin12> PinG12;
    typedef PinDeviceX<PortID::portG, PinID::pin13> PinG13;
    typedef PinDeviceX<PortID::portG, PinID::pin14> PinG14;
    typedef PinDeviceX<PortID::portG, PinID::pin15> PinG15;
#endif
#ifdef GPIOH_BASE
    typedef PinDeviceX<PortID::portH, PinID::pin0> PinH0;
    typedef PinDeviceX<PortID::portH, PinID::pin1> PinH1;
    typedef PinDeviceX<PortID::portH, PinID::pin2> PinH2;
    typedef PinDeviceX<PortID::portH, PinID::pin3> PinH3;
    typedef PinDeviceX<PortID::portH, PinID::pin4> PinH4;
    typedef PinDeviceX<PortID::portH, PinID::pin5> PinH5;
    typedef PinDeviceX<PortID::portH, PinID::pin6> PinH6;
    typedef PinDeviceX<PortID::portH, PinID::pin7> PinH7;
    typedef PinDeviceX<PortID::portH, PinID::pin8> PinH8;
    typedef PinDeviceX<PortID::portH, PinID::pin9> PinH9;
    typedef PinDeviceX<PortID::portH, PinID::pin10> PinH10;
    typedef PinDeviceX<PortID::portH, PinID::pin11> PinH11;
    typedef PinDeviceX<PortID::portH, PinID::pin12> PinH12;
    typedef PinDeviceX<PortID::portH, PinID::pin13> PinH13;
    typedef PinDeviceX<PortID::portH, PinID::pin14> PinH14;
    typedef PinDeviceX<PortID::portH, PinID::pin15> PinH15;
#endif
#ifdef GPIOI_BASE
    typedef PinDeviceX<PortID::portI, PinID::pin0> PinI0;
    typedef PinDeviceX<PortID::portI, PinID::pin1> PinI1;
    typedef PinDeviceX<PortID::portI, PinID::pin2> PinI2;
    typedef PinDeviceX<PortID::portI, PinID::pin3> PinI3;
    typedef PinDeviceX<PortID::portI, PinID::pin4> PinI4;
    typedef PinDeviceX<PortID::portI, PinID::pin5> PinI5;
    typedef PinDeviceX<PortID::portI, PinID::pin6> PinI6;
    typedef PinDeviceX<PortID::portI, PinID::pin7> PinI7;
    typedef PinDeviceX<PortID::portI, PinID::pin8> PinI8;
    typedef PinDeviceX<PortID::portI, PinID::pin9> PinI9;
    typedef PinDeviceX<PortID::portI, PinID::pin10> PinI10;
    typedef PinDeviceX<PortID::portI, PinID::pin11> PinI11;
    typedef PinDeviceX<PortID::portI, PinID::pin12> PinI12;
    typedef PinDeviceX<PortID::portI, PinID::pin13> PinI13;
    typedef PinDeviceX<PortID::portI, PinID::pin14> PinI14;
    typedef PinDeviceX<PortID::portI, PinID::pin15> PinI15;
#endif
#ifdef GPIOJ_BASE
    typedef PinDeviceX<PortID::portJ, PinID::pin0> PinJ0;
    typedef PinDeviceX<PortID::portJ, PinID::pin1> PinJ1;
    typedef PinDeviceX<PortID::portJ, PinID::pin2> PinJ2;
    typedef PinDeviceX<PortID::portJ, PinID::pin3> PinJ3;
    typedef PinDeviceX<PortID::portJ, PinID::pin4> PinJ4;
    typedef PinDeviceX<PortID::portJ, PinID::pin5> PinJ5;
    typedef PinDeviceX<PortID::portJ, PinID::pin6> PinJ6;
    typedef PinDeviceX<PortID::portJ, PinID::pin7> PinJ7;
    typedef PinDeviceX<PortID::portJ, PinID::pin8> PinJ8;
    typedef PinDeviceX<PortID::portJ, PinID::pin9> PinJ9;
    typedef PinDeviceX<PortID::portJ, PinID::pin10> PinJ10;
    typedef PinDeviceX<PortID::portJ, PinID::pin11> PinJ11;
    typedef PinDeviceX<PortID::portJ, PinID::pin12> PinJ12;
    typedef PinDeviceX<PortID::portJ, PinID::pin13> PinJ13;
    typedef PinDeviceX<PortID::portJ, PinID::pin14> PinJ14;
    typedef PinDeviceX<PortID::portJ, PinID::pin15> PinJ15;
#endif
#ifdef GPIOK_BASE
    typedef PinDeviceX<PortID::portK, PinID::pin0> PinK0;
    typedef PinDeviceX<PortID::portK, PinID::pin1> PinK1;
    typedef PinDeviceX<PortID::portK, PinID::pin2> PinK2;
    typedef PinDeviceX<PortID::portK, PinID::pin3> PinK3;
    typedef PinDeviceX<PortID::portK, PinID::pin4> PinK4;
    typedef PinDeviceX<PortID::portK, PinID::pin5> PinK5;
    typedef PinDeviceX<PortID::portK, PinID::pin6> PinK6;
    typedef PinDeviceX<PortID::portK, PinID::pin7> PinK7;
    typedef PinDeviceX<PortID::portK, PinID::pin8> PinK8;
    typedef PinDeviceX<PortID::portK, PinID::pin9> PinK9;
    typedef PinDeviceX<PortID::portK, PinID::pin10> PinK10;
    typedef PinDeviceX<PortID::portK, PinID::pin11> PinK11;
    typedef PinDeviceX<PortID::portK, PinID::pin12> PinK12;
    typedef PinDeviceX<PortID::portK, PinID::pin13> PinK13;
    typedef PinDeviceX<PortID::portK, PinID::pin14> PinK14;
    typedef PinDeviceX<PortID::portK, PinID::pin15> PinK15;
#endif

}
