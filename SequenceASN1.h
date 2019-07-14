#ifndef __02_SEQUENCEASN1_H__
#define __02_SEQUENCEASN1_H__
#define DISALLOW_COPY_AND_ASSIGN(Typename) \
        Typename(const Typename&); \
        void operator=(const Typename&)
#include "BaseASN1.h"
#include "ItcastLog.h"

//���󻯵�ASN1������
class SequenceASN1 : public BaseASN1 {
public:
 //���캯��
SequenceASN1();
 //��������
 virtual ~SequenceASN1();

 //����ͷ���
 int writeHeadNode(int iValue); //����
 int writeHeadNode(char* sValue, int len); //�ַ���

 //������ͨ�ڵ�
 int writeNextNode(int iValue); //����
 int writeNextNode(char* sValue, int len);  //�ַ���
 
 //����ͷ���
 int readHeadNode(int& iValue); //����
 int readHeadNode(char* sValue);  //�ַ���

 //������ͨ�ڵ�
 int readNextNode(int& iValue); //����
 int readNextNode(char* sValue); //�ַ���

 //��������
 int packSequence(char** outData, int& outLen);
 //��������
 int unpackSequence(char* inData, int inLen);

 //�ͷ�����
 void freeSequnce(ITCAST_ANYBUF* node = NULL);

 private:
  ITCAST_ANYBUF* m_header; //ͷ�ڵ�
  ITCAST_ANYBUF* m_next; //β�ڵ�
  ITCAST_ANYBUF* m_temp; //��ʱ�ڵ�
  ItcastLog LogASN1;  //��־��

  //��ֹ�Զ��ϳɿ�����������ظ�ֵ�����
  DISALLOW_COPY_AND_ASSIGN(SequenceASN1);
};


#endif

