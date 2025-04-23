#include <stdlib.h>
#include "objects.h"
#include <ctime>
#include <time.h>

#include "run.h"
#include "brianlib/common_math.h"

#include "code_objects/exc_feedback_synapses_pre_codeobject.h"
#include "code_objects/exc_feedback_synapses_pre_push_spikes.h"
#include "code_objects/before_run_exc_feedback_synapses_pre_push_spikes.h"
#include "code_objects/exc_feedback_synapses_stateupdater_codeobject.h"
#include "code_objects/exc_feedback_synapses_summed_variable_ge_post_codeobject.h"
#include "code_objects/exc_feedback_synapses_synapses_create_generator_codeobject.h"
#include "code_objects/exc_neurons_group_variable_set_conditional_codeobject.h"
#include "code_objects/exc_neurons_group_variable_set_conditional_codeobject_1.h"
#include "code_objects/exc_neurons_spike_resetter_codeobject.h"
#include "code_objects/exc_neurons_spike_thresholder_codeobject.h"
#include "code_objects/after_run_exc_neurons_spike_thresholder_codeobject.h"
#include "code_objects/exc_neurons_stateupdater_codeobject.h"
#include "code_objects/exc_recurrent_synapses_pre_codeobject.h"
#include "code_objects/exc_recurrent_synapses_pre_push_spikes.h"
#include "code_objects/before_run_exc_recurrent_synapses_pre_push_spikes.h"
#include "code_objects/exc_recurrent_synapses_stateupdater_codeobject.h"
#include "code_objects/exc_recurrent_synapses_summed_variable_ge_post_codeobject.h"
#include "code_objects/exc_recurrent_synapses_synapses_create_generator_codeobject.h"
#include "code_objects/inh_neurons_group_variable_set_conditional_codeobject.h"
#include "code_objects/inh_neurons_group_variable_set_conditional_codeobject_1.h"
#include "code_objects/inh_neurons_spike_resetter_codeobject.h"
#include "code_objects/inh_neurons_spike_thresholder_codeobject.h"
#include "code_objects/after_run_inh_neurons_spike_thresholder_codeobject.h"
#include "code_objects/inh_neurons_stateupdater_codeobject.h"
#include "code_objects/inh_synapses_pre_codeobject.h"
#include "code_objects/inh_synapses_pre_push_spikes.h"
#include "code_objects/before_run_inh_synapses_pre_push_spikes.h"
#include "code_objects/inh_synapses_stateupdater_codeobject.h"
#include "code_objects/inh_synapses_summed_variable_gi_post_codeobject.h"
#include "code_objects/inh_synapses_synapses_create_generator_codeobject.h"
#include "code_objects/M_exc_codeobject.h"
#include "code_objects/M_inh_codeobject.h"
#include "code_objects/M_syn_codeobject.h"
#include "code_objects/S_codeobject.h"


#include <iostream>
#include <fstream>
#include <string>




