#include "RequestCodec.h"

//����
RequestCodec::RequestCodec() {

  mRequestMsg = new RequestMsg;
  memset(mRequestMsg, 0, sizeof(mRequestMsg));
}

RequestCodec::RequestCodec(RequestMsg* msg) {

  mRequestMsg = new RequestMsg;
  memset(mRequestMsg, 0, sizeof(mRequestMsg));
  memcpy(mRequestMsg, msg, sizeof(msg));
}

//����
RequestCodec::~RequestCodec() {

  delete mRequestMsg;
}

//����
int RequestCodec::msgEncode(char** outData, int& len) {
  //���뱨������(int)
  int retval = writeHeadNode(mRequestMsg->cmdType);
  if (0 != retval) {
    printf("encode mRequestMsg->cmdType failed...\n");
    return 25;
  }

  //����ͻ��˱��(char[])
  retval = writeNextNode(mRequestMsg->clientId, 
                         strlen(mRequestMsg->clientId));

  if (0 != retval) {
    printf("encode mRequestMsg->clientId failed...\n");
    return 26;
  }
  //������֤��(char[])
  retval = writeNextNode(mRequestMsg->authCode, 
                          strlen(mRequestMsg->authCode));

  if (0 != retval) {
    printf("encode mRequestMsg->authCode failed...\n");
    return 27;
  }
  //�������˱��(char[])
  retval = writeNextNode(mRequestMsg->serverId, 
                          strlen(mRequestMsg->serverId));

  if (0 != retval) {
    printf("encode mRequestMsg->serverId failed...\n");
    return 28;
  }
  //����ͻ��������(char[])
  retval = writeNextNode(mRequestMsg->r1, 
                          strlen(mRequestMsg->r1));

  if (0 != retval) {
    printf("encode mRequestMsg->r1 failed...\n");
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
int RequestCodec::msgDecode(char* inData, int inLen) {
  
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
  retval = readHeadNode(mRequestMsg->cmdType);
  if (0 != retval) {
    printf("decode cmdType failed...\n");
    return 33;
  }

  //����ͻ��˱��
  retval = readNextNode(mRequestMsg->clientId);
  if (0 != retval) {
    printf("decode clientId failed...\n");
    return 34;
  }

  //������֤��
  retval = readNextNode(mRequestMsg->authCode);
  if (0 != retval) {
    printf("decode authCode failed...\n");
    return 35;
  }


  //�������˱��
  retval = readNextNode(mRequestMsg->serverId);
  if (0 != retval) {
    printf("decode serverId failed...\n");
    return 36;
  }

  //����ͻ��������
  retval = readHeadNode(mRequestMsg->r1);
  if (0 != retval) {
    printf("decode r1 failed...\n");
    return 37;
  }

  //�ͷ��ڴ�
  freeSequnce();

  return 0;
}

//�ͷ��ڴ汨������ṹ��
int RequestCodec::msgMemFree(void** point) {
  if (NULL == point) {
    return 38;
  }
  else {
    delete *point;
    *point = NULL;
  }

  return 0;
}
