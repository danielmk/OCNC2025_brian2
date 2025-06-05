import brian2 as b2
import numpy as np
import matplotlib.pyplot as plt

# ----------------------------
# 1. Define the AdEx neuron model
# ----------------------------

# Adaptive Exponential Integrate-and-Fire (AdEx) model equations
# Task: replace the ? with the correct variables/terms that define the AdEX neuron
# Reference: https://journals.physiology.org/doi/epdf/10.1152/jn.00686.2005
adex_model = '''
dv/dt = (-gL*(v - EL) + ? *  ? * exp((? - ?) / ?) - ? + I(t, i)) / C : volt
dw/dt = (a*(v - EL) - w) / tau_w : amp
?     # Adaptation time constant
b : amp            # Spike-triggered adaptation increment
?      # Slope factor
?        # Subthreshold adaptation
C : farad          # Membrane capacitance
gL : siemens       # Leak conductance
EL : volt          # Resting potential
VT : volt          # Spike threshold
Vr : volt          # Reset voltage
'''

# Reset behavior after a spike
adex_reset = '''?'''

if __name__ == '__main__':
    # ----------------------------
    # 2. Create the neuron group
    # ----------------------------

    n_neurons = 10  # Number of neurons

    neuron = b2.NeuronGroup(
        N=n_neurons,
        model=adex_model,
        reset=adex_reset,
        threshold='v > 0*mV',
        method='euler'
    )

    # ----------------------------
    # 3. Set neuron parameters
    # ----------------------------

    neuron.v = -70 * b2.mV         # Initial voltage
    neuron.gL = 10 * b2.nS         # Leak conductance
    neuron.EL = -70 * b2.mV        # Resting potential
    neuron.VT = -50.4 * b2.mV      # Threshold
    neuron.Vr = -75 * b2.mV        # Reset value
    neuron.tau_w = 144 * b2.ms     # Adaptation time constant
    neuron.a = 4 * b2.nS           # Subthreshold adaptation
    neuron.b = 0.0805 * b2.nA      # Spike-triggered adaptation
    neuron.DeltaT = 2 * b2.mV      # Slope factor
    neuron.C = 20 * b2.pF          # Membrane capacitance

    # ----------------------------
    # 4. Simulation setup
    # ----------------------------

    dt = 0.1 * b2.ms
    duration = 2.0 * b2.second
    b2.defaultclock.dt = dt  # Set global time step

    # ----------------------------
    # 5. Create input stimulus
    # ----------------------------

    stim_start = 0.5 * b2.second
    stim_stop = 1.5 * b2.second

    # Each neuron receives a different current amplitude
    stim_amp = np.linspace(200, 290, n_neurons) * b2.pA

    # Create a 2D stimulus array [time x neuron]
    stim_array = np.zeros((int(duration / dt), n_neurons))
    stim_array[int(stim_start / dt):int(stim_stop / dt), :] = 1
    stim_array *= stim_amp

    # Turn into a TimedArray to use in the model
    I = b2.TimedArray(stim_array, dt=dt)

    # ----------------------------
    # 6. Set up recording
    # ----------------------------

    state_monitor = b2.StateMonitor(neuron, variables=True, record=True)
    spike_monitor = b2.SpikeMonitor(neuron)

    # ----------------------------
    # 7. Run simulation
    # ----------------------------

    b2.run(duration)

    # ----------------------------
    # 8. Analyze and visualize results
    # ----------------------------

    spike_trains = spike_monitor.spike_trains()
    n_spikes = np.array([len(spike_trains[i]) for i in range(n_neurons)])
    firing_rates = n_spikes / ((stim_stop - stim_start) / b2.second)

    # Plot voltage trace of neuron 0
    plt.figure()
    plt.plot(state_monitor.t / b2.ms, state_monitor.v[0] / b2.mV)
    plt.xlabel("Time (ms)")
    plt.ylabel("Membrane potential (mV)")
    plt.title("Neuron 0 Voltage Trace (AdEx)")

    # Raster plot of spikes
    plt.figure()
    plt.scatter(spike_monitor.t / b2.ms, spike_monitor.i, marker='|')
    plt.xlabel("Time (ms)")
    plt.ylabel("Neuron index")
    plt.title("Spike Raster Plot (AdEx)")

    # Firing rate vs input current
    plt.figure()
    plt.plot(stim_amp / b2.pA, firing_rates, marker='o')
    plt.xlabel("Input current (pA)")
    plt.ylabel("Firing rate (Hz)")
    plt.title("Firing Rate vs Input Current (AdEx)")

    plt.show()

