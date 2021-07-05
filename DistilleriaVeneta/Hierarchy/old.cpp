#include "old.h"

old::aux_map_initializer::aux_map_initializer() {
  ptr = new old();
  _map[ptr->type_product()] = ptr;
}
old::aux_map_initializer::~aux_map_initializer() { delete ptr; }
old::aux_map_initializer old::aux_map;

old::old(const color c, const u_vector<taste>& t, bool b, unsigned int m, bottle_size bs, const std::string& n, double ac) : grappa(bs, n, ac < max_ac && ac >= min_ac ? ac : min_ac), col(c), tastes(t), barrique(b), month(m) {}

old::old(const old& o) : grappa(o), col(o.col), tastes(o.tastes), barrique(o.barrique), month(o.month) {}

const double old::month_incr = 0.20;

unsigned int old::get_month_old() const { return month; }

double const old::discount_old = 0.80;

old* old::clone() const { return new old(*this); }

double old::kind_price() const {
  if (get_kind() == small) {
    return -1.50 + (is_barrique() ? -1.50 : 0.00);
  } else if (get_kind() == large) {
    return 1.00 + (is_barrique() ? 1.20 : 0.00);
  }
  return 0.00;
}

double old::price_increment() const { return kind_price() + month_incr * month + (is_barrique() ? 3.00 : 0.00); }

std::string old::type_product() const { return "old"; }

double old::get_price() const { return grappa::get_price() + price_increment(); }

double old::promotion() const { return get_price() * discount_old; }

u_vector<taste> old::get_tastes() const { return tastes; }

color old::get_color() const { return col; }

std::string old::code() const {
  std::string aux = "SGO";
  u_vector<taste>::const_iterator cit = tastes.const_begin();
  u_vector<taste>::const_iterator end = tastes.const_end();
  for (; cit != end; cit++) {
    aux += std::to_string(*cit);
  }
  return aux;
}

std::string old::get_image_path() const {
  std::string name = get_name();
  name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
  return grappa::get_image_path() + "old/" + name;
}

bool old::is_barrique() const { return barrique; }

old* old::create(QMap<QString, QVariant>& m) const {
  color _color = static_cast<color>(m["color"].toString().toInt());
  u_vector<taste> _tastes;

  QList<QVariant> list = m["tastes"].toList();
  for (auto const& element : list) {
    _tastes.push_back(static_cast<taste>(element.toString().toInt()));
  }
  bottle_size _bottle = static_cast<bottle_size>(m["bottle_size"].toString().toInt());
  std::string _name = m["name"].toString().toStdString();
  double _alcohol_content = m["alcohol_content"].toString().toDouble();
  bool _barrique = m["barrique"].toBool();
  unsigned int _month = m["month"].toUInt();

  return new old(_color, _tastes, _barrique, _month, _bottle, _name, _alcohol_content);
}

std::string old::write() const {
  std::string aux =
      "\"product\": \"$0\", \
	    \"name\": \"$1\", \
	    \"alcohol_content\": \"$2\", \
	    \"color\": \"$3\", \
	    \"tastes\": [ \
	      $4 \
	    ], \
	    \"bottle_size\": \"$5\", \
            \"barrique\": \"$6\", \
            \"month\": \"$7\"";

  std::string name = std::regex_replace(get_name(), std::regex("\n"), "");

  aux = std::regex_replace(aux, std::regex("\\$0"), type_product());
  aux = std::regex_replace(aux, std::regex("\\$1"), name);
  aux = std::regex_replace(aux, std::regex("\\$2"), std::to_string(get_alcohol_content()));
  aux = std::regex_replace(aux, std::regex("\\$3"), std::to_string(get_color()));
  aux = std::regex_replace(aux, std::regex("\\$4"), std::to_string(get_tastes()[0]));
  aux = std::regex_replace(aux, std::regex("\\$5"), std::to_string(get_kind()));
  aux = std::regex_replace(aux, std::regex("\\$6"), std::to_string(is_barrique()));
  aux = std::regex_replace(aux, std::regex("\\$7"), std::to_string(get_month_old()));

  return aux;
}
