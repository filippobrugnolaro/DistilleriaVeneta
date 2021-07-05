#ifndef FILTER_H
#define FILTER_H

#include <functional>
#include <string>

#include "./Hierarchy/enum.h"
#include "./Hierarchy/product.h"
#include "./Utilities/deep_ptr.hpp"
#include "./Utilities/u_vector.hpp"

class filter {
 public:
  filter();

  /**
   * @brief colors, metodo per il filtraggio in base al colore
   * @param _vector: const u_vector<deep_ptr<product>>&, vettore nel quale eseguire il filtro
   * @param _value: const unsigned int, chiave per il filtro
   * @return
   */
  static u_vector<deep_ptr<product>> colors(const u_vector<deep_ptr<product>>&, const unsigned int = 0);

  /**
   * @brief products, metodo per il filtraggio in base al prodotto
   * @param _vector: const u_vector<deep_ptr<product>>&, vettore nel quale eseguire il filtro
   * @param _value: std::string, chiave per il filtro
   * @return
   */
  static u_vector<deep_ptr<product>> products(const u_vector<deep_ptr<product>>&, const std::string& = std::string());

  /**
   * @brief tastas, metodo per il filtraggio in base al gusto
   * @param _vector: const u_vector<deep_ptr<product>>&, vettore nel quale eseguire il filtro
   * @param _value: const taste, chiave per il filtro
   * @return
   */
  static u_vector<deep_ptr<product>> tastes(const u_vector<deep_ptr<product>>&, const taste = taste::_amable);

  /**
   * @brief cre_ac, metodo per il filtraggio in ordine crescente
   * @param _vector: const u_vector<deep_ptr<product>>&, vettore nel quale eseguire il filtro
   * @return
   */
  static u_vector<deep_ptr<product>> cre_ac(const u_vector<deep_ptr<product>>&);

  /**
   * @brief dec_ac, metodo per il filtraggio in ordine decrescente
   * @param _vector: const u_vector<deep_ptr<product>>&, vettore nel quale eseguire il filtro
   * @return
   */
  static u_vector<deep_ptr<product>> dec_ac(const u_vector<deep_ptr<product>>&);
};

#endif  // FILTER_H
