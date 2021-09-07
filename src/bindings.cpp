// MIT License
//
// Copyright (c) 2021 Daniel Robertson
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <chrono>
#include <cstdint>
#include <string>
#include <vector>
#include <hx711/common.h>
#include <pybind11/chrono.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace HX711;

namespace py = pybind11;
using namespace py::literals;

PYBIND11_MODULE(HX711, m) {

    m.doc() = "HX711 namespace";

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
     * HX711.GpioException
     */
    //py::class_<GpioException>(m, "GpioException")
    //    .def(py::init<const char*>(), "what_arg"_a);
    py::register_exception<GpioException>(m, "GpioException");

    /**
     * HX711.IntegrityException
     */
    //py::class_<IntegrityException>(m, "IntegrityException")
    //    .def(py::init<const char*>(), "what_arg"_a);
    py::register_exception<IntegrityException>(m, "IntegrityException");

    /**
     * HX711.TimeoutException
     */
    //py::class_<TimeoutException>(m, "TimeoutException")
    //    .def(py::init<const char*>(), "what_arg"_a);
    py::register_exception<TimeoutException>(m, "TimeoutException");


    /**
     * HX711.Mass
     */
    py::class_<Mass> mass_Type(m, "Mass");

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
            "amount"_a = 0.0, "u"_a = Mass::Unit::UG)

        .def(py::init<const Mass&>(), "m2"_a)

        .def("__float__",
            static_cast<double (Mass::*)() const>(&Mass::operator double))

        .def("getValue", &Mass::getValue)

        .def("getUnit", &Mass::getUnit)
        .def("setUnit", &Mass::setUnit, "u"_a)
        
        .def("convertTo", &Mass::convertTo, "to"_a)
        
        .def(py::self + py::self)
        .def(py::self - py::self)
        .def(py::self * py::self)
        .def(py::self / py::self)
        .def(py::self += py::self)
        .def(py::self -= py::self)
        .def(py::self *= py::self)
        .def(py::self /= py::self)
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def(py::self < py::self)
        .def(py::self > py::self)
        .def(py::self <= py::self)
        .def(py::self >= py::self)

        .def("toString",
            static_cast<std::string(Mass::*)() const>(&Mass::toString))

        .def("toString",
            static_cast<std::string(Mass::*)(const Mass::Unit) const>(&Mass::toString),
            "u"_a)

        .def("__str__",
            static_cast<std::string(Mass::*)() const>(&Mass::toString))

        .def("__repr__",
            static_cast<std::string(Mass::*)() const>(&Mass::toString))

        .def_static("convert", &Mass::convert,
            "amount"_a, "from"_a, "to"_a = Mass::Unit::UG)

    ;


    /**
     * HX711.Value
     */

    /**
     * std::int32_t is given instead of Value::_INTERNAL_TYPE
     * which is protected in C++ HX711 library
     */
    typedef std::int32_t INTERNAL_VALUE_TYPE;

    py::class_<Value>(m, "Value")

        .def_property_readonly_static(
            "SATURATION_MIN",
            [](const py::object&) { return Value::SATURATION_MIN; })

        .def_property_readonly_static(
            "SATURATION_MAX",
            [](const py::object&) { return Value::SATURATION_MAX; })

        .def("isSaturated", &Value::isSaturated)
        .def("isValid", &Value::isValid)

        .def("__int__",
            static_cast<INTERNAL_VALUE_TYPE(Value::*)() const>(&Value::operator INTERNAL_VALUE_TYPE))

        .def("__str__",
            [](const Value& v) { return std::to_string(v); })

        .def("__repr__",
            [](const Value& v) { return std::to_string(v); })

        .def(py::init<const INTERNAL_VALUE_TYPE>(), "v"_a)
        .def(py::init<>())

    ;

    //allow for casts to the internal type
    py::implicitly_convertible<INTERNAL_VALUE_TYPE, Value>();


    /**
     * HX711.HX711
     */
    py::class_<HX711::HX711>(m, "HX711")

        .def(py::init<const int, const int, const Rate>(),
            "dataPin"_a, "clockPin"_a, "rate"_a = Rate::HZ_10)

        .def("begin", &HX711::HX711::begin)

        .def("setStrictTiming", &HX711::HX711::setStrictTiming, "strict"_a)
        .def("isStrictTiming", &HX711::HX711::isStrictTiming)

        .def("useDelays", &HX711::HX711::useDelays, "use"_a)
        .def("isUsingDelays", &HX711::HX711::isUsingDelays)

        .def("getFormat", &HX711::HX711::getFormat)
        .def("setFormat", &HX711::HX711::setFormat, "bitFormat"_a)

        .def("getDataPin", &HX711::HX711::getDataPin)
        .def("getClockPin", &HX711::HX711::getClockPin)

        .def("getChannel", &HX711::HX711::getChannel)
        .def("getGain", &HX711::HX711::getGain)
        .def("setConfig", &HX711::HX711::setConfig,
            "c"_a = Channel::A, "g"_a = Gain::GAIN_128)

        .def("isReady", &HX711::HX711::isReady)
        .def("readValue", &HX711::HX711::readValue)

        .def("powerDown", &HX711::HX711::powerDown)
        .def("powerUp", &HX711::HX711::powerUp)

    ;


    /**
     * HX711.Options
     */
    py::class_<HX711::Options>(m, "Options")

        .def_readwrite("stratType", &Options::stratType)
        .def_readwrite("readType", &Options::readType)
        .def_readwrite("samples", &Options::samples)
        .def_readwrite("timeout", &Options::timeout)

        .def(py::init<>())
        .def(py::init<const std::size_t>(), "s"_a)
        .def(py::init<const std::chrono::nanoseconds>(), "t"_a)

    ;


    /**
     * HX711.AbstractScale
     */
    py::class_<AbstractScale>(m, "AbstractScale")

        .def("setUnit", &AbstractScale::setUnit, "unit"_a)
        .def("getUnit", &AbstractScale::getUnit)

        .def("getReferenceUnit", &AbstractScale::getReferenceUnit)
        .def("setReferenceUnit", &AbstractScale::setReferenceUnit, "refUnit"_a)

        .def("getOffset", &AbstractScale::getOffset)
        .def("setOffset", &AbstractScale::setOffset, "offset"_a)

        .def("normalise", &AbstractScale::normalise, "v"_a)
        
        .def("getValues",
            static_cast<std::vector<Value>(AbstractScale::*)(const std::size_t)>(&AbstractScale::getValues),
            "samples"_a)

        .def("getValues",
            static_cast<std::vector<Value>(AbstractScale::*)(const std::chrono::nanoseconds)>(&AbstractScale::getValues),
            "timeout"_a)

        .def("read", &AbstractScale::read, "o"_a = Options())
        .def("zero", &AbstractScale::zero, "o"_a = Options())

        .def("weight",
            static_cast<Mass(AbstractScale::*)(const Options)>(&AbstractScale::weight),
            "o"_a = Options())

        .def("weight",
            static_cast<Mass(AbstractScale::*)(const std::chrono::nanoseconds)>(&AbstractScale::weight),
            "timeout"_a)

        .def("weight",
            static_cast<Mass(AbstractScale::*)(const std::size_t)>(&AbstractScale::weight),
            "samples"_a)

    ;


    /**
     * HX711.SimpleHX711
     */
    py::class_<SimpleHX711, HX711::HX711, AbstractScale>(m, "SimpleHX711")
        .def(py::init<
            const int,
            const int,
            const HX711::Value,
            const HX711::Value,
            const HX711::Rate>(),
            "dataPin"_a,
            "clockPin"_a,
            "refUnit"_a = Value(1),
            "offset"_a = Value(0),
            "rate"_a = Rate::HZ_10)
    ;


    /**
     * HX711.AdvancedHX711
     */
    py::class_<AdvancedHX711, HX711::HX711, AbstractScale>(m, "AdvancedHX711")
        .def(py::init<
            const int,
            const int,
            const HX711::Value,
            const HX711::Value,
            const HX711::Rate>(),
            "dataPin"_a,
            "clockPin"_a,
            "refUnit"_a = Value(1),
            "offset"_a = Value(0),
            "rate"_a = Rate::HZ_10)
    ;

}
