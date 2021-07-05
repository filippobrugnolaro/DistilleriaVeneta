#include "young.h"

young::aux_map_initializer::aux_map_initializer() {
  ptr = new young();
  _map[ptr->type_product()] = ptr;
}
young::aux_map_initializer::~aux_map_initializer() { delete ptr; }
young::aux_map_initializer young::aux_map;

young::young(const color c, const u_vector<taste>& t, bottle_size bs, const std::string& n, double ac) : grappa(bs, n, ac < max_ac && ac >= min_ac ? ac : min_ac), col(c), tastes(t) {}

young::young(const young& y) : grappa(y), col(y.col), tastes(y.tastes) {}

double const young::discount_young = 0.85;

young* young::clone() const { return new young(*this); }

double young::kind_price() const {
  if (get_kind() == small) {
    return -0.30;
  } else if (get_kind() == large) {
    return 0.10;
  }
  return 0.00;
}

double young::price_increment() const { return kind_price(); }

std::string young::type_product() const { return "young"; }

double young::get_price() const { return grappa::get_price() + price_increment(); }

double young::promotion() const { return get_price() * discount_young; }

u_vector<taste> young::get_tastes() const { return tastes; }

color young::get_color() const { return col; }

std::string young::code() const {
  std::string aux = "SGY";
  u_vector<taste>::const_iterator cit = tastes.const_begin();
  u_vector<taste>::const_iterator end = tastes.const_end();
  for (; cit != end; cit++) {
    aux += std::to_string(*cit);
  }
  return aux;
}

std::string young::get_image_path() const {
  std::string name = get_name();
  name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
  return grappa::get_image_path() + "young/" + name;
}

young* young::create(QMap<QString, QVariant>& m) const {
  color _color = static_cast<color>(m["color"].toString().toInt());
  u_vector<taste> _tastes;

  QList<QVariant> list = m["tastes"].toList();
  for (auto const& element : list) {
    _tastes.push_back(static_cast<taste>(element.toString().toInt()));
  }

  bottle_size _bottle = static_cast<bottle_size>(m["bottle_size"].toString().toInt());
  std::string _name = m["name"].toString().toStdString();
  double _alcohol_content = m["alcohol_content"].toString().toDouble();

  return new young(_color, _tastes, _bottle, _name, _alcohol_content);
}

std::string young::write() const {
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
