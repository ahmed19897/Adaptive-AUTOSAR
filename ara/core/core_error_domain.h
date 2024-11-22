// ErrorDomain include guard following SWS_CORE_90001]
#ifndef ARA_CORE_CORE_ERROR_DOMAIN_H_
#define ARA_CORE_CORE_ERROR_DOMAIN_H_
    #include "error_domain.h" 
    #include "error_code.h"
    #include "Exception.h"
    // forward decleratio  of Exception , ErrorCode and CoreException as a stub to be able to build the type
    class ErrorCode;
    class CoreException;
    namespace ara
    {
        namespace core
        {
            // An enumeration that defines all errors of the CORE Functional Cluster
            enum class CoreErrc : ErrorDomain::CodeType
            {
                // an invalid argument was passed to a function
                kInvalidArgument= 22,
                // given string is not a valid model element shortname
                kInvalidMetaModelShortname= 137,
                // missing or invalid path to model element    
                kInvalidMetaModelPath= 138
            };
            // An error domain for errors originating from the CORE Functional Cluster
            class CoreErrorDomain final : public ErrorDomain
            {
                private:   
                public:
                    // Alias for the error code value enumeration
                    using Errc = CoreErrc;
                    // Alias for the exception base class
                    using Exception = CoreException;

                    // Default constructor
                    constexpr CoreErrorDomain () noexcept
                    :ErrorDomain(0x8000000000000014)
                    {
                        ;
                    }
                    // Return the "shortname" ApApplicationErrorDomain.SN of this error domain.
                    const char* Name () const noexcept override
                    {
                        return "Core";
                    }
                    // Translate an error code value into a text message
                    const char* Message (ErrorDomain::CodeType errorCode) const noexcept override
                    {
                        const char *Result=" ";
                        switch (errorCode)
                        {
                            case (ErrorDomain::CodeType) ara::core::CoreErrc::kInvalidArgument :
                                Result="kInvalidArgument\0";
                            break;
                            case (ErrorDomain::CodeType) ara::core::CoreErrc::kInvalidMetaModelPath :
                                Result="kInvalidMetaModelPath\0";
                            break;
                            case (ErrorDomain::CodeType) ara::core::CoreErrc::kInvalidMetaModelShortname :
                                Result="kInvalidMetaModelShortname\0";
                            break;
                            default:
                                Result="Unknown Error Code in the Core Domain!\0";
                            break;
                        }
                        return Result;
                    }
                    // throw the exception type corresponding to the given ErrorCode
                    void ThrowAsException (const ErrorCode &errorCode) const noexcept(false)
                    {
                        throw (errorCode.Value());
                    }
            };
            //global instance of the CoreErrorDomain class 
            const static CoreErrorDomain GlobalCoreErrorDomain;
            // Return a reference to the global CoreErrorDomain.
            constexpr const ErrorDomain& GetCoreErrorDomain () noexcept
            {
               return GlobalCoreErrorDomain;
            }
            // Create a new ErrorCode within CoreErrorDomain.
            // This function is used internally by constructors of ErrorCode. It is usually not used directly by
            // users.
            constexpr ErrorCode MakeErrorCode (CoreErrc code, ErrorDomain::SupportDataType data) noexcept
            {
                ErrorCode NewErrorCode(code,data);
                return NewErrorCode;       
            }
            // Exception type thrown for CORE errors
            class CoreException : public Exception
            {
                private:
                public:
                    // Construct a new CoreException from an ErrorCode
                    explicit CoreException (ErrorCode err) noexcept
                    :Exception(err)
                    {
                        ;
                    }
            };
        }
    }
#endif
