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

int add(int i, int j) {
    return i + j;
}

namespace py = pybind11;
using namespace Kakoune;



PyObject * InitKakoune(void) {
    py::module m("kakoune", "pybind11 example plugin");

    m.def("add", &add, "A function which adds two numbers");
    m.def("get_kak_binary_path",
          []() { return std::string(Kakoune::get_kak_binary_path().data()); },
          "kak's binary path");
    m.def("parse_filename",
          [](const char* filename) {
              return std::string(Kakoune::parse_filename(filename).data());
          },
          "parse filename");
    m.def("list_files",
          [](const char* filename) {
              std::vector<std::string> files;
              auto _files = Kakoune::list_files(String(filename));
              files.reserve(_files.size());
              std::transform(_files.begin(), _files.end(),
                             std::back_inserter(files),
                             [](String s) { return std::string(s.data()); });
              return files;
          },
          "list files in a path");

    // py::class_<Buffer>(m, "Buffer").def("__init__", [](Buffer& b) {
    //     cli(0, nullptr);
    //     // new (&b) Buffer("test", Buffer::Flags::None,
    //     //                 "allo ?\nmais que fais la police\n hein ?\n youpi\n");
    //     // b.insert(2_line, "tchou\n");
    //     BufferManager& buffer_manager = BufferManager::instance();
    //     new (&b) Buffer(buffer_manager.create_buffer("*scratch*", Buffer::Flags::None));
    // });
    return m.ptr();
}
