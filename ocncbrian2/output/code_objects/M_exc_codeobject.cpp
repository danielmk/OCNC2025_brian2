#include "code_objects/M_exc_codeobject.h"
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



void _run_M_exc_codeobject()
{
    using namespace brian;


    ///// CONSTANTS ///////////
    const size_t _numN = 1;
const size_t _num___source_I_total_exc_neurons_I_AMPA_exc_neurons_EEx = 500;
const size_t _num___source_I_total_exc_neurons_I_AMPA_exc_neurons_ge = 500;
const size_t _num___source_I_total_exc_neurons_I_AMPA_exc_neurons_v = 500;
const size_t _num___source_I_total_exc_neurons_I_GABA_exc_neurons_EIn = 500;
const size_t _num___source_I_total_exc_neurons_I_GABA_exc_neurons_gi = 500;
const size_t _num___source_I_total_exc_neurons_I_GABA_exc_neurons_v = 500;
const size_t _num__source_I_AMPA_exc_neurons_EEx = 500;
const size_t _num__source_I_AMPA_exc_neurons_ge = 500;
const size_t _num__source_I_AMPA_exc_neurons_v = 500;
const size_t _num__source_I_GABA_exc_neurons_EIn = 500;
const size_t _num__source_I_GABA_exc_neurons_gi = 500;
const size_t _num__source_I_GABA_exc_neurons_v = 500;
const size_t _num__source_I_total_exc_neurons_I = 500;
const size_t _num_clock_t = 1;
const size_t _num_indices = 500;
const size_t _num_source_C = 500;
const size_t _num_source_DeltaT = 500;
const size_t _num_source_EEx = 500;
const size_t _num_source_EIn = 500;
const size_t _num_source_EL = 500;
const size_t _num_source_I = 500;
const size_t _num_source_VT = 500;
const size_t _num_source_Vr = 500;
const size_t _num_source_a = 500;
const size_t _num_source_b = 500;
const size_t _num_source_gL = 500;
const size_t _num_source_ge = 500;
const size_t _num_source_gi = 500;
const size_t _num_source_tau_w = 500;
const size_t _num_source_v = 500;
const size_t _num_source_w = 500;
double* const _array_M_exc_t = _dynamic_array_M_exc_t.empty()? 0 : &_dynamic_array_M_exc_t[0];
const size_t _numt = _dynamic_array_M_exc_t.size();
    ///// POINTERS ////////////
        
    int32_t*   _ptr_array_M_exc_N = _array_M_exc_N;
    double* __restrict  _ptr_array_exc_neurons_EEx = _array_exc_neurons_EEx;
    double* __restrict  _ptr_array_exc_neurons_ge = _array_exc_neurons_ge;
    double* __restrict  _ptr_array_exc_neurons_v = _array_exc_neurons_v;
    double* __restrict  _ptr_array_exc_neurons_EIn = _array_exc_neurons_EIn;
    double* __restrict  _ptr_array_exc_neurons_gi = _array_exc_neurons_gi;
    double* __restrict  _ptr_array_exc_neurons_I = _array_exc_neurons_I;
    double*   _ptr_array_exc_neurons_clock_t = _array_exc_neurons_clock_t;
    int32_t* __restrict  _ptr_array_M_exc__indices = _array_M_exc__indices;
    double* __restrict  _ptr_array_exc_neurons_C = _array_exc_neurons_C;
    double* __restrict  _ptr_array_exc_neurons_DeltaT = _array_exc_neurons_DeltaT;
    double* __restrict  _ptr_array_exc_neurons_EL = _array_exc_neurons_EL;
    double* __restrict  _ptr_array_exc_neurons_VT = _array_exc_neurons_VT;
    double* __restrict  _ptr_array_exc_neurons_Vr = _array_exc_neurons_Vr;
    double* __restrict  _ptr_array_exc_neurons_a = _array_exc_neurons_a;
    double* __restrict  _ptr_array_exc_neurons_b = _array_exc_neurons_b;
    double* __restrict  _ptr_array_exc_neurons_gL = _array_exc_neurons_gL;
    double* __restrict  _ptr_array_exc_neurons_tau_w = _array_exc_neurons_tau_w;
    double* __restrict  _ptr_array_exc_neurons_w = _array_exc_neurons_w;
    double* __restrict  _ptr_array_M_exc_t = _array_M_exc_t;


    _dynamic_array_M_exc_t.push_back(_ptr_array_exc_neurons_clock_t[0]);

    const size_t _new_size = _dynamic_array_M_exc_t.size();
    // Resize the dynamic arrays
    _dynamic_array_M_exc_a.resize(_new_size, _num_indices);
    _dynamic_array_M_exc_b.resize(_new_size, _num_indices);
    _dynamic_array_M_exc_C.resize(_new_size, _num_indices);
    _dynamic_array_M_exc_DeltaT.resize(_new_size, _num_indices);
    _dynamic_array_M_exc_EEx.resize(_new_size, _num_indices);
    _dynamic_array_M_exc_EIn.resize(_new_size, _num_indices);
    _dynamic_array_M_exc_EL.resize(_new_size, _num_indices);
    _dynamic_array_M_exc_ge.resize(_new_size, _num_indices);
    _dynamic_array_M_exc_gi.resize(_new_size, _num_indices);
    _dynamic_array_M_exc_gL.resize(_new_size, _num_indices);
    _dynamic_array_M_exc_I.resize(_new_size, _num_indices);
    _dynamic_array_M_exc_I_AMPA.resize(_new_size, _num_indices);
    _dynamic_array_M_exc_I_GABA.resize(_new_size, _num_indices);
    _dynamic_array_M_exc_I_total.resize(_new_size, _num_indices);
    _dynamic_array_M_exc_tau_w.resize(_new_size, _num_indices);
    _dynamic_array_M_exc_v.resize(_new_size, _num_indices);
    _dynamic_array_M_exc_Vr.resize(_new_size, _num_indices);
    _dynamic_array_M_exc_VT.resize(_new_size, _num_indices);
    _dynamic_array_M_exc_w.resize(_new_size, _num_indices);

    // scalar code
    const size_t _vectorisation_idx = -1;
        


    
    for (int _i = 0; _i < (int)_num_indices; _i++)
    {
        // vector code
        const size_t _idx = _ptr_array_M_exc__indices[_i];
        const size_t _vectorisation_idx = _idx;
                
        const double ___source_I_total_exc_neurons_I_AMPA_exc_neurons_EEx = _ptr_array_exc_neurons_EEx[_idx];
        const double ___source_I_total_exc_neurons_I_AMPA_exc_neurons_ge = _ptr_array_exc_neurons_ge[_idx];
        const double ___source_I_total_exc_neurons_I_AMPA_exc_neurons_v = _ptr_array_exc_neurons_v[_idx];
        const double ___source_I_total_exc_neurons_I_GABA_exc_neurons_EIn = _ptr_array_exc_neurons_EIn[_idx];
        const double ___source_I_total_exc_neurons_I_GABA_exc_neurons_gi = _ptr_array_exc_neurons_gi[_idx];
        const double ___source_I_total_exc_neurons_I_GABA_exc_neurons_v = _ptr_array_exc_neurons_v[_idx];
        const double __source_I_AMPA_exc_neurons_EEx = _ptr_array_exc_neurons_EEx[_idx];
        const double __source_I_AMPA_exc_neurons_ge = _ptr_array_exc_neurons_ge[_idx];
        const double __source_I_AMPA_exc_neurons_v = _ptr_array_exc_neurons_v[_idx];
        const double __source_I_GABA_exc_neurons_EIn = _ptr_array_exc_neurons_EIn[_idx];
        const double __source_I_GABA_exc_neurons_gi = _ptr_array_exc_neurons_gi[_idx];
        const double __source_I_GABA_exc_neurons_v = _ptr_array_exc_neurons_v[_idx];
        const double __source_I_total_exc_neurons_I = _ptr_array_exc_neurons_I[_idx];
        const double _source_C = _ptr_array_exc_neurons_C[_idx];
        const double _source_DeltaT = _ptr_array_exc_neurons_DeltaT[_idx];
        const double _source_EEx = _ptr_array_exc_neurons_EEx[_idx];
        const double _source_EIn = _ptr_array_exc_neurons_EIn[_idx];
        const double _source_EL = _ptr_array_exc_neurons_EL[_idx];
        const double _source_I = _ptr_array_exc_neurons_I[_idx];
        const double _source_VT = _ptr_array_exc_neurons_VT[_idx];
        const double _source_Vr = _ptr_array_exc_neurons_Vr[_idx];
        const double _source_a = _ptr_array_exc_neurons_a[_idx];
        const double _source_b = _ptr_array_exc_neurons_b[_idx];
        const double _source_gL = _ptr_array_exc_neurons_gL[_idx];
        const double _source_ge = _ptr_array_exc_neurons_ge[_idx];
        const double _source_gi = _ptr_array_exc_neurons_gi[_idx];
        const double _source_tau_w = _ptr_array_exc_neurons_tau_w[_idx];
        const double _source_v = _ptr_array_exc_neurons_v[_idx];
        const double _source_w = _ptr_array_exc_neurons_w[_idx];
        const double __source_I_total_exc_neurons_I_AMPA = (- ___source_I_total_exc_neurons_I_AMPA_exc_neurons_ge) * (___source_I_total_exc_neurons_I_AMPA_exc_neurons_v - ___source_I_total_exc_neurons_I_AMPA_exc_neurons_EEx);
        const double __source_I_total_exc_neurons_I_GABA = (- ___source_I_total_exc_neurons_I_GABA_exc_neurons_gi) * (___source_I_total_exc_neurons_I_GABA_exc_neurons_v - ___source_I_total_exc_neurons_I_GABA_exc_neurons_EIn);
        const double _source_I_total = (__source_I_total_exc_neurons_I_AMPA + __source_I_total_exc_neurons_I_GABA) + __source_I_total_exc_neurons_I;
        const double _to_record_I_total = _source_I_total;
        const double _to_record_a = _source_a;
        const double _to_record_I = _source_I;
        const double _to_record_EEx = _source_EEx;
        const double _to_record_EL = _source_EL;
        const double _to_record_w = _source_w;
        const double _to_record_v = _source_v;
        const double _to_record_Vr = _source_Vr;
        const double _to_record_ge = _source_ge;
        const double _to_record_C = _source_C;
        const double _to_record_tau_w = _source_tau_w;
        const double _to_record_gi = _source_gi;
        const double _source_I_GABA = (- __source_I_GABA_exc_neurons_gi) * (__source_I_GABA_exc_neurons_v - __source_I_GABA_exc_neurons_EIn);
        const double _to_record_I_GABA = _source_I_GABA;
        const double _to_record_VT = _source_VT;
        const double _to_record_gL = _source_gL;
        const double _source_I_AMPA = (- __source_I_AMPA_exc_neurons_ge) * (__source_I_AMPA_exc_neurons_v - __source_I_AMPA_exc_neurons_EEx);
        const double _to_record_I_AMPA = _source_I_AMPA;
        const double _to_record_EIn = _source_EIn;
        const double _to_record_DeltaT = _source_DeltaT;
        const double _to_record_b = _source_b;


        _dynamic_array_M_exc_a(_new_size-1, _i) = _to_record_a;
        _dynamic_array_M_exc_b(_new_size-1, _i) = _to_record_b;
        _dynamic_array_M_exc_C(_new_size-1, _i) = _to_record_C;
        _dynamic_array_M_exc_DeltaT(_new_size-1, _i) = _to_record_DeltaT;
        _dynamic_array_M_exc_EEx(_new_size-1, _i) = _to_record_EEx;
        _dynamic_array_M_exc_EIn(_new_size-1, _i) = _to_record_EIn;
        _dynamic_array_M_exc_EL(_new_size-1, _i) = _to_record_EL;
        _dynamic_array_M_exc_ge(_new_size-1, _i) = _to_record_ge;
        _dynamic_array_M_exc_gi(_new_size-1, _i) = _to_record_gi;
        _dynamic_array_M_exc_gL(_new_size-1, _i) = _to_record_gL;
        _dynamic_array_M_exc_I(_new_size-1, _i) = _to_record_I;
        _dynamic_array_M_exc_I_AMPA(_new_size-1, _i) = _to_record_I_AMPA;
        _dynamic_array_M_exc_I_GABA(_new_size-1, _i) = _to_record_I_GABA;
        _dynamic_array_M_exc_I_total(_new_size-1, _i) = _to_record_I_total;
        _dynamic_array_M_exc_tau_w(_new_size-1, _i) = _to_record_tau_w;
        _dynamic_array_M_exc_v(_new_size-1, _i) = _to_record_v;
        _dynamic_array_M_exc_Vr(_new_size-1, _i) = _to_record_Vr;
        _dynamic_array_M_exc_VT(_new_size-1, _i) = _to_record_VT;
        _dynamic_array_M_exc_w(_new_size-1, _i) = _to_record_w;
    }

    _ptr_array_M_exc_N[0] = _new_size;


}


