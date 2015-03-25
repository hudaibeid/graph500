//  Copyright (c) 2015 Huda Ibeid
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GRAPH500_RMAT_HPP
#define GRAPH500_RMAT_HPP

#include <generator/graph_generator.hpp>

#include <vector>

namespace graph500 { namespace generator
{

/** Fill IJ with a randomly permuted R-MAT generated edge list. */
   std::vector<packed_edge> edgelist_type rmat_edgelist(
       std::int64_t nedge
     , int SCALE
     , std::double A
     , std::double B
     , std::double C
   );

   std::vector<packed_edge> edgelist_type permute_edgelist(
       std::int64_t nedge
     , mrg_state &st
   );

#endif  
