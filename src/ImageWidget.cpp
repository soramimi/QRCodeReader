#include "ImageWidget.h"
#include <QPainter>

ImageWidget::ImageWidget(QWidget *parent)
	: QWidget(parent)
{

}

void ImageWidget::setImage(const QImage &image)
{
	image_ = image;
	update();
}

void ImageWidget::setBounds(QList<QPoint> const &pts)
{
	pts_ = pts;
	update();
}

void ImageWidget::paintEvent(QPaintEvent *)
{
	QPainter pr(this);

	pr.drawImage(0, 0, image_);

	// draw bounding box
	const int n = pts_.size();
	if (n == 4) {
		pr.setPen(QPen(Qt::cyan));
		for (int i = 0; i < n; i++) {
			int j = (i + 1) % n;
			QPoint pt0 = pts_[i];
			QPoint pt1 = pts_[j];
			pr.drawLine(pt0, pt1);
		}
	}
}

