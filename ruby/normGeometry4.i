%module normGeometry4
%{
#include "NormMainGeometry.hh"

#include "class_list_anlGeant4.hh"

using namespace normgeometry;

%}

%import "anlGeant4.i"

namespace normgeometry {

class NormMainGeometry : public anlgeant4::VANLGeometry {
public:
  NormMainGeometry() {}
  virtual ~NormMainGeometry() {}
};

}
