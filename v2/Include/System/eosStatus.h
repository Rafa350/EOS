#pragma once
#ifndef __eosStatus__
#define __eosStatus__


namespace eos {


    enum class Status {
        success,
        busy,
        timeout,
        error
    };
    
    
    template <typename Enum_>
    class SimpleStatus {
        private:
            Enum_ const _status;

        private:
            constexpr Simple(Enum_ status) :
                _status {status} {
            }        

            constexpr bool isSuccess() const {
                return _status == Enum_::success;
            }
            
            constexpr bool hasError() const {
                return _status != Enum_::success;
            }        
    }
    
    
    template <typename Enum_, typename ValueType_>
    class ResultStatus: public SimpleStatus<Enum_> {
        private:
            ValueType_ const _value;
            
        private:
            constexpr ResultStatus(Enum_ status, ValueType_ value = {}) :
                SimpleStatus {status}, 
                _value {value} {
            }        
            
        public:
            constexpr static ResultStatus makeSuccess(ValueType_ value) {
                return ResultStatus(Enum_::success, value);
            }
            
            constexpr static ResultStatus makeError(Enum_ status = Enum_::error) {
                return ResultStatus(status);
            }            
            
            constexpr ValueType_ getValue() const { 
                return _value; 
            }
    };
                
    
    
    template <typename Enum_>
    constexpr bool isSuccess(Enum_ status) {
        return status == Enum_::success;
    }
    
    template <typename Enum_>
    constexpr bool hasError(Enum_ status) {
        return status != Enum_::success;
    }
    
    
    
    template <typename Enum_, typename ValueType_>
    constexpr bool isSuccessful(const ResultStatus<Enum_, ValueType> &status) {
        return status.isSuccess();
    }
    
    template <typename Enum_, typename ValueType_>
    constexpr bool hasError(const ResultStatus<Enum_, ValueType_> &status) {
        return !status.isSuccess();
    }
}


#endif // __eosStatus__