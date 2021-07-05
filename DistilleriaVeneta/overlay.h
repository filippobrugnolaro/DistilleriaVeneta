#ifndef OVERLAY_H
#define OVERLAY_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class QOverlay : public QWidget {
  Q_OBJECT
 private:
  QVBoxLayout* overlay_layout;
  QPushButton* small_button;
  QPushButton* medium_button;
  QPushButton* large_button;

 public:
  /**
   * @brief costruttore di QOverlay
   * @param parent : QWidget*, puntatore al padre, default = nullptr
   */
  explicit QOverlay(QWidget* = nullptr);

  /**
   * @brief getter al pulsante small
   * @return QPushbutton*, puntatore al bottone small
   */
  QPushButton* get_small_button() const;

  /**
   * @brief getter al pulsante medium
   * @return QPushbutton*, puntatore al bottone medium
   */
  QPushButton* get_medium_button() const;

  /**
   * @brief getter al pulsante large
   * @return QPushbutton*, puntatore al bottone large
   */
  QPushButton* get_large_button() const;
};

#endif  // OVERLAY_H
