import brian2 as b2
import numpy as np
import matplotlib.pyplot as plt
from dataclasses import dataclass

# Import model definitions (AdEx neuron and synapses)
from ocncbrian2.solution_synapse import (
    adex_model,
    adex_reset,
    exc_synapse_model,
    inh_synapse_model
)

# Set Brian2 to use C++ standalone mode for better performance
b2.set_device('cpp_standalone', build_on_run=False, directory='standalone_directory', debug=True)

# ------------------------------------------------------------------------------
# Define configuration classes to organize parameters
# ------------------------------------------------------------------------------

@dataclass
class RNNSimulatorIntrinsicConstants:
    """Intrinsic neuron parameters."""
    gL: b2.units.fundamentalunits.Unit
    EL: b2.units.fundamentalunits.Unit
    VT: b2.units.fundamentalunits.Unit
    Vr: b2.units.fundamentalunits.Unit
    tau_w: b2.units.fundamentalunits.Unit
    a: b2.units.fundamentalunits.Unit
    b: b2.units.fundamentalunits.Unit
    DeltaT: b2.units.fundamentalunits.Unit
    C: b2.units.fundamentalunits.Unit
    EEx: b2.units.fundamentalunits.Unit
    EIn: b2.units.fundamentalunits.Unit

@dataclass
class RNNSimulatorSynapticConstants:
    """Synaptic inactivation time constants."""
    exc_tau_inact: b2.units.fundamentalunits.Unit
    inh_tau_inact: b2.units.fundamentalunits.Unit

@dataclass
class RNNSimulatorParameters:
    """Synaptic weights for the RNN."""
    exc_recurrent_weight: b2.units.fundamentalunits.Unit
    exc_feedback_weight: b2.units.fundamentalunits.Unit
    inh_weight: b2.units.fundamentalunits.Unit

# ------------------------------------------------------------------------------
# Main Simulator Class
# ------------------------------------------------------------------------------

class RNNSimulator:

    def __init__(self,
                 intrinsic_constants: RNNSimulatorIntrinsicConstants,
                 synaptic_constants: RNNSimulatorSynapticConstants,
                 N_exc: int = 500,
                 N_inh: int = 100):
        self.N_exc = N_exc
        self.N_inh = N_inh
        self.intrinsic_constants = intrinsic_constants
        self.synaptic_constants = synaptic_constants
        self.make_network()

    def make_network(self):
        # Create excitatory and inhibitory neuron groups
        exc_neurons = b2.NeuronGroup(
            self.N_exc, model=adex_model, threshold='v > 0.0*mV',
            reset=adex_reset, method='euler', name='exc_neurons', dt=0.1 * b2.ms
        )

        inh_neurons = b2.NeuronGroup(
            self.N_inh, model=adex_model, threshold='v > 0.0*mV',
            reset=adex_reset, method='euler', name='inh_neurons', dt=0.1 * b2.ms
        )

        # Set initial conditions and random inputs
        exc_neurons.v = '-70 * mV'
        exc_neurons.I = 'rand() * 20 * pA + 196 * pA'
        inh_neurons.v = 'rand() * -70 * mV'
        inh_neurons.I = 'rand() * 50 * pA'

        # Assign intrinsic parameters to all neurons
        for param, value in self.intrinsic_constants.__dict__.items():
            setattr(exc_neurons, param, value)
            setattr(inh_neurons, param, value)

        # Optional override for inhibitory capacitance
        inh_neurons.C = 1 * b2.pF

        # Create synapses
        exc_recurrent_synapses = b2.Synapses(
            exc_neurons, exc_neurons,
            model=exc_synapse_model,
            on_pre='g += weight', method='euler',
            name='exc_recurrent_synapses', dt=0.1 * b2.ms, delay=2 * b2.ms
        )
        exc_recurrent_synapses.connect(condition='i != j', p=0.02)
        exc_recurrent_synapses.tau_inact = self.synaptic_constants.exc_tau_inact

        exc_feedback_synapses = b2.Synapses(
            exc_neurons, inh_neurons,
            model=exc_synapse_model,
            on_pre='g += weight', method='euler',
            name='exc_feedback_synapses', dt=0.1 * b2.ms
        )
        exc_feedback_synapses.connect(p=0.5)
        exc_feedback_synapses.tau_inact = self.synaptic_constants.exc_tau_inact

        inh_synapses = b2.Synapses(
            inh_neurons, exc_neurons,
            model=inh_synapse_model,
            on_pre='g += weight', method='euler',
            name='inh_synapses', dt=0.1 * b2.ms
        )
        inh_synapses.connect(p=0.5)
        inh_synapses.tau_inact = self.synaptic_constants.inh_tau_inact

        # Set up monitors
        M_exc = b2.StateMonitor(exc_neurons, variables=True, record=range(self.N_exc), name='M_exc')
        M_inh = b2.StateMonitor(inh_neurons, variables=True, record=range(self.N_inh), name='M_inh')
        M_syn = b2.StateMonitor(exc_recurrent_synapses, variables=True, record=range(500), name='M_syn')
        S = b2.SpikeMonitor(exc_neurons, name='S')

        # Assemble the network
        self.nw = b2.Network([
            exc_neurons, inh_neurons,
            exc_recurrent_synapses, exc_feedback_synapses, inh_synapses,
            M_exc, M_inh, S, M_syn
        ])

        # Run simulation and build C++ code
        self.nw.run(2.0 * b2.second)
        b2.device.build(run=False)

    def run_standalone(self, parameters: RNNSimulatorParameters):
        """Set weights and run the simulation in standalone mode."""
        run_args = {
            self.nw['exc_recurrent_synapses'].weight: parameters.exc_recurrent_weight,
            self.nw['exc_feedback_synapses'].weight: parameters.exc_feedback_weight,
            self.nw['inh_synapses'].weight: parameters.inh_weight
        }
        b2.device.run(run_args=run_args)

