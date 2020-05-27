#ifndef WIDGET_H
#define WIDGET_H


#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include "functions.h"
#include "calculations.h"


QT_BEGIN_NAMESPACE

namespace Ui {
  class Widget;
}

QT_END_NAMESPACE


class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr, double scale = 1.0);
  ~Widget();

 protected:
  void paintEvent(QPaintEvent *event);
  void resizeEvent(QResizeEvent *event);
  void keyPressEvent(QKeyEvent *event);
  void ReDraw();

 private:
  Ui::Widget *ui;
  double scale_;
  QPixmap *pixmap_;
};


#endif // WIDGET_H
