#include "overlay.h"

QOverlay::QOverlay(QWidget* parent) : QWidget(parent) {
  overlay_layout = new QVBoxLayout(this);

  small_button = new QPushButton("Small", this);
  small_button->setObjectName("overlay_button");

  medium_button = new QPushButton("Medium", this);
  medium_button->setObjectName("overlay_button");

  large_button = new QPushButton("Large", this);
  large_button->setObjectName("overlay_button");

  overlay_layout->addWidget(small_button);
  overlay_layout->addWidget(medium_button);
  overlay_layout->addWidget(large_button);

  setLayout(overlay_layout);
}

QPushButton* QOverlay::get_small_button() const { return small_button; }

QPushButton* QOverlay::get_medium_button() const { return medium_button; }

QPushButton* QOverlay::get_large_button() const { return large_button; }
