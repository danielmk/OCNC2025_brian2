import brian2 as b2
from dataclasses import dataclass
import numpy as np
import matplotlib.pyplot as plt

b2.start_scope()

# This string describes the ordinary differential equationof the leaky integrate-and-fire neuron model
lif_model_string = '''dv/dt = (-gL*(v-EL)+I(t,i))/C : volt
            gL : siemens 
            EL : volt
            C : farad
            VT : volt
            Vr : volt'''

lif_reset_string = '''v=Vr'''

n_neurons = 10

neuron = b2.NeuronGroup(N=n_neurons,  # How many neurons are in the neuron group?
                        model=lif_model_string,  # The string that describes the model
                        reset=lif_reset_string,  # The string that describes what happens at reset
                        threshold='v>VT',  # When to reset
                        method='euler')  # ODE solving method

# Now the neuron exists but by default its parameters are set at 0
# We need to define reasonable parameters
neuron.v = -70 * b2.mV  # Initial voltage
neuron.gL = 10 * b2.nS  # 10 nano siemens is 100 MOhm
neuron.EL = -70 * b2.mV  # Resting potential
neuron.VT = -40 * b2.mV  # Threshold potential
neuron.Vr = -75 * b2.mV  # Reset potential
neuron.C = 30 * b2.pF  

# Simulation hyperparameters
_dt = 0.1 * b2.ms
b2.defaultclock.dt = _dt
_duration = 2.0 * b2.second

# Now we need to define a input stimulus
stim_start = 0.5 * b2.second
stim_stop = 1.5 * b2.second
stim_amp = np.linspace(300, 390, n_neurons) * b2.pA
stim_array = np.zeros((int(_duration / _dt), n_neurons))
stim_array[int(stim_start / _dt):int(stim_stop / _dt), :] = 1

stim_array = stim_array * stim_amp

I = b2.TimedArray(stim_array, dt=_dt)

# Measure the membrane voltage
M = b2.StateMonitor(neuron, variables=True, record=True)
S = b2.SpikeMonitor(neuron)

b2.run(_duration)

spike_trains = S.spike_trains()
n_spikes = [len(spike_trains[k]) for k in spike_trains]

plt.figure()
plt.plot(M.t, M.v[-1])

plt.figure()
plt.scatter(S.t, S.i, marker='|')

plt.figure()
plt.plot(stim_amp, n_spikes / (stim_stop - stim_start), marker='o')
    

