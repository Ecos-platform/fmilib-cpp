
#include <fmilibcpp/fmu.hpp>

#include <exception>
#include <iostream>

using namespace fmilibcpp;

void run()
{

    std::string fmuPath("../fmus/2.0/20sim/ControlledTemperature.fmu");
    auto fmu = loadFmu(fmuPath);

    auto md = fmu->get_model_description();
    std::cout << "GUID=" << md.guid << std::endl;
    std::cout << "description=" << md.description << std::endl;
    std::cout << "generationTool=" << md.generationTool << std::endl;

    auto mv = md.modelVariables;
    std::cout << mv.size() << std::endl;
    std::cout << mv[0].name << std::endl;

    for (auto& v : mv) {
        auto attr = v.typeAttributes;
        if (v.is_real()) {
            auto start = std::get<real_attributes>(attr).start;
            if (start) {
                std::cout << "start=" << std::get<real_attributes>(attr).start.value() << std::endl;
            }
        }
    }

    auto slaves = std::vector<std::unique_ptr<slave>>();
    for (auto i = 0; i < 10; i++) {
        auto slave = fmu->new_instance("instance_" + std::to_string(i));
        slave->setup_experiment();
        slave->enter_initialization_mode();
        slave->exit_initialization_mode();

        double t = 0;
        double dt = 0.1;
        for (int j = 0; j < 10; j++) {

            slave->step(t, dt);
            std::cout << slave->slave::get_real(md.get_by_name("Temperature_Room")->vr) << std::endl;

            t += dt;
        }

        slaves.push_back(std::move(slave));
    }

    for (auto& slave : slaves) {
        slave->terminate();
    }
}

int main()
{
    try {

        run();

    } catch (std::exception& ex) {
        std::cerr << "error: " << ex.what() << std::endl;
        return -1;
    }
    return 0;
}
