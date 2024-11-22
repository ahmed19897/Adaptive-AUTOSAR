
// ErrorDomain include guard following SWS_CORE_90001]
#ifndef ARA_CORE_ERROR_CODE_H_
#define ARA_CORE_ERROR_CODE_H_
    #include "error_domain.h"
    #include <string_view>
    namespace ara
    {
        namespace core
        {
            //Encapsulation of an error code.
            //An ErrorCode contains a raw error code value and an error domain. The raw error code value is
            //specific to this error domain.
            class ErrorCode final
            {
                public:
                    // Construct a new ErrorCode instance with parameters.
                    // This constructor does not participate in overload resolution unless EnumT is an enum type.
                    template <typename EnumT>constexpr ErrorCode (EnumT e, ara::core::ErrorDomain::SupportDataType data=ara::core::ErrorDomain::SupportDataType()) noexcept
                    :MyErrorCode(ara::core::ErrorDomain::CodeType(e)),MyErrorDomain(nullptr),MySupportData(data)
                    {
                        ;
                    }
                    // Construct a new ErrorCode instance with parameters.
                    constexpr ErrorCode (ara::core::ErrorDomain::CodeType value, const ara::core::ErrorDomain &domain, ara::core::ErrorDomain::SupportDataType data=ara::core::ErrorDomain::SupportDataType()) noexcept
                    :MyErrorCode(value),MyErrorDomain(&domain),MySupportData(data)
                    {
                        ;
                    }
                    // Return the raw error code value
                    constexpr ara::core::ErrorDomain::CodeType Value () const noexcept
                    {
                        return MyErrorCode;
                    }
                    // Return the domain with which this ErrorCode is associated
                    constexpr const ara::core::ErrorDomain& Domain () const noexcept
                    {
                        // should consider using the gsl library no null
                        // using the constructor with the domain makes more sense ,so we don't have null pointers
                        // now we have the risk of returning null pointers
                        // verify
                        return *MyErrorDomain;   
                    }
                    // Return the supplementary error context data.
                    // The underlying type and the meaning of the returned value are implementation-defined.
                    constexpr ara::core::ErrorDomain::SupportDataType SupportData () const noexcept
                    {
                        return MySupportData;
                    }
                    // Return a textual representation of this ErrorCode.
                    std::string_view Message () const noexcept
                    {
                        std::string_view Result{this->Domain().Message(this->MyErrorCode)};
                        return Result;
                    }
                    // Throw this error as exception.
                    // This function will determine the appropriate exception type for this ErrorCode and throw it. The
                    // thrown exception will contain this ErrorCode.
                    void ThrowAsException () const
                    {
                        throw MyErrorCode;
                    }
                
                private:
                    ara::core::ErrorDomain::CodeType MyErrorCode;
                    const ara::core::ErrorDomain *MyErrorDomain;
                    ara::core::ErrorDomain::SupportDataType MySupportData;

            };
            // Global operator== for ErrorCode.
            // Two ErrorCode instances compare equal if the results of their Value() and Domain() functions
            // are equal. The result of SupportData() is not considered for equality.
            constexpr bool operator== (const ErrorCode &lhs, const ErrorCode &rhs)noexcept
            {
                // ".Domain" return the ErrorDomain object then the == operator in the ErrorDomain class is called to compare
                // the id of both the ErrorDomain of both lhs and rhs 
                return (  (lhs.Domain()==rhs.Domain())   &&   (lhs.Value()==rhs.Value())  );
            }
            // Global operator!= for ErrorCode.
            // Two ErrorCode instances compare equal if the results of their Value() and Domain() functions
            // are equal. The result of SupportData() is not considered for equality
            constexpr bool operator!= (const ErrorCode &lhs, const ErrorCode &rhs)noexcept
            {
                // ".Domain" return the ErrorDomain object then the != operator in the ErrorDomain class is called to compare
                // the id of both the ErrorDomain of both lhs and rhs
                return (  (lhs.Domain()!=rhs.Domain())   ||   (lhs.Value()!=rhs.Value())  );
            }
        }  
    } 

#endif
