#ifndef SPIRITS_H_
#define SPIRITS_H_

#include "product.h"

class spirits : public product {
 public:
  /**
   * @brief costruttore di spirits
   * @param bs : bottle_size, indica la grandezza del superalcolico, default = medium
   * @param n : const std::string&, indica il nome del superalcolico, default = ""
   * @param ac : double, indica il contenuto alcolico del superalcolico, default = min_ac
   */
  spirits(bottle_size = medium, const std::string& = "", double = min_ac);
  /**
   * @brief costruttore di copia di spirits
   * @param s : const spirits&, indirizzo costante del superalcolico da copiare
   */
  spirits(const spirits&);

  static const double min_ac;
  static const double max_ac;

  /**
   * @brief metodo kind_price
   * @return double, variazione di prezzo del superalcolico in base alla dimensione
   */
  double kind_price() const;

  /**
   * @brief metodo price_increment
   * @return double, variazione di prezzo totale del superalcolico
   */
  double price_increment() const;

  /**
   * @brief metodo getter per il prezzo totale del superalcolico
   * @return double, prezzo totale del superalcolico
   */
  virtual double get_price() const override;

  /**
   * @brief metodo code
   * @return std::string, codice del superalcolico
   */
  virtual std::string code() const override;

  /**
   * @brief metodo getter per il path del superalcolico
   * @return std::string, path del superalcolico
   */
  virtual std::string get_image_path() const override;
};

#endif  // SPIRITS_H_
