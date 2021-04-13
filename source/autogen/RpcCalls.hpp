#pragma once

#include <cstdint>

// FPHOMIDIMBN in 2020.9.22
// JHNKMAGPAEP in 2020.10.8i
// FOBFDOIGNKE in 2020.10.22s
// GODNMPFGJHC in 2020.11.4s
// FBGKAFLCOBO in 2020.11.17s
// KPLHBGFHGBI in 2020.12.9s
// OGHLFADACAG in 2021.3.5s
// GLEJPDNDION in 2021.4.12s
enum class RpcCalls : std::uint8_t {
    PlayAnimation = 0, // [marker]
    CompleteTask = 1,
    SyncSettings = 2,
    SetInfected = 3,
    Exiled = 4,
    CheckName = 5,
    SetName = 6,
    CheckColor = 7,
    SetColor = 8,
    SetHat = 9,
    SetSkin = 10,
    ReportDeadBody = 11,
    MurderPlayer = 12,
    SendChat = 13,
    StartMeeting = 14,
    SetScanner = 15,
    SendChatNote = 16,
    SetPet = 17,
    SetStartCounter = 18,
    EnterVent = 19,
    ExitVent = 20,
    SnapTo = 21,
    CloseMeeting = 22, // renamed in 2021.3.5s
    VotingComplete = 23,
    CastVote = 24,
    ClearVote = 25,
    AddVote = 26,
    CloseDoorsOfType = 27,
    RepairSystem = 28,
    SetTasks = 29,
    // UpdateGameData = 30, // until 2021.4.12s
    ClimbLadder = 31, // since 2021.3.5s
    UsePlatform = 32, // since 2021.3.5s
};
