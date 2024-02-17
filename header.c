#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

//Flags used for Passthru connect
#define J2534_CONNECT_FLAG_CAN_29BIT_ID_BIT 0x00000080
#define J2534_CONNECT_ISO15765_ADDR_TYPE_BIT 0x00000100

//flags used for Passthru write msg
#define J2534_TxFlag_FLAG_CAN_29BIT_ID_BIT 0x00000080
#define J2534_TxFlag_ISO15765_ADDR_TYPE_BIT 0x00000100
#define J2534_TxFlag_ISO15765_Flow_Control_TYPE_BIT 0x00000100

//flags used for Passthru read msg
#define J2534_RxFlag_FLAG_CAN_29BIT_ID_BIT 0x00000080
#define J2534_RxFlag_ISO15765_ADDR_TYPE_BIT 0x00000100

//I
#define CAN_29BIT_ID_BIT 0x00000080
#define CAN_11BIT_ID_BIT 0x00000080
#define STD_ADDR_TYPE_BIT 0x00000100
#define EXTENDED_ADDR_TYPE_BIT 0x00000100




#define FIRMWAREVERSION "APCAN2X_JF1.1.0"
#define DLLVERSION "APCAN2X_JD1.1.0"
#define APIVERSION "APCAN2X_JA1.1.0"

#define FILTER_TYPE_PASS_FILTER     0x00000001
#define FILTER_TYPE_BLOCK_FILTER	0x00000002
#define FILTER_TYPE_FLOWCTRL_FILTER 0x00000003


typedef unsigned long J2534_ERROR;
typedef unsigned long J2534_CANID_TYPE;
typedef unsigned long J2534_CAN_ADDRESSING_TYPE;





typedef struct {
unsigned long ProtocolID; /* vehicle network protocol */
unsigned long RxStatus; /* receive message status */
unsigned long TxFlags; /* transmit message flags */
unsigned long Timestamp; /* receive message timestamp(in microseconds) */
unsigned long DataSize; /* byte size of message payload in the Data array */
unsigned long ExtraDataIndex; /* start of extra data(i.e. CRC, checksum, etc) in Data array */
unsigned char Data[4128]; /* message payload or data */
} PASSTHRU_MSG;


typedef struct {
unsigned long Parameter; /* Name of configuration parameter */
unsigned long Value; /* Value of configuration parameter */
} SCONFIG;

typedef struct {
unsigned long NumOfParams; /* sizeof SCONFIG array */
SCONFIG *ConfigPtr; /* array containing configuration item(s) */
} SCONFIG_LIST;

typedef struct {
unsigned long NumOfBytes; /* Number of ECU target addresses in array */
unsigned char *BytePtr; /* Pointer to ECU target address array */
} SBYTE_ARRAY;


