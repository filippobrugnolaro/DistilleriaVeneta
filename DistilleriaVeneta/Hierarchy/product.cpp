#include "product.h"

std::map<std::string, product*> _map = std::map<std::string, product*>();

product::product(bottle_size bs, const std::string& n, double ac) : kind(bs), name(n), alcohol_content(ac) {}

const double product::fixed_price = 5.00;

double product::get_default_price() const { return price_increment() + fixed_price + taxes(); }

product::product(const product& p) : kind(p.kind), name(p.name), alcohol_content(p.alcohol_content < max_ac && p.alcohol_content >= min_ac ? p.alcohol_content : min_ac) {}

const double product::multiplier_taxes = 0.10;

const double product::max_ac = 90.0;

const double product::min_ac = 18.0;

double product::kind_price() const {
  if (kind == small) {
    return -1.00;
  } else if (kind == large) {
    return 1.00;
  }
  return 0.00;
}

double product::price_increment() const { return kind_price(); }

std::string product::get_image_path() const { return ":/product/"; }

std::string product::get_name() const { return name; }

double product::taxes() const {
  double aux = multiplier_taxes * alcohol_content;
  if (kind == small) {
    return aux * 0.50;
  } else if (kind == large) {
    return aux * 1.50;
  }
  return aux;
}

double product::get_alcohol_content() const { return alcohol_content; }

bottle_size product::get_kind() const { return kind; }

void product::set_kind_bottle(bottle_size __bottle_size) { kind = __bottle_size; }

std::string product::fromKindToStdString(bottle_size b) const {
  if (b == small)
    return "Small";
  else if (b == large)
    return "Large";
  return "Medium";
}

double product::operator+(const product& p) const { return get_price() + p.get_price(); }

double product::operator-(const product& p) const { return get_price() >= p.get_price() ? get_price() - p.get_price() : p.get_price() - get_price(); }

bool product::operator<(const product& _p) const { return (alcohol_content < _p.alcohol_content); }

bool product::operator>(const product& _p) const { return (alcohol_content > _p.alcohol_content); }

product* product::unserialize(QMap<QString, QVariant>& m) {
  std::string p = m["product"].toString().toStdString();
  if (_map.count(p) != 0) {
    return _map[p]->create(m);
  }

  return nullptr;
}
