#ifndef ARA_CORE_RESULT_H_
#define ARA_CORE_RESULT_H_
    #include <optional>
    #include "error_domain.h"
    #include "error_code.h"
    namespace ara
    {
        namespace core
        {
            // This class is a type that contains either a value or an error.
            template <typename T, typename E = ErrorCode>
            class Result final 
            {
                public:
                    // Type alias for the type T of values .
                    using value_type = T;
                    // Type alias for the type E of errors .
                    using error_type = E;
                    // Construct a new Result from the specified value (given as lvalue).
                    Result (const T &t)
                    :Result_value(t)
                    {
                        ;
                    }
                    // Construct a new Result from the specified value (given as rvalue).
                    Result (T &&t)
                    :Result_value(std::move(t))
                    {
                        ;
                    }
                    // Construct a new Result from the specified error (given as lvalue).
                    explicit Result (const E &e)
                    :Result_error(e)
                    {
                        ;
                    }
                    // Construct a new Result from the specified error (given as rvalue).
                    explicit Result (E &&e)
                    :Result_error(std::move(e))
                    {
                        ;
                    }
                    // Copy-construct a new Result from another instance.
                    Result (const Result &other)
                    {
                        if(other.Result_value.has_value())
                        {
                            this->Result_value=other.Result_value;
                        }
                        else
                        {
                            //
                        }
                        if(other.Result_error.has_value())
                        {
                            this->Result_error=other.Result_error;
                        }
                        else
                        {
                            //
                        }  
                    }
                    // Move-construct a new Result from another instance.
                    Result (Result &&other) noexcept(std::is_nothrow_move_constructible< T>::value &&std::is_nothrow_move_constructible< E >::value)
                    {
                        if(other.Result_value.has_value())
                        {
                            this->Result_value=std::move(other.Result_value);
                        }
                        else
                        {
                            //
                        }
                        if(other.Result_error.has_value())
                        {
                            this->Result_error=std::move(other.Result_error);
                        }
                        else
                        {
                            //
                        }
                    }
                    // Destructor.
                    // This destructor is trivial if std::is_trivially_destructible<T>::value && std::is_trivially_destructible<E>::value is true.
                    ~Result ()
                    {
                        ;
                    }
                    // Build a new Result from the specified value (given as lvalue).
                    static Result FromValue (const T &t)
                    {
                        return  Result(t);
                    }
                    // Build a new Result from the specified value (given as rvalue).
                    static Result FromValue (T &&t)
                    {
                        return Result(std::move(t));
                    }
                    // Build a new Result from a value that is constructed in-place from the given arguments.
                    // This function shall not participate in overload resolution unless: std::is_constructible<T,
                    // Args&&...>::value is true, and the first type of the expanded parameter pack is not T, and the
                    // first type of the expanded parameter pack is not a specialization of Result
                    template <typename... Args>
                    static Result FromValue (Args &&...args)
                    {
                        //page 56 of 191;
                        //what is this ?!
                    }
                    // Build a new Result from the specified error (given as lvalue).
                    static Result FromError (const E &e)
                    {
                        return Result(e);
                    }
                    // Build a new Result from the specified error (given as rvalue).
                    static Result FromError (E &&e)
                    {
                        return Result(std::move(e));
                    }
                    // Build a new Result from an error that is constructed in-place from the given arguments.
                    // This function shall not participate in overload resolution unless: std::is_constructible<E,
                    // Args&&...>::value is true, and the first type of the expanded parameter pack is not E, and the
                    // first type of the expanded parameter pack is not a specialization of Result
                    template <typename... Args>
                    static Result FromError (Args &&...args)
                    {
                        //
                    }
                    // Copy-assign another Result to this instance.
                    Result& operator= (const Result &other)
                    {
                        if(other.Result_value)
                        {
                            this->FromValue=other.FromValue;
                        }
                        else
                        {
                            //
                        }
                        if(other.Result_error)
                        {
                            this->FromError=other.FromError;
                        }
                        else
                        {
                            //
                        }
                        return this;
                    }
                    // Move-assign another Result to this instance.
                    Result& operator= (Result &&other) noexcept(std::is_nothrow_move_constructible< T >::value &&std::is_nothrow_move_assignable< T>::value &&std::is_nothrow_move_constructible< E >::value &&std::is_nothrow_move_assignable< E >::value)
                    {
                        if(other.Result_value)
                        {
                            this->FromValue(std::move(other.FromValue));
                        }
                        else
                        {
                            //
                        }
                        if(other.Result_error)
                        {
                            this->FromError(std::move(other.FromError));
                        }
                        else
                        {
                            //
                        }
                        return this;
                    }
                    // Put a new value into this instance, constructed in-place from the given arguments.
                    template <typename... Args>
                    void EmplaceValue (Args &&...args)
                    {
                        //
                    }
                    // Put a new error into this instance, constructed in-place from the given arguments.
                    template <typename... Args>
                    void EmplaceError (Args &&...args)
                    {
                        //
                    }
                    // Exchange the contents of this instance with those of other.
                    void Swap (Result &other) noexcept(std::is_nothrow_move_constructible<T >::value &&std::is_nothrow_move_assignable< T >::value &&std::is_nothrow_move_constructible< E >::value &&std::is_nothrow_move_assignable< E >::value)
                    {
                        Result temp(other.Result_value,other.Result_error);

                        other.Result_value=this->Result_value;
                        other.Result_error=this->Result_error;

                        this->Result_value=temp.Result_value;
                        this->Result_error=temp.Result_error;
                    }
                    // Check whether *this contains a value.
                    bool HasValue () const noexcept
                    {
                        return this->FromValue!=0;
                    }
                    // Check whether *this contains a value.
                    explicit operator bool () const noexcept
                    {
                        return this->FromValue!=0;
                    }
                    // Access the contained value.
                    // This function’s behavior is undefined if *this does not contain a value.
                    const T& operator* () const &
                    {
                        return this->Result_value;
                    }
                    // Access the contained value.
                    // This function’s behavior is undefined if *this does not contain a value.
                    T&& operator* () &&
                    {
                        return std::move(Result_value);
                    }
                    // Access the contained value.
                    // This function’s behavior is undefined if *this does not contain a value.
                    const T* operator-> () const
                    {
                        return &this->Result_value;
                    }
                    // Access the contained value.
                    // The behavior of this function is undefined if *this does not contain a value.
                    const T& Value () const &
                    {
                        return Result_value.value();
                    }
                    // Access the contained value.
                    // The behavior of this function is undefined if *this does not contain a value.
                    T&& Value () &&
                    {
                        return std::move(Result_value.value());
                    }
                    // Access the contained error.
                    // The behavior of this function is undefined if *this does not contain an error.
                    const E& Error () const &
                    {
                        return Result_error.value();
                    }
                    // Access the contained error.
                    // The behavior of this function is undefined if *this does not contain an error.
                    E&& Error () &&
                    {
                        return std::move(Result_error.value());
                    }
                    // Return the contained value as an Optional.
                    std::optional<T> Ok () const &
                    {
                        if(this->Result_value)
                        {
                            return this->Result_value;
                        }
                        else
                            return {};
                    }
                    // Return the contained value as an Optional.
                    std::optional<T> Ok () &&
                    {
                        if(this->Result_value)
                        {
                            return this->Result_value;
                        }
                        else
                            return {};
                    }
                    // Return the contained error as an Optional.
                    std::optional<E> Err () const &
                    {
                        if(this->Result_error)
                        {
                            return this->Result_error;
                        }
                        else
                            return {};  
                    }
                    // Return the contained error as an Optional.
                    std::optional<E> Err () &&
                    {
                        if(this->Result_error)
                        {
                            return this->Result_error;
                        }
                        else
                            return {};  
                    }
                    // Return the contained value or the given default value.
                    // If *this contains a value, it is returned. Otherwise, the specified default value is returned, static_
                    // cast’d to T.
                    template <typename U>
                    T ValueOr (U &&defaultValue) const &
                    {
                        if(this->Result_value)
                        {
                            return this->Result_value;
                        }
                        else
                        {
                            return (static_cast<T>(std::move(defaultValue)));
                        }
                    }
                    // Return the contained value or the given default value.
                    // If *this contains a value, it is returned. Otherwise, the specified default value is returned, static_
                    // cast’d to T.
                    template <typename U>
                    T ValueOr (U &&defaultValue) &&
                    {
                        if(this->Result_value)
                        {
                            return this->Result_value;
                        }
                        else
                        {
                            return (static_cast<T>(std::move(defaultValue)));
                        }
                    }
                    // Return the contained error or the given default error.
                    // If *this contains an error, it is returned. Otherwise, the specified default error is returned, static_
                    // cast’d to E.
                    template <typename G>
                    E ErrorOr (G &&defaultError) const &
                    {
                        if(this->Result_error)
                        {
                            return this->Result_error;
                        }
                        else
                        {
                            return (static_cast<T>(std::move(defaultError)));
                        }  
                    }
                    // Return the contained error or the given default error.
                    // If *this contains an error, it is std::move’d into the return value. Otherwise, the specified default
                    // error is returned, static_cast’d to E.
                    template <typename G>
                    E ErrorOr (G &&defaultError) &&
                    {
                        if(this->Result_error)
                        {
                            return this->Result_error;
                        }
                        else
                        {
                            return (static_cast<T>(std::move(defaultError)));
                        } 
                    }
                    // Return whether this instance contains the given error.
                    // This call compares the argument error, static_cast’d to E, with the return value from Error().
                    template <typename G>
                    bool CheckError (G &&error) const
                    {
                        return ( this->Error()==static_cast<E>(error) );
                    }
                    // Return the contained value or throw an exception.
                    // This function does not participate in overload resolution when the compiler toolchain does not
                    // support C++ exceptions.
                    const T& ValueOrThrow () const &noexcept(false)
                    {
                        //
                    }
                    // Return the contained value or throw an exception.
                    // This function does not participate in overload resolution when the compiler toolchain does not
                    // support C++ exceptions.
                    T&& ValueOrThrow () &&noexcept(false)
                    {

                    }
                    // Return the contained value or return the result of a function call.
                    // If *this contains a value, it is returned. Otherwise, the specified callable is invoked and its return
                    // value which is to be compatible to type T is returned from this function.
                    // The Callable is expected to be compatible to this interface: T f(const E&);
                    template <typename F>
                    T Resolve (F &&f) const
                    {

                    }
                    // Apply the given Callable to the value of this instance, and return a new Result with the result of
                    // the call.
                    // The Callable is expected to be compatible to one of these two interfaces: Result<XXX, E>
                    // f(const T&); XXX f(const T&); meaning that the Callable either returns a Result<XXX> or a XXX
                    // directly, where XXX can be any type that is suitable for use by class Result.
                    // The return type of this function is decltype(f(Value())) for a template argument F that returns a
                    // Result type, and it is Result<decltype(f(Value())), E> for a template argument F that does not
                    // return a Result type.
                    // If this instance does not contain a value, a new Result<XXX, E> is still created and returned,
                    // with the original error contents of this instance being copied into the new instance.
                    // template <typename F>
                    // auto Bind (F &&f) const -> <see below>
                    // {

                    // }
                private:
                    std::optional<T> Result_value;
                    std::optional<E> Result_error;
            };
        }
    }
#endif
