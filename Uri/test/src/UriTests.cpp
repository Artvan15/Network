#include <gtest/gtest.h>
#include <memory>
#include <Uri/Uri.hpp>
#include "UriState.hpp"
#include "ParserException.hpp"


//UriFixture is a class to set up initial state of Uri class.
struct UriFixture : public testing::Test
{
    std::unique_ptr<Uri::Uri> uri = std::make_unique<Uri::Uri>();
};


TEST_F(UriFixture, PortIsNotValid)
{
    const std::vector<std::string> parsing_strings{
       "http://google.com.ua:afv/home",
       "http://google.com.ua:8080ac/home",
       "http://google.com.ua:65536/home",
       "http://google.com.ua:-5421/home"
    };

    for(const auto& parsing_string : parsing_strings)
    {
        ASSERT_THROW(uri->ParseFromString(parsing_string), ParserPortException);
    }

    //TODO: add checks for invalid URI
}

TEST_F(UriFixture, SchemeIllegalCharacters)
{
    const std::vector<std::string> parsing_strings{
        "://www.example.com",
        "2://www.example.com",
        "+://www.example.com",
        "@://www.example.com",
        ".://www.example.com",
        "h@://www.example.com"
    };

    for(const auto& parsing_string : parsing_strings)
    {
        ASSERT_THROW(uri->ParseFromString(parsing_string), ParserSchemeException);
    }
}


TEST_F(UriFixture, SchemeBarelyLegal)
{
	struct TestVector
	{
        std::string uriString;
        std::string scheme;
	};

    const std::vector<TestVector> test_vectors{
        {"h://www.olx.ua", "h"},
        {"x+://www.olx.ua", "x+"},
        {"y-://www.prom.ua", "y-"},
        {"z.://www.youtube.com", "z."},
        {"aa://spotify.com", "aa"},
        {"a0://github.com", "a0"}
    };

    for(const auto& vector : test_vectors)
    {
        ASSERT_NO_THROW(uri->ParseFromString(vector.uriString));
        ASSERT_EQ(uri->GetScheme(), vector.scheme);
    }
}


TEST_F(UriFixture, UserInfoIllegalCharacters)
{
    const std::vector<std::string> parsing_strings{
        //invalid hex code cast to char
        "//%X@www.google.com",

        //invalid chars in user_info
        "//{@google.com",
        "//fa#@google.com",
        "//]@google.com"
    };

    for (const auto& parsing_string : parsing_strings)
    {
        ASSERT_THROW(uri->ParseFromString(parsing_string), ParserUserInfoException) << "Parsing string: " << parsing_string;
    }
}

TEST_F(UriFixture, UserInfoBarelyLegal)
{
	struct TestVector
	{
        std::string uri_string;
        std::string user_info;
	};

    const std::vector<TestVector> test_vectors{
        {"//joe%26%41@djini.com.ua", "joe&A"},
        {"//%41@djini.com.ua", "A"},
        {"//@djini.com.ua", ""},
        {"//!@djini.com.ua", "!"},
        {"//'@djini.com.ua", "'"},
        {"//(@djini.com.ua", "("},
		{"//;@djini.com.ua", ";"},
		{"//:@djini.com.ua", ":"}
    };

    for(const auto& test_vector : test_vectors)
    {
        ASSERT_NO_THROW(uri->ParseFromString(test_vector.uri_string)) << test_vector.uri_string;
        ASSERT_EQ(uri->GetUserInfo(), test_vector.user_info);
    }
}

TEST_F(UriFixture, HostIllegalCharacters)
{
    const std::vector<std::string> test_vectors
    {
        //invalid char '@' in host
        "//@www@example.com/",

        //invalid cast from hex code to char
        "//dou.com%-.ua",

        //digit after 'v' isn't hex
        "//[vX.:]/",

        //no '.' in IPvFuture
        "//[vA45]/",

        //no '['
        "//[vAF.56:8080",

        //nothing after '.'
        "//[vA0.]/"
    };

    for(const auto& test_vector : test_vectors)
    {
        ASSERT_THROW(uri->ParseFromString(test_vector), ParserHostException) << 
            "Host: " << uri->GetHost();
    }
}

