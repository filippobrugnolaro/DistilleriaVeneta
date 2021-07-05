#ifndef NON_SPIRITS_H_
#define NON_SPIRITS_H_
#include "product.h"

class non_spirits : public product {
 public:
  /**
   * @brief costruttore di non_spirits
   * @param bs : bottle_size, indica la grandezza dell'alcolico, default = medium
   * @param n : const std::string&, indica il nome dell'alcolico, default = ""
   * @param ac : double, indica il contenuto alcolico dell'alcolico, default = min_ac
   */
  non_spirits(bottle_size = medium, const std::string& = "", double = min_ac);

  /**
   * @brief costruttore di copia di non_spirits
   * @param ns : const non_spirits&, indirizzo costante dell'alcolico da copiare
   */
  non_spirits(const non_spirits&);

  static const double min_ac;
  static const double max_ac;

  /**
   * @brief metodo kind_price
   * @return double, variazione di prezzo dell'alcolico in base alla dimensione
   */
  double kind_price() const;

  /**
   * @brief metodo price_increment
   * @return double, variazione di prezzo totale dell'alcolico
   */
  double price_increment() const;

  /**
   * @brief metodo getter per il prezzo totale dell'alcolico
   * @return double, prezzo totale dell'alcolico
   */
  virtual double get_price() const override;

  /**
   * @brief metodo code
   * @return std::string, codice dell'alcolico
   */
  virtual std::string code() const override;

  /**
   * @brief metodo getter per il path dell'alcolico
   * @return std::string, path dell'alcolico
   */
  virtual std::string get_image_path() const override;
};

#endif  // NON_SPIRITS_H_
