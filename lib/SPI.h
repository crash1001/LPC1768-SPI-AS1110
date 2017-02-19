#ifndef __SSP_H
#define __SSP_H

#ifdef __cplusplus
extern "C"
{
#endif
	

//Variables	
typedef struct {
	uint8_t Databit; 		/** Databit number, should be SSP_DATABIT_x,
							where x is in range from 4 - 16 */
	uint8_t CPHA;			/** Clock phase, should be:
							- SSP_CPHA_FIRST: first clock edge
							- SSP_CPHA_SECOND: second clock edge */
	uint8_t CPOL;			/** Clock polarity, should be:
							- SSP_CPOL_HI: high level
							- SSP_CPOL_LO: low level */
	uint8_t Mode;			/** SSP mode, should be:
							- SSP_MASTER_MODE: Master mode
							- SSP_SLAVE_MODE: Slave mode */
	uint8_t FrameFormat;	/** Frame Format:
							- SSP_FRAME_SPI: Motorola SPI frame format
							- SSP_FRAME_TI: TI frame format
							- SSP_FRAME_MICROWIRE: National Microwire frame format */
	uint32_t ClockRate;		/** Clock rate,in Hz */
} SSP_CFG_Type;


//Functions
void SSPInit(uint8_t portNum, SSP_CFG_Type *SSP_ConfigStruct);


	

#ifdef __cplusplus
}
#endif

#endif