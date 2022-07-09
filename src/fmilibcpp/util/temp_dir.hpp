
#ifndef FMILIBCPP_TEMP_DIR_HPP
#define FMILIBCPP_TEMP_DIR_HPP

#include "uuid.hpp"

#include "fmilibcpp/util/fs_portability.hpp"

#include <iostream>
#include <string>

namespace fmilibcpp
{

class temp_dir
{
private:
    const filesystem::path path_;

public:
    explicit temp_dir(const std::string& name)
        : path_(filesystem::temp_directory_path() /= "fmilibcpp_" + name + "_" + generate_uuid())
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
            std::cerr << "Failed to remove temp folder '" << path_.string() << "': " << status.message() << std::endl;
        }
    }
};

} // namespace fmilibcpp


#endif // FMILIBCPP_TEMP_DIR_HPP
