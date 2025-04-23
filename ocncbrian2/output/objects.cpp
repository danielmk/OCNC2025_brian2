

#include "objects.h"
#include "synapses_classes.h"
#include "brianlib/clocks.h"
#include "brianlib/dynamic_array.h"
#include "brianlib/stdint_compat.h"
#include "network.h"
#include<random>
#include<vector>
#include<iostream>
#include<fstream>
#include<map>
#include<tuple>
#include<cstdlib>
#include<string>

namespace brian {

std::string results_dir = "results/";  // can be overwritten by --results_dir command line arg

// For multhreading, we need one generator for each thread. We also create a distribution for
// each thread, even though this is not strictly necessary for the uniform distribution, as
// the distribution is stateless.
std::vector< RandomGenerator > _random_generators;

//////////////// networks /////////////////
Network network;

void set_variable_from_value(std::string varname, char* var_pointer, size_t size, char value) {
    #ifdef DEBUG
    std::cout << "Setting '" << varname << "' to " << (value == 1 ? "True" : "False") << std::endl;
    #endif
    std::fill(var_pointer, var_pointer+size, value);
}

template<class T> void set_variable_from_value(std::string varname, T* var_pointer, size_t size, T value) {
    #ifdef DEBUG
    std::cout << "Setting '" << varname << "' to " << value << std::endl;
    #endif
    std::fill(var_pointer, var_pointer+size, value);
}

template<class T> void set_variable_from_file(std::string varname, T* var_pointer, size_t data_size, std::string filename) {
    ifstream f;
    streampos size;
    #ifdef DEBUG
    std::cout << "Setting '" << varname << "' from file '" << filename << "'" << std::endl;
    #endif
    f.open(filename, ios::in | ios::binary | ios::ate);
    size = f.tellg();
    if (size != data_size) {
        std::cerr << "Error reading '" << filename << "': file size " << size << " does not match expected size " << data_size << std::endl;
        return;
    }
    f.seekg(0, ios::beg);
    if (f.is_open())
        f.read(reinterpret_cast<char *>(var_pointer), data_size);
    else
        std::cerr << "Could not read '" << filename << "'" << std::endl;
    if (f.fail())
        std::cerr << "Error reading '" << filename << "'" << std::endl;
}

//////////////// set arrays by name ///////
void set_variable_by_name(std::string name, std::string s_value) {
    size_t var_size;
    size_t data_size;
    // C-style or Python-style capitalization is allowed for boolean values
    if (s_value == "true" || s_value == "True")
        s_value = "1";
    else if (s_value == "false" || s_value == "False")
        s_value = "0";
    // non-dynamic arrays
    if (name == "exc_neurons._spikespace") {
        var_size = 501;
        data_size = 501*sizeof(int32_t);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<int32_t>(name, _array_exc_neurons__spikespace, var_size, (int32_t)atoi(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_exc_neurons__spikespace, data_size, s_value);
        }
        return;
    }
    if (name == "exc_neurons.a") {
        var_size = 500;
        data_size = 500*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_exc_neurons_a, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_exc_neurons_a, data_size, s_value);
        }
        return;
    }
    if (name == "exc_neurons.b") {
        var_size = 500;
        data_size = 500*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_exc_neurons_b, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_exc_neurons_b, data_size, s_value);
        }
        return;
    }
    if (name == "exc_neurons.C") {
        var_size = 500;
        data_size = 500*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_exc_neurons_C, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_exc_neurons_C, data_size, s_value);
        }
        return;
    }
    if (name == "exc_neurons.DeltaT") {
        var_size = 500;
        data_size = 500*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_exc_neurons_DeltaT, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_exc_neurons_DeltaT, data_size, s_value);
        }
        return;
    }
    if (name == "exc_neurons.EEx") {
        var_size = 500;
        data_size = 500*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_exc_neurons_EEx, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_exc_neurons_EEx, data_size, s_value);
        }
        return;
    }
    if (name == "exc_neurons.EIn") {
        var_size = 500;
        data_size = 500*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_exc_neurons_EIn, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_exc_neurons_EIn, data_size, s_value);
        }
        return;
    }
    if (name == "exc_neurons.EL") {
        var_size = 500;
        data_size = 500*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_exc_neurons_EL, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_exc_neurons_EL, data_size, s_value);
        }
        return;
    }
    if (name == "exc_neurons.ge") {
        var_size = 500;
        data_size = 500*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_exc_neurons_ge, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_exc_neurons_ge, data_size, s_value);
        }
        return;
    }
    if (name == "exc_neurons.gi") {
        var_size = 500;
        data_size = 500*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_exc_neurons_gi, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_exc_neurons_gi, data_size, s_value);
        }
        return;
    }
    if (name == "exc_neurons.gL") {
        var_size = 500;
        data_size = 500*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_exc_neurons_gL, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_exc_neurons_gL, data_size, s_value);
        }
        return;
    }
    if (name == "exc_neurons.I") {
        var_size = 500;
        data_size = 500*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_exc_neurons_I, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_exc_neurons_I, data_size, s_value);
        }
        return;
    }
    if (name == "exc_neurons.tau_w") {
        var_size = 500;
        data_size = 500*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_exc_neurons_tau_w, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_exc_neurons_tau_w, data_size, s_value);
        }
        return;
    }
    if (name == "exc_neurons.v") {
        var_size = 500;
        data_size = 500*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_exc_neurons_v, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_exc_neurons_v, data_size, s_value);
        }
        return;
    }
    if (name == "exc_neurons.Vr") {
        var_size = 500;
        data_size = 500*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_exc_neurons_Vr, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_exc_neurons_Vr, data_size, s_value);
        }
        return;
    }
    if (name == "exc_neurons.VT") {
        var_size = 500;
        data_size = 500*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_exc_neurons_VT, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_exc_neurons_VT, data_size, s_value);
        }
        return;
    }
    if (name == "exc_neurons.w") {
        var_size = 500;
        data_size = 500*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_exc_neurons_w, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_exc_neurons_w, data_size, s_value);
        }
        return;
    }
    if (name == "inh_neurons._spikespace") {
        var_size = 101;
        data_size = 101*sizeof(int32_t);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<int32_t>(name, _array_inh_neurons__spikespace, var_size, (int32_t)atoi(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_inh_neurons__spikespace, data_size, s_value);
        }
        return;
    }
    if (name == "inh_neurons.a") {
        var_size = 100;
        data_size = 100*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_inh_neurons_a, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_inh_neurons_a, data_size, s_value);
        }
        return;
    }
    if (name == "inh_neurons.b") {
        var_size = 100;
        data_size = 100*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_inh_neurons_b, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_inh_neurons_b, data_size, s_value);
        }
        return;
    }
    if (name == "inh_neurons.C") {
        var_size = 100;
        data_size = 100*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_inh_neurons_C, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_inh_neurons_C, data_size, s_value);
        }
        return;
    }
    if (name == "inh_neurons.DeltaT") {
        var_size = 100;
        data_size = 100*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_inh_neurons_DeltaT, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_inh_neurons_DeltaT, data_size, s_value);
        }
        return;
    }
    if (name == "inh_neurons.EEx") {
        var_size = 100;
        data_size = 100*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_inh_neurons_EEx, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_inh_neurons_EEx, data_size, s_value);
        }
        return;
    }
    if (name == "inh_neurons.EIn") {
        var_size = 100;
        data_size = 100*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_inh_neurons_EIn, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_inh_neurons_EIn, data_size, s_value);
        }
        return;
    }
    if (name == "inh_neurons.EL") {
        var_size = 100;
        data_size = 100*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_inh_neurons_EL, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_inh_neurons_EL, data_size, s_value);
        }
        return;
    }
    if (name == "inh_neurons.ge") {
        var_size = 100;
        data_size = 100*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_inh_neurons_ge, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_inh_neurons_ge, data_size, s_value);
        }
        return;
    }
    if (name == "inh_neurons.gi") {
        var_size = 100;
        data_size = 100*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_inh_neurons_gi, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_inh_neurons_gi, data_size, s_value);
        }
        return;
    }
    if (name == "inh_neurons.gL") {
        var_size = 100;
        data_size = 100*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_inh_neurons_gL, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_inh_neurons_gL, data_size, s_value);
        }
        return;
    }
    if (name == "inh_neurons.I") {
        var_size = 100;
        data_size = 100*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_inh_neurons_I, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_inh_neurons_I, data_size, s_value);
        }
        return;
    }
    if (name == "inh_neurons.tau_w") {
        var_size = 100;
        data_size = 100*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_inh_neurons_tau_w, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_inh_neurons_tau_w, data_size, s_value);
        }
        return;
    }
    if (name == "inh_neurons.v") {
        var_size = 100;
        data_size = 100*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_inh_neurons_v, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_inh_neurons_v, data_size, s_value);
        }
        return;
    }
    if (name == "inh_neurons.Vr") {
        var_size = 100;
        data_size = 100*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_inh_neurons_Vr, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_inh_neurons_Vr, data_size, s_value);
        }
        return;
    }
    if (name == "inh_neurons.VT") {
        var_size = 100;
        data_size = 100*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_inh_neurons_VT, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_inh_neurons_VT, data_size, s_value);
        }
        return;
    }
    if (name == "inh_neurons.w") {
        var_size = 100;
        data_size = 100*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, _array_inh_neurons_w, var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, _array_inh_neurons_w, data_size, s_value);
        }
        return;
    }
    // dynamic arrays (1d)
    if (name == "exc_feedback_synapses.delay") {
        var_size = _dynamic_array_exc_feedback_synapses_delay.size();
        data_size = var_size*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, &_dynamic_array_exc_feedback_synapses_delay[0], var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, &_dynamic_array_exc_feedback_synapses_delay[0], data_size, s_value);
        }
        return;
    }
    if (name == "exc_feedback_synapses.g") {
        var_size = _dynamic_array_exc_feedback_synapses_g.size();
        data_size = var_size*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, &_dynamic_array_exc_feedback_synapses_g[0], var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, &_dynamic_array_exc_feedback_synapses_g[0], data_size, s_value);
        }
        return;
    }
    if (name == "exc_feedback_synapses.tau_inact") {
        var_size = _dynamic_array_exc_feedback_synapses_tau_inact.size();
        data_size = var_size*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, &_dynamic_array_exc_feedback_synapses_tau_inact[0], var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, &_dynamic_array_exc_feedback_synapses_tau_inact[0], data_size, s_value);
        }
        return;
    }
    if (name == "exc_feedback_synapses.weight") {
        var_size = _dynamic_array_exc_feedback_synapses_weight.size();
        data_size = var_size*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, &_dynamic_array_exc_feedback_synapses_weight[0], var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, &_dynamic_array_exc_feedback_synapses_weight[0], data_size, s_value);
        }
        return;
    }
    if (name == "exc_recurrent_synapses.delay") {
        var_size = _dynamic_array_exc_recurrent_synapses_delay.size();
        data_size = var_size*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, &_dynamic_array_exc_recurrent_synapses_delay[0], var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, &_dynamic_array_exc_recurrent_synapses_delay[0], data_size, s_value);
        }
        return;
    }
    if (name == "exc_recurrent_synapses.g") {
        var_size = _dynamic_array_exc_recurrent_synapses_g.size();
        data_size = var_size*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, &_dynamic_array_exc_recurrent_synapses_g[0], var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, &_dynamic_array_exc_recurrent_synapses_g[0], data_size, s_value);
        }
        return;
    }
    if (name == "exc_recurrent_synapses.tau_inact") {
        var_size = _dynamic_array_exc_recurrent_synapses_tau_inact.size();
        data_size = var_size*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, &_dynamic_array_exc_recurrent_synapses_tau_inact[0], var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, &_dynamic_array_exc_recurrent_synapses_tau_inact[0], data_size, s_value);
        }
        return;
    }
    if (name == "exc_recurrent_synapses.weight") {
        var_size = _dynamic_array_exc_recurrent_synapses_weight.size();
        data_size = var_size*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, &_dynamic_array_exc_recurrent_synapses_weight[0], var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, &_dynamic_array_exc_recurrent_synapses_weight[0], data_size, s_value);
        }
        return;
    }
    if (name == "inh_synapses.delay") {
        var_size = _dynamic_array_inh_synapses_delay.size();
        data_size = var_size*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, &_dynamic_array_inh_synapses_delay[0], var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, &_dynamic_array_inh_synapses_delay[0], data_size, s_value);
        }
        return;
    }
    if (name == "inh_synapses.g") {
        var_size = _dynamic_array_inh_synapses_g.size();
        data_size = var_size*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, &_dynamic_array_inh_synapses_g[0], var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, &_dynamic_array_inh_synapses_g[0], data_size, s_value);
        }
        return;
    }
    if (name == "inh_synapses.tau_inact") {
        var_size = _dynamic_array_inh_synapses_tau_inact.size();
        data_size = var_size*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, &_dynamic_array_inh_synapses_tau_inact[0], var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, &_dynamic_array_inh_synapses_tau_inact[0], data_size, s_value);
        }
        return;
    }
    if (name == "inh_synapses.weight") {
        var_size = _dynamic_array_inh_synapses_weight.size();
        data_size = var_size*sizeof(double);
        if (s_value[0] == '-' || (s_value[0] >= '0' && s_value[0] <= '9')) {
            // set from single value
            set_variable_from_value<double>(name, &_dynamic_array_inh_synapses_weight[0], var_size, (double)atof(s_value.c_str()));

        } else {
            // set from file
            set_variable_from_file(name, &_dynamic_array_inh_synapses_weight[0], data_size, s_value);
        }
        return;
    }
    std::cerr << "Cannot set unknown variable '" << name << "'." << std::endl;
    exit(1);
}
//////////////// arrays ///////////////////
double * _array_defaultclock_dt;
const int _num__array_defaultclock_dt = 1;
double * _array_defaultclock_t;
const int _num__array_defaultclock_t = 1;
int64_t * _array_defaultclock_timestep;
const int _num__array_defaultclock_timestep = 1;
double * _array_exc_feedback_synapses_clock_dt;
const int _num__array_exc_feedback_synapses_clock_dt = 1;
double * _array_exc_feedback_synapses_clock_t;
const int _num__array_exc_feedback_synapses_clock_t = 1;
int64_t * _array_exc_feedback_synapses_clock_timestep;
const int _num__array_exc_feedback_synapses_clock_timestep = 1;
int32_t * _array_exc_feedback_synapses_N;
const int _num__array_exc_feedback_synapses_N = 1;
int32_t * _array_exc_neurons__spikespace;
const int _num__array_exc_neurons__spikespace = 501;
double * _array_exc_neurons_a;
const int _num__array_exc_neurons_a = 500;
double * _array_exc_neurons_b;
const int _num__array_exc_neurons_b = 500;
double * _array_exc_neurons_C;
const int _num__array_exc_neurons_C = 500;
double * _array_exc_neurons_clock_dt;
const int _num__array_exc_neurons_clock_dt = 1;
double * _array_exc_neurons_clock_t;
const int _num__array_exc_neurons_clock_t = 1;
int64_t * _array_exc_neurons_clock_timestep;
const int _num__array_exc_neurons_clock_timestep = 1;
double * _array_exc_neurons_DeltaT;
const int _num__array_exc_neurons_DeltaT = 500;
double * _array_exc_neurons_EEx;
const int _num__array_exc_neurons_EEx = 500;
double * _array_exc_neurons_EIn;
const int _num__array_exc_neurons_EIn = 500;
double * _array_exc_neurons_EL;
const int _num__array_exc_neurons_EL = 500;
double * _array_exc_neurons_ge;
const int _num__array_exc_neurons_ge = 500;
double * _array_exc_neurons_gi;
const int _num__array_exc_neurons_gi = 500;
double * _array_exc_neurons_gL;
const int _num__array_exc_neurons_gL = 500;
int32_t * _array_exc_neurons_i;
const int _num__array_exc_neurons_i = 500;
double * _array_exc_neurons_I;
const int _num__array_exc_neurons_I = 500;
double * _array_exc_neurons_tau_w;
const int _num__array_exc_neurons_tau_w = 500;
double * _array_exc_neurons_v;
const int _num__array_exc_neurons_v = 500;
double * _array_exc_neurons_Vr;
const int _num__array_exc_neurons_Vr = 500;
double * _array_exc_neurons_VT;
const int _num__array_exc_neurons_VT = 500;
double * _array_exc_neurons_w;
const int _num__array_exc_neurons_w = 500;
double * _array_exc_recurrent_synapses_clock_dt;
const int _num__array_exc_recurrent_synapses_clock_dt = 1;
double * _array_exc_recurrent_synapses_clock_t;
const int _num__array_exc_recurrent_synapses_clock_t = 1;
int64_t * _array_exc_recurrent_synapses_clock_timestep;
const int _num__array_exc_recurrent_synapses_clock_timestep = 1;
int32_t * _array_exc_recurrent_synapses_N;
const int _num__array_exc_recurrent_synapses_N = 1;
int32_t * _array_inh_neurons__spikespace;
const int _num__array_inh_neurons__spikespace = 101;
double * _array_inh_neurons_a;
const int _num__array_inh_neurons_a = 100;
double * _array_inh_neurons_b;
const int _num__array_inh_neurons_b = 100;
double * _array_inh_neurons_C;
const int _num__array_inh_neurons_C = 100;
double * _array_inh_neurons_clock_dt;
const int _num__array_inh_neurons_clock_dt = 1;
double * _array_inh_neurons_clock_t;
const int _num__array_inh_neurons_clock_t = 1;
int64_t * _array_inh_neurons_clock_timestep;
const int _num__array_inh_neurons_clock_timestep = 1;
double * _array_inh_neurons_DeltaT;
const int _num__array_inh_neurons_DeltaT = 100;
double * _array_inh_neurons_EEx;
const int _num__array_inh_neurons_EEx = 100;
double * _array_inh_neurons_EIn;
const int _num__array_inh_neurons_EIn = 100;
double * _array_inh_neurons_EL;
const int _num__array_inh_neurons_EL = 100;
double * _array_inh_neurons_ge;
const int _num__array_inh_neurons_ge = 100;
double * _array_inh_neurons_gi;
const int _num__array_inh_neurons_gi = 100;
double * _array_inh_neurons_gL;
const int _num__array_inh_neurons_gL = 100;
int32_t * _array_inh_neurons_i;
const int _num__array_inh_neurons_i = 100;
double * _array_inh_neurons_I;
const int _num__array_inh_neurons_I = 100;
double * _array_inh_neurons_tau_w;
const int _num__array_inh_neurons_tau_w = 100;
double * _array_inh_neurons_v;
const int _num__array_inh_neurons_v = 100;
double * _array_inh_neurons_Vr;
const int _num__array_inh_neurons_Vr = 100;
double * _array_inh_neurons_VT;
const int _num__array_inh_neurons_VT = 100;
double * _array_inh_neurons_w;
const int _num__array_inh_neurons_w = 100;
double * _array_inh_synapses_clock_dt;
const int _num__array_inh_synapses_clock_dt = 1;
double * _array_inh_synapses_clock_t;
const int _num__array_inh_synapses_clock_t = 1;
int64_t * _array_inh_synapses_clock_timestep;
const int _num__array_inh_synapses_clock_timestep = 1;
int32_t * _array_inh_synapses_N;
const int _num__array_inh_synapses_N = 1;
int32_t * _array_M_exc__indices;
const int _num__array_M_exc__indices = 500;
double * _array_M_exc_a;
const int _num__array_M_exc_a = (0, 500);
double * _array_M_exc_b;
const int _num__array_M_exc_b = (0, 500);
double * _array_M_exc_C;
const int _num__array_M_exc_C = (0, 500);
double * _array_M_exc_DeltaT;
const int _num__array_M_exc_DeltaT = (0, 500);
double * _array_M_exc_EEx;
const int _num__array_M_exc_EEx = (0, 500);
double * _array_M_exc_EIn;
const int _num__array_M_exc_EIn = (0, 500);
double * _array_M_exc_EL;
const int _num__array_M_exc_EL = (0, 500);
double * _array_M_exc_ge;
const int _num__array_M_exc_ge = (0, 500);
double * _array_M_exc_gi;
const int _num__array_M_exc_gi = (0, 500);
double * _array_M_exc_gL;
const int _num__array_M_exc_gL = (0, 500);
double * _array_M_exc_I;
const int _num__array_M_exc_I = (0, 500);
double * _array_M_exc_I_AMPA;
const int _num__array_M_exc_I_AMPA = (0, 500);
double * _array_M_exc_I_GABA;
const int _num__array_M_exc_I_GABA = (0, 500);
double * _array_M_exc_I_total;
const int _num__array_M_exc_I_total = (0, 500);
int32_t * _array_M_exc_N;
const int _num__array_M_exc_N = 1;
double * _array_M_exc_tau_w;
const int _num__array_M_exc_tau_w = (0, 500);
double * _array_M_exc_v;
const int _num__array_M_exc_v = (0, 500);
double * _array_M_exc_Vr;
const int _num__array_M_exc_Vr = (0, 500);
double * _array_M_exc_VT;
const int _num__array_M_exc_VT = (0, 500);
double * _array_M_exc_w;
const int _num__array_M_exc_w = (0, 500);
int32_t * _array_M_inh__indices;
const int _num__array_M_inh__indices = 100;
double * _array_M_inh_a;
const int _num__array_M_inh_a = (0, 100);
double * _array_M_inh_b;
const int _num__array_M_inh_b = (0, 100);
double * _array_M_inh_C;
const int _num__array_M_inh_C = (0, 100);
double * _array_M_inh_DeltaT;
const int _num__array_M_inh_DeltaT = (0, 100);
double * _array_M_inh_EEx;
const int _num__array_M_inh_EEx = (0, 100);
double * _array_M_inh_EIn;
const int _num__array_M_inh_EIn = (0, 100);
double * _array_M_inh_EL;
const int _num__array_M_inh_EL = (0, 100);
double * _array_M_inh_ge;
const int _num__array_M_inh_ge = (0, 100);
double * _array_M_inh_gi;
const int _num__array_M_inh_gi = (0, 100);
double * _array_M_inh_gL;
const int _num__array_M_inh_gL = (0, 100);
double * _array_M_inh_I;
const int _num__array_M_inh_I = (0, 100);
double * _array_M_inh_I_AMPA;
const int _num__array_M_inh_I_AMPA = (0, 100);
double * _array_M_inh_I_GABA;
const int _num__array_M_inh_I_GABA = (0, 100);
double * _array_M_inh_I_total;
const int _num__array_M_inh_I_total = (0, 100);
int32_t * _array_M_inh_N;
const int _num__array_M_inh_N = 1;
double * _array_M_inh_tau_w;
const int _num__array_M_inh_tau_w = (0, 100);
double * _array_M_inh_v;
const int _num__array_M_inh_v = (0, 100);
double * _array_M_inh_Vr;
const int _num__array_M_inh_Vr = (0, 100);
double * _array_M_inh_VT;
const int _num__array_M_inh_VT = (0, 100);
double * _array_M_inh_w;
const int _num__array_M_inh_w = (0, 100);
int32_t * _array_M_syn__indices;
const int _num__array_M_syn__indices = 500;
double * _array_M_syn_g;
const int _num__array_M_syn_g = (0, 500);
int32_t * _array_M_syn_N;
const int _num__array_M_syn_N = 1;
double * _array_M_syn_tau_inact;
const int _num__array_M_syn_tau_inact = (0, 500);
double * _array_M_syn_weight;
const int _num__array_M_syn_weight = (0, 500);
int32_t * _array_S__source_idx;
const int _num__array_S__source_idx = 500;
int32_t * _array_S_count;
const int _num__array_S_count = 500;
int32_t * _array_S_N;
const int _num__array_S_N = 1;

