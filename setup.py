from setuptools import setup

with open('README.md') as f:
    readme = f.read()

with open('LICENSE') as f:
    license = f.read()

setup(
    name='ocncbrian2',
    version='0.1.0',
    description='Code for the Brian2 tutorial as OCNC.',
    long_description=readme,
    author='Daniel Müller-Komorowska',
    author_email='danielmuellermsc@gmail.com',
    url='https://github.com/danielmk/OCNC2025_brian2',
    license=license,
    packages=['ocncbrian2'],
    install_requires=[
          'numpy',
          'pandas',
          'matplotlib',
          'spyder',
          'brian2',],)
