import brian2 as b2
import numpy as np
import matplotlib.pyplot as plt

adex_model_string = '''dv/dt = (-gL*(v-EL)+gL*DeltaT*exp((v-VT)/DeltaT)-w+I_total)/C : volt
                dw/dt = (a*(v-EL)-w)/tau_w : amp
                I_total =  I_AMPA + I_GABA : amp
                I_AMPA = - ge * (v - EEx) : amp
                I_GABA = - gi * (v - EIn) : amp
                tau_w : second
                b : amp
                DeltaT : volt
                a : siemens
                C : farad
                gL : siemens
                EL : volt
                VT : volt
                Vr : volt
                EEx : volt
                EIn : volt
                ge : siemens
                gi : siemens
                '''

adex_reset_string ='''v = Vr
                    w = w+b
                    '''

synapse_model_string = '''dg/dt = -g/tau_inact : siemens (clock-driven) # active
                          tau_inact : second
                          weight : siemens
                       '''

excitatory_synapse_model_string = synapse_model_string + '''? (summed)'''

inhibitory_synapse_model_string = synapse_model_string + '''? (summed)'''

if __name__ == '__main__':
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
    
    

