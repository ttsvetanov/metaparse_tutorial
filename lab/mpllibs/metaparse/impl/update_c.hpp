#ifndef MPLLIBS_METAPARSE_IMPL_UPDATE_C_HPP
#define MPLLIBS_METAPARSE_IMPL_UPDATE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metaparse/config.hpp>
#include <mpllibs/metaparse/string_fwd.hpp>
#include <mpllibs/metaparse/impl/split_at_c.hpp>
#include <mpllibs/metaparse/impl/concat.hpp>

#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace mpllibs
{
  namespace metaparse
  {
    namespace impl
    {
      template <class S, int N, char C>
      struct update_c;

#ifndef MPLLIBS_VARIADIC_STRING
      #ifdef MPLLIBS_ARGN
        #error MPLLIBS_ARGN already defined
      #endif
      #define MPLLIBS_ARGN(z, n, unused) , BOOST_PP_CAT(C, n)

      #ifdef MPLLIBS_UPDATE
        #error MPLLIBS_UPDATE already defined
      #endif
      #define MPLLIBS_UPDATE(z, n, unused) \
        template < \
          BOOST_PP_ENUM_PARAMS(MPLLIBS_STRING_MAX_LENGTH, int C), \
          char Ch \
        > \
        struct update_c< \
          string<BOOST_PP_ENUM_PARAMS(MPLLIBS_STRING_MAX_LENGTH, C)>, \
          n, \
          Ch \
        > : \
          string< \
            BOOST_PP_ENUM_PARAMS(n, C) BOOST_PP_COMMA_IF(n) \
            Ch \
            BOOST_PP_REPEAT_FROM_TO( \
              BOOST_PP_INC(n), \
              BOOST_PP_DEC(MPLLIBS_STRING_MAX_LENGTH), \
              MPLLIBS_ARGN, \
              ~ \
            ) \
          > \
        {};

      BOOST_PP_REPEAT(MPLLIBS_STRING_MAX_LENGTH, MPLLIBS_UPDATE, ~)

      #undef MPLLIBS_UPDATE
      #undef MPLLIBS_ARGN
#else
      template <class S, int N, char C>
      struct update_c :
        concat<
          typename split_at_c<N, S>::type::first,
          typename update_c<typename split_at_c<N, S>::type::second, 0, C>::type
        >
      {};

      template <char... Cs, char C, char NewChar>
      struct update_c<string<C, Cs...>, 0, NewChar> : string<NewChar, Cs...> {};
#endif
    }
  }
}

#endif

