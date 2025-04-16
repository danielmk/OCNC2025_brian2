import brian2 as b2
import numpy as np
import matplotlib.pyplot as plt

from ocncbrian2.synapse_solution import adex_model_string, adex_reset_string
from ocncbrian2.synapse_solution import excitatory_synapse_model_string, inhibitory_synapse_model_string

from dataclasses import dataclass

import pdb

b2.set_device('cpp_standalone', build_on_run=False, directory='standalone_directory')

@dataclass
class RNNSimulatorConstants():
    gL: b2.units.fundamentalunits.Unit  # 10 nano siemens is 100 MOhm
    EL: b2.units.fundamentalunits.Unit  # Resting potential
    VT: b2.units.fundamentalunits.Unit  # Threshold potential
    Vr: b2.units.fundamentalunits.Unit  # Reset potential
    tau_w: b2.units.fundamentalunits.Unit
    a: b2.units.fundamentalunits.Unit
    b: b2.units.fundamentalunits.Unit
    DeltaT: b2.units.fundamentalunits.Unit
    C: b2.units.fundamentalunits.Unit
    EEx: b2.units.fundamentalunits.Unit
    EIn: b2.units.fundamentalunits.Unit
    
@dataclass
class RNNSimulatorParameters():
    exc_mean: float
    exc_sigma: float
    exc_scale: b2.units.fundamentalunits.Unit
    inh_mean: float
    inh_sigma: float
    inh_scale: b2.units.fundamentalunits.Unit


class RNNSimulator():

    def __init__(self, constants: RNNSimulatorConstants, N:int = 500):
        self.N = N
        self.constants = constants
        self.nw = self.make_network()
    
    def make_network(self):
        net = b2.Network()
        
        rnn_neuron_model_string = adex_model_string + '''exc_mean: 1 (constant, shared)
                                                         exc_sigma: 1 (constant, shared)
                                                         exc_scale: siemens (constant, shared)
                                                         inh_mean: 1 (constant, shared)
                                                         inh_sigma: 1 (constant, shared)
                                                         inh_scale: siemens (constant, shared)
                                                         '''

        neurons = b2.NeuronGroup(self.N,
                                 model=rnn_neuron_model_string,
                                 threshold='v>0.0*mV',
                                 reset=adex_reset_string,
                                 method='euler',
                                 name='neurons')
        
        # Set all constant parameters in a single loop0
        for param, value in self.constants.__dict__.items():
            setattr(neurons, param, value)
        
        exc_synapses = b2.Synapses(neurons,
                                   neurons,
                                   model=excitatory_synapse_model_string,
                                   on_pre='g += weight',
                                   name='exc_synapses')
            
        exc_synapses.connect(p=1.0)
        
        inh_synapses = b2.Synapses(neurons,
                                   neurons,
                                   model=inhibitory_synapse_model_string,
                                   on_pre='g += weight',
                                   name='inh_synapses')
        
        inh_synapses.connect(p=1.0)
            
        b2.device.apply_run_args()
        """
        exc_synapses.weight = np.random.lognormal(mean=b2.asarray(neurons.exc_mean),
                                               sigma=b2.asarray(neurons.exc_sigma),
                                               size=self.N*self.N) * b2.nS

        inh_synapses.weight = np.random.lognormal(mean=b2.asarray(neurons.inh_mean),
                                               sigma=b2.asarray(neurons.inh_sigma),
                                               size=self.N*self.N) * b2.nS
        """
        pdb.set_trace()
        
        neurons.v = np.random.normal(-45 * b2.mV, 10 * b2.mV) * b2. mV
        
        M = b2.StateMonitor(neurons, variables='v', record=True, name='M')
        
        net.add([neurons, exc_synapses, inh_synapses, M])
        
        net.run(2 * b2.second)

        b2.device.build(run=False)
        
        return net
    
    def run(self, parameters):
        run_args = {simulator.nw['neurons'].exc_mean: parameters.exc_mean,
                    simulator.nw['neurons'].exc_sigma: parameters.exc_sigma,
                    simulator.nw['neurons'].exc_scale: parameters.exc_scale,
                    simulator.nw['neurons'].inh_mean: parameters.exc_mean,
                    simulator.nw['neurons'].inh_sigma: parameters.exc_sigma,
                    simulator.nw['neurons'].inh_scale: parameters.exc_scale}
        
        b2.device.run(run_args=run_args)
    

