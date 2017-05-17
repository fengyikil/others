#ifndef ALL_ALG_H
#define ALL_ALG_H
#include "DUTSocketLocation.h"
#include "SocketLocation.h"
#include "PocketLocation.h"
#include "DUTTrayLocation.h"
#include "TrayLocation.h"
extern int test_ex;

typedef enum _Alg{
    ALG_TEST=0,
    ALG_DUTTrayLocation,
    ALG_SocketLocation,
    ALG_DUTSocketLocation,
    ALG_PocketLocation,
    ALG_TrayLocation,

}Alg;
class allAlg
{
public:
    allAlg(void);
    bool test_exposure(Alg alg,HImage image);
    CDUTTrayLocation* alg1;
    CSocketLocation* alg2;
    CDUTSocketLocation* alg3;
    CPocketLocation* alg4;
    CTrayLocation* alg5;
};

#endif
