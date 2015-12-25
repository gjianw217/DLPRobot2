#ifndef DLP_PTZ_CFOCUSPART_H_
#define DLP_PTZ_CFOCUSPART_H_

#include "iparts.h"
class CFocusPart:public IParts
{
public:
    explicit CFocusPart(PCDataMapping datamapping);
    ~CFocusPart();
    virtual void Init();

protected:

private:
    void parseCoderAttr(DLPEncoderAttr &attr);
    void parseMotorAttr(DLPMotorAttr &attr);
};

#endif // DLP_PTZ_CFOCUSPART_H_
