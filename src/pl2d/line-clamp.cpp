#include <pl2d.hpp>

namespace pl2d {

template <typename T>
auto BaseLine<T>::clamp(const BaseRect<T> &rect) -> bool {
  return clamp(rect, *this);
}
template <typename T>
auto BaseLine<T>::clamp(const BaseRect<T> &rect, BaseLine &l) const -> bool {
  float x1 = this->x1, y1 = this->y1;
  float x2 = this->x2, y2 = this->y2;
  float xmin = rect.x1, ymin = rect.y1;
  float xmax = rect.x2, ymax = rect.y2;
  if (x1 < xmin && x2 < xmin) return false;
  if (y1 < ymin && y2 < ymin) return false;
  if (x1 > xmax && x2 > xmax) return false;
  if (y1 > ymax && y2 > ymax) return false;
  if (x1 < x2) {
    if (x1 < xmin) {
      float k = (xmin - x1) / (x2 - x1);
      y1      = (1 - k) * y1 + k * y2;
      x1      = xmin;
    }
    if (x2 > xmax) {
      float k = (xmax - x1) / (x2 - x1);
      y2      = (1 - k) * y1 + k * y2;
      x2      = xmax;
    }
  } else {
    if (x1 > xmax) {
      float k = (xmax - x1) / (x2 - x1);
      y1      = (1 - k) * y1 + k * y2;
      x1      = xmax;
    }
    if (x2 < xmin) {
      float k = (xmin - x1) / (x2 - x1);
      y2      = (1 - k) * y1 + k * y2;
      x2      = xmin;
    }
  }
  if (y1 < ymin && y2 < ymin) return false;
  if (y1 > ymax && y2 > ymax) return false;
  if (y1 < y2) {
    if (y1 < ymin) {
      float k = (ymin - y1) / (y2 - y1);
      x1      = (1 - k) * x1 + k * x2;
      y1      = ymin;
    }
    if (y2 > ymax) {
      float k = (ymax - y1) / (y2 - y1);
      x2      = (1 - k) * x1 + k * x2;
      y2      = ymax;
    }
  } else {
    if (y1 > ymax) {
      float k = (ymax - y1) / (y2 - y1);
      x1      = (1 - k) * x1 + k * x2;
      y1      = ymax;
    }
    if (y2 < ymin) {
      float k = (ymin - y1) / (y2 - y1);
      x2      = (1 - k) * x1 + k * x2;
      y2      = ymin;
    }
  }
  l.x1 = x1;
  l.y2 = y1;
  l.x2 = x2;
  l.y2 = y2;
  return true;
}

template class BaseLine<i32>;
template class BaseLine<f32>;
template class BaseLine<f64>;

} // namespace pl2d
