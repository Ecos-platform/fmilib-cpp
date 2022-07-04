
#ifndef FMILIBCPP_TEMP_DIR_HPP
#define FMILIBCPP_TEMP_DIR_HPP

#include "fixed_range_random_generator.hpp"

#include "fmilibcpp/util/fs_portability.hpp"

#include <iostream>
#include <memory>
#include <random>
#include <string>

namespace
{

std::string generate_simple_id(const int len)
{
    std::string id;
    fmilibcpp::fixed_range_random_generator rng(0, 9);
    for (auto i = 0; i < len; i++) {
        id += std::to_string(rng.next());
    }
    return id;
}

} // namespace

namespace fmilibcpp
{

class temp_dir
{
private:
    const filesystem::path path_;

public:
    explicit temp_dir(const std::string& name)
        : path_(filesystem::temp_directory_path() /= "proxy_fmu_" + name + "_" + generate_simple_id(6))
    {
        filesystem::create_directories(path_);
    }

    [[nodiscard]] filesystem::path path()
    {
        return path_;
    }

    ~temp_dir()
    {
        std::error_code status;
        filesystem::remove_all(path_, status);
        if (status) {
            std::cerr << "Failed to remove temp folder '" << path_.string() << "' " << status.message() << std::endl;
        }
    }
};

} // namespace fmilibcpp


#endif // FMILIBCPP_TEMP_DIR_HPP
