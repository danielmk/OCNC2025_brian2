import brian2 as b2
import numpy as np
import matplotlib.pyplot as plt

# from ocncbrian2.synapse_solution import adex_model_string, adex_reset_string
# from ocncbrian2.synapse_solution import excitatory_synapse_model_string, inhibitory_synapse_model_string

from dataclasses import dataclass

b2.set_device('cpp_standalone', build_on_run=False, directory='standalone_directory', debug=True)

@dataclass
class RNNSimulatorIntrinsicConstants():
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
class RNNSimulatorSynapticConstants():
    exc_tau_inact: b2.units.fundamentalunits.Unit
    inh_tau_inact: b2.units.fundamentalunits.Unit

    
@dataclass
class RNNSimulatorParameters():
    exc_weight: b2.units.fundamentalunits.Unit
    inh_weight: b2.units.fundamentalunits.Unit


class RNNSimulator():

    def __init__(self,
                 intrinsic_constants: RNNSimulatorIntrinsicConstants,
                 synaptic_constants: RNNSimulatorSynapticConstants,
                 N: int = 500):
        self.N = N
        self.intrinsic_constants = intrinsic_constants
        self.synaptic_constants = synaptic_constants
        self.make_network()
        # self.device = b2.devices.get_device()
        # if self.device == b2.devices.cpp_standalone.device.CPPStandaloneDevice:
        #     self.build_device()
        
    
    def make_network(self):    
        excitatory_synapse_model_string = synapse_model_string + '''ge_post=g : siemens (summed)'''

        inhibitory_synapse_model_string = synapse_model_string + '''gi_post=g : siemens (summed)'''

        neurons = b2.NeuronGroup(self.N,
                                 model=adex_model_string,
                                 threshold='v>0.0*mV',
                                 reset=adex_reset_string,
                                 method='euler',
                                 name='neurons',
                                 dt=0.1*b2.ms)

        neurons.v = 'rand() * -70 * mV'
        
        # Set all constant parameters in a single loop
        for param, value in self.intrinsic_constants.__dict__.items():
            setattr(neurons, param, value)
               
        exc_synapses = b2.Synapses(neurons,
                                   neurons,
                                   model=excitatory_synapse_model_string,
                                   on_pre='g += weight',
                                   name='exc_synapses',
                                   method='euler',
                                   dt=0.1*b2.ms)
            
        exc_synapses.connect(condition='i != j', p=0.2)
        
        exc_synapses.tau_inact = self.synaptic_constants.exc_tau_inact
        
        inh_synapses = b2.Synapses(neurons,
                                   neurons,
                                   model=inhibitory_synapse_model_string,
                                   on_pre='g += weight',
                                   name='inh_synapses',
                                   method='euler',
                                   dt=0.1*b2.ms)
        
        inh_synapses.connect(condition='i != j', p=0.5)
        
        inh_synapses.tau_inact = self.synaptic_constants.inh_tau_inact

        # b2.device.apply_run_args()

        M = b2.StateMonitor(neurons, variables=True, record=range(500), name='M')
        
        M_syn = b2.StateMonitor(exc_synapses, variables=True, record=range(500), name='M_syn')
        
        S = b2.SpikeMonitor(neurons, name='S')
    
        net = b2.Network([neurons, exc_synapses, inh_synapses, M, S, M_syn])
        
        self.nw = net
        
        self.nw.run(0.5 * b2.second)

        b2.device.build(run=False)
        
        # return net, curr_device
        
    def build_device(self):
        
        self.net.run(0.5 * b2.second)

        b2.device.build(run=False)
        
        self.device = b2.devices.get_device()

    def run_standalone(self, parameters: RNNSimulatorParameters):
        run_args = {self.nw['exc_synapses'].weight: parameters.exc_weight,
                    self.nw['inh_synapses'].weight: parameters.inh_weight}
        
        b2.device.run(run_args=run_args)
    
    def run_cython(self, parameters: RNNSimulatorParameters):
        self.nw['exc_synapses'].weight = parameters.exc_weight
        self.nw['inh_synapses'].weight = parameters.inh_weight
          
        self.nw.run(0.5 * b2.second)
        
    

if __name__ == '__main__':
    default_intrinsic_constants = RNNSimulatorIntrinsicConstants(
        gL=10*b2.nS,
        EL=-70*b2.mV,
        VT=-50.4*b2.mV,
        Vr=-75*b2.mV,
        tau_w=80*b2.ms,
        a=2*b2.nS,
        b=0.00805*b2.nA,
        # b=0.0805*b2.nA,
        DeltaT=2*b2.mV,
        C=20*b2.pF,
        EEx=0*b2.mV,
        EIn=-70*b2.mV,
        )
    
    default_synaptic_constants = RNNSimulatorSynapticConstants(
        exc_tau_inact = 20 * b2.ms,
        inh_tau_inact = 100 * b2.ms)
    
    simulator = RNNSimulator(intrinsic_constants=default_intrinsic_constants,
                             synaptic_constants=default_synaptic_constants,
                             N=500)
    
    parameters = RNNSimulatorParameters(exc_weight=70.0*b2.psiemens,
                                        inh_weight=9.18779*b2.psiemens)

    simulator.run_standalone(parameters)

    plt.figure()    
    plt.plot(simulator.nw['M'].v[:,:].T)
    
    plt.figure()
    plt.plot(simulator.nw['M'].ge[:,:].T)

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
    

