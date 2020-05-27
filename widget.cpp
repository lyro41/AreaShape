#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent, double scale) : QWidget(parent), ui(new Ui::Widget), scale_(scale) {
  ui->setupUi(this);
  pixmap_ = new QPixmap(this->width(), this->height());
  this->ReDraw();
  return;
}


Widget::~Widget() {
  delete ui;
}


void Widget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.drawPixmap(0, 0, pixmap_->scaled(this->width(), this->height()));
  painter.drawPixmap(0, 0, *pixmap_);
  return;
}


void Widget::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Plus) {
    scale_ -= 0.01;
  } else if (event->key() == Qt::Key_Minus) {
    scale_ += 0.01;
  }
  this->ReDraw();
  return;
}


void Widget::resizeEvent(QResizeEvent *event) {
  this->ReDraw();
  return;
}


void Widget::ReDraw() {
  delete pixmap_;
  pixmap_ = new QPixmap(this->width(), this->height());
  pixmap_->fill();

  QPainter painter(pixmap_);


  painter.setPen(QColor("#91b5eb"));
  const int gap = 20;

  for (int x = (this->width() >> 1) - 1; x >= 0; x -= gap) {
    painter.drawLine(x, 0, x, this->height());
  }

  for (int x = this->width() >> 1; x < this->width(); x += gap) {
    painter.drawLine(x, 0, x, this->height());
  }

  for (int y = (this->height() >> 1) - 1; y >= 0; y -= gap) {
    painter.drawLine(0, y, this->width(), y);
  }

  for (int y = this->height() >> 1; y < this->height(); y += gap) {
    painter.drawLine(0, y, this->width(), y);
  }


  painter.setPen(Qt::black);

  painter.drawLine((this->width() >> 1) - 1, 0, (this->width() >> 1) - 1, this->height());
  painter.drawLine(this->width() >> 1, 0, this->width() >> 1, this->height());

  painter.drawLine((this->width() >> 1) - 1, 0, (this->width() >> 1) - 11, 10);
  painter.drawLine(this->width() >> 1, 0, (this->width() >> 1) - 10, 10);
  painter.drawLine((this->width() >> 1) - 1, 0, (this->width() >> 1) + 9, 10);
  painter.drawLine(this->width() >> 1, 0, (this->width() >> 1) + 10, 10);


  painter.drawLine(0, (this->height() >> 1) - 1, this->width(), (this->height() >> 1) - 1);
  painter.drawLine(0, this->height() >> 1, this->width(), this->height() >> 1);

  painter.drawLine(this->width() - 1, (this->height() >> 1) - 1, this->width() - 11, (this->height() >> 1) - 11);
  painter.drawLine(this->width() - 1, this->height() >> 1, this->width() - 11, (this->height() >> 1) - 10);
  painter.drawLine(this->width() - 1, (this->height() >> 1) - 1, this->width() - 11, (this->height() >> 1) + 9);
  painter.drawLine(this->width() - 1, this->height() >> 1, this->width() - 11, (this->height() >> 1) + 10);


  painter.drawText((this->width() >> 1) - gap, (this->height() >> 1) + gap, QString::number(0));
  painter.drawText((this->width() >> 1) - gap + 1, gap >> 1, QString('y'));
  painter.drawText(this->width() - gap + 1, (this->height() >> 1) + gap, QString('x'));


  for (int x = (this->width() >> 1) - 1 - (gap << 2), i = 1; x >= 0; x -= gap << 2, ++i) {
    painter.drawLine(x - 1, (this->height() >> 1) - 6, x - 1, (this->height() >> 1) + 5);
    painter.drawLine(x, (this->height() >> 1) - 6, x, (this->height() >> 1) + 5);
    painter.drawText(x - gap, (this->height() >> 1) + gap, QString::number(- scale_ * i * 4, 'f', 3));
  }

  for (int x = (this->width() >> 1) + (gap << 2), i = 1; x < this->width() - gap; x += gap << 2, ++i) {
    painter.drawLine(x, (this->height() >> 1) - 6, x, (this->height() >> 1) + 5);
    painter.drawLine(x + 1, (this->height() >> 1) - 6, x + 1, (this->height() >> 1) + 5);
    painter.drawText(x - gap, (this->height() >> 1) + gap, QString::number(scale_ * i * 4, 'f', 3));
  }

  for (int y = (this->height() >> 1) - 1 - (gap << 2), i = 1; y >= gap; y -= gap << 2, ++i) {
    painter.drawLine((this->width() >> 1) - 6, y - 1, (this->width() >> 1) + 5, y - 1);
    painter.drawLine((this->width() >> 1) - 6, y, (this->width() >> 1) + 5, y);
    painter.drawText((this->width() >> 1) + gap - 1, y + gap, QString::number(scale_ * i * 4, 'f', 3));
  }

  for (int y = (this->height() >> 1) + (gap << 2), i = 1; y < this->height(); y += gap << 1, ++i) {
    painter.drawLine((this->width() >> 1) - 6, y, (this->width() >> 1) + 5, y);
    painter.drawLine((this->width() >> 1) - 6, y + 1, (this->width() >> 1) + 5, y + 1);
    painter.drawText((this->width() >> 1) + gap - 1, y + gap, QString::number(- scale_ * i * 2, 'f', 3));
  }


  painter.setPen(Qt::red);

  for (int x = 0; x < this->width(); ++x) {
    painter.drawLine(x, (this->height() >> 1) - f1(static_cast<double>(x - x / (this->width() >> 1) - (this->width() >> 1) + 1) *
                                                   (scale_ / static_cast<double>(gap))) / scale_ * static_cast<double>(gap),
                     x + 1, (this->height() >> 1) - f1(static_cast<double>(x + 1 - x / (this->width() >> 1) - (this->width() >> 1) + 1) *
                                                       (scale_ / static_cast<double>(gap))) / scale_ * static_cast<double>(gap));
  }

  painter.setPen(Qt::blue);

  for (int x = 0; x < this->width(); ++x) {
    if (x + 1 == this->width() >> 1) continue;
    painter.drawLine(x, (this->height() >> 1) - f2(static_cast<double>(x - x / (this->width() >> 1) - (this->width() >> 1) + 1) *
                                                   (scale_ / static_cast<double>(gap))) / scale_ * static_cast<double>(gap),
                     x + 1, (this->height() >> 1) - f2(static_cast<double>(x + 1 - x / (this->width() >> 1) - (this->width() >> 1) + 1) *
                                                       (scale_ / static_cast<double>(gap))) / scale_ * static_cast<double>(gap));
  }

  painter.setPen(Qt::magenta);

  for (int x = 0; x < this->width(); ++x) {
    if (x + 1 == this->width() >> 1) continue;
    painter.drawLine(x, (this->height() >> 1) - f3(static_cast<double>(x - x / (this->width() >> 1) - (this->width() >> 1) + 1) *
                                                   (scale_ / static_cast<double>(gap))) / scale_ * static_cast<double>(gap),
                     x + 1, (this->height() >> 1) - f3(static_cast<double>(x + 1 - x / (this->width() >> 1) - (this->width() >> 1) + 1) *
                                                       (scale_ / static_cast<double>(gap))) / scale_ * static_cast<double>(gap));
  }

  double tmp = FindArea(f1, df1, ddf1, f2, df2, ddf2, f3, df3, ddf3);
  this->setWindowTitle(QString("Area of the given curved shape is ") + QString::number(tmp, 'f', 7));

  this->repaint();
}
