#pragma once


namespace eos {


    enum class BasicResults {
        success,
        error
    };


    template <typename Enum_>
    class ResultBase {
        private:
            Enum_ const _result;

        protected:
            constexpr ResultBase(Enum_ result) :
                _result {result} {
            }        

        public:
            constexpr bool isSuccess() const {
                return _result == Enum_::success;
            }

            constexpr bool hasError() const {
                return _result != Enum_::success;
            }

            constexpr Enum_ getResult() const {
                return _result; }
    };


    template <typename Enum_>
    class SimpleResult: public ResultBase<Enum_> {
        public:
            constexpr static SimpleResult success() {
                return SimpleResult(Enum_::success);
            }

            constexpr static SimpleResult busy() {
                return SimpleResult(Enum_::busy);
            }

            constexpr static SimpleResult timeout() {
                return SimpleResult(Enum_::timeout);
            }

            constexpr static SimpleResult error() {
                return SimpleResult(Enum_::error);
            }

        private:
            constexpr SimpleResult(Enum_ result) :
                ResultBase<Enum_> {result} {
            }
    };


    template <typename Enum_, typename Value_>
    class ComplexResult: public ResultBase<Enum_> {
        private:
            Value_ const _value;
            
        private:
            constexpr ComplexResult(Enum_ status, Value_ value = {}) :
                ResultBase<Enum_> {status},
                _value {value} {
            }        
            
        public:
            constexpr Value_ getValue() const {
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

    
    template <typename Enum_, typename Value_>
    constexpr bool isSuccess(const ComplexResult<Enum_, Value_> &result) {
        return result.isSuccess();
    }
    
    template <typename Enum_, typename Value_>
    constexpr bool hasError(const ComplexResult<Enum_, Value_> &result) {
        return !result.isSuccess();
    }
}
