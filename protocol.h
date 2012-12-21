/*********************************************************************/
/* Copyright (C) lichao, 2012                                        */
/*                                                                   */
/*  FILE NAME             :  protocol.h                              */
/*  PRINCIPAL AUTHOR      :  lichao                                  */
/*  SUBSYSTEM NAME        :  network                                 */
/*  MODULE NAME           :  protocol                                */
/*  LANGUAGE              :  C                                       */
/*  TARGET ENVIRONMENT    :  Linux                                   */
/*  DATE OF FIRST RELEASE :  2012/12/15                              */
/*  DESCRIPTION           :  Protocol between lichao Sever and Client*/
/*********************************************************************/

/*
 * Revision log:
 *
 * Created by lichao,2012/12/15
 *
 */

#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_
/*
 * Data format
    0---------------------------------------------------31
    |         operation command(int-4bytes)             |
    -----------------------------------------------------
    |         number of data(int-4bytes) = 0..x         |
    -----------------------------------------------------
    |            data-1 length(int-4bytes)              |
    -----------------------------------------------------
    |                                                   |
    /                   data-1                          /
    |                                                   |
    -----------------------------------------------------
    |          data-2..x length(int-4bytes)             |
    -----------------------------------------------------
    |                                                   |
    /                   data-2..x                       /
    |                                                   |
    0---------------------------------------------------31
 */
 
/* operation commands */
#define SUCCESS 0       //SUCCESS
#define FAILURE -1      //FAILURE    

#define OPEN_CMD        1 /* With one data - database file name */
#define CLOSE_CMD       2 /* With zero data */
#define GET_CMD         3 /* With one data - key */
#define SET_CMD         4 /* With two data - key and value */
#define DELETE_CMD      5 /* With one data - key */
#define ERROR_RSP       0 /* With one data - Error infomation */
#define OPEN_RSP        OPEN_CMD    /* if success,With zero data */
#define CLOSE_RSP       CLOSE_CMD   /* if success,With zero data */
#define GET_RSP         GET_CMD     /* if success,With two data - key and value */
#define SET_RSP         SET_CMD     /* if success,With zero data */
#define DELETE_RSP      DELETE_CMD  /* if success,With zero data */

/*
 * ZipData - maximum 2 data
 * input    : cmd,data and data size
 * in/out	: pBuf - to store formated packet 
 * in/out	: pBufSize - size of the memory pointed by pBuf,and output the size be used
 * return	: if SUCCESS return 0
 *          : if FAILURE return (-1)
 */
/*a command with no parameter*/
int ZipDataZero(char* pBuf,int* pBufSize,int cmdType);

/*a command with one parameter*/
int ZipDataOne(char* pBuf,int* pBufSize,int cmdType,char* pData,int DataSize);

/*a command with two parameters*/
int ZipDataTwo(char* pBuf,int* pBufSize,int cmdType,char* pDataOne,int DataSizeOne,char* pDataTwo,int DataSizeTwo);

/*
 * UnzipData - maximum 2 data
 * input	: pBuf - point to recved packet 
 *       	: BufSize - size of packet pointed by pBuf
 * output   : pcmdType,pDataCount
 *          : pDataOne,pDataSizeOne,pDataTwo,pDataSizeTwo,if no data,
 *          : *pDataOne == '\0',*pDataSizeOne == 0 or *pDataTwo == '\0',*pDataSizeTwo == 0
 * return	: if SUCCESS return 0
 *          : if FAILURE return (-1)
 */
int UnzipData(char* pBuf,int BufSize,int* pcmdType,int* pDataCount,char* pDataOne,int* pDataSizeOne,char* pDataTwo,int* pDataSizeTwo);
        
#endif /* _PROTOCOL_H_ */


