#pragma once

#include <string>

struct Reservation
{
    long id;
    long objectId;
    long residentId;
    std::string reason;
    std::string startReservation;
    std::string endReservation;
};