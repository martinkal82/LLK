#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "LL1.hpp"


using namespace LL1;


template <typename T>
struct input_stream_dummy
{
    constexpr input_stream_dummy(typename std::char_traits<T>::int_type tok)
        : tok{ tok }
    { }

    constexpr auto peek() noexcept
    {
        return tok;
    }

    constexpr auto get() noexcept
    {
        return tok;
    }

    typename std::char_traits<T>::int_type tok;

};


namespace LL1
{
    template <typename T>
    struct input_source_traits<input_stream_dummy<T>>
    {
        using char_type = T;

        static char_type look_ahead(input_stream_dummy<T>& ins) noexcept
        {
            return ins.peek();
        }

        static constexpr char_type read(input_stream_dummy<T>& ins) noexcept
        {
            return ins.get();
        }

        static constexpr bool is_end(input_stream_dummy<T>& ins) noexcept
        {
            return ins.peek() == std::char_traits<T>::eof();
        }
    };
}


TEST_CASE( "testing is function overloads", "[is]" )
{
    SECTION("char tests")
    {
        input_stream_dummy<char> ins('a');
        input_stream_dummy<char> ins_eof(std::char_traits<char>::eof());

        REQUIRE(is(ins,     'a'      ) == true );
        REQUIRE(is(ins,     'b'      ) == false);
        REQUIRE(is(ins,     character) == true );
        REQUIRE(is(ins,     end      ) == false);
        REQUIRE(is(ins_eof, 'a'      ) == false);
        REQUIRE(is(ins_eof, character) == false);
        REQUIRE(is(ins_eof, end      ) == true );
    }

    SECTION("wchar_t tests")
    {
        input_stream_dummy<wchar_t> ins(L'a');
        input_stream_dummy<wchar_t> ins_eof(std::char_traits<wchar_t>::eof());

        REQUIRE(is(ins,     L'a'     ) == true );
        REQUIRE(is(ins,     L'b'     ) == false);
        REQUIRE(is(ins,     character) == true );
        REQUIRE(is(ins,     end      ) == false);
        REQUIRE(is(ins_eof, L'a'     ) == false);
        REQUIRE(is(ins_eof, character) == false);
        REQUIRE(is(ins_eof, end      ) == true );
    }

    SECTION("char16_t tests")
    {
        input_stream_dummy<char16_t> ins(u'a');
        input_stream_dummy<char16_t> ins_eof(std::char_traits<char16_t>::eof());

        REQUIRE(is(ins,     u'a'     ) == true );
        REQUIRE(is(ins,     u'b'     ) == false);
        REQUIRE(is(ins,     character) == true );
        REQUIRE(is(ins,     end      ) == false);
        REQUIRE(is(ins_eof, u'a'     ) == false);
        REQUIRE(is(ins_eof, character) == false);
        REQUIRE(is(ins_eof, end      ) == true );

    }

    SECTION("char32_t tests")
    {
        input_stream_dummy<char32_t> ins(U'a');
        input_stream_dummy<char32_t> ins_eof(std::char_traits<char32_t>::eof());

        REQUIRE(is(ins,     U'a'     ) == true );
        REQUIRE(is(ins,     U'b'     ) == false);
        REQUIRE(is(ins,     character) == true );
        REQUIRE(is(ins,     end      ) == false);
        REQUIRE(is(ins_eof, U'a'     ) == false);
        REQUIRE(is(ins_eof, character) == false);
        REQUIRE(is(ins_eof, end      ) == true );

    }
}

