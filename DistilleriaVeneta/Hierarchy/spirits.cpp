#include "spirits.h"

spirits::spirits(bottle_size bs, const std::string& n, double ac) : product(bs, n, ac < max_ac && ac >= min_ac ? ac : min_ac) {}

spirits::spirits(const spirits& s) : product(s) {}

const double spirits::min_ac = 21.0;

const double spirits::max_ac = 90.0;

double spirits::kind_price() const {
  if (get_kind() == small) {
    return -1.00;
  } else if (get_kind() == large) {
    return 0.50;
  }
  return 0.00;
}

double spirits::price_increment() const { return kind_price(); }

double spirits::get_price() const { return get_default_price() + price_increment(); }

std::string spirits::code() const { return "S"; }

std::string spirits::get_image_path() const { return product::get_image_path() + "spirits/"; }
