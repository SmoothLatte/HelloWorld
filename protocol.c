
/*********************************************************************/
/* Copyright (C) lichao, 2012                                        */
/*                                                                   */
/*  FILE NAME             :  protocol.c                              */
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

#include "protocol.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>



typedef struct ProtocolData
{
    int cmdType; //the type of cmd
    int count;   //the number of parameters
    int lenght;  //the length of DataOne
}ProtocolData;

int ZipDataZero(char* pBuf,int* pBufSize,int cmdType)
{
    if((*pBufSize < sizeof(ProtocolData)) || pBuf == NULL)
  {
		fprintf(stderr,"error!!!  ZipDataZero,%s:%d\n",__FILE__,__LINE__);
		return FAILURE;
	}
	ProtocolData* pData = (ProtocolData *)pBuf;
	pData->cmdType = htonl(cmdType);
	pData->count = htonl(0);
	pData->length = htonl(0);
	*pBuffSize = sizeof(ProtocolData);
	return SUCCESS;
}

int ZipDataOne(char* pBuf,int* pBufSize,int cmdType,char* pData,int DataSize)
{
    if((*pBufSize < sizeof(ProtocolData) + Datasize) \
        || pBuf == NULL || pData == NULL)
    {
        fprintf(stderr,"error!!!  ZipDataOne,%s:%d\n",__FILE__,__LINE__);
		return FAILURE;
    }
    ProtocolData* pData = (ProtocolData *)pBuf;
	pData->cmdType = htonl(cmdType);
	pData->count = htonl(1);
	pData->length = htonl(DataSize);
    memcpy(pBuf + sizeof(ProtocolData),pData,DataSize);
	*pBuffSize = sizeof(ProtocolData) + DataSize;
	return SUCCESS;
}

int ZipDataTwo(char* pBuf,int* pBufSize,int cmdType,char* pDataOne,int DataSizeOne,char* pDataTwo,int DataSizeTwo)
{
    if((*pBufSize < sizeof(ProtocolData) + DataSizeOne + sizeof(int) + DataSizeTwo) \
        || pBuf == NULL || pDataOne == NULL || pDataTwo == NULL)
    {
        fprintf(stderr,"error!!!  ZipDataOne,%s:%d\n",__FILE__,__LINE__);
		return FAILURE;
    }
    ProtocolData* pData = (ProtocolData *)pBuf;
	pData->cmdType = htonl(cmdType);
	pData->count = htonl(2);
	pData->length = htonl(DataSizeOne);
    memcpy(pBuf + sizeof(ProtocolData),pDataOne,DataSizeOne);
    memcpy(pBuf + sizeof(ProtocolData) + DataSizeOne + sizeof(int),pDataTwo,DataSizeTwo);
	*pBuffSize = sizeof(ProtocolData) + DataSizeOne + sizeof(int) + DataSizeTwo;
	return SUCCESS;
}

int UnzipData(char* pBuf,int BufSize,int* pcmdType,int* pDataCount,char* pDataOne,int* pDataSizeOne,char* pDataTwo,int* pDataSizeTwo)
{
    int lengthOne=0,lengthTwo=0;
    if(BufSize < sizeof(ProtocolData) || pBuf == NULL \
    || pcmdType == NULL || pDataCount == NULL || pDataOne == NULL\
    || pDataSizeOne == NULL || pDataSizeTwo == NULL)
    {
        fprintf(stderr,"error!!!  UnzipData,%s:%d\n",__FILE__,__LINE__);
		return FAILURE;
    }
    ProtocolData* pData = (ProtocolData *)pBuf;
    *pcmdType = ntohl(pData->cmdType);
    *pDataCount = ntohl(pData->count);
    if((*pDataCount) > )
}






















