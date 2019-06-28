#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT
private:
	struct Private;
	Private *m;
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
private slots:
	void doCapture();
private:
	Ui::MainWindow *ui;
	void setBounds(const QList<QPoint> &pts);
	void setStatusText(const QString &text);
};

#endif // MAINWINDOW_H
