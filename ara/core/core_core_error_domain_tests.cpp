#include "error_domain.h"
#include "core_error_domain.h"
#include "error_code.h"
#include <stdexcept>
#include <gtest/gtest.h>


using namespace ::testing;


class CoreErrorDomainTesting : public ::testing::Test
{
    public:
    //testing fixtures
        void SetUp()override
        {
            std::cout<<"Setup CoreErrorDomainTesting\n";
        }

        void TearDown()override
        {
            std::cout<<"Tear down CoreErrorDomainTesting\n";
        }

};

TEST_F(CoreErrorDomainTesting,print_test)
{
    ara::core::CoreErrorDomain TestCoreErrorDomain;

    //testing the first value
    ara::core::CoreErrc TestCoreErrorType =  ara::core::CoreErrc::kInvalidArgument ;
    std::string expectedvalue="kInvalidArgument\0";
    //function call
    std::string output=TestCoreErrorDomain.Message((ara::core::ErrorDomain::CodeType) TestCoreErrorType);
    //compare 
    EXPECT_EQ(output,expectedvalue);

    // testing the second value
    TestCoreErrorType =  ara::core::CoreErrc::kInvalidMetaModelPath ;
    expectedvalue="kInvalidMetaModelPath\0";
    // function call
    output=TestCoreErrorDomain.Message((ara::core::ErrorDomain::CodeType) TestCoreErrorType);
    // compare 
    EXPECT_EQ(output,expectedvalue);

    // testing the third value
    TestCoreErrorType =  ara::core::CoreErrc::kInvalidMetaModelShortname ;
    expectedvalue="kInvalidMetaModelShortname\0";
    // function call
    output=TestCoreErrorDomain.Message((ara::core::ErrorDomain::CodeType) TestCoreErrorType);
    // compare 
    EXPECT_EQ(output,expectedvalue);
}

TEST_F(CoreErrorDomainTesting,Name_test)
{
    ara::core::CoreErrorDomain TestCoreErrorDomain;

    std::string expectedvalue="Core";
    //function call
    std::string output=TestCoreErrorDomain.Name();
    //compare 
    EXPECT_EQ(output,expectedvalue);
}

TEST_F(CoreErrorDomainTesting,ThrowAsException_test)
{
    ara::core::CoreErrorDomain TestCoreErrorDomain;
    const ara::core::ErrorDomain::CodeType TestCodeType=10;
    const ara::core::ErrorDomain::SupportDataType TestSupportDataType=10;
    ara::core::ErrorCode TestErrorCode(TestCodeType,TestSupportDataType);

    //function call
    EXPECT_ANY_THROW(TestCoreErrorDomain.ThrowAsException(TestErrorCode));
}

TEST_F(CoreErrorDomainTesting,GetCoreErrorDomain_test)
{
    const ara::core::ErrorDomain& TestCoreErrorDomain=ara::core::GetCoreErrorDomain();
    //performing some function code to make sure our reference points to the global CoreErrorDomain class
    std::string expectedvalue="Core";

    //function call
    EXPECT_EQ(expectedvalue,TestCoreErrorDomain.Name());
}

TEST_F(CoreErrorDomainTesting,MakeErrorCode_test)
{
    const ara::core::ErrorDomain::SupportDataType TestSupportingDataType(10);
    const ara::core::CoreErrc TestCoreErrcDataType(ara::core::CoreErrc::kInvalidArgument);
    ara::core::ErrorCode TestErrorCode=ara::core::MakeErrorCode(TestCoreErrcDataType,TestSupportingDataType);

    //function call
    EXPECT_EQ( ara::core::ErrorDomain::CodeType(TestCoreErrcDataType),TestErrorCode.Value());
    EXPECT_EQ(TestSupportingDataType,TestErrorCode.SupportData());
}







class CoreExceptionTesting : public ::testing::Test
{
    public:
    //testing fixtures
        void SetUp()override
        {
            std::cout<<"Setup CoreExceptionTesting\n";
        }

        void TearDown()override
        {
            std::cout<<"Tear down CoreExceptionTesting\n";
        }

};

TEST_F(CoreExceptionTesting,What_test)
{
    ara::core::CoreErrorDomain TestCoreErrorDomain;
    const ara::core::ErrorDomain::SupportDataType TestSupportingDataType(10);
    const ara::core::ErrorDomain::CodeType TestCodeTypeDataType(22);
    const ara::core::ErrorCode TestErrorCode(TestCodeTypeDataType,TestCoreErrorDomain,TestSupportingDataType);
    const ara::core::CoreException TestCoreException(TestErrorCode);
    const char* output="kInvalidArgument\0";

    //function call
    EXPECT_EQ( output,TestCoreException.what());
}

TEST_F(CoreExceptionTesting,Error_test)
{
    const ara::core::ErrorDomain::SupportDataType TestSupportingDataType(10);
    const ara::core::ErrorDomain::CodeType TestCodeTypeDataType(11);
    const ara::core::ErrorCode TestErrorCode(TestCodeTypeDataType,TestSupportingDataType);
    
    const ara::core::CoreException TestCoreException(TestErrorCode);
    const ara::core::ErrorCode& TestRefErrorCode=TestCoreException.Error();
    //function call
    EXPECT_EQ( TestErrorCode.Value(),TestRefErrorCode.Value());
    EXPECT_EQ( TestErrorCode.SupportData(),TestRefErrorCode.SupportData());
}

TEST_F(CoreExceptionTesting,operator_test)
{
    const ara::core::ErrorDomain::SupportDataType TestSupportingDataType(10);
    const ara::core::ErrorDomain::CodeType TestCodeTypeDataType(11);
    const ara::core::ErrorCode TestErrorCode(TestCodeTypeDataType,TestSupportingDataType);
    
    const ara::core::CoreException TestCoreException(TestErrorCode);
    const ara::core::CoreException TestCoreException2=TestCoreException;

    const ara::core::ErrorCode& TestRefErrorCode=TestCoreException.Error();
    const ara::core::ErrorCode& TestRefErrorCode2=TestCoreException2.Error();
    //function call
    EXPECT_EQ( TestRefErrorCode.Value(),TestRefErrorCode2.Value());
}