#include <pybind11/pybind11.h>
namespace py = pybind11;
using namespace pybind11::literals;

// Define C struct
struct Point {
    int x;
    int y;
};

// Function to create a new point
Point *create_point(int x, int y) {
    Point *point = new Point;
    point->x = x;
    point->y = y;
    return point;
}

// retrieves the x-coordinate of the point.
int get_x(const Point *point) {
    return point->x;
}

// retrieves the y-coordinate of the point.
int get_y(const Point *point) {
    return point->y;
}

PYBIND11_MODULE(point, m) {
    py::class_<Point>(m, "Point")
        .def(py::init<int, int>())
        .def_readonly("x", &Point::x)
        .def_readonly("y", &Point::y);

    m.def("create_point", &create_point, "Create a new point", "a"_a, "b"_a);
    m.def("get_x", &get_x, "Get the x-coordinate of point", py::arg("point"));
    m.def("get_y", &get_y, "Get the y-coordinate of point", py::arg("point"));
}
