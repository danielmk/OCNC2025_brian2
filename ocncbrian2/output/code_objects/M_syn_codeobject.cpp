#include "code_objects/M_syn_codeobject.h"
#include "objects.h"
#include "brianlib/common_math.h"
#include "brianlib/stdint_compat.h"
#include<cmath>
#include<ctime>
#include<iostream>
#include<fstream>
#include<climits>

////// SUPPORT CODE ///////
namespace {
        
    template < typename T1, typename T2 > struct _higher_type;
    template < > struct _higher_type<int32_t,int32_t> { typedef int32_t type; };
    template < > struct _higher_type<int32_t,int64_t> { typedef int64_t type; };
    template < > struct _higher_type<int32_t,float> { typedef float type; };
    template < > struct _higher_type<int32_t,double> { typedef double type; };
    template < > struct _higher_type<int32_t,long double> { typedef long double type; };
    template < > struct _higher_type<int64_t,int32_t> { typedef int64_t type; };
    template < > struct _higher_type<int64_t,int64_t> { typedef int64_t type; };
    template < > struct _higher_type<int64_t,float> { typedef float type; };
    template < > struct _higher_type<int64_t,double> { typedef double type; };
    template < > struct _higher_type<int64_t,long double> { typedef long double type; };
    template < > struct _higher_type<float,int32_t> { typedef float type; };
    template < > struct _higher_type<float,int64_t> { typedef float type; };
    template < > struct _higher_type<float,float> { typedef float type; };
    template < > struct _higher_type<float,double> { typedef double type; };
    template < > struct _higher_type<float,long double> { typedef long double type; };
    template < > struct _higher_type<double,int32_t> { typedef double type; };
    template < > struct _higher_type<double,int64_t> { typedef double type; };
    template < > struct _higher_type<double,float> { typedef double type; };
    template < > struct _higher_type<double,double> { typedef double type; };
    template < > struct _higher_type<double,long double> { typedef long double type; };
    template < > struct _higher_type<long double,int32_t> { typedef long double type; };
    template < > struct _higher_type<long double,int64_t> { typedef long double type; };
    template < > struct _higher_type<long double,float> { typedef long double type; };
    template < > struct _higher_type<long double,double> { typedef long double type; };
    template < > struct _higher_type<long double,long double> { typedef long double type; };
    // General template, used for floating point types
    template < typename T1, typename T2 >
    static inline typename _higher_type<T1,T2>::type
    _brian_mod(T1 x, T2 y)
    {
        return x-y*floor(1.0*x/y);
    }
    // Specific implementations for integer types
    // (from Cython, see LICENSE file)
    template <>
    inline int32_t _brian_mod(int32_t x, int32_t y)
    {
        int32_t r = x % y;
        r += ((r != 0) & ((r ^ y) < 0)) * y;
        return r;
    }
    template <>
    inline int64_t _brian_mod(int32_t x, int64_t y)
    {
        int64_t r = x % y;
        r += ((r != 0) & ((r ^ y) < 0)) * y;
        return r;
    }
    template <>
    inline int64_t _brian_mod(int64_t x, int32_t y)
    {
        int64_t r = x % y;
        r += ((r != 0) & ((r ^ y) < 0)) * y;
        return r;
    }
    template <>
    inline int64_t _brian_mod(int64_t x, int64_t y)
    {
        int64_t r = x % y;
        r += ((r != 0) & ((r ^ y) < 0)) * y;
        return r;
    }
    // General implementation, used for floating point types
    template < typename T1, typename T2 >
    static inline typename _higher_type<T1,T2>::type
    _brian_floordiv(T1 x, T2 y)
    {{
        return floor(1.0*x/y);
    }}
    // Specific implementations for integer types
    // (from Cython, see LICENSE file)
    template <>
    inline int32_t _brian_floordiv<int32_t, int32_t>(int32_t a, int32_t b) {
        int32_t q = a / b;
        int32_t r = a - q*b;
        q -= ((r != 0) & ((r ^ b) < 0));
        return q;
    }
    template <>
    inline int64_t _brian_floordiv<int32_t, int64_t>(int32_t a, int64_t b) {
        int64_t q = a / b;
        int64_t r = a - q*b;
        q -= ((r != 0) & ((r ^ b) < 0));
        return q;
    }
    template <>
    inline int64_t _brian_floordiv<int64_t, int>(int64_t a, int32_t b) {
        int64_t q = a / b;
        int64_t r = a - q*b;
        q -= ((r != 0) & ((r ^ b) < 0));
        return q;
    }
    template <>
    inline int64_t _brian_floordiv<int64_t, int64_t>(int64_t a, int64_t b) {
        int64_t q = a / b;
        int64_t r = a - q*b;
        q -= ((r != 0) & ((r ^ b) < 0));
        return q;
    }
    #ifdef _MSC_VER
    #define _brian_pow(x, y) (pow((double)(x), (y)))
    #else
    #define _brian_pow(x, y) (pow((x), (y)))
    #endif

}

