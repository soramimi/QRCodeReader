
#include "MainWindow.h"
#include <QApplication>
#include <stdint.h>
#include <zbar.h>

QList<QByteArray> scan(QImage const &source, QList<QPoint> *pts)
{
	QList<QByteArray> results;
	int width = source.width();
	int height = source.height();
	if (width > 0 && height > 0) {

		zbar_image_scanner_t *scanner = nullptr;

		/* create a reader */
		scanner = zbar_image_scanner_create();

		/* configure the reader */
		zbar_image_scanner_set_config(scanner, ZBAR_QRCODE, ZBAR_CFG_ENABLE, 1);

		/* obtain image data */
		void *raw = nullptr;
		//	get_data(path, &width, &height, &raw);
		raw = malloc(width * height);
		for (int i = 0; i < height; i++) {
			memcpy((uint8_t *)raw + width * i, source.scanLine(i), width);
		}

		/* wrap image data */
		zbar_image_t *image = zbar_image_create();
		zbar_image_set_format(image, *(int*)"Y800");
		zbar_image_set_size(image, width, height);
		//	zbar_image_set_data(image, raw, width * height, zbar_image_free_data);
		zbar_image_set_data(image, raw, width * height, zbar_image_free_data);

		/* scan the image for barcodes */
		zbar_scan_image(scanner, image);

		/* extract results */
		const zbar_symbol_t *symbol = zbar_image_first_symbol(image);
		for (; symbol; symbol = zbar_symbol_next(symbol)) {
			/* do something useful with results */
			const char *data = zbar_symbol_get_data(symbol);
			unsigned int size = zbar_symbol_get_data_length(symbol);
			if (pts) {
				int n = zbar_symbol_get_loc_size(symbol);
				for (int i = 0; i < n; i++) {
					int x = zbar_symbol_get_loc_x(symbol, i);
					int y = zbar_symbol_get_loc_y(symbol, i);
					pts->push_back(QPoint(x, y));
				}
			}
			QByteArray ba(data, size);
			results.push_back(ba);
//			zbar_symbol_type_t typ = zbar_symbol_get_type(symbol);
//			zbar_get_symbol_name(typ);
		}

		/* clean up */
		zbar_image_destroy(image);
		zbar_image_scanner_destroy(scanner);
	}
	return results;
}

int main(int argc, char **argv)
{
#if 1
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
#else
	char const *path = "../helloworld.png";
//	char const *path = "../nyaan.png";

//	zbar_set_verbosity(300);
	QImage source;
	source.load(path);
	source = source.convertToFormat(QImage::Format_Grayscale8);

	scan(source, nullptr);
	return 0;
#endif
}
