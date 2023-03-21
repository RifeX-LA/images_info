#include <ui_mainwindow.h>
#include <QFileDialog>
#include <flow/image/image.hpp>
#include <flow/qwidgets/images_info.hpp>

namespace flow::qwigets {

    images_info::images_info(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
        ui->setupUi(this);
        setWindowTitle("Images Info");
        QObject::connect(ui->choose_directory_btn, SIGNAL(clicked(bool)), this, SLOT(btn_clicked_handler(bool)));
    }

    images_info::~images_info() {
        delete ui;
    }

    bool images_info::is_image_extenstion(const std::filesystem::path& extension) {
        return !extension.empty();
    }

    bool images_info::is_image(const std::filesystem::path& path) {
        return is_image_extenstion(path.extension());
    }

    void images_info::add_image_info(const std::filesystem::path& path) {
        auto table = ui->table;
        table->insertRow(table->rowCount());

        auto img = image::image_info(path);
        auto size = std::to_string(img.width) + "x" + std::to_string(img.height);
        auto resolution = std::to_string(img.res_x) + "x" + std::to_string(img.res_y);

        set_last(table, 0, img.filename);
        set_last(table, 1, img.extenstion);
        set_last(table, 2, size);
        set_last(table, 3, resolution);
        set_last(table, 4, img.depth);
        set_last(table, 5, img.compression);
    }

    void images_info::process_images(const std::filesystem::path& directory) {
        for (auto&& entry: std::filesystem::directory_iterator(directory)) {
            if (is_image(entry)) {
                add_image_info(entry);
            }
        }
    }

    void images_info::btn_clicked_handler(bool) {
        QString dir = QFileDialog::getExistingDirectory(this, "Open directory", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        ui->table->setRowCount(0);
        ui->derectory_le->setText(dir);
        process_images(dir.toStdString());
    }

} // namespace flow::qwigets
