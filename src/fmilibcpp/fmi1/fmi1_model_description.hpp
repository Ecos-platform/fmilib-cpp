
#ifndef FMILIBCPP_FMI1_MODEL_DESCRIPTION_HPP
#define FMILIBCPP_FMI1_MODEL_DESCRIPTION_HPP

#include <fmilib.h>
#include <fmilibcpp/model_description.hpp>

namespace fmilibcpp
{

model_description create_model_description(fmi1_import_t* handle);

} // namespace fmilibcpp

#endif //FMILIBCPP_FMI1_MODEL_DESCRIPTION_HPP
