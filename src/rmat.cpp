/* -*- mode: C; mode: folding; fill-column: 70; -*- */
/* Copyright 2010,  Georgia Institute of Technology, USA. */
/* See COPYING for license. */

#include <hpx/util/assert.hpp>

#include <prng.hpp>
#include <generator/splittable_mrg.hpp>
#include <generator/graph_generator.hpp>

#include <rmat.hpp>

/* Recursively divide a grid of N x N by four to a single point, (i, j).
   Choose between the four quadrants with probability a, b, c, and d.
   Create an edge between node i and j.
*/

typedef std::vector<graph500::generator::packed_edge> edgelist_type;

namespace graph500 { namespace generator
{

    std::vector<packed_edge> permute_edgelist(
        std::int64_t nedge
      , mrg_state &st)
    {
        edgelist_type IJ;
        for(std::size_t k = 0; k < nedge; ++k){
            std::int64_t place; 
            place = k + (std::int64_t)floor (st.get_double_orig() * (nedge - k)); 
           
            if(k != place) { 
                edgelist_type t; 
                t[0] = IJ[place]; 
                IJ[place] = IJ[k]; 
                IJ[k] = t[0]; 
            } 
        } 
    }

#define NRAND(ne) (5 * SCALE * (ne))

    std::vector<packed_edge> rmat_edgelist(
        std::int64_t nedge
      , int SCALE
      , std::double A
      , std::double B
      , std::double C
    )
    {
        edgelist_type IJ;

        std::vector<int64_t> iwork;
        iwork.reserve((1L<<SCALE));

        std::double D = 1.0 - (A + B + C);

        std::vector<double> Rlocal;
        Rlocal.reserve(NRAND(1));

        mrg_state new_st(prng_state);

        for(std::size_t k = 0; k < nedge; ++k) 
        {
            new_st.skip (1, NRAND(1), 0);
            for(std::size_t k2 = 0; k2 < NRAND(1); ++k2)
                Rlocal.push_back(new_st.get_double_orig());
//          IJ.push_back(rmat_edge(SCALE,A,B,C,D,Rlocal));
        }

        new_st.skip(1, NRAND(nedge), 0);
        mrg_state new_st(prng_state);
//      permute_vertex_labels
        new_st.skip(1, (1L<<SCALE), 0);
        mrg_state new_st(prng_state);
        IJ=permute_edgelist(nedge,&new_st);
    }
    new_st.skip(1, nedge, 0);
}

