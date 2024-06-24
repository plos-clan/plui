#pragma once
#include "matrix.hpp"

namespace pl2d {

#include "point2-t.hpp"
_Point(Point2I, i32);
_Point(Point2F, f32);
_Point(Point2D, f64);
#undef _Point

using Point2 = Point2F;
using Point  = Point2;

} // namespace pl2d
