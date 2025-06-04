import brian2 as b2
import numpy as np
import matplotlib.pyplot as plt

# Start a clean simulation environment
b2.start_scope()

# ----------------------------
# 1. Define the neuron model
# ----------------------------

# Leaky Integrate-and-Fire model (LIF)
lif_model = '''
dv/dt = (-gL*(v - EL) + I(t, i)) / C : volt
gL : siemens       # Leak conductance
EL : volt          # Resting potential
C : farad          # Membrane capacitance
VT : volt          # Spike threshold
Vr : volt          # Reset potential
'''

# What happens when a neuron spikes
reset_rule = 'v = Vr'

# ----------------------------
# 2. Create the neuron group
# ----------------------------

n_neurons = 10  # Number of neurons

neuron = b2.NeuronGroup(
    N=n_neurons,
    model=lif_model,
    reset=reset_rule,
    threshold='v > VT',
    dt=0.1 * b2.ms,
    method='euler'
)

# ----------------------------
# 3. Set neuron parameters
# ----------------------------

neuron.v = -70 * b2.mV   # Initial membrane potential
neuron.gL = 10 * b2.nS   # Leak conductance
neuron.EL = -70 * b2.mV  # Resting potential
neuron.VT = -40 * b2.mV  # Spike threshold
neuron.Vr = -75 * b2.mV  # Reset value after spike
neuron.C = 30 * b2.pF    # Membrane capacitance

# ----------------------------
# 4. Set simulation parameters
# ----------------------------

dt = 0.1 * b2.ms
duration = 2.0 * b2.second

b2.defaultclock.dt = dt  # Set global time step

# ----------------------------
# 5. Create input stimulus
# ----------------------------

# Stimulus parameters
stim_start = 0.5 * b2.second
stim_stop = 1.5 * b2.second

# Varying stimulus amplitude for each neuron
stim_amp = np.linspace(300, 390, n_neurons) * b2.pA

# Create an array of zeros and set values during the stimulus time
stim_array = np.zeros((int(duration / dt), n_neurons))
stim_array[int(stim_start / dt):int(stim_stop / dt), :] = 1
stim_array *= stim_amp  # Scale by amplitude

# Use TimedArray to turn the stimulus into a Brian2 input
I = b2.TimedArray(stim_array, dt=dt)

# ----------------------------
# 6. Set up recording
# ----------------------------

# Record all state variables for all neurons
state_monitor = b2.StateMonitor(neuron, variables=True, record=True)

# Record spike times
spike_monitor = b2.SpikeMonitor(neuron)

# ----------------------------
# 7. Run the simulation
# ----------------------------

b2.run(duration)

# ----------------------------
# 8. Analyze and visualize results
# ----------------------------

# Plot voltage trace of neuron 0
plt.figure()
plt.plot(state_monitor.t / b2.ms, state_monitor.v[0] / b2.mV)
plt.xlabel("Time (ms)")
plt.ylabel("Membrane potential (mV)")
plt.title("Neuron 0 Voltage Trace")

# Plot voltage trace of neuron 1
plt.figure()
plt.plot(state_monitor.t / b2.ms, state_monitor.v[1] / b2.mV)
plt.xlabel("Time (ms)")
plt.ylabel("Membrane potential (mV)")
plt.title("Neuron 1 Voltage Trace")

# Raster plot of all spikes
plt.figure()
plt.scatter(spike_monitor.t / b2.ms, spike_monitor.i, marker='|')
plt.xlabel("Time (ms)")
plt.ylabel("Neuron index")
plt.title("Spike Raster Plot")

# Firing rate vs input current
spike_trains = spike_monitor.spike_trains()
n_spikes = np.array([len(spike_trains[i]) for i in range(n_neurons)])
firing_rates = n_spikes / ((stim_stop - stim_start) / b2.second)

plt.figure()
plt.plot(stim_amp / b2.pA, firing_rates, marker='o')
plt.xlabel("Input current (pA)")
plt.ylabel("Firing rate (Hz)")
plt.title("Firing Rate vs Input Current")



