#include "RespondCodec.h"

//����
RespondCodec::RespondCodec() {

  mRespondMsg = new RespondMsg;
  memset(mRespondMsg, 0, sizeof(mRespondMsg));
}

RespondCodec::RespondCodec(RespondMsg* msg) {

  mRespondMsg = new RespondMsg;
  memset(mRespondMsg, 0, sizeof(mRespondMsg));
  memcpy(mRespondMsg, msg, sizeof(msg));
}

//����
RespondCodec::~RespondCodec() {

  delete mRespondMsg;
}

//����
int RespondCodec::msgEncode(char** outData, int& len) {
  //���뱨������(int)
  int retval = writeHeadNode(mRespondMsg->rv);
  if (0 != retval) {
    printf("encode mRespondMsg->rv failed...\n");
    return 25;
  }

  //����ͻ��˱��(char[])
  retval = writeNextNode(mRespondMsg->clientId, 
                         strlen(mRespondMsg->clientId));

  if (0 != retval) {
    printf("encode mRespondMsg->clientId failed...\n");
    return 26;
  }
  //������֤��(char[])
  retval = writeNextNode(mRespondMsg->serverId, 
                          strlen(mRespondMsg->serverId));

  if (0 != retval) {
    printf("encode mRespondMsg->serverId failed...\n");
    return 27;
  }
  //�������˱��(char[])
  retval = writeNextNode(mRespondMsg->r2, 
                          strlen(mRespondMsg->r2));

  if (0 != retval) {
    printf("encode mRespondMsg->r2 failed...\n");
    return 28;
  }
  //����ͻ��������(char[])
  retval = writeNextNode(mRespondMsg->seckeyid);

  if (0 != retval) {
    printf("encode mRespondMsg->seckeyid failed...\n");
    return 29;
  }
  //��������
  retval = packSequence(outData, len);

  if (0 != retval) {
    printf("packSequence failed...\n");
    return 30;
  }
  //�ͷ��ڴ�
  freeSequnce();

  return 0;
}

//����
int RespondCodec::msgDecode(char* inData, int inLen) {
  
  //�������
  if (NULL == inData || inLen <= 0) {
    printf("msgDecode: the parameter is invalid...\n");
    return 31;
  }

  //��������
  int retval = unpackSequence(inData, inLen);
  if (0 != retval) {
    printf("unpackSequence failed...\n");
    return 32;
  }

  //���뱨������
  retval = readHeadNode(mRespondMsg->rv);
  if (0 != retval) {
    printf("decode rv failed...\n");
    return 33;
  }

  //����ͻ��˱��
  retval = readNextNode(mRespondMsg->clientId);
  if (0 != retval) {
    printf("decode clientId failed...\n");
    return 34;
  }

  //������֤��
  retval = readNextNode(mRespondMsg->serverId);
  if (0 != retval) {
    printf("decode serverId failed...\n");
    return 35;
  }


  //�������˱��
  retval = readNextNode(mRespondMsg->r2);
  if (0 != retval) {
    printf("decode r2 failed...\n");
    return 36;
  }

  //����ͻ��������
  retval = readHeadNode(mRespondMsg->seckeyid);
  if (0 != retval) {
    printf("decode seckeyid failed...\n");
    return 37;
  }

  //�ͷ��ڴ�
  freeSequnce();

  return 0;
}

//�ͷ��ڴ汨������ṹ��
int RespondCodec::msgMemFree(void** point) {
  if (NULL == point) {
    return 38;
  }
  else {
    delete *point;
    *point = NULL;
  }

  return 0;
}
