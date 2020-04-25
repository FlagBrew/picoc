/*  */
#include <math.h>

#include "interpreter.h"

static double M_EValue        = 2.7182818284590452354;  /* e */
static double M_LOG2EValue    = 1.4426950408889634074;  /* log_2 e */
static double M_LOG10EValue   = 0.43429448190325182765; /* log_10 e */
static double M_LN2Value      = 0.69314718055994530942; /* log_e 2 */
static double M_LN10Value     = 2.30258509299404568402; /* log_e 10 */
static double M_PIValue       = 3.14159265358979323846; /* pi */
static double M_PI_2Value     = 1.57079632679489661923; /* pi/2 */
static double M_PI_4Value     = 0.78539816339744830962; /* pi/4 */
static double M_1_PIValue     = 0.31830988618379067154; /* 1/pi */
static double M_2_PIValue     = 0.63661977236758134308; /* 2/pi */
static double M_2_SQRTPIValue = 1.12837916709551257390; /* 2/sqrt(pi) */
static double M_SQRT2Value    = 1.41421356237309504880; /* sqrt(2) */
static double M_SQRT1_2Value  = 0.70710678118654752440; /* 1/sqrt(2) */

void MathSin(struct ParseState* Parser, struct Value* ReturnValue, struct Value** Param, int NumArgs)
{
    ReturnValue->Val->Double = sin(Param[0]->Val->Double);
}

void MathCos(struct ParseState* Parser, struct Value* ReturnValue, struct Value** Param, int NumArgs)
{
    ReturnValue->Val->Double = cos(Param[0]->Val->Double);
}

void MathTan(struct ParseState* Parser, struct Value* ReturnValue, struct Value** Param, int NumArgs)
{
    ReturnValue->Val->Double = tan(Param[0]->Val->Double);
}

void MathAsin(struct ParseState* Parser, struct Value* ReturnValue, struct Value** Param, int NumArgs)
{
    ReturnValue->Val->Double = asin(Param[0]->Val->Double);
}

void MathAcos(struct ParseState* Parser, struct Value* ReturnValue, struct Value** Param, int NumArgs)
{
    ReturnValue->Val->Double = acos(Param[0]->Val->Double);
}

void MathAtan(struct ParseState* Parser, struct Value* ReturnValue, struct Value** Param, int NumArgs)
{
    ReturnValue->Val->Double = atan(Param[0]->Val->Double);
}

void MathAtan2(struct ParseState* Parser, struct Value* ReturnValue, struct Value** Param, int NumArgs)
{
    ReturnValue->Val->Double = atan2(Param[0]->Val->Double, Param[1]->Val->Double);
}

void MathSinh(struct ParseState* Parser, struct Value* ReturnValue, struct Value** Param, int NumArgs)
{
    ReturnValue->Val->Double = sinh(Param[0]->Val->Double);
}

void MathCosh(struct ParseState* Parser, struct Value* ReturnValue, struct Value** Param, int NumArgs)
{
    ReturnValue->Val->Double = cosh(Param[0]->Val->Double);
}

void MathTanh(struct ParseState* Parser, struct Value* ReturnValue, struct Value** Param, int NumArgs)
{
    ReturnValue->Val->Double = tanh(Param[0]->Val->Double);
}

void MathExp(struct ParseState* Parser, struct Value* ReturnValue, struct Value** Param, int NumArgs)
{
    ReturnValue->Val->Double = exp(Param[0]->Val->Double);
}

void MathFabs(struct ParseState* Parser, struct Value* ReturnValue, struct Value** Param, int NumArgs)
{
    ReturnValue->Val->Double = fabs(Param[0]->Val->Double);
}

void MathFmod(struct ParseState* Parser, struct Value* ReturnValue, struct Value** Param, int NumArgs)
{
    ReturnValue->Val->Double = fmod(Param[0]->Val->Double, Param[1]->Val->Double);
}

void MathFrexp(struct ParseState* Parser, struct Value* ReturnValue, struct Value** Param, int NumArgs)
{
    ReturnValue->Val->Double = frexp(Param[0]->Val->Double, Param[1]->Val->Pointer);
}

void MathLdexp(struct ParseState* Parser, struct Value* ReturnValue, struct Value** Param, int NumArgs)
{
    ReturnValue->Val->Double = ldexp(Param[0]->Val->Double, Param[1]->Val->Integer);
}

void MathLog(struct ParseState* Parser, struct Value* ReturnValue, struct Value** Param, int NumArgs)
{
    ReturnValue->Val->Double = log(Param[0]->Val->Double);
}

void MathLog10(struct ParseState* Parser, struct Value* ReturnValue, struct Value** Param, int NumArgs)
{
    ReturnValue->Val->Double = log10(Param[0]->Val->Double);
}

