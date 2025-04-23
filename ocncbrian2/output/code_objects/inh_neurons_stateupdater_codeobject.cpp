#include "code_objects/inh_neurons_stateupdater_codeobject.h"
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



void _run_inh_neurons_stateupdater_codeobject()
{
    using namespace brian;


    ///// CONSTANTS ///////////
    const size_t _numC = 100;
const size_t _numDeltaT = 100;
const size_t _numEEx = 100;
const size_t _numEIn = 100;
const size_t _numEL = 100;
const size_t _numI = 100;
const int64_t N = 100;
const size_t _numVT = 100;
const size_t _numa = 100;
const size_t _numdt = 1;
const size_t _numgL = 100;
const size_t _numge = 100;
const size_t _numgi = 100;
const size_t _numtau_w = 100;
const size_t _numv = 100;
const size_t _numw = 100;
    ///// POINTERS ////////////
        
    double* __restrict  _ptr_array_inh_neurons_C = _array_inh_neurons_C;
    double* __restrict  _ptr_array_inh_neurons_DeltaT = _array_inh_neurons_DeltaT;
    double* __restrict  _ptr_array_inh_neurons_EEx = _array_inh_neurons_EEx;
    double* __restrict  _ptr_array_inh_neurons_EIn = _array_inh_neurons_EIn;
    double* __restrict  _ptr_array_inh_neurons_EL = _array_inh_neurons_EL;
    double* __restrict  _ptr_array_inh_neurons_I = _array_inh_neurons_I;
    double* __restrict  _ptr_array_inh_neurons_VT = _array_inh_neurons_VT;
    double* __restrict  _ptr_array_inh_neurons_a = _array_inh_neurons_a;
    double*   _ptr_array_inh_neurons_clock_dt = _array_inh_neurons_clock_dt;
    double* __restrict  _ptr_array_inh_neurons_gL = _array_inh_neurons_gL;
    double* __restrict  _ptr_array_inh_neurons_ge = _array_inh_neurons_ge;
    double* __restrict  _ptr_array_inh_neurons_gi = _array_inh_neurons_gi;
    double* __restrict  _ptr_array_inh_neurons_tau_w = _array_inh_neurons_tau_w;
    double* __restrict  _ptr_array_inh_neurons_v = _array_inh_neurons_v;
    double* __restrict  _ptr_array_inh_neurons_w = _array_inh_neurons_w;


    //// MAIN CODE ////////////
    // scalar code
    const size_t _vectorisation_idx = -1;
        
    const double dt = _ptr_array_inh_neurons_clock_dt[0];


    const int _N = N;
    
    for(int _idx=0; _idx<_N; _idx++)
    {
        // vector code
        const size_t _vectorisation_idx = _idx;
                
        const double C = _ptr_array_inh_neurons_C[_idx];
        const double DeltaT = _ptr_array_inh_neurons_DeltaT[_idx];
        const double EEx = _ptr_array_inh_neurons_EEx[_idx];
        const double EIn = _ptr_array_inh_neurons_EIn[_idx];
        const double EL = _ptr_array_inh_neurons_EL[_idx];
        const double I = _ptr_array_inh_neurons_I[_idx];
        const double VT = _ptr_array_inh_neurons_VT[_idx];
        const double a = _ptr_array_inh_neurons_a[_idx];
        const double gL = _ptr_array_inh_neurons_gL[_idx];
        const double ge = _ptr_array_inh_neurons_ge[_idx];
        const double gi = _ptr_array_inh_neurons_gi[_idx];
        const double tau_w = _ptr_array_inh_neurons_tau_w[_idx];
        double v = _ptr_array_inh_neurons_v[_idx];
        double w = _ptr_array_inh_neurons_w[_idx];
        const double _v = v + (1.0f*(dt * ((((DeltaT * gL) * exp(1.0f*((- VT) + v)/DeltaT)) + I) - ((((gL * ((- EL) + v)) + (ge * ((- EEx) + v))) + (gi * ((- EIn) + v))) + w)))/C);
        const double _w = (1.0f*(dt * ((a * ((- EL) + v)) - w))/tau_w) + w;
        v = _v;
        w = _w;
        _ptr_array_inh_neurons_v[_idx] = v;
        _ptr_array_inh_neurons_w[_idx] = w;

    }

}


