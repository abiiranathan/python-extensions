#include <pybind11/pybind11.h>
#include <string.h>

#include <iostream>

namespace py = pybind11;

class Pet {
   public:
    Pet(const std::string &name) : name(name) {}

    void setName(const std::string &name_) { name = name_; }
    const std::string &getName() const { return name; }

   private:
    std::string name;
};

PYBIND11_MODULE(pet, m) {
    py::class_<Pet>(m, "Pet")
        .def(py::init<const std::string &>())
        .def("setName", &Pet::setName)
        .def("getName", &Pet::getName)
        .def("__repr__",
             [](const Pet &a) {
                 return "<example.Pet named '" + a.getName() + "'>";
             });
}

/*
.def
.def_readonly
.def_readwrite("name", &Pet::name);
.def_property("name", &Pet::getName, &Pet::setName)
.def_property_readonly() for readonly property.

py::class_<Pet>(m, "Pet", py::dynamic_attr())
to allow dynamic attributes(make the classes slow.)
*/