#ifndef __02_CODEC_H__
#define __02_CODEC_H__
#define DISALLOW_COPY_AND_ASSIGN(Typename) \
        Typename(const Typename&); \
        void operator=(const Typename&)
#include "SequenceASN1.h"

//����ģʽ����
class Codec : public SequenceASN1 {
 public:
  //���캯��
  Codec();
  //��������
  ~Codec();

  //����(�麯��)
  virtual int msgEncode(char** outData, int& len);
  //����(�麯��)
  virtual int msgDecode(char* inData, int inLen);
  //�ڴ��ͷ�(�麯��)
  virtual int msgMemFree(void** point);

 private:
  //��ֹ�Զ����ɿ�����������ظ��������
  DISALLOW_COPY_AND_ASSIGN(Codec);
};

#endif
