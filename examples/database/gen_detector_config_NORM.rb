#!/usr/bin/env ruby

# author: Hirokazu Odaka
# 2014-09-11
# 2015-10-06 | for ComptonSoft version 5
# 2015-10-14 | z-position of CdTe sides are modified.

require 'csv'
require 'builder'

target = STDOUT
x = Builder::XmlMarkup.new(:target=>target, :indent=>2)
x.instruct!
x.instruct!(:"xml-stylesheet",
  :type => "text/xsl",
  :href =>"/Users/takeda/soft/ComptonSoft/xmlstyle/detector_config_v3.xsl")

def x.define_si_detector!(basename: "Si", detid: 0, posx: 0.0, posy: 0.0, posz: 0.0)
  detector(:id => detid) {
    type "2DPixel"
    name basename+":%04d"%detid
    geometry { widthx 53.9; widthy 53.9; thickness 0.6; offsetx 1.35; offsety 1.35 }
    pixel { numx 16; numy 16; pitchx 3.2; pitchy 3.2 }
    position { x "%.3f"%posx; y "%.3f"%posy; z "%.3f"%posz }
    direction_xaxis { x 1.0; y 0.0; z 0.0 }
    direction_yaxis { x 0.0; y 1.0; z 0.0 }
    energy_priority "cathode"
    readout { 4.times{ section(num_channels: 64, electrode_side: "cathode") } }
  }
end

def x.define_cdte_detector!(basename: "CdTe", detid: 0, posx: 0.0, posy: 0.0, posz: 0.0, subid: "B0")
  if subid == "B0"
    dxx = +1.0; dxy =  0.0; dxz =  0.0
    dyx =  0.0; dyy = +1.0; dyz =  0.0
  elsif subid == "B1";
    dxx =  0.0; dxy = +1.0; dxz =  0.0
    dyx = -1.0; dyy =  0.0; dyz =  0.0
  elsif subid == "B2"
    dxx = -1.0; dxy =  0.0; dxz =  0.0
    dyx =  0.0; dyy = -1.0; dyz =  0.0
  elsif subid == "B3"
    dxx =  0.0; dxy = -1.0; dxz =  0.0
    dyx = +1.0; dyy =  0.0; dyz =  0.0
  elsif subid == "SE"
    dxx =  0.0; dxy =  0.0; dxz = -1.0
    dyx =  0.0; dyy = -1.0; dyz =  0.0
  elsif subid == "SN"
    dxx =  0.0; dxy =  0.0; dxz = -1.0
    dyx = +1.0; dyy =  0.0; dyz =  0.0
  elsif subid == "SW"
    dxx =  0.0; dxy =  0.0; dxz = -1.0
    dyx =  0.0; dyy = +1.0; dyz =  0.0
  elsif subid == "SS"
    dxx =  0.0; dxy =  0.0; dxz = -1.0
    dyx = -1.0; dyy =  0.0; dyz =  0.0
  else
    raise "subid should be B0..B3 or SE, SN, SW, SS."
  end
  detector(id: detid) {
    type "2DPixel"
    name basename+":%04d"%detid
    geometry { widthx 26.75; widthy 26.75; thickness 0.75; offsetx 0.575; offsety 0.575 }
    pixel { numx 8; numy 8; pitchx 3.2; pitchy 3.2 }
    position { x "%.3f"%posx; y "%.3f"%posy; z "%.3f"%posz }
    direction_xaxis { x dxx; y dxy; z dxz }
    direction_yaxis { x dyx; y dyy; z dyz }
    energy_priority "cathode"
    readout { section(num_channels: 64, electrode_side: "cathode") }
  }
end

def build_detectors(x)
  si_layers = 16
  cdte_bottom_layers = 4

