#ifndef __DEEP_PTR_H__
#define __DEEP_PTR_H__
template <class T>
class deep_ptr {
 private:
 T* pointer;
 public:
  /**
  * @brief costruttore di deep_ptr
  * @param dp T*, puntatore templatizzato polimorfo inizializzato di default a nullptr
 */
  deep_ptr(T* = nullptr);

  /**
   * @brief costruttore di copia di deep_ptr
   * @param dp const deep_ptr&, deep_ptr dalla quale costruire la copia
   */
  deep_ptr(const deep_ptr&);

  /**
   * @brief distruttore di deep_ptr, tramite il distruttore virtuale di T
   */
  ~deep_ptr();

  /**
   * @brief metodo per ricevere il puntatore di deep_ptr
   * @return T*, puntatore di deep_ptr
   */
  T* get() const;

  /**
   * @brief operatore di assegnazione
   * @param dp const deep_ptr&, deep_ptr con il quale fare l'assegnazione
   * @return deep_ptr&, indirizzo di deep_ptr di invocazione riassegnato
   */
  deep_ptr& operator=(const deep_ptr&);

  /**
   * @brief operatore di uguaglianza
   * @param dp const deep_ptr&, deep_ptr con il quale fare il confronto
   * @return bool, true se deep_ptr di invocazione è uguale a dp, false altrimenti
   */
  bool operator==(const deep_ptr&) const;

  /**
   * @brief operatore di disuguaglianza
   * @param dp const deep_ptr&, deep_ptr con il quale fare il confronto
   * @return bool, true se deep_ptr di invocazione è diverso di dp, false altrimenti
   */
  bool operator!=(const deep_ptr&) const;

  /**
   * @brief operatore di minoranza
   * @param dp const deep_ptr&, deep_ptr con il quale fare il confronto
   * @return bool, true se deep_ptr di invocazione è minore di dp, false altrimenti
   */
  bool operator<(const deep_ptr&) const;

  /**
   * @brief operatore di minore-uguale
   * @param dp const deep_ptr&, deep_ptr con il quale fare il confronto
   * @return bool, true se deep_ptr di invocazione è minore-uguale di dp, false altrimenti
   */
  bool operator<=(const deep_ptr&) const;

  /**
   * @brief operatore di maggioranza
   * @param dp const deep_ptr&, deep_ptr con il quale fare il confronto
   * @return bool, true se deep_ptr di invocazione è maggiore di dp, false altrimenti
   */
  bool operator>(const deep_ptr&) const;

  /**
   * @brief operatore di maggiore-uguale
   * @param dp const deep_ptr&, deep_ptr con il quale fare il confronto
   * @return bool, true se deep_ptr di invocazione è maggiore-uguale di dp, false altrimenti
   */
  bool operator>=(const deep_ptr&) const;

  /**
   * @brief operatore booleano
   * @return bool, true se deep_ptr punta ad un oggetto, false altrimenti
   */
  explicit operator bool() const;

  /**
   * @brief operatore di dereferenziazione
   * @return T&, indirizzo della variabile puntata da deep_ptr
   */
  T& operator*() const;

  /**
   * @brief operatore freccia
   * @return T*, puntatore alla variabile puntata da deep_ptr
   */
  T* operator->() const;

  /**
     * @brief operatore di dereferenziazione
     * @return T&, indirizzo dell'oggetto dereferenziato
     */
  T& operator[](unsigned int) const;
};

template <class T>
deep_ptr<T>::deep_ptr(T* dp) : pointer(dp) {}

template <class T>
deep_ptr<T>::deep_ptr(const deep_ptr& dp) : pointer(dp.pointer ? dp.pointer->clone() : nullptr) {}

template <class T>
deep_ptr<T>::~deep_ptr() {
  if (pointer) {
    delete pointer;
  }
}

template <class T>
T* deep_ptr<T>::get() const {
  return pointer;
}

template <class T>
deep_ptr<T>& deep_ptr<T>::operator=(const deep_ptr& dp) {
  if (this != &dp) {
    delete pointer;
    pointer = dp.pointer ? dp.pointer->clone() : nullptr;
  }
  return *this;
}

template <class T>
bool deep_ptr<T>::operator==(const deep_ptr& dp) const {
  return pointer == dp.pointer;
}

template <class T>
bool deep_ptr<T>::operator!=(const deep_ptr& dp) const {
  return pointer != dp.pointer;
}

template <class T>
bool deep_ptr<T>::operator<(const deep_ptr& dp) const {
  return pointer < dp.pointer;
}

template <class T>
bool deep_ptr<T>::operator<=(const deep_ptr& dp) const {
  return pointer <= dp.pointer;
}

template <class T>
bool deep_ptr<T>::operator>(const deep_ptr& dp) const {
  return pointer > dp.pointer;
}

template <class T>
bool deep_ptr<T>::operator>=(const deep_ptr& dp) const {
  return pointer >= dp.pointer;
}

template <class T>
deep_ptr<T>::operator bool() const {
  return *this != nullptr;
}

template <class T>
T& deep_ptr<T>::operator*() const {
  return *pointer;
}

template <class T>
T* deep_ptr<T>::operator->() const {
  return pointer;
}

template <class T>
T& deep_ptr<T>::operator[](unsigned int index) const{
  return *(pointer + index);
}
#endif  // __DEEP_PTR_H__
