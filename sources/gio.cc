//
// FILE: gio.cc -- Provide global standard stream instances
//
// $Id$
//

#include "gstream.h"

#ifndef __BORLANDC__ 

gFileInput _gin(stdin);
gInput &gin = _gin;

gStandardOutput _gout(stdout);
gOutput &gout = _gout;

gStandardOutput _gerr(stderr);
gOutput &gerr = _gerr;

#else

gFileInput _gin(stdin);
gInput &gin = _gin;

gWinOutput _gout;
gOutput &gout = _gout;

gWinOutput _gerr;
gOutput &gerr = _gerr;

#endif