#  si_layers.times do |i|
#    detid0 = i*2
#    z0 = -0.3-3.6*i
#    z1 = z0 - 1.1
#    x.define_si_detector!(basename: "SiF", detid: detid0,   posx: 0.0, posy: 0.0, posz: z0)
#    x.define_si_detector!(basename: "SiB", detid: detid0+1, posx: 0.0, posy: 0.0, posz: z1)
#  end

  si_layers.times do |i|
    detid0 = 100+i*10
    z0 = -0.9-3.6*i
    offset = 13.875
    x.define_cdte_detector!(basename: "CdTeBB", detid: detid0, posx: +offset, posy: +offset, posz: z0, subid: "B0")
    x.define_cdte_detector!(basename: "CdTeBB", detid: detid0+1, posx: -offset, posy: +offset, posz: z0, subid: "B1")
    x.define_cdte_detector!(basename: "CdTeBB", detid: detid0+2, posx: -offset, posy: -offset, posz: z0, subid: "B2")
    x.define_cdte_detector!(basename: "CdTeBB", detid: detid0+3, posx: +offset, posy: -offset, posz: z0, subid: "B3")
  end
  
  cdte_bottom_layers.times do |i|
    detid0 = 260+i*10
    z0 = -59.175-4.4*i
    z1 = z0 - 1.65
    offset = 13.875
  #  x.define_cdte_detector!(basename: "CdTeBF", detid: detid0,   posx: +offset, posy: +offset, posz: z0, subid: "B0")
  #  x.define_cdte_detector!(basename: "CdTeBF", detid: detid0+1, posx: -offset, posy: +offset, posz: z0, subid: "B1")
  #  x.define_cdte_detector!(basename: "CdTeBF", detid: detid0+2, posx: -offset, posy: -offset, posz: z0, subid: "B2")
  #  x.define_cdte_detector!(basename: "CdTeBF", detid: detid0+3, posx: +offset, posy: -offset, posz: z0, subid: "B3")
    x.define_cdte_detector!(basename: "CdTeBB", detid: detid0, posx: +offset, posy: +offset, posz: z1, subid: "B0")
    x.define_cdte_detector!(basename: "CdTeBB", detid: detid0+1, posx: -offset, posy: +offset, posz: z1, subid: "B1")
    x.define_cdte_detector!(basename: "CdTeBB", detid: detid0+2, posx: -offset, posy: -offset, posz: z1, subid: "B2")
    x.define_cdte_detector!(basename: "CdTeBB", detid: detid0+3, posx: +offset, posy: -offset, posz: z1, subid: "B3")
  end

  side_localx = [0.675, 0.675, 0.675, 27.725, 27.725, 27.725]
  side_localz = [-8.975, -37.075, -65.175, -8.975, -37.075, -65.175]
  side_layers = [30.975, 34.775]

  4.times do |side|
    2.times do |l|
      6.times do |i|
        posz = side_localz[i]
        if side==0
          subid = "SE"
          detid = 200 + l*10 + i
          posy = -side_localx[i]
          posx = -side_layers[l]
        elsif side==1
          subid = "SN"
          detid = 220 + l*10 + i
          posx = side_localx[i]
          posy = -side_layers[l]
        elsif side==2
          subid = "SW"
          detid = 240 + l*10 + i
          posy = side_localx[i]
          posx = side_layers[l]
        elsif side==3
          subid = "SS"
          detid = 260 + l*10 + i
          posx = -side_localx[i]
          posy = side_layers[l]
        end
        basename = (i<3) ? "CdTeSL" : "CdTeSR"
 #       x.define_cdte_detector!(basename: basename, detid: detid, posx: posx, posy: posy, posz: posz, subid: subid)
      end
    end
  end
end

def build_readout(x)
  readout_order = [
    [[102, 0], [122, 0], [142, 0], [162, 0]],
    [[182, 0], [202, 0], [222, 0], [242, 0]],
    [[101, 0], [121, 0], [141, 0], [161, 0]],
    [[181, 0], [201, 0], [221, 0], [241, 0]],
    [[262, 0], [282, 0], [281, 0], [262, 0]],
    [],
    [],
    [[113, 0], [133, 0], [153, 0], [173, 0]],
    [[193, 0], [213, 0], [233, 0], [253, 0]],
    [[112, 0], [132, 0], [152, 0], [172, 0]],
    [[192, 0], [212, 0], [232, 0], [252, 0]],
    [[273, 0], [293, 0], [292, 0], [272, 0]],
    [],
    [],
    [[100, 0], [120, 0], [140, 0], [160, 0]],
    [[180, 0], [200, 0], [220, 0], [240, 0]],
    [[103, 0], [123, 0], [143, 0], [163, 0]],
    [[183, 0], [203, 0], [223, 0], [243, 0]],
    [[260, 0], [280, 0], [283, 0], [263, 0]],
    [],
    [],  
    [[111, 0], [131, 0], [151, 0], [171, 0]],
    [[191, 0], [211, 0], [231, 0], [251, 0]],
    [[110, 0], [130, 0], [150, 0], [170, 0]],
    [[190, 0], [210, 0], [230, 0], [250, 0]],
    [[271, 0], [291, 0], [290, 0], [270, 0]],
    [],
    [],
  ]
  readout_order.each_with_index do |list, i|
    x.module(id: i) {
      list.each do |l|
        x.section {
          x.detector(id: l[0], section: l[1])
        }
      end
    }
  end