void MathModf(struct ParseState* Parser, struct Value* ReturnValue, struct Value** Param, int NumArgs)
{
    ReturnValue->Val->Double = modf(Param[0]->Val->Double, Param[0]->Val->Pointer);
}

void MathPow(struct ParseState* Parser, struct Value* ReturnValue, struct Value** Param, int NumArgs)
{
    ReturnValue->Val->Double = pow(Param[0]->Val->Double, Param[1]->Val->Double);
}

void MathSqrt(struct ParseState* Parser, struct Value* ReturnValue, struct Value** Param, int NumArgs)
{
    ReturnValue->Val->Double = sqrt(Param[0]->Val->Double);
}

void MathRound(struct ParseState* Parser, struct Value* ReturnValue, struct Value** Param, int NumArgs)
{
    /* this awkward definition of "round()" due to it being inconsistently
     * declared in math.h */
    ReturnValue->Val->Double = ceil(Param[0]->Val->Double - 0.5);
}

void MathCeil(struct ParseState* Parser, struct Value* ReturnValue, struct Value** Param, int NumArgs)
{
    ReturnValue->Val->Double = ceil(Param[0]->Val->Double);
}

void MathFloor(struct ParseState* Parser, struct Value* ReturnValue, struct Value** Param, int NumArgs)
{
    ReturnValue->Val->Double = floor(Param[0]->Val->Double);
}

/* all math.h functions */
struct LibraryFunction MathFunctions[] = {{MathAcos, "double acos(double);"}, {MathAsin, "double asin(double);"}, {MathAtan, "double atan(double);"},
    {MathAtan2, "double atan2(double, double);"}, {MathCeil, "double ceil(double);"}, {MathCos, "double cos(double);"},
    {MathCosh, "double cosh(double);"}, {MathExp, "double exp(double);"}, {MathFabs, "double fabs(double);"}, {MathFloor, "double floor(double);"},
    {MathFmod, "double fmod(double, double);"}, {MathFrexp, "double frexp(double, int *);"}, {MathLdexp, "double ldexp(double, int);"},
    {MathLog, "double log(double);"}, {MathLog10, "double log10(double);"}, {MathModf, "double modf(double, double *);"},
    {MathPow, "double pow(double,double);"}, {MathRound, "double round(double);"}, {MathSin, "double sin(double);"},
    {MathSinh, "double sinh(double);"}, {MathSqrt, "double sqrt(double);"}, {MathTan, "double tan(double);"}, {MathTanh, "double tanh(double);"},
    {NULL, NULL}};

/* creates various system-dependent definitions */
void MathSetupFunc(Picoc* pc)
{
    VariableDefinePlatformVar(pc, NULL, "M_E", &pc->DoubleType, (union AnyValue*)&M_EValue, false);
    VariableDefinePlatformVar(pc, NULL, "M_LOG2E", &pc->DoubleType, (union AnyValue*)&M_LOG2EValue, false);
    VariableDefinePlatformVar(pc, NULL, "M_LOG10E", &pc->DoubleType, (union AnyValue*)&M_LOG10EValue, false);
    VariableDefinePlatformVar(pc, NULL, "M_LN2", &pc->DoubleType, (union AnyValue*)&M_LN2Value, false);
    VariableDefinePlatformVar(pc, NULL, "M_LN10", &pc->DoubleType, (union AnyValue*)&M_LN10Value, false);
    VariableDefinePlatformVar(pc, NULL, "M_PI", &pc->DoubleType, (union AnyValue*)&M_PIValue, false);
    VariableDefinePlatformVar(pc, NULL, "M_PI_2", &pc->DoubleType, (union AnyValue*)&M_PI_2Value, false);
    VariableDefinePlatformVar(pc, NULL, "M_PI_4", &pc->DoubleType, (union AnyValue*)&M_PI_4Value, false);
    VariableDefinePlatformVar(pc, NULL, "M_1_PI", &pc->DoubleType, (union AnyValue*)&M_1_PIValue, false);
    VariableDefinePlatformVar(pc, NULL, "M_2_PI", &pc->DoubleType, (union AnyValue*)&M_2_PIValue, false);
    VariableDefinePlatformVar(pc, NULL, "M_2_SQRTPI", &pc->DoubleType, (union AnyValue*)&M_2_SQRTPIValue, false);
    VariableDefinePlatformVar(pc, NULL, "M_SQRT2", &pc->DoubleType, (union AnyValue*)&M_SQRT2Value, false);
    VariableDefinePlatformVar(pc, NULL, "M_SQRT1_2", &pc->DoubleType, (union AnyValue*)&M_SQRT1_2Value, false);
}
