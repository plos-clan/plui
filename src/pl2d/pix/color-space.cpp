#include <cpp.hpp>
#include <define.h>
#include <pl2d.hpp>
#include <type.hpp>

#include "gamma.hpp"

namespace pl2d {

// void PixelB::RGB2LAB() {
//   float r = G::rgb2xyz(this->r);
//   float g = G::rgb2xyz(this->g);
//   float b = G::rgb2xyz(this->b);

//   float x = r * 0.4124564f + g * 0.3575761f + b * 0.1804375f;
//   float y = r * 0.2126729f + g * 0.7151522f + b * 0.0721750f;
//   float z = r * 0.0193339f + g * 0.1191920f + b * 0.9503041f;

//   x /= 0.950456f;
//   y /= 1.0f;
//   z /= 1.088754f;

//   x = G::xyz2lab(x);
//   y = G::xyz2lab(y);
//   z = G::xyz2lab(z);

//   this->r = y * 255;       // l
//   this->g = (x - y) * 127; // a
//   this->b = (y - z) * 127; // b
// }

// void PixelB::LAB2RGB() {
//   float y = this->r;     // l
//   float x = y + this->g; // a
//   float z = y - this->b; // b

//   x = G::lab2xyz(x);
//   y = G::lab2xyz(y);
//   z = G::lab2xyz(z);

//   x *= 0.950456f;
//   y *= 1.0f;
//   z *= 1.088754f;

//   float r = x * 3.2404542f + y * -1.5371385f + z * -0.4985314f;
//   float g = x * -0.9692660f + y * 1.8760108f + z * 0.0415560f;
//   float b = x * 0.0556434f + y * -0.2040259f + z * 1.0572252f;

//   this->r = G::xyz2rgb(r);
//   this->g = G::xyz2rgb(g);
//   this->b = G::xyz2rgb(b);
// }

template <BasePixelTemplate>
void BasePixelT::RGB2HSV() {
  FT r = this->r / (FT)v_max;
  FT g = this->g / (FT)v_max;
  FT b = this->b / (FT)v_max;

  FT max   = cpp::max(r, g, b);
  FT min   = cpp::min(r, g, b);
  FT delta = max - min;

  FT h = 0, s = 0, v = max;
  if (delta > (FT)1e-5) {
    s = delta / max;
    h = ((r == max) ? (g - b) : (g == max) ? (2 + b - r) : (4 + r - g)) / (delta * 6);
    if (h < 0) h += 1;
  }

  this->r = h * (FT)v_max;
  this->g = s * (FT)v_max;
  this->b = v * (FT)v_max;
}

template <BasePixelTemplate>
void BasePixelT::HSV2RGB() {
  FT h = this->r / (FT)v_max * (FT)6;
  FT s = this->g / (FT)v_max;
  FT v = this->b / (FT)v_max;

  FT c = v * s;
  FT x = c * (1 - cpp::abs(cpp::mod(h, 2) - 1));
  FT m = v - c;

  FT r, g, b;
  if (h < 1) {
    r = c, g = x, b = 0;
  } else if (h < 2) {
    r = x, g = c, b = 0;
  } else if (h < 3) {
    r = 0, g = c, b = x;
  } else if (h < 4) {
    r = 0, g = x, b = c;
  } else if (h < 5) {
    r = x, g = 0, b = c;
  } else {
    r = c, g = 0, b = x;
  }

  this->r = (r + m) * (FT)v_max;
  this->g = (g + m) * (FT)v_max;
  this->b = (b + m) * (FT)v_max;
}

template <BasePixelTemplate>
void BasePixelT::RGB2HSL() {
  FT r = this->r / (FT)v_max;
  FT g = this->g / (FT)v_max;
  FT b = this->b / (FT)v_max;

  FT max   = cpp::max(r, g, b);
  FT min   = cpp::min(r, g, b);
  FT delta = max - min;

  FT h = 0, s = 0, l = max + min;
  if (delta > (FT)1e-5) {
    s = delta / (l > 1 ? 2 - l : l);
    h = ((r == max) ? (g - b) : (g == max) ? (2 + b - r) : (4 + r - g)) / (delta * 6);
    if (h < 0) h += 1;
  }
  l /= 2;

  this->r = h * (FT)v_max;
  this->g = s * (FT)v_max;
  this->b = l * (FT)v_max;
}

template <BasePixelTemplate>
void BasePixelT::HSL2RGB() {
  FT h = this->r * 6;
  FT s = this->g;
  FT l = this->b;

  FT c = (1 - cpp::abs(2 * l - 1)) * s;
  FT x = c * (1 - cpp::abs(cpp::mod(h, 2) - 1));
  FT m = l - c / 2;

  FT r, g, b;
  if (h < 1) {
    r = c, g = x, b = 0;
  } else if (h < 2) {
    r = x, g = c, b = 0;
  } else if (h < 3) {
    r = 0, g = c, b = x;
  } else if (h < 4) {
    r = 0, g = x, b = c;
  } else if (h < 5) {
    r = x, g = 0, b = c;
  } else {
    r = c, g = 0, b = x;
  }

  this->r = (r + m) * (FT)v_max;
  this->g = (g + m) * (FT)v_max;
  this->b = (b + m) * (FT)v_max;
}

template <BasePixelTemplate>
void BasePixelT::RGB2LAB() {
  FT r = G::rgb2xyz(this->r / (FT)v_max);
  FT g = G::rgb2xyz(this->g / (FT)v_max);
  FT b = G::rgb2xyz(this->b / (FT)v_max);

  FT x = r * 0.4124564f + g * 0.3575761f + b * 0.1804375f;
  FT y = r * 0.2126729f + g * 0.7151522f + b * 0.0721750f;
  FT z = r * 0.0193339f + g * 0.1191920f + b * 0.9503041f;

  x /= 0.950456f;
  y /= 1.0f;
  z /= 1.088754f;

  x = G::xyz2lab(x);
  y = G::xyz2lab(y);
  z = G::xyz2lab(z);

  this->r = y * (FT)v_max;                                                // l
  this->g = (x - y) * (FT)v_max_2 + (v_max != v_max_2 ? v_max_2 + 1 : 0); // a
  this->b = (y - z) * (FT)v_max_2 + (v_max != v_max_2 ? v_max_2 + 1 : 0); // b
}

template <BasePixelTemplate>
void BasePixelT::LAB2RGB() {
  FT y = this->r / (FT)v_max;                                                    // l
  FT x = y + ((FT)this->g - (v_max != v_max_2 ? v_max_2 + 1 : 0)) / (FT)v_max_2; // a
  FT z = y - ((FT)this->b - (v_max != v_max_2 ? v_max_2 + 1 : 0)) / (FT)v_max_2; // b

  x = G::lab2xyz(x);
  y = G::lab2xyz(y);
  z = G::lab2xyz(z);

  x *= 0.950456f;
  y *= 1.0f;
  z *= 1.088754f;

  float r = x * 3.2404542f + y * -1.5371385f + z * -0.4985314f;
  float g = x * -0.9692660f + y * 1.8760108f + z * 0.0415560f;
  float b = x * 0.0556434f + y * -0.2040259f + z * 1.0572252f;

  this->r = G::xyz2rgb(r) * (FT)v_max;
  this->g = G::xyz2rgb(g) * (FT)v_max;
  this->b = G::xyz2rgb(b) * (FT)v_max;
}

//;  未实现
template <BasePixelTemplate>
void BasePixelT::XYZ2LUV() {
  float x = this->r;
  float y = this->g;
  float z = this->b;

  float L = (y > 0.008856f) ? 116.f * cpp::cbrt(y) - 16.f : (903.3f * y + 16.f) / 116.f;

  float u_prime = 4.f * x / (x + 15.f * y + 3.f * z);
  float v_prime = 9.f * y / (x + 15.f * y + 3.f * z);

  this->r = L;       // L component
  this->g = u_prime; // u' component
  this->b = v_prime; // v' component
}

template <BasePixelTemplate>
void BasePixelT::RGB2LUV() {}
template <BasePixelTemplate>
void BasePixelT::LUV2RGB() {}

template class BasePixel<u8, 255, 128, u32, f32>;
template class BasePixel<u16, 65535, 32767, u32, f32>;
template class BasePixel<u32, 4294967295, 2147483647, u64, f32>;
template class BasePixel<f32, 1, 1, f32, f32>;
template class BasePixel<f64, 1, 1, f32, f64>;
} // namespace pl2d
