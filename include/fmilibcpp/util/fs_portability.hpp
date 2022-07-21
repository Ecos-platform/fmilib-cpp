
#ifndef FMILIBCPP_FS_PORTABILITY_HPP
#define FMILIBCPP_FS_PORTABILITY_HPP


#if __has_include(<filesystem>)
#    include <filesystem>
namespace fmilibcpp
{
namespace filesystem = std::filesystem;
}
#else
#    include <experimental/filesystem>
namespace fmilibcpp
{
namespace filesystem = std::experimental::filesystem;
}
#endif

#endif // FMILIBCPP_FS_PORTABILITY_HPP