TEST_CASE( "testing is_not function overloads", "[is-not]" )
{
    SECTION("char tests")
    {
        input_stream_dummy<char> ins('a');
        input_stream_dummy<char> ins_eof(std::char_traits<char>::eof());

        REQUIRE(is_not(ins,     'a'      ) == false);
        REQUIRE(is_not(ins,     'b'      ) == true );
        REQUIRE(is_not(ins,     character) == false);
        REQUIRE(is_not(ins,     end      ) == true );
        REQUIRE(is_not(ins_eof, 'a'      ) == true );
        REQUIRE(is_not(ins_eof, character) == true );
        REQUIRE(is_not(ins_eof, end      ) == false);
    }

    SECTION("wchar_t tests")
    {
        input_stream_dummy<wchar_t> ins(L'a');
        input_stream_dummy<wchar_t> ins_eof(std::char_traits<wchar_t>::eof());

        REQUIRE(is_not(ins,     L'a'     ) == false);
        REQUIRE(is_not(ins,     L'b'     ) == true );
        REQUIRE(is_not(ins,     character) == false);
        REQUIRE(is_not(ins,     end      ) == true );
        REQUIRE(is_not(ins_eof, L'a'     ) == true );
        REQUIRE(is_not(ins_eof, character) == true );
        REQUIRE(is_not(ins_eof, end      ) == false);
    }

    SECTION("char16_t tests")
    {
        input_stream_dummy<char16_t> ins(u'a');
        input_stream_dummy<char16_t> ins_eof(std::char_traits<char16_t>::eof());

        REQUIRE(is_not(ins,     u'a'     ) == false);
        REQUIRE(is_not(ins,     u'b'     ) == true );
        REQUIRE(is_not(ins,     character) == false);
        REQUIRE(is_not(ins,     end      ) == true );
        REQUIRE(is_not(ins_eof, u'a'     ) == true );
        REQUIRE(is_not(ins_eof, character) == true );
        REQUIRE(is_not(ins_eof, end      ) == false);
    }

    SECTION("char32_t tests")
    {
        input_stream_dummy<char32_t> ins(U'a');
        input_stream_dummy<char32_t> ins_eof(std::char_traits<char32_t>::eof());

        REQUIRE(is_not(ins,     U'a'     ) == false);
        REQUIRE(is_not(ins,     U'b'     ) == true );
        REQUIRE(is_not(ins,     character) == false);
        REQUIRE(is_not(ins,     end      ) == true );
        REQUIRE(is_not(ins_eof, U'a'     ) == true );
        REQUIRE(is_not(ins_eof, character) == true );
        REQUIRE(is_not(ins_eof, end      ) == false);
    }
}


TEST_CASE( "testing is_one_of function overloads", "[is-one-of]" )
{
    SECTION("char tests")
    {
        input_stream_dummy<char> ins('a');
        input_stream_dummy<char> ins_eof(std::char_traits<char>::eof());

        REQUIRE(is_one_of(ins,     'a'     ) == true );
        REQUIRE(is_one_of(ins,     'b'     ) == false);

        REQUIRE(is_one_of(ins_eof, 'a'     ) == false);
        
        REQUIRE(is_one_of(ins,     'a', 'b') == true );
        REQUIRE(is_one_of(ins,     'b', 'a') == true );
        REQUIRE(is_one_of(ins,     'b', 'c') == false);

        REQUIRE(is_one_of(ins_eof, 'a', 'b') == false);
    }

    SECTION("wchar_t tests")
    {
        input_stream_dummy<wchar_t> ins(L'a');
        input_stream_dummy<wchar_t> ins_eof(std::char_traits<wchar_t>::eof());

        REQUIRE(is_one_of(ins,     L'a'      ) == true );
        REQUIRE(is_one_of(ins,     L'b'      ) == false);

        REQUIRE(is_one_of(ins_eof, L'a'      ) == false);
        
        REQUIRE(is_one_of(ins,     L'a', L'b') == true );
        REQUIRE(is_one_of(ins,     L'b', L'a') == true );
        REQUIRE(is_one_of(ins,     L'b', L'c') == false);

        REQUIRE(is_one_of(ins_eof, L'a', L'b') == false);
    }

    SECTION("char16_t tests")
    {
        input_stream_dummy<char16_t> ins(u'a');
        input_stream_dummy<char16_t> ins_eof(std::char_traits<char16_t>::eof());

        REQUIRE(is_one_of(ins,     u'a'      ) == true );
        REQUIRE(is_one_of(ins,     u'b'      ) == false);

        REQUIRE(is_one_of(ins_eof, u'a'      ) == false);
        
        REQUIRE(is_one_of(ins,     u'a', u'b') == true );
        REQUIRE(is_one_of(ins,     u'b', u'a') == true );
        REQUIRE(is_one_of(ins,     u'b', u'c') == false);

        REQUIRE(is_one_of(ins_eof, u'a', u'b') == false);
    }

    SECTION("char32_t tests")
    {
        input_stream_dummy<char32_t> ins(U'a');
        input_stream_dummy<char32_t> ins_eof(std::char_traits<char32_t>::eof());

        REQUIRE(is_one_of(ins,     U'a'      ) == true );
        REQUIRE(is_one_of(ins,     U'b'      ) == false);

        REQUIRE(is_one_of(ins_eof, U'a'      ) == false);
        
        REQUIRE(is_one_of(ins,     U'a', U'b') == true );
        REQUIRE(is_one_of(ins,     U'b', U'a') == true );
        REQUIRE(is_one_of(ins,     U'b', U'c') == false);

        REQUIRE(is_one_of(ins_eof, U'a', U'b') == false);
    }
}

