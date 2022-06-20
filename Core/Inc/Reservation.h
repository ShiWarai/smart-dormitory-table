#pragma once

#include <string>

struct Reservation
{
    long objectId;
    long residentId;
    std::string reason;
    std::string startReservation;
    std::string endReservation;
};