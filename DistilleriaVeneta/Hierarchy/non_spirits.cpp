#include "non_spirits.h"

non_spirits::non_spirits(bottle_size bs, const std::string& n, double ac) : product(bs, n, ac < max_ac && ac >= min_ac ? ac : min_ac) {}

non_spirits::non_spirits(const non_spirits& ns) : product(ns) {}

const double non_spirits::max_ac = 21.0;

const double non_spirits::min_ac = 18.0;

double non_spirits::kind_price() const {
  if (get_kind() == small) {
    return -1.20;
  } else if (get_kind() == large) {
    return 0.40;
  }
  return 0.00;
}

double non_spirits::price_increment() const { return kind_price(); }

double non_spirits::get_price() const { return get_default_price() + price_increment(); }

std::string non_spirits::code() const { return "A"; }

std::string non_spirits::get_image_path() const { return product::get_image_path() + "non_spirits/"; }