//////////////// dynamic arrays 1d /////////
std::vector<int32_t> _dynamic_array_exc_feedback_synapses__synaptic_post;
std::vector<int32_t> _dynamic_array_exc_feedback_synapses__synaptic_pre;
std::vector<double> _dynamic_array_exc_feedback_synapses_delay;
std::vector<double> _dynamic_array_exc_feedback_synapses_g;
std::vector<int32_t> _dynamic_array_exc_feedback_synapses_N_incoming;
std::vector<int32_t> _dynamic_array_exc_feedback_synapses_N_outgoing;
std::vector<double> _dynamic_array_exc_feedback_synapses_tau_inact;
std::vector<double> _dynamic_array_exc_feedback_synapses_weight;
std::vector<int32_t> _dynamic_array_exc_recurrent_synapses__synaptic_post;
std::vector<int32_t> _dynamic_array_exc_recurrent_synapses__synaptic_pre;
std::vector<double> _dynamic_array_exc_recurrent_synapses_delay;
std::vector<double> _dynamic_array_exc_recurrent_synapses_g;
std::vector<int32_t> _dynamic_array_exc_recurrent_synapses_N_incoming;
std::vector<int32_t> _dynamic_array_exc_recurrent_synapses_N_outgoing;
std::vector<double> _dynamic_array_exc_recurrent_synapses_tau_inact;
std::vector<double> _dynamic_array_exc_recurrent_synapses_weight;
std::vector<int32_t> _dynamic_array_inh_synapses__synaptic_post;
std::vector<int32_t> _dynamic_array_inh_synapses__synaptic_pre;
std::vector<double> _dynamic_array_inh_synapses_delay;
std::vector<double> _dynamic_array_inh_synapses_g;
std::vector<int32_t> _dynamic_array_inh_synapses_N_incoming;
std::vector<int32_t> _dynamic_array_inh_synapses_N_outgoing;
std::vector<double> _dynamic_array_inh_synapses_tau_inact;
std::vector<double> _dynamic_array_inh_synapses_weight;
std::vector<double> _dynamic_array_M_exc_t;
std::vector<double> _dynamic_array_M_inh_t;
std::vector<double> _dynamic_array_M_syn_t;
std::vector<int32_t> _dynamic_array_S_i;
std::vector<double> _dynamic_array_S_t;

//////////////// dynamic arrays 2d /////////
DynamicArray2D<double> _dynamic_array_M_exc_a;
DynamicArray2D<double> _dynamic_array_M_exc_b;
DynamicArray2D<double> _dynamic_array_M_exc_C;
DynamicArray2D<double> _dynamic_array_M_exc_DeltaT;
DynamicArray2D<double> _dynamic_array_M_exc_EEx;
DynamicArray2D<double> _dynamic_array_M_exc_EIn;
DynamicArray2D<double> _dynamic_array_M_exc_EL;
DynamicArray2D<double> _dynamic_array_M_exc_ge;
DynamicArray2D<double> _dynamic_array_M_exc_gi;
DynamicArray2D<double> _dynamic_array_M_exc_gL;
DynamicArray2D<double> _dynamic_array_M_exc_I;
DynamicArray2D<double> _dynamic_array_M_exc_I_AMPA;
DynamicArray2D<double> _dynamic_array_M_exc_I_GABA;
DynamicArray2D<double> _dynamic_array_M_exc_I_total;
DynamicArray2D<double> _dynamic_array_M_exc_tau_w;
DynamicArray2D<double> _dynamic_array_M_exc_v;
DynamicArray2D<double> _dynamic_array_M_exc_Vr;
DynamicArray2D<double> _dynamic_array_M_exc_VT;
DynamicArray2D<double> _dynamic_array_M_exc_w;
DynamicArray2D<double> _dynamic_array_M_inh_a;
DynamicArray2D<double> _dynamic_array_M_inh_b;
DynamicArray2D<double> _dynamic_array_M_inh_C;
DynamicArray2D<double> _dynamic_array_M_inh_DeltaT;
DynamicArray2D<double> _dynamic_array_M_inh_EEx;
DynamicArray2D<double> _dynamic_array_M_inh_EIn;
DynamicArray2D<double> _dynamic_array_M_inh_EL;
DynamicArray2D<double> _dynamic_array_M_inh_ge;
DynamicArray2D<double> _dynamic_array_M_inh_gi;
DynamicArray2D<double> _dynamic_array_M_inh_gL;
DynamicArray2D<double> _dynamic_array_M_inh_I;
DynamicArray2D<double> _dynamic_array_M_inh_I_AMPA;
DynamicArray2D<double> _dynamic_array_M_inh_I_GABA;
DynamicArray2D<double> _dynamic_array_M_inh_I_total;
DynamicArray2D<double> _dynamic_array_M_inh_tau_w;
DynamicArray2D<double> _dynamic_array_M_inh_v;
DynamicArray2D<double> _dynamic_array_M_inh_Vr;
DynamicArray2D<double> _dynamic_array_M_inh_VT;
DynamicArray2D<double> _dynamic_array_M_inh_w;
DynamicArray2D<double> _dynamic_array_M_syn_g;
DynamicArray2D<double> _dynamic_array_M_syn_tau_inact;
DynamicArray2D<double> _dynamic_array_M_syn_weight;

/////////////// static arrays /////////////
int32_t * _static_array__array_M_exc__indices;
const int _num__static_array__array_M_exc__indices = 500;
int32_t * _static_array__array_M_inh__indices;
const int _num__static_array__array_M_inh__indices = 100;
int32_t * _static_array__array_M_syn__indices;
const int _num__static_array__array_M_syn__indices = 500;

//////////////// synapses /////////////////
// exc_feedback_synapses
SynapticPathway exc_feedback_synapses_pre(
    _dynamic_array_exc_feedback_synapses__synaptic_pre,
    0, 500);
// exc_recurrent_synapses
SynapticPathway exc_recurrent_synapses_pre(
    _dynamic_array_exc_recurrent_synapses__synaptic_pre,
    0, 500);
// inh_synapses
SynapticPathway inh_synapses_pre(
    _dynamic_array_inh_synapses__synaptic_pre,
    0, 100);

//////////////// clocks ///////////////////
Clock exc_feedback_synapses_clock;  // attributes will be set in run.cpp
Clock exc_neurons_clock;  // attributes will be set in run.cpp
Clock exc_recurrent_synapses_clock;  // attributes will be set in run.cpp
Clock inh_neurons_clock;  // attributes will be set in run.cpp
Clock inh_synapses_clock;  // attributes will be set in run.cpp

// Profiling information for each code object
}

