/**
 *
 * @file interrupts.cpp
 * @author Sasisekhar Govind
 *
 */

#include<interrupts.hpp>

int main(int argc, char** argv) {

    //vectors is a C++ std::vector of strings that contain the address of the ISR
    //delays  is a C++ std::vector of ints that contain the delays of each device
    //the index of these elemens is the device number, starting from 0
    auto [vectors, delays] = parse_args(argc, argv);
    std::ifstream input_file(argv[1]);

    std::string trace;      //!< string to store single line of trace file
    std::string execution;  //!< string to accumulate the execution output

    /******************ADD YOUR VARIABLES HERE*************************/

    int current_time = 0;
    execution = "";

    /******************************************************************/

    //parse each line of the input trace file
    while(std::getline(input_file, trace)) {
        auto [activity, duration_intr] = parse_trace(trace);

        /******************ADD YOUR SIMULATION CODE HERE*************************/
            //parse each line of the input trace file
    while(std::getline(input_file, trace)) {
        auto [activity, duration_intr] = parse_trace(trace);

        if (activity == "CPU") {
            execution += std::to_string(current_time) + ", " + std::to_string(duration_intr) + ", CPU\n";
            current_time += duration_intr;
        }
        else if (activity == "SYSCALL") {
            int intr_num = duration_intr;

            auto [intr_execution, updated_time] = intr_boilerplate(current_time, intr_num, 10, vectors);
            execution += intr_execution;
            current_time = updated_time;

            int isr_duration = delays[intr_num];
            execution += std::to_string(current_time) + ", " + std::to_string(isr_duration) + ", execute ISR\n";
            current_time += isr_duration;

            execution += std::to_string(current_time) + ", " + std::to_string(1) + ", IRET\n";
            current_time += 1;

            execution += std::to_string(current_time) + ", " + std::to_string(1) + ", switch to user mode\n";
            current_time += 1;
        }
        else if (activity == "END_IO") {
            // Optional: log IO completion
            execution += std::to_string(current_time) + ", " + std::to_string(duration_intr) + ", END_IO\n";
            current_time += duration_intr;
        }
    }
        /************************************************************************/

    }

    input_file.close();

    write_output(execution);

    return 0;
}
