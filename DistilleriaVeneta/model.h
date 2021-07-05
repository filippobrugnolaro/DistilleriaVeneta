#ifndef _MODEL_H
#define _MODEL_H

#include "./Hierarchy/product.h"
#include "./Utilities/u_vector.hpp"
#include "filter.h"
#include "io_json.h"
#include "receipt.h"

class model {
 private:
  receipt* r;
  u_vector<deep_ptr<product>> products;

 public:
  /**
   * @brief costruttore di model
   * @param filename: const std::string&, path del file json contentente i prodotti inseribili nello scontrino, default = ":/data/data.json"
   */
  model(const std::string& = ":/data/data.json");

  ~model();

  /**
   * @brief metodo per il caricamento dei prodotti inseribili nello scontrino
   * @param path : const std::string&, path del file json contentente i prodotti inseribili nello scontrino, default = ":/data/data.json"
   */
  void load_from_file(const std::string& = ":/data/data.json");

  /**
   * @brief metodo getter per ottenere i prodotti inseribili nello scontrino
   * @return u_vector<deep_ptr<product>>, vettore dei prodotti inseribili nello scontrino
   */
  u_vector<deep_ptr<product>> get_products_json() const;

  /**
   * @brief metodo per aggiungere un elemento al vettore scontrino
   * @param p : const deep_ptr<product>&, indirizzo del puntatore profondo al prodotto
   */
  void add_item(const deep_ptr<product>&);

  /**
   * @brief metodo per rimuove un elemento dal vettore scontrino
   * @param name : std::string, indica il nome del prodotto da rimuovere
   * @param dim : std::string, indica la dimensione del prodotto da rimuovere
   */
  void remove_item(const std::string&, const std::string&);

  /**
   * @brief metodo per rimuovere tutti i prodotti dal vettore scontrino
   */
  void delete_all();

  /**
   * @brief metodo per cambiare la quantità di un prodotto nel vettore scontrino
   * @param name : std::string, indica il nome del prodotto di cui si vuole modificare la quantità
   * @param dim : std::string, indica la dimensione del prodotto di cui si vuole modificare la quantità
   * @param v : int, nuovo quantità del prodotto
   */
  void refresh_quantity(const std::string&, const std::string&, int);

  /**
   * @brief metodo per verificare la presenza di un prodotto nel vettore scontrino
   * @param p : const deep_ptr<product>&, indirizzo del puntatore profondo al prodotto
   * @return bool, 'true' sse nome e dimensione del prodotto coincide, 'false' altrimenti
   */
  bool presenza(const deep_ptr<product>&) const;

  /**
   * @brief metodo per contare il numero degli elementi totale nel vettore scontrino
   * @return unsigned int, numero di prodotti totale nel vettore
   */
  unsigned int total_number_items() const;

  /**
   * @brief metodo che ritorna il prezzo di un prodotto in base alla quantità
   * @param l : std::pair<deep_ptr<product>, int>, coppia puntatore-quantità del prodotto
   * @return double, prezzo di un prodotto in base alla quantità
   */
  double total_price_line(const std::pair<deep_ptr<product>, int>&) const;

  /**
   * @brief metodo per il prezzo totale del vettore scontrino
   * @return double, indica il prezzo totale dello scontrino
   */
  double total_price() const;

  /**
   * @brief metodo per le tasse totali incluse nel prezzo
   * @return double, indica il totale delle tasse dello scontrino
   */
  double total_taxes() const;

  /**
   * @brief metodo getter per avere lo scontrino
   * @return u_vector<std::pair<deep_ptr<product>, int>>, scontrino contenente tutti i prodotti
   */
  u_vector<std::pair<deep_ptr<product>, int>> get_receipt() const;

  /**
   * @brief filter_products
   * @param _key: const std::string&, tipo di prodotto da ricercare
   * @return u_vector<deep_ptr<product>>, vettore contenente i prodotti desiderati
   */
  u_vector<deep_ptr<product>> filter_products(const std::string& = std::string()) const;

  /**
   * @brief filter_color
   * @param _key: unsigned int, colore del prodotto da ricercare
   * @return u_vector<deep_ptr<product>>, vettore contenente i prodotti desiderati
   */
  u_vector<deep_ptr<product>> filter_color(const unsigned int = 0) const;

  /**
   * @brief filter_taste
   * @param _key: const std::string&, gusto del prodotto da ricercare
   * @return u_vector<deep_ptr<product>>, vettore contenente i prodotti desiderati
   */
  u_vector<deep_ptr<product>> filter_taste(const unsigned int = 0) const;

  /**
   * @brief filter_products
   * @return u_vector<deep_ptr<product>>, vettore contenente tutti i prodotti
   */
  u_vector<deep_ptr<product>> filter_all() const;

  /**
   * @brief filter_products
   * @return u_vector<deep_ptr<product>>, vettore contenente tutti i prodotti in ordine crescente secondo il contenuto alcolico
   */
  u_vector<deep_ptr<product>> filter_cre_ac() const;

  /**
   * @brief filter_products
   * @return u_vector<deep_ptr<product>>, vettore contenente tutti i prodotti in ordine decrescente secondo il contenuto alcolico
   */
  u_vector<deep_ptr<product>> filter_dec_ac() const;
};
#endif
