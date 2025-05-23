#pragma once
#ifndef __eosTouchPadDriver_FT5336__
#define __eosTouchPadDriver_FT5336__


// EOS includes
//
#include "eos.h"

#ifdef USE_TOUCHPAD


#include "Controllers/TouchPad/eosTouchPadDriver.h"
#include "HTL/htlI2C.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlINT.h"
#ifdef EOS_PLATFORM_STM32
#include "HTL/STM32/htlEXTI.h"
#endif


// Adressa I2C
#ifndef FT5336_I2C_ADDR
#define FT5336_I2C_ADDR                0x70
#endif

// Max detectable simultaneous touches
#define FT5336_MAX_DETECTABLE_TOUCH         ((uint8_t)0x05)

// Current mode register of the FT5336 (R/W)
#define FT5336_DEV_MODE_REG                 ((uint8_t)0x00)

// Possible values of FT5336_DEV_MODE_REG
#define FT5336_DEV_MODE_WORKING             ((uint8_t)0x00)
#define FT5336_DEV_MODE_FACTORY             ((uint8_t)0x04)

#define FT5336_DEV_MODE_MASK                ((uint8_t)0x07)
#define FT5336_DEV_MODE_SHIFT               ((uint8_t)0x04)

// Gesture ID register
#define FT5336_GEST_ID_REG                  ((uint8_t)0x01)

// Possible values of FT5336_GEST_ID_REG
#define FT5336_GEST_ID_NO_GESTURE           ((uint8_t)0x00)
#define FT5336_GEST_ID_MOVE_UP              ((uint8_t)0x10)
#define FT5336_GEST_ID_MOVE_RIGHT           ((uint8_t)0x14)
#define FT5336_GEST_ID_MOVE_DOWN            ((uint8_t)0x18)
#define FT5336_GEST_ID_MOVE_LEFT            ((uint8_t)0x1C)
#define FT5336_GEST_ID_SINGLE_CLICK         ((uint8_t)0x20)
#define FT5336_GEST_ID_DOUBLE_CLICK         ((uint8_t)0x22)
#define FT5336_GEST_ID_ROTATE_CLOCKWISE     ((uint8_t)0x28)
#define FT5336_GEST_ID_ROTATE_C_CLOCKWISE   ((uint8_t)0x29)
#define FT5336_GEST_ID_ZOOM_IN              ((uint8_t)0x40)
#define FT5336_GEST_ID_ZOOM_OUT             ((uint8_t)0x49)

// Touch Data Status register : gives number of active touch points (0..5)
#define FT5336_TD_STAT_REG                  ((uint8_t)0x02)

// Values related to FT5336_TD_STAT_REG
#define FT5336_TD_STAT_MASK                 ((uint8_t)0x0F)
#define FT5336_TD_STAT_SHIFT                ((uint8_t)0x00)

// Values Pn_XH and Pn_YH related
#define FT5336_TOUCH_EVT_FLAG_PRESS_DOWN    ((uint8_t)0x00)
#define FT5336_TOUCH_EVT_FLAG_LIFT_UP       ((uint8_t)0x01)
#define FT5336_TOUCH_EVT_FLAG_CONTACT       ((uint8_t)0x02)
#define FT5336_TOUCH_EVT_FLAG_NO_EVENT      ((uint8_t)0x03)

#define FT5336_TOUCH_EVT_FLAG_SHIFT         ((uint8_t)0x06)
#define FT5336_TOUCH_EVT_FLAG_MASK          ((uint8_t)(3 << FT5336_TOUCH_EVT_FLAG_SHIFT))

#define FT5336_TOUCH_POS_MSB_MASK           ((uint8_t)0x0F)
#define FT5336_TOUCH_POS_MSB_SHIFT          ((uint8_t)0x00)

// Values Pn_XL and Pn_YL related
#define FT5336_TOUCH_POS_LSB_MASK           ((uint8_t)0xFF)
#define FT5336_TOUCH_POS_LSB_SHIFT          ((uint8_t)0x00)

