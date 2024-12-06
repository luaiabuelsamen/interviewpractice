#define MAX_READINGS 10

// Temperature structure to store readings
typedef struct {
    float temperature;
    unsigned long timestamp;
} SensorReading;

// Circular buffer structure
typedef struct {
    SensorReading readings[MAX_READINGS];
    int head;           // Points to the next insertion point
    int tail;           // Points to the oldest data point
    int current_count;  // Number of current items in buffer
    float sum;
    float maxTemp;
} TemperatureRingBuffer;

// Function prototypes
void initBuffer(TemperatureRingBuffer* buffer);
int addReading(TemperatureRingBuffer* buffer, float temp, unsigned long timestamp);
float getAverageTemperature(TemperatureRingBuffer* buffer);
float getMaxTemperature(TemperatureRingBuffer* buffer);
int getNumReadings(TemperatureRingBuffer* buffer);

void initBuffer(TemperatureRingBuffer* buffer){
    buffer->head = 0;
    buffer->tail = 0;
    buffer->current_count = 0;
}

int addReading(TemperatureRingBuffer* buffer, float temp, unsigned long timestamp){
    SensorReading newReading = {temp, timestamp};
    buffer->sum += -buffer->readings[buffer->tail].temperature + temp;
    buffer->readings[buffer->tail] = newReading;
    buffer->tail = (buffer->tail + 1) % MAX_READINGS;
    if (buffer->current_count < MAX_READINGS){
        buffer->current_count++;
    } 
    if (temp > buffer->maxTemp){
        buffer->maxTemp = temp;
    }
    return  buffer->current_count;
}


float getAverageTemperature(TemperatureRingBuffer* buffer){
    return buffer->sum/buffer->current_count;
}

float getMaxTemperature(TemperatureRingBuffer* buffer){
    return buffer->maxTemp;
}

int getNumReadings(TemperatureRingBuffer* buffer){
    return buffer->current_count;
}