TEST_CASE( "testing is_none_of function overloads", "[is-none-of]" )
{
    SECTION("char tests")
    {
        input_stream_dummy<char> ins('a');
        input_stream_dummy<char> ins_eof(std::char_traits<char>::eof());

        REQUIRE(is_none_of(ins,     'a'     ) == false);
        REQUIRE(is_none_of(ins,     'b'     ) == true );

        REQUIRE(is_none_of(ins_eof, 'a'     ) == true );

        REQUIRE(is_none_of(ins,     'a', 'b') == false);
        REQUIRE(is_none_of(ins,     'b', 'a') == false);
        REQUIRE(is_none_of(ins,     'b', 'c') == true );

        REQUIRE(is_none_of(ins_eof, 'a', 'b') == true );
    }

    SECTION("wchar_t tests")
    {
        input_stream_dummy<wchar_t> ins(L'a');
        input_stream_dummy<wchar_t> ins_eof(std::char_traits<wchar_t>::eof());

        REQUIRE(is_none_of(ins,     L'a'      ) == false);
        REQUIRE(is_none_of(ins,     L'b'      ) == true );

        REQUIRE(is_none_of(ins_eof, L'a'      ) == true );

        REQUIRE(is_none_of(ins,     L'a', L'b') == false);
        REQUIRE(is_none_of(ins,     L'b', L'a') == false);
        REQUIRE(is_none_of(ins,     L'b', L'c') == true );

        REQUIRE(is_none_of(ins_eof, L'a', L'b') == true );
    }

    SECTION("char16_t tests")
    {
        input_stream_dummy<char16_t> ins(u'a');
        input_stream_dummy<char16_t> ins_eof(std::char_traits<char16_t>::eof());

        REQUIRE(is_none_of(ins,     u'a'      ) == false);
        REQUIRE(is_none_of(ins,     u'b'      ) == true );

        REQUIRE(is_none_of(ins_eof, u'a'      ) == true );

        REQUIRE(is_none_of(ins,     u'a', u'b') == false);
        REQUIRE(is_none_of(ins,     u'b', u'a') == false);
        REQUIRE(is_none_of(ins,     u'b', u'c') == true );

        REQUIRE(is_none_of(ins_eof, u'a', u'b') == true );
    }

    SECTION("char32_t tests")
    {
        input_stream_dummy<char32_t> ins(U'a');
        input_stream_dummy<char32_t> ins_eof(std::char_traits<char32_t>::eof());

        REQUIRE(is_none_of(ins,     U'a'      ) == false);
        REQUIRE(is_none_of(ins,     U'b'      ) == true );

        REQUIRE(is_none_of(ins_eof, U'a'      ) == true );

        REQUIRE(is_none_of(ins,     U'a', U'b') == false);
        REQUIRE(is_none_of(ins,     U'b', U'a') == false);
        REQUIRE(is_none_of(ins,     U'b', U'c') == true );

        REQUIRE(is_none_of(ins_eof, U'a', U'b') == true );
    }
}



