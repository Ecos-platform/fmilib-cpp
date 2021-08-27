
#ifndef FMILIBCPP_FMU_FMU_HPP
#define FMILIBCPP_FMU_FMU_HPP

#include <fmilibcpp/model_description.hpp>
#include <fmilibcpp/slave.hpp>
#include <fmilibcpp/util/fs_portability.hpp>

#include <memory>

namespace fmilibcpp
{

class fmu
{

public:
    [[nodiscard]] virtual const model_description& get_model_description() const = 0;

    virtual std::unique_ptr<slave> new_instance(const std::string& instanceName) = 0;

    virtual ~fmu() = default;
};


std::unique_ptr<fmu> loadFmu(const filesystem::path& fmuPath);

} // namespace fmilibcpp

#endif //FMILIBCPP_FMU_FMU_HPP
