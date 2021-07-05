#include "cream.h"

cream::aux_map_initializer::aux_map_initializer() {
  ptr = new cream();
  _map[ptr->type_product()] = ptr;
}

cream::aux_map_initializer::~aux_map_initializer() { delete ptr; }

cream::aux_map_initializer cream::aux_map;

cream::cream(const color c, const u_vector<taste>& t, bottle_size bs, const std::string& n, double ac) : non_spirits(bs, n, ac < max_ac && ac >= min_ac ? ac : min_ac), col(c), tastes(t) {}

const double cream::cream_incr = 3.50;

cream::cream(const cream& c) : non_spirits(c), col(c.col), tastes(c.tastes) {}

const double cream::discount_cream = 0.95;

const double cream::max_ac = 21.0;

const double cream::min_ac = 18.0;

cream* cream::clone() const { return new cream(*this); }

double cream::kind_price() const {
  if (get_kind() == small) {
    return -0.50;
  } else if (get_kind() == large) {
    return 0.50;
  }
  return 0.00;
}

double cream::price_increment() const { return kind_price() + cream_incr; }

std::string cream::type_product() const { return "cream"; }

double cream::get_price() const {
  return non_spirits::get_price() + price_increment();
  ;
}

double cream::promotion() const { return get_price() * discount_cream; }

u_vector<taste> cream::get_tastes() const { return tastes; }

color cream::get_color() const { return col; }

std::string cream::code() const {
  std::string aux = "AC0";
  u_vector<taste>::const_iterator cit = tastes.const_begin();
  u_vector<taste>::const_iterator end = tastes.const_end();
  for (; cit != end; cit++) {
    aux += std::to_string(*cit);
  }
  return aux;
}

std::string cream::get_image_path() const {
  std::string name = get_name();
  name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
  return non_spirits::get_image_path() + "cream/" + name + ".png";
}

cream* cream::create(QMap<QString, QVariant>& m) const {
  color _color = static_cast<color>(m["color"].toString().toInt());
  u_vector<taste> _tastes;

  QList<QVariant> list = m["tastes"].toList();
  for (auto const& element : list) {
    _tastes.push_back(static_cast<taste>(element.toString().toInt()));
  }

  bottle_size _bottle = static_cast<bottle_size>(m["bottle_size"].toString().toInt());
  std::string _name = m["name"].toString().toStdString();
  double _alcohol_content = m["alcohol_content"].toString().toDouble();

  return new cream(_color, _tastes, _bottle, _name, _alcohol_content);
}

std::string cream::write() const {
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