#define FT5336_P1_XH_REG                    ((uint8_t)0x03)
#define FT5336_P1_XL_REG                    ((uint8_t)0x04)
#define FT5336_P1_YH_REG                    ((uint8_t)0x05)
#define FT5336_P1_YL_REG                    ((uint8_t)0x06)

// Touch Pressure register value (R)
#define FT5336_P1_WEIGHT_REG                ((uint8_t)0x07)

// Values Pn_WEIGHT related
#define FT5336_TOUCH_WEIGHT_MASK            ((uint8_t)0xFF)
#define FT5336_TOUCH_WEIGHT_SHIFT           ((uint8_t)0x00)

// Touch area register
#define FT5336_P1_MISC_REG                  ((uint8_t)0x08)

// Values related to FT5336_Pn_MISC_REG
#define FT5336_TOUCH_AREA_MASK              ((uint8_t)(0x04 << 4))
#define FT5336_TOUCH_AREA_SHIFT             ((uint8_t)0x04)

#define FT5336_P2_XH_REG                    ((uint8_t)0x09)
#define FT5336_P2_XL_REG                    ((uint8_t)0x0A)
#define FT5336_P2_YH_REG                    ((uint8_t)0x0B)
#define FT5336_P2_YL_REG                    ((uint8_t)0x0C)
#define FT5336_P2_WEIGHT_REG                ((uint8_t)0x0D)
#define FT5336_P2_MISC_REG                  ((uint8_t)0x0E)

#define FT5336_P3_XH_REG                    ((uint8_t)0x0F)
#define FT5336_P3_XL_REG                    ((uint8_t)0x10)
#define FT5336_P3_YH_REG                    ((uint8_t)0x11)
#define FT5336_P3_YL_REG                    ((uint8_t)0x12)
#define FT5336_P3_WEIGHT_REG                ((uint8_t)0x13)
#define FT5336_P3_MISC_REG                  ((uint8_t)0x14)

#define FT5336_P4_XH_REG                    ((uint8_t)0x15)
#define FT5336_P4_XL_REG                    ((uint8_t)0x16)
#define FT5336_P4_YH_REG                    ((uint8_t)0x17)
#define FT5336_P4_YL_REG                    ((uint8_t)0x18)
#define FT5336_P4_WEIGHT_REG                ((uint8_t)0x19)
#define FT5336_P4_MISC_REG                  ((uint8_t)0x1A)

#define FT5336_P5_XH_REG                    ((uint8_t)0x1B)
#define FT5336_P5_XL_REG                    ((uint8_t)0x1C)
#define FT5336_P5_YH_REG                    ((uint8_t)0x1D)
#define FT5336_P5_YL_REG                    ((uint8_t)0x1E)
#define FT5336_P5_WEIGHT_REG                ((uint8_t)0x1F)
#define FT5336_P5_MISC_REG                  ((uint8_t)0x20)

#define FT5336_P6_XH_REG                    ((uint8_t)0x21)
#define FT5336_P6_XL_REG                    ((uint8_t)0x22)
#define FT5336_P6_YH_REG                    ((uint8_t)0x23)
#define FT5336_P6_YL_REG                    ((uint8_t)0x24)
#define FT5336_P6_WEIGHT_REG                ((uint8_t)0x25)
#define FT5336_P6_MISC_REG                  ((uint8_t)0x26)

#define FT5336_P7_XH_REG                    ((uint8_t)0x27)
#define FT5336_P7_XL_REG                    ((uint8_t)0x28)
#define FT5336_P7_YH_REG                    ((uint8_t)0x29)
#define FT5336_P7_YL_REG                    ((uint8_t)0x2A)
#define FT5336_P7_WEIGHT_REG                ((uint8_t)0x2B)
#define FT5336_P7_MISC_REG                  ((uint8_t)0x2C)

