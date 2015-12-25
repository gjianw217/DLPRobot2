
#ifndef DLP_PTZ_CPANPART_H_
#define DLP_PTZ_CPANPART_H_

#include "iparts.h"

class CPanPart:public IParts
{
public:
    explicit CPanPart(PCDataMapping datamapping);
    ~CPanPart();
    virtual void Init();
private:
    void parseCoderAttr(DLPEncoderAttr &attr);
    void parseMotorAttr(DLPMotorAttr &attr);


};
#endif // DLP_PTZ_CPANPART_H_