typedef enum J2534_GET_SET_PARAMETERS
{
	DATA_RATE = 0x01,		// all protocols  ------------------ 5 - 500000		----------------------- Baud Rate of communication
	LOOPBACK = 0x03,		// all protocols ------------------- 0 - off, 1 - on----------------------- Tx message echo
	NODE_ADDRESS = 0x04, 	// J1850PWM specific --------------- 0x00 - 0xff	------------------------ Rx ID of ecu
	NETWORK_LINE = 0x05, 	// J1850PWM specific --------------- 0x00 BUS_NORMAL, 0x01 - BUS_PLUS, 0x02 - BUS_MINUS ; j1850 specific
	P1_MIN= 0x06,			// ISO9141 specific ---------------- 0x00 to 0xFFFF ------------------------ minimum ECU inter-byte time (in milliseconds) for responses. Default is 0 ms
	P1_MAX= 0x07,			//ISO9141 specific ---------------- 0x00 to 0xFFFF ------------------------ maximum ECU inter-byte time (in milliseconds) for responses. Default is 20 ms
	P2_MIN= 0x08,			//ISO9141 specific ---------------- 0x00 to 0xFFFF ------------------------ minimum ECU response time (in milliseconds) to a tester request or between ECU responses. Default 25 ms
	P2_MAX= 0x09,			//ISO9141 specific ---------------- 0x00 to 0xFFFF ------------------------ maximum ECU response time (in milliseconds) to a tester request or between ECU responses. max is 50 ms
	P3_MIN= 0x0a,			//ISO9141 specific ---------------- 0x00 to 0xFFFF ------------------------ minimum ECU response time (in milliseconds) between end of ECU response and next tester request. Default 55 ms
	P3_MAX= 0x0b,			//ISO9141 specific ---------------- 0x00 to 0xFFFF ------------------------ maximum ECU response time (in milliseconds) between end of ECU response and next tester request. Default 5000 ms
	P4_MIN= 0x0c,			//ISO9141 specific ---------------- 0x00 to 0xFFFF ------------------------ minimum tester inter-byte time (in milliseconds) for a request. default is 5 ms
	P4_MAX= 0x0d,			//ISO9141 specific ---------------- 0x00 to 0xFFFF ------------------------ maximum tester inter-byte time (in milliseconds) for a request. default is 20 ms
	W1= 0x0e,			//ISO9141 specific ---------------- 0x00 to 0xFFFF ------------------------ maximum time(in milliseconds) from the address byte end to synchronization pattern start. Default value is 300 milliseconds.
	W2= 0x0f,			//ISO9141 specific ---------------- 0x00 to 0xFFFF ------------------------ maximum time(in milliseconds) from the synchronization byte end to key byte 1 start. Default value is 20 milliseconds.
	W3= 0x10,			//ISO9141 specific ---------------- 0x00 to 0xFFFF ------------------------ maximum time(in milliseconds) between key byte 1 and key byte 2. Default value is 20 milliseconds.
	W4= 0x11,			//ISO9141 specific ---------------- 0x00 to 0xFFFF ------------------------ maximum time(in milliseconds) between key byte 2 and its inversion from the tester. Default value is 50 milliseconds.
	W5= 0x12,			//ISO9141 specific ---------------- 0x00 to 0xFFFF ------------------------ minimum time(in milliseconds) before the tester begins retransmission of the address byte. Default value is 300 milliseconds.
	TIDLE= 0x13,		//ISO9141 specific ---------------- 0x00 to 0xFFFF ------------------------ bus idle time required before starting a fast initialization sequence. Default value is W5 value
	TINL= 0x14,			//ISO9141 specific ---------------- 0x00 to 0xFFFF ------------------------ the duration(in milliseconds) of the fast initialization low pulse. Default value is 25 milliseconds
	TWUP= 0x15,			//ISO9141 specific ---------------- 0x00 to 0xFFFF ------------------------ the duration(in milliseconds) of the fast initialization wake-up pulse. Default value is 50 milliseconds.
	PARITY= 0x16,		//ISO9141 specific ---------------- 0 - no parity, 1 - odd, 2 - even ------ parity type for detecting bit errors. Default value is 0(NO_PARITY).
	BIT_SAMPLE_POINT = 0x17,// CAN Specific --------------- 0 - 100-------------------------------- CAN specific, the desired bit sample point as a percentage of bit time. Default is 80%
	SYNCH_JUMP_WIDTH = 0x18, // CAN specific -------------- 0 - 100 ------------------------------- the desired synchronization jump width as a percentage of the bit time. Default is 15 %
	T1_MAX = 0x19, // SCI_X_XXXX specific ----------------- 0x00 - 0xffff ------------------------- the maximum interframe response delay. Default 20 ms
	T2_MAX = 0x1a, // SCI_X_XXXX specific ----------------- 0x00 - 0xffff ------------------------- the maximum interframe request delay. Default is 100 ms
	T4_MAX = 0x1b, // SCI_X_XXXX specific ----------------- 0x00 - 0xffff ------------------------- the maximum intermessage response delay. Default is 20 ms
	T5_MAX = 0x1c, // SCI_X_XXXX specific ----------------- 0x00 - 0xffff ------------------------- the maximum intermessage request delay. Default is 100 ms
	ISO15765_BS = 0x1e, // ISO15765 specific -------------- 0x1e to 0xff -------------------------- the block size for segmented transfers. The scan tool may override this value to match the capabilities reported by the ECUs. Default value is 0.
	ISO15765_STMIN = 0x1f, // ISO15765 specific ----------- 0x00 to 0xff -------------------------- the separation time for segmented transfers. The scan tool may override this value to match the capabilities reported by the ECUs. Default value is 0.
}J2534_GET_SET_PARAMETERS;


