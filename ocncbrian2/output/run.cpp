#include<stdlib.h>
#include "objects.h"
#include<ctime>
#include<random>

#include "code_objects/exc_feedback_synapses_pre_codeobject.h"
#include "code_objects/exc_feedback_synapses_pre_push_spikes.h"
#include "code_objects/exc_feedback_synapses_stateupdater_codeobject.h"
#include "code_objects/exc_feedback_synapses_summed_variable_ge_post_codeobject.h"
#include "code_objects/exc_feedback_synapses_synapses_create_generator_codeobject.h"
#include "code_objects/exc_neurons_group_variable_set_conditional_codeobject.h"
#include "code_objects/exc_neurons_group_variable_set_conditional_codeobject_1.h"
#include "code_objects/exc_neurons_spike_resetter_codeobject.h"
#include "code_objects/exc_neurons_spike_thresholder_codeobject.h"
#include "code_objects/exc_neurons_stateupdater_codeobject.h"
#include "code_objects/exc_recurrent_synapses_pre_codeobject.h"
#include "code_objects/exc_recurrent_synapses_pre_push_spikes.h"
#include "code_objects/exc_recurrent_synapses_stateupdater_codeobject.h"
#include "code_objects/exc_recurrent_synapses_summed_variable_ge_post_codeobject.h"
#include "code_objects/exc_recurrent_synapses_synapses_create_generator_codeobject.h"
#include "code_objects/inh_neurons_group_variable_set_conditional_codeobject.h"
#include "code_objects/inh_neurons_group_variable_set_conditional_codeobject_1.h"
#include "code_objects/inh_neurons_spike_resetter_codeobject.h"
#include "code_objects/inh_neurons_spike_thresholder_codeobject.h"
#include "code_objects/inh_neurons_stateupdater_codeobject.h"
#include "code_objects/inh_synapses_pre_codeobject.h"
#include "code_objects/inh_synapses_pre_push_spikes.h"
#include "code_objects/inh_synapses_stateupdater_codeobject.h"
#include "code_objects/inh_synapses_summed_variable_gi_post_codeobject.h"
#include "code_objects/inh_synapses_synapses_create_generator_codeobject.h"
#include "code_objects/M_exc_codeobject.h"
#include "code_objects/M_inh_codeobject.h"
#include "code_objects/M_syn_codeobject.h"
#include "code_objects/S_codeobject.h"


void brian_start()
{
	_init_arrays();
	_load_arrays();
	// Initialize clocks (link timestep and dt to the respective arrays)
    brian::exc_feedback_synapses_clock.timestep = brian::_array_exc_feedback_synapses_clock_timestep;
    brian::exc_feedback_synapses_clock.dt = brian::_array_exc_feedback_synapses_clock_dt;
    brian::exc_feedback_synapses_clock.t = brian::_array_exc_feedback_synapses_clock_t;
    brian::exc_neurons_clock.timestep = brian::_array_exc_neurons_clock_timestep;
    brian::exc_neurons_clock.dt = brian::_array_exc_neurons_clock_dt;
    brian::exc_neurons_clock.t = brian::_array_exc_neurons_clock_t;
    brian::exc_recurrent_synapses_clock.timestep = brian::_array_exc_recurrent_synapses_clock_timestep;
    brian::exc_recurrent_synapses_clock.dt = brian::_array_exc_recurrent_synapses_clock_dt;
    brian::exc_recurrent_synapses_clock.t = brian::_array_exc_recurrent_synapses_clock_t;
    brian::inh_neurons_clock.timestep = brian::_array_inh_neurons_clock_timestep;
    brian::inh_neurons_clock.dt = brian::_array_inh_neurons_clock_dt;
    brian::inh_neurons_clock.t = brian::_array_inh_neurons_clock_t;
    brian::inh_synapses_clock.timestep = brian::_array_inh_synapses_clock_timestep;
    brian::inh_synapses_clock.dt = brian::_array_inh_synapses_clock_dt;
    brian::inh_synapses_clock.t = brian::_array_inh_synapses_clock_t;
}

void brian_end()
{
	_write_arrays();
	_dealloc_arrays();
}


