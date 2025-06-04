import brian2 as b2
import numpy as np
import matplotlib.pyplot as plt

# ------------------------------------------------------------
# 1. Define the Adaptive Exponential Integrate-and-Fire model
# ------------------------------------------------------------

adex_model = '''
dv/dt = (-gL*(v - EL) + gL*DeltaT*exp((v - VT)/DeltaT) - w + I_total) / C : volt
dw/dt = (a*(v - EL) - w) / tau_w : amp

# Total input current
I_total = I_AMPA + I_GABA + I : amp

# Excitatory and inhibitory synaptic currents
I_AMPA = -ge * (v - EEx) : amp
I_GABA = -gi * (v - EIn) : amp

# Intrinsic and synaptic parameters
tau_w : second       # Adaptation time constant
I : amp              # External injected current
b : amp              # Spike-triggered adaptation
DeltaT : volt        # Slope factor
a : siemens          # Subthreshold adaptation strength
C : farad            # Membrane capacitance
gL : siemens         # Leak conductance
EL : volt            # Resting potential
VT : volt            # Spike threshold
Vr : volt            # Reset voltage after spike
EEx : volt           # Excitatory reversal potential
EIn : volt           # Inhibitory reversal potential
ge : siemens         # Total excitatory conductance
gi : siemens         # Total inhibitory conductance
'''

# Reset behavior
adex_reset = '''
v = Vr
w = w + b
'''

# ------------------------------------------------------------
# 2. Define synapse models for excitation and inhibition
# ------------------------------------------------------------

# Generic synapse model with exponential decay
base_synapse_model = '''
dg/dt = -g / tau_inact : siemens (clock-driven)
tau_inact : second (constant)
weight : siemens (constant)
'''

# Excitatory synapse model (affects ge)
exc_synapse_model = base_synapse_model + 'ge_post = g : siemens (summed)'

# Inhibitory synapse model (affects gi)
inh_synapse_model = base_synapse_model + 'gi_post = g : siemens (summed)'

# ------------------------------------------------------------
# 3. Create network and run simulation
# ------------------------------------------------------------

if __name__ == '__main__':
    n_neurons = 1  # Only one postsynaptic AdEx neuron

    # Create the AdEx neuron
    neuron = b2.NeuronGroup(
        N=n_neurons,
        model=adex_model,
        reset=adex_reset,
        threshold='v > 0*mV',
        method='euler'
    )

    # Create Poisson input groups
    exc_input = b2.PoissonGroup(400, rates=np.random.uniform(1, 10, 400) * b2.Hz)
    inh_input = b2.PoissonGroup(400, rates=np.random.uniform(1, 10, 400) * b2.Hz)

    # Create excitatory synapses
    exc_syn = b2.Synapses(exc_input, neuron, model=exc_synapse_model, on_pre='g += weight')
    exc_syn.connect(p=0.1)
    exc_syn.tau_inact = 20 * b2.ms
    exc_syn.weight = 5 * b2.nS

    # Create inhibitory synapses
    inh_syn = b2.Synapses(inh_input, neuron, model=inh_synapse_model, on_pre='g += weight')
    inh_syn.connect(p=0.1)
    inh_syn.tau_inact = 100 * b2.ms
    inh_syn.weight = 1 * b2.nS

    # Set neuron parameters
    neuron.v = -70 * b2.mV
    neuron.gL = 10 * b2.nS
    neuron.EL = -70 * b2.mV
    neuron.VT = -50.4 * b2.mV
    neuron.Vr = -75 * b2.mV
    neuron.tau_w = 144 * b2.ms
    neuron.a = 4 * b2.nS
    neuron.b = 0.0805 * b2.nA
    neuron.DeltaT = 2 * b2.mV
    neuron.C = 20 * b2.pF
    neuron.EEx = 0 * b2.mV
    neuron.EIn = -70 * b2.mV

    # Simulation settings
    _dt = 0.1 * b2.ms
    duration = 2.0 * b2.second
    b2.defaultclock.dt = _dt

    # Monitors
    state_monitor = b2.StateMonitor(neuron, variables=True, record=True)
    spike_monitor = b2.SpikeMonitor(neuron)

    # Run the simulation
    b2.run(duration)

    # Get spike count
    spike_trains = spike_monitor.spike_trains()
    n_spikes = [len(spike_trains[i]) for i in spike_trains]

    # ------------------------------------------------------------
    # 4. Visualization
    # ------------------------------------------------------------

    # Membrane voltage trace
    plt.figure()
    plt.plot(state_monitor.t / b2.ms, state_monitor.v[0] / b2.mV)
    plt.xlabel("Time (ms)")
    plt.ylabel("Membrane voltage (mV)")
    plt.title("AdEx Neuron Membrane Potential")

    # Raster plot
    plt.figure()
    plt.scatter(spike_monitor.t / b2.ms, spike_monitor.i, marker='|')
    plt.xlabel("Time (ms)")
    plt.ylabel("Neuron index")
    plt.title("Spike Raster Plot")

    plt.show()

    

