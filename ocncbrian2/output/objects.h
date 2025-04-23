
#ifndef _BRIAN_OBJECTS_H
#define _BRIAN_OBJECTS_H

#include "synapses_classes.h"
#include "brianlib/clocks.h"
#include "brianlib/dynamic_array.h"
#include "brianlib/stdint_compat.h"
#include "network.h"
#include<random>
#include<vector>


namespace brian {

extern std::string results_dir;

class RandomGenerator {
    private:
        std::mt19937 gen;
        double stored_gauss;
        bool has_stored_gauss = false;
    public:
        RandomGenerator() {
            seed();
        }
        void seed() {
            std::random_device rd;
            gen.seed(rd());
            has_stored_gauss = false;
        }
        void seed(unsigned long seed) {
            gen.seed(seed);
            has_stored_gauss = false;
        }
        double rand() {
            /* shifts : 67108864 = 0x4000000, 9007199254740992 = 0x20000000000000 */
            const long a = gen() >> 5;
            const long b = gen() >> 6;
            return (a * 67108864.0 + b) / 9007199254740992.0;
        }

        double randn() {
            if (has_stored_gauss) {
                const double tmp = stored_gauss;
                has_stored_gauss = false;
                return tmp;
            }
            else {
                double f, x1, x2, r2;

                do {
                    x1 = 2.0*rand() - 1.0;
                    x2 = 2.0*rand() - 1.0;
                    r2 = x1*x1 + x2*x2;
                }
                while (r2 >= 1.0 || r2 == 0.0);

                /* Box-Muller transform */
                f = sqrt(-2.0*log(r2)/r2);
                /* Keep for next call */
                stored_gauss = f*x1;
                has_stored_gauss = true;
                return f*x2;
            }
        }
};

// In OpenMP we need one state per thread
extern std::vector< RandomGenerator > _random_generators;

//////////////// clocks ///////////////////
extern Clock exc_feedback_synapses_clock;
extern Clock exc_neurons_clock;
extern Clock exc_recurrent_synapses_clock;
extern Clock inh_neurons_clock;
extern Clock inh_synapses_clock;

//////////////// networks /////////////////
extern Network network;



void set_variable_by_name(std::string, std::string);

//////////////// dynamic arrays ///////////
extern std::vector<int32_t> _dynamic_array_exc_feedback_synapses__synaptic_post;
extern std::vector<int32_t> _dynamic_array_exc_feedback_synapses__synaptic_pre;
extern std::vector<double> _dynamic_array_exc_feedback_synapses_delay;
extern std::vector<double> _dynamic_array_exc_feedback_synapses_g;
extern std::vector<int32_t> _dynamic_array_exc_feedback_synapses_N_incoming;
extern std::vector<int32_t> _dynamic_array_exc_feedback_synapses_N_outgoing;
extern std::vector<double> _dynamic_array_exc_feedback_synapses_tau_inact;
extern std::vector<double> _dynamic_array_exc_feedback_synapses_weight;
extern std::vector<int32_t> _dynamic_array_exc_recurrent_synapses__synaptic_post;
extern std::vector<int32_t> _dynamic_array_exc_recurrent_synapses__synaptic_pre;
extern std::vector<double> _dynamic_array_exc_recurrent_synapses_delay;
extern std::vector<double> _dynamic_array_exc_recurrent_synapses_g;
extern std::vector<int32_t> _dynamic_array_exc_recurrent_synapses_N_incoming;
extern std::vector<int32_t> _dynamic_array_exc_recurrent_synapses_N_outgoing;
extern std::vector<double> _dynamic_array_exc_recurrent_synapses_tau_inact;
extern std::vector<double> _dynamic_array_exc_recurrent_synapses_weight;
extern std::vector<int32_t> _dynamic_array_inh_synapses__synaptic_post;
extern std::vector<int32_t> _dynamic_array_inh_synapses__synaptic_pre;
extern std::vector<double> _dynamic_array_inh_synapses_delay;
extern std::vector<double> _dynamic_array_inh_synapses_g;
extern std::vector<int32_t> _dynamic_array_inh_synapses_N_incoming;
extern std::vector<int32_t> _dynamic_array_inh_synapses_N_outgoing;
extern std::vector<double> _dynamic_array_inh_synapses_tau_inact;
extern std::vector<double> _dynamic_array_inh_synapses_weight;
extern std::vector<double> _dynamic_array_M_exc_t;
extern std::vector<double> _dynamic_array_M_inh_t;
extern std::vector<double> _dynamic_array_M_syn_t;
extern std::vector<int32_t> _dynamic_array_S_i;
extern std::vector<double> _dynamic_array_S_t;

//////////////// arrays ///////////////////
extern double *_array_defaultclock_dt;
extern const int _num__array_defaultclock_dt;
extern double *_array_defaultclock_t;
extern const int _num__array_defaultclock_t;
extern int64_t *_array_defaultclock_timestep;
extern const int _num__array_defaultclock_timestep;
extern double *_array_exc_feedback_synapses_clock_dt;
extern const int _num__array_exc_feedback_synapses_clock_dt;
extern double *_array_exc_feedback_synapses_clock_t;
extern const int _num__array_exc_feedback_synapses_clock_t;
extern int64_t *_array_exc_feedback_synapses_clock_timestep;
extern const int _num__array_exc_feedback_synapses_clock_timestep;
extern int32_t *_array_exc_feedback_synapses_N;
extern const int _num__array_exc_feedback_synapses_N;
extern int32_t *_array_exc_neurons__spikespace;
extern const int _num__array_exc_neurons__spikespace;
extern double *_array_exc_neurons_a;
extern const int _num__array_exc_neurons_a;
extern double *_array_exc_neurons_b;
extern const int _num__array_exc_neurons_b;
extern double *_array_exc_neurons_C;
extern const int _num__array_exc_neurons_C;
extern double *_array_exc_neurons_clock_dt;
extern const int _num__array_exc_neurons_clock_dt;
extern double *_array_exc_neurons_clock_t;
extern const int _num__array_exc_neurons_clock_t;
extern int64_t *_array_exc_neurons_clock_timestep;
extern const int _num__array_exc_neurons_clock_timestep;
extern double *_array_exc_neurons_DeltaT;
extern const int _num__array_exc_neurons_DeltaT;
extern double *_array_exc_neurons_EEx;
extern const int _num__array_exc_neurons_EEx;
extern double *_array_exc_neurons_EIn;
extern const int _num__array_exc_neurons_EIn;
extern double *_array_exc_neurons_EL;
extern const int _num__array_exc_neurons_EL;
extern double *_array_exc_neurons_ge;
extern const int _num__array_exc_neurons_ge;
extern double *_array_exc_neurons_gi;
extern const int _num__array_exc_neurons_gi;
extern double *_array_exc_neurons_gL;
extern const int _num__array_exc_neurons_gL;
extern int32_t *_array_exc_neurons_i;
extern const int _num__array_exc_neurons_i;
extern double *_array_exc_neurons_I;
extern const int _num__array_exc_neurons_I;
extern double *_array_exc_neurons_tau_w;
extern const int _num__array_exc_neurons_tau_w;
extern double *_array_exc_neurons_v;
extern const int _num__array_exc_neurons_v;
extern double *_array_exc_neurons_Vr;
extern const int _num__array_exc_neurons_Vr;
extern double *_array_exc_neurons_VT;
extern const int _num__array_exc_neurons_VT;
extern double *_array_exc_neurons_w;
extern const int _num__array_exc_neurons_w;
extern double *_array_exc_recurrent_synapses_clock_dt;
extern const int _num__array_exc_recurrent_synapses_clock_dt;
extern double *_array_exc_recurrent_synapses_clock_t;
extern const int _num__array_exc_recurrent_synapses_clock_t;
extern int64_t *_array_exc_recurrent_synapses_clock_timestep;
extern const int _num__array_exc_recurrent_synapses_clock_timestep;
extern int32_t *_array_exc_recurrent_synapses_N;
extern const int _num__array_exc_recurrent_synapses_N;
extern int32_t *_array_inh_neurons__spikespace;
extern const int _num__array_inh_neurons__spikespace;
extern double *_array_inh_neurons_a;
extern const int _num__array_inh_neurons_a;
extern double *_array_inh_neurons_b;
extern const int _num__array_inh_neurons_b;
extern double *_array_inh_neurons_C;
extern const int _num__array_inh_neurons_C;
extern double *_array_inh_neurons_clock_dt;
extern const int _num__array_inh_neurons_clock_dt;
extern double *_array_inh_neurons_clock_t;
extern const int _num__array_inh_neurons_clock_t;
extern int64_t *_array_inh_neurons_clock_timestep;
extern const int _num__array_inh_neurons_clock_timestep;
extern double *_array_inh_neurons_DeltaT;
extern const int _num__array_inh_neurons_DeltaT;
extern double *_array_inh_neurons_EEx;
extern const int _num__array_inh_neurons_EEx;
extern double *_array_inh_neurons_EIn;
extern const int _num__array_inh_neurons_EIn;
extern double *_array_inh_neurons_EL;
extern const int _num__array_inh_neurons_EL;
extern double *_array_inh_neurons_ge;
extern const int _num__array_inh_neurons_ge;
extern double *_array_inh_neurons_gi;
extern const int _num__array_inh_neurons_gi;
extern double *_array_inh_neurons_gL;
extern const int _num__array_inh_neurons_gL;
extern int32_t *_array_inh_neurons_i;
extern const int _num__array_inh_neurons_i;
extern double *_array_inh_neurons_I;
extern const int _num__array_inh_neurons_I;
extern double *_array_inh_neurons_tau_w;
extern const int _num__array_inh_neurons_tau_w;
extern double *_array_inh_neurons_v;
extern const int _num__array_inh_neurons_v;
extern double *_array_inh_neurons_Vr;
extern const int _num__array_inh_neurons_Vr;
extern double *_array_inh_neurons_VT;
extern const int _num__array_inh_neurons_VT;
extern double *_array_inh_neurons_w;
extern const int _num__array_inh_neurons_w;
extern double *_array_inh_synapses_clock_dt;
extern const int _num__array_inh_synapses_clock_dt;
extern double *_array_inh_synapses_clock_t;
extern const int _num__array_inh_synapses_clock_t;
extern int64_t *_array_inh_synapses_clock_timestep;
extern const int _num__array_inh_synapses_clock_timestep;
extern int32_t *_array_inh_synapses_N;
extern const int _num__array_inh_synapses_N;
extern int32_t *_array_M_exc__indices;
extern const int _num__array_M_exc__indices;
extern double *_array_M_exc_a;
extern const int _num__array_M_exc_a;
extern double *_array_M_exc_b;
extern const int _num__array_M_exc_b;
extern double *_array_M_exc_C;
extern const int _num__array_M_exc_C;
extern double *_array_M_exc_DeltaT;
extern const int _num__array_M_exc_DeltaT;
extern double *_array_M_exc_EEx;
extern const int _num__array_M_exc_EEx;
extern double *_array_M_exc_EIn;
extern const int _num__array_M_exc_EIn;
extern double *_array_M_exc_EL;
extern const int _num__array_M_exc_EL;
extern double *_array_M_exc_ge;
extern const int _num__array_M_exc_ge;
extern double *_array_M_exc_gi;
extern const int _num__array_M_exc_gi;
extern double *_array_M_exc_gL;
extern const int _num__array_M_exc_gL;
extern double *_array_M_exc_I;
extern const int _num__array_M_exc_I;
extern double *_array_M_exc_I_AMPA;
extern const int _num__array_M_exc_I_AMPA;
extern double *_array_M_exc_I_GABA;
extern const int _num__array_M_exc_I_GABA;
extern double *_array_M_exc_I_total;
extern const int _num__array_M_exc_I_total;
extern int32_t *_array_M_exc_N;
extern const int _num__array_M_exc_N;
extern double *_array_M_exc_tau_w;
extern const int _num__array_M_exc_tau_w;
extern double *_array_M_exc_v;
extern const int _num__array_M_exc_v;
extern double *_array_M_exc_Vr;
extern const int _num__array_M_exc_Vr;
extern double *_array_M_exc_VT;
extern const int _num__array_M_exc_VT;
extern double *_array_M_exc_w;
extern const int _num__array_M_exc_w;
extern int32_t *_array_M_inh__indices;
extern const int _num__array_M_inh__indices;
extern double *_array_M_inh_a;
extern const int _num__array_M_inh_a;
extern double *_array_M_inh_b;
extern const int _num__array_M_inh_b;
extern double *_array_M_inh_C;
extern const int _num__array_M_inh_C;
extern double *_array_M_inh_DeltaT;
extern const int _num__array_M_inh_DeltaT;
extern double *_array_M_inh_EEx;
extern const int _num__array_M_inh_EEx;
extern double *_array_M_inh_EIn;
extern const int _num__array_M_inh_EIn;
extern double *_array_M_inh_EL;
extern const int _num__array_M_inh_EL;
extern double *_array_M_inh_ge;
extern const int _num__array_M_inh_ge;
extern double *_array_M_inh_gi;
extern const int _num__array_M_inh_gi;
extern double *_array_M_inh_gL;
extern const int _num__array_M_inh_gL;
extern double *_array_M_inh_I;
extern const int _num__array_M_inh_I;
extern double *_array_M_inh_I_AMPA;
extern const int _num__array_M_inh_I_AMPA;
extern double *_array_M_inh_I_GABA;
extern const int _num__array_M_inh_I_GABA;
extern double *_array_M_inh_I_total;
extern const int _num__array_M_inh_I_total;
extern int32_t *_array_M_inh_N;
extern const int _num__array_M_inh_N;
extern double *_array_M_inh_tau_w;
extern const int _num__array_M_inh_tau_w;
extern double *_array_M_inh_v;
extern const int _num__array_M_inh_v;
extern double *_array_M_inh_Vr;
extern const int _num__array_M_inh_Vr;
extern double *_array_M_inh_VT;
extern const int _num__array_M_inh_VT;
extern double *_array_M_inh_w;
extern const int _num__array_M_inh_w;
extern int32_t *_array_M_syn__indices;
extern const int _num__array_M_syn__indices;
extern double *_array_M_syn_g;
extern const int _num__array_M_syn_g;
extern int32_t *_array_M_syn_N;
extern const int _num__array_M_syn_N;
extern double *_array_M_syn_tau_inact;
extern const int _num__array_M_syn_tau_inact;
extern double *_array_M_syn_weight;
extern const int _num__array_M_syn_weight;
extern int32_t *_array_S__source_idx;
extern const int _num__array_S__source_idx;
extern int32_t *_array_S_count;
extern const int _num__array_S_count;
extern int32_t *_array_S_N;
extern const int _num__array_S_N;

//////////////// dynamic arrays 2d /////////
extern DynamicArray2D<double> _dynamic_array_M_exc_a;
extern DynamicArray2D<double> _dynamic_array_M_exc_b;
extern DynamicArray2D<double> _dynamic_array_M_exc_C;
extern DynamicArray2D<double> _dynamic_array_M_exc_DeltaT;
extern DynamicArray2D<double> _dynamic_array_M_exc_EEx;
extern DynamicArray2D<double> _dynamic_array_M_exc_EIn;
extern DynamicArray2D<double> _dynamic_array_M_exc_EL;
extern DynamicArray2D<double> _dynamic_array_M_exc_ge;
extern DynamicArray2D<double> _dynamic_array_M_exc_gi;
extern DynamicArray2D<double> _dynamic_array_M_exc_gL;
extern DynamicArray2D<double> _dynamic_array_M_exc_I;
extern DynamicArray2D<double> _dynamic_array_M_exc_I_AMPA;
extern DynamicArray2D<double> _dynamic_array_M_exc_I_GABA;
extern DynamicArray2D<double> _dynamic_array_M_exc_I_total;
extern DynamicArray2D<double> _dynamic_array_M_exc_tau_w;
extern DynamicArray2D<double> _dynamic_array_M_exc_v;
extern DynamicArray2D<double> _dynamic_array_M_exc_Vr;
extern DynamicArray2D<double> _dynamic_array_M_exc_VT;
extern DynamicArray2D<double> _dynamic_array_M_exc_w;
extern DynamicArray2D<double> _dynamic_array_M_inh_a;
extern DynamicArray2D<double> _dynamic_array_M_inh_b;
extern DynamicArray2D<double> _dynamic_array_M_inh_C;
extern DynamicArray2D<double> _dynamic_array_M_inh_DeltaT;
extern DynamicArray2D<double> _dynamic_array_M_inh_EEx;
extern DynamicArray2D<double> _dynamic_array_M_inh_EIn;
extern DynamicArray2D<double> _dynamic_array_M_inh_EL;
extern DynamicArray2D<double> _dynamic_array_M_inh_ge;
extern DynamicArray2D<double> _dynamic_array_M_inh_gi;
extern DynamicArray2D<double> _dynamic_array_M_inh_gL;
extern DynamicArray2D<double> _dynamic_array_M_inh_I;
extern DynamicArray2D<double> _dynamic_array_M_inh_I_AMPA;
extern DynamicArray2D<double> _dynamic_array_M_inh_I_GABA;
extern DynamicArray2D<double> _dynamic_array_M_inh_I_total;
extern DynamicArray2D<double> _dynamic_array_M_inh_tau_w;
extern DynamicArray2D<double> _dynamic_array_M_inh_v;
extern DynamicArray2D<double> _dynamic_array_M_inh_Vr;
extern DynamicArray2D<double> _dynamic_array_M_inh_VT;
extern DynamicArray2D<double> _dynamic_array_M_inh_w;
extern DynamicArray2D<double> _dynamic_array_M_syn_g;
extern DynamicArray2D<double> _dynamic_array_M_syn_tau_inact;
extern DynamicArray2D<double> _dynamic_array_M_syn_weight;

/////////////// static arrays /////////////
extern int32_t *_static_array__array_M_exc__indices;
extern const int _num__static_array__array_M_exc__indices;
extern int32_t *_static_array__array_M_inh__indices;
extern const int _num__static_array__array_M_inh__indices;
extern int32_t *_static_array__array_M_syn__indices;
extern const int _num__static_array__array_M_syn__indices;

//////////////// synapses /////////////////
// exc_feedback_synapses
extern SynapticPathway exc_feedback_synapses_pre;
// exc_recurrent_synapses
extern SynapticPathway exc_recurrent_synapses_pre;
// inh_synapses
extern SynapticPathway inh_synapses_pre;

// Profiling information for each code object
}

void _init_arrays();
void _load_arrays();
void _write_arrays();
void _dealloc_arrays();

#endif


