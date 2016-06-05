#include <boost/python.hpp>
#include "ncurses_ui.hh"
#include "ncurses.h"
#include "file.hh"
#include "string.hh"
#include "buffer.hh"
#include "buffer_manager.hh"
#include "flags.hh"
#include "scope.hh"
#include "option_manager.hh"

int add(int i, int j) {
    return i + j;
}

namespace py = boost::python;
using namespace Kakoune;

std::string get_kak_bin_path() {
    return std::string(Kakoune::get_kak_binary_path().data());
}

BOOST_PYTHON_MODULE(kakoune) {
    // py::module m("kakoune", "pybind11 example plugin");

    py::def("add", add);
    py::def("get_kak_binary_path", get_kak_bin_path);
    // py::def("parse_filename", [](const char* filename) {
    //     return std::string(Kakoune::parse_filename(filename).data());
    // });
    // py::def("list_files", [](const char* filename) {
    //     std::vector<std::string> files;
    //     auto _files = Kakoune::list_files(String(filename));
    //     files.reserve(_files.size());
    //     std::transform(_files.begin(), _files.end(),
    //     std::back_inserter(files),
    //                    [](String s) { return std::string(s.data()); });
    //     return files;
    // });

    // py::class_<SafeCountable>(m, "SafeCountrable").def(py::init<>());

    // py::class_<OptionManagerWatcher>(m, "OptionManagerWatcher")
    //     .def(py::init<>());
    // py::class_<Scope>(m, "Scope").def(py::init<>());

    // py::class_<Buffer>("Buffer", py::bases<OptionManagerWatcher>())
    //     .def("__init__", [](Buffer& b) {
    //         new (&b)
    //             Buffer{"test", Buffer::Flags::None,
    //                    "allo ?\nmais que fais la police\n hein ?\n youpi\n"};
    //     });
}
