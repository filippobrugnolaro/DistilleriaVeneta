#include "receipt.h"

receipt::receipt() : date(steady_clock::now()), items(u_vector<std::pair<deep_ptr<product>, int>>()) {}

void receipt::add_item(const deep_ptr<product>& p) {
  std::pair<deep_ptr<product>, int> element(p, 1);
  if (!presenza(element.first)) {
    items.push_back(element);
  }
}

void receipt::remove_item(const std::string& name, const std::string& dim) {
  u_vector<std::pair<deep_ptr<product>, int>>::iterator it = items.begin();
  u_vector<std::pair<deep_ptr<product>, int>>::iterator end = items.end();

  bool stop = false;
  for (; it != end && !stop; it++) {
    if ((*it).first->get_name() == name && (*it).first->fromKindToStdString((*it).first->get_kind()) == dim) {
      items.erase(it);
      stop = true;
    }
  }
}

void receipt::delete_all() { items.erase(items.begin(), items.end()); }

void receipt::refresh_quantity(const std::string& name, const std::string& dim, int v) {
  u_vector<std::pair<deep_ptr<product>, int>>::iterator it = items.begin();
  u_vector<std::pair<deep_ptr<product>, int>>::iterator end = items.end();

  bool stop = false;

  for (; it != end && !stop; it++) {
    if ((*it).first->get_name() == name && (*it).first->fromKindToStdString((*it).first->get_kind()) == dim) {
      (*it).second = v;
      stop = true;
    }
  }
}

bool receipt::presenza(const deep_ptr<product>& p) const {
  u_vector<std::pair<deep_ptr<product>, int>>::const_iterator cit = items.const_begin();
  u_vector<std::pair<deep_ptr<product>, int>>::const_iterator end = items.const_end();

  for (; cit != end; cit++) {
    if ((*cit).first->get_name() == p->get_name() && (*cit).first->get_kind() == p->get_kind()) {
      return true;
    }
  }
  return false;
}

unsigned int receipt::total_number_items() const {
  unsigned int count = 0;
  u_vector<std::pair<deep_ptr<product>, int>> aux = get_items();
  auto cit = aux.const_begin();
  auto end = aux.const_end();

  for (; cit != end; cit++) {
    count += (*cit).second;
  }
  return count;
}

double receipt::total_price() const {
  double price = 0;
  u_vector<std::pair<deep_ptr<product>, int>>::const_iterator cit = items.const_begin();
  u_vector<std::pair<deep_ptr<product>, int>>::const_iterator end = items.const_end();

  for (; cit != end; cit++) {
    price += total_price_line(*cit);
  }
  return price;
}

double receipt::total_price_line(const std::pair<deep_ptr<product>, int>& l) const { return l.first->get_price() * l.second; }

double receipt::total_taxes() const {
  double tot_taxes = 0;
  u_vector<std::pair<deep_ptr<product>, int>>::iterator it = items.begin();
  u_vector<std::pair<deep_ptr<product>, int>>::iterator end = items.end();

  for (; it != end; it++) {
    tot_taxes += (it->first->taxes() * it->second);
  }
  return tot_taxes;
}

u_vector<std::pair<deep_ptr<product>, int>> receipt::get_items() const { return items; }
