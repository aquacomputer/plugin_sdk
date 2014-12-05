﻿//*****************************************************************************
//* Name:
//*   struct GuiState 
//* Description:
//*   only for internal handling
//*****************************************************************************
struct GuiState {
   uint8_t buffer[20];   
};

//*****************************************************************************
//* Name:
//*   SystemLockControl
//* Description:
//*   only for internal handling
//*****************************************************************************
typedef union {
   uint16_t data;   
} SystemLockControl;

//*****************************************************************************
//* Name:
//*   DeviceType_t
//* Description:
//*   connected device type
//*****************************************************************************
typedef uint8_t DeviceType_t;
   #define AQUAERO5_LT              0
   #define AQUAERO5_PRO             1
   #define AQUAERO5_XT              2
   #define AQUADUCT_MK4_361         3
   #define AQUADUCT_MK4_360         4
   #define AQUADUCT_MK4_720         5 
   #define AQUADUCT_MK5_360         6
   #define AQUADUCT_MK5_720         7 

//*****************************************************************************
//* Name:
//*   DeviceCapabilities
//* Description:
//*   device capabilities, available hardware features
//*****************************************************************************
typedef union {
   uint16_t data;
   struct {
      uint16_t HasDisplay :1;
      uint16_t HasKeys :1;
      uint16_t HasTouch :1;
      uint16_t HasIrReciver :1;
   } Bits;
} DeviceCapabilities;

//*****************************************************************************
//* Name:
//*     DeviceInfo
//* Description:
//*     device informations
//*****************************************************************************
typedef struct 
{
   uint16_t serial[2];              //serial number - 2x 16 bit value
   uint16_t firmware;               //firmware version
   uint16_t bootloader;             //bootloader id
   uint16_t hardware;               //hardware id
   uint32_t uptime;                 //uptime poweron -> now
   uint32_t uptimeTotal;            //uptime total
   DeviceStatus status;             //iunt8_t, supply state
   SystemLockControl lockControl;   //uint16_t, gerätesperren verwalten
   DeviceType_t deviceType;
   DeviceCapabilities capabilities;
}tDeviceInfo;

//*****************************************************************************
//* Name:
//*   AlarmLevel_t
//* Description:
//*   Alarm priority, 0..3
//*   0 = normal, 1..3 alarm state
//*****************************************************************************
typedef uint8_t AlarmLevel_t;
   #define ALARM_LEVEL_NORMAL       0
   #define ALARM_LEVEL_WARN         1
   #define ALARM_LEVEL_ALARM        2
   #define ALARM_LEVEL_X            3

   //*****************************************************************************
//* Name:
//*   AquabusStatus
//* Description:
//*   connected aquabus devices
//*****************************************************************************
typedef union {
   uint32_t data;
   struct {
      uint32_t aquastream1 :1;   //0x0001
      uint32_t aquastream2 :1;   //0x0002
      
      uint32_t poweradjust1 :1;  //0x0004
      uint32_t poweradjust2 :1;  //0x0008
      uint32_t poweradjust3 :1;  //0x0010
      uint32_t poweradjust4 :1;  //0x0020
      uint32_t poweradjust5 :1;  //0x0040
      uint32_t poweradjust6 :1;  //0x0080
      uint32_t poweradjust7 :1;  //0x0100
      uint32_t poweradjust8 :1;  //0x0200
      
      uint32_t mps1 :1;          //0x0400
      uint32_t mps2 :1;          //0x0800
      uint32_t mps3 :1;          //0x1000
      uint32_t mps4 :1;          //0x2000
      
      uint32_t rtc :1;           //0x4000
      uint32_t aquaero5slave :1; //0x8000  
      
      uint32_t farbwerk1 :1;     //0x10000
      uint32_t farbwerk2 :1;     //0x20000
      
   } Bits;
} AquabusStatus;

//*****************************************************************************
//* Name:
//*   PowerConsumptionData
//* Description:
//*  read out data from power consumption
//*****************************************************************************
typedef struct
{
   int16_t flow;                 //flow
   int16_t sensor1;              //sensor 1
   int16_t sensor2;              //sensor 2
   int16_t detaT;                //absolute delta temperature between s1 und s2
   int16_t power;                //calculated power consumption
   int16_t rth;                  //thermal resistance
}tPowerConsumptionData;

