#ifndef current_dist_h
#define current_dist_h

// Include definitions required by distribution files. Fot the sake of
// simplicity the genreated headers do not contain any project specific type
// definitions.
#include "definitions.h"
#include "obj.h"

// Objects and signals
#include "gtl/object/centrality.h"
#include "gtl/object/external.h"

// Cuts
#include "gtl/cut/centrality.h"
#include "gtl/cut/external.h"

// Conditions
#include "gtl/condition/signal.h"
#include "gtl/condition/comb.h"


// Includes menu distribution from symbolic link `current_dist`.
#include "../current_dist/src/impl/menu.hxx"

#endif
