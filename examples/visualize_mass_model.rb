#! /usr/bin/env ruby

require 'comptonsoft/basic'
require 'normGeometry4'
include NormGeometry4


def run_simulation(num, random)
  energy = 1000.0 # keV
  posx = 0.0 #cm
  posy = 0.0 #cm
  posz = 100 #cm

  dirx = 0.0
  diry = 0.0
  dirz = -1.0
  thetamax = 0.05
  output = "vis_ene#{energy}_posx#{posx}cm_posy#{posy}cm_poz#{posz}cm_seed#{random}.root"

  sim = ComptonSoft::Simulation.new
  sim.output = output
  sim.random_seed = random
  sim.verbose = 2

#  sim.detector_config = "database/analysisparam_Norm.xml"
#  sim.simulation_param = "database/simparam_Norm2.xml"
#  sim.analysis_param = "database/analysisparam_Norm.xml"


  
  sim.set_physics(hadron_hp: false, cut_value: 0.001)
  sim.set_geometry :NormMainGeometry

  
  sim.set_primary_generator :PointSourcePrimaryGen, {
    particle: "geantino",
    photon_index: 0.0,
    energy_min: energy,
    energy_max: energy,
    position: vec(posx, posy, posz),
    direction: vec(dirx, diry, dirz),
    theta_min: 0.0,
    theta_max: thetamax,
  }
  
  sim.visualize(mode: 'OGLSQt')
  sim.run(num)
end

### main ###
num = 1000
run_id = 0
random = run_id
run_simulation(num, random)
