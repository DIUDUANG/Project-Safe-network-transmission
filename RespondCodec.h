#ifndef __02_RESPONDCODEC_H__
#define __02_RESPONDCODEC_H__
#define DISALLOW_COPY_AND_ASSIGN(Typename) \
        Typename(const Typename&) \
        void operator=(const Typename&)
#include "Codec.h"

//请求报文结构体类型
struct RespondMsg
{
  //1 密钥协商  	//2 密钥校验; 	// 3 密钥注销
  int		 rv;						//靠� 
  char	 clientId[12];	//靠靠�
  char	 serverId[12];	//靠靠�
  char	 r2[64];			  //靠靠靠
	int    seckeyid;			//靠靠
};

class RespondCodec : public Codec {
 public:
  //构造
  RespondCodec();
  explicit RespondCodec(RespondMsg* msg);
  //析构
  ~RespondCodec();


  //编码(重写)
  int msgEncode(char** outData, int& len) override;
  //解码(重写)
  int msgDecode(char* inData, int inLen) override;
  //释放报文请求结构体(重写)
  int msgMemFree(void** point) override;

 private:
  //请求报文结构体
  RespondMsg* mRespondMsg; 

  //防止自动生成拷贝构造和重载赋值运算符
  DISALLOW_COPY_AND_ASSIGN(RespondCodec);
};

#endif
