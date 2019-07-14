#include "RequestCodec.h"

//����
RequestCodec::RequestCodec() {

  mRequsetMsg = new RequestMsg;
  memset(mRequsetMsg, 0, sizeof(mRequsetMsg));
}

RequestCodec::RequestCodec(RequestMsg* msg) {

  mRequsetMsg = new RequestMsg;
  memset(mRequsetMsg, 0, sizeof(mRequsetMsg));
  memcpy(mRequsetMsg, msg, sizeof(msg));
}

//����
RequestCodec::~RequestCodec() {

  delete mRequsetMsg;
}

//����
int RequestCodec::msgEncode(char** outData, int& len) {
  //���뱨������(int)
  int retval = writeHeadNode(mRequsetMsg->cmdType);
  if (0 != retval) {
    printf("encode mRequsetMsg->cmdType failed...\n");
    return 25;
  }

  //����ͻ��˱��(char[])
  retval = writeNextNode(mRequsetMsg->clientId, 
                          strlen(mRequsetMsg->clientId));

  if (0 != retval) {
    printf("encode mRequsetMsg->clientId failed...\n");
    return 26;
  }
  //������֤��(char[])
  retval = writeNextNode(mRequsetMsg->authCode, 
                          strlen(mRequsetMsg->authCode));

  if (0 != retval) {
    printf("encode mRequsetMsg->authCode failed...\n");
    return 27;
  }
  //�������˱��(char[])
  retval = writeNextNode(mRequsetMsg->serverId, 
                          strlen(mRequsetMsg->serverId));

  if (0 != retval) {
    printf("encode mRequsetMsg->serverId failed...\n");
    return 28;
  }
  //����ͻ��������(char[])
  retval = writeNextNode(mRequsetMsg->r1, 
                          strlen(mRequsetMsg->r1));

  if (0 != retval) {
    printf("encode mRequsetMsg->r1 failed...\n");
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
  retval = readHeadNode(mRequsetMsg->cmdType);
  if (0 != retval) {
    printf("decode cmdType failed...\n");
    return 33;
  }

  //����ͻ��˱��
  retval = readNextNode(mRequsetMsg->clientId);
  if (0 != retval) {
    printf("decode clientId failed...\n");
    return 34;
  }

  //������֤��
  retval = readNextNode(mRequsetMsg->authCode);
  if (0 != retval) {
    printf("decode authCode failed...\n");
    return 35;
  }


  //�������˱��
  retval = readNextNode(mRequsetMsg->serverId);
  if (0 != retval) {
    printf("decode serverId failed...\n");
    return 36;
  }

  //����ͻ��������
  retval = readHeadNode(mRequsetMsg->r1);
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
