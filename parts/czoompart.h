
#include "iparts.h"

#ifndef DLP_PTZ_CZOOMPART_H_
#define DLP_PTZ_CZOOMPART_H_
class CZoomPart:public IParts
{
public:
    explicit CZoomPart(PCDataMapping datamapping);
    ~CZoomPart();
    virtual void Init();
private:
    void parseCoderAttr(DLPEncoderAttr &attr);
    void parseMotorAttr(DLPMotorAttr &attr);

};

#endif //DLP_PTZ_CZOOMPART_H_
