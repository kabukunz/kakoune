#include <pybind11/pybind11.h>
#include "ncurses_ui.hh"
#include "ncurses.h"

int add(int i, int j) {
    return i + j;
}

namespace py = pybind11;

PYBIND11_PLUGIN(kakoune) {
    py::module m("kakoune", "pybind11 example plugin");

    m.def("add", &add, "A function which adds two numbers");

    return m.ptr();
}
