#include "DSPLib.h"

#include "bass.h"

DSPLIB_DATA(bass,4)
msp_biquad_df1_q15_coeffs bass[2] = {
    {
        .b0     = _Q15(+0.811901),
        .b1By2  = _Q15(-1.623802/2),
        .b2     = _Q15(+0.811901),
        .a1By2  = _Q15(+1.959020/2),
        .a2     = _Q15(-0.960822)
    },
    {
        .b0     = _Q15(+0.000411),
        .b1By2  = _Q15(+0.000822/2),
        .b2     = _Q15(+0.000411),
        .a1By2  = _Q15(+1.987517/2),
        .a2     = _Q15(-0.987692)
    },
};