# ------------------------------------------------------------------------------
# Run Simulation
# ------------------------------------------------------------------------------

if __name__ == '__main__':
    # Default neuron properties
    default_intrinsic_constants = RNNSimulatorIntrinsicConstants(
        gL=10 * b2.nS, EL=-70 * b2.mV, VT=-50.4 * b2.mV, Vr=-75 * b2.mV,
        tau_w=40 * b2.ms, a=2 * b2.nS, b=0.00805 * b2.nA,
        DeltaT=2 * b2.mV, C=20 * b2.pF, EEx=0 * b2.mV, EIn=-70 * b2.mV
    )

    # Synapse time constants
    default_synaptic_constants = RNNSimulatorSynapticConstants(
        exc_tau_inact=20 * b2.ms,
        inh_tau_inact=100 * b2.ms
    )

    # Create simulator
    simulator = RNNSimulator(
        intrinsic_constants=default_intrinsic_constants,
        synaptic_constants=default_synaptic_constants,
        N_exc=500, N_inh=100
    )

    # Define synaptic weights
    parameters = RNNSimulatorParameters(
        exc_recurrent_weight=100.0 * b2.psiemens,
        exc_feedback_weight=8.0 * b2.psiemens,
        inh_weight=8.5 * b2.psiemens
    )

    simulator.run_standalone(parameters)

    # ------------------------------------------------------------------------------
    # Plotting
    # ------------------------------------------------------------------------------

    # Plot membrane potentials of excitatory neurons
    plt.figure()
    plt.title("Excitatory neuron voltage")
    plt.plot(simulator.nw['M_exc'].v[2].T)

    # Plot membrane potentials of inhibitory neurons
    plt.figure()
    plt.title("Inhibitory neuron voltage")
    plt.plot(simulator.nw['M_inh'].v[:3].T)

    # Plot inhibitory synaptic conductances
    plt.figure()
    plt.title("Inhibitory synaptic conductance on excitatory neurons")
    plt.plot(simulator.nw['M_exc'].gi[:3].T)

    plt.show()
