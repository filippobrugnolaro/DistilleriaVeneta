#ifndef OLD_H_
#define OLD_H_

#include "grappa.h"

class old : public grappa {
 private:
  class aux_map_initializer {
   private:
    old* ptr;

   public:
    aux_map_initializer();
    ~aux_map_initializer();
  };
  static aux_map_initializer aux_map;

  color col;
  u_vector<taste> tastes;
  bool barrique;
  unsigned int month;

 protected:
  static const double month_incr;
  unsigned int get_month_old() const;

 public:
  /**
   * @brief costruttore di old
   * @param c : const color, indica il colore della grappa invecchiata, default = yellow_trasparent
   * @param t : const u_vector<taste>&, indica i gusti che può avere la grappa invecchiata, default = {}
   * @param b : bool, 'true' se la grappa è barricata, 'false' altrimenti, default = false
   * @param m : unsigned int, indica il numero di mesi di invecchiamento, default = 18
   * @param bs : bottle_size, indica la grandezza della grappa invecchiata, default = medium
   * @param n : const std::string&, indica il nome della grappa invecchiata, default = ""
   * @param ac : double, indica il contenuto alcolico della grappa invecchiata, default = min_ac
   */
  old(const color = yellow_trasparent, const u_vector<taste>& = {}, bool = false, unsigned int = 18, bottle_size = medium, const std::string& = "", double = min_ac);

  /**
   * @brief costruttore di copia di old
   * @param o : const old&, indirizzo costante della grappa invecchiata da copiare
   */
  old(const old&);

  static const double discount_old;

  /**
   * @brief metodo di clonazione
   * @return product*, ritorna un puntatore alla nuova grappa invecchiata creata
   */
  virtual old* clone() const override;

  /**
   * @brief metodo kind_price
   * @return double, variazione di prezzo della grappa invecchiata in base alla dimensione
   */
  double kind_price() const;

  /**
   * @brief metodo price_increment
   * @return double, variazione di prezzo totale della grappa invecchiata
   */
  double price_increment() const;

  /**
   * @brief metodo type_product
   * @return std::string, tipo di prodotto a cui il puntatore sta puntando (old)
   */
  virtual std::string type_product() const override;

  /**
   * @brief metodo getter per il prezzo totale della grappa invecchiata
   * @return double, prezzo totale della grappa invecchiata
   */
  virtual double get_price() const override;

  /**
   * @brief metodo promotion
   * @return double, prezzo totale della grappa invecchiata scontato
   */
  virtual double promotion() const override;

  /**
   * @brief metodo getter per i gusti della grappa invecchiata
   * @return u_vector<taste>, vettore dei gusti della grappa invecchiata
   */
  virtual u_vector<taste> get_tastes() const override;

  /**
   * @brief metodo getter per il colore della grappa invecchiata
   * @return color, colore della grappa invecchiata
   */
  virtual color get_color() const override;

  /**
   * @brief metodo code
   * @return std::string, codice della grappa invecchiata
   */
  virtual std::string code() const override;

  /**
   * @brief metodo getter per il path della grappa invecchiata
   * @return std::string, path della grappa invecchiata
   */
  virtual std::string get_image_path() const override;

  /**
   * @brief metodo per controllare se una grappa invecchiata è barricata
   * @return bool, 'true' sse barrique è true, 'false' altrimenti
   */
  bool is_barrique() const;

  /**
   * @brief create
   * @param m: QMap<QString, QVariant>&, mappa contentente tutti i dati per la costruzione
   * @return old*, oggetto creato
   */
  virtual old* create(QMap<QString, QVariant>&) const override;

  /**
   * @brief metodo per la preparazione dell'oggetto per la scrittura
   * @return std::string, serializzazione dell'oggetto
   */
  virtual std::string write() const override;
};

#endif  // OLD_H_
