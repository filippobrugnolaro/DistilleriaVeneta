#include "liquor.h"

liquor::aux_map_initializer::aux_map_initializer() {
  ptr = new liquor(color::white, {});
  _map[ptr->type_product()] = ptr;
}
liquor::aux_map_initializer::~aux_map_initializer() { delete ptr; }
liquor::aux_map_initializer liquor::aux_map;

liquor::liquor(const color c, const u_vector<taste>& t, bottle_size bs, const std::string& n, double ac) : spirits(bs, n, ac < max_ac && ac >= min_ac ? ac : min_ac), col(c), tastes(t) {}

const double liquor::liquor_incr = 4.00;

const double liquor::taste_incr = 0.10;

liquor::liquor(const liquor& l) : spirits(l), col(l.col), tastes(l.tastes) {}

const double liquor::min_ac = 21.0;

const double liquor::max_ac = 38.0;

double const liquor::discount_liquor = 0.90;

liquor* liquor::clone() const { return new liquor(*this); }

double liquor::kind_price() const {
  if (get_kind() == small) {
    return -0.80;
  } else if (get_kind() == large) {
    return 0.30;
  }
  return 0.00;
}

double liquor::price_increment() const { return kind_price() + liquor_incr + tastes.size() * taste_incr; }

std::string liquor::type_product() const { return "liquor"; }

double liquor::get_price() const { return spirits::get_price() + price_increment(); }

double liquor::promotion() const { return get_price() * discount_liquor; }

u_vector<taste> liquor::get_tastes() const { return tastes; }

color liquor::get_color() const { return col; }

std::string liquor::code() const {
  std::string aux = "SL0";
  u_vector<taste>::const_iterator cit = tastes.const_begin();
  u_vector<taste>::const_iterator end = tastes.const_end();
  for (; cit != end; cit++) {
    aux += std::to_string(*cit);
  }
  return aux;
}

std::string liquor::get_image_path() const {
  std::string name = get_name();
  name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
  return spirits::get_image_path() + "liquor/" + name;
}

liquor* liquor::create(QMap<QString, QVariant>& m) const {
  color _color = static_cast<color>(m["color"].toString().toInt());
  u_vector<taste> _tastes;

  QList<QVariant> list = m["tastes"].toList();
  for (auto const& element : list) {
    _tastes.push_back(static_cast<taste>(element.toString().toInt()));
  }
  bottle_size _bottle = static_cast<bottle_size>(m["bottle_size"].toString().toInt());
  std::string _name = m["name"].toString().toStdString();
  double _alcohol_content = m["alcohol_content"].toString().toDouble();

  return new liquor(_color, _tastes, _bottle, _name, _alcohol_content);
}

std::string liquor::write() const {
  std::string aux =
      "\"product\": \"$0\", \
	    \"name\": \"$1\", \
	    \"alcohol_content\": \"$2\", \
	    \"color\": \"$3\", \
	    \"tastes\": [ \
	      $4 \
	    ], \
	    \"bottle_size\": \"$5\"";

  std::string name = std::regex_replace(get_name(), std::regex("\n"), "");

  aux = std::regex_replace(aux, std::regex("\\$0"), type_product());
  aux = std::regex_replace(aux, std::regex("\\$1"), name);
  aux = std::regex_replace(aux, std::regex("\\$2"), std::to_string(get_alcohol_content()));
  aux = std::regex_replace(aux, std::regex("\\$3"), std::to_string(get_color()));
  aux = std::regex_replace(aux, std::regex("\\$4"), std::to_string(get_tastes()[0]));
  aux = std::regex_replace(aux, std::regex("\\$5"), std::to_string(get_kind()));

  return aux;
}
