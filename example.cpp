#include <pybind11/pybind11.h>
#include <hx711/common.h>

namespace py = pybind11;
using namespace HX711;

PYBIND11_MODULE(hx711, m) {
    
    py::class_<Mass>(m, "Mass")
        .def(py::init<const double>())
        .def("toString", &Mass::toString);

}