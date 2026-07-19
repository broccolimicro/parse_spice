#include "factory.h"

#include "netlist.h"

namespace parse_spice {

const parse::factory factory(parse::schema::from<netlist>());

}

