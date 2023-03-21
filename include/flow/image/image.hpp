#pragma once

#include <string_view>
#include <filesystem>
#include <QImageReader>

namespace flow::image {

    struct image_t {
        std::string filename;
        std::string extenstion;
        int width;
        int height;
        int res_x;
        int res_y;
        int depth;
        int compression;
    };

    constexpr int dpm2dpi(int dpm) noexcept {
        return std::round(dpm / 39.37);
    }

    inline image_t image_info(const std::filesystem::path& path) {
        QImage img(path.c_str());
        QImageReader img_reader(path.c_str());
        std::pair dpi(dpm2dpi(img.dotsPerMeterX()), dpm2dpi(img.dotsPerMeterY()));

        return {path.filename().stem(), path.extension(), img.width(), img.height(), dpi.first, dpi.second, img.depth(), img_reader.quality()};
    }

} // namespace flow::image
