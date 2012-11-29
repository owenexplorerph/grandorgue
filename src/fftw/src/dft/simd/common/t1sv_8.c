/*
 * Copyright (c) 2003, 2007-11 Matteo Frigo
 * Copyright (c) 2003, 2007-11 Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Sat Apr 28 11:02:20 EDT 2012 */

#include "codelet-dft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_twiddle.native -fma -reorder-insns -schedule-for-pipeline -simd -compact -variables 4 -pipeline-latency 8 -n 8 -name t1sv_8 -include ts.h */

/*
 * This function contains 66 FP additions, 36 FP multiplications,
 * (or, 44 additions, 14 multiplications, 22 fused multiply/add),
 * 59 stack variables, 1 constants, and 32 memory accesses
 */
#include "ts.h"

static void t1sv_8(R *ri, R *ii, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DVK(KP707106781, +0.707106781186547524400844362104849039284835938);
     {
	  INT m;
	  for (m = mb, W = W + (mb * 14); m < me; m = m + (2 * VL), ri = ri + ((2 * VL) * ms), ii = ii + ((2 * VL) * ms), W = W + ((2 * VL) * 14), MAKE_VOLATILE_STRIDE(rs)) {
	       V T1, T1m, T1l, T7, TS, Tk, TQ, Te, To, Tr, Tu, T14, TF, Tx, T16;
	       V TL, Tt, TW, Tp, Tq, Tw;
	       {
		    V T3, T6, T2, T5;
		    T1 = LD(&(ri[0]), ms, &(ri[0]));
		    T1m = LD(&(ii[0]), ms, &(ii[0]));
		    T3 = LD(&(ri[WS(rs, 4)]), ms, &(ri[0]));
		    T6 = LD(&(ii[WS(rs, 4)]), ms, &(ii[0]));
		    T2 = LDW(&(W[TWVL * 6]));
		    T5 = LDW(&(W[TWVL * 7]));
		    {
			 V Tg, Tj, Ti, Ta, Td, T1k, T4, T9, Tc, TR, Th, Tf;
			 Tg = LD(&(ri[WS(rs, 6)]), ms, &(ri[0]));
			 Tj = LD(&(ii[WS(rs, 6)]), ms, &(ii[0]));
			 Tf = LDW(&(W[TWVL * 10]));
			 Ti = LDW(&(W[TWVL * 11]));
			 Ta = LD(&(ri[WS(rs, 2)]), ms, &(ri[0]));
			 Td = LD(&(ii[WS(rs, 2)]), ms, &(ii[0]));
			 T1k = VMUL(T2, T6);
			 T4 = VMUL(T2, T3);
			 T9 = LDW(&(W[TWVL * 2]));
			 Tc = LDW(&(W[TWVL * 3]));
			 TR = VMUL(Tf, Tj);
			 Th = VMUL(Tf, Tg);
			 {
			      V TB, TE, TH, TK, TG, TD, TJ, T13, TC, TA, TP, Tb, T15, TI, Tn;
			      TB = LD(&(ri[WS(rs, 7)]), ms, &(ri[WS(rs, 1)]));
			      TE = LD(&(ii[WS(rs, 7)]), ms, &(ii[WS(rs, 1)]));
			      T1l = VFNMS(T5, T3, T1k);
			      T7 = VFMA(T5, T6, T4);
			      TP = VMUL(T9, Td);
			      Tb = VMUL(T9, Ta);
			      TS = VFNMS(Ti, Tg, TR);
			      Tk = VFMA(Ti, Tj, Th);
			      TA = LDW(&(W[TWVL * 12]));
			      TH = LD(&(ri[WS(rs, 3)]), ms, &(ri[WS(rs, 1)]));
			      TK = LD(&(ii[WS(rs, 3)]), ms, &(ii[WS(rs, 1)]));
			      TG = LDW(&(W[TWVL * 4]));
			      TQ = VFNMS(Tc, Ta, TP);
			      Te = VFMA(Tc, Td, Tb);
			      TD = LDW(&(W[TWVL * 13]));
			      TJ = LDW(&(W[TWVL * 5]));
			      T13 = VMUL(TA, TE);
			      TC = VMUL(TA, TB);
			      To = LD(&(ri[WS(rs, 1)]), ms, &(ri[WS(rs, 1)]));
			      T15 = VMUL(TG, TK);
			      TI = VMUL(TG, TH);
			      Tr = LD(&(ii[WS(rs, 1)]), ms, &(ii[WS(rs, 1)]));
			      Tn = LDW(&(W[0]));
			      Tu = LD(&(ri[WS(rs, 5)]), ms, &(ri[WS(rs, 1)]));
			      T14 = VFNMS(TD, TB, T13);
			      TF = VFMA(TD, TE, TC);
			      Tx = LD(&(ii[WS(rs, 5)]), ms, &(ii[WS(rs, 1)]));
			      T16 = VFNMS(TJ, TH, T15);
			      TL = VFMA(TJ, TK, TI);
			      Tt = LDW(&(W[TWVL * 8]));
			      TW = VMUL(Tn, Tr);
			      Tp = VMUL(Tn, To);
			      Tq = LDW(&(W[TWVL * 1]));
			      Tw = LDW(&(W[TWVL * 9]));
			 }
		    }
	       }
	       {
		    V T8, T1g, TM, T1j, TX, Ts, T1n, T1r, T1s, Tl, T1c, T18, TZ, Ty, T1a;
		    V TU;
		    {
			 V TO, T17, T12, TY, Tv, TT;
			 T8 = VADD(T1, T7);
			 TO = VSUB(T1, T7);
			 T17 = VSUB(T14, T16);
			 T1g = VADD(T14, T16);
			 TM = VADD(TF, TL);
			 T12 = VSUB(TF, TL);
			 TY = VMUL(Tt, Tx);
			 Tv = VMUL(Tt, Tu);
			 TT = VSUB(TQ, TS);
			 T1j = VADD(TQ, TS);
			 TX = VFNMS(Tq, To, TW);
			 Ts = VFMA(Tq, Tr, Tp);
			 T1n = VADD(T1l, T1m);
			 T1r = VSUB(T1m, T1l);
			 T1s = VSUB(Te, Tk);
			 Tl = VADD(Te, Tk);
			 T1c = VADD(T12, T17);
			 T18 = VSUB(T12, T17);
			 TZ = VFNMS(Tw, Tu, TY);
			 Ty = VFMA(Tw, Tx, Tv);
			 T1a = VSUB(TO, TT);
			 TU = VADD(TO, TT);
		    }
		    {
			 V T1v, T1t, Tm, T1e, T1o, T1q, TN, T1p, T1d, T1u, T19, T1w, T1i, T1h;
			 {
			      V T10, T1f, Tz, TV, T11, T1b;
			      T1v = VADD(T1s, T1r);
			      T1t = VSUB(T1r, T1s);
			      T10 = VSUB(TX, TZ);
			      T1f = VADD(TX, TZ);
			      Tz = VADD(Ts, Ty);
			      TV = VSUB(Ts, Ty);
			      T11 = VADD(TV, T10);
			      T1b = VSUB(T10, TV);
			      Tm = VADD(T8, Tl);
			      T1e = VSUB(T8, Tl);
			      T1o = VADD(T1j, T1n);
			      T1q = VSUB(T1n, T1j);
			      TN = VADD(Tz, TM);
			      T1p = VSUB(TM, Tz);
			      T1d = VSUB(T1b, T1c);
			      T1u = VADD(T1b, T1c);
			      T19 = VADD(T11, T18);
			      T1w = VSUB(T18, T11);
			      T1i = VADD(T1f, T1g);
			      T1h = VSUB(T1f, T1g);
			 }
			 ST(&(ii[WS(rs, 6)]), VSUB(T1q, T1p), ms, &(ii[0]));
			 ST(&(ri[0]), VADD(Tm, TN), ms, &(ri[0]));
			 ST(&(ri[WS(rs, 4)]), VSUB(Tm, TN), ms, &(ri[0]));
			 ST(&(ii[WS(rs, 1)]), VFMA(LDK(KP707106781), T1u, T1t), ms, &(ii[WS(rs, 1)]));
			 ST(&(ii[WS(rs, 5)]), VFNMS(LDK(KP707106781), T1u, T1t), ms, &(ii[WS(rs, 1)]));
			 ST(&(ri[WS(rs, 3)]), VFMA(LDK(KP707106781), T1d, T1a), ms, &(ri[WS(rs, 1)]));
			 ST(&(ri[WS(rs, 7)]), VFNMS(LDK(KP707106781), T1d, T1a), ms, &(ri[WS(rs, 1)]));
			 ST(&(ii[WS(rs, 3)]), VFMA(LDK(KP707106781), T1w, T1v), ms, &(ii[WS(rs, 1)]));
			 ST(&(ii[WS(rs, 7)]), VFNMS(LDK(KP707106781), T1w, T1v), ms, &(ii[WS(rs, 1)]));
			 ST(&(ri[WS(rs, 1)]), VFMA(LDK(KP707106781), T19, TU), ms, &(ri[WS(rs, 1)]));
			 ST(&(ri[WS(rs, 5)]), VFNMS(LDK(KP707106781), T19, TU), ms, &(ri[WS(rs, 1)]));
			 ST(&(ri[WS(rs, 6)]), VSUB(T1e, T1h), ms, &(ri[0]));
			 ST(&(ii[0]), VADD(T1i, T1o), ms, &(ii[0]));
			 ST(&(ii[WS(rs, 4)]), VSUB(T1o, T1i), ms, &(ii[0]));
			 ST(&(ri[WS(rs, 2)]), VADD(T1e, T1h), ms, &(ri[0]));
			 ST(&(ii[WS(rs, 2)]), VADD(T1p, T1q), ms, &(ii[0]));
		    }
	       }
	  }
     }
     VLEAVE();
}

