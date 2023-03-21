#pragma once

#include <string>
#include <filesystem>
#include <boost/lexical_cast.hpp>
#include <QMainWindow>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace flow::qwigets {

    class images_info : public QMainWindow {
        Q_OBJECT

    public:
        images_info(QWidget *parent = nullptr);
        ~images_info();

        template <typename T>
        void set_last(QTableWidget* table, std::size_t column, const T& value) {
            auto* item = new QTableWidgetItem(boost::lexical_cast<std::string>(value).c_str());
            item->setTextAlignment(Qt::AlignCenter);
            table->setItem(table->rowCount() - 1, column, item);
        }

        static bool is_image_extenstion(const std::filesystem::path& extension);
        static bool is_image(const std::filesystem::path& path);
        void add_image_info(const std::filesystem::path& path);
        void process_images(const std::filesystem::path& directory);

    public slots:
        void btn_clicked_handler(bool);

    private:
        Ui::MainWindow* ui;
    };

} // namespace flow::qwigets
