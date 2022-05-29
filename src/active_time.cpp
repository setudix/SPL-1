#include "../include/active_time.h"

SPL::Time pcOnDuration;

namespace SPL
{
    void setPcOnDuration()
    {
        std::fstream file;
        std::string filename =  SPL::runCommand("pwd", "r") + "/logs/pcOnDuration/" + SPL::runCommand(SPL::Util::getDateIn_YYYY_DD_MM(),"r") + ".dat";

        file.open(filename, std::ios::in);

        if (file.is_open())
        {
            long long time; 
            file >> time;

            pcOnDuration.setTime(time);
            file.close();
        }
        else 
            pcOnDuration.setTime(0);
    }

    void writePcOnDuration()
    {
        std::fstream file;
        std::string filename =  SPL::runCommand("pwd", "r") + "/logs/pcOnDuration/" + SPL::runCommand(SPL::Util::getDateIn_YYYY_DD_MM(),"r") + ".dat";

        file.open(filename, std::ios::out);

        if (file.is_open())
        {
            file << pcOnDuration.getTimeInSeconds();
            file.close();
        }
    }
    void calculatePcOnTime()
    {
        SPL::Time tempTime;

        setPcOnDuration();

        while (1)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            tempTime.setTime(5);
            pcOnDuration = pcOnDuration + tempTime;
            writePcOnDuration();
        }
    }
}