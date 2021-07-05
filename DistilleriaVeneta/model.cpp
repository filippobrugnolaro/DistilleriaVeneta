#include "model.h"

model::model(const std::string& filename) : r(new receipt()) { load_from_file(filename); }

model::~model() { delete r; }

void model::load_from_file(const std::string& path) {
  io_json io(path);
  products = io.read();
}

u_vector<deep_ptr<product>> model::get_products_json() const { return products; }

void model::add_item(const deep_ptr<product>& p) { r->add_item(p); }

void model::remove_item(const std::string& name, const std::string& dim) { r->remove_item(name, dim); }

void model::delete_all() { r->delete_all(); }

void model::refresh_quantity(const std::string& name, const std::string& dim, int v) { r->refresh_quantity(name, dim, v); }

bool model::presenza(const deep_ptr<product>& p) const { return r->presenza(p); }

unsigned int model::total_number_items() const { return r->total_number_items(); }

double model::total_price_line(const std::pair<deep_ptr<product>, int>& p) const { return r->total_price_line(p); }

double model::total_price() const { return r->total_price(); }

double model::total_taxes() const { return r->total_taxes(); }

u_vector<std::pair<deep_ptr<product>, int>> model::get_receipt() const { return r->get_items(); }

u_vector<deep_ptr<product>> model::filter_products(const std::string& _key) const { return filter::products(products, _key); }

u_vector<deep_ptr<product>> model::filter_color(const unsigned int _key) const { return filter::colors(products, _key); }

u_vector<deep_ptr<product>> model::filter_taste(const unsigned int _key) const { return filter::tastes(products, static_cast<taste>(_key)); }

u_vector<deep_ptr<product>> model::filter_all() const { return products; }

u_vector<deep_ptr<product>> model::filter_cre_ac() const { return filter::cre_ac(products); }

u_vector<deep_ptr<product>> model::filter_dec_ac() const { return filter::dec_ac(products); }