end

def build_groups(x)
  x.group(name: "LowZ") {
#    0.upto(31){|i| x.detector(id: i) }
  }
  x.group(name: "HighZ") {
    10.upto(29){|i| 0.upto(3){|j| x.detector(id: i*10+j) }}
#    20.upto(27){|i| 0.upto(5){|j| x.detector(id: i*10+j) }}
  }
  x.group(name: "Si") {
#    0.upto(31){|i| x.detector(id: i) }
  }
  x.group(name: "CdTe") {
    10.upto(29){|i| 0.upto(3){|j| x.detector(id: i*10+j) }}
#    20.upto(27){|i| 0.upto(5){|j| x.detector(id: i*10+j) }}
  }
  x.group(name: "CdTeB") {
    10.upto(29){|i| 0.upto(3){|j| x.detector(id: i*10+j) }}
  }
  x.group(name: "CdTeS") {
#    20.upto(27){|i| 0.upto(5){|j| x.detector(id: i*10+j) }}
  }
  x.hit_pattern(name: "LowZ-LowZ", short_name: "LL", bit: 0) {
    ["LowZ", "LowZ"].each{|group| x.group(name: group)}
  }
  x.hit_pattern(name: "LowZ-HighZ", short_name: "LH", bit: 1) {
    ["LowZ", "HighZ"].each{|group| x.group(name: group)}
  }
  x.hit_pattern(name: "HighZ-HighZ", short_name: "HH", bit: 2) {
    ["HighZ", "HighZ"].each{|group| x.group(name: group)}
  }
  x.hit_pattern(name: "Si-Si", short_name: "SS", bit: 3) {
    ["Si", "Si"].each{|group| x.group(name: group)}
  }
  x.hit_pattern(name: "Si-CdTe", short_name: "SC", bit: 4) {
    ["Si", "CdTe"].each{|group| x.group(name: group)}
  }
  x.hit_pattern(name: "Si-CdTeB", short_name: "SCb", bit: 5) {
    ["Si", "CdTeB"].each{|group| x.group(name: group)}
  }
  x.hit_pattern(name: "Si-CdTeS", short_name: "SCs", bit: 6) {
    ["Si", "CdTeS"].each{|group| x.group(name: group)}
  }
  x.hit_pattern(name: "CdTe-CdTe", short_name: "CC", bit: 7) {
    ["CdTe", "CdTe"].each{|group| x.group(name: group)}
  }
  x.hit_pattern(name: "CdTeB-CdTeB", short_name: "CbCb", bit: 8) {
    ["CdTe", "CdTe"].each{|group| x.group(name: group)}
  }
  x.hit_pattern(name: "CdTeB-CdTeS", short_name: "CbCs", bit: 9) {
    ["CdTe", "CdTe"].each{|group| x.group(name: group)}
  }
  x.hit_pattern(name: "CdTeS-CdTeS", short_name: "CsCs", bit: 10) {
    ["CdTe", "CdTe"].each{|group| x.group(name: group)}
  }
  x.hit_pattern(name: "Si-Si-CdTe", short_name: "SSC", bit: 11) {
    ["Si", "Si", "CdTe"].each{|group| x.group(name: group)}
  }
  x.hit_pattern(name: "Si-CdTe-CdTe", short_name: "SCC", bit: 12) {
    ["Si", "CdTe", "CdTe"].each{|group| x.group(name: group)}
  }
end

x.configuration {
  x.name "NORM"
  x.length_unit "mm"
  x.detectors { build_detectors(x) }
  x.readout { build_readout(x) }
  x.groups { build_groups(x) }
}
