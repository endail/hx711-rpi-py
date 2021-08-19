#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <hx711/common.h>
#include <string>
#include <cstdint>
#include <chrono>

namespace py = pybind11;
using namespace HX711;

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
        .def(py::init<const double, const Mass::Unit>(),
            py::arg("amount") = 0.0,
            py::arg("u") = Mass::Unit::UG)
        .def(py::init<const Mass&>())
        .def("getValue", &Mass::getValue)
        .def("getUnit", &Mass::getUnit)
        .def("setUnit", &Mass::setUnit)
        .def("convertTo", &Mass::convertTo)
        .def("toString",
            static_cast<std::string (Mass::*)() const>(&Mass::toString))
        .def("toString",
            static_cast<std::string (Mass::*)(const Mass::Unit) const>(&Mass::toString))
        .def("__float__", static_cast<double (Mass::*)() const>(&Mass::operator double))
        .def("__str__", static_cast<std::string (Mass::*)() const>(&Mass::toString))
        .def("__repr__", static_cast<std::string (Mass::*)() const>(&Mass::toString))
        .def("assign", &Mass::operator=)
    ;



    /**
     * HX711.Value
     */

    typedef std::int32_t INTERNAL_VALUE_TYPE;

    py::class_<Value> value_Type(m, "Value");

    value_Type
        .def("isSaturated", &Value::isSaturated)
        .def("isValid", &Value::isValid)

        /**
         * std::int32_t is given instead of Value::_INTERNAL_TYPE
         * which is protected
         */
        .def("__int__", static_cast<INTERNAL_VALUE_TYPE (Value::*)() const>(&Value::operator INTERNAL_VALUE_TYPE))
        .def("assign", &Value::operator=)

        .def(py::init<const INTERNAL_VALUE_TYPE>())
        .def(py::init<>())

        .def_property_readonly_static(
            "SATURATION_MIN",
            [](const py::object&) { return Value::SATURATION_MIN; })

        .def_property_readonly_static(
            "SATURATION_MAX",
            [](const py::object&) { return Value::SATURATION_MAX; })
    ;


    /**
     * HX711.Channel
     */

    py::enum_<HX711::Channel>(m, "Channel")
        .value("A", HX711::Channel::A)
        .value("B", HX711::Channel::B);


    /**
     * HX711.Gain
     */

    py::enum_<HX711::Gain>(m, "Gain")
        .value("GAIN_128", HX711::Gain::GAIN_128)
        .value("GAIN_32", HX711::Gain::GAIN_32)
        .value("GAIN_64", HX711::Gain::GAIN_64);


    /**
     * HX711.Rate
     */

    py::enum_<HX711::Rate>(m, "Rate")
        .value("HZ_10", HX711::Rate::HZ_10)
        .value("HZ_80", HX711::Rate::HZ_80)
        .value("OTHER", HX711::Rate::OTHER);


    /**
     * HX711.Format
     */

    py::enum_<HX711::Format>(m, "Format")
        .value("MSB", HX711::Format::MSB)
        .value("LSB", HX711::Format::LSB);



    /**
     * HX711.HX711
     */

    py::class_<HX711::HX711> hx711_Type(m, "HX711");

    hx711_Type
        .def("setStrictTiming", &HX711::HX711::setStrictTiming)
        .def("isStrictTiming", &HX711::HX711::isStrictTiming)
        .def("getFormat", &HX711::HX711::getFormat)
        .def("setFormat", &HX711::HX711::setFormat)
        .def("getDataPin", &HX711::HX711::getDataPin)
        .def("getClockPin", &HX711::HX711::getClockPin)
        .def("getChannel", &HX711::HX711::getChannel)
        .def("getGain", &HX711::HX711::getGain)
        .def("setConfig", &HX711::HX711::setConfig)
        .def("isReady", &HX711::HX711::isReady)
        .def("readValue", &HX711::HX711::readValue)
        .def("powerDown", &HX711::HX711::powerDown)
        .def("powerUp", &HX711::HX711::powerUp)
    ;


    /**
     * HX711.StrategyType
     */

    py::enum_<HX711::StrategyType>(m, "StrategyType")
        .value("Samples", StrategyType::Samples)
        .value("Time", StrategyType::Time);


    /**
     * HX711.ReadType
     */

    py::enum_<HX711::ReadType>(m, "ReadType")
        .value("Median", ReadType::Median)
        .value("Average",ReadType::Average);


    /**
     * HX711.Options
     */

    py::class_<HX711::Options> options_Type(m, "Options");
    
    options_Type
        .def_readwrite("stratType", &Options::stratType)
        .def_readwrite("readType", &Options::readType)
        .def_readwrite("samples", &Options::samples)
        .def_readwrite("timeout", &Options::timeout)
        .def(py::init<>())
        .def(py::init<const std::size_t>())
        .def(py::init<const std::chrono::nanoseconds>())
    ;


    /**
     * HX711.AbstractScale
     */

    py::class_<AbstractScale> abstractScale_Type(m, "AbstractScale");

    abstractScale_Type
        .def("setUnit", &AbstractScale::setUnit)
        .def("getUnit", &AbstractScale::getUnit)
        .def("getReferenceUnit", &AbstractScale::getReferenceUnit)
        .def("setReferenceUnit", &AbstractScale::setReferenceUnit)
        .def("getOffset", &AbstractScale::getOffset)
        .def("setOffset", &AbstractScale::setOffset)
        .def("normalise", &AbstractScale::normalise)

        //getValues virtual functions here

        .def("read", &AbstractScale::read)
        .def("zero", &AbstractScale::zero)

        //overloaded weight functions here

    ;


    /**
     * HX711.SimpleHX711
     */

    py::class_<SimpleHX711, HX711::HX711, AbstractScale> simpleHX711_Type(m, "SimpleHX711");

    simpleHX711_Type
        .def(py::init<
            const int,
            const int,
            const HX711::Value,
            const HX711::Value,
            const HX711::Rate>())

        //virtual getValues functions here

    ;


}
