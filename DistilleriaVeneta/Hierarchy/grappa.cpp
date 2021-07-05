#include "grappa.h"

grappa::grappa(bottle_size bs, const std::string& n, double ac) : spirits(bs, n, ac < max_ac && ac >= min_ac ? ac : min_ac) {}

grappa::grappa(const grappa& g) : spirits(g) {}

const double grappa::grappa_incr = 4.50;

const double grappa::min_ac = 38.0;

const double grappa::max_ac = 90.0;

double grappa::kind_price() const {
  if (get_kind() == small) {
    return -0.40;
  } else if (get_kind() == large) {
    return 0.10;
  }
  return 0.00;
}

double grappa::price_increment() const { return kind_price() + grappa_incr; }

double grappa::get_price() const { return spirits::get_price() + price_increment(); }

std::string grappa::code() const { return "SG"; }

std::string grappa::get_image_path() const { return spirits::get_image_path() + "grappa/"; }
