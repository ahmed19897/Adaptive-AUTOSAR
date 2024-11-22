#include "error_domain.h"
#include "core_error_domain.h"
#include "error_code.h"
#include <stdexcept>
#include <gtest/gtest.h>
#include <iostream>


using namespace ::testing;


class ErrorCodeTesting : public ::testing::Test
{
    public:
    //testing fixtures
        void SetUp()override
        {
            std::cout<<"Setup ErrorCodeTesting\n";
        }

        void TearDown()override
        {
            std::cout<<"Tear down ErrorCodeTesting\n";
        }

};

TEST_F(ErrorCodeTesting,Value_test)
{
    ara::core::CoreErrorDomain TestCoreErrorDomain;
    const ara::core::ErrorDomain::CodeType TestCodeType=10;
    const ara::core::ErrorDomain::SupportDataType TestSupportDataType=10;
    ara::core::ErrorCode TestErrorCode(TestCodeType,TestCoreErrorDomain,TestSupportDataType);

    EXPECT_EQ(TestErrorCode.Value(),TestCodeType);
}

TEST_F(ErrorCodeTesting,Domain_test)
{
    ara::core::CoreErrorDomain TestCoreErrorDomain;
    const ara::core::ErrorDomain::CodeType TestCodeType=10;
    const ara::core::ErrorDomain::SupportDataType TestSupportDataType=10;
    ara::core::ErrorCode TestErrorCode(TestCodeType,TestCoreErrorDomain,TestSupportDataType);

    EXPECT_EQ(TestErrorCode.Domain().Id(),TestCoreErrorDomain.Id());
}

TEST_F(ErrorCodeTesting,SupportData_test)
{
    ara::core::CoreErrorDomain TestCoreErrorDomain;
    const ara::core::ErrorDomain::CodeType TestCodeType=10;
    const ara::core::ErrorDomain::SupportDataType TestSupportDataType=10;
    ara::core::ErrorCode TestErrorCode(TestCodeType,TestCoreErrorDomain,TestSupportDataType);
    
    EXPECT_EQ(TestErrorCode.SupportData(),TestSupportDataType);
}

TEST_F(ErrorCodeTesting,Message_test)
{
    ara::core::CoreErrorDomain TestCoreErrorDomain;
    ara::core::ErrorDomain::CodeType TestCodeType=(ara::core::ErrorDomain::CodeType) ara::core::CoreErrc::kInvalidMetaModelShortname;
    const ara::core::ErrorDomain::SupportDataType TestSupportDataType=10;
    ara::core::ErrorCode TestErrorCode(TestCodeType,TestCoreErrorDomain,TestSupportDataType);
    std::string expectedvalue="kInvalidMetaModelShortname\0";

    //function call
    EXPECT_EQ(TestErrorCode.Message(),expectedvalue);
}

TEST_F(ErrorCodeTesting,ThrowAsException_test)
{
    ara::core::CoreErrorDomain TestCoreErrorDomain;
    const ara::core::ErrorDomain::CodeType TestCodeType=10;
    const ara::core::ErrorDomain::SupportDataType TestSupportDataType=10;
    ara::core::ErrorCode TestErrorCode(TestCodeType,TestCoreErrorDomain,TestSupportDataType);

    //function call
    EXPECT_ANY_THROW(TestErrorCode.ThrowAsException());
}

TEST_F(ErrorCodeTesting,operator_equal_test)
{
    ara::core::CoreErrorDomain TestCoreErrorDomain;
    ara::core::CoreErrorDomain TestCoreErrorDomain2;
    const ara::core::ErrorDomain::CodeType TestCodeType=22;
    const ara::core::ErrorDomain::SupportDataType TestSupportDataType=10;

    ara::core::ErrorCode TestErrorCode(TestCodeType,TestCoreErrorDomain,TestSupportDataType);
    ara::core::ErrorCode TestErrorCode2(TestCodeType,TestCoreErrorDomain2,TestSupportDataType);
    std::cout<<(TestErrorCode==TestErrorCode2)<<std::endl;
    //function call
    EXPECT_EQ(TestErrorCode==TestErrorCode2,true);
}

TEST_F(ErrorCodeTesting,operator_notequal_test)
{
    ara::core::CoreErrorDomain TestCoreErrorDomain;
    const ara::core::ErrorDomain::CodeType TestCodeType=22;
    const ara::core::ErrorDomain::SupportDataType TestSupportDataType=10;

    ara::core::ErrorCode TestErrorCode(TestCodeType,TestCoreErrorDomain,TestSupportDataType);
    ara::core::ErrorCode TestErrorCode2(TestCodeType,TestCoreErrorDomain,TestSupportDataType);

    //function call
    EXPECT_EQ(TestErrorCode!=TestErrorCode2,false);
}