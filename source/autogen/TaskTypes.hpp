#pragma once

#include <cstdint>

// LJGAMCIMPMO in 22.9.2020
// FPDJEEJPHAH in 2020.10.8i
// CANPENMJFOD in 2020.10.22s
// KKNINLOPJHM in 2020.11.4s
// IGJKPGJPEFN in 2020.11.17s
// BOOMIBKNGPP in 2020.12.9s
// FHLMPHLKGCK in 2021.3.5s
// DMOAGPGAFKM in 2021.4.12s
enum class TaskTypes : std::int32_t {
    SubmitScan = 0, // [marker]
    PrimeShields = 1,
    FuelEngines = 2,
    ChartCourse = 3,
    StartReactor = 4,
    SwipeCard = 5,
    ClearAsteroids = 6,
    UploadData = 7,
    InspectSample = 8,
    EmptyChute = 9,
    EmptyGarbage = 10,
    AlignEngineOutput = 11,
    FixWiring = 12,
    CalibrateDistributor = 13,
    DivertPower = 14,
    UnlockManifolds = 15,
    ResetReactor = 16,
    FixLights = 17,
    CleanO2Filter = 18,
    FixComms = 19,
    RestoreOxy = 20,
    StabilizeSteering = 21,
    AssembleArtifact = 22,
    SortSamples = 23,
    MeasureWeather = 24,
    EnterIdCode = 25,
    BuyBeverage = 26,
    ProcessData = 27,
    RunDiagnostics = 28,
    WaterPlants = 29,
    MonitorOxygen = 30,
    StoreArtifacts = 31,
    FillCanisters = 32,
    ActivateWeatherNodes = 33,
    InsertKeys = 34,
    ResetSeismic = 35,
    ScanBoardingPass = 36,
    OpenWaterways = 37,
    ReplaceWaterJug = 38,
    RepairDrill = 39,
    AlignTelescope = 40,
    RecordTemperature = 41,
    RebootWifi = 42,
    PolishRuby = 43, // since 2021.3.5s
    ResetBreakers = 44, // since 2021.3.5s
    Decontaminate = 45, // since 2021.3.5s
    MakeBurger = 46, // since 2021.3.5s
    UnlockSafe = 47, // since 2021.3.5s
    SortRecords = 48, // since 2021.3.5s
    PutAwayPistols = 49, // since 2021.3.5s
    FixShower = 50, // since 2021.3.5s
    CleanToilet = 51, // since 2021.3.5s
    DressMannequin = 52, // since 2021.3.5s
    PickUpTowels = 53, // since 2021.3.5s
    RewindTapes = 54, // since 2021.3.5s
    StartFans = 55, // since 2021.3.5s
    DevelopPhotos = 56, // since 2021.3.5s
    GetBiggolSword = 57, // since 2021.3.5s
    PutAwayRifles = 58, // since 2021.3.5s
    StopCharles = 59, // since 2021.3.5s
};
