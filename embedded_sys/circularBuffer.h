#define CIRCULAR_BUF_SIZE 5

typedef struct sCircularBuffer{
    int buf[CIRCULAR_BUF_SIZE];
    int isFull;
    int isEmpty;
    int head;
    int tail;
} sCircularBuffer;

typedef enum {
    BUF_ADD_OK = 0,
    BUF_READ_OK = 1,
    BUF_ADD_FAILED = 2,
    BUF_READ_FAILED = 3
} eBUF_ACTION_STATUS;


void initBuffer();
eBUF_ACTION_STATUS addElement(int num);
eBUF_ACTION_STATUS readElement(int *num);
void printBuffer();

static sCircularBuffer buffer;