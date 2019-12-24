#include "Game2048.h"

#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>

using namespace std;
namespace py = pybind11;

PYBIND11_MODULE(Game2048, m) {
    py::add_ostream_redirect(m);
    m.doc() = "2048 Board v1";      // module doc string
    py::class_<Board>(m, "Board")
        .def(py::init<>())
        .def_readwrite("score", &Board::score)  // allow read/write attributes , def_readonly for readonly attributes
        .def_readwrite("step", &Board::step)
        .def("is_win", &Board::is_win)
        .def("game_over", &Board::game_over)
        .def("display", &Board::display, py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>())
        .def("get_board", &Board::get_board)
        .def("get_code", &Board::get_code)
        .def("add_element", &Board::add_element)
        .def("move", &Board::move)
        .def("move_left", &Board::move_left)
        .def("move_right", &Board::move_right)
        .def("move_up", &Board::move_up)
        .def("move_down", &Board::move_down);
}