TEST_F(UriFixture, HostBarelyLegal)
{
    struct TestVector
    {
        std::string uri_string;
        std::string host;
    };

    const std::vector<TestVector> test_vectors{
        {"//olx%26%41", "olx&A"},
        {"///", ""},
        {"//!", "!"},
        {"//'", "'"},
        {"//(", "("},
        {"//;", ";"},
        {"//1.2.3.4", "1.2.3.4"},
        {"//[v7.:]/", "[v7.:]"}
    };

    for (const auto& test_vector : test_vectors)
    {
        ASSERT_NO_THROW(uri->ParseFromString(test_vector.uri_string)) << test_vector.uri_string;
        ASSERT_EQ(uri->GetHost(), test_vector.host);
    }
}

TEST_F(UriFixture, PathIllegalCharacters)
{
    const std::vector<std::string> test_strings
    {
        "http://www.google.com/foo[bar",
        "http://google/[bar",
        "http://google/bar}",
        "http://google/[",
        "bar/foo}",
        "/bar/[",
        "/bar]/foo",
        "[/bar",
        "bar{/",
        "/[",
        "http://www.google.com/foo bar"
    };
    for(const auto& test_string : test_strings)
    {
        ASSERT_THROW(uri->ParseFromString(test_string), ParserPathException);
    }
}

TEST_F(UriFixture, PathBarelyLegal)
{
	struct TestVector
	{
        std::string uri_string;
        std::vector<std::string> path;
	};

    const std::vector<TestVector> test_vectors
    {
        {"/:/foo", {"", ":", "foo"}},
        {"bob@/foo", {"bob@", "foo"}},
        {"hello!", {"hello!"}},
        {"urn:hello,%20w%6Frld!", {"hello, world!"}},
        {"//example.com/foo/(bar)/", {"", "foo", "(bar)", ""}}
    };

    for(const auto& test_vector : test_vectors)
    {
        ASSERT_NO_THROW(uri->ParseFromString(test_vector.uri_string)) <<
            "Parsing string: " << test_vector.uri_string;
        ASSERT_EQ(uri->GetPath(), test_vector.path);
    } 
}

TEST_F(UriFixture, QueryIllegalCharacters)
{
    const std::vector<std::string> test_strings
    {
        "http://www.google.com?foo[bar",
        "http://google/?[bar",
        "http://google?bar}",
        "http://google/?[",
        "/bar/foo?}",
        "/bar/?[",
        "/bar?]/foo",
        "/?[",
        "http://www.google.com?foo bar"
    };
    for (const auto& test_string : test_strings)
    {
        ASSERT_THROW(uri->ParseFromString(test_string), ParserQueryException) << test_string;
    }
}

TEST_F(UriFixture, QueryBarelyLegal)
{
    struct TestVector
    {
        std::string uri_string;
        std::string query;
    };

    const std::vector<TestVector> test_vectors
    {
        {"/?:/foo", ":/foo"},
        {"/?bob@/foo", "bob@/foo"},
        {"/?hello!", "hello!"},
        {"urn:?hello,%20w%6Frld!", "hello, world!"},
        {"//example.com/foo?(bar)/", "(bar)/"},
        {"//example.com/foo?bar?/", "bar?/"}

    };

    for (const auto& test_vector : test_vectors)
    {
        ASSERT_NO_THROW(uri->ParseFromString(test_vector.uri_string)) <<
            "Parsing string: " << test_vector.uri_string;
        ASSERT_EQ(uri->GetQuery(), test_vector.query);
    }
}


TEST_F(UriFixture, FragmentIllegalCharacters)
{
    const std::vector<std::string> test_strings
    {
        "http://www.google.com#foo[bar",
        "http://google/#[bar",
        "http://google#bar}",
        "http://google/#[",
        "/bar/foo#}",
        "/bar/#[",
        "/bar#]/foo",
        "/#[",
        "http://www.google.com#foo bar"
    };
    for (const auto& test_string : test_strings)
    {
        ASSERT_THROW(uri->ParseFromString(test_string), ParserFragmentException) << test_string;
    }
}