if __name__ == '__main__':
    default_constants =RNNSimulatorConstants(
        gL=10*b2.nS,
        EL=-70*b2.mV,
        VT=-50.4*b2.mV,
        Vr=-75*b2.mV,
        tau_w=144*b2.ms,
        a=4*b2.nS,
        b=0.0805*b2.nA,
        DeltaT=2*b2.mV,
        C=20*b2.pF,
        EEx=0*b2.mV,
        EIn=-70*b2.mV
        )
    
    simulator = RNNSimulator(constants=default_constants, N=500)
    
    parameters = RNNSimulatorParameters(exc_mean=0,
                                        exc_sigma= 0.1,
                                        exc_scale=0.01 * b2.nS,
                                        inh_mean=0,
                                        inh_sigma=0.1,
                                        inh_scale=1 * b2.nS)
    
    simulator.run(parameters)

    plt.plot(simulator.nw['M'].t, simulator.nw['M'].v[5,:])    

    """
    n_neurons = 1
    
    neuron = b2.NeuronGroup(N=n_neurons,  # How many neurons are in the neuron group?
                            model=adex_model_string,  # The string that describes the model
                            reset=adex_reset_string,  # The string that describes what happens at reset
                            threshold='v>0*mV',  # When to reset
                            method='euler')  # ODE solving method
        
    exc_input = b2.PoissonGroup(400, np.random.uniform(1*b2.Hz, 10*b2.Hz, 400)*b2.Hz)
    
    inh_input = b2.PoissonGroup(400, np.random.uniform(1*b2.Hz, 10*b2.Hz, 400)*b2.Hz)
    
    e_syn = b2.Synapses(exc_input, neuron, model=excitatory_synapse_model_string, on_pre='g += ?')
    
    e_syn.connect(p=0.1)
    
    e_syn.tau_inact = 20 * b2.ms
    
    i_syn = b2.Synapses(inh_input, neuron, model=inhibitory_synapse_model_string, on_pre='g += ?')
    
    i_syn.connect(p=0.1)
    
    i_syn.tau_inact = 100 * b2.ms
    
    e_syn.weight = 5 * b2.nS

    i_syn.weight = 1 * b2.nS

    # Now the neuron exists but by default its parameters are set at 0
    # We need to define reasonable parameters
    neuron.v = -70 * b2.mV  # Initial voltage
    neuron.gL = 10 * b2.nS  # 10 nano siemens is 100 MOhm
    neuron.EL = -70 * b2.mV  # Resting potential
    neuron.VT = -50.4 * b2.mV  # Threshold potential
    neuron.Vr = -75 * b2.mV  # Reset potential
    neuron.tau_w = 144 * b2.ms
    neuron.a = 4 * b2.nS
    neuron.b = 0.0805 * b2.nA
    neuron.DeltaT = 2 * b2.mV
    neuron.C = 20 * b2.pF  
    neuron.EEx = 0 * b2.mV
    neuron.EIn = -70 * b2.mV
    
    # Simulation hyperparameters
    _dt = 0.1 * b2.ms
    b2.defaultclock.dt = _dt
    _duration = 2.0 * b2.second
    
    # Measure the membrane voltage
    M = b2.StateMonitor(neuron, variables=True, record=True)
    S = b2.SpikeMonitor(neuron)
    
    b2.run(_duration)
    
    spike_trains = S.spike_trains()
    n_spikes = [len(spike_trains[k]) for k in spike_trains]
    
    plt.figure()
    plt.plot(M.t, M.v[0])
    
    plt.figure()
    plt.scatter(S.t, S.i, marker='|')
    """
    

