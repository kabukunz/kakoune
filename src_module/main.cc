#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "ncurses_ui.hh"
#include "ncurses.h"
#include "file.hh"
#include "string.hh"
#include "buffer.hh"
#include "flags.hh"
#include "client.hh"
#include "main.hh"
#include "option_manager.hh"
#include "buffer_manager.hh"
#include "kakoune_py.hh"
#include "Python.h"

namespace py = pybind11;

PYBIND11_PLUGIN(kakoune) {
    return InitKakoune();
}