TEST_F(UriFixture, FragmentBarelyLegal)
{
    struct TestVector
    {
        std::string uri_string;
        std::string fragment;
    };

    const std::vector<TestVector> test_vectors
    {
        {"/#:/foo", ":/foo"},
        {"/#bob@/foo", "bob@/foo"},
        {"/#hello!", "hello!"},
        {"urn:#hello,%20w%6Frld!", "hello, world!"},
        {"//example.com/foo#(bar)/", "(bar)/"},
        {"//example.com/foo#bar?/", "bar?/"}

    };

    for (const auto& test_vector : test_vectors)
    {
        ASSERT_NO_THROW(uri->ParseFromString(test_vector.uri_string)) <<
            "Parsing string: " << test_vector.uri_string;
        ASSERT_EQ(uri->GetFragment(), test_vector.fragment);
    }
}



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
    ASSERT_EQ(uri->GetUserInfo(), uri_state.GetFinalUserInfo());
    ASSERT_EQ(uri->GetHost(), uri_state.GetFinalHost());
    ASSERT_EQ(uri->HasPort(), uri_state.GetHasPort());

    if (uri->HasPort() && uri_state.GetHasPort())
    {
        ASSERT_EQ(uri->GetPortNumber(), uri_state.GetPortNumber());
    }
    ASSERT_EQ(uri->GetPath(), uri_state.GetFinalPath());
    ASSERT_EQ(uri->IsRelativeReference(), uri_state.IsRelativeReference());
    ASSERT_EQ(uri->HasRelativePath(), uri_state.HasRelativePath());
    ASSERT_EQ(uri->GetQuery(), uri_state.GetFinalQuery());
    ASSERT_EQ(uri->GetFragment(), uri_state.GetFinalFragment());
}


/*
 * Generate parameters of UriState's class that will be used
 * in tests
 */
INSTANTIATE_TEST_SUITE_P(UriWithAuthorityAndOrQueryFragment, UriParam,
    testing::Values(
        static_cast<UriState>(
            UriState::create()
			.SetInitialParsingString("http://www.google.com/foo/bar")
			.SetFinalScheme("http")
			.SetFinalHost("www.google.com")
			.SetFinalPath({"", "foo", "bar"})),
        //path ends with a '/' and query starts
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("http://www.example.com/foo/bar/?query")
            .SetFinalScheme("http")
            .SetFinalHost("www.example.com")
            .SetFinalPath({"", "foo", "bar", ""})
            .SetFinalQuery("query")),
        //fragment goes just after the host, without port, path, query
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("http://www.example.com#fragment")
            .SetFinalScheme("http")
            .SetFinalHost("www.example.com")
            .SetHasRelativePath(true)
            .SetFinalFragment("fragment")),
        // '?' mark is in query part
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("http://www.example.com/?query?earth#fragment")
            .SetFinalScheme("http")
            .SetFinalHost("www.example.com")
            .SetFinalPath({""})
            .SetFinalQuery("query?earth")
            .SetFinalFragment("fragment")),
        //query and fragment are empty
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("http://www.prom.org/?")
            .SetFinalScheme("http")
            .SetFinalHost("www.prom.org")
            .SetFinalPath({ "" }))
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
            .SetFinalPath({"", "settings", "account"})
            ),
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("https://google.com.ua:8000")
            .SetFinalScheme("https")
            .SetFinalHost("google.com.ua")
            .SetFinalPortNumber(8000)
            .SetFinalPath({ })
            .SetHasRelativePath(true)
            ),
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("https://google.com.ua:8080/settings/account?query")
            .SetFinalScheme("https")
            .SetFinalHost("google.com.ua")
            .SetFinalPortNumber(8080)
            .SetFinalPath({ "", "settings", "account" })
            .SetFinalQuery("query")
            ),
        static_cast<UriState>(
            //without path, fragment goes after port
            UriState::create()
            .SetInitialParsingString("https://google.com.ua:8080#fragment")
            .SetFinalScheme("https")
            .SetFinalHost("google.com.ua")
            .SetFinalPortNumber(8080)
            .SetHasRelativePath(true)
            .SetFinalFragment("fragment")
            ),
        static_cast<UriState>(
            //query and fragment go after port
            UriState::create()
            .SetInitialParsingString("https://google.com.ua:8080?query#fragment")
            .SetFinalScheme("https")
            .SetFinalHost("google.com.ua")
            .SetFinalPortNumber(8080)
            .SetHasRelativePath(true)
            .SetFinalQuery("query")
            .SetFinalFragment("fragment")
            )
    )
);