#define FT5336_P8_XH_REG                    ((uint8_t)0x2D)
#define FT5336_P8_XL_REG                    ((uint8_t)0x2E)
#define FT5336_P8_YH_REG                    ((uint8_t)0x2F)
#define FT5336_P8_YL_REG                    ((uint8_t)0x30)
#define FT5336_P8_WEIGHT_REG                ((uint8_t)0x31)
#define FT5336_P8_MISC_REG                  ((uint8_t)0x32)

#define FT5336_P9_XH_REG                    ((uint8_t)0x33)
#define FT5336_P9_XL_REG                    ((uint8_t)0x34)
#define FT5336_P9_YH_REG                    ((uint8_t)0x35)
#define FT5336_P9_YL_REG                    ((uint8_t)0x36)
#define FT5336_P9_WEIGHT_REG                ((uint8_t)0x37)
#define FT5336_P9_MISC_REG                  ((uint8_t)0x38)

#define FT5336_P10_XH_REG                   ((uint8_t)0x39)
#define FT5336_P10_XL_REG                   ((uint8_t)0x3A)
#define FT5336_P10_YH_REG                   ((uint8_t)0x3B)
#define FT5336_P10_YL_REG                   ((uint8_t)0x3C)
#define FT5336_P10_WEIGHT_REG               ((uint8_t)0x3D)
#define FT5336_P10_MISC_REG                 ((uint8_t)0x3E)

// Threshold for touch detection
#define FT5336_TH_GROUP_REG                 ((uint8_t)0x80)

// Values FT5336_TH_GROUP_REG : threshold related
#define FT5336_THRESHOLD_MASK               ((uint8_t)0xFF)
#define FT5336_THRESHOLD_SHIFT              ((uint8_t)0x00)

// Filter function coefficients
#define FT5336_TH_DIFF_REG                  ((uint8_t)0x85)

// Control register
#define FT5336_CTRL_REG                     ((uint8_t)0x86)

// Values related to FT5336_CTRL_REG

// Will keep the Active mode when there is no touching
#define FT5336_CTRL_KEEP_ACTIVE_MODE        ((uint8_t)0x00)

// Switching from Active mode to Monitor mode automatically when there is no touching
#define FT5336_CTRL_KEEP_AUTO_SWITCH_MONITOR_MODE  ((uint8_t)0x01

// The time period of switching from Active mode to Monitor mode when there is no touching
#define FT5336_TIMEENTERMONITOR_REG         ((uint8_t)0x87)

// Report rate in Active mode
#define FT5336_PERIODACTIVE_REG             ((uint8_t)0x88)

// Report rate in Monitor mode
#define FT5336_PERIODMONITOR_REG            ((uint8_t)0x89)

// The value of the minimum allowed angle while Rotating gesture mode
#define FT5336_RADIAN_VALUE_REG             ((uint8_t)0x91)

// Maximum offset while Moving Left and Moving Right gesture
#define FT5336_OFFSET_LEFT_RIGHT_REG        ((uint8_t)0x92)

// Maximum offset while Moving Up and Moving Down gesture
#define FT5336_OFFSET_UP_DOWN_REG           ((uint8_t)0x93)

// Minimum distance while Moving Left and Moving Right gesture
#define FT5336_DISTANCE_LEFT_RIGHT_REG      ((uint8_t)0x94)

// Minimum distance while Moving Up and Moving Down gesture
#define FT5336_DISTANCE_UP_DOWN_REG         ((uint8_t)0x95)

// Maximum distance while Zoom In and Zoom Out gesture
#define FT5336_DISTANCE_ZOOM_REG            ((uint8_t)0x96)

// High 8-bit of LIB Version info
#define FT5336_LIB_VER_H_REG                ((uint8_t)0xA1)

// Low 8-bit of LIB Version info
#define FT5336_LIB_VER_L_REG                ((uint8_t)0xA2)

// Chip Selecting
#define FT5336_CIPHER_REG                   ((uint8_t)0xA3)