//*****************************************************************************
//* Name:
//*   FanData
//* Description:
//*   current fan data
//*****************************************************************************
typedef struct 
{
   int16_t rpm;                     //fan rpm
   int16_t power;                   //fan power in %
   int16_t voltage;                 //fan voltage
   int16_t current;                 //fan current
   int16_t performance;				//power consumption in W
   int16_t torque;					//torque in Nm
}tFanData;

//*****************************************************************************
//* Name:
//*   AquastreamMode_t
//* Description:
//*   pump mode
//*****************************************************************************
typedef uint8_t tAquastreamMode;
#define AQUASTREAM_AUTOFREQ            0     //automatic speed setup (force maximum)
#define AQUASTREAM_MANUALFREQ          1     //manual speed preset
#define AQUASTREAM_DATA_SOURCE         2     //contolled from controller
#define AQUASTREAM_LEVELSENS           3     //only for aquaduct internal state
#define AQUASTREAM_OFFLINE             255   //not connected

//*****************************************************************************
//* Name:
//*   AquastreamStatus
//* Description:
//*   pump state
//*****************************************************************************
typedef union {
   uint8_t data;
   struct {
      uint8_t available :1;  //pump is connected
      uint8_t alarm :1;      //is alarm active
   } Bits;
} tAquastreamStatus;

//*****************************************************************************
//* Name:
//*   tPumpData
//* Description:
//*   Aquastream Daten
//*****************************************************************************
typedef struct 
{
   tAquastreamStatus status;     //pump state
   tAquastreamMode mode;         //pump mode
   int16_t rpm;                  //pump speed in rpm
   int16_t voltage;              //pump voltage in 1/10V
   int16_t current;              //pump current in mA
}tPumpData;

//*****************************************************************************
//* Name:
//*   OutData
//* Description:
//*   device data
//*****************************************************************************
struct OutData 
{
   uint8_t reportId;                //usb report id
   uint32_t timestamp;              //curretn UTC device datetime in 32bit unix format sek ab zeitpunkt x.
   uint16_t stuctureVersion;        //structure id (data lyout version)
   
   tDeviceInfo devInfo;             //device info (serial...)
   uint32_t lastSettingsUpdateTime; //last settings change
   
   struct GuiState lcdstate;        //device gui state (20bytes)
   AlarmLevel_t alarmlevel;         //current alarm level
   uint8_t actualProfile;           //current profile
   AquabusStatus aquabus;           //aquabus devices

   uint16_t adcRAW[20];             //adc raw values range:0..0xffff
   int16_t temperatures[64];        //64 temperaturesensoren, invalid: 0x7fff
   uint32_t rawRpmFlow[5];          //impulse rpm times in 1/100ms == 0.01e10-3s 
   int16_t flow[14];                //2xinternal flow + 8xpoweradjust + 4xmps flow
   tPowerConsumptionData powerConsumption[4];   //power consumption data
   int16_t level[4];                //fill level sensors
   int16_t humidity[4];             //humidity sensor data (not available yet)
   int16_t conductivity[4];         //water quality (aquaduct only)
   int16_t pressure[4];             //pressure sensors (mps)
   
   int16_t tacho;                   //rpm output
   tFanData fans[FAN_COUNT];        //fan data
   tPumpData aquastream[8];         //pump data
   uint32_t output_available[2];    //output states, 64bits == outputs[64]
   int16_t outputs[64];             //output values  
      #define OUTPUT_LED_R       0  //index of outputs
      #define OUTPUT_LED_G       1
      #define OUTPUT_LED_B       2
      #define OUTPUT_RELAY       3
      #define OUTPUT_POWER1      4
      #define OUTPUT_POWER2      5
      #define OUTPUT_FARBWERK    6   
      #define OUTPUT_AQUASTREAM  30
      #define OUTPUT_MPS         32
   
   //controller outputs, scaled from 0..100% [0...10000]
   int16_t twopoint[16];            //2controller outputs
   int16_t constData[32];           //constant preset outputs
   int16_t rgbLed[12];              //rgb controller outputs
   int16_t setPoint[8];             //setpoint controller
   int16_t curve[4];                //curve controller
   .
   .
   .
};