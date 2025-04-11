import brian2 as b2
import numpy as np
import matplotlib.pyplot as plt

adex_model_string = '''dv/dt = (-gL*(v-EL)+gL*DeltaT*exp((v-VT)/DeltaT)-w+I(t, i))/C : volt
                dw/dt = (a*(v-EL)-w)/tau_w : amp
                tau_w : second
                b : amp
                DeltaT : volt
                a : siemens
                C : farad
                gL : siemens
                EL : volt
                VT : volt
                Vr : volt
                '''

adex_reset_string ='''v=Vr
                    w=w+b
                    '''

if __name__ == '__main__':
    n_neurons = 10
    
    neuron = b2.NeuronGroup(N=n_neurons,  # How many neurons are in the neuron group?
                            model=adex_model_string,  # The string that describes the model
                            reset=adex_reset_string,  # The string that describes what happens at reset
                            threshold='v>0*mV',  # When to reset
                            method='euler')  # ODE solving method

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
    
    # Simulation hyperparameters
    _dt = 0.1 * b2.ms
    b2.defaultclock.dt = _dt
    _duration = 2.0 * b2.second

    # Now we need to define a input stimulus
    stim_start = 0.5 * b2.second
    stim_stop = 1.5 * b2.second
    stim_amp = np.linspace(200, 290, n_neurons) * b2.pA
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
    plt.plot(M.t, M.v[0])
    
    plt.figure()
    plt.scatter(S.t, S.i, marker='|')
    
    plt.figure()
    plt.plot(stim_amp, n_spikes / (stim_stop - stim_start), marker='o')
    

