import ase.io as io

atoms = io.read("alpha_quartz_18.data", format="lammps-data", style="atomic")
atoms.write("alpha_quartz_18.xyz")
