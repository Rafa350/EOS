#pragma once
#ifndef __eosDigInputService__
#define __eosDigInputService__


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosIntrusiveForwardList.h"


namespace eos {

	// Declaracions forward
	//
    class DigInputService;
    class DigInput;
    class PinDriver;

    // Definicio de handlers
    //
    using DigInputHandler = DigInput*;
    using DigInputServiceHandler = DigInputService*;

    // Declaracions per les llistes
    //
    using DigInputList = IntrusiveForwardList<DigInput, 0>;
    using DigInputListNode = IntrusiveForwardListNode<DigInput, 0>;

    /// \brief Clase que implementa una entrada digital
    ///
    class DigInput: public DigInputListNode {
    	private:
    		uint32_t const _tag;

    	protected:
    		inline DigInput(uint32_t tag): _tag {tag} { }

    	public:
    	    DigInput(const DigInput&) = delete;
    	    DigInput(const DigInput&&) = delete;

    	    DigInput& operator=(const DigInput&) = delete;
    	    DigInput& operator=(const DigInput&&) = delete;

    	    inline uint32_t getTag() const { return _tag; }
    };

    /// \brief Clase que implementa el servei de gestio d'entrades digitals
    //
    class DigInputService final: public Service {
    	public:
			using IBeforeScanEvent = ICallbackP1<DigInputService*>;
			template <typename Instance_> using BeforeScanEvent = CallbackP1<Instance_, DigInputService*>;

			struct InputChangedEventArgs {
				uint32_t tag;
				bool value;
			};
			using IInputChangedEvent = ICallbackP2<DigInputService*, InputChangedEventArgs*>;
			template <typename Instance_> using InputChangedEvent = CallbackP2<Instance_, DigInputService*, InputChangedEventArgs*>;

        private:
    		DigInputList _inputs;
    		IInputChangedEvent *_inputChangedEvent;
    		IBeforeScanEvent *_beforeScanEvent;
            uint32_t _scanPeriod;

        private:
            void onInputChanged(DigInput *input);
            void beforeScan();
            void raiseInitializeNotificationEvent(ServiceParams *params);

        protected:
            void onInitialize(ServiceParams &params) override;
            void onExecute() override;

        public:
            DigInputService();
            DigInputService(const DigInputService&) = delete;
            DigInputService(const DigInputService&&) = delete;

            DigInputService& operator=(const DigInputService&) = delete;
    	    DigInputService& operator=(const DigInputService&&) = delete;

            void setScanPeriod(uint32_t scanPeriod);

            DigInput * addInput(PinDriver *drv, uint32_t tag);
            DigInput * getInput(uint32_t tag) const;

            bool read(const DigInput *input) const;
            uint32_t getEdges(DigInput *input, bool clear = true) const;

            inline void setInputChangedEvent(IInputChangedEvent &event) {
            	_inputChangedEvent = &event;
            }
            inline void clearInputChangedEvent() {
            	_inputChangedEvent = nullptr;
            }

            inline void setBeforeScanEvent(IBeforeScanEvent &event) {
            	_beforeScanEvent = &event;
            }
            inline void clearBeforeScanEvent() {
            	_beforeScanEvent = nullptr;
            }
    };

}


#endif // __eosDigInputService__
