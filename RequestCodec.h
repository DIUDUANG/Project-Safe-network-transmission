#ifndef __02_REQUESTCODEC_H__
#define __02_REQUESTCODEC_H__
#define DISALLOW_COPY_AND_ASSIGN(Typename) \
        Typename(const Typename&) \
        void operator=(const Typename&)
#include "Codec.h"

//�����Ľṹ������
struct RequestMsg
{
  //1 ��ԿЭ��  	//2 ��ԿУ��; 	// 3 ��Կע��
  int	 cmdType;		// �������� 
  char	 clientId[12];	// �ͻ��˱��
  char	 authCode[65];	// ��֤��
  char	 serverId[12];	// �������˱�� 
  char	 r1[64];			// �ͻ��������
};

class RequestCodec : public Codec {
 public:
  //����
  RequestCodec();
  explicit RequestCodec(RequestMsg* msg);
  //����
  ~RequestCodec();


  //����(��д)
  int msgEncode(char** outData, int& len) override;
  //����(��д)
  int msgDecode(char* inData, int inLen) override;
  //�ͷű�������ṹ��(��д)
  int msgMemFree(void** point) override;

 private:
  //�����Ľṹ��
  RequestMsg* mRequsetMsg; 

  //��ֹ�Զ����ɿ�����������ظ�ֵ�����
  DISALLOW_COPY_AND_ASSIGN(RequestCodec);
};

#endif