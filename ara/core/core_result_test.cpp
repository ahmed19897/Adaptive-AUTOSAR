#include <gtest/gtest.h>
#include <optional>
#include "result.h"
#include "core_error_domain.h"
#include "error_code.h"
#include "error_domain.h"

using namespace ::testing;

class ResultTesting : public ::testing::Test
{
    public:
    //testing fixtures
        void SetUp()override
        {
            std::cout<<"Setup ResultTesting\n";
        }

        void TearDown()override
        {
            std::cout<<"Tear down ResultTesting\n";
        }
};

TEST_F(ResultTesting,lvalue_Constructor_value_test)
{
    const std::uint32_t ResultValue = 100;
    ara::core::Result<std::uint32_t> TestResult(ResultValue);

    EXPECT_EQ(TestResult.Value(),ResultValue);
}

TEST_F(ResultTesting,rvalue_Constructor_value_test)
{
    ara::core::Result<int> TestResult(100);
    
    EXPECT_EQ(std::move(TestResult).Value(),100);
}

TEST_F(ResultTesting,lvalue_Constructor_error_test)
{
    ara::core::CoreErrorDomain TestCoreErrorDomain;
    const ara::core::ErrorDomain::CodeType TestCodeType=10;
    const ara::core::ErrorDomain::SupportDataType TestSupportDataType=10;
    ara::core::ErrorCode TestErrorCode(TestCodeType,TestCoreErrorDomain,TestSupportDataType);
    ara::core::Result<int,ara::core::ErrorCode> TestResult(TestErrorCode);

    EXPECT_EQ(TestResult.Error(),TestErrorCode);
}

TEST_F(ResultTesting,rvalue_Constructor_error_test)
{
    ara::core::CoreErrorDomain TestCoreErrorDomain;
    const ara::core::ErrorDomain::CodeType TestCodeType=10;
    const ara::core::ErrorDomain::SupportDataType TestSupportDataType=10;
    ara::core::ErrorCode TestErrorCode(TestCodeType,TestCoreErrorDomain,TestSupportDataType);
    ara::core::Result<int,ara::core::ErrorCode> TestResult(std::move(TestErrorCode));
    
    EXPECT_EQ(std::move(TestResult).Error(),TestErrorCode);
}

TEST_F(ResultTesting,lvalue_copy_Constructor_test)
{
    const ara::core::Result TestResult(100);
    ara::core::Result CopyResult(TestResult);
    
    EXPECT_EQ(CopyResult.Value(),TestResult.Value());
}

TEST_F(ResultTesting,rvalue_copy_Constructor_test)
{
    ara::core::Result TestResult(100);
    ara::core::Result CopyResult(std::move(TestResult));

    EXPECT_EQ(CopyResult.Value(),TestResult.Value());
}

TEST_F(ResultTesting,lvalue_FromValue_test)
{
    const ara::core::Result<int>::value_type FromValueVariable{100};
    ara::core::Result<int> CopyResult(ara::core::Result<int>::FromValue(FromValueVariable));

    EXPECT_EQ(CopyResult.Value(),100);
}

TEST_F(ResultTesting,rvalue_FromValue_test)
{
    ara::core::Result<int> CopyResult(ara::core::Result<int>::FromValue(100));

    EXPECT_EQ(CopyResult.Value(),100);
}