typedef enum J2534_IOCTL_ID_TYPE
{
	GET_CONFIG = 0x01,
	SET_CONFIG = 0x02,
	READ_VBATT = 0x03,
	READ_PROG_VOLTAGE = 0x04,
	FIVE_BAUD_INIT = 0x05,
	FAST_INIT = 0x06,
	CLEAR_TX_BUFFER = 0x07,
	CLEAR_RX_BUFFER = 0x08,
	CLEAR_PERIODIC_MSGS = 0x09,
	CLEAR_MSG_FILTERS = 0x0a,
	CLEAR_FUNCT_MSG_LOOKUP_TABLE = 0x0b,
	ADD_TO_FUNCT_MSG_LOOKUP_TABLE = 0x0c,
	DELETE_FROM_FUNCT_MSG_LOOUP_TABLE = 0x0d,
}J2534_IOCTL_ID_TYPE;


typedef enum J2534_ERR_TYPES
{
	J2534_NO_ERROR = 0x00,
	J2534_ERR_NOT_SUPPORTED = 0x01,
	J2534_ERR_INVALID_CHANNEL_ID = 0x02,
	J2534_ERR_INVALID_PROTOCOL_ID = 0x03,
	J2534_ERR_NULL_PARAMETER = 0x04,
	J2534_ERR_INVALID_IOCTL_VALUE = 0x05,
	J2534_ERR_INVALID_FLAGS = 0x06,
	J2534_ERR_FAILED = 0x07,
	J2534_ERR_DEVICE_NOT_CONNECTED = 0x08,
	J2534_ERR_TIMEOUT = 0x09,
	J2534_ERR_INVALID_MSG = 0x0A,
	J2534_ERR_INVALID_TIME_INTERVAL = 0x0B,
	J2534_ERR_EXCEEDED_LIMIT = 0x0C,
	J2534_ERR_INVALID_MSG_ID = 0x0D,
	J2534_ERR_INVALID_ERR_ID = 0x0E,
	J2534_ERR_INVALID_IOCTL_ID = 0x0F,
	J2534_ERR_BUFFER_EMPTY = 0x10,
	J2534_ERR_BUFFER_FULL = 0x11,
	J2534_ERR_BUFFER_OVERFLOW = 0x12,
	J2534_ERR_PIN_INVALID = 0x13,
	J2534_ERR_CHANNEL_IN_USE = 0x14,
	J2534_ERR_MSG_PROTOCOL_ID = 0x15,
	J2534_ERR_TX_ERROR = 0x16,
	J2534_DONGLE_COMMAND_NOT_SUPPORTED = 0x17,
	J2534_DONGLE_INVALID_FORMAT_OR_INCORRECT_MSG_LEN = 0x18,
	J2534_DONGLE_CRC_FAILURE = 0x19,
    J2534_DONGLE_SECURITY_ACCESS_DENIED =0x1a,
    J2534_DONGLE_INVALID_SECURITY_KEY=0x1b,
	J2534_DONGLE_PHYSICAL_CHANNEL_NOT_AVAILABLE=0x1e,
	
	


}J2534_ERR_TYPES;

typedef enum J2534_PROTOCOL_ID 
{
	J1850VPW = 0x00000001,
	J1850PWM = 0x00000002,
	ISO9141 = 0x00000003,  // physical channel 2 supporting protocol
	ISO14230 = 0x00000004, // physical channel 2 supporting protocol
	CAN = 0x00000005, // Physical channel 0 supporting protocol
	ISO15765 = 0x00000006, //Physucal channel 0 supporting protocol
	SCI_A_ENGINE = 0x00000007,
	SCI_A_TRANS = 0x00000008,
	SCI_B_ENGINE = 0x00000009,
	SCI_B_TRANS = 0x000000a,
    ISO9141_1 = 0x0000000b,  // Physical channel 3 supporting protocol
	ISO14230_1 = 0x0000000c, //physical channel 3 supporting protocol
	CAN_1 = 0x0000000d, // Physical channel 1 supporting protocol 
	ISO15765_1 = 0x0000000e, // physical channel 1 supporting protocol
	
}J2534_PROTOCOL_ID;

