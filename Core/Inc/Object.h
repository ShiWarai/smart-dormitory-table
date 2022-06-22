#pragma once

#include <string>
#include <vector>

struct Object
{
    long id;
    std::string name;
    long type_id;
    long status_id;

    bool available;
    std::vector<long> user_reservations;
};