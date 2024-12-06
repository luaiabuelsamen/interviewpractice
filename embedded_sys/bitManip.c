// Sensor state tracking using bitfields
typedef struct {
    unsigned int is_powered : 1;      // Power state
    unsigned int is_calibrated : 1;   // Calibration status
    unsigned int error_code : 4;      // Error tracking (0-15 range)
    unsigned int mode : 2;            // Operating mode
    unsigned int data_ready : 1;      // Data availability flag
    unsigned int reserved : 23;       // Future expansion
} SensorStatus;

// Possible operating modes
typedef enum {
    LOW_POWER = 0,
    NORMAL = 1,
    HIGH_PRECISION = 2,
    DIAGNOSTIC = 3
} SensorMode;

// Error codes
typedef enum {
    NO_ERROR = 0,
    TEMP_RANGE_ERROR = 1,
    CALIBRATION_FAIL = 2,
    COMMUNICATION_ERROR = 3,
    POWER_ERROR = 4
} SensorErrorCode;

// Function prototypes
void initSensor(SensorStatus* status){
    status->is_powered = 0;
    status->is_calibrated = 1; 
    status->error_code = NO_ERROR;
    status-> mode = LOW_POWER;
    status->data_ready = 0;
    status->reserved = 0;
}

int setSensorMode(SensorStatus* status, SensorMode mode){
    switch (status->mode)
    {
    case LOW_POWER:
        if(status->is_powered){
            status->mode = NORMAL;
        }
        break;
    
    default:
        break;
    }

}

int reportError(SensorStatus* status, SensorErrorCode error){
    status->error_code = error; 
    status->mode = DIAGNOSTIC;
}

int clearError(SensorStatus* status){
    status->mode = NORMAL;
}

int powerOnSensor(SensorStatus* status){
    status->is_powered = 1;
}

int powerOffSensor(SensorStatus* status){
    status->is_powered = 0;
}