#ifndef ARA_CORE_EXCEPTION_H_
#define ARA_CORE_EXCEPTION_H_
    #include <stdexcept>
    #include "error_code.h"
    namespace ara
    {
        namespace core
        {
            // Base type for all AUTOSAR exception types.
            class Exception: public std::exception
            {
                private:
                    ErrorCode err;
                public:
                    // Construct a new Exception object with a specific ErrorCode.
                    explicit Exception (ErrorCode err) noexcept
                    :err(err)
                    {
                        // verify we might need to consider checking the err object before saving it to make sure it is 
                        // a proper ErrorCode type
                        ;
                    }
                    // Return the explanatory string.
                    // This function overrides the virtual function std::exception::what. All guarantees about the
                    // lifetime of the returned pointer that are given for std::exception::what are preserved.
                    const char* what () const noexcept override
                    {
                        const char* Result=err.Domain().Message(err.Value());
                        return  Result;
                    }
                    const ErrorCode& Error () const noexcept
                    {
                        return this->err;
                    }
                protected:
                    Exception& operator= (Exception const &other)
                    {
                        // avoid self referencing (e.g exception_ob1=exception_ob1)
                        if(&other != this)
                        {
                            this->err=other.err;
                        }
                        return *this; // allow x=y=z
                    }
            }; 
        }
    }
#endif