/*---------------------Dongle Received Eroros*/
typedef enum DONGLE_ERR_TYPES
{
	NO_ERROR = 0x00,
	COMMAND_NOT_SUPPORTED = 0x10,
	INVALID_FORMAT_OR_INCORRECT_MSG_LEN = 0x13,
	CRC_FAILURE = 0x15,
    SECURITY_ACCESS_DENIED =0x33,
    INVALID_SECURITY_KEY=0x35,
}DONGLE_ERR_TYPES;

DONGLE_ERR_TYPES DONGLE_ERRS_TYPES; 

typedef enum DongleApiType{
	CommandAPI=0x02,
	DataAPI=0x04,
	SecurityAPI=0x05,
}DongleApiType;

typedef struct  {
    int data_rate;
    bool loopback;
}protocol_parameters_common;

typedef struct  {
    int p1_min;
    int p1_max;
    int p2_min;
    int p2_max;
    int p3_min;
    int p3_max;
    int p4_min;
    int p4_max;
    int w1;
    int w2;
    int w3;
    int w4;
    int w5;
    int tidle;
    int tinl;
    int twup;
    int parity;
}protocol_parameters_9141;

// Define the main structure



typedef struct{
    PASSTHRU_MSG MaskMsg;
    PASSTHRU_MSG PatternMsg;
    PASSTHRU_MSG FlowControlMsg;
}filter;

typedef struct{
    int bit_sample_point;
    int synch_jump_width;
}protocol_parameters_can;

typedef struct  {
    int block_size;
    int separation_time;
}protocol_parameters_iso15765;



// Define the main structure
typedef  struct{
	
	//CAN and ISO15765 protocol
	bool status;
	unsigned long Protocol_ID;
	unsigned long Protocol_Speed;
	J2534_CANID_TYPE can_id_type;
	J2534_CAN_ADDRESSING_TYPE can_addressing;
	unsigned long some_variable; // You need to provide a name for this member
	unsigned long rxid;
	unsigned long rxstatusFlag;
	uint8_t receiverxid[4];
	bool PaddingStatus;
	PASSTHRU_MSG rolling_rx_data_array[10];
	uint8_t rolling_rx_data_array_index;
	filter pass_filter;
	filter block_filter;
	filter flowcontrol_filter;
	protocol_parameters_common common_parameters;
	protocol_parameters_can can_parameters;
	protocol_parameters_iso15765 iso15765_parameters;
	bool PaddingStatus;

	//ISO9141 and ISO14230
	unsigned long Protocol_ID;
    unsigned long txid;
    unsigned long rxid;
    PASSTHRU_MSG rolling_rx_data_array[10];
    uint8_t rolling_rx_data_array_index;
    protocol_parameters_9141 parameters_9141;
}Physical_protocol_interface;

Physical_protocol_interface Physical_protocol_interfaces;


// Going to use this stucture to check the physical channel status
typedef struct{ 
 bool busy;
}Physicalchannel;

Physicalchannel Physical_channels[4] = { {false}, }; // Note: making all physical channel free



//Passthru
//J2534_ERROR PassThruConnect(unsigned long ProtocolID,unsigned long Flags,unsigned long *pChannelID);
// J2534_ERROR PassThruDisconnect(unsigned long ChannelID);
// J2534_ERROR PassThruReadMsgs(unsigned long ChannelID, PASSTHRU_MSG *pMsg, unsigned long *pNumMsgs, unsigned long Timeout);
// J2534_ERROR PassThruWriteMsgs(unsigned long ChannelID, PASSTHRU_MSG *pMsg, unsigned long *pNumMsgs, unsigned long Timeout);
// J2534_ERROR PassThruStartPeriodicMsg(unsigned long ChannelID, PASSTHRU_MSG *pMsg, unsigned long *pMsgID, unsigned long TimeInterval);
// J2534_ERROR PassThruStopPeriodicMsg(unsigned long ChannelID, unsigned long MsgID);
// J2534_ERROR PassThruStartMsgFilter(unsigned long ChannelID, unsigned long FilterType, PASSTHRU_MSG *pMaskMsg, 
												PASSTHRU_MSG *pPatternMsg, PASSTHRU_MSG *pFlowControlMsg, unsigned long *pMsgID);
