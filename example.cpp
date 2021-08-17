#include <pybind11/pybind11.h>
#include <hx711/common.h>

namespace py = pybind11;
using namespace HX711;

PYBIND11_MODULE(HX711, m) {

    m.doc() = "HX711 namespace";

    py::class_<Mass>(m, "Mass")
        .def(py::init<
            py::arg("amount") = 0.0,
            py::arg("u") = Mass::Unit::UG>())
        .def("toString", static_cast<std::string (Mass::*)(void)>(&Mass::toString), "toString method")


}