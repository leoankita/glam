// Copyright 2017 Oh-Hyun Kwon (kwonoh.net)
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __KW_ALGORITHM_NORMALIZE_HPP__
#define __KW_ALGORITHM_NORMALIZE_HPP__

#ifdef KW_USE_TBB
#include <tbb/tbb.h>
#include <iterator>
#endif

#include <algorithm>

namespace kw {

template <typename Container>
void
minmax_normalize(Container& c)
{
    auto const minmax = std::minmax_element(c.begin(), c.end());
    auto const min = *minmax.first;
    auto const max = *minmax.second;
    auto const range = max - min;

#ifdef KW_USE_TBB
    tbb::parallel_for_each(c, [=](auto& x) { x = (x - min) / range; });
#else
    std::transform(std::begin(c), std::end(c), std::begin(c),
                   [&](auto const x) { return (x - min) / range; });
#endif
}

}  // namespace kw

#endif  // __KW_ALGORITHM_NORMALIZE_HPP__