// J2534_ERROR PassThruStopMsgFilter(unsigned long ChannelID, unsigned long MsgID);
// J2534_ERROR PassThruSetProgrammingVoltage(unsigned long PinNumber, unsigned long Voltage);
J2534_ERROR PassThruReadVersion(char *pFirmwareVersion, char * pDllVersion, char *pApiVersion);
J2534_ERROR PassThruGetLastError(char *pErrorDescription);
// J2534_ERROR PassThruIoctl(unsigned long ChannelID, unsigned long IoctlID, void *pInput, void *pOutput);

//Dongle 
J2534_ERROR DongleCommandSender(uint8_t APIType, uint16_t totalbytelngth,uint8_t channelId, uint8_t *payload);
J2534_ERROR DongleSetProtocol(uint8_t APIType, uint16_t totalbytelngth,uint8_t channelId, uint8_t *payload);
J2534_ERROR DongleSetTxId();
J2534_ERROR DongleSetRxId();
J2534_ERROR DongleSetPaddbyte();
J2534_ERROR DongleStopPadbyte();

//Continue running function
J2534_ERROR DongleReceivedFunction();



J2534_ERROR PassThruConnect(unsigned long ProtocolID,unsigned long Flags,unsigned long *pChannelID){
    if (ProtocolID == CAN || ProtocolID == ISO15765) {
        
		if (Physical_channels[0].busy == false) { // is CAN0 available
            Physical_channels[0].busy = true;            		
			Physical_protocol_interfaces.Protocol_ID = ProtocolID;

            if (Flags & J2534_CONNECT_FLAG_CAN_29BIT_ID_BIT) {
                Physical_protocol_interfaces.can_id_type = CAN_29BIT_ID_BIT;
            } else if {
                Physical_protocol_interfaces.can_id_type = CAN_11BIT_ID_BIT;
            }
			if (Flags & J2534_CONNECT_ISO15765_ADDR_TYPE_BIT) {
               Physical_protocol_interfaces.can_addressing = EXTENDED_ADDR_TYPE_BIT;
            } else if {
            	Physical_protocol_interfaces.can_addressing = STD_ADDR_TYPE_BIT;
            }
		}else{
			return J2534_DONGLE_PHYSICAL_CHANNEL_NOT_AVAILABLE;

		}
	}

	else if (ProtocolID == CAN_1 || ProtocolID == ISO15765_1) {
        
		if (Physical_channels[1].busy == false) { // is CAN0 available
            Physical_channels[1].busy = true;            		
			Physical_protocol_interfaces.Protocol_ID = ProtocolID;
            if (Flags & J2534_CONNECT_FLAG_CAN_29BIT_ID_BIT) {
                Physical_protocol_interfaces.can_id_type = CAN_29BIT_ID_BIT;
            } else if {
                Physical_protocol_interfaces.can_id_type = CAN_11BIT_ID_BIT;
            }else{
			}
            
            if (Flags & J2534_CONNECT_ISO15765_ADDR_TYPE_BIT) {
               Physical_protocol_interfaces.can_addressing = EXTENDED_ADDR_TYPE_BIT;
            } else if {
            	Physical_protocol_interfaces.can_addressing = STD_ADDR_TYPE_BIT;
            }else{

			}
        
		}
		else{
			return J2534_DONGLE_PHYSICAL_CHANNEL_NOT_AVAILABLE;

		}
	}


    else if (ProtocolID == ISO9141 || ProtocolID == ISO14230) {
    	if (Physical_channels[2].busy == false) { // is KLINE0 available
           Physical_channels[2].busy = true;
           Physical_protocol_interfaces.Protocol_ID = ProtocolID;
            
        } else {
            return J2534_ERR_EXCEEDED_LIMIT;
        }
    } 
	else if (ProtocolID == ISO9141 || ProtocolID == ISO14230) {
    	if (Physical_channels[3].busy == false) { // is KLINE1 available
            Physical_channels[3].busy = true;
           	Physical_protocol_interfaces.Protocol_ID = ProtocolID;
            
        }else{
            return J2534_ERR_EXCEEDED_LIMIT;
        }
    } 

	else {
        return J2534_ERR_INVALID_PROTOCOL_ID;
    }

	return J2534_NO_ERROR;


}


J2534_ERROR PassThruDisconnect(unsigned long ChannelID){

}

J2534_ERROR PassThruIoctl(unsigned long ChannelID, unsigned long IoctlID, void *pInput, void *pOutput)
{


}


