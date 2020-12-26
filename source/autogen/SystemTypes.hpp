#pragma once

#include <cstdint>

// HBKFJKIHEFM in 2020.9.22
// NAKOBFDMIMP in 2020.10.8i
// JBPEMAACAEP in 2020.10.22s
// PECPIEDFOHP in 2020.11.4s
// AOKAHIJINGJ in 2020.11.17s
// LJFDDJHBOGF in 2020.12.9s
enum class SystemTypes : std::uint8_t {
    Hallway = 0, // [marker]
    Storage = 1,
    Cafeteria = 2,
    Reactor = 3,
    UpperEngine = 4,
    Nav = 5,
    Admin = 6,
    Electrical = 7,
    LifeSupp = 8,
    Shields = 9,
    MedBay = 10,
    Security = 11,
    Weapons = 12,
    LowerEngine = 13,
    Comms = 14,
    ShipTasks = 15,
    Doors = 16,
    Sabotage = 17,
    Decontamination = 18,
    Launchpad = 19,
    LockerRoom = 20,
    Laboratory = 21,
    Balcony = 22,
    Office = 23,
    Greenhouse = 24,
    Dropship = 25,
    Decontamination2 = 26,
    Outside = 27,
    Specimens = 28,
    BoilerRoom = 29,
};
