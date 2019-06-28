#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QImage>

class ImageWidget : public QWidget {
	Q_OBJECT
private:
	QImage image_;
	QList<QPoint> pts_;
protected:
	void paintEvent(QPaintEvent *);
public:
	explicit ImageWidget(QWidget *parent = 0);
	void setImage(QImage const &image);
	void setBounds(const QList<QPoint> &pts);
};

#endif // IMAGEWIDGET_H
