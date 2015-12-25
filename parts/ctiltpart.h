#ifndef DLP_PTZ_CTILTPART_H_
#define DLP_PTZ_CTILTPART_H_

#include "iparts.h"
class CTiltPart:public IParts
{
public:
    explicit CTiltPart(PCDataMapping datamapping);
    ~CTiltPart();
    virtual void Init();
private:
private:
    void parseCoderAttr(DLPEncoderAttr &attr);
    void parseMotorAttr(DLPMotorAttr &attr);
};

#endif //DLP_PTZ_CTILTPART_H_