void _init_arrays()
{
    using namespace brian;

    // Arrays initialized to 0
    _array_defaultclock_dt = new double[1];
    
    for(int i=0; i<1; i++) _array_defaultclock_dt[i] = 0;

    _array_defaultclock_t = new double[1];
    
    for(int i=0; i<1; i++) _array_defaultclock_t[i] = 0;

    _array_defaultclock_timestep = new int64_t[1];
    
    for(int i=0; i<1; i++) _array_defaultclock_timestep[i] = 0;

    _array_exc_feedback_synapses_clock_dt = new double[1];
    
    for(int i=0; i<1; i++) _array_exc_feedback_synapses_clock_dt[i] = 0;

    _array_exc_feedback_synapses_clock_t = new double[1];
    
    for(int i=0; i<1; i++) _array_exc_feedback_synapses_clock_t[i] = 0;

    _array_exc_feedback_synapses_clock_timestep = new int64_t[1];
    
    for(int i=0; i<1; i++) _array_exc_feedback_synapses_clock_timestep[i] = 0;

    _array_exc_feedback_synapses_N = new int32_t[1];
    
    for(int i=0; i<1; i++) _array_exc_feedback_synapses_N[i] = 0;

    _array_exc_neurons__spikespace = new int32_t[501];
    
    for(int i=0; i<501; i++) _array_exc_neurons__spikespace[i] = 0;

    _array_exc_neurons_a = new double[500];
    
    for(int i=0; i<500; i++) _array_exc_neurons_a[i] = 0;

    _array_exc_neurons_b = new double[500];
    
    for(int i=0; i<500; i++) _array_exc_neurons_b[i] = 0;

    _array_exc_neurons_C = new double[500];
    
    for(int i=0; i<500; i++) _array_exc_neurons_C[i] = 0;

    _array_exc_neurons_clock_dt = new double[1];
    
    for(int i=0; i<1; i++) _array_exc_neurons_clock_dt[i] = 0;

    _array_exc_neurons_clock_t = new double[1];
    
    for(int i=0; i<1; i++) _array_exc_neurons_clock_t[i] = 0;

    _array_exc_neurons_clock_timestep = new int64_t[1];
    
    for(int i=0; i<1; i++) _array_exc_neurons_clock_timestep[i] = 0;

    _array_exc_neurons_DeltaT = new double[500];
    
    for(int i=0; i<500; i++) _array_exc_neurons_DeltaT[i] = 0;

    _array_exc_neurons_EEx = new double[500];
    
    for(int i=0; i<500; i++) _array_exc_neurons_EEx[i] = 0;

    _array_exc_neurons_EIn = new double[500];
    
    for(int i=0; i<500; i++) _array_exc_neurons_EIn[i] = 0;

    _array_exc_neurons_EL = new double[500];
    
    for(int i=0; i<500; i++) _array_exc_neurons_EL[i] = 0;

    _array_exc_neurons_ge = new double[500];
    
    for(int i=0; i<500; i++) _array_exc_neurons_ge[i] = 0;

    _array_exc_neurons_gi = new double[500];
    
    for(int i=0; i<500; i++) _array_exc_neurons_gi[i] = 0;

    _array_exc_neurons_gL = new double[500];
    
    for(int i=0; i<500; i++) _array_exc_neurons_gL[i] = 0;

    _array_exc_neurons_i = new int32_t[500];
    
    for(int i=0; i<500; i++) _array_exc_neurons_i[i] = 0;

    _array_exc_neurons_I = new double[500];
    
    for(int i=0; i<500; i++) _array_exc_neurons_I[i] = 0;

    _array_exc_neurons_tau_w = new double[500];
    
    for(int i=0; i<500; i++) _array_exc_neurons_tau_w[i] = 0;

    _array_exc_neurons_v = new double[500];
    
    for(int i=0; i<500; i++) _array_exc_neurons_v[i] = 0;

    _array_exc_neurons_Vr = new double[500];
    
    for(int i=0; i<500; i++) _array_exc_neurons_Vr[i] = 0;

    _array_exc_neurons_VT = new double[500];
    
    for(int i=0; i<500; i++) _array_exc_neurons_VT[i] = 0;

    _array_exc_neurons_w = new double[500];
    
    for(int i=0; i<500; i++) _array_exc_neurons_w[i] = 0;

    _array_exc_recurrent_synapses_clock_dt = new double[1];
    
    for(int i=0; i<1; i++) _array_exc_recurrent_synapses_clock_dt[i] = 0;

    _array_exc_recurrent_synapses_clock_t = new double[1];
    
    for(int i=0; i<1; i++) _array_exc_recurrent_synapses_clock_t[i] = 0;

    _array_exc_recurrent_synapses_clock_timestep = new int64_t[1];
    
    for(int i=0; i<1; i++) _array_exc_recurrent_synapses_clock_timestep[i] = 0;

    _array_exc_recurrent_synapses_N = new int32_t[1];
    
    for(int i=0; i<1; i++) _array_exc_recurrent_synapses_N[i] = 0;

    _array_inh_neurons__spikespace = new int32_t[101];
    
    for(int i=0; i<101; i++) _array_inh_neurons__spikespace[i] = 0;

    _array_inh_neurons_a = new double[100];
    
    for(int i=0; i<100; i++) _array_inh_neurons_a[i] = 0;

    _array_inh_neurons_b = new double[100];
    
    for(int i=0; i<100; i++) _array_inh_neurons_b[i] = 0;

    _array_inh_neurons_C = new double[100];
    
    for(int i=0; i<100; i++) _array_inh_neurons_C[i] = 0;

    _array_inh_neurons_clock_dt = new double[1];
    
    for(int i=0; i<1; i++) _array_inh_neurons_clock_dt[i] = 0;

    _array_inh_neurons_clock_t = new double[1];
    
    for(int i=0; i<1; i++) _array_inh_neurons_clock_t[i] = 0;

    _array_inh_neurons_clock_timestep = new int64_t[1];
    
    for(int i=0; i<1; i++) _array_inh_neurons_clock_timestep[i] = 0;

    _array_inh_neurons_DeltaT = new double[100];
    
    for(int i=0; i<100; i++) _array_inh_neurons_DeltaT[i] = 0;

    _array_inh_neurons_EEx = new double[100];
    
    for(int i=0; i<100; i++) _array_inh_neurons_EEx[i] = 0;

    _array_inh_neurons_EIn = new double[100];
    
    for(int i=0; i<100; i++) _array_inh_neurons_EIn[i] = 0;

    _array_inh_neurons_EL = new double[100];
    
    for(int i=0; i<100; i++) _array_inh_neurons_EL[i] = 0;

    _array_inh_neurons_ge = new double[100];
    
    for(int i=0; i<100; i++) _array_inh_neurons_ge[i] = 0;

    _array_inh_neurons_gi = new double[100];
    
    for(int i=0; i<100; i++) _array_inh_neurons_gi[i] = 0;

    _array_inh_neurons_gL = new double[100];
    
    for(int i=0; i<100; i++) _array_inh_neurons_gL[i] = 0;

    _array_inh_neurons_i = new int32_t[100];
    
    for(int i=0; i<100; i++) _array_inh_neurons_i[i] = 0;

    _array_inh_neurons_I = new double[100];
    
    for(int i=0; i<100; i++) _array_inh_neurons_I[i] = 0;

    _array_inh_neurons_tau_w = new double[100];
    
    for(int i=0; i<100; i++) _array_inh_neurons_tau_w[i] = 0;

    _array_inh_neurons_v = new double[100];
    
    for(int i=0; i<100; i++) _array_inh_neurons_v[i] = 0;

    _array_inh_neurons_Vr = new double[100];
    
    for(int i=0; i<100; i++) _array_inh_neurons_Vr[i] = 0;

    _array_inh_neurons_VT = new double[100];
    
    for(int i=0; i<100; i++) _array_inh_neurons_VT[i] = 0;

    _array_inh_neurons_w = new double[100];
    
    for(int i=0; i<100; i++) _array_inh_neurons_w[i] = 0;

    _array_inh_synapses_clock_dt = new double[1];
    
    for(int i=0; i<1; i++) _array_inh_synapses_clock_dt[i] = 0;

    _array_inh_synapses_clock_t = new double[1];
    
    for(int i=0; i<1; i++) _array_inh_synapses_clock_t[i] = 0;

    _array_inh_synapses_clock_timestep = new int64_t[1];
    
    for(int i=0; i<1; i++) _array_inh_synapses_clock_timestep[i] = 0;

    _array_inh_synapses_N = new int32_t[1];
    
    for(int i=0; i<1; i++) _array_inh_synapses_N[i] = 0;

    _array_M_exc__indices = new int32_t[500];
    
    for(int i=0; i<500; i++) _array_M_exc__indices[i] = 0;

    _array_M_exc_N = new int32_t[1];
    
    for(int i=0; i<1; i++) _array_M_exc_N[i] = 0;

    _array_M_inh__indices = new int32_t[100];
    
    for(int i=0; i<100; i++) _array_M_inh__indices[i] = 0;

    _array_M_inh_N = new int32_t[1];
    
    for(int i=0; i<1; i++) _array_M_inh_N[i] = 0;

    _array_M_syn__indices = new int32_t[500];
    
    for(int i=0; i<500; i++) _array_M_syn__indices[i] = 0;

    _array_M_syn_N = new int32_t[1];
    
    for(int i=0; i<1; i++) _array_M_syn_N[i] = 0;

    _array_S__source_idx = new int32_t[500];
    
    for(int i=0; i<500; i++) _array_S__source_idx[i] = 0;

    _array_S_count = new int32_t[500];
    
    for(int i=0; i<500; i++) _array_S_count[i] = 0;

    _array_S_N = new int32_t[1];
    
    for(int i=0; i<1; i++) _array_S_N[i] = 0;

    _dynamic_array_exc_recurrent_synapses_delay.resize(1);
    
    for(int i=0; i<1; i++) _dynamic_array_exc_recurrent_synapses_delay[i] = 0;


    // Arrays initialized to an "arange"
    _array_exc_neurons_i = new int32_t[500];
    
    for(int i=0; i<500; i++) _array_exc_neurons_i[i] = 0 + i;

    _array_inh_neurons_i = new int32_t[100];
    
    for(int i=0; i<100; i++) _array_inh_neurons_i[i] = 0 + i;

    _array_S__source_idx = new int32_t[500];
    
    for(int i=0; i<500; i++) _array_S__source_idx[i] = 0 + i;


    // static arrays
    _static_array__array_M_exc__indices = new int32_t[500];
    _static_array__array_M_inh__indices = new int32_t[100];
    _static_array__array_M_syn__indices = new int32_t[500];

    // Random number generator states
    std::random_device rd;
    for (int i=0; i<1; i++)
        _random_generators.push_back(RandomGenerator());
}

void _load_arrays()
{
    using namespace brian;

    ifstream f_static_array__array_M_exc__indices;
    f_static_array__array_M_exc__indices.open("static_arrays/_static_array__array_M_exc__indices", ios::in | ios::binary);
    if(f_static_array__array_M_exc__indices.is_open())
    {
        f_static_array__array_M_exc__indices.read(reinterpret_cast<char*>(_static_array__array_M_exc__indices), 500*sizeof(int32_t));
    } else
    {
        std::cout << "Error opening static array _static_array__array_M_exc__indices." << endl;
    }
    ifstream f_static_array__array_M_inh__indices;
    f_static_array__array_M_inh__indices.open("static_arrays/_static_array__array_M_inh__indices", ios::in | ios::binary);
    if(f_static_array__array_M_inh__indices.is_open())
    {
        f_static_array__array_M_inh__indices.read(reinterpret_cast<char*>(_static_array__array_M_inh__indices), 100*sizeof(int32_t));
    } else
    {
        std::cout << "Error opening static array _static_array__array_M_inh__indices." << endl;
    }
    ifstream f_static_array__array_M_syn__indices;
    f_static_array__array_M_syn__indices.open("static_arrays/_static_array__array_M_syn__indices", ios::in | ios::binary);
    if(f_static_array__array_M_syn__indices.is_open())
    {
        f_static_array__array_M_syn__indices.read(reinterpret_cast<char*>(_static_array__array_M_syn__indices), 500*sizeof(int32_t));
    } else
    {
        std::cout << "Error opening static array _static_array__array_M_syn__indices." << endl;
    }
}