////// HASH DEFINES ///////



void _run_M_syn_codeobject()
{
    using namespace brian;


    ///// CONSTANTS ///////////
    const size_t _numN = 1;
const size_t _num_clock_t = 1;
const size_t _num_indices = 500;
double* const _array_exc_recurrent_synapses_g = _dynamic_array_exc_recurrent_synapses_g.empty()? 0 : &_dynamic_array_exc_recurrent_synapses_g[0];
const size_t _num_source_g = _dynamic_array_exc_recurrent_synapses_g.size();
double* const _array_exc_recurrent_synapses_tau_inact = _dynamic_array_exc_recurrent_synapses_tau_inact.empty()? 0 : &_dynamic_array_exc_recurrent_synapses_tau_inact[0];
const size_t _num_source_tau_inact = _dynamic_array_exc_recurrent_synapses_tau_inact.size();
double* const _array_exc_recurrent_synapses_weight = _dynamic_array_exc_recurrent_synapses_weight.empty()? 0 : &_dynamic_array_exc_recurrent_synapses_weight[0];
const size_t _num_source_weight = _dynamic_array_exc_recurrent_synapses_weight.size();
double* const _array_M_syn_t = _dynamic_array_M_syn_t.empty()? 0 : &_dynamic_array_M_syn_t[0];
const size_t _numt = _dynamic_array_M_syn_t.size();
    ///// POINTERS ////////////
        
    int32_t*   _ptr_array_M_syn_N = _array_M_syn_N;
    double*   _ptr_array_exc_recurrent_synapses_clock_t = _array_exc_recurrent_synapses_clock_t;
    int32_t* __restrict  _ptr_array_M_syn__indices = _array_M_syn__indices;
    double* __restrict  _ptr_array_exc_recurrent_synapses_g = _array_exc_recurrent_synapses_g;
    double* __restrict  _ptr_array_exc_recurrent_synapses_tau_inact = _array_exc_recurrent_synapses_tau_inact;
    double* __restrict  _ptr_array_exc_recurrent_synapses_weight = _array_exc_recurrent_synapses_weight;
    double* __restrict  _ptr_array_M_syn_t = _array_M_syn_t;


    _dynamic_array_M_syn_t.push_back(_ptr_array_exc_recurrent_synapses_clock_t[0]);

    const size_t _new_size = _dynamic_array_M_syn_t.size();
    // Resize the dynamic arrays
    _dynamic_array_M_syn_g.resize(_new_size, _num_indices);
    _dynamic_array_M_syn_tau_inact.resize(_new_size, _num_indices);
    _dynamic_array_M_syn_weight.resize(_new_size, _num_indices);

    // scalar code
    const size_t _vectorisation_idx = -1;
        


    
    for (int _i = 0; _i < (int)_num_indices; _i++)
    {
        // vector code
        const size_t _idx = _ptr_array_M_syn__indices[_i];
        const size_t _vectorisation_idx = _idx;
                
        const double _source_g = _ptr_array_exc_recurrent_synapses_g[_idx];
        const double _source_tau_inact = _ptr_array_exc_recurrent_synapses_tau_inact[_idx];
        const double _source_weight = _ptr_array_exc_recurrent_synapses_weight[_idx];
        const double _to_record_tau_inact = _source_tau_inact;
        const double _to_record_g = _source_g;
        const double _to_record_weight = _source_weight;


        _dynamic_array_M_syn_g(_new_size-1, _i) = _to_record_g;
        _dynamic_array_M_syn_tau_inact(_new_size-1, _i) = _to_record_tau_inact;
        _dynamic_array_M_syn_weight(_new_size-1, _i) = _to_record_weight;
    }

    _ptr_array_M_syn_N[0] = _new_size;


}


