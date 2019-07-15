#ifndef __02_RESPONDCODEC_H__
#define __02_RESPONDCODEC_H__
#define DISALLOW_COPY_AND_ASSIGN(Typename) \
        Typename(const Typename&) \
        void operator=(const Typename&)
#include "Codec.h"

//�����Ľṹ������
struct RespondMsg
{
  //1 ��ԿЭ��  	//2 ��ԿУ��; 	// 3 ��Կע��
  int		 rv;						//��� 
  char	 clientId[12];	//�����
  char	 serverId[12];	//�����
  char	 r2[64];			  //������
	int    seckeyid;			//����
};

class RespondCodec : public Codec {
 public:
  //����
  RespondCodec();
  explicit RespondCodec(RespondMsg* msg);
  //����
  ~RespondCodec();


  //����(��д)
  int msgEncode(char** outData, int& len) override;
  //����(��д)
  int msgDecode(char* inData, int inLen) override;
  //�ͷű�������ṹ��(��д)
  int msgMemFree(void** point) override;

 private:
  //�����Ľṹ��
  RespondMsg* mRespondMsg; 

  //��ֹ�Զ����ɿ�����������ظ�ֵ�����
  DISALLOW_COPY_AND_ASSIGN(RespondCodec);
};

#endif
