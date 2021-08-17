#include <pybind11/pybind11.h>
#include <hx711/common.h>
#include <string>

namespace py = pybind11;
using namespace HX711;

PYBIND11_MODULE(HX711, m) {

    m.doc() = "HX711 namespace";

    py::class_<Mass> mass_Type(m, "Mass");

    mass_Type
      .def(py::init<const double, Mass::Unit>());

    mass_Type
      .def("getUnit", &Mass::getUnit);

    py::enum_<Mass::Unit>(mass_Type, "Unit")
      .value("UG", Mass::Unit::UG)
      .value("MG", Mass::Unit::MG)
      .value("G", Mass::Unit::G);

//        .def(
//        "toString",
//        static_cast<std::string (Mass::*)()>(&Mass::toString),
//          "toString method");

}
