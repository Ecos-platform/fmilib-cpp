
#ifndef FMILIBCPP_MODEL_DESCRIPTION_HPP
#define FMILIBCPP_MODEL_DESCRIPTION_HPP

#include <fmilibcpp/scalar_variable.hpp>

#include <optional>
#include <vector>

namespace fmilibcpp
{

struct default_experiment
{
    double startTime;
    double stopTime;
    double tolerance;
    double stepSize;
};

struct model_description
{
    std::string guid;
    std::string author;
    std::string modelName;
    std::string modelIdentifier;
    std::string fmiVersion;
    std::string description;
    std::string generationTool;
    std::string generationDateAndTime;

    model_variables modelVariables;
    default_experiment defaultExperiment;
};

} // namespace fmilibcpp

#endif //FMILIBCPP_MODEL_DESCRIPTION_HPP
