#include <gtest/gtest.h>
#include <memory>
#include <Uri/Uri.hpp>
#include "UriState.hpp"

//UriFixture is a class to set up initial state of Uri class.
struct UriFixture : public testing::Test
{
    std::unique_ptr<Uri::Uri> uri = std::make_unique<Uri::Uri>();
};

/*
 * UriParam makes set up from GetParam() which is UriState class
 * It can be used in TEST_P (test with parameters)
 */
struct UriParam : public UriFixture, public testing::WithParamInterface<UriState>
{
    UriParam()
    {
        if (!GetParam().GetInitialDelimiter().empty())
        {
            uri->SetDelimiter(GetParam().GetInitialDelimiter());
        }
    }
};


/*
 * Actual test, where params from UriFixture class are
 * compared to expected from UriState class 
 */
TEST_P(UriParam, UriTests)
{
    const auto& uri_state = GetParam();

    ASSERT_TRUE(uri->ParseFromString(uri_state.GetInitialParsingString()));
    ASSERT_EQ(uri->GetScheme(), uri_state.GetFinalScheme());
    ASSERT_EQ(uri->GetHost(), uri_state.GetFinalHost());
    ASSERT_EQ(uri->HasPort(), uri_state.GetHasPort());

    if(uri->HasPort() && uri_state.GetHasPort())
    {
        ASSERT_EQ(uri->GetPortNumber(), uri_state.GetPortNumber());
    }
    ASSERT_EQ(uri->GetPath(), uri_state.GetFinalPath());
}

TEST_F(UriFixture, UriIsNotValid)
{
    ASSERT_FALSE(uri->ParseFromString("http://google.com.ua:afv/home"));

    //TODO: add checks for invalid URI
}


/*
 * Generate parameters of UriState's class that will be used
 * in tests
 */
INSTANTIATE_TEST_SUITE_P(UriWithAuthority, UriParam,
    testing::Values(
        static_cast<UriState>(
            UriState::create()
			.SetInitialParsingString("http://www.example.com/foo/bar")
			.SetFinalScheme("http")
			.SetFinalHost("www.example.com")
			.SetFinalPath({"foo","bar"})),
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("http://www.example.com/foo/bar/")
            .SetFinalScheme("http")
            .SetFinalHost("www.example.com")
            .SetFinalPath({"foo","bar",""})),
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("http://www.example.com")
            .SetFinalScheme("http")
            .SetFinalHost("www.example.com")
            .SetFinalPath({})),
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("http://www.example.com/")
            .SetFinalScheme("http")
            .SetFinalHost("www.example.com")
            .SetFinalPath({""}))
    )
);

INSTANTIATE_TEST_SUITE_P(UriWithAuthorityWithPort, UriParam,
    testing::Values(
		static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("https://google.com.ua:8080/settings/account")
            .SetFinalScheme("https")
            .SetFinalHost("google.com.ua")
            .SetFinalPortNumber(8080)
            .SetFinalPath({"settings", "account"})
            ),
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("https://google.com.ua:8000")
            .SetFinalScheme("https")
            .SetFinalHost("google.com.ua")
            .SetFinalPortNumber(8000)
            .SetFinalPath({ })
            )
    )
);

INSTANTIATE_TEST_SUITE_P(UriWithoutAuthority, UriParam,
    testing::Values(
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("udp:book:fantasy:Hobbyt")
            .SetInitialDelimiter(":")
            .SetFinalScheme("udp")
            .SetFinalPath({"book","fantasy","Hobbyt"})
            ),
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("udp:")
            .SetFinalScheme("udp")
            .SetFinalPath({""})
            )
	)
);

INSTANTIATE_TEST_SUITE_P(UriWithoutAuthorityCustomDelimiter, UriParam,
    testing::Values(
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("dpu:film:/thriller:/silence_of_lambs")
            .SetInitialDelimiter(":/")
            .SetFinalScheme("dpu")
            .SetFinalPath({ "film", "thriller", "silence_of_lambs" })
            )
    )
);


/*
 *Builder isn't convenient, cause user needs to use manual cast
 *to UriState. Maybe it's simpler to implement just public set_functions
 *with public constructor
 *
*/






