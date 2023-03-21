#include <QApplication>
#include <flow/qwidgets/images_info.hpp>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    flow::qwigets::images_info images_info;
    images_info.show();

    return a.exec();
}
