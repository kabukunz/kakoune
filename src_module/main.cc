#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "ncurses_ui.hh"
#include "ncurses.h"
#include "file.hh"
#include "string.hh"
#include "buffer.hh"
#include "flags.hh"

int add(int i, int j) {
    return i + j;
}

namespace py = pybind11;
using namespace Kakoune;

PYBIND11_PLUGIN(kakoune) {
    py::module m("kakoune", "pybind11 example plugin");

    m.def("add", &add, "A function which adds two numbers");
    m.def("get_kak_binary_path",
          []() { return std::string(Kakoune::get_kak_binary_path().data()); },
          "kak's binary path");
    m.def("parse_filename",
          [](const char* filename) {
              return std::string(Kakoune::parse_filename(filename).data());
          },
          "kak's binary path");

    m.def("list_files",
          [](const char* filename) {
              std::vector<std::string> files;
              auto _files = Kakoune::list_files(filename);
              std::transform(_files.begin(), _files.end(), files.begin(),
                             [](String n) { return std::string(n.data()); });
              return files;
          },
          "kak's binary path", py::return_value_policy::copy);

    py::class_<Buffer>(m, "Buffer").def("__init__", [](Buffer& b) {
        new (&b) Buffer("test", Buffer::Flags::None,
                        "allo ?\nmais que fais la police\n hein ?\n youpi\n");
    });
    return m.ptr();
}
