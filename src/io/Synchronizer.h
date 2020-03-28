#pragma once
#include <string>
#include "Time.h"
namespace raydelto
{

class Synchronizer
{
    public:
        void Process(std::string sourcePath, std::string destinationPath, Time variation);
};
} // namespace raydelto