void set_from_command_line(const std::vector<std::string> args)
{
    for (const auto& arg : args) {
		// Split into two parts
		size_t equal_sign = arg.find("=");
		auto name = arg.substr(0, equal_sign);
		auto value = arg.substr(equal_sign + 1, arg.length());
		brian::set_variable_by_name(name, value);
	}
}
int main(int argc, char **argv)
{
	std::random_device _rd;
	std::vector<std::string> args(argv + 1, argv + argc);
	if (args.size() >=2 && args[0] == "--results_dir")
	{
		brian::results_dir = args[1];
		#ifdef DEBUG
		std::cout << "Setting results dir to '" << brian::results_dir << "'" << std::endl;
		#endif
		args.erase(args.begin(), args.begin()+2);
	}
        

	brian_start();
        

	{
		using namespace brian;

		
                
        _array_defaultclock_dt[0] = 0.0001;
        _array_defaultclock_dt[0] = 0.0001;
        _array_defaultclock_dt[0] = 0.0001;
        _array_exc_neurons_clock_dt[0] = 0.0001;
        _array_exc_neurons_clock_dt[0] = 0.0001;
        _array_inh_neurons_clock_dt[0] = 0.0001;
        _array_inh_neurons_clock_dt[0] = 0.0001;
        _run_exc_neurons_group_variable_set_conditional_codeobject();
        _run_exc_neurons_group_variable_set_conditional_codeobject_1();
        _run_inh_neurons_group_variable_set_conditional_codeobject();
        _run_inh_neurons_group_variable_set_conditional_codeobject_1();
        
                        
                        for(int i=0; i<_num__array_exc_neurons_gL; i++)
                        {
                            _array_exc_neurons_gL[i] = 1e-08;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_inh_neurons_gL; i++)
                        {
                            _array_inh_neurons_gL[i] = 1e-08;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_exc_neurons_EL; i++)
                        {
                            _array_exc_neurons_EL[i] = - 0.07;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_inh_neurons_EL; i++)
                        {
                            _array_inh_neurons_EL[i] = - 0.07;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_exc_neurons_VT; i++)
                        {
                            _array_exc_neurons_VT[i] = - 0.0504;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_inh_neurons_VT; i++)
                        {
                            _array_inh_neurons_VT[i] = - 0.0504;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_exc_neurons_Vr; i++)
                        {
                            _array_exc_neurons_Vr[i] = - 0.075;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_inh_neurons_Vr; i++)
                        {
                            _array_inh_neurons_Vr[i] = - 0.075;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_exc_neurons_tau_w; i++)
                        {
                            _array_exc_neurons_tau_w[i] = 0.04;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_inh_neurons_tau_w; i++)
                        {
                            _array_inh_neurons_tau_w[i] = 0.04;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_exc_neurons_a; i++)
                        {
                            _array_exc_neurons_a[i] = 2e-09;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_inh_neurons_a; i++)
                        {
                            _array_inh_neurons_a[i] = 2e-09;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_exc_neurons_b; i++)
                        {
                            _array_exc_neurons_b[i] = 8.05e-12;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_inh_neurons_b; i++)
                        {
                            _array_inh_neurons_b[i] = 8.05e-12;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_exc_neurons_DeltaT; i++)
                        {
                            _array_exc_neurons_DeltaT[i] = 0.002;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_inh_neurons_DeltaT; i++)
                        {
                            _array_inh_neurons_DeltaT[i] = 0.002;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_exc_neurons_C; i++)
                        {
                            _array_exc_neurons_C[i] = 2e-11;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_inh_neurons_C; i++)
                        {
                            _array_inh_neurons_C[i] = 2e-11;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_exc_neurons_EEx; i++)
                        {
                            _array_exc_neurons_EEx[i] = 0.0;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_inh_neurons_EEx; i++)
                        {
                            _array_inh_neurons_EEx[i] = 0.0;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_exc_neurons_EIn; i++)
                        {
                            _array_exc_neurons_EIn[i] = - 0.07;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_inh_neurons_EIn; i++)
                        {
                            _array_inh_neurons_EIn[i] = - 0.07;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_inh_neurons_C; i++)
                        {
                            _array_inh_neurons_C[i] = 1e-12;
                        }
                        
        _array_exc_recurrent_synapses_clock_dt[0] = 0.0001;
        _array_exc_recurrent_synapses_clock_dt[0] = 0.0001;
        _dynamic_array_exc_recurrent_synapses_delay.resize(1);
        _dynamic_array_exc_recurrent_synapses_delay.resize(1);
        _dynamic_array_exc_recurrent_synapses_delay[0] = 0.002;
        _run_exc_recurrent_synapses_synapses_create_generator_codeobject();
        
                        
                        for(int i=0; i<_dynamic_array_exc_recurrent_synapses_tau_inact.size(); i++)
                        {
                            _dynamic_array_exc_recurrent_synapses_tau_inact[i] = 0.02;
                        }
                        
        _array_exc_feedback_synapses_clock_dt[0] = 0.0001;
        _array_exc_feedback_synapses_clock_dt[0] = 0.0001;
        _run_exc_feedback_synapses_synapses_create_generator_codeobject();
        
                        
                        for(int i=0; i<_dynamic_array_exc_feedback_synapses_tau_inact.size(); i++)
                        {
                            _dynamic_array_exc_feedback_synapses_tau_inact[i] = 0.02;
                        }
                        
        _array_inh_synapses_clock_dt[0] = 0.0001;
        _array_inh_synapses_clock_dt[0] = 0.0001;
        _run_inh_synapses_synapses_create_generator_codeobject();
        
                        
                        for(int i=0; i<_dynamic_array_inh_synapses_tau_inact.size(); i++)
                        {
                            _dynamic_array_inh_synapses_tau_inact[i] = 0.1;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_M_exc__indices; i++)
                        {
                            _array_M_exc__indices[i] = _static_array__array_M_exc__indices[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_M_inh__indices; i++)
                        {
                            _array_M_inh__indices[i] = _static_array__array_M_inh__indices[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_M_syn__indices; i++)
                        {
                            _array_M_syn__indices[i] = _static_array__array_M_syn__indices[i];
                        }
                        
        _array_exc_feedback_synapses_clock_timestep[0] = 0;
        _array_exc_feedback_synapses_clock_t[0] = 0.0;
        _array_inh_synapses_clock_timestep[0] = 0;
        _array_inh_synapses_clock_t[0] = 0.0;
        _array_exc_recurrent_synapses_clock_timestep[0] = 0;
        _array_exc_recurrent_synapses_clock_t[0] = 0.0;
        _array_inh_neurons_clock_timestep[0] = 0;
        _array_inh_neurons_clock_t[0] = 0.0;
        _array_exc_neurons_clock_timestep[0] = 0;
        _array_exc_neurons_clock_t[0] = 0.0;
        _before_run_exc_feedback_synapses_pre_push_spikes();
        _before_run_exc_recurrent_synapses_pre_push_spikes();
        _before_run_inh_synapses_pre_push_spikes();
        network.clear();
        network.add(&exc_neurons_clock, _run_M_exc_codeobject);
        network.add(&inh_neurons_clock, _run_M_inh_codeobject);
        network.add(&exc_recurrent_synapses_clock, _run_M_syn_codeobject);
        network.add(&inh_neurons_clock, _run_exc_feedback_synapses_summed_variable_ge_post_codeobject);
        network.add(&exc_neurons_clock, _run_exc_recurrent_synapses_summed_variable_ge_post_codeobject);
        network.add(&exc_neurons_clock, _run_inh_synapses_summed_variable_gi_post_codeobject);
        network.add(&exc_feedback_synapses_clock, _run_exc_feedback_synapses_stateupdater_codeobject);
        network.add(&exc_neurons_clock, _run_exc_neurons_stateupdater_codeobject);
        network.add(&exc_recurrent_synapses_clock, _run_exc_recurrent_synapses_stateupdater_codeobject);
        network.add(&inh_neurons_clock, _run_inh_neurons_stateupdater_codeobject);
        network.add(&inh_synapses_clock, _run_inh_synapses_stateupdater_codeobject);
        network.add(&exc_neurons_clock, _run_exc_neurons_spike_thresholder_codeobject);
        network.add(&inh_neurons_clock, _run_inh_neurons_spike_thresholder_codeobject);
        network.add(&exc_neurons_clock, _run_S_codeobject);
        network.add(&exc_neurons_clock, _run_exc_feedback_synapses_pre_push_spikes);
        network.add(&exc_neurons_clock, _run_exc_feedback_synapses_pre_codeobject);
        network.add(&exc_neurons_clock, _run_exc_recurrent_synapses_pre_push_spikes);
        network.add(&exc_neurons_clock, _run_exc_recurrent_synapses_pre_codeobject);
        network.add(&inh_neurons_clock, _run_inh_synapses_pre_push_spikes);
        network.add(&inh_neurons_clock, _run_inh_synapses_pre_codeobject);
        network.add(&exc_neurons_clock, _run_exc_neurons_spike_resetter_codeobject);
        network.add(&inh_neurons_clock, _run_inh_neurons_spike_resetter_codeobject);
        set_from_command_line(args);
        network.run(2.0, NULL, 10.0);
        _after_run_exc_neurons_spike_thresholder_codeobject();
        _after_run_inh_neurons_spike_thresholder_codeobject();
        #ifdef DEBUG
        _debugmsg_S_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_exc_feedback_synapses_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_exc_recurrent_synapses_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_inh_synapses_pre_codeobject();
        #endif

	}
        

	brian_end();
        

	return 0;
}