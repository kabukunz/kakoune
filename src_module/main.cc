#include <pybind11/pybind11.h>
#include "ncurses_ui.hh"
#include "ncurses.h"
#include "file.hh"
#include "string.hh"

int add(int i, int j) {
    return i + j;
}

namespace py = pybind11;

PYBIND11_PLUGIN(kakoune) {
    py::module m("kakoune", "pybind11 example plugin");

    m.def("add", &add, "A function which adds two numbers");
    m.def("get_kak_binary_path",
          []() { return std::string(Kakoune::get_kak_binary_path().data()); },
          "kak's binary path");

    return m.ptr();
}
