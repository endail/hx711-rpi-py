#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <hx711/common.h>
#include <string>

namespace py = pybind11;
using namespace HX711;

template<typename... Args>
using overload_cast_ = pybind11::detail::overload_cast_impl<Args...>;

PYBIND11_MODULE(HX711, m) {

    m.doc() = "HX711 namespace";

    /**
     * HX711.Mass
     */

    py::class_<Mass> mass_Type(m, "Mass");

    mass_Type.def_static("convert", &Mass::convert);

    py::enum_<Mass::Unit>(mass_Type, "Unit")
      .value("UG", Mass::Unit::UG)
      .value("MG", Mass::Unit::MG)
      .value("G", Mass::Unit::G)
      .value("KG", Mass::Unit::KG)
      .value("TON", Mass::Unit::TON)
      .value("IMP_TON", Mass::Unit::IMP_TON)
      .value("US_TON", Mass::Unit::US_TON)
      .value("ST", Mass::Unit::ST)
      .value("LB", Mass::Unit::LB)
      .value("OZ", Mass::Unit::OZ);

    mass_Type
        .def(py::init<const double, Mass::Unit>())
        .def(py::init<const Mass&>())
        .def("getValue", &Mass::getValue)
        .def("getUnit", &Mass::getUnit)
        .def("setUnit", &Mass::setUnit)
        .def("convertTo", &Mass::convertTo)
        .def(
            "toString",
            static_cast<std::string (Mass::*)() const>(&Mass::toString),
            "toString")
        .def(
            "toString",
            static_cast<std::string (Mass::*)(const Mass::Unit) const>(&Mass::toString),
            "toString")
        ;

    //python-specific
    mass_Type
        .def("__float__", static_cast<double (Mass::*)() const>(&Mass::operator double))
        .def("__str__", static_cast<std::string (Mass::*)() const>(&Mass::toString))
        .def("__repr__", static_cast<std::string (Mass::*)() const>(&Mass::toString))
        .def("assign", &Mass::operator=)

}
