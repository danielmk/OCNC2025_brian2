import brian2 as b2
import numpy as np
import matplotlib.pyplot as plt

# from ocncbrian2.synapse_solution import adex_model_string, adex_reset_string
# from ocncbrian2.synapse_solution import excitatory_synapse_model_string, inhibitory_synapse_model_string

from dataclasses import dataclass

# b2.set_device('cpp_standalone', build_on_run=False, directory='standalone_directory', debug=True)

@dataclass
class RNNSimulatorIntrinsicConstants():
    gL: b2.units.fundamentalunits.Unit  # 10 nano siemens is 100 MOhm
    EL: b2.units.fundamentalunits.Unit  # Resting potential
    Vr: b2.units.fundamentalunits.Unit  # Reset potential
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
    
    def make_network(self):    
        adex_model_string = '''dv/dt = (-gL*(v-EL)+I_total)/C : volt
                        I_total =  I_AMPA + I_GABA : amp
                        I_AMPA = - ge * (v - EEx) : amp
                        I_GABA = - gi * (v - EIn) : amp
                        C : farad
                        gL : siemens
                        EL : volt
                        Vr : volt
                        EEx : volt
                        EIn : volt
                        ge : siemens
                        gi : siemens
                        '''

        adex_reset_string ='''v = Vr
                            '''

        synapse_model_string = '''dg/dt = -g/tau_inact : siemens (clock-driven)
                                  tau_inact : second (constant)
                                  weight : siemens (constant)
                               '''

        excitatory_synapse_model_string = synapse_model_string + '''ge_post=g : siemens (summed)'''

        inhibitory_synapse_model_string = synapse_model_string + '''gi_post=g : siemens (summed)'''

        neurons = b2.NeuronGroup(self.N,
                                 model=adex_model_string,
                                 threshold='v>-40.0*mV',
                                 reset=adex_reset_string,
                                 method='euler',
                                 name='neurons',
                                 dt=0.1*b2.ms)

        neurons.v = 'rand() * -70 * mV'
        
        # Set all constant parameters in a single loop
        for param, value in self.intrinsic_constants.__dict__.items():
            setattr(neurons, param, value)
        
        neurons.run_regularly('''v += rand() * 40 * mV''',dt=100*b2.ms)    
        
        exc_input = b2.PoissonGroup(400, np.random.uniform(1*b2.Hz, 10*b2.Hz, 400)*b2.Hz)
        
        exc_synapses = b2.Synapses(neurons,
                                   neurons,
                                   model=excitatory_synapse_model_string,
                                   on_pre='g += weight',
                                   name='exc_synapses',
                                   method='euler',
                                   dt=0.1*b2.ms)
            
        exc_synapses.connect(condition='i != j', p=0.5)
        
        exc_synapses.tau_inact = self.synaptic_constants.exc_tau_inact

        # b2.device.apply_run_args()

        M = b2.StateMonitor(neurons, variables=True, record=range(500), name='M')
        
        M_syn = b2.StateMonitor(exc_synapses, variables=True, record=range(500), name='M_syn')
        
        S = b2.SpikeMonitor(neurons, name='S')
    
        net = b2.Network([neurons, exc_synapses, M, S, M_syn, exc_input])
        
        self.nw = net
        
        # self.nw.run(0.5 * b2.second)
        
        # return net, curr_device
    
    def run_network(self, parameters):
        
        self.nw['exc_synapses'].weight = parameters.exc_weight
        
        self.nw.run(0.5 * b2.second)
    

if __name__ == '__main__':
    default_intrinsic_constants = RNNSimulatorIntrinsicConstants(
        gL=10*b2.nS,
        EL=-70*b2.mV,
        Vr=-75*b2.mV,
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
    
    parameters = RNNSimulatorParameters(exc_weight=1.0*b2.psiemens,
                                        inh_weight=0.0*b2.nS)

    simulator.run_network(parameters)

    plt.figure()    
    plt.plot(simulator.nw['M'].v[:,:].T)
    
    plt.figure()
    plt.plot(simulator.nw['M'].ge[:,:].T)

