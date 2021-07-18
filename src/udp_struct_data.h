#include "stdint.h"
#include "inttypes.h"
#pragma pack(push)
#pragma pack(1)
struct PacketHeader
{
    uint16_t    m_packetFormat;             // 2020
    uint8_t    m_gameMajorVersion;         // Game major version - "X.00"
    uint8_t     m_gameMinorVersion;         // Game minor version - "1.XX"
    uint8_t     m_packetVersion;            // Version of this packet type, all start from 1
    uint8_t     m_packetId;                 // Identifier for the packet type, see below
    uint64_t    m_sessionUID;               // Unique identifier for the session
    float     m_sessionTime;              // Session timestamp
    uint32_t    m_frameIdentifier;          // Identifier for the frame the data was retrieved on
    uint8_t     m_playerCarIndex;           // Index of player's car in the array
    
   // ADDED IN BETA 2: 
    uint8_t     m_secondaryPlayerCarIndex;  // Index of secondary player's car in the array (splitscreen)
                                          // 255 if no second player
};

struct CarTelemetryData
{
    uint16_t    m_speed;                         // Speed of car in kilometres per hour
    float     m_throttle;                      // Amount of throttle applied (0.0 to 1.0)
    float     m_steer;                         // Steering (-1.0 (full lock left) to 1.0 (full lock right))
    float     m_brake;                         // Amount of brake applied (0.0 to 1.0)
    uint8_t    m_clutch;                        // Amount of clutch applied (0 to 100)
    int8_t      m_gear;                          // Gear selected (1-8, N=0, R=-1)
    uint16_t    m_engineRPM;                     // Engine RPM
    uint8_t     m_drs;                           // 0 = off, 1 = on
    uint8_t     m_revLightsPercent;              // Rev lights indicator (percentage)
    uint16_t    m_brakesTemperature[4];          // Brakes temperature (celsius)
    uint8_t     m_tyresSurfaceTemperature[4];    // Tyres surface temperature (celsius)
    uint8_t     m_tyresInnerTemperature[4];      // Tyres inner temperature (celsius)
    uint16_t    m_engineTemperature;             // Engine temperature (celsius)
    float     m_tyresPressure[4];              // Tyres pressure (PSI)
    uint8_t     m_surfaceType[4];                // Driving surface, see appendices
};

struct PacketCarTelemetryData
{
    struct PacketHeader  m_header;	       // Header

    struct CarTelemetryData    m_carTelemetryData[22];

    uint32_t              m_buttonStatus;        // Bit flags specifying which buttons are being pressed
                                               // currently - see appendices

    // Added in Beta 3:
    uint8_t               m_mfdPanelIndex;       // Index of MFD panel open - 255 = MFD closed
                                               // Single player, race – 0 = Car setup, 1 = Pits
                                               // 2 = Damage, 3 =  Engine, 4 = Temperatures
                                               // May vary depending on game mode
    uint8_t               m_mfdPanelIndexSecondaryPlayer;   // See above
    int8_t                m_suggestedGear;       // Suggested gear for the player (1-8)
                                               // 0 if no gear suggested
};
/*
struct CarStatusData
{
    uint8_t      m_tractionControl;          // 0 (off) - 2 (high)
    uint8_t       m_antiLockBrakes;           // 0 (off) - 1 (on)
    uint8_t       m_fuelMix;                  // Fuel mix - 0 = lean, 1 = standard, 2 = rich, 3 = max
    uint8_t       m_frontBrakeBias;           // Front brake bias (percentage)
    uint8_t       m_pitLimiterStatus;         // Pit limiter status - 0 = off, 1 = on
    float       m_fuelInTank;               // Current fuel mass
    float       m_fuelCapacity;             // Fuel capacity
    float       m_fuelRemainingLaps;        // Fuel remaining in terms of laps (value on MFD)
    uint16_t      m_maxRPM;                   // Cars max RPM, point of rev limiter
    uint16_t      m_idleRPM;                  // Cars idle RPM
    uint8_t       m_maxGears;                 // Maximum number of gears
    uint8_t       m_drsAllowed;               // 0 = not allowed, 1 = allowed, -1 = unknown
    

    // Added in Beta3:
    uint16_t      m_drsActivationDistance;    // 0 = DRS not available, non-zero - DRS will be available
                                            // in [X] metres
    
    uint8_t       m_tyresWear[4];             // Tyre wear percentage
    uint8_t       m_actualTyreCompound;	    // F1 Modern - 16 = C5, 17 = C4, 18 = C3, 19 = C2, 20 = C1
   					    // 7 = inter, 8 = wet
   					    // F1 Classic - 9 = dry, 10 = wet
   					    // F2 – 11 = super soft, 12 = soft, 13 = medium, 14 = hard
   					    // 15 = wet
   uint8_t       m_visualTyreCompound;        // F1 visual (can be different from actual compound)
                                            // 16 = soft, 17 = medium, 18 = hard, 7 = inter, 8 = wet
                                            // F1 Classic – same as above
                                            // F2 – same as above
    uint8_t       m_tyresAgeLaps;             // Age in laps of the current set of tyres
    uint8_t       m_tyresDamage[4];           // Tyre damage (percentage)
    uint8_t       m_frontLeftWingDamage;      // Front left wing damage (percentage)
    uint8_t       m_frontRightWingDamage;     // Front right wing damage (percentage)
    uint8_t       m_rearWingDamage;           // Rear wing damage (percentage)
    
    // Added Beta 3:
    uint8_t       m_drsFault;                 // Indicator for DRS fault, 0 = OK, 1 = fault
    
    uint8_t       m_engineDamage;             // Engine damage (percentage)
    uint8_t       m_gearBoxDamage;            // Gear box damage (percentage)
    int8_t        m_vehicleFiaFlags;          // -1 = invalid/unknown, 0 = none, 1 = green
                                            // 2 = blue, 3 = yellow, 4 = red
    float       m_ersStoreEnergy;           // ERS energy store in Joules
    uint8_t       m_ersDeployMode;            // ERS deployment mode, 0 = none, 1 = medium
                                            // 2 = overtake, 3 = hotlap
    float       m_ersHarvestedThisLapMGUK;  // ERS energy harvested this lap by MGU-K
    float       m_ersHarvestedThisLapMGUH;  // ERS energy harvested this lap by MGU-H
    float       m_ersDeployedThisLap;       // ERS energy deployed this lap
};
*/
#pragma pack(pop)