static const tw_instr twinstr[] = {
     VTW(0, 1),
     VTW(0, 2),
     VTW(0, 3),
     VTW(0, 4),
     VTW(0, 5),
     VTW(0, 6),
     VTW(0, 7),
     {TW_NEXT, (2 * VL), 0}
};

static const ct_desc desc = { 8, XSIMD_STRING("t1sv_8"), twinstr, &GENUS, {44, 14, 22, 0}, 0, 0, 0 };

void XSIMD(codelet_t1sv_8) (planner *p) {
     X(kdft_dit_register) (p, t1sv_8, &desc);
}
#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_twiddle.native -simd -compact -variables 4 -pipeline-latency 8 -n 8 -name t1sv_8 -include ts.h */

/*
 * This function contains 66 FP additions, 32 FP multiplications,
 * (or, 52 additions, 18 multiplications, 14 fused multiply/add),
 * 28 stack variables, 1 constants, and 32 memory accesses
 */
#include "ts.h"

static void t1sv_8(R *ri, R *ii, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DVK(KP707106781, +0.707106781186547524400844362104849039284835938);
     {
	  INT m;
	  for (m = mb, W = W + (mb * 14); m < me; m = m + (2 * VL), ri = ri + ((2 * VL) * ms), ii = ii + ((2 * VL) * ms), W = W + ((2 * VL) * 14), MAKE_VOLATILE_STRIDE(rs)) {
	       V T7, T1e, TH, T19, TF, T13, TR, TU, Ti, T1f, TK, T16, Tu, T12, TM;
	       V TP;
	       {
		    V T1, T18, T6, T17;
		    T1 = LD(&(ri[0]), ms, &(ri[0]));
		    T18 = LD(&(ii[0]), ms, &(ii[0]));
		    {
			 V T3, T5, T2, T4;
			 T3 = LD(&(ri[WS(rs, 4)]), ms, &(ri[0]));
			 T5 = LD(&(ii[WS(rs, 4)]), ms, &(ii[0]));
			 T2 = LDW(&(W[TWVL * 6]));
			 T4 = LDW(&(W[TWVL * 7]));
			 T6 = VFMA(T2, T3, VMUL(T4, T5));
			 T17 = VFNMS(T4, T3, VMUL(T2, T5));
		    }
		    T7 = VADD(T1, T6);
		    T1e = VSUB(T18, T17);
		    TH = VSUB(T1, T6);
		    T19 = VADD(T17, T18);
	       }
	       {
		    V Tz, TS, TE, TT;
		    {
			 V Tw, Ty, Tv, Tx;
			 Tw = LD(&(ri[WS(rs, 7)]), ms, &(ri[WS(rs, 1)]));
			 Ty = LD(&(ii[WS(rs, 7)]), ms, &(ii[WS(rs, 1)]));
			 Tv = LDW(&(W[TWVL * 12]));
			 Tx = LDW(&(W[TWVL * 13]));
			 Tz = VFMA(Tv, Tw, VMUL(Tx, Ty));
			 TS = VFNMS(Tx, Tw, VMUL(Tv, Ty));
		    }
		    {
			 V TB, TD, TA, TC;
			 TB = LD(&(ri[WS(rs, 3)]), ms, &(ri[WS(rs, 1)]));
			 TD = LD(&(ii[WS(rs, 3)]), ms, &(ii[WS(rs, 1)]));
			 TA = LDW(&(W[TWVL * 4]));
			 TC = LDW(&(W[TWVL * 5]));
			 TE = VFMA(TA, TB, VMUL(TC, TD));
			 TT = VFNMS(TC, TB, VMUL(TA, TD));
		    }
		    TF = VADD(Tz, TE);
		    T13 = VADD(TS, TT);
		    TR = VSUB(Tz, TE);
		    TU = VSUB(TS, TT);
	       }
	       {
		    V Tc, TI, Th, TJ;
		    {
			 V T9, Tb, T8, Ta;
			 T9 = LD(&(ri[WS(rs, 2)]), ms, &(ri[0]));
			 Tb = LD(&(ii[WS(rs, 2)]), ms, &(ii[0]));
			 T8 = LDW(&(W[TWVL * 2]));
			 Ta = LDW(&(W[TWVL * 3]));
			 Tc = VFMA(T8, T9, VMUL(Ta, Tb));
			 TI = VFNMS(Ta, T9, VMUL(T8, Tb));
		    }
		    {
			 V Te, Tg, Td, Tf;
			 Te = LD(&(ri[WS(rs, 6)]), ms, &(ri[0]));
			 Tg = LD(&(ii[WS(rs, 6)]), ms, &(ii[0]));
			 Td = LDW(&(W[TWVL * 10]));
			 Tf = LDW(&(W[TWVL * 11]));
			 Th = VFMA(Td, Te, VMUL(Tf, Tg));
			 TJ = VFNMS(Tf, Te, VMUL(Td, Tg));
		    }
		    Ti = VADD(Tc, Th);
		    T1f = VSUB(Tc, Th);
		    TK = VSUB(TI, TJ);
		    T16 = VADD(TI, TJ);
	       }
	       {
		    V To, TN, Tt, TO;
		    {
			 V Tl, Tn, Tk, Tm;
			 Tl = LD(&(ri[WS(rs, 1)]), ms, &(ri[WS(rs, 1)]));
			 Tn = LD(&(ii[WS(rs, 1)]), ms, &(ii[WS(rs, 1)]));
			 Tk = LDW(&(W[0]));
			 Tm = LDW(&(W[TWVL * 1]));
			 To = VFMA(Tk, Tl, VMUL(Tm, Tn));
			 TN = VFNMS(Tm, Tl, VMUL(Tk, Tn));
		    }
		    {
			 V Tq, Ts, Tp, Tr;
			 Tq = LD(&(ri[WS(rs, 5)]), ms, &(ri[WS(rs, 1)]));
			 Ts = LD(&(ii[WS(rs, 5)]), ms, &(ii[WS(rs, 1)]));
			 Tp = LDW(&(W[TWVL * 8]));
			 Tr = LDW(&(W[TWVL * 9]));
			 Tt = VFMA(Tp, Tq, VMUL(Tr, Ts));
			 TO = VFNMS(Tr, Tq, VMUL(Tp, Ts));
		    }
		    Tu = VADD(To, Tt);
		    T12 = VADD(TN, TO);
		    TM = VSUB(To, Tt);
		    TP = VSUB(TN, TO);
	       }
	       {
		    V Tj, TG, T1b, T1c;
		    Tj = VADD(T7, Ti);
		    TG = VADD(Tu, TF);
		    ST(&(ri[WS(rs, 4)]), VSUB(Tj, TG), ms, &(ri[0]));
		    ST(&(ri[0]), VADD(Tj, TG), ms, &(ri[0]));
		    {
			 V T15, T1a, T11, T14;
			 T15 = VADD(T12, T13);
			 T1a = VADD(T16, T19);
			 ST(&(ii[0]), VADD(T15, T1a), ms, &(ii[0]));
			 ST(&(ii[WS(rs, 4)]), VSUB(T1a, T15), ms, &(ii[0]));
			 T11 = VSUB(T7, Ti);
			 T14 = VSUB(T12, T13);
			 ST(&(ri[WS(rs, 6)]), VSUB(T11, T14), ms, &(ri[0]));
			 ST(&(ri[WS(rs, 2)]), VADD(T11, T14), ms, &(ri[0]));
		    }
		    T1b = VSUB(TF, Tu);
		    T1c = VSUB(T19, T16);
		    ST(&(ii[WS(rs, 2)]), VADD(T1b, T1c), ms, &(ii[0]));
		    ST(&(ii[WS(rs, 6)]), VSUB(T1c, T1b), ms, &(ii[0]));
		    {
			 V TX, T1g, T10, T1d, TY, TZ;
			 TX = VSUB(TH, TK);
			 T1g = VSUB(T1e, T1f);
			 TY = VSUB(TP, TM);
			 TZ = VADD(TR, TU);
			 T10 = VMUL(LDK(KP707106781), VSUB(TY, TZ));
			 T1d = VMUL(LDK(KP707106781), VADD(TY, TZ));
			 ST(&(ri[WS(rs, 7)]), VSUB(TX, T10), ms, &(ri[WS(rs, 1)]));
			 ST(&(ii[WS(rs, 5)]), VSUB(T1g, T1d), ms, &(ii[WS(rs, 1)]));
			 ST(&(ri[WS(rs, 3)]), VADD(TX, T10), ms, &(ri[WS(rs, 1)]));
			 ST(&(ii[WS(rs, 1)]), VADD(T1d, T1g), ms, &(ii[WS(rs, 1)]));
		    }
		    {
			 V TL, T1i, TW, T1h, TQ, TV;
			 TL = VADD(TH, TK);
			 T1i = VADD(T1f, T1e);
			 TQ = VADD(TM, TP);
			 TV = VSUB(TR, TU);
			 TW = VMUL(LDK(KP707106781), VADD(TQ, TV));
			 T1h = VMUL(LDK(KP707106781), VSUB(TV, TQ));
			 ST(&(ri[WS(rs, 5)]), VSUB(TL, TW), ms, &(ri[WS(rs, 1)]));
			 ST(&(ii[WS(rs, 7)]), VSUB(T1i, T1h), ms, &(ii[WS(rs, 1)]));
			 ST(&(ri[WS(rs, 1)]), VADD(TL, TW), ms, &(ri[WS(rs, 1)]));
			 ST(&(ii[WS(rs, 3)]), VADD(T1h, T1i), ms, &(ii[WS(rs, 1)]));
		    }
	       }
	  }
     }
     VLEAVE();
}

static const tw_instr twinstr[] = {
     VTW(0, 1),
     VTW(0, 2),
     VTW(0, 3),
     VTW(0, 4),
     VTW(0, 5),
     VTW(0, 6),
     VTW(0, 7),
     {TW_NEXT, (2 * VL), 0}
};

static const ct_desc desc = { 8, XSIMD_STRING("t1sv_8"), twinstr, &GENUS, {52, 18, 14, 0}, 0, 0, 0 };

void XSIMD(codelet_t1sv_8) (planner *p) {
     X(kdft_dit_register) (p, t1sv_8, &desc);
}
#endif				/* HAVE_FMA */