INSTANTIATE_TEST_SUITE_P(UriWithoutSchemeWithAuthorityWithUserInfo, UriParam,
    testing::Values(
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("//joe@google.com.ua:8080#fragment")
            .SetFinalUserInfo("joe")
            .SetFinalHost("google.com.ua")
            .SetFinalPortNumber(8080)
            .SetHasRelativePath(true)
            .SetFinalFragment("fragment")
            ),
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("//joe:123@wikipedia.com")
            .SetFinalUserInfo("joe:123")
            .SetFinalHost("wikipedia.com")
            .SetHasRelativePath(true)
            ),
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("https://bob@google.com.ua:8000")
            .SetFinalScheme("https")
            .SetFinalUserInfo("bob")
            .SetFinalHost("google.com.ua")
            .SetFinalPortNumber(8000)
            .SetHasRelativePath(true)
            )
        )
);

INSTANTIATE_TEST_SUITE_P(UriWithMultipleColonCharacter, UriParam,
    testing::Values(
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("//[v7.:]")
            .SetFinalHost("[v7.:]")
            .SetHasRelativePath(true)
            ),
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("//google.com/a:b")
            .SetFinalHost("google.com")
            .SetFinalPath({ "", "a:b" })
            ),
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("//google.com?a:b")
            .SetFinalHost("google.com")
            .SetHasRelativePath(true)
            .SetFinalQuery("a:b")
            ),
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("//google.com#a:b")
            .SetFinalHost("google.com")
            .SetFinalFragment("a:b")
            .SetHasRelativePath(true)
            ),
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("http://google.com:8080/pa:th?u:a#a:b")
            .SetFinalScheme("http")
            .SetFinalHost("google.com")
            .SetFinalPortNumber(8080)
            .SetFinalPath({ "", "pa:th" })
            .SetFinalQuery("u:a")
            .SetFinalFragment("a:b")
            ),
        
        //interpreted as  relative reference, first part can hold ':' character, because starts with '/'
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("/path:1/path:2")
            .SetFinalPath({ "", "path:1", "path:2" })
            .SetIsRelativeReference(true)
            ),

        //interpreted as urn, because first segment has ':' and doesn't start with a '/'
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("path:1/path:2")
            .SetFinalScheme("path")
            .SetFinalPath({ "1", "path:2" })
            .SetHasRelativePath(true)
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
            .SetHasRelativePath(true)
            ),
        //TODO: ???
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
            .SetFinalPath({ "film", "thriller", "silence_of_lambs"})
            .SetHasRelativePath(true)
            ),
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("dpu::/film:/horror:/ring:/")
            .SetInitialDelimiter(":/")
            .SetFinalScheme("dpu")
            .SetFinalPath({ "", "film", "horror", "ring", ""})
            .SetHasRelativePath(false)
            )
    )
);


INSTANTIATE_TEST_SUITE_P(UriRelativeReferenceAndPath, UriParam,
    testing::Values(
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("home/users/ivan_che")
            .SetFinalPath({ "home", "users", "ivan_che" })
            .SetIsRelativeReference(true)
            .SetHasRelativePath(true)
            ),
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("/downloads/torrent/")
            .SetFinalPath({ "", "downloads", "torrent", "" })
            .SetIsRelativeReference(true)
            .SetHasRelativePath(false)
            ),
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("home")
            .SetFinalPath({ "home" })
            .SetIsRelativeReference(true)
            .SetHasRelativePath(true)
            ),
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("/home")
            .SetFinalPath({ "", "home" })
            .SetIsRelativeReference(true)
            .SetHasRelativePath(false)
            ),
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("/")
            .SetFinalPath({ "" })
            .SetIsRelativeReference(true)
            .SetHasRelativePath(false)
            ),
        static_cast<UriState>(
            UriState::create()
            .SetInitialParsingString("")
            .SetFinalPath({ })
            .SetIsRelativeReference(true)
            .SetHasRelativePath(true)
            )
    )
);


/*
 *Builder isn't convenient, cause user needs to use manual cast
 *to UriState. Maybe it's simpler to implement just public set_functions
 *with public constructor
 *
*/







