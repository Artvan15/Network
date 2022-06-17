#include <gtest/gtest.h>
#include <memory>
#include <Uri/Uri.hpp>
#include "UriState.hpp"

/*
 * UriFixture is a class to set up initial state of
 * Uri class. This preset setup will be used in further tests
 * Setup can be made using data from UriState using GetParam() method
 */
struct UriFixture : public testing::TestWithParam<UriState>
{
    std::unique_ptr<Uri::Uri> uri;

    UriFixture()
	    : uri(std::make_unique<Uri::Uri>())
    {}
};


/*
 * Actual test, where params from UriFixture class are
 * compared to expected from UriState class 
 */
TEST_P(UriFixture, UriWithAuthority)
{
    const auto& uri_state = GetParam();

    ASSERT_TRUE(uri->ParseFromString(uri_state.GetInitialParsingString()));
    ASSERT_EQ(uri->GetScheme(), uri_state.GetFinalScheme());
    ASSERT_EQ(uri->GetHost(), uri_state.GetFinalHost());
    ASSERT_EQ(uri->GetPath(), uri_state.GetFinalPath());
}


/*
 * Generate parameters of UriState's class that will be used
 * in tests
 */
INSTANTIATE_TEST_SUITE_P(UriWithAuthority, UriFixture,
    testing::Values(
        static_cast<UriState>(
            UriState::create()
			.set_initial_parsing_string("http://www.example.com/foo/bar")
			.set_final_scheme("http")
			.set_final_host("www.example.com")
			.set_final_path(std::vector<std::string>
				{"foo",
				"bar"}))
    )
);

INSTANTIATE_TEST_SUITE_P(UriWithoutAuthority, UriFixture,
    testing::Values(
        static_cast<UriState>(
            UriState::create()
            .set_initial_parsing_string("udp:book:fantasy:Hobbyt")
            .set_final_scheme("udp")
            .set_final_path(std::vector<std::string>
						{"book",
						"fantasy",
						"Hobbyt"})
            )
	)
);

/*TODO: rename methods to uppercase
 *Builder isn't convenient, cause user needs to use manual cast
 *to UriState. Maybe it's simpler to implement just public set_functions
 *with public constructor
 *
 *
*/






