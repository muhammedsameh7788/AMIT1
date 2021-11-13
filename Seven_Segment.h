/*
 * Seven_Segment.h
 *
 * Created: 10/16/2021 1:52:28 PM
 *  Author: osama
 */ 


#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_


void Seven_SEGMENT_INIT();
void Seven_SEGMENT_write_number(u8 number);
void Seven_SEGMENT_Enable1();
void Seven_SEGMENT_Enable2();
void Seven_SEGMENT_Disable1();
void Seven_SEGMENT_Disable2();
///////////////////////////////////////
void Seven_SEGMENT_Disable();

void Seven_SEGMENT_write_number_BARAKAT(u8 number ,u8 SEGMANT);


void _7_SEGMENT_READ(u8 Data);


#endif /* SEVEN_SEGMENT_H_ */