// Interrupt mode register (used when in interrupt mode)
#define FT5336_GMODE_REG                    ((uint8_t)0xA4)

#define FT5336_G_MODE_INTERRUPT_MASK        ((uint8_t)0x03)
#define FT5336_G_MODE_INTERRUPT_SHIFT       ((uint8_t)0x00)

// Possible values of FT5336_GMODE_REG
#define FT5336_G_MODE_INTERRUPT_POLLING     ((uint8_t)0x00)
#define FT5336_G_MODE_INTERRUPT_TRIGGER     ((uint8_t)0x01)

// Current power mode the FT5336 system is in (R)
#define FT5336_PWR_MODE_REG                 ((uint8_t)0xA5)

// FT5336 firmware version
#define FT5336_FIRMID_REG                   ((uint8_t)0xA6)

// FT5336 Chip identification register
#define FT5336_CHIP_ID_REG                  ((uint8_t)0xA8)

//  Possible values of FT5336_CHIP_ID_REG
#define FT5336_ID_VALUE                     ((uint8_t)0x51)

// Release code version
#define FT5336_RELEASE_CODE_ID_REG          ((uint8_t)0xAF)

// Current operating mode the FT5336 system is in (R)
#define FT5336_STATE_REG                    ((uint8_t)0xBC)


namespace eos {

	class TouchPadDriver_FT5336;

	using ITouchPadEvent = ICallbackP1<TouchPadDriver_FT5336*>;

	template <typename instance_>
	using TouchPadEvent = CallbackP1<instance_, TouchPadDriver_FT5336*>;


	class TouchPadDriver_FT5336: public TouchPadDriver {
		private:
	    	using PinINT = TOUCHPAD_INT_Pin;
	    	using PinInterruptINT = TOUCHPAD_INT_PinInterrupt;
			using PinSCL = TOUCHPAD_SCL_Pin;
			using PinSDA = TOUCHPAD_SDA_Pin;
			using DevI2C = TOUCHPAD_I2C_Device;

			using IntNotifyEvent = htl::gpio::NotifyEvent<TouchPadDriver_FT5336>;

			static constexpr uint16_t _width = TOUCHPAD_WIDTH;
     		static constexpr uint16_t _height = TOUCHPAD_HEIGHT;
     		static constexpr uint8_t _i2cAddr = TOUCHPAD_I2C_ADDR;

     		static constexpr htl::irq::VectorID _vector = TOUCHPAD_INT_IntVector;
        	static constexpr htl::irq::Priority _priority = htl::irq::Priority::_15;
        	static constexpr htl::irq::SubPriority _subPriority = htl::irq::SubPriority::_0;

			static ITouchPadDriver *_instance;
			TouchPadOrientation _orientation;
			IntNotifyEvent _intNotifyEvent;
			ITouchPadEvent *_touchPadEvent;

			TouchPadDriver_FT5336(const TouchPadDriver_FT5336 &) = delete;
			TouchPadDriver_FT5336(const TouchPadDriver_FT5336 &&) = delete;

			void initializeInterface();
			uint8_t readRegister(uint8_t reg);
			void writeRegister(uint8_t reg, uint8_t value);
			void intNotifyEventHandler(htl::gpio::PinInterrupt *sender, htl::gpio::NotifyEventArgs &args);

		public:
			TouchPadDriver_FT5336();

			void initialize();
			void deinitialize();

			int getPadWidth() const override { return _width; }
			int getPadHeight() const override { return _height; }
			int getTouchCount();
			bool getState(TouchPadState& state);
			void setOrientation(TouchPadOrientation orientation);
			void setTouchPadEvent(ITouchPadEvent &event, bool enabled = true) {
				_touchPadEvent = &event;
			}
			void enableInt();
			void disableInt();
			void clearInt();
	};
}


#endif // USE_TOUCHPAD


#endif // __eosTouchPadDriver_FT5336Driver__