extern J2534_ERROR PassThruIoctl(unsigned long ChannelID, unsigned long IoctlID, void *pInput, void *pOutput) {
    J2534_ERROR return_error = J2534_NO_ERROR;

    switch (IoctlID) {
        case GET_CONFIG:
            // Handle GET_CONFIG command
            // Check if pInput is not NULL
            if (pInput == NULL) {
                return J2534_ERR_NULL_PARAMETER;
            }

            // Cast pInput to the appropriate data structure
            // Assuming ConfigPtr is a pointer to an array of structures
            // Modify it according to your actual implementation
            // Example:
            // struct ConfigInput *configInput = (struct ConfigInput *)pInput;

            // Process each configuration parameter
            for (int i = 0; i < configInput->NumOfParams; i++) {
                switch (configInput->ConfigPtr[i]->Parameter) {
                    case DATA_RATE:
                        configInput->ConfigPtr[i]->Value = data_rate;
						//Take above data rate the from above and send it to DongleSetProtocol function
						DongleSetProtocol()

                        break;
                    case LOOPBACK:
                        configInput->ConfigPtr[i]->Value = loopback;
                        break;
                    case NODE_ADDRESS:
                    case NETWORK_LINE:
                    case P1_MIN:
                    case P1_MAX:
                    case P2_MIN:
                    case P2_MAX:
                    case P3_MIN:
                    case P3_MAX:
                    case P4_MIN:
                    case P4_MAX:
                    case W1:
                    case W2:
                    case W3:
                    case W4:
                    case W5:
                    case TIDLE:
                    case TINL:
                    case TWUP:
                    case PARITY:
                    case T1_MAX:
                    case T2_MAX:
                    case T4_MAX:
                    case T5_MAX:
                        // These parameters are not supported, return an error
                        return_error = J2534_ERR_INVALID_IOCTL_ID;
                        return return_error;
                    case BIT_SAMPLE_POINT:
                        configInput->ConfigPtr[i]->Value = sample_point;
                        break;
                    case SYNCH_JUMP_WIDTH:
                        configInput->ConfigPtr[i]->Value = synch_jump_width;
                        break;
                    case ISO15765_BS:
                        configInput->ConfigPtr[i]->Value = block_size;
                        break;
                    case ISO15765_STMIN:
                        configInput->ConfigPtr[i]->Value = separation_time;
                        break;
                    default:
                        // Unknown parameter, return an error
                        return_error = J2534_ERR_INVALID_IOCTL_ID;
                        return return_error;
                }
            }
            break;
        case SET_CONFIG:
            // Handle SET_CONFIG command
            // Check if pInput is not NULL
            if (pInput == NULL) {
                return J2534_ERR_NULL_PARAMETER;
            }

            // Cast pInput to the appropriate data structure
            // Assuming ConfigPtr is a pointer to an array of structures
            // Modify it according to your actual implementation
            // Example:
            // struct ConfigInput *configInput = (struct ConfigInput *)pInput;

            // Process each configuration parameter
            for (int i = 0; i < configInput->NumOfParams; i++) {
                switch (configInput->ConfigPtr[i]->Parameter) {
                    case DATA_RATE:
                        data_rate = configInput->ConfigPtr[i]->Value;
                        break;
                    case LOOPBACK:
                        loopback = configInput->ConfigPtr[i]->Value;
                        break;
                    case NODE_ADDRESS:
                    case NETWORK_LINE:
                    case P1_MIN:
                    case P1_MAX:
                    case P2_MIN:
                    case P2_MAX:
                    case P3_MIN:
                    case P3_MAX:
                    case P4_MIN:
                    case P4_MAX:
                    case W1:
                    case W2:
                    case W3:
                    case W4:
                    case W5:
                    case TIDLE:
                    case TINL:
                    case TWUP:
                    case PARITY:
                    case T1_MAX:
                    case T2_MAX:
                    case T4_MAX:
                    case T5_MAX:
                        // These parameters are not supported, return an error
                        return_error = J2534_ERR_INVALID_IOCTL_ID;
                        return return_error;
                    case BIT_SAMPLE_POINT:
                        sample_point = configInput->ConfigPtr[i]->Value;
                        break;
                    case SYNCH_JUMP_WIDTH:
                        synch_jump_width = configInput->ConfigPtr[i]->Value;
                        break;
                    case ISO15765_BS:
                        block_size = configInput->ConfigPtr[i]->Value;
                        break;
                    case ISO15765_STMIN:
                        separation_time = configInput->ConfigPtr[i]->Value;
                        break;
                    default:
                        // Unknown parameter, return an error
                        return_error = J2534_ERR_INVALID_IOCTL_ID;
                        return return_error;
                }
            }
            break;
        case READ_VBATT:
            // Implement READ_VBATT command
            // Read vbatt from the device and put the result in vbatt
            // Example:
            // unsigned long vbatt;
            // read_vbatt(&vbatt); // Assuming read_vbatt is a function provided by your device API
            // *(unsigned long *)pOutput = vbatt;
            break;
        case READ_PROG_VOLTAGE:
            // Implement READ_PROG_VOLTAGE command
            // Put the programmed voltage in pOutput
            // Example:
            // *(unsigned long *)pOutput = read_prog_voltage();
            break;
        case FIVE_BAUD_INIT:
            // Implement FIVE_BAUD_INIT command
            // Initiate 5 baud init
            break;
        case FAST_INIT:
            // Implement FAST_INIT command
            // Initiate fast init
            break;
        case CLEAR_TX_BUFFER:
            // Implement CLEAR_TX_BUFFER command
            // Clear the transmit buffer
            break;
        case CLEAR_RX_BUFFER:
            // Implement CLEAR_RX_BUFFER command
            // Clear the receive buffer
            // Example:
            // log_channel[ChannelID].rolling_rx_data_array_index = 0;
            break;
        case CLEAR_PERIODIC_MSGS:
            // Implement CLEAR_PERIODIC_MSGS command
            // Stop the periodic messages that are running
            break;
        case CLEAR_MSG_FILTERS:
            // Implement CLEAR_MSG_FILTERS command
            // Clear message filters
            break;
        case CLEAR_FUNCT_MSG_LOOKUP_TABLE:
            // Implement CLEAR_FUNCT_MSG_LOOKUP_TABLE command
            // Clear function message lookup table
            break;
        case ADD_TO_FUNCT_MSG_LOOKUP_TABLE:
            // Implement ADD_TO_FUNCT_MSG_LOOKUP_TABLE command
            // Add function message to lookup table
            break;
        case DELETE_FROM_FUNCT_MSG_LOOUP_TABLE:
            // Implement DELETE_FROM_FUNCT_MSG_LOOUP_TABLE command
            // Delete function message from lookup table
            break;
        default:
            // Unknown IOCTL ID, return an error
            return_error = J2534_ERR_INVALID_IOCTL_ID;
            break;
    }

    return return_error;
}




