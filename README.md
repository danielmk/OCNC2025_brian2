# Brian2 Tutorial at OCNC2025
## Setup

Clone the repository with ```git clone https://github.com/danielmk/OCNC2025_brian2```

Go into the repository directory with ```cd OCNC2025_brian2```

Create a virtual environment with ```conda env create --file environment.yml```

Activate the environment with ```conda activate ocncbrian2```

You are good to go

## Content

We will learn brian2 through two main projects. First, we will compare the input-output curve of the leaky-integrate-and fire (LIF) neuron model and the adaptive exponential (AdEX) LIF neuron model. Second, we will create a recurrent neuronal network of AdEX neurons and try to find the intrinsic and synaptic parameters that maintain biologically plausible level of activity and spiking statistics.

## brian2 Basics

In brian2 