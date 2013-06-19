#ifndef MPLLIBS_METAMONAD_HAS_GET_VALUE_HPP
#define MPLLIBS_METAMONAD_HAS_GET_VALUE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metamonad/impl/yes.hpp>
#include <mpllibs/metamonad/impl/no.hpp>

#include <mpllibs/metamonad/lazy_metafunction.hpp>

#include <boost/config.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/int.hpp>

namespace mpllibs
{
  namespace metamonad
  {
    namespace impl
    {
      no has_get_value_test(...);

#if defined BOOST_NO_CXX11_DECLTYPE || defined BOOST_NO_DECLTYPE
      template <class T>
      yes has_get_value_test(T*, boost::mpl::int_<sizeof(T::get_value())>* = 0);
#else
      template <class T>
      yes has_get_value_test(T*, decltype(T::get_value())* = 0);
#endif
    }

    MPLLIBS_LAZY_METAFUNCTION(has_get_value, (T))
    ((
      boost::mpl::bool_<
        sizeof(impl::has_get_value_test((T*)0)) == sizeof(impl::yes)
      >
    ));
  }
}

#endif