/*------------------Dongel APIs*/

J2534_ERROR DongleCommandgenerator(uint8_t APIType, uint16_t totalbytelngth,uint8_t channelId, uint8_t * databytes){
    uint8_t *senddata;
    int index=0;
    senddata[index++]=APIType<<4|(uint8_t)(totalbytelngth >> 8);
    senddata[index++]=(uint8_t)(totalbytelngth & 0x00FF);
    senddata[index++]=channelId;
    memcpy(sendata[index++],databytes,totalbytelngth);
    index=index+totalbytelngth;
    //do the crc calculation and add after the payload
    senddata[index++]=crc1;
    senddata[index++]=crc2;
    //send data to the bluetoth or other commuincation channel  
    return J2534_NO_ERROR;
}





J2534_ERROR SetProtocol(uint8_t dongleprotoid, uint8_t dongleprotospeed, uint8_t dongleprotoidtype, uint8_t dongleadressing) {
    uint8_t SetprotocolID[2];
	uint8_t physical_channel; //varibale to assign physical channel 
     
   /*we will checked CAN_CHANNEL structure Variable */
    // Check the protocol ID, speed, type, and addressing to determine the protocol
    if (dongleprotoid == ISO15765) {
		physical_channel=0x00; // assgining physical channel byte to 0.
        if (dongleprotospeed == 250000) {
            if (dongleprotoidtype == CAN_11BIT_ID_BIT && dongleadressing == STD_ADDR_TYPE_BIT) {
                SetprotocolID[2] = {0x02,0x00};
				DongleCommandgenerator(uint8_t APIType, uint16_t totalbytelngth,uint8_t channelId, uint8_t * databytes){
            } else if (dongleprotoidtype == CAN_29BIT_ID_BIT && dongleadressing == STD_ADDR_TYPE_BIT) {
                SetprotocolID[2] = {0x02,0x01};
            } else {
                return J2534_DONGLE_INVALID_FORMAT_OR_INCORRECT_MSG_LEN; // Invalid type or addressing
            }
        } else if (dongleprotospeed == 500000) {
            if (dongleprotoidtype == CAN_11BIT_ID_BIT && dongleadressing == STD_ADDR_TYPE_BIT) {

				SetprotocolID[2] = {0x02,0x02};
            } else if (dongleprotoidtype == CAN_29BIT_ID_BIT && dongleadressing == STD_ADDR_TYPE_BIT) {
				SetprotocolID[2] = {0x02,0x03}; 
           } else {
               return J2534_DONGLE_INVALID_FORMAT_OR_INCORRECT_MSG_LEN; // Invalid type or addressing
            }
        } else if (dongleprotospeed == 1000000) {
            if (dongleprotoidtype == CAN_11BIT_ID_BIT && dongleadressing == STD_ADDR_TYPE_BIT) {
                SetprotocolID[2] = {0x02,0x04};
				
            } else if (dongleprotoidtype == CAN_29BIT_ID_BIT && dongleadressing == STD_ADDR_TYPE_BIT) {
                SetprotocolID[2] = {0x02,0x05};
			
            } else {
                return J2534_DONGLE_INVALID_FORMAT_OR_INCORRECT_MSG_LEN; // Invalid type or addressing
            }
        } else {
            return J2534_DONGLE_INVALID_FORMAT_OR_INCORRECT_MSG_LEN; // Invalid speed
        }
    }else if (dongleprotoid == ISO15765_1) {
		physical_channel=0x01; // assgining physical channel byte to 1.
        if (dongleprotospeed == 250000) {
            if (dongleprotoidtype == CAN_11BIT_ID_BIT && dongleadressing == STD_ADDR_TYPE_BIT) {
                SetprotocolID[2] = {0x02,0x00};
				
            } else if (dongleprotoidtype == CAN_29BIT_ID_BIT && dongleadressing == STD_ADDR_TYPE_BIT) {
                SetprotocolID[2] = {0x02,0x01};
				
            } else {
                return J2534_DONGLE_INVALID_FORMAT_OR_INCORRECT_MSG_LEN; // Invalid type or addressing
            }
        } else if (dongleprotospeed == 500000) {
            if (dongleprotoidtype == CAN_11BIT_ID_BIT && dongleadressing == STD_ADDR_TYPE_BIT) {
                SetprotocolID[2] = {0x02,0x02};
				
            } else if (dongleprotoidtype == CAN_29BIT_ID_BIT && dongleadressing == STD_ADDR_TYPE_BIT) {
            	SetprotocolID[2] = {0x02,0x03};
				
            } else {
                return J2534_DONGLE_INVALID_FORMAT_OR_INCORRECT_MSG_LEN; // Invalid type or addressing
            }
        } else if (dongleprotospeed == 1000000) {
            if (dongleprotoidtype == CAN_11BIT_ID_BIT && dongleadressing == STD_ADDR_TYPE_BIT) {
                SetprotocolID[2] = {0x02,0x04};
				
            } else if (dongleprotoidtype == CAN_29BIT_ID_BIT && dongleadressing == STD_ADDR_TYPE_BIT) {
                SetprotocolID[2] = {0x02,0x05};
				
            } else {
                return J2534_DONGLE_INVALID_FORMAT_OR_INCORRECT_MSG_LEN; // Invalid type or addressing
            }
        } else {
            return J2534_DONGLE_INVALID_FORMAT_OR_INCORRECT_MSG_LEN; // Invalid speed
        }
    }else if(dongleprotoid=ISO9141) {



	}
	else if(dongleprotoid=ISO9141_1) {



	}
	else {
        return J2534_DONGLE_INVALID_FORMAT_OR_INCORRECT_MSG_LEN; // Invalid protocol ID
    }

    // Call the command generator function if no error occurred
    if (error == DONGLE_API_NO_ERROR) {
        DongleCommandgenerator(CommandAPI, 2, 0x00, SetprotocolID);
    }

    return J2534_NO_ERROR;
}