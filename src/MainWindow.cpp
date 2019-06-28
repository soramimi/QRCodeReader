#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "opencv2/opencv.hpp"
#include <QDebug>
#include <QLabel>
#include <QTimer>

#define VIDEO_DEVICE_NUMBER 0

class Capture {
private:
	cv::VideoCapture cap;
public:
	void open()
	{
		close();
		bool f = cap.open(VIDEO_DEVICE_NUMBER);
		qDebug() << f;
	}
	void close()
	{
		cap.release();
	}
	bool isOpened() const
	{
		return cap.isOpened();
	}
	QImage capture()
	{
		if (isOpened()) {
			cv::Mat frame;
			cap.read(frame);
			if (frame.dims == 2 && frame.channels() == 3) {
				int w = frame.cols;
				int h = frame.rows;
				QImage image(w, h, QImage::Format_RGB32);
				for (int i = 0; i < h; i++) {
					uint8_t const *src = frame.ptr(i);
					QRgb *dst = (QRgb *)image.scanLine(i);
					for (int j = 0; j < w; j++) {
						dst[j] = qRgb(src[2], src[1], src[0]);
						src += 3;
					}
				}
				return image;
			}
		}
		return QImage();
	}
};

struct MainWindow::Private {
	QLabel *status_label = nullptr;

	Capture cap;
	QTimer timer;

	QByteArray last_data;
	QList<QPoint> pts;
};

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, m(new Private)
{
	ui->setupUi(this);
	m->status_label = new QLabel;
	ui->statusBar->addWidget(m->status_label);

	m->cap.open();

	connect(&m->timer, SIGNAL(timeout()), this, SLOT(doCapture()));
	m->timer.setInterval(0);
	m->timer.start();
}

MainWindow::~MainWindow()
{
	m->cap.close();
	delete m;
	delete ui;
}

QList<QByteArray> scan(QImage const &source, QList<QPoint> *pts);

void MainWindow::setStatusText(QString const &text)
{
	m->status_label->setText(text);
}

void MainWindow::setBounds(QList<QPoint> const &pts)
{
	ui->widget->setBounds(pts);
}

void MainWindow::doCapture()
{
	QImage image = m->cap.capture();
	int w = image.width();
	int h = image.height();
	if (w > 0 && h > 0) {
		ui->widget->setImage(image);

		QImage grayed = image.convertToFormat(QImage::Format_Grayscale8);

		QList<QPoint> pts;
		QList<QByteArray> results = scan(grayed, &pts);
		if (results.empty()) {
			if (!m->last_data.isNull()) {
				setStatusText("(none)");
			}
			m->last_data = QByteArray();
			setBounds({});
		} else {
			QByteArray ba = results.front();
			if (ba != m->last_data) {
				m->last_data = ba;
				QString text = QString::fromUtf8(ba);
				setStatusText(text);
			}
			setBounds(pts);
		}
	}
}




