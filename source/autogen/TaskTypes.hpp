#pragma once

#include <cstdint>

// LJGAMCIMPMO in 22.9.2020
// FPDJEEJPHAH in 2020.10.8i
// CANPENMJFOD in 2020.10.22s
// KKNINLOPJHM in 2020.11.4s
// IGJKPGJPEFN in 2020.11.17s
// BOOMIBKNGPP in 2020.12.9s
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
};
