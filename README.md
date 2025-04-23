# Brian2 Tutorial at OCNC2025
## Setup

Clone the repository with 

```
git clone https://github.com/danielmk/OCNC2025_brian2
```

Go into the repository directory with

```
cd OCNC2025_brian2
```

Create a virtual environment with 
```
conda env create --file environment.yml
```

Activate the environment with
```
conda activate ocncbrian2
```

Open spyder with 
```
spyder
```

You are ready to start working on the scripts.

## Content

We will learn brian2 in four steps. First, we will simulate the leaky-integrate-and fire (LIF) neuron model to learn the basics of defining equations, recording variables and setting parameters. Second, we extend the model by implementing the adaptive exponential (AdEX) LIF neuron model. Third, we will add synaptic Poisson input to the AdEx model. Finally, we will run a just-in-time compiled simulator with multiple AdEX popoulations, recurrent connetions.


