#ifndef GRAPPA_H_
#define GRAPPA_H_

#include "spirits.h"

class grappa : public spirits {
 private:
 protected:
  static const double grappa_incr;

 public:
  /**
   * @brief costruttore di grappa
   * @param bs : bottle_size, indica la grandezza della grappa, default = medium
   * @param n : const std::string&, indica il nome della grappa, default = ""
   * @param ac : double, indica il contenuto alcolico della grappa, default = min_ac
   */
  grappa(bottle_size = medium, const std::string& = "", double = min_ac);

  /**
   * @brief costruttore di copia di grappa
   * @param g : const grappa&, indirizzo costante della grappa da copiare
   */
  grappa(const grappa&);

  static const double min_ac;
  static const double max_ac;

  /**
   * @brief metodo kind_price
   * @return double, variazione di prezzo della grappa in base alla dimensione
   */
  double kind_price() const;

  /**
   * @brief metodo price_increment
   * @return double, variazione di prezzo totale della grappa
   */
  double price_increment() const;

  /**
   * @brief metodo getter per il prezzo totale della grappa
   * @return double, prezzo totale della grappa
   */
  virtual double get_price() const override;

  /**
   * @brief metodo code
   * @return std::string, codice della grappa
   */
  virtual std::string code() const override;

  /**
   * @brief metodo getter per il path della grappa
   * @return std::string, path della grappa
   */
  virtual std::string get_image_path() const override;
};

#endif  // GRAPPA_H_