void _write_arrays()
{
    using namespace brian;

    ofstream outfile__array_defaultclock_dt;
    outfile__array_defaultclock_dt.open(results_dir + "_array_defaultclock_dt_1978099143", ios::binary | ios::out);
    if(outfile__array_defaultclock_dt.is_open())
    {
        outfile__array_defaultclock_dt.write(reinterpret_cast<char*>(_array_defaultclock_dt), 1*sizeof(_array_defaultclock_dt[0]));
        outfile__array_defaultclock_dt.close();
    } else
    {
        std::cout << "Error writing output file for _array_defaultclock_dt." << endl;
    }
    ofstream outfile__array_defaultclock_t;
    outfile__array_defaultclock_t.open(results_dir + "_array_defaultclock_t_2669362164", ios::binary | ios::out);
    if(outfile__array_defaultclock_t.is_open())
    {
        outfile__array_defaultclock_t.write(reinterpret_cast<char*>(_array_defaultclock_t), 1*sizeof(_array_defaultclock_t[0]));
        outfile__array_defaultclock_t.close();
    } else
    {
        std::cout << "Error writing output file for _array_defaultclock_t." << endl;
    }
    ofstream outfile__array_defaultclock_timestep;
    outfile__array_defaultclock_timestep.open(results_dir + "_array_defaultclock_timestep_144223508", ios::binary | ios::out);
    if(outfile__array_defaultclock_timestep.is_open())
    {
        outfile__array_defaultclock_timestep.write(reinterpret_cast<char*>(_array_defaultclock_timestep), 1*sizeof(_array_defaultclock_timestep[0]));
        outfile__array_defaultclock_timestep.close();
    } else
    {
        std::cout << "Error writing output file for _array_defaultclock_timestep." << endl;
    }
    ofstream outfile__array_exc_feedback_synapses_clock_dt;
    outfile__array_exc_feedback_synapses_clock_dt.open(results_dir + "_array_exc_feedback_synapses_clock_dt_1169769220", ios::binary | ios::out);
    if(outfile__array_exc_feedback_synapses_clock_dt.is_open())
    {
        outfile__array_exc_feedback_synapses_clock_dt.write(reinterpret_cast<char*>(_array_exc_feedback_synapses_clock_dt), 1*sizeof(_array_exc_feedback_synapses_clock_dt[0]));
        outfile__array_exc_feedback_synapses_clock_dt.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_feedback_synapses_clock_dt." << endl;
    }
    ofstream outfile__array_exc_feedback_synapses_clock_t;
    outfile__array_exc_feedback_synapses_clock_t.open(results_dir + "_array_exc_feedback_synapses_clock_t_1958875419", ios::binary | ios::out);
    if(outfile__array_exc_feedback_synapses_clock_t.is_open())
    {
        outfile__array_exc_feedback_synapses_clock_t.write(reinterpret_cast<char*>(_array_exc_feedback_synapses_clock_t), 1*sizeof(_array_exc_feedback_synapses_clock_t[0]));
        outfile__array_exc_feedback_synapses_clock_t.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_feedback_synapses_clock_t." << endl;
    }
    ofstream outfile__array_exc_feedback_synapses_clock_timestep;
    outfile__array_exc_feedback_synapses_clock_timestep.open(results_dir + "_array_exc_feedback_synapses_clock_timestep_3738994347", ios::binary | ios::out);
    if(outfile__array_exc_feedback_synapses_clock_timestep.is_open())
    {
        outfile__array_exc_feedback_synapses_clock_timestep.write(reinterpret_cast<char*>(_array_exc_feedback_synapses_clock_timestep), 1*sizeof(_array_exc_feedback_synapses_clock_timestep[0]));
        outfile__array_exc_feedback_synapses_clock_timestep.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_feedback_synapses_clock_timestep." << endl;
    }
    ofstream outfile__array_exc_feedback_synapses_N;
    outfile__array_exc_feedback_synapses_N.open(results_dir + "_array_exc_feedback_synapses_N_3290911165", ios::binary | ios::out);
    if(outfile__array_exc_feedback_synapses_N.is_open())
    {
        outfile__array_exc_feedback_synapses_N.write(reinterpret_cast<char*>(_array_exc_feedback_synapses_N), 1*sizeof(_array_exc_feedback_synapses_N[0]));
        outfile__array_exc_feedback_synapses_N.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_feedback_synapses_N." << endl;
    }
    ofstream outfile__array_exc_neurons__spikespace;
    outfile__array_exc_neurons__spikespace.open(results_dir + "_array_exc_neurons__spikespace_2431962188", ios::binary | ios::out);
    if(outfile__array_exc_neurons__spikespace.is_open())
    {
        outfile__array_exc_neurons__spikespace.write(reinterpret_cast<char*>(_array_exc_neurons__spikespace), 501*sizeof(_array_exc_neurons__spikespace[0]));
        outfile__array_exc_neurons__spikespace.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_neurons__spikespace." << endl;
    }
    ofstream outfile__array_exc_neurons_a;
    outfile__array_exc_neurons_a.open(results_dir + "_array_exc_neurons_a_632244190", ios::binary | ios::out);
    if(outfile__array_exc_neurons_a.is_open())
    {
        outfile__array_exc_neurons_a.write(reinterpret_cast<char*>(_array_exc_neurons_a), 500*sizeof(_array_exc_neurons_a[0]));
        outfile__array_exc_neurons_a.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_neurons_a." << endl;
    }
    ofstream outfile__array_exc_neurons_b;
    outfile__array_exc_neurons_b.open(results_dir + "_array_exc_neurons_b_3165001316", ios::binary | ios::out);
    if(outfile__array_exc_neurons_b.is_open())
    {
        outfile__array_exc_neurons_b.write(reinterpret_cast<char*>(_array_exc_neurons_b), 500*sizeof(_array_exc_neurons_b[0]));
        outfile__array_exc_neurons_b.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_neurons_b." << endl;
    }
    ofstream outfile__array_exc_neurons_C;
    outfile__array_exc_neurons_C.open(results_dir + "_array_exc_neurons_C_4040099386", ios::binary | ios::out);
    if(outfile__array_exc_neurons_C.is_open())
    {
        outfile__array_exc_neurons_C.write(reinterpret_cast<char*>(_array_exc_neurons_C), 500*sizeof(_array_exc_neurons_C[0]));
        outfile__array_exc_neurons_C.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_neurons_C." << endl;
    }
    ofstream outfile__array_exc_neurons_clock_dt;
    outfile__array_exc_neurons_clock_dt.open(results_dir + "_array_exc_neurons_clock_dt_3849017614", ios::binary | ios::out);
    if(outfile__array_exc_neurons_clock_dt.is_open())
    {
        outfile__array_exc_neurons_clock_dt.write(reinterpret_cast<char*>(_array_exc_neurons_clock_dt), 1*sizeof(_array_exc_neurons_clock_dt[0]));
        outfile__array_exc_neurons_clock_dt.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_neurons_clock_dt." << endl;
    }
    ofstream outfile__array_exc_neurons_clock_t;
    outfile__array_exc_neurons_clock_t.open(results_dir + "_array_exc_neurons_clock_t_2889507835", ios::binary | ios::out);
    if(outfile__array_exc_neurons_clock_t.is_open())
    {
        outfile__array_exc_neurons_clock_t.write(reinterpret_cast<char*>(_array_exc_neurons_clock_t), 1*sizeof(_array_exc_neurons_clock_t[0]));
        outfile__array_exc_neurons_clock_t.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_neurons_clock_t." << endl;
    }
    ofstream outfile__array_exc_neurons_clock_timestep;
    outfile__array_exc_neurons_clock_timestep.open(results_dir + "_array_exc_neurons_clock_timestep_3278492", ios::binary | ios::out);
    if(outfile__array_exc_neurons_clock_timestep.is_open())
    {
        outfile__array_exc_neurons_clock_timestep.write(reinterpret_cast<char*>(_array_exc_neurons_clock_timestep), 1*sizeof(_array_exc_neurons_clock_timestep[0]));
        outfile__array_exc_neurons_clock_timestep.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_neurons_clock_timestep." << endl;
    }
    ofstream outfile__array_exc_neurons_DeltaT;
    outfile__array_exc_neurons_DeltaT.open(results_dir + "_array_exc_neurons_DeltaT_4171806623", ios::binary | ios::out);
    if(outfile__array_exc_neurons_DeltaT.is_open())
    {
        outfile__array_exc_neurons_DeltaT.write(reinterpret_cast<char*>(_array_exc_neurons_DeltaT), 500*sizeof(_array_exc_neurons_DeltaT[0]));
        outfile__array_exc_neurons_DeltaT.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_neurons_DeltaT." << endl;
    }
    ofstream outfile__array_exc_neurons_EEx;
    outfile__array_exc_neurons_EEx.open(results_dir + "_array_exc_neurons_EEx_1515104128", ios::binary | ios::out);
    if(outfile__array_exc_neurons_EEx.is_open())
    {
        outfile__array_exc_neurons_EEx.write(reinterpret_cast<char*>(_array_exc_neurons_EEx), 500*sizeof(_array_exc_neurons_EEx[0]));
        outfile__array_exc_neurons_EEx.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_neurons_EEx." << endl;
    }
    ofstream outfile__array_exc_neurons_EIn;
    outfile__array_exc_neurons_EIn.open(results_dir + "_array_exc_neurons_EIn_36658653", ios::binary | ios::out);
    if(outfile__array_exc_neurons_EIn.is_open())
    {
        outfile__array_exc_neurons_EIn.write(reinterpret_cast<char*>(_array_exc_neurons_EIn), 500*sizeof(_array_exc_neurons_EIn[0]));
        outfile__array_exc_neurons_EIn.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_neurons_EIn." << endl;
    }
    ofstream outfile__array_exc_neurons_EL;
    outfile__array_exc_neurons_EL.open(results_dir + "_array_exc_neurons_EL_1036931844", ios::binary | ios::out);
    if(outfile__array_exc_neurons_EL.is_open())
    {
        outfile__array_exc_neurons_EL.write(reinterpret_cast<char*>(_array_exc_neurons_EL), 500*sizeof(_array_exc_neurons_EL[0]));
        outfile__array_exc_neurons_EL.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_neurons_EL." << endl;
    }
    ofstream outfile__array_exc_neurons_ge;
    outfile__array_exc_neurons_ge.open(results_dir + "_array_exc_neurons_ge_3637415240", ios::binary | ios::out);
    if(outfile__array_exc_neurons_ge.is_open())
    {
        outfile__array_exc_neurons_ge.write(reinterpret_cast<char*>(_array_exc_neurons_ge), 500*sizeof(_array_exc_neurons_ge[0]));
        outfile__array_exc_neurons_ge.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_neurons_ge." << endl;
    }
    ofstream outfile__array_exc_neurons_gi;
    outfile__array_exc_neurons_gi.open(results_dir + "_array_exc_neurons_gi_3514351971", ios::binary | ios::out);
    if(outfile__array_exc_neurons_gi.is_open())
    {
        outfile__array_exc_neurons_gi.write(reinterpret_cast<char*>(_array_exc_neurons_gi), 500*sizeof(_array_exc_neurons_gi[0]));
        outfile__array_exc_neurons_gi.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_neurons_gi." << endl;
    }
    ofstream outfile__array_exc_neurons_gL;
    outfile__array_exc_neurons_gL.open(results_dir + "_array_exc_neurons_gL_2591823140", ios::binary | ios::out);
    if(outfile__array_exc_neurons_gL.is_open())
    {
        outfile__array_exc_neurons_gL.write(reinterpret_cast<char*>(_array_exc_neurons_gL), 500*sizeof(_array_exc_neurons_gL[0]));
        outfile__array_exc_neurons_gL.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_neurons_gL." << endl;
    }
    ofstream outfile__array_exc_neurons_i;
    outfile__array_exc_neurons_i.open(results_dir + "_array_exc_neurons_i_729075692", ios::binary | ios::out);
    if(outfile__array_exc_neurons_i.is_open())
    {
        outfile__array_exc_neurons_i.write(reinterpret_cast<char*>(_array_exc_neurons_i), 500*sizeof(_array_exc_neurons_i[0]));
        outfile__array_exc_neurons_i.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_neurons_i." << endl;
    }
    ofstream outfile__array_exc_neurons_I;
    outfile__array_exc_neurons_I.open(results_dir + "_array_exc_neurons_I_270200612", ios::binary | ios::out);
    if(outfile__array_exc_neurons_I.is_open())
    {
        outfile__array_exc_neurons_I.write(reinterpret_cast<char*>(_array_exc_neurons_I), 500*sizeof(_array_exc_neurons_I[0]));
        outfile__array_exc_neurons_I.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_neurons_I." << endl;
    }
    ofstream outfile__array_exc_neurons_tau_w;
    outfile__array_exc_neurons_tau_w.open(results_dir + "_array_exc_neurons_tau_w_2053339577", ios::binary | ios::out);
    if(outfile__array_exc_neurons_tau_w.is_open())
    {
        outfile__array_exc_neurons_tau_w.write(reinterpret_cast<char*>(_array_exc_neurons_tau_w), 500*sizeof(_array_exc_neurons_tau_w[0]));
        outfile__array_exc_neurons_tau_w.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_neurons_tau_w." << endl;
    }
    ofstream outfile__array_exc_neurons_v;
    outfile__array_exc_neurons_v.open(results_dir + "_array_exc_neurons_v_2793194009", ios::binary | ios::out);
    if(outfile__array_exc_neurons_v.is_open())
    {
        outfile__array_exc_neurons_v.write(reinterpret_cast<char*>(_array_exc_neurons_v), 500*sizeof(_array_exc_neurons_v[0]));
        outfile__array_exc_neurons_v.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_neurons_v." << endl;
    }
    ofstream outfile__array_exc_neurons_Vr;
    outfile__array_exc_neurons_Vr.open(results_dir + "_array_exc_neurons_Vr_2638221117", ios::binary | ios::out);
    if(outfile__array_exc_neurons_Vr.is_open())
    {
        outfile__array_exc_neurons_Vr.write(reinterpret_cast<char*>(_array_exc_neurons_Vr), 500*sizeof(_array_exc_neurons_Vr[0]));
        outfile__array_exc_neurons_Vr.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_neurons_Vr." << endl;
    }
    ofstream outfile__array_exc_neurons_VT;
    outfile__array_exc_neurons_VT.open(results_dir + "_array_exc_neurons_VT_1330481856", ios::binary | ios::out);
    if(outfile__array_exc_neurons_VT.is_open())
    {
        outfile__array_exc_neurons_VT.write(reinterpret_cast<char*>(_array_exc_neurons_VT), 500*sizeof(_array_exc_neurons_VT[0]));
        outfile__array_exc_neurons_VT.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_neurons_VT." << endl;
    }
    ofstream outfile__array_exc_neurons_w;
    outfile__array_exc_neurons_w.open(results_dir + "_array_exc_neurons_w_3514561167", ios::binary | ios::out);
    if(outfile__array_exc_neurons_w.is_open())
    {
        outfile__array_exc_neurons_w.write(reinterpret_cast<char*>(_array_exc_neurons_w), 500*sizeof(_array_exc_neurons_w[0]));
        outfile__array_exc_neurons_w.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_neurons_w." << endl;
    }
    ofstream outfile__array_exc_recurrent_synapses_clock_dt;
    outfile__array_exc_recurrent_synapses_clock_dt.open(results_dir + "_array_exc_recurrent_synapses_clock_dt_413401186", ios::binary | ios::out);
    if(outfile__array_exc_recurrent_synapses_clock_dt.is_open())
    {
        outfile__array_exc_recurrent_synapses_clock_dt.write(reinterpret_cast<char*>(_array_exc_recurrent_synapses_clock_dt), 1*sizeof(_array_exc_recurrent_synapses_clock_dt[0]));
        outfile__array_exc_recurrent_synapses_clock_dt.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_recurrent_synapses_clock_dt." << endl;
    }
    ofstream outfile__array_exc_recurrent_synapses_clock_t;
    outfile__array_exc_recurrent_synapses_clock_t.open(results_dir + "_array_exc_recurrent_synapses_clock_t_26899937", ios::binary | ios::out);
    if(outfile__array_exc_recurrent_synapses_clock_t.is_open())
    {
        outfile__array_exc_recurrent_synapses_clock_t.write(reinterpret_cast<char*>(_array_exc_recurrent_synapses_clock_t), 1*sizeof(_array_exc_recurrent_synapses_clock_t[0]));
        outfile__array_exc_recurrent_synapses_clock_t.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_recurrent_synapses_clock_t." << endl;
    }
    ofstream outfile__array_exc_recurrent_synapses_clock_timestep;
    outfile__array_exc_recurrent_synapses_clock_timestep.open(results_dir + "_array_exc_recurrent_synapses_clock_timestep_3644160724", ios::binary | ios::out);
    if(outfile__array_exc_recurrent_synapses_clock_timestep.is_open())
    {
        outfile__array_exc_recurrent_synapses_clock_timestep.write(reinterpret_cast<char*>(_array_exc_recurrent_synapses_clock_timestep), 1*sizeof(_array_exc_recurrent_synapses_clock_timestep[0]));
        outfile__array_exc_recurrent_synapses_clock_timestep.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_recurrent_synapses_clock_timestep." << endl;
    }
    ofstream outfile__array_exc_recurrent_synapses_N;
    outfile__array_exc_recurrent_synapses_N.open(results_dir + "_array_exc_recurrent_synapses_N_3437243050", ios::binary | ios::out);
    if(outfile__array_exc_recurrent_synapses_N.is_open())
    {
        outfile__array_exc_recurrent_synapses_N.write(reinterpret_cast<char*>(_array_exc_recurrent_synapses_N), 1*sizeof(_array_exc_recurrent_synapses_N[0]));
        outfile__array_exc_recurrent_synapses_N.close();
    } else
    {
        std::cout << "Error writing output file for _array_exc_recurrent_synapses_N." << endl;
    }
    ofstream outfile__array_inh_neurons__spikespace;
    outfile__array_inh_neurons__spikespace.open(results_dir + "_array_inh_neurons__spikespace_368817581", ios::binary | ios::out);
    if(outfile__array_inh_neurons__spikespace.is_open())
    {
        outfile__array_inh_neurons__spikespace.write(reinterpret_cast<char*>(_array_inh_neurons__spikespace), 101*sizeof(_array_inh_neurons__spikespace[0]));
        outfile__array_inh_neurons__spikespace.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_neurons__spikespace." << endl;
    }
    ofstream outfile__array_inh_neurons_a;
    outfile__array_inh_neurons_a.open(results_dir + "_array_inh_neurons_a_2131833213", ios::binary | ios::out);
    if(outfile__array_inh_neurons_a.is_open())
    {
        outfile__array_inh_neurons_a.write(reinterpret_cast<char*>(_array_inh_neurons_a), 100*sizeof(_array_inh_neurons_a[0]));
        outfile__array_inh_neurons_a.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_neurons_a." << endl;
    }
    ofstream outfile__array_inh_neurons_b;
    outfile__array_inh_neurons_b.open(results_dir + "_array_inh_neurons_b_3860357319", ios::binary | ios::out);
    if(outfile__array_inh_neurons_b.is_open())
    {
        outfile__array_inh_neurons_b.write(reinterpret_cast<char*>(_array_inh_neurons_b), 100*sizeof(_array_inh_neurons_b[0]));
        outfile__array_inh_neurons_b.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_neurons_b." << endl;
    }
    ofstream outfile__array_inh_neurons_C;
    outfile__array_inh_neurons_C.open(results_dir + "_array_inh_neurons_C_2859561113", ios::binary | ios::out);
    if(outfile__array_inh_neurons_C.is_open())
    {
        outfile__array_inh_neurons_C.write(reinterpret_cast<char*>(_array_inh_neurons_C), 100*sizeof(_array_inh_neurons_C[0]));
        outfile__array_inh_neurons_C.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_neurons_C." << endl;
    }
    ofstream outfile__array_inh_neurons_clock_dt;
    outfile__array_inh_neurons_clock_dt.open(results_dir + "_array_inh_neurons_clock_dt_1158948754", ios::binary | ios::out);
    if(outfile__array_inh_neurons_clock_dt.is_open())
    {
        outfile__array_inh_neurons_clock_dt.write(reinterpret_cast<char*>(_array_inh_neurons_clock_dt), 1*sizeof(_array_inh_neurons_clock_dt[0]));
        outfile__array_inh_neurons_clock_dt.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_neurons_clock_dt." << endl;
    }
    ofstream outfile__array_inh_neurons_clock_t;
    outfile__array_inh_neurons_clock_t.open(results_dir + "_array_inh_neurons_clock_t_3651569435", ios::binary | ios::out);
    if(outfile__array_inh_neurons_clock_t.is_open())
    {
        outfile__array_inh_neurons_clock_t.write(reinterpret_cast<char*>(_array_inh_neurons_clock_t), 1*sizeof(_array_inh_neurons_clock_t[0]));
        outfile__array_inh_neurons_clock_t.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_neurons_clock_t." << endl;
    }
    ofstream outfile__array_inh_neurons_clock_timestep;
    outfile__array_inh_neurons_clock_timestep.open(results_dir + "_array_inh_neurons_clock_timestep_3327157152", ios::binary | ios::out);
    if(outfile__array_inh_neurons_clock_timestep.is_open())
    {
        outfile__array_inh_neurons_clock_timestep.write(reinterpret_cast<char*>(_array_inh_neurons_clock_timestep), 1*sizeof(_array_inh_neurons_clock_timestep[0]));
        outfile__array_inh_neurons_clock_timestep.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_neurons_clock_timestep." << endl;
    }
    ofstream outfile__array_inh_neurons_DeltaT;
    outfile__array_inh_neurons_DeltaT.open(results_dir + "_array_inh_neurons_DeltaT_250596189", ios::binary | ios::out);
    if(outfile__array_inh_neurons_DeltaT.is_open())
    {
        outfile__array_inh_neurons_DeltaT.write(reinterpret_cast<char*>(_array_inh_neurons_DeltaT), 100*sizeof(_array_inh_neurons_DeltaT[0]));
        outfile__array_inh_neurons_DeltaT.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_neurons_DeltaT." << endl;
    }
    ofstream outfile__array_inh_neurons_EEx;
    outfile__array_inh_neurons_EEx.open(results_dir + "_array_inh_neurons_EEx_1711457821", ios::binary | ios::out);
    if(outfile__array_inh_neurons_EEx.is_open())
    {
        outfile__array_inh_neurons_EEx.write(reinterpret_cast<char*>(_array_inh_neurons_EEx), 100*sizeof(_array_inh_neurons_EEx[0]));
        outfile__array_inh_neurons_EEx.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_neurons_EEx." << endl;
    }
    ofstream outfile__array_inh_neurons_EIn;
    outfile__array_inh_neurons_EIn.open(results_dir + "_array_inh_neurons_EIn_1046690880", ios::binary | ios::out);
    if(outfile__array_inh_neurons_EIn.is_open())
    {
        outfile__array_inh_neurons_EIn.write(reinterpret_cast<char*>(_array_inh_neurons_EIn), 100*sizeof(_array_inh_neurons_EIn[0]));
        outfile__array_inh_neurons_EIn.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_neurons_EIn." << endl;
    }
    ofstream outfile__array_inh_neurons_EL;
    outfile__array_inh_neurons_EL.open(results_dir + "_array_inh_neurons_EL_1917525792", ios::binary | ios::out);
    if(outfile__array_inh_neurons_EL.is_open())
    {
        outfile__array_inh_neurons_EL.write(reinterpret_cast<char*>(_array_inh_neurons_EL), 100*sizeof(_array_inh_neurons_EL[0]));
        outfile__array_inh_neurons_EL.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_neurons_EL." << endl;
    }
    ofstream outfile__array_inh_neurons_ge;
    outfile__array_inh_neurons_ge.open(results_dir + "_array_inh_neurons_ge_2538324332", ios::binary | ios::out);
    if(outfile__array_inh_neurons_ge.is_open())
    {
        outfile__array_inh_neurons_ge.write(reinterpret_cast<char*>(_array_inh_neurons_ge), 100*sizeof(_array_inh_neurons_ge[0]));
        outfile__array_inh_neurons_ge.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_neurons_ge." << endl;
    }
    ofstream outfile__array_inh_neurons_gi;
    outfile__array_inh_neurons_gi.open(results_dir + "_array_inh_neurons_gi_2667416903", ios::binary | ios::out);
    if(outfile__array_inh_neurons_gi.is_open())
    {
        outfile__array_inh_neurons_gi.write(reinterpret_cast<char*>(_array_inh_neurons_gi), 100*sizeof(_array_inh_neurons_gi[0]));
        outfile__array_inh_neurons_gi.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_neurons_gi." << endl;
    }
    ofstream outfile__array_inh_neurons_gL;
    outfile__array_inh_neurons_gL.open(results_dir + "_array_inh_neurons_gL_3589888256", ios::binary | ios::out);
    if(outfile__array_inh_neurons_gL.is_open())
    {
        outfile__array_inh_neurons_gL.write(reinterpret_cast<char*>(_array_inh_neurons_gL), 100*sizeof(_array_inh_neurons_gL[0]));
        outfile__array_inh_neurons_gL.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_neurons_gL." << endl;
    }
    ofstream outfile__array_inh_neurons_i;
    outfile__array_inh_neurons_i.open(results_dir + "_array_inh_neurons_i_1909111119", ios::binary | ios::out);
    if(outfile__array_inh_neurons_i.is_open())
    {
        outfile__array_inh_neurons_i.write(reinterpret_cast<char*>(_array_inh_neurons_i), 100*sizeof(_array_inh_neurons_i[0]));
        outfile__array_inh_neurons_i.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_neurons_i." << endl;
    }
    ofstream outfile__array_inh_neurons_I;
    outfile__array_inh_neurons_I.open(results_dir + "_array_inh_neurons_I_1252301191", ios::binary | ios::out);
    if(outfile__array_inh_neurons_I.is_open())
    {
        outfile__array_inh_neurons_I.write(reinterpret_cast<char*>(_array_inh_neurons_I), 100*sizeof(_array_inh_neurons_I[0]));
        outfile__array_inh_neurons_I.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_neurons_I." << endl;
    }
    ofstream outfile__array_inh_neurons_tau_w;
    outfile__array_inh_neurons_tau_w.open(results_dir + "_array_inh_neurons_tau_w_2218385516", ios::binary | ios::out);
    if(outfile__array_inh_neurons_tau_w.is_open())
    {
        outfile__array_inh_neurons_tau_w.write(reinterpret_cast<char*>(_array_inh_neurons_tau_w), 100*sizeof(_array_inh_neurons_tau_w[0]));
        outfile__array_inh_neurons_tau_w.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_neurons_tau_w." << endl;
    }
    ofstream outfile__array_inh_neurons_v;
    outfile__array_inh_neurons_v.open(results_dir + "_array_inh_neurons_v_4240618682", ios::binary | ios::out);
    if(outfile__array_inh_neurons_v.is_open())
    {
        outfile__array_inh_neurons_v.write(reinterpret_cast<char*>(_array_inh_neurons_v), 100*sizeof(_array_inh_neurons_v[0]));
        outfile__array_inh_neurons_v.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_neurons_v." << endl;
    }
    ofstream outfile__array_inh_neurons_Vr;
    outfile__array_inh_neurons_Vr.open(results_dir + "_array_inh_neurons_Vr_3536143129", ios::binary | ios::out);
    if(outfile__array_inh_neurons_Vr.is_open())
    {
        outfile__array_inh_neurons_Vr.write(reinterpret_cast<char*>(_array_inh_neurons_Vr), 100*sizeof(_array_inh_neurons_Vr[0]));
        outfile__array_inh_neurons_Vr.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_neurons_Vr." << endl;
    }
    ofstream outfile__array_inh_neurons_VT;
    outfile__array_inh_neurons_VT.open(results_dir + "_array_inh_neurons_VT_13158116", ios::binary | ios::out);
    if(outfile__array_inh_neurons_VT.is_open())
    {
        outfile__array_inh_neurons_VT.write(reinterpret_cast<char*>(_array_inh_neurons_VT), 100*sizeof(_array_inh_neurons_VT[0]));
        outfile__array_inh_neurons_VT.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_neurons_VT." << endl;
    }
    ofstream outfile__array_inh_neurons_w;
    outfile__array_inh_neurons_w.open(results_dir + "_array_inh_neurons_w_2344977452", ios::binary | ios::out);
    if(outfile__array_inh_neurons_w.is_open())
    {
        outfile__array_inh_neurons_w.write(reinterpret_cast<char*>(_array_inh_neurons_w), 100*sizeof(_array_inh_neurons_w[0]));
        outfile__array_inh_neurons_w.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_neurons_w." << endl;
    }
    ofstream outfile__array_inh_synapses_clock_dt;
    outfile__array_inh_synapses_clock_dt.open(results_dir + "_array_inh_synapses_clock_dt_933887592", ios::binary | ios::out);
    if(outfile__array_inh_synapses_clock_dt.is_open())
    {
        outfile__array_inh_synapses_clock_dt.write(reinterpret_cast<char*>(_array_inh_synapses_clock_dt), 1*sizeof(_array_inh_synapses_clock_dt[0]));
        outfile__array_inh_synapses_clock_dt.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_synapses_clock_dt." << endl;
    }
    ofstream outfile__array_inh_synapses_clock_t;
    outfile__array_inh_synapses_clock_t.open(results_dir + "_array_inh_synapses_clock_t_1662580957", ios::binary | ios::out);
    if(outfile__array_inh_synapses_clock_t.is_open())
    {
        outfile__array_inh_synapses_clock_t.write(reinterpret_cast<char*>(_array_inh_synapses_clock_t), 1*sizeof(_array_inh_synapses_clock_t[0]));
        outfile__array_inh_synapses_clock_t.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_synapses_clock_t." << endl;
    }
    ofstream outfile__array_inh_synapses_clock_timestep;
    outfile__array_inh_synapses_clock_timestep.open(results_dir + "_array_inh_synapses_clock_timestep_1322348174", ios::binary | ios::out);
    if(outfile__array_inh_synapses_clock_timestep.is_open())
    {
        outfile__array_inh_synapses_clock_timestep.write(reinterpret_cast<char*>(_array_inh_synapses_clock_timestep), 1*sizeof(_array_inh_synapses_clock_timestep[0]));
        outfile__array_inh_synapses_clock_timestep.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_synapses_clock_timestep." << endl;
    }
    ofstream outfile__array_inh_synapses_N;
    outfile__array_inh_synapses_N.open(results_dir + "_array_inh_synapses_N_3992895614", ios::binary | ios::out);
    if(outfile__array_inh_synapses_N.is_open())
    {
        outfile__array_inh_synapses_N.write(reinterpret_cast<char*>(_array_inh_synapses_N), 1*sizeof(_array_inh_synapses_N[0]));
        outfile__array_inh_synapses_N.close();
    } else
    {
        std::cout << "Error writing output file for _array_inh_synapses_N." << endl;
    }
    ofstream outfile__array_M_exc__indices;
    outfile__array_M_exc__indices.open(results_dir + "_array_M_exc__indices_3190905137", ios::binary | ios::out);
    if(outfile__array_M_exc__indices.is_open())
    {
        outfile__array_M_exc__indices.write(reinterpret_cast<char*>(_array_M_exc__indices), 500*sizeof(_array_M_exc__indices[0]));
        outfile__array_M_exc__indices.close();
    } else
    {
        std::cout << "Error writing output file for _array_M_exc__indices." << endl;
    }
    ofstream outfile__array_M_exc_N;
    outfile__array_M_exc_N.open(results_dir + "_array_M_exc_N_852921380", ios::binary | ios::out);
    if(outfile__array_M_exc_N.is_open())
    {
        outfile__array_M_exc_N.write(reinterpret_cast<char*>(_array_M_exc_N), 1*sizeof(_array_M_exc_N[0]));
        outfile__array_M_exc_N.close();
    } else
    {
        std::cout << "Error writing output file for _array_M_exc_N." << endl;
    }
    ofstream outfile__array_M_inh__indices;
    outfile__array_M_inh__indices.open(results_dir + "_array_M_inh__indices_93905359", ios::binary | ios::out);
    if(outfile__array_M_inh__indices.is_open())
    {
        outfile__array_M_inh__indices.write(reinterpret_cast<char*>(_array_M_inh__indices), 100*sizeof(_array_M_inh__indices[0]));
        outfile__array_M_inh__indices.close();
    } else
    {
        std::cout << "Error writing output file for _array_M_inh__indices." << endl;
    }
    ofstream outfile__array_M_inh_N;
    outfile__array_M_inh_N.open(results_dir + "_array_M_inh_N_2382464647", ios::binary | ios::out);
    if(outfile__array_M_inh_N.is_open())
    {
        outfile__array_M_inh_N.write(reinterpret_cast<char*>(_array_M_inh_N), 1*sizeof(_array_M_inh_N[0]));
        outfile__array_M_inh_N.close();
    } else
    {
        std::cout << "Error writing output file for _array_M_inh_N." << endl;
    }
    ofstream outfile__array_M_syn__indices;
    outfile__array_M_syn__indices.open(results_dir + "_array_M_syn__indices_1768179037", ios::binary | ios::out);
    if(outfile__array_M_syn__indices.is_open())
    {
        outfile__array_M_syn__indices.write(reinterpret_cast<char*>(_array_M_syn__indices), 500*sizeof(_array_M_syn__indices[0]));
        outfile__array_M_syn__indices.close();
    } else
    {
        std::cout << "Error writing output file for _array_M_syn__indices." << endl;
    }
    ofstream outfile__array_M_syn_N;
    outfile__array_M_syn_N.open(results_dir + "_array_M_syn_N_1829902896", ios::binary | ios::out);
    if(outfile__array_M_syn_N.is_open())
    {
        outfile__array_M_syn_N.write(reinterpret_cast<char*>(_array_M_syn_N), 1*sizeof(_array_M_syn_N[0]));
        outfile__array_M_syn_N.close();
    } else
    {
        std::cout << "Error writing output file for _array_M_syn_N." << endl;
    }
    ofstream outfile__array_S__source_idx;
    outfile__array_S__source_idx.open(results_dir + "_array_S__source_idx_3022606653", ios::binary | ios::out);
    if(outfile__array_S__source_idx.is_open())
    {
        outfile__array_S__source_idx.write(reinterpret_cast<char*>(_array_S__source_idx), 500*sizeof(_array_S__source_idx[0]));
        outfile__array_S__source_idx.close();
    } else
    {
        std::cout << "Error writing output file for _array_S__source_idx." << endl;
    }
    ofstream outfile__array_S_count;
    outfile__array_S_count.open(results_dir + "_array_S_count_1598288115", ios::binary | ios::out);
    if(outfile__array_S_count.is_open())
    {
        outfile__array_S_count.write(reinterpret_cast<char*>(_array_S_count), 500*sizeof(_array_S_count[0]));
        outfile__array_S_count.close();
    } else
    {
        std::cout << "Error writing output file for _array_S_count." << endl;
    }
    ofstream outfile__array_S_N;
    outfile__array_S_N.open(results_dir + "_array_S_N_330730475", ios::binary | ios::out);
    if(outfile__array_S_N.is_open())
    {
        outfile__array_S_N.write(reinterpret_cast<char*>(_array_S_N), 1*sizeof(_array_S_N[0]));
        outfile__array_S_N.close();
    } else
    {
        std::cout << "Error writing output file for _array_S_N." << endl;
    }

    ofstream outfile__dynamic_array_exc_feedback_synapses__synaptic_post;
    outfile__dynamic_array_exc_feedback_synapses__synaptic_post.open(results_dir + "_dynamic_array_exc_feedback_synapses__synaptic_post_960157852", ios::binary | ios::out);
    if(outfile__dynamic_array_exc_feedback_synapses__synaptic_post.is_open())
    {
        if (! _dynamic_array_exc_feedback_synapses__synaptic_post.empty() )
        {
            outfile__dynamic_array_exc_feedback_synapses__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_exc_feedback_synapses__synaptic_post[0]), _dynamic_array_exc_feedback_synapses__synaptic_post.size()*sizeof(_dynamic_array_exc_feedback_synapses__synaptic_post[0]));
            outfile__dynamic_array_exc_feedback_synapses__synaptic_post.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_exc_feedback_synapses__synaptic_post." << endl;
    }
    ofstream outfile__dynamic_array_exc_feedback_synapses__synaptic_pre;
    outfile__dynamic_array_exc_feedback_synapses__synaptic_pre.open(results_dir + "_dynamic_array_exc_feedback_synapses__synaptic_pre_1035597820", ios::binary | ios::out);
    if(outfile__dynamic_array_exc_feedback_synapses__synaptic_pre.is_open())
    {
        if (! _dynamic_array_exc_feedback_synapses__synaptic_pre.empty() )
        {
            outfile__dynamic_array_exc_feedback_synapses__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_exc_feedback_synapses__synaptic_pre[0]), _dynamic_array_exc_feedback_synapses__synaptic_pre.size()*sizeof(_dynamic_array_exc_feedback_synapses__synaptic_pre[0]));
            outfile__dynamic_array_exc_feedback_synapses__synaptic_pre.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_exc_feedback_synapses__synaptic_pre." << endl;
    }
    ofstream outfile__dynamic_array_exc_feedback_synapses_delay;
    outfile__dynamic_array_exc_feedback_synapses_delay.open(results_dir + "_dynamic_array_exc_feedback_synapses_delay_3777117845", ios::binary | ios::out);
    if(outfile__dynamic_array_exc_feedback_synapses_delay.is_open())
    {
        if (! _dynamic_array_exc_feedback_synapses_delay.empty() )
        {
            outfile__dynamic_array_exc_feedback_synapses_delay.write(reinterpret_cast<char*>(&_dynamic_array_exc_feedback_synapses_delay[0]), _dynamic_array_exc_feedback_synapses_delay.size()*sizeof(_dynamic_array_exc_feedback_synapses_delay[0]));
            outfile__dynamic_array_exc_feedback_synapses_delay.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_exc_feedback_synapses_delay." << endl;
    }
    ofstream outfile__dynamic_array_exc_feedback_synapses_g;
    outfile__dynamic_array_exc_feedback_synapses_g.open(results_dir + "_dynamic_array_exc_feedback_synapses_g_2618089291", ios::binary | ios::out);
    if(outfile__dynamic_array_exc_feedback_synapses_g.is_open())
    {
        if (! _dynamic_array_exc_feedback_synapses_g.empty() )
        {
            outfile__dynamic_array_exc_feedback_synapses_g.write(reinterpret_cast<char*>(&_dynamic_array_exc_feedback_synapses_g[0]), _dynamic_array_exc_feedback_synapses_g.size()*sizeof(_dynamic_array_exc_feedback_synapses_g[0]));
            outfile__dynamic_array_exc_feedback_synapses_g.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_exc_feedback_synapses_g." << endl;
    }
    ofstream outfile__dynamic_array_exc_feedback_synapses_N_incoming;
    outfile__dynamic_array_exc_feedback_synapses_N_incoming.open(results_dir + "_dynamic_array_exc_feedback_synapses_N_incoming_4053371862", ios::binary | ios::out);
    if(outfile__dynamic_array_exc_feedback_synapses_N_incoming.is_open())
    {
        if (! _dynamic_array_exc_feedback_synapses_N_incoming.empty() )
        {
            outfile__dynamic_array_exc_feedback_synapses_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_exc_feedback_synapses_N_incoming[0]), _dynamic_array_exc_feedback_synapses_N_incoming.size()*sizeof(_dynamic_array_exc_feedback_synapses_N_incoming[0]));
            outfile__dynamic_array_exc_feedback_synapses_N_incoming.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_exc_feedback_synapses_N_incoming." << endl;
    }
    ofstream outfile__dynamic_array_exc_feedback_synapses_N_outgoing;
    outfile__dynamic_array_exc_feedback_synapses_N_outgoing.open(results_dir + "_dynamic_array_exc_feedback_synapses_N_outgoing_3599104780", ios::binary | ios::out);
    if(outfile__dynamic_array_exc_feedback_synapses_N_outgoing.is_open())
    {
        if (! _dynamic_array_exc_feedback_synapses_N_outgoing.empty() )
        {
            outfile__dynamic_array_exc_feedback_synapses_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_exc_feedback_synapses_N_outgoing[0]), _dynamic_array_exc_feedback_synapses_N_outgoing.size()*sizeof(_dynamic_array_exc_feedback_synapses_N_outgoing[0]));
            outfile__dynamic_array_exc_feedback_synapses_N_outgoing.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_exc_feedback_synapses_N_outgoing." << endl;
    }
    ofstream outfile__dynamic_array_exc_feedback_synapses_tau_inact;
    outfile__dynamic_array_exc_feedback_synapses_tau_inact.open(results_dir + "_dynamic_array_exc_feedback_synapses_tau_inact_4204288625", ios::binary | ios::out);
    if(outfile__dynamic_array_exc_feedback_synapses_tau_inact.is_open())
    {
        if (! _dynamic_array_exc_feedback_synapses_tau_inact.empty() )
        {
            outfile__dynamic_array_exc_feedback_synapses_tau_inact.write(reinterpret_cast<char*>(&_dynamic_array_exc_feedback_synapses_tau_inact[0]), _dynamic_array_exc_feedback_synapses_tau_inact.size()*sizeof(_dynamic_array_exc_feedback_synapses_tau_inact[0]));
            outfile__dynamic_array_exc_feedback_synapses_tau_inact.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_exc_feedback_synapses_tau_inact." << endl;
    }
    ofstream outfile__dynamic_array_exc_feedback_synapses_weight;
    outfile__dynamic_array_exc_feedback_synapses_weight.open(results_dir + "_dynamic_array_exc_feedback_synapses_weight_3760636152", ios::binary | ios::out);
    if(outfile__dynamic_array_exc_feedback_synapses_weight.is_open())
    {
        if (! _dynamic_array_exc_feedback_synapses_weight.empty() )
        {
            outfile__dynamic_array_exc_feedback_synapses_weight.write(reinterpret_cast<char*>(&_dynamic_array_exc_feedback_synapses_weight[0]), _dynamic_array_exc_feedback_synapses_weight.size()*sizeof(_dynamic_array_exc_feedback_synapses_weight[0]));
            outfile__dynamic_array_exc_feedback_synapses_weight.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_exc_feedback_synapses_weight." << endl;
    }
    ofstream outfile__dynamic_array_exc_recurrent_synapses__synaptic_post;
    outfile__dynamic_array_exc_recurrent_synapses__synaptic_post.open(results_dir + "_dynamic_array_exc_recurrent_synapses__synaptic_post_4280877876", ios::binary | ios::out);
    if(outfile__dynamic_array_exc_recurrent_synapses__synaptic_post.is_open())
    {
        if (! _dynamic_array_exc_recurrent_synapses__synaptic_post.empty() )
        {
            outfile__dynamic_array_exc_recurrent_synapses__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_exc_recurrent_synapses__synaptic_post[0]), _dynamic_array_exc_recurrent_synapses__synaptic_post.size()*sizeof(_dynamic_array_exc_recurrent_synapses__synaptic_post[0]));
            outfile__dynamic_array_exc_recurrent_synapses__synaptic_post.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_exc_recurrent_synapses__synaptic_post." << endl;
    }
    ofstream outfile__dynamic_array_exc_recurrent_synapses__synaptic_pre;
    outfile__dynamic_array_exc_recurrent_synapses__synaptic_pre.open(results_dir + "_dynamic_array_exc_recurrent_synapses__synaptic_pre_582741446", ios::binary | ios::out);
    if(outfile__dynamic_array_exc_recurrent_synapses__synaptic_pre.is_open())
    {
        if (! _dynamic_array_exc_recurrent_synapses__synaptic_pre.empty() )
        {
            outfile__dynamic_array_exc_recurrent_synapses__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_exc_recurrent_synapses__synaptic_pre[0]), _dynamic_array_exc_recurrent_synapses__synaptic_pre.size()*sizeof(_dynamic_array_exc_recurrent_synapses__synaptic_pre[0]));
            outfile__dynamic_array_exc_recurrent_synapses__synaptic_pre.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_exc_recurrent_synapses__synaptic_pre." << endl;
    }
    ofstream outfile__dynamic_array_exc_recurrent_synapses_delay;
    outfile__dynamic_array_exc_recurrent_synapses_delay.open(results_dir + "_dynamic_array_exc_recurrent_synapses_delay_3316926404", ios::binary | ios::out);
    if(outfile__dynamic_array_exc_recurrent_synapses_delay.is_open())
    {
        if (! _dynamic_array_exc_recurrent_synapses_delay.empty() )
        {
            outfile__dynamic_array_exc_recurrent_synapses_delay.write(reinterpret_cast<char*>(&_dynamic_array_exc_recurrent_synapses_delay[0]), _dynamic_array_exc_recurrent_synapses_delay.size()*sizeof(_dynamic_array_exc_recurrent_synapses_delay[0]));
            outfile__dynamic_array_exc_recurrent_synapses_delay.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_exc_recurrent_synapses_delay." << endl;
    }
    ofstream outfile__dynamic_array_exc_recurrent_synapses_g;
    outfile__dynamic_array_exc_recurrent_synapses_g.open(results_dir + "_dynamic_array_exc_recurrent_synapses_g_2660389258", ios::binary | ios::out);
    if(outfile__dynamic_array_exc_recurrent_synapses_g.is_open())
    {
        if (! _dynamic_array_exc_recurrent_synapses_g.empty() )
        {
            outfile__dynamic_array_exc_recurrent_synapses_g.write(reinterpret_cast<char*>(&_dynamic_array_exc_recurrent_synapses_g[0]), _dynamic_array_exc_recurrent_synapses_g.size()*sizeof(_dynamic_array_exc_recurrent_synapses_g[0]));
            outfile__dynamic_array_exc_recurrent_synapses_g.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_exc_recurrent_synapses_g." << endl;
    }
    ofstream outfile__dynamic_array_exc_recurrent_synapses_N_incoming;
    outfile__dynamic_array_exc_recurrent_synapses_N_incoming.open(results_dir + "_dynamic_array_exc_recurrent_synapses_N_incoming_3937118047", ios::binary | ios::out);
    if(outfile__dynamic_array_exc_recurrent_synapses_N_incoming.is_open())
    {
        if (! _dynamic_array_exc_recurrent_synapses_N_incoming.empty() )
        {
            outfile__dynamic_array_exc_recurrent_synapses_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_exc_recurrent_synapses_N_incoming[0]), _dynamic_array_exc_recurrent_synapses_N_incoming.size()*sizeof(_dynamic_array_exc_recurrent_synapses_N_incoming[0]));
            outfile__dynamic_array_exc_recurrent_synapses_N_incoming.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_exc_recurrent_synapses_N_incoming." << endl;
    }
    ofstream outfile__dynamic_array_exc_recurrent_synapses_N_outgoing;
    outfile__dynamic_array_exc_recurrent_synapses_N_outgoing.open(results_dir + "_dynamic_array_exc_recurrent_synapses_N_outgoing_3451377541", ios::binary | ios::out);
    if(outfile__dynamic_array_exc_recurrent_synapses_N_outgoing.is_open())
    {
        if (! _dynamic_array_exc_recurrent_synapses_N_outgoing.empty() )
        {
            outfile__dynamic_array_exc_recurrent_synapses_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_exc_recurrent_synapses_N_outgoing[0]), _dynamic_array_exc_recurrent_synapses_N_outgoing.size()*sizeof(_dynamic_array_exc_recurrent_synapses_N_outgoing[0]));
            outfile__dynamic_array_exc_recurrent_synapses_N_outgoing.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_exc_recurrent_synapses_N_outgoing." << endl;
    }
    ofstream outfile__dynamic_array_exc_recurrent_synapses_tau_inact;
    outfile__dynamic_array_exc_recurrent_synapses_tau_inact.open(results_dir + "_dynamic_array_exc_recurrent_synapses_tau_inact_3373377572", ios::binary | ios::out);
    if(outfile__dynamic_array_exc_recurrent_synapses_tau_inact.is_open())
    {
        if (! _dynamic_array_exc_recurrent_synapses_tau_inact.empty() )
        {
            outfile__dynamic_array_exc_recurrent_synapses_tau_inact.write(reinterpret_cast<char*>(&_dynamic_array_exc_recurrent_synapses_tau_inact[0]), _dynamic_array_exc_recurrent_synapses_tau_inact.size()*sizeof(_dynamic_array_exc_recurrent_synapses_tau_inact[0]));
            outfile__dynamic_array_exc_recurrent_synapses_tau_inact.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_exc_recurrent_synapses_tau_inact." << endl;
    }
    ofstream outfile__dynamic_array_exc_recurrent_synapses_weight;
    outfile__dynamic_array_exc_recurrent_synapses_weight.open(results_dir + "_dynamic_array_exc_recurrent_synapses_weight_4235081699", ios::binary | ios::out);
    if(outfile__dynamic_array_exc_recurrent_synapses_weight.is_open())
    {
        if (! _dynamic_array_exc_recurrent_synapses_weight.empty() )
        {
            outfile__dynamic_array_exc_recurrent_synapses_weight.write(reinterpret_cast<char*>(&_dynamic_array_exc_recurrent_synapses_weight[0]), _dynamic_array_exc_recurrent_synapses_weight.size()*sizeof(_dynamic_array_exc_recurrent_synapses_weight[0]));
            outfile__dynamic_array_exc_recurrent_synapses_weight.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_exc_recurrent_synapses_weight." << endl;
    }
    ofstream outfile__dynamic_array_inh_synapses__synaptic_post;
    outfile__dynamic_array_inh_synapses__synaptic_post.open(results_dir + "_dynamic_array_inh_synapses__synaptic_post_1631671701", ios::binary | ios::out);
    if(outfile__dynamic_array_inh_synapses__synaptic_post.is_open())
    {
        if (! _dynamic_array_inh_synapses__synaptic_post.empty() )
        {
            outfile__dynamic_array_inh_synapses__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_inh_synapses__synaptic_post[0]), _dynamic_array_inh_synapses__synaptic_post.size()*sizeof(_dynamic_array_inh_synapses__synaptic_post[0]));
            outfile__dynamic_array_inh_synapses__synaptic_post.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_inh_synapses__synaptic_post." << endl;
    }
    ofstream outfile__dynamic_array_inh_synapses__synaptic_pre;
    outfile__dynamic_array_inh_synapses__synaptic_pre.open(results_dir + "_dynamic_array_inh_synapses__synaptic_pre_779677633", ios::binary | ios::out);
    if(outfile__dynamic_array_inh_synapses__synaptic_pre.is_open())
    {
        if (! _dynamic_array_inh_synapses__synaptic_pre.empty() )
        {
            outfile__dynamic_array_inh_synapses__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_inh_synapses__synaptic_pre[0]), _dynamic_array_inh_synapses__synaptic_pre.size()*sizeof(_dynamic_array_inh_synapses__synaptic_pre[0]));
            outfile__dynamic_array_inh_synapses__synaptic_pre.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_inh_synapses__synaptic_pre." << endl;
    }
    ofstream outfile__dynamic_array_inh_synapses_delay;
    outfile__dynamic_array_inh_synapses_delay.open(results_dir + "_dynamic_array_inh_synapses_delay_4219424348", ios::binary | ios::out);
    if(outfile__dynamic_array_inh_synapses_delay.is_open())
    {
        if (! _dynamic_array_inh_synapses_delay.empty() )
        {
            outfile__dynamic_array_inh_synapses_delay.write(reinterpret_cast<char*>(&_dynamic_array_inh_synapses_delay[0]), _dynamic_array_inh_synapses_delay.size()*sizeof(_dynamic_array_inh_synapses_delay[0]));
            outfile__dynamic_array_inh_synapses_delay.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_inh_synapses_delay." << endl;
    }
    ofstream outfile__dynamic_array_inh_synapses_g;
    outfile__dynamic_array_inh_synapses_g.open(results_dir + "_dynamic_array_inh_synapses_g_1927327076", ios::binary | ios::out);
    if(outfile__dynamic_array_inh_synapses_g.is_open())
    {
        if (! _dynamic_array_inh_synapses_g.empty() )
        {
            outfile__dynamic_array_inh_synapses_g.write(reinterpret_cast<char*>(&_dynamic_array_inh_synapses_g[0]), _dynamic_array_inh_synapses_g.size()*sizeof(_dynamic_array_inh_synapses_g[0]));
            outfile__dynamic_array_inh_synapses_g.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_inh_synapses_g." << endl;
    }
    ofstream outfile__dynamic_array_inh_synapses_N_incoming;
    outfile__dynamic_array_inh_synapses_N_incoming.open(results_dir + "_dynamic_array_inh_synapses_N_incoming_2867521240", ios::binary | ios::out);
    if(outfile__dynamic_array_inh_synapses_N_incoming.is_open())
    {
        if (! _dynamic_array_inh_synapses_N_incoming.empty() )
        {
            outfile__dynamic_array_inh_synapses_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_inh_synapses_N_incoming[0]), _dynamic_array_inh_synapses_N_incoming.size()*sizeof(_dynamic_array_inh_synapses_N_incoming[0]));
            outfile__dynamic_array_inh_synapses_N_incoming.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_inh_synapses_N_incoming." << endl;
    }
    ofstream outfile__dynamic_array_inh_synapses_N_outgoing;
    outfile__dynamic_array_inh_synapses_N_outgoing.open(results_dir + "_dynamic_array_inh_synapses_N_outgoing_2381747714", ios::binary | ios::out);
    if(outfile__dynamic_array_inh_synapses_N_outgoing.is_open())
    {
        if (! _dynamic_array_inh_synapses_N_outgoing.empty() )
        {
            outfile__dynamic_array_inh_synapses_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_inh_synapses_N_outgoing[0]), _dynamic_array_inh_synapses_N_outgoing.size()*sizeof(_dynamic_array_inh_synapses_N_outgoing[0]));
            outfile__dynamic_array_inh_synapses_N_outgoing.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_inh_synapses_N_outgoing." << endl;
    }
    ofstream outfile__dynamic_array_inh_synapses_tau_inact;
    outfile__dynamic_array_inh_synapses_tau_inact.open(results_dir + "_dynamic_array_inh_synapses_tau_inact_1465600462", ios::binary | ios::out);
    if(outfile__dynamic_array_inh_synapses_tau_inact.is_open())
    {
        if (! _dynamic_array_inh_synapses_tau_inact.empty() )
        {
            outfile__dynamic_array_inh_synapses_tau_inact.write(reinterpret_cast<char*>(&_dynamic_array_inh_synapses_tau_inact[0]), _dynamic_array_inh_synapses_tau_inact.size()*sizeof(_dynamic_array_inh_synapses_tau_inact[0]));
            outfile__dynamic_array_inh_synapses_tau_inact.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_inh_synapses_tau_inact." << endl;
    }
    ofstream outfile__dynamic_array_inh_synapses_weight;
    outfile__dynamic_array_inh_synapses_weight.open(results_dir + "_dynamic_array_inh_synapses_weight_42264476", ios::binary | ios::out);
    if(outfile__dynamic_array_inh_synapses_weight.is_open())
    {
        if (! _dynamic_array_inh_synapses_weight.empty() )
        {
            outfile__dynamic_array_inh_synapses_weight.write(reinterpret_cast<char*>(&_dynamic_array_inh_synapses_weight[0]), _dynamic_array_inh_synapses_weight.size()*sizeof(_dynamic_array_inh_synapses_weight[0]));
            outfile__dynamic_array_inh_synapses_weight.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_inh_synapses_weight." << endl;
    }
    ofstream outfile__dynamic_array_M_exc_t;
    outfile__dynamic_array_M_exc_t.open(results_dir + "_dynamic_array_M_exc_t_1435475181", ios::binary | ios::out);
    if(outfile__dynamic_array_M_exc_t.is_open())
    {
        if (! _dynamic_array_M_exc_t.empty() )
        {
            outfile__dynamic_array_M_exc_t.write(reinterpret_cast<char*>(&_dynamic_array_M_exc_t[0]), _dynamic_array_M_exc_t.size()*sizeof(_dynamic_array_M_exc_t[0]));
            outfile__dynamic_array_M_exc_t.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_exc_t." << endl;
    }
    ofstream outfile__dynamic_array_M_inh_t;
    outfile__dynamic_array_M_inh_t.open(results_dir + "_dynamic_array_M_inh_t_3914896974", ios::binary | ios::out);
    if(outfile__dynamic_array_M_inh_t.is_open())
    {
        if (! _dynamic_array_M_inh_t.empty() )
        {
            outfile__dynamic_array_M_inh_t.write(reinterpret_cast<char*>(&_dynamic_array_M_inh_t[0]), _dynamic_array_M_inh_t.size()*sizeof(_dynamic_array_M_inh_t[0]));
            outfile__dynamic_array_M_inh_t.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_inh_t." << endl;
    }
    ofstream outfile__dynamic_array_M_syn_t;
    outfile__dynamic_array_M_syn_t.open(results_dir + "_dynamic_array_M_syn_t_172690169", ios::binary | ios::out);
    if(outfile__dynamic_array_M_syn_t.is_open())
    {
        if (! _dynamic_array_M_syn_t.empty() )
        {
            outfile__dynamic_array_M_syn_t.write(reinterpret_cast<char*>(&_dynamic_array_M_syn_t[0]), _dynamic_array_M_syn_t.size()*sizeof(_dynamic_array_M_syn_t[0]));
            outfile__dynamic_array_M_syn_t.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_syn_t." << endl;
    }
    ofstream outfile__dynamic_array_S_i;
    outfile__dynamic_array_S_i.open(results_dir + "_dynamic_array_S_i_3640783844", ios::binary | ios::out);
    if(outfile__dynamic_array_S_i.is_open())
    {
        if (! _dynamic_array_S_i.empty() )
        {
            outfile__dynamic_array_S_i.write(reinterpret_cast<char*>(&_dynamic_array_S_i[0]), _dynamic_array_S_i.size()*sizeof(_dynamic_array_S_i[0]));
            outfile__dynamic_array_S_i.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_S_i." << endl;
    }
    ofstream outfile__dynamic_array_S_t;
    outfile__dynamic_array_S_t.open(results_dir + "_dynamic_array_S_t_3121061693", ios::binary | ios::out);
    if(outfile__dynamic_array_S_t.is_open())
    {
        if (! _dynamic_array_S_t.empty() )
        {
            outfile__dynamic_array_S_t.write(reinterpret_cast<char*>(&_dynamic_array_S_t[0]), _dynamic_array_S_t.size()*sizeof(_dynamic_array_S_t[0]));
            outfile__dynamic_array_S_t.close();
        }
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_S_t." << endl;
    }

    ofstream outfile__dynamic_array_M_exc_a;
    outfile__dynamic_array_M_exc_a.open(results_dir + "_dynamic_array_M_exc_a_944928774", ios::binary | ios::out);
    if(outfile__dynamic_array_M_exc_a.is_open())
    {
        for (int n=0; n<_dynamic_array_M_exc_a.n; n++)
        {
            if (! _dynamic_array_M_exc_a(n).empty())
            {
                outfile__dynamic_array_M_exc_a.write(reinterpret_cast<char*>(&_dynamic_array_M_exc_a(n, 0)), _dynamic_array_M_exc_a.m*sizeof(_dynamic_array_M_exc_a(0, 0)));
            }
        }
        outfile__dynamic_array_M_exc_a.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_exc_a." << endl;
    }
    ofstream outfile__dynamic_array_M_exc_b;
    outfile__dynamic_array_M_exc_b.open(results_dir + "_dynamic_array_M_exc_b_2707106236", ios::binary | ios::out);
    if(outfile__dynamic_array_M_exc_b.is_open())
    {
        for (int n=0; n<_dynamic_array_M_exc_b.n; n++)
        {
            if (! _dynamic_array_M_exc_b(n).empty())
            {
                outfile__dynamic_array_M_exc_b.write(reinterpret_cast<char*>(&_dynamic_array_M_exc_b(n, 0)), _dynamic_array_M_exc_b.m*sizeof(_dynamic_array_M_exc_b(0, 0)));
            }
        }
        outfile__dynamic_array_M_exc_b.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_exc_b." << endl;
    }
    ofstream outfile__dynamic_array_M_exc_C;
    outfile__dynamic_array_M_exc_C.open(results_dir + "_dynamic_array_M_exc_C_3979491810", ios::binary | ios::out);
    if(outfile__dynamic_array_M_exc_C.is_open())
    {
        for (int n=0; n<_dynamic_array_M_exc_C.n; n++)
        {
            if (! _dynamic_array_M_exc_C(n).empty())
            {
                outfile__dynamic_array_M_exc_C.write(reinterpret_cast<char*>(&_dynamic_array_M_exc_C(n, 0)), _dynamic_array_M_exc_C.m*sizeof(_dynamic_array_M_exc_C(0, 0)));
            }
        }
        outfile__dynamic_array_M_exc_C.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_exc_C." << endl;
    }
    ofstream outfile__dynamic_array_M_exc_DeltaT;
    outfile__dynamic_array_M_exc_DeltaT.open(results_dir + "_dynamic_array_M_exc_DeltaT_2870339439", ios::binary | ios::out);
    if(outfile__dynamic_array_M_exc_DeltaT.is_open())
    {
        for (int n=0; n<_dynamic_array_M_exc_DeltaT.n; n++)
        {
            if (! _dynamic_array_M_exc_DeltaT(n).empty())
            {
                outfile__dynamic_array_M_exc_DeltaT.write(reinterpret_cast<char*>(&_dynamic_array_M_exc_DeltaT(n, 0)), _dynamic_array_M_exc_DeltaT.m*sizeof(_dynamic_array_M_exc_DeltaT(0, 0)));
            }
        }
        outfile__dynamic_array_M_exc_DeltaT.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_exc_DeltaT." << endl;
    }
    ofstream outfile__dynamic_array_M_exc_EEx;
    outfile__dynamic_array_M_exc_EEx.open(results_dir + "_dynamic_array_M_exc_EEx_2781468759", ios::binary | ios::out);
    if(outfile__dynamic_array_M_exc_EEx.is_open())
    {
        for (int n=0; n<_dynamic_array_M_exc_EEx.n; n++)
        {
            if (! _dynamic_array_M_exc_EEx(n).empty())
            {
                outfile__dynamic_array_M_exc_EEx.write(reinterpret_cast<char*>(&_dynamic_array_M_exc_EEx(n, 0)), _dynamic_array_M_exc_EEx.m*sizeof(_dynamic_array_M_exc_EEx(0, 0)));
            }
        }
        outfile__dynamic_array_M_exc_EEx.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_exc_EEx." << endl;
    }
    ofstream outfile__dynamic_array_M_exc_EIn;
    outfile__dynamic_array_M_exc_EIn.open(results_dir + "_dynamic_array_M_exc_EIn_4255654410", ios::binary | ios::out);
    if(outfile__dynamic_array_M_exc_EIn.is_open())
    {
        for (int n=0; n<_dynamic_array_M_exc_EIn.n; n++)
        {
            if (! _dynamic_array_M_exc_EIn(n).empty())
            {
                outfile__dynamic_array_M_exc_EIn.write(reinterpret_cast<char*>(&_dynamic_array_M_exc_EIn(n, 0)), _dynamic_array_M_exc_EIn.m*sizeof(_dynamic_array_M_exc_EIn(0, 0)));
            }
        }
        outfile__dynamic_array_M_exc_EIn.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_exc_EIn." << endl;
    }
    ofstream outfile__dynamic_array_M_exc_EL;
    outfile__dynamic_array_M_exc_EL.open(results_dir + "_dynamic_array_M_exc_EL_3051091165", ios::binary | ios::out);
    if(outfile__dynamic_array_M_exc_EL.is_open())
    {
        for (int n=0; n<_dynamic_array_M_exc_EL.n; n++)
        {
            if (! _dynamic_array_M_exc_EL(n).empty())
            {
                outfile__dynamic_array_M_exc_EL.write(reinterpret_cast<char*>(&_dynamic_array_M_exc_EL(n, 0)), _dynamic_array_M_exc_EL.m*sizeof(_dynamic_array_M_exc_EL(0, 0)));
            }
        }
        outfile__dynamic_array_M_exc_EL.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_exc_EL." << endl;
    }
    ofstream outfile__dynamic_array_M_exc_ge;
    outfile__dynamic_array_M_exc_ge.open(results_dir + "_dynamic_array_M_exc_ge_1356540561", ios::binary | ios::out);
    if(outfile__dynamic_array_M_exc_ge.is_open())
    {
        for (int n=0; n<_dynamic_array_M_exc_ge.n; n++)
        {
            if (! _dynamic_array_M_exc_ge(n).empty())
            {
                outfile__dynamic_array_M_exc_ge.write(reinterpret_cast<char*>(&_dynamic_array_M_exc_ge(n, 0)), _dynamic_array_M_exc_ge.m*sizeof(_dynamic_array_M_exc_ge(0, 0)));
            }
        }
        outfile__dynamic_array_M_exc_ge.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_exc_ge." << endl;
    }
    ofstream outfile__dynamic_array_M_exc_gi;
    outfile__dynamic_array_M_exc_gi.open(results_dir + "_dynamic_array_M_exc_gi_1500341946", ios::binary | ios::out);
    if(outfile__dynamic_array_M_exc_gi.is_open())
    {
        for (int n=0; n<_dynamic_array_M_exc_gi.n; n++)
        {
            if (! _dynamic_array_M_exc_gi(n).empty())
            {
                outfile__dynamic_array_M_exc_gi.write(reinterpret_cast<char*>(&_dynamic_array_M_exc_gi(n, 0)), _dynamic_array_M_exc_gi.m*sizeof(_dynamic_array_M_exc_gi(0, 0)));
            }
        }
        outfile__dynamic_array_M_exc_gi.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_exc_gi." << endl;
    }
    ofstream outfile__dynamic_array_M_exc_gL;
    outfile__dynamic_array_M_exc_gL.open(results_dir + "_dynamic_array_M_exc_gL_308916989", ios::binary | ios::out);
    if(outfile__dynamic_array_M_exc_gL.is_open())
    {
        for (int n=0; n<_dynamic_array_M_exc_gL.n; n++)
        {
            if (! _dynamic_array_M_exc_gL(n).empty())
            {
                outfile__dynamic_array_M_exc_gL.write(reinterpret_cast<char*>(&_dynamic_array_M_exc_gL(n, 0)), _dynamic_array_M_exc_gL.m*sizeof(_dynamic_array_M_exc_gL(0, 0)));
            }
        }
        outfile__dynamic_array_M_exc_gL.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_exc_gL." << endl;
    }
    ofstream outfile__dynamic_array_M_exc_I;
    outfile__dynamic_array_M_exc_I.open(results_dir + "_dynamic_array_M_exc_I_233296124", ios::binary | ios::out);
    if(outfile__dynamic_array_M_exc_I.is_open())
    {
        for (int n=0; n<_dynamic_array_M_exc_I.n; n++)
        {
            if (! _dynamic_array_M_exc_I(n).empty())
            {
                outfile__dynamic_array_M_exc_I.write(reinterpret_cast<char*>(&_dynamic_array_M_exc_I(n, 0)), _dynamic_array_M_exc_I.m*sizeof(_dynamic_array_M_exc_I(0, 0)));
            }
        }
        outfile__dynamic_array_M_exc_I.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_exc_I." << endl;
    }
    ofstream outfile__dynamic_array_M_exc_I_AMPA;
    outfile__dynamic_array_M_exc_I_AMPA.open(results_dir + "_dynamic_array_M_exc_I_AMPA_779623987", ios::binary | ios::out);
    if(outfile__dynamic_array_M_exc_I_AMPA.is_open())
    {
        for (int n=0; n<_dynamic_array_M_exc_I_AMPA.n; n++)
        {
            if (! _dynamic_array_M_exc_I_AMPA(n).empty())
            {
                outfile__dynamic_array_M_exc_I_AMPA.write(reinterpret_cast<char*>(&_dynamic_array_M_exc_I_AMPA(n, 0)), _dynamic_array_M_exc_I_AMPA.m*sizeof(_dynamic_array_M_exc_I_AMPA(0, 0)));
            }
        }
        outfile__dynamic_array_M_exc_I_AMPA.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_exc_I_AMPA." << endl;
    }
    ofstream outfile__dynamic_array_M_exc_I_GABA;
    outfile__dynamic_array_M_exc_I_GABA.open(results_dir + "_dynamic_array_M_exc_I_GABA_2063452248", ios::binary | ios::out);
    if(outfile__dynamic_array_M_exc_I_GABA.is_open())
    {
        for (int n=0; n<_dynamic_array_M_exc_I_GABA.n; n++)
        {
            if (! _dynamic_array_M_exc_I_GABA(n).empty())
            {
                outfile__dynamic_array_M_exc_I_GABA.write(reinterpret_cast<char*>(&_dynamic_array_M_exc_I_GABA(n, 0)), _dynamic_array_M_exc_I_GABA.m*sizeof(_dynamic_array_M_exc_I_GABA(0, 0)));
            }
        }
        outfile__dynamic_array_M_exc_I_GABA.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_exc_I_GABA." << endl;
    }
    ofstream outfile__dynamic_array_M_exc_I_total;
    outfile__dynamic_array_M_exc_I_total.open(results_dir + "_dynamic_array_M_exc_I_total_3770827051", ios::binary | ios::out);
    if(outfile__dynamic_array_M_exc_I_total.is_open())
    {
        for (int n=0; n<_dynamic_array_M_exc_I_total.n; n++)
        {
            if (! _dynamic_array_M_exc_I_total(n).empty())
            {
                outfile__dynamic_array_M_exc_I_total.write(reinterpret_cast<char*>(&_dynamic_array_M_exc_I_total(n, 0)), _dynamic_array_M_exc_I_total.m*sizeof(_dynamic_array_M_exc_I_total(0, 0)));
            }
        }
        outfile__dynamic_array_M_exc_I_total.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_exc_I_total." << endl;
    }
    ofstream outfile__dynamic_array_M_exc_tau_w;
    outfile__dynamic_array_M_exc_tau_w.open(results_dir + "_dynamic_array_M_exc_tau_w_1956690251", ios::binary | ios::out);
    if(outfile__dynamic_array_M_exc_tau_w.is_open())
    {
        for (int n=0; n<_dynamic_array_M_exc_tau_w.n; n++)
        {
            if (! _dynamic_array_M_exc_tau_w(n).empty())
            {
                outfile__dynamic_array_M_exc_tau_w.write(reinterpret_cast<char*>(&_dynamic_array_M_exc_tau_w(n, 0)), _dynamic_array_M_exc_tau_w.m*sizeof(_dynamic_array_M_exc_tau_w(0, 0)));
            }
        }
        outfile__dynamic_array_M_exc_tau_w.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_exc_tau_w." << endl;
    }
    ofstream outfile__dynamic_array_M_exc_v;
    outfile__dynamic_array_M_exc_v.open(results_dir + "_dynamic_array_M_exc_v_3145858497", ios::binary | ios::out);
    if(outfile__dynamic_array_M_exc_v.is_open())
    {
        for (int n=0; n<_dynamic_array_M_exc_v.n; n++)
        {
            if (! _dynamic_array_M_exc_v(n).empty())
            {
                outfile__dynamic_array_M_exc_v.write(reinterpret_cast<char*>(&_dynamic_array_M_exc_v(n, 0)), _dynamic_array_M_exc_v.m*sizeof(_dynamic_array_M_exc_v(0, 0)));
            }
        }
        outfile__dynamic_array_M_exc_v.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_exc_v." << endl;
    }
    ofstream outfile__dynamic_array_M_exc_Vr;
    outfile__dynamic_array_M_exc_Vr.open(results_dir + "_dynamic_array_M_exc_Vr_357935332", ios::binary | ios::out);
    if(outfile__dynamic_array_M_exc_Vr.is_open())
    {
        for (int n=0; n<_dynamic_array_M_exc_Vr.n; n++)
        {
            if (! _dynamic_array_M_exc_Vr(n).empty())
            {
                outfile__dynamic_array_M_exc_Vr.write(reinterpret_cast<char*>(&_dynamic_array_M_exc_Vr(n, 0)), _dynamic_array_M_exc_Vr.m*sizeof(_dynamic_array_M_exc_Vr(0, 0)));
            }
        }
        outfile__dynamic_array_M_exc_Vr.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_exc_Vr." << endl;
    }
    ofstream outfile__dynamic_array_M_exc_VT;
    outfile__dynamic_array_M_exc_VT.open(results_dir + "_dynamic_array_M_exc_VT_3344444697", ios::binary | ios::out);
    if(outfile__dynamic_array_M_exc_VT.is_open())
    {
        for (int n=0; n<_dynamic_array_M_exc_VT.n; n++)
        {
            if (! _dynamic_array_M_exc_VT(n).empty())
            {
                outfile__dynamic_array_M_exc_VT.write(reinterpret_cast<char*>(&_dynamic_array_M_exc_VT(n, 0)), _dynamic_array_M_exc_VT.m*sizeof(_dynamic_array_M_exc_VT(0, 0)));
            }
        }
        outfile__dynamic_array_M_exc_VT.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_exc_VT." << endl;
    }
    ofstream outfile__dynamic_array_M_exc_w;
    outfile__dynamic_array_M_exc_w.open(results_dir + "_dynamic_array_M_exc_w_3431386455", ios::binary | ios::out);
    if(outfile__dynamic_array_M_exc_w.is_open())
    {
        for (int n=0; n<_dynamic_array_M_exc_w.n; n++)
        {
            if (! _dynamic_array_M_exc_w(n).empty())
            {
                outfile__dynamic_array_M_exc_w.write(reinterpret_cast<char*>(&_dynamic_array_M_exc_w(n, 0)), _dynamic_array_M_exc_w.m*sizeof(_dynamic_array_M_exc_w(0, 0)));
            }
        }
        outfile__dynamic_array_M_exc_w.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_exc_w." << endl;
    }
    ofstream outfile__dynamic_array_M_inh_a;
    outfile__dynamic_array_M_inh_a.open(results_dir + "_dynamic_array_M_inh_a_2223338149", ios::binary | ios::out);
    if(outfile__dynamic_array_M_inh_a.is_open())
    {
        for (int n=0; n<_dynamic_array_M_inh_a.n; n++)
        {
            if (! _dynamic_array_M_inh_a(n).empty())
            {
                outfile__dynamic_array_M_inh_a.write(reinterpret_cast<char*>(&_dynamic_array_M_inh_a(n, 0)), _dynamic_array_M_inh_a.m*sizeof(_dynamic_array_M_inh_a(0, 0)));
            }
        }
        outfile__dynamic_array_M_inh_a.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_inh_a." << endl;
    }
    ofstream outfile__dynamic_array_M_inh_b;
    outfile__dynamic_array_M_inh_b.open(results_dir + "_dynamic_array_M_inh_b_495723295", ios::binary | ios::out);
    if(outfile__dynamic_array_M_inh_b.is_open())
    {
        for (int n=0; n<_dynamic_array_M_inh_b.n; n++)
        {
            if (! _dynamic_array_M_inh_b(n).empty())
            {
                outfile__dynamic_array_M_inh_b.write(reinterpret_cast<char*>(&_dynamic_array_M_inh_b(n, 0)), _dynamic_array_M_inh_b.m*sizeof(_dynamic_array_M_inh_b(0, 0)));
            }
        }
        outfile__dynamic_array_M_inh_b.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_inh_b." << endl;
    }
    ofstream outfile__dynamic_array_M_inh_C;
    outfile__dynamic_array_M_inh_C.open(results_dir + "_dynamic_array_M_inh_C_1373975361", ios::binary | ios::out);
    if(outfile__dynamic_array_M_inh_C.is_open())
    {
        for (int n=0; n<_dynamic_array_M_inh_C.n; n++)
        {
            if (! _dynamic_array_M_inh_C(n).empty())
            {
                outfile__dynamic_array_M_inh_C.write(reinterpret_cast<char*>(&_dynamic_array_M_inh_C(n, 0)), _dynamic_array_M_inh_C.m*sizeof(_dynamic_array_M_inh_C(0, 0)));
            }
        }
        outfile__dynamic_array_M_inh_C.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_inh_C." << endl;
    }
    ofstream outfile__dynamic_array_M_inh_DeltaT;
    outfile__dynamic_array_M_inh_DeltaT.open(results_dir + "_dynamic_array_M_inh_DeltaT_865673292", ios::binary | ios::out);
    if(outfile__dynamic_array_M_inh_DeltaT.is_open())
    {
        for (int n=0; n<_dynamic_array_M_inh_DeltaT.n; n++)
        {
            if (! _dynamic_array_M_inh_DeltaT(n).empty())
            {
                outfile__dynamic_array_M_inh_DeltaT.write(reinterpret_cast<char*>(&_dynamic_array_M_inh_DeltaT(n, 0)), _dynamic_array_M_inh_DeltaT.m*sizeof(_dynamic_array_M_inh_DeltaT(0, 0)));
            }
        }
        outfile__dynamic_array_M_inh_DeltaT.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_inh_DeltaT." << endl;
    }
    ofstream outfile__dynamic_array_M_inh_EEx;
    outfile__dynamic_array_M_inh_EEx.open(results_dir + "_dynamic_array_M_inh_EEx_3224789684", ios::binary | ios::out);
    if(outfile__dynamic_array_M_inh_EEx.is_open())
    {
        for (int n=0; n<_dynamic_array_M_inh_EEx.n; n++)
        {
            if (! _dynamic_array_M_inh_EEx(n).empty())
            {
                outfile__dynamic_array_M_inh_EEx.write(reinterpret_cast<char*>(&_dynamic_array_M_inh_EEx(n, 0)), _dynamic_array_M_inh_EEx.m*sizeof(_dynamic_array_M_inh_EEx(0, 0)));
            }
        }
        outfile__dynamic_array_M_inh_EEx.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_inh_EEx." << endl;
    }
    ofstream outfile__dynamic_array_M_inh_EIn;
    outfile__dynamic_array_M_inh_EIn.open(results_dir + "_dynamic_array_M_inh_EIn_2555877609", ios::binary | ios::out);
    if(outfile__dynamic_array_M_inh_EIn.is_open())
    {
        for (int n=0; n<_dynamic_array_M_inh_EIn.n; n++)
        {
            if (! _dynamic_array_M_inh_EIn(n).empty())
            {
                outfile__dynamic_array_M_inh_EIn.write(reinterpret_cast<char*>(&_dynamic_array_M_inh_EIn(n, 0)), _dynamic_array_M_inh_EIn.m*sizeof(_dynamic_array_M_inh_EIn(0, 0)));
            }
        }
        outfile__dynamic_array_M_inh_EIn.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_inh_EIn." << endl;
    }
    ofstream outfile__dynamic_array_M_inh_EL;
    outfile__dynamic_array_M_inh_EL.open(results_dir + "_dynamic_array_M_inh_EL_4206416261", ios::binary | ios::out);
    if(outfile__dynamic_array_M_inh_EL.is_open())
    {
        for (int n=0; n<_dynamic_array_M_inh_EL.n; n++)
        {
            if (! _dynamic_array_M_inh_EL(n).empty())
            {
                outfile__dynamic_array_M_inh_EL.write(reinterpret_cast<char*>(&_dynamic_array_M_inh_EL(n, 0)), _dynamic_array_M_inh_EL.m*sizeof(_dynamic_array_M_inh_EL(0, 0)));
            }
        }
        outfile__dynamic_array_M_inh_EL.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_inh_EL." << endl;
    }
    ofstream outfile__dynamic_array_M_inh_ge;
    outfile__dynamic_array_M_inh_ge.open(results_dir + "_dynamic_array_M_inh_ge_532156361", ios::binary | ios::out);
    if(outfile__dynamic_array_M_inh_ge.is_open())
    {
        for (int n=0; n<_dynamic_array_M_inh_ge.n; n++)
        {
            if (! _dynamic_array_M_inh_ge(n).empty())
            {
                outfile__dynamic_array_M_inh_ge.write(reinterpret_cast<char*>(&_dynamic_array_M_inh_ge(n, 0)), _dynamic_array_M_inh_ge.m*sizeof(_dynamic_array_M_inh_ge(0, 0)));
            }
        }
        outfile__dynamic_array_M_inh_ge.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_inh_ge." << endl;
    }
    ofstream outfile__dynamic_array_M_inh_gi;
    outfile__dynamic_array_M_inh_gi.open(results_dir + "_dynamic_array_M_inh_gi_370033634", ios::binary | ios::out);
    if(outfile__dynamic_array_M_inh_gi.is_open())
    {
        for (int n=0; n<_dynamic_array_M_inh_gi.n; n++)
        {
            if (! _dynamic_array_M_inh_gi(n).empty())
            {
                outfile__dynamic_array_M_inh_gi.write(reinterpret_cast<char*>(&_dynamic_array_M_inh_gi(n, 0)), _dynamic_array_M_inh_gi.m*sizeof(_dynamic_array_M_inh_gi(0, 0)));
            }
        }
        outfile__dynamic_array_M_inh_gi.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_inh_gi." << endl;
    }
    ofstream outfile__dynamic_array_M_inh_gL;
    outfile__dynamic_array_M_inh_gL.open(results_dir + "_dynamic_array_M_inh_gL_1560975269", ios::binary | ios::out);
    if(outfile__dynamic_array_M_inh_gL.is_open())
    {
        for (int n=0; n<_dynamic_array_M_inh_gL.n; n++)
        {
            if (! _dynamic_array_M_inh_gL(n).empty())
            {
                outfile__dynamic_array_M_inh_gL.write(reinterpret_cast<char*>(&_dynamic_array_M_inh_gL(n, 0)), _dynamic_array_M_inh_gL.m*sizeof(_dynamic_array_M_inh_gL(0, 0)));
            }
        }
        outfile__dynamic_array_M_inh_gL.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_inh_gL." << endl;
    }
    ofstream outfile__dynamic_array_M_inh_I;
    outfile__dynamic_array_M_inh_I.open(results_dir + "_dynamic_array_M_inh_I_2972768863", ios::binary | ios::out);
    if(outfile__dynamic_array_M_inh_I.is_open())
    {
        for (int n=0; n<_dynamic_array_M_inh_I.n; n++)
        {
            if (! _dynamic_array_M_inh_I(n).empty())
            {
                outfile__dynamic_array_M_inh_I.write(reinterpret_cast<char*>(&_dynamic_array_M_inh_I(n, 0)), _dynamic_array_M_inh_I.m*sizeof(_dynamic_array_M_inh_I(0, 0)));
            }
        }
        outfile__dynamic_array_M_inh_I.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_inh_I." << endl;
    }
    ofstream outfile__dynamic_array_M_inh_I_AMPA;
    outfile__dynamic_array_M_inh_I_AMPA.open(results_dir + "_dynamic_array_M_inh_I_AMPA_3069499664", ios::binary | ios::out);
    if(outfile__dynamic_array_M_inh_I_AMPA.is_open())
    {
        for (int n=0; n<_dynamic_array_M_inh_I_AMPA.n; n++)
        {
            if (! _dynamic_array_M_inh_I_AMPA(n).empty())
            {
                outfile__dynamic_array_M_inh_I_AMPA.write(reinterpret_cast<char*>(&_dynamic_array_M_inh_I_AMPA(n, 0)), _dynamic_array_M_inh_I_AMPA.m*sizeof(_dynamic_array_M_inh_I_AMPA(0, 0)));
            }
        }
        outfile__dynamic_array_M_inh_I_AMPA.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_inh_I_AMPA." << endl;
    }
    ofstream outfile__dynamic_array_M_inh_I_GABA;
    outfile__dynamic_array_M_inh_I_GABA.open(results_dir + "_dynamic_array_M_inh_I_GABA_3799060347", ios::binary | ios::out);
    if(outfile__dynamic_array_M_inh_I_GABA.is_open())
    {
        for (int n=0; n<_dynamic_array_M_inh_I_GABA.n; n++)
        {
            if (! _dynamic_array_M_inh_I_GABA(n).empty())
            {
                outfile__dynamic_array_M_inh_I_GABA.write(reinterpret_cast<char*>(&_dynamic_array_M_inh_I_GABA(n, 0)), _dynamic_array_M_inh_I_GABA.m*sizeof(_dynamic_array_M_inh_I_GABA(0, 0)));
            }
        }
        outfile__dynamic_array_M_inh_I_GABA.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_inh_I_GABA." << endl;
    }
    ofstream outfile__dynamic_array_M_inh_I_total;
    outfile__dynamic_array_M_inh_I_total.open(results_dir + "_dynamic_array_M_inh_I_total_1111342238", ios::binary | ios::out);
    if(outfile__dynamic_array_M_inh_I_total.is_open())
    {
        for (int n=0; n<_dynamic_array_M_inh_I_total.n; n++)
        {
            if (! _dynamic_array_M_inh_I_total(n).empty())
            {
                outfile__dynamic_array_M_inh_I_total.write(reinterpret_cast<char*>(&_dynamic_array_M_inh_I_total(n, 0)), _dynamic_array_M_inh_I_total.m*sizeof(_dynamic_array_M_inh_I_total(0, 0)));
            }
        }
        outfile__dynamic_array_M_inh_I_total.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_inh_I_total." << endl;
    }
    ofstream outfile__dynamic_array_M_inh_tau_w;
    outfile__dynamic_array_M_inh_tau_w.open(results_dir + "_dynamic_array_M_inh_tau_w_709305865", ios::binary | ios::out);
    if(outfile__dynamic_array_M_inh_tau_w.is_open())
    {
        for (int n=0; n<_dynamic_array_M_inh_tau_w.n; n++)
        {
            if (! _dynamic_array_M_inh_tau_w(n).empty())
            {
                outfile__dynamic_array_M_inh_tau_w.write(reinterpret_cast<char*>(&_dynamic_array_M_inh_tau_w(n, 0)), _dynamic_array_M_inh_tau_w.m*sizeof(_dynamic_array_M_inh_tau_w(0, 0)));
            }
        }
        outfile__dynamic_array_M_inh_tau_w.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_inh_tau_w." << endl;
    }
    ofstream outfile__dynamic_array_M_inh_v;
    outfile__dynamic_array_M_inh_v.open(results_dir + "_dynamic_array_M_inh_v_123139938", ios::binary | ios::out);
    if(outfile__dynamic_array_M_inh_v.is_open())
    {
        for (int n=0; n<_dynamic_array_M_inh_v.n; n++)
        {
            if (! _dynamic_array_M_inh_v(n).empty())
            {
                outfile__dynamic_array_M_inh_v.write(reinterpret_cast<char*>(&_dynamic_array_M_inh_v(n, 0)), _dynamic_array_M_inh_v.m*sizeof(_dynamic_array_M_inh_v(0, 0)));
            }
        }
        outfile__dynamic_array_M_inh_v.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_inh_v." << endl;
    }
    ofstream outfile__dynamic_array_M_inh_Vr;
    outfile__dynamic_array_M_inh_Vr.open(results_dir + "_dynamic_array_M_inh_Vr_1513524668", ios::binary | ios::out);
    if(outfile__dynamic_array_M_inh_Vr.is_open())
    {
        for (int n=0; n<_dynamic_array_M_inh_Vr.n; n++)
        {
            if (! _dynamic_array_M_inh_Vr(n).empty())
            {
                outfile__dynamic_array_M_inh_Vr.write(reinterpret_cast<char*>(&_dynamic_array_M_inh_Vr(n, 0)), _dynamic_array_M_inh_Vr.m*sizeof(_dynamic_array_M_inh_Vr(0, 0)));
            }
        }
        outfile__dynamic_array_M_inh_Vr.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_inh_Vr." << endl;
    }
    ofstream outfile__dynamic_array_M_inh_VT;
    outfile__dynamic_array_M_inh_VT.open(results_dir + "_dynamic_array_M_inh_VT_2285570113", ios::binary | ios::out);
    if(outfile__dynamic_array_M_inh_VT.is_open())
    {
        for (int n=0; n<_dynamic_array_M_inh_VT.n; n++)
        {
            if (! _dynamic_array_M_inh_VT(n).empty())
            {
                outfile__dynamic_array_M_inh_VT.write(reinterpret_cast<char*>(&_dynamic_array_M_inh_VT(n, 0)), _dynamic_array_M_inh_VT.m*sizeof(_dynamic_array_M_inh_VT(0, 0)));
            }
        }
        outfile__dynamic_array_M_inh_VT.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_inh_VT." << endl;
    }
    ofstream outfile__dynamic_array_M_inh_w;
    outfile__dynamic_array_M_inh_w.open(results_dir + "_dynamic_array_M_inh_w_1884407796", ios::binary | ios::out);
    if(outfile__dynamic_array_M_inh_w.is_open())
    {
        for (int n=0; n<_dynamic_array_M_inh_w.n; n++)
        {
            if (! _dynamic_array_M_inh_w(n).empty())
            {
                outfile__dynamic_array_M_inh_w.write(reinterpret_cast<char*>(&_dynamic_array_M_inh_w(n, 0)), _dynamic_array_M_inh_w.m*sizeof(_dynamic_array_M_inh_w(0, 0)));
            }
        }
        outfile__dynamic_array_M_inh_w.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_inh_w." << endl;
    }
    ofstream outfile__dynamic_array_M_syn_g;
    outfile__dynamic_array_M_syn_g.open(results_dir + "_dynamic_array_M_syn_g_2398440231", ios::binary | ios::out);
    if(outfile__dynamic_array_M_syn_g.is_open())
    {
        for (int n=0; n<_dynamic_array_M_syn_g.n; n++)
        {
            if (! _dynamic_array_M_syn_g(n).empty())
            {
                outfile__dynamic_array_M_syn_g.write(reinterpret_cast<char*>(&_dynamic_array_M_syn_g(n, 0)), _dynamic_array_M_syn_g.m*sizeof(_dynamic_array_M_syn_g(0, 0)));
            }
        }
        outfile__dynamic_array_M_syn_g.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_syn_g." << endl;
    }
    ofstream outfile__dynamic_array_M_syn_tau_inact;
    outfile__dynamic_array_M_syn_tau_inact.open(results_dir + "_dynamic_array_M_syn_tau_inact_1323708825", ios::binary | ios::out);
    if(outfile__dynamic_array_M_syn_tau_inact.is_open())
    {
        for (int n=0; n<_dynamic_array_M_syn_tau_inact.n; n++)
        {
            if (! _dynamic_array_M_syn_tau_inact(n).empty())
            {
                outfile__dynamic_array_M_syn_tau_inact.write(reinterpret_cast<char*>(&_dynamic_array_M_syn_tau_inact(n, 0)), _dynamic_array_M_syn_tau_inact.m*sizeof(_dynamic_array_M_syn_tau_inact(0, 0)));
            }
        }
        outfile__dynamic_array_M_syn_tau_inact.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_syn_tau_inact." << endl;
    }
    ofstream outfile__dynamic_array_M_syn_weight;
    outfile__dynamic_array_M_syn_weight.open(results_dir + "_dynamic_array_M_syn_weight_1277629643", ios::binary | ios::out);
    if(outfile__dynamic_array_M_syn_weight.is_open())
    {
        for (int n=0; n<_dynamic_array_M_syn_weight.n; n++)
        {
            if (! _dynamic_array_M_syn_weight(n).empty())
            {
                outfile__dynamic_array_M_syn_weight.write(reinterpret_cast<char*>(&_dynamic_array_M_syn_weight(n, 0)), _dynamic_array_M_syn_weight.m*sizeof(_dynamic_array_M_syn_weight(0, 0)));
            }
        }
        outfile__dynamic_array_M_syn_weight.close();
    } else
    {
        std::cout << "Error writing output file for _dynamic_array_M_syn_weight." << endl;
    }
    // Write last run info to disk
    ofstream outfile_last_run_info;
    outfile_last_run_info.open(results_dir + "last_run_info.txt", ios::out);
    if(outfile_last_run_info.is_open())
    {
        outfile_last_run_info << (Network::_last_run_time) << " " << (Network::_last_run_completed_fraction) << std::endl;
        outfile_last_run_info.close();
    } else
    {
        std::cout << "Error writing last run info to file." << std::endl;
    }
}

void _dealloc_arrays()
{
    using namespace brian;


    // static arrays
    if(_static_array__array_M_exc__indices!=0)
    {
        delete [] _static_array__array_M_exc__indices;
        _static_array__array_M_exc__indices = 0;
    }
    if(_static_array__array_M_inh__indices!=0)
    {
        delete [] _static_array__array_M_inh__indices;
        _static_array__array_M_inh__indices = 0;
    }
    if(_static_array__array_M_syn__indices!=0)
    {
        delete [] _static_array__array_M_syn__indices;
        _static_array__array_M_syn__indices = 0;
    }
}

