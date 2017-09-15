/* Generated automatically by the program `genflags'
   from the machine description file `md'.  */

#ifndef GCC_INSN_FLAGS_H
#define GCC_INSN_FLAGS_H

#define HAVE_load_pcrel_symsi ((REGNO (operands[0]) == INTVAL (operands[3])) && (TARGET_ARCH32))
#define HAVE_load_pcrel_symdi ((REGNO (operands[0]) == INTVAL (operands[3])) && (TARGET_ARCH64))
#define HAVE_movsi_lo_sum_pic (flag_pic)
#define HAVE_movsi_high_pic (flag_pic && check_pic (1))
#define HAVE_movsi_pic_gotdata_op (flag_pic && check_pic (1))
#define HAVE_seth44 (TARGET_CM_MEDMID && !flag_pic)
#define HAVE_setm44 (TARGET_CM_MEDMID && !flag_pic)
#define HAVE_setl44 (TARGET_CM_MEDMID && !flag_pic)
#define HAVE_sethh (TARGET_CM_MEDANY && !flag_pic)
#define HAVE_setlm (TARGET_CM_MEDANY && !flag_pic)
#define HAVE_sethm (TARGET_CM_MEDANY && !flag_pic)
#define HAVE_setlo (TARGET_CM_MEDANY && !flag_pic)
#define HAVE_embmedany_sethi (TARGET_CM_EMBMEDANY && !flag_pic)
#define HAVE_embmedany_losum (TARGET_CM_EMBMEDANY && !flag_pic)
#define HAVE_embmedany_brsum (TARGET_CM_EMBMEDANY && !flag_pic)
#define HAVE_embmedany_textuhi (TARGET_CM_EMBMEDANY && !flag_pic)
#define HAVE_embmedany_texthi (TARGET_CM_EMBMEDANY && !flag_pic)
#define HAVE_embmedany_textulo (TARGET_CM_EMBMEDANY && !flag_pic)
#define HAVE_embmedany_textlo (TARGET_CM_EMBMEDANY && !flag_pic)
#define HAVE_movdf_cc_v9 (TARGET_V9 && TARGET_FPU)
#define HAVE_extendsfdf2 (TARGET_FPU)
#define HAVE_truncdfsf2 (TARGET_FPU)
#define HAVE_floatsisf2 (TARGET_FPU)
#define HAVE_floatsidf2 (TARGET_FPU)
#define HAVE_floatdisf2 (TARGET_V9 && TARGET_FPU)
#define HAVE_floatdidf2 (TARGET_V9 && TARGET_FPU)
#define HAVE_fix_truncsfsi2 (TARGET_FPU)
#define HAVE_fix_truncdfsi2 (TARGET_FPU)
#define HAVE_fix_truncsfdi2 (TARGET_V9 && TARGET_FPU)
#define HAVE_fix_truncdfdi2 (TARGET_V9 && TARGET_FPU)
#define HAVE_adddi3_sp32 1
#define HAVE_uaddvdi4_sp32 1
#define HAVE_addvdi4_sp32 1
#define HAVE_addsi3 1
#define HAVE_subdi3_sp32 1
#define HAVE_usubvdi4_sp32 1
#define HAVE_subvdi4_sp32 1
#define HAVE_subsi3 1
#define HAVE_mulsi3 (TARGET_HARD_MUL)
#define HAVE_muldi3_v8plus (TARGET_V8PLUS)
#define HAVE_mulsidi3_v8plus (TARGET_V8PLUS)
#define HAVE_const_mulsidi3_v8plus (TARGET_V8PLUS)
#define HAVE_const_mulsidi3_sp32 (TARGET_HARD_MUL32)
#define HAVE_smulsi3_highpart_v8plus (TARGET_V8PLUS)
#define HAVE_const_smulsi3_highpart_v8plus (TARGET_V8PLUS)
#define HAVE_const_smulsi3_highpart (TARGET_HARD_MUL32)
#define HAVE_umulsidi3_v8plus (TARGET_V8PLUS)
#define HAVE_const_umulsidi3_sp32 (TARGET_HARD_MUL32)
#define HAVE_const_umulsidi3_v8plus (TARGET_V8PLUS)
#define HAVE_umulsi3_highpart_v8plus (TARGET_V8PLUS)
#define HAVE_const_umulsi3_highpart_v8plus (TARGET_V8PLUS)
#define HAVE_const_umulsi3_highpart (TARGET_HARD_MUL32)
#define HAVE_umulxhi_v8plus (TARGET_VIS3 && TARGET_ARCH32)
#define HAVE_xmulx_v8plus (TARGET_VIS3 && TARGET_ARCH32)
#define HAVE_xmulxhi_v8plus (TARGET_VIS3 && TARGET_ARCH32)
#define HAVE_divsi3_sp32 ((TARGET_V8 || TARGET_DEPRECATED_V8_INSNS) && TARGET_ARCH32)
#define HAVE_udivsi3_sp32 ((TARGET_V8 || TARGET_DEPRECATED_V8_INSNS) && TARGET_ARCH32)
#define HAVE_andsi3 1
#define HAVE_iorsi3 1
#define HAVE_xorsi3 1
#define HAVE_negdi2_sp32 1
#define HAVE_unegvdi3_sp32 1
#define HAVE_negvdi3_sp32 1
#define HAVE_negsi2 1
#define HAVE_one_cmplsi2 1
#define HAVE_adddf3 (TARGET_FPU)
#define HAVE_addsf3 (TARGET_FPU)
#define HAVE_subdf3 (TARGET_FPU)
#define HAVE_subsf3 (TARGET_FPU)
#define HAVE_muldf3 (TARGET_FPU)
#define HAVE_mulsf3 (TARGET_FPU)
#define HAVE_fmadf4 (TARGET_FMAF)
#define HAVE_fmsdf4 (TARGET_FMAF)
#define HAVE_fmasf4 (TARGET_FMAF)
#define HAVE_fmssf4 (TARGET_FMAF)
#define HAVE_divsf3 (TARGET_FPU && !sparc_fix_ut699)
#define HAVE_negsf2 (TARGET_FPU)
#define HAVE_abssf2 (TARGET_FPU)
#define HAVE_sqrtsf2 (TARGET_FPU && !sparc_fix_ut699)
#define HAVE_ashlsi3 1
#define HAVE_ashldi3_v8plus (TARGET_V8PLUS)
#define HAVE_ashrsi3 1
#define HAVE_ashrdi3_v8plus (TARGET_V8PLUS)
#define HAVE_lshrsi3 1
#define HAVE_lshrdi3_v8plus (TARGET_V8PLUS)
#define HAVE_window_save (!TARGET_FLAT)
#define HAVE_eh_return_internal 1
#define HAVE_blockage 1
#define HAVE_probe_stack_rangesi 1
#define HAVE_update_return 1
#define HAVE_nop 1
#define HAVE_flush_register_windows 1
#define HAVE_flushsi 1
#define HAVE_ldfsr (TARGET_FPU)
#define HAVE_stfsr (TARGET_FPU)
#define HAVE_popcountdi_v8plus (TARGET_POPC && TARGET_ARCH32)
#define HAVE_popcountsi_v8plus (TARGET_POPC && TARGET_ARCH32)
#define HAVE_clzdi_v8plus (TARGET_VIS3 && TARGET_ARCH32)
#define HAVE_clzsi_v8plus (TARGET_VIS3 && TARGET_ARCH32)
#define HAVE_prefetch_64 1
#define HAVE_prefetch_32 1
#define HAVE_trap 1
#define HAVE_tgd_hi22 1
#define HAVE_tgd_lo10 1
#define HAVE_tgd_add32 1
#define HAVE_tgd_call32 1
#define HAVE_tldm_hi22 1
#define HAVE_tldm_lo10 1
#define HAVE_tldm_add32 1
#define HAVE_tldm_call32 1
#define HAVE_tldo_hix22 1
#define HAVE_tldo_lox10 1
#define HAVE_tldo_add32 1
#define HAVE_tie_hi22 1
#define HAVE_tie_lo10 1
#define HAVE_tie_ld32 1
#define HAVE_tle_hix22_sp32 1
#define HAVE_tle_lox10_sp32 1
#define HAVE_stack_protect_setsi 1
#define HAVE_stack_protect_testsi 1
#define HAVE_addv1si3 (TARGET_VIS)
#define HAVE_subv1si3 (TARGET_VIS)
#define HAVE_addv2si3 (TARGET_VIS)
#define HAVE_subv2si3 (TARGET_VIS)
#define HAVE_addv2hi3 (TARGET_VIS)
#define HAVE_subv2hi3 (TARGET_VIS)
#define HAVE_addv4hi3 (TARGET_VIS)
#define HAVE_subv4hi3 (TARGET_VIS)
#define HAVE_iorv1si3 (TARGET_VIS)
#define HAVE_andv1si3 (TARGET_VIS)
#define HAVE_xorv1si3 (TARGET_VIS)
#define HAVE_iorv2hi3 (TARGET_VIS)
#define HAVE_andv2hi3 (TARGET_VIS)
#define HAVE_xorv2hi3 (TARGET_VIS)
#define HAVE_iorv4qi3 (TARGET_VIS)
#define HAVE_andv4qi3 (TARGET_VIS)
#define HAVE_xorv4qi3 (TARGET_VIS)
#define HAVE_iorv1di3 (TARGET_VIS)
#define HAVE_andv1di3 (TARGET_VIS)
#define HAVE_xorv1di3 (TARGET_VIS)
#define HAVE_iorv2si3 (TARGET_VIS)
#define HAVE_andv2si3 (TARGET_VIS)
#define HAVE_xorv2si3 (TARGET_VIS)
#define HAVE_iorv4hi3 (TARGET_VIS)
#define HAVE_andv4hi3 (TARGET_VIS)
#define HAVE_xorv4hi3 (TARGET_VIS)
#define HAVE_iorv8qi3 (TARGET_VIS)
#define HAVE_andv8qi3 (TARGET_VIS)
#define HAVE_xorv8qi3 (TARGET_VIS)
#define HAVE_one_cmplv1si2 (TARGET_VIS)
#define HAVE_one_cmplv2hi2 (TARGET_VIS)
#define HAVE_one_cmplv4qi2 (TARGET_VIS)
#define HAVE_one_cmplv1di2 (TARGET_VIS)
#define HAVE_one_cmplv2si2 (TARGET_VIS)
#define HAVE_one_cmplv4hi2 (TARGET_VIS)
#define HAVE_one_cmplv8qi2 (TARGET_VIS)
#define HAVE_fpack16_vis (TARGET_VIS)
#define HAVE_fpackfix_vis (TARGET_VIS)
#define HAVE_fpack32_vis (TARGET_VIS)
#define HAVE_fexpand_vis (TARGET_VIS)
#define HAVE_fpmerge_vis (TARGET_VIS)
#define HAVE_fmul8x16_vis (TARGET_VIS)
#define HAVE_fmul8x16au_vis (TARGET_VIS)
#define HAVE_fmul8x16al_vis (TARGET_VIS)
#define HAVE_fmul8sux16_vis (TARGET_VIS)
#define HAVE_fmul8ulx16_vis (TARGET_VIS)
#define HAVE_fmuld8sux16_vis (TARGET_VIS)
#define HAVE_fmuld8ulx16_vis (TARGET_VIS)
#define HAVE_wrgsr_v8plus (TARGET_VIS && TARGET_ARCH32)
#define HAVE_rdgsr_v8plus (TARGET_VIS && TARGET_ARCH32)
#define HAVE_faligndatav1di_vis (TARGET_VIS)
#define HAVE_faligndatav2si_vis (TARGET_VIS)
#define HAVE_faligndatav4hi_vis (TARGET_VIS)
#define HAVE_faligndatav8qi_vis (TARGET_VIS)
#define HAVE_alignaddrsi_vis (TARGET_VIS)
#define HAVE_alignaddrdi_vis (TARGET_VIS)
#define HAVE_alignaddrlsi_vis (TARGET_VIS)
#define HAVE_alignaddrldi_vis (TARGET_VIS)
#define HAVE_pdist_vis (TARGET_VIS)
#define HAVE_edge8si_vis ((TARGET_VIS) && (TARGET_ARCH32))
#define HAVE_edge8lsi_vis ((TARGET_VIS) && (TARGET_ARCH32))
#define HAVE_edge16si_vis ((TARGET_VIS) && (TARGET_ARCH32))
#define HAVE_edge16lsi_vis ((TARGET_VIS) && (TARGET_ARCH32))
#define HAVE_edge32si_vis ((TARGET_VIS) && (TARGET_ARCH32))
#define HAVE_edge32lsi_vis ((TARGET_VIS) && (TARGET_ARCH32))
#define HAVE_fcmple16si_vis ((TARGET_VIS) && (TARGET_ARCH32))
#define HAVE_fcmpne16si_vis ((TARGET_VIS) && (TARGET_ARCH32))
#define HAVE_fcmpgt16si_vis ((TARGET_VIS) && (TARGET_ARCH32))
#define HAVE_fcmpeq16si_vis ((TARGET_VIS) && (TARGET_ARCH32))
#define HAVE_fcmple32si_vis ((TARGET_VIS) && (TARGET_ARCH32))
#define HAVE_fcmpne32si_vis ((TARGET_VIS) && (TARGET_ARCH32))
#define HAVE_fcmpgt32si_vis ((TARGET_VIS) && (TARGET_ARCH32))
#define HAVE_fcmpeq32si_vis ((TARGET_VIS) && (TARGET_ARCH32))
#define HAVE_fpcmple8si_vis ((TARGET_VIS4) && (TARGET_ARCH32))
#define HAVE_fpcmpne8si_vis ((TARGET_VIS4) && (TARGET_ARCH32))
#define HAVE_fpcmpgt8si_vis ((TARGET_VIS4) && (TARGET_ARCH32))
#define HAVE_fpcmpeq8si_vis ((TARGET_VIS4) && (TARGET_ARCH32))
#define HAVE_array8si_vis ((TARGET_VIS) && (TARGET_ARCH32))
#define HAVE_array16si_vis ((TARGET_VIS) && (TARGET_ARCH32))
#define HAVE_array32si_vis ((TARGET_VIS) && (TARGET_ARCH32))
#define HAVE_bmasksi_vis (TARGET_VIS2)
#define HAVE_bshufflev1di_vis (TARGET_VIS2)
#define HAVE_bshufflev2si_vis (TARGET_VIS2)
#define HAVE_bshufflev4hi_vis (TARGET_VIS2)
#define HAVE_bshufflev8qi_vis (TARGET_VIS2)
#define HAVE_edge8nsi_vis ((TARGET_VIS2) && (TARGET_ARCH32))
#define HAVE_edge8lnsi_vis ((TARGET_VIS2) && (TARGET_ARCH32))
#define HAVE_edge16nsi_vis ((TARGET_VIS2) && (TARGET_ARCH32))
#define HAVE_edge16lnsi_vis ((TARGET_VIS2) && (TARGET_ARCH32))
#define HAVE_edge32nsi_vis ((TARGET_VIS2) && (TARGET_ARCH32))
#define HAVE_edge32lnsi_vis ((TARGET_VIS2) && (TARGET_ARCH32))
#define HAVE_cmask8si_vis ((TARGET_VIS3) && (TARGET_ARCH32))
#define HAVE_cmask16si_vis ((TARGET_VIS3) && (TARGET_ARCH32))
#define HAVE_cmask32si_vis ((TARGET_VIS3) && (TARGET_ARCH32))
#define HAVE_fchksm16_vis (TARGET_VIS3)
#define HAVE_vashlv4hi3 (TARGET_VIS3)
#define HAVE_vssashlv4hi3 (TARGET_VIS3)
#define HAVE_vlshrv4hi3 (TARGET_VIS3)
#define HAVE_vashrv4hi3 (TARGET_VIS3)
#define HAVE_vashlv2si3 (TARGET_VIS3)
#define HAVE_vssashlv2si3 (TARGET_VIS3)
#define HAVE_vlshrv2si3 (TARGET_VIS3)
#define HAVE_vashrv2si3 (TARGET_VIS3)
#define HAVE_pdistnsi_vis ((TARGET_VIS3) && (TARGET_ARCH32))
#define HAVE_fmean16_vis (TARGET_VIS3)
#define HAVE_fpadd64_vis (TARGET_VIS3)
#define HAVE_fpsub64_vis (TARGET_VIS3)
#define HAVE_addv8qi3 (TARGET_VIS4)
#define HAVE_subv8qi3 (TARGET_VIS4)
#define HAVE_ssaddv4hi3 (TARGET_VIS3)
#define HAVE_sssubv4hi3 (TARGET_VIS3)
#define HAVE_ssaddv2si3 (TARGET_VIS3)
#define HAVE_sssubv2si3 (TARGET_VIS3)
#define HAVE_ssaddv2hi3 (TARGET_VIS3)
#define HAVE_sssubv2hi3 (TARGET_VIS3)
#define HAVE_ssaddv1si3 (TARGET_VIS3)
#define HAVE_sssubv1si3 (TARGET_VIS3)
#define HAVE_minv8qi3 (TARGET_VIS4)
#define HAVE_maxv8qi3 (TARGET_VIS4)
#define HAVE_minv4hi3 (TARGET_VIS4)
#define HAVE_maxv4hi3 (TARGET_VIS4)
#define HAVE_minv2si3 (TARGET_VIS4)
#define HAVE_maxv2si3 (TARGET_VIS4)
#define HAVE_minuv8qi3 (TARGET_VIS4)
#define HAVE_maxuv8qi3 (TARGET_VIS4)
#define HAVE_minuv4hi3 (TARGET_VIS4)
#define HAVE_maxuv4hi3 (TARGET_VIS4)
#define HAVE_minuv2si3 (TARGET_VIS4)
#define HAVE_maxuv2si3 (TARGET_VIS4)
#define HAVE_ssaddv8qi3 (TARGET_VIS4)
#define HAVE_sssubv8qi3 (TARGET_VIS4)
#define HAVE_usaddv4hi3 (TARGET_VIS4)
#define HAVE_ussubv4hi3 (TARGET_VIS4)
#define HAVE_usaddv8qi3 (TARGET_VIS4)
#define HAVE_ussubv8qi3 (TARGET_VIS4)
#define HAVE_fucmple8si_vis ((TARGET_VIS3) && (TARGET_ARCH32))
#define HAVE_fucmpne8si_vis ((TARGET_VIS3) && (TARGET_ARCH32))
#define HAVE_fucmpgt8si_vis ((TARGET_VIS3) && (TARGET_ARCH32))
#define HAVE_fucmpeq8si_vis ((TARGET_VIS3) && (TARGET_ARCH32))
#define HAVE_fpcmpule16si_vis ((TARGET_VIS4) && (TARGET_ARCH32))
#define HAVE_fpcmpune16si_vis ((TARGET_VIS4) && (TARGET_ARCH32))
#define HAVE_fpcmpugt16si_vis ((TARGET_VIS4) && (TARGET_ARCH32))
#define HAVE_fpcmpueq16si_vis ((TARGET_VIS4) && (TARGET_ARCH32))
#define HAVE_fpcmpule32si_vis ((TARGET_VIS4) && (TARGET_ARCH32))
#define HAVE_fpcmpune32si_vis ((TARGET_VIS4) && (TARGET_ARCH32))
#define HAVE_fpcmpugt32si_vis ((TARGET_VIS4) && (TARGET_ARCH32))
#define HAVE_fpcmpueq32si_vis ((TARGET_VIS4) && (TARGET_ARCH32))
#define HAVE_fhaddsf_vis (TARGET_VIS3)
#define HAVE_fhadddf_vis (TARGET_VIS3)
#define HAVE_fhsubsf_vis (TARGET_VIS3)
#define HAVE_fhsubdf_vis (TARGET_VIS3)
#define HAVE_fnhaddsf_vis (TARGET_VIS3)
#define HAVE_fnhadddf_vis (TARGET_VIS3)
#define HAVE_atomic_loaddi_1 1
#define HAVE_atomic_storedi_1 1
#define HAVE_swapsi ((TARGET_V8 || TARGET_V9) && !sparc_fix_ut699)
#define HAVE_ldstub (!sparc_fix_ut699)
#define HAVE_cstoresi4 1
#define HAVE_cstoresf4 (TARGET_FPU)
#define HAVE_cstoredf4 (TARGET_FPU)
#define HAVE_cstoretf4 (TARGET_FPU)
#define HAVE_cbranchcc4 1
#define HAVE_cbranchsi4 1
#define HAVE_cbranchsf4 (TARGET_FPU)
#define HAVE_cbranchdf4 (TARGET_FPU)
#define HAVE_cbranchtf4 (TARGET_FPU)
#define HAVE_movqi 1
#define HAVE_movhi 1
#define HAVE_movsi 1
#define HAVE_movsi_pic_label_ref (flag_pic)
#define HAVE_movdi 1
#define HAVE_reload_indi ((TARGET_CM_MEDANY || TARGET_CM_EMBMEDANY) && !flag_pic)
#define HAVE_reload_outdi ((TARGET_CM_MEDANY || TARGET_CM_EMBMEDANY) && !flag_pic)
#define HAVE_movsf 1
#define HAVE_movdf 1
#define HAVE_movtf 1
#define HAVE_movqicc (TARGET_V9 && !(QImode == DImode && TARGET_ARCH32))
#define HAVE_movhicc (TARGET_V9 && !(HImode == DImode && TARGET_ARCH32))
#define HAVE_movsicc (TARGET_V9 && !(SImode == DImode && TARGET_ARCH32))
#define HAVE_movsfcc (TARGET_V9 && TARGET_FPU)
#define HAVE_movdfcc (TARGET_V9 && TARGET_FPU)
#define HAVE_movtfcc (TARGET_V9 && TARGET_FPU)
#define HAVE_zero_extendhisi2 1
#define HAVE_zero_extendqihi2 1
#define HAVE_zero_extendqisi2 1
#define HAVE_zero_extendsidi2 1
#define HAVE_extendhisi2 1
#define HAVE_extendqihi2 1
#define HAVE_extendqisi2 1
#define HAVE_extendsftf2 (TARGET_FPU && (TARGET_HARD_QUAD || TARGET_ARCH64))
#define HAVE_extenddftf2 (TARGET_FPU && (TARGET_HARD_QUAD || TARGET_ARCH64))
#define HAVE_trunctfsf2 (TARGET_FPU && (TARGET_HARD_QUAD || TARGET_ARCH64))
#define HAVE_trunctfdf2 (TARGET_FPU && (TARGET_HARD_QUAD || TARGET_ARCH64))
#define HAVE_floatsitf2 (TARGET_FPU && (TARGET_HARD_QUAD || TARGET_ARCH64))
#define HAVE_floatditf2 (TARGET_FPU && TARGET_V9 && (TARGET_HARD_QUAD || TARGET_ARCH64))
#define HAVE_fix_trunctfsi2 (TARGET_FPU && (TARGET_HARD_QUAD || TARGET_ARCH64))
#define HAVE_fix_trunctfdi2 (TARGET_V9 && TARGET_FPU && (TARGET_HARD_QUAD || TARGET_ARCH64))
#define HAVE_adddi3 1
#define HAVE_uaddvdi4 1
#define HAVE_addvdi4 1
#define HAVE_uaddvsi4 1
#define HAVE_addvsi4 1
#define HAVE_subdi3 1
#define HAVE_usubvdi4 1
#define HAVE_subvdi4 1
#define HAVE_usubvsi4 1
#define HAVE_subvsi4 1
#define HAVE_muldi3 (TARGET_ARCH64 || TARGET_V8PLUS)
#define HAVE_mulsidi3 (TARGET_HARD_MUL)
#define HAVE_smulsi3_highpart (TARGET_HARD_MUL && TARGET_ARCH32)
#define HAVE_umulsidi3 (TARGET_HARD_MUL)
#define HAVE_umulsi3_highpart (TARGET_HARD_MUL && TARGET_ARCH32)
#define HAVE_umulxhi_vis (TARGET_VIS3)
#define HAVE_xmulx_vis (TARGET_VIS3)
#define HAVE_xmulxhi_vis (TARGET_VIS3)
#define HAVE_divsi3 (TARGET_V8 || TARGET_DEPRECATED_V8_INSNS)
#define HAVE_udivsi3 (TARGET_V8 || TARGET_DEPRECATED_V8_INSNS)
#define HAVE_negdi2 1
#define HAVE_unegvdi3 1
#define HAVE_negvdi3 1
#define HAVE_unegvsi3 1
#define HAVE_negvsi3 1
#define HAVE_addtf3 (TARGET_FPU && (TARGET_HARD_QUAD || TARGET_ARCH64))
#define HAVE_subtf3 (TARGET_FPU && (TARGET_HARD_QUAD || TARGET_ARCH64))
#define HAVE_multf3 (TARGET_FPU && (TARGET_HARD_QUAD || TARGET_ARCH64))
#define HAVE_divtf3 (TARGET_FPU && (TARGET_HARD_QUAD || TARGET_ARCH64))
#define HAVE_divdf3 (TARGET_FPU)
#define HAVE_negtf2 (TARGET_FPU)
#define HAVE_negdf2 (TARGET_FPU)
#define HAVE_abstf2 (TARGET_FPU)
#define HAVE_absdf2 (TARGET_FPU)
#define HAVE_sqrttf2 (TARGET_FPU && (TARGET_HARD_QUAD || TARGET_ARCH64))
#define HAVE_sqrtdf2 (TARGET_FPU)
#define HAVE_ashldi3 (TARGET_ARCH64 || TARGET_V8PLUS)
#define HAVE_ashrdi3 (TARGET_ARCH64 || TARGET_V8PLUS)
#define HAVE_lshrdi3 (TARGET_ARCH64 || TARGET_V8PLUS)
#define HAVE_jump 1
#define HAVE_tablejump 1
#define HAVE_call 1
#define HAVE_call_value 1
#define HAVE_untyped_call 1
#define HAVE_sibcall 1
#define HAVE_sibcall_value 1
#define HAVE_prologue 1
#define HAVE_epilogue 1
#define HAVE_sibcall_epilogue 1
#define HAVE_eh_return 1
#define HAVE_return (sparc_can_use_return_insn_p ())
#define HAVE_frame_blockage 1
#define HAVE_probe_stack 1
#define HAVE_untyped_return 1
#define HAVE_indirect_jump 1
#define HAVE_save_stack_nonlocal 1
#define HAVE_restore_stack_nonlocal 1
#define HAVE_nonlocal_goto 1
#define HAVE_builtin_setjmp_receiver (flag_pic)
#define HAVE_popcountdi2 (TARGET_POPC)
#define HAVE_popcountsi2 (TARGET_POPC)
#define HAVE_clzdi2 (TARGET_VIS3)
#define HAVE_clzsi2 (TARGET_VIS3)
#define HAVE_prefetch (TARGET_V9)
#define HAVE_ctrapsi4 1
#define HAVE_stack_protect_set 1
#define HAVE_stack_protect_test 1
#define HAVE_movv1si (TARGET_VIS)
#define HAVE_movv2hi (TARGET_VIS)
#define HAVE_movv4qi (TARGET_VIS)
#define HAVE_movv1di (TARGET_VIS)
#define HAVE_movv2si (TARGET_VIS)
#define HAVE_movv4hi (TARGET_VIS)
#define HAVE_movv8qi (TARGET_VIS)
#define HAVE_vec_initv1si (TARGET_VIS)
#define HAVE_vec_initv2hi (TARGET_VIS)
#define HAVE_vec_initv4qi (TARGET_VIS)
#define HAVE_vec_initv1di (TARGET_VIS)
#define HAVE_vec_initv2si (TARGET_VIS)
#define HAVE_vec_initv4hi (TARGET_VIS)
#define HAVE_vec_initv8qi (TARGET_VIS)
#define HAVE_wrgsr_vis (TARGET_VIS)
#define HAVE_rdgsr_vis (TARGET_VIS)
#define HAVE_vcondv4hiv4hi (TARGET_VIS3)
#define HAVE_vcondv2siv2si (TARGET_VIS3)
#define HAVE_vconduv8qiv8qi (TARGET_VIS3)
#define HAVE_vec_perm_constv8qi (TARGET_VIS2)
#define HAVE_vec_permv1di (TARGET_VIS2)
#define HAVE_vec_permv2si (TARGET_VIS2)
#define HAVE_vec_permv4hi (TARGET_VIS2)
#define HAVE_vec_permv8qi (TARGET_VIS2)
#define HAVE_mem_thread_fence (TARGET_V8 || TARGET_V9)
#define HAVE_membar (TARGET_V8 || TARGET_V9)
#define HAVE_atomic_loadqi 1
#define HAVE_atomic_loadhi 1
#define HAVE_atomic_loadsi 1
#define HAVE_atomic_loaddi 1
#define HAVE_atomic_storeqi 1
#define HAVE_atomic_storehi 1
#define HAVE_atomic_storesi 1
#define HAVE_atomic_storedi 1
#define HAVE_atomic_compare_and_swapqi ((TARGET_V9 || TARGET_LEON3) \
   && (QImode != DImode || TARGET_ARCH64 || TARGET_V8PLUS))
#define HAVE_atomic_compare_and_swaphi ((TARGET_V9 || TARGET_LEON3) \
   && (HImode != DImode || TARGET_ARCH64 || TARGET_V8PLUS))
#define HAVE_atomic_compare_and_swapsi ((TARGET_V9 || TARGET_LEON3) \
   && (SImode != DImode || TARGET_ARCH64 || TARGET_V8PLUS))
#define HAVE_atomic_compare_and_swapdi ((TARGET_V9 || TARGET_LEON3) \
   && (DImode != DImode || TARGET_ARCH64 || TARGET_V8PLUS))
#define HAVE_atomic_compare_and_swapsi_1 (TARGET_V9 || TARGET_LEON3)
#define HAVE_atomic_compare_and_swapdi_1 ((TARGET_V9 || TARGET_LEON3) && (TARGET_ARCH64 || TARGET_V8PLUS))
#define HAVE_atomic_exchangesi ((TARGET_V8 || TARGET_V9) && !sparc_fix_ut699)
#define HAVE_atomic_test_and_set (!sparc_fix_ut699)
extern rtx        gen_load_pcrel_symsi              (rtx, rtx, rtx, rtx);
extern rtx        gen_load_pcrel_symdi              (rtx, rtx, rtx, rtx);
extern rtx        gen_movsi_lo_sum_pic              (rtx, rtx, rtx);
extern rtx        gen_movsi_high_pic                (rtx, rtx);
extern rtx        gen_movsi_pic_gotdata_op          (rtx, rtx, rtx, rtx);
static inline rtx gen_movdi_lo_sum_pic              (rtx, rtx, rtx);
static inline rtx
gen_movdi_lo_sum_pic(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
static inline rtx gen_movdi_high_pic                (rtx, rtx);
static inline rtx
gen_movdi_high_pic(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b))
{
  return 0;
}
static inline rtx gen_movdi_pic_gotdata_op          (rtx, rtx, rtx, rtx);
static inline rtx
gen_movdi_pic_gotdata_op(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c), rtx ARG_UNUSED (d))
{
  return 0;
}
extern rtx        gen_seth44                        (rtx, rtx);
extern rtx        gen_setm44                        (rtx, rtx, rtx);
extern rtx        gen_setl44                        (rtx, rtx, rtx);
extern rtx        gen_sethh                         (rtx, rtx);
extern rtx        gen_setlm                         (rtx, rtx);
extern rtx        gen_sethm                         (rtx, rtx, rtx);
extern rtx        gen_setlo                         (rtx, rtx, rtx);
extern rtx        gen_embmedany_sethi               (rtx, rtx);
extern rtx        gen_embmedany_losum               (rtx, rtx, rtx);
extern rtx        gen_embmedany_brsum               (rtx, rtx);
extern rtx        gen_embmedany_textuhi             (rtx, rtx);
extern rtx        gen_embmedany_texthi              (rtx, rtx);
extern rtx        gen_embmedany_textulo             (rtx, rtx, rtx);
extern rtx        gen_embmedany_textlo              (rtx, rtx, rtx);
extern rtx        gen_movdf_cc_v9                   (rtx, rtx, rtx, rtx, rtx);
static inline rtx gen_movdf_cc_reg_sp64             (rtx, rtx, rtx, rtx, rtx);
static inline rtx
gen_movdf_cc_reg_sp64(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c), rtx ARG_UNUSED (d), rtx ARG_UNUSED (e))
{
  return 0;
}
extern rtx        gen_extendsfdf2                   (rtx, rtx);
extern rtx        gen_truncdfsf2                    (rtx, rtx);
extern rtx        gen_floatsisf2                    (rtx, rtx);
extern rtx        gen_floatsidf2                    (rtx, rtx);
extern rtx        gen_floatdisf2                    (rtx, rtx);
extern rtx        gen_floatdidf2                    (rtx, rtx);
extern rtx        gen_fix_truncsfsi2                (rtx, rtx);
extern rtx        gen_fix_truncdfsi2                (rtx, rtx);
extern rtx        gen_fix_truncsfdi2                (rtx, rtx);
extern rtx        gen_fix_truncdfdi2                (rtx, rtx);
extern rtx        gen_adddi3_sp32                   (rtx, rtx, rtx);
extern rtx        gen_uaddvdi4_sp32                 (rtx, rtx, rtx);
extern rtx        gen_addvdi4_sp32                  (rtx, rtx, rtx);
extern rtx        gen_addsi3                        (rtx, rtx, rtx);
extern rtx        gen_subdi3_sp32                   (rtx, rtx, rtx);
extern rtx        gen_usubvdi4_sp32                 (rtx, rtx, rtx);
extern rtx        gen_subvdi4_sp32                  (rtx, rtx, rtx);
extern rtx        gen_subsi3                        (rtx, rtx, rtx);
extern rtx        gen_mulsi3                        (rtx, rtx, rtx);
extern rtx        gen_muldi3_v8plus                 (rtx, rtx, rtx);
extern rtx        gen_mulsidi3_v8plus               (rtx, rtx, rtx);
extern rtx        gen_const_mulsidi3_v8plus         (rtx, rtx, rtx);
extern rtx        gen_const_mulsidi3_sp32           (rtx, rtx, rtx);
static inline rtx gen_const_mulsidi3_sp64           (rtx, rtx, rtx);
static inline rtx
gen_const_mulsidi3_sp64(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_smulsi3_highpart_v8plus       (rtx, rtx, rtx, rtx);
extern rtx        gen_const_smulsi3_highpart_v8plus (rtx, rtx, rtx, rtx);
extern rtx        gen_const_smulsi3_highpart        (rtx, rtx, rtx);
extern rtx        gen_umulsidi3_v8plus              (rtx, rtx, rtx);
extern rtx        gen_const_umulsidi3_sp32          (rtx, rtx, rtx);
static inline rtx gen_const_umulsidi3_sp64          (rtx, rtx, rtx);
static inline rtx
gen_const_umulsidi3_sp64(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_const_umulsidi3_v8plus        (rtx, rtx, rtx);
extern rtx        gen_umulsi3_highpart_v8plus       (rtx, rtx, rtx, rtx);
extern rtx        gen_const_umulsi3_highpart_v8plus (rtx, rtx, rtx, rtx);
extern rtx        gen_const_umulsi3_highpart        (rtx, rtx, rtx);
extern rtx        gen_umulxhi_v8plus                (rtx, rtx, rtx);
extern rtx        gen_xmulx_v8plus                  (rtx, rtx, rtx);
extern rtx        gen_xmulxhi_v8plus                (rtx, rtx, rtx);
extern rtx        gen_divsi3_sp32                   (rtx, rtx, rtx);
static inline rtx gen_divsi3_sp64                   (rtx, rtx, rtx, rtx);
static inline rtx
gen_divsi3_sp64(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c), rtx ARG_UNUSED (d))
{
  return 0;
}
static inline rtx gen_divdi3                        (rtx, rtx, rtx);
static inline rtx
gen_divdi3(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_udivsi3_sp32                  (rtx, rtx, rtx);
static inline rtx gen_udivsi3_sp64                  (rtx, rtx, rtx);
static inline rtx
gen_udivsi3_sp64(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
static inline rtx gen_udivdi3                       (rtx, rtx, rtx);
static inline rtx
gen_udivdi3(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
static inline rtx gen_anddi3                        (rtx, rtx, rtx);
static inline rtx
gen_anddi3(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_andsi3                        (rtx, rtx, rtx);
static inline rtx gen_iordi3                        (rtx, rtx, rtx);
static inline rtx
gen_iordi3(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_iorsi3                        (rtx, rtx, rtx);
static inline rtx gen_xordi3                        (rtx, rtx, rtx);
static inline rtx
gen_xordi3(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_xorsi3                        (rtx, rtx, rtx);
extern rtx        gen_negdi2_sp32                   (rtx, rtx);
extern rtx        gen_unegvdi3_sp32                 (rtx, rtx);
extern rtx        gen_negvdi3_sp32                  (rtx, rtx);
extern rtx        gen_negsi2                        (rtx, rtx);
static inline rtx gen_one_cmpldi2                   (rtx, rtx);
static inline rtx
gen_one_cmpldi2(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b))
{
  return 0;
}
extern rtx        gen_one_cmplsi2                   (rtx, rtx);
extern rtx        gen_adddf3                        (rtx, rtx, rtx);
extern rtx        gen_addsf3                        (rtx, rtx, rtx);
extern rtx        gen_subdf3                        (rtx, rtx, rtx);
extern rtx        gen_subsf3                        (rtx, rtx, rtx);
extern rtx        gen_muldf3                        (rtx, rtx, rtx);
extern rtx        gen_mulsf3                        (rtx, rtx, rtx);
extern rtx        gen_fmadf4                        (rtx, rtx, rtx, rtx);
extern rtx        gen_fmsdf4                        (rtx, rtx, rtx, rtx);
extern rtx        gen_fmasf4                        (rtx, rtx, rtx, rtx);
extern rtx        gen_fmssf4                        (rtx, rtx, rtx, rtx);
extern rtx        gen_divsf3                        (rtx, rtx, rtx);
extern rtx        gen_negsf2                        (rtx, rtx);
extern rtx        gen_abssf2                        (rtx, rtx);
extern rtx        gen_sqrtsf2                       (rtx, rtx);
extern rtx        gen_ashlsi3                       (rtx, rtx, rtx);
extern rtx        gen_ashldi3_v8plus                (rtx, rtx, rtx);
extern rtx        gen_ashrsi3                       (rtx, rtx, rtx);
extern rtx        gen_ashrdi3_v8plus                (rtx, rtx, rtx);
extern rtx        gen_lshrsi3                       (rtx, rtx, rtx);
extern rtx        gen_lshrdi3_v8plus                (rtx, rtx, rtx);
extern rtx        gen_window_save                   (rtx);
extern rtx        gen_eh_return_internal            (void);
extern rtx        gen_blockage                      (void);
extern rtx        gen_probe_stack_rangesi           (rtx, rtx, rtx);
static inline rtx gen_probe_stack_rangedi           (rtx, rtx, rtx);
static inline rtx
gen_probe_stack_rangedi(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_update_return                 (rtx, rtx);
extern rtx        gen_nop                           (void);
extern rtx        gen_flush_register_windows        (void);
extern rtx        gen_flushsi                       (rtx);
static inline rtx gen_flushdi                       (rtx);
static inline rtx
gen_flushdi(rtx ARG_UNUSED (a))
{
  return 0;
}
extern rtx        gen_ldfsr                         (rtx);
extern rtx        gen_stfsr                         (rtx);
extern rtx        gen_popcountdi_v8plus             (rtx, rtx);
extern rtx        gen_popcountsi_v8plus             (rtx, rtx);
extern rtx        gen_clzdi_v8plus                  (rtx, rtx);
extern rtx        gen_clzsi_v8plus                  (rtx, rtx);
extern rtx        gen_prefetch_64                   (rtx, rtx, rtx);
extern rtx        gen_prefetch_32                   (rtx, rtx, rtx);
extern rtx        gen_trap                          (void);
extern rtx        gen_tgd_hi22                      (rtx, rtx);
extern rtx        gen_tgd_lo10                      (rtx, rtx, rtx);
extern rtx        gen_tgd_add32                     (rtx, rtx, rtx, rtx);
static inline rtx gen_tgd_add64                     (rtx, rtx, rtx, rtx);
static inline rtx
gen_tgd_add64(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c), rtx ARG_UNUSED (d))
{
  return 0;
}
extern rtx        gen_tgd_call32                    (rtx, rtx, rtx, rtx);
static inline rtx gen_tgd_call64                    (rtx, rtx, rtx, rtx);
static inline rtx
gen_tgd_call64(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c), rtx ARG_UNUSED (d))
{
  return 0;
}
extern rtx        gen_tldm_hi22                     (rtx);
extern rtx        gen_tldm_lo10                     (rtx, rtx);
extern rtx        gen_tldm_add32                    (rtx, rtx, rtx);
static inline rtx gen_tldm_add64                    (rtx, rtx, rtx);
static inline rtx
gen_tldm_add64(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_tldm_call32                   (rtx, rtx, rtx);
static inline rtx gen_tldm_call64                   (rtx, rtx, rtx);
static inline rtx
gen_tldm_call64(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_tldo_hix22                    (rtx, rtx);
extern rtx        gen_tldo_lox10                    (rtx, rtx, rtx);
extern rtx        gen_tldo_add32                    (rtx, rtx, rtx, rtx);
static inline rtx gen_tldo_add64                    (rtx, rtx, rtx, rtx);
static inline rtx
gen_tldo_add64(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c), rtx ARG_UNUSED (d))
{
  return 0;
}
extern rtx        gen_tie_hi22                      (rtx, rtx);
extern rtx        gen_tie_lo10                      (rtx, rtx, rtx);
extern rtx        gen_tie_ld32                      (rtx, rtx, rtx, rtx);
static inline rtx gen_tie_ld64                      (rtx, rtx, rtx, rtx);
static inline rtx
gen_tie_ld64(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c), rtx ARG_UNUSED (d))
{
  return 0;
}
static inline rtx gen_tie_add32                     (rtx, rtx, rtx, rtx);
static inline rtx
gen_tie_add32(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c), rtx ARG_UNUSED (d))
{
  return 0;
}
static inline rtx gen_tie_add64                     (rtx, rtx, rtx, rtx);
static inline rtx
gen_tie_add64(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c), rtx ARG_UNUSED (d))
{
  return 0;
}
extern rtx        gen_tle_hix22_sp32                (rtx, rtx);
extern rtx        gen_tle_lox10_sp32                (rtx, rtx, rtx);
static inline rtx gen_tle_hix22_sp64                (rtx, rtx);
static inline rtx
gen_tle_hix22_sp64(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b))
{
  return 0;
}
static inline rtx gen_tle_lox10_sp64                (rtx, rtx, rtx);
static inline rtx
gen_tle_lox10_sp64(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_stack_protect_setsi           (rtx, rtx);
static inline rtx gen_stack_protect_setdi           (rtx, rtx);
static inline rtx
gen_stack_protect_setdi(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b))
{
  return 0;
}
extern rtx        gen_stack_protect_testsi          (rtx, rtx);
static inline rtx gen_stack_protect_testdi          (rtx, rtx, rtx);
static inline rtx
gen_stack_protect_testdi(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_addv1si3                      (rtx, rtx, rtx);
extern rtx        gen_subv1si3                      (rtx, rtx, rtx);
extern rtx        gen_addv2si3                      (rtx, rtx, rtx);
extern rtx        gen_subv2si3                      (rtx, rtx, rtx);
extern rtx        gen_addv2hi3                      (rtx, rtx, rtx);
extern rtx        gen_subv2hi3                      (rtx, rtx, rtx);
extern rtx        gen_addv4hi3                      (rtx, rtx, rtx);
extern rtx        gen_subv4hi3                      (rtx, rtx, rtx);
extern rtx        gen_iorv1si3                      (rtx, rtx, rtx);
extern rtx        gen_andv1si3                      (rtx, rtx, rtx);
extern rtx        gen_xorv1si3                      (rtx, rtx, rtx);
extern rtx        gen_iorv2hi3                      (rtx, rtx, rtx);
extern rtx        gen_andv2hi3                      (rtx, rtx, rtx);
extern rtx        gen_xorv2hi3                      (rtx, rtx, rtx);
extern rtx        gen_iorv4qi3                      (rtx, rtx, rtx);
extern rtx        gen_andv4qi3                      (rtx, rtx, rtx);
extern rtx        gen_xorv4qi3                      (rtx, rtx, rtx);
extern rtx        gen_iorv1di3                      (rtx, rtx, rtx);
extern rtx        gen_andv1di3                      (rtx, rtx, rtx);
extern rtx        gen_xorv1di3                      (rtx, rtx, rtx);
extern rtx        gen_iorv2si3                      (rtx, rtx, rtx);
extern rtx        gen_andv2si3                      (rtx, rtx, rtx);
extern rtx        gen_xorv2si3                      (rtx, rtx, rtx);
extern rtx        gen_iorv4hi3                      (rtx, rtx, rtx);
extern rtx        gen_andv4hi3                      (rtx, rtx, rtx);
extern rtx        gen_xorv4hi3                      (rtx, rtx, rtx);
extern rtx        gen_iorv8qi3                      (rtx, rtx, rtx);
extern rtx        gen_andv8qi3                      (rtx, rtx, rtx);
extern rtx        gen_xorv8qi3                      (rtx, rtx, rtx);
extern rtx        gen_one_cmplv1si2                 (rtx, rtx);
extern rtx        gen_one_cmplv2hi2                 (rtx, rtx);
extern rtx        gen_one_cmplv4qi2                 (rtx, rtx);
extern rtx        gen_one_cmplv1di2                 (rtx, rtx);
extern rtx        gen_one_cmplv2si2                 (rtx, rtx);
extern rtx        gen_one_cmplv4hi2                 (rtx, rtx);
extern rtx        gen_one_cmplv8qi2                 (rtx, rtx);
extern rtx        gen_fpack16_vis                   (rtx, rtx);
extern rtx        gen_fpackfix_vis                  (rtx, rtx);
extern rtx        gen_fpack32_vis                   (rtx, rtx, rtx);
extern rtx        gen_fexpand_vis                   (rtx, rtx);
extern rtx        gen_fpmerge_vis                   (rtx, rtx, rtx);
extern rtx        gen_fmul8x16_vis                  (rtx, rtx, rtx);
extern rtx        gen_fmul8x16au_vis                (rtx, rtx, rtx);
extern rtx        gen_fmul8x16al_vis                (rtx, rtx, rtx);
extern rtx        gen_fmul8sux16_vis                (rtx, rtx, rtx);
extern rtx        gen_fmul8ulx16_vis                (rtx, rtx, rtx);
extern rtx        gen_fmuld8sux16_vis               (rtx, rtx, rtx);
extern rtx        gen_fmuld8ulx16_vis               (rtx, rtx, rtx);
extern rtx        gen_wrgsr_v8plus                  (rtx);
extern rtx        gen_rdgsr_v8plus                  (rtx);
extern rtx        gen_faligndatav1di_vis            (rtx, rtx, rtx);
extern rtx        gen_faligndatav2si_vis            (rtx, rtx, rtx);
extern rtx        gen_faligndatav4hi_vis            (rtx, rtx, rtx);
extern rtx        gen_faligndatav8qi_vis            (rtx, rtx, rtx);
extern rtx        gen_alignaddrsi_vis               (rtx, rtx, rtx);
extern rtx        gen_alignaddrdi_vis               (rtx, rtx, rtx);
extern rtx        gen_alignaddrlsi_vis              (rtx, rtx, rtx);
extern rtx        gen_alignaddrldi_vis              (rtx, rtx, rtx);
extern rtx        gen_pdist_vis                     (rtx, rtx, rtx, rtx);
extern rtx        gen_edge8si_vis                   (rtx, rtx, rtx);
static inline rtx gen_edge8di_vis                   (rtx, rtx, rtx);
static inline rtx
gen_edge8di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_edge8lsi_vis                  (rtx, rtx, rtx);
static inline rtx gen_edge8ldi_vis                  (rtx, rtx, rtx);
static inline rtx
gen_edge8ldi_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_edge16si_vis                  (rtx, rtx, rtx);
static inline rtx gen_edge16di_vis                  (rtx, rtx, rtx);
static inline rtx
gen_edge16di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_edge16lsi_vis                 (rtx, rtx, rtx);
static inline rtx gen_edge16ldi_vis                 (rtx, rtx, rtx);
static inline rtx
gen_edge16ldi_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_edge32si_vis                  (rtx, rtx, rtx);
static inline rtx gen_edge32di_vis                  (rtx, rtx, rtx);
static inline rtx
gen_edge32di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_edge32lsi_vis                 (rtx, rtx, rtx);
static inline rtx gen_edge32ldi_vis                 (rtx, rtx, rtx);
static inline rtx
gen_edge32ldi_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_fcmple16si_vis                (rtx, rtx, rtx);
extern rtx        gen_fcmpne16si_vis                (rtx, rtx, rtx);
extern rtx        gen_fcmpgt16si_vis                (rtx, rtx, rtx);
extern rtx        gen_fcmpeq16si_vis                (rtx, rtx, rtx);
static inline rtx gen_fcmple16di_vis                (rtx, rtx, rtx);
static inline rtx
gen_fcmple16di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
static inline rtx gen_fcmpne16di_vis                (rtx, rtx, rtx);
static inline rtx
gen_fcmpne16di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
static inline rtx gen_fcmpgt16di_vis                (rtx, rtx, rtx);
static inline rtx
gen_fcmpgt16di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
static inline rtx gen_fcmpeq16di_vis                (rtx, rtx, rtx);
static inline rtx
gen_fcmpeq16di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_fcmple32si_vis                (rtx, rtx, rtx);
extern rtx        gen_fcmpne32si_vis                (rtx, rtx, rtx);
extern rtx        gen_fcmpgt32si_vis                (rtx, rtx, rtx);
extern rtx        gen_fcmpeq32si_vis                (rtx, rtx, rtx);
static inline rtx gen_fcmple32di_vis                (rtx, rtx, rtx);
static inline rtx
gen_fcmple32di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
static inline rtx gen_fcmpne32di_vis                (rtx, rtx, rtx);
static inline rtx
gen_fcmpne32di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
static inline rtx gen_fcmpgt32di_vis                (rtx, rtx, rtx);
static inline rtx
gen_fcmpgt32di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
static inline rtx gen_fcmpeq32di_vis                (rtx, rtx, rtx);
static inline rtx
gen_fcmpeq32di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_fpcmple8si_vis                (rtx, rtx, rtx);
extern rtx        gen_fpcmpne8si_vis                (rtx, rtx, rtx);
extern rtx        gen_fpcmpgt8si_vis                (rtx, rtx, rtx);
extern rtx        gen_fpcmpeq8si_vis                (rtx, rtx, rtx);
static inline rtx gen_fpcmple8di_vis                (rtx, rtx, rtx);
static inline rtx
gen_fpcmple8di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
static inline rtx gen_fpcmpne8di_vis                (rtx, rtx, rtx);
static inline rtx
gen_fpcmpne8di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
static inline rtx gen_fpcmpgt8di_vis                (rtx, rtx, rtx);
static inline rtx
gen_fpcmpgt8di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
static inline rtx gen_fpcmpeq8di_vis                (rtx, rtx, rtx);
static inline rtx
gen_fpcmpeq8di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_array8si_vis                  (rtx, rtx, rtx);
static inline rtx gen_array8di_vis                  (rtx, rtx, rtx);
static inline rtx
gen_array8di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_array16si_vis                 (rtx, rtx, rtx);
static inline rtx gen_array16di_vis                 (rtx, rtx, rtx);
static inline rtx
gen_array16di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_array32si_vis                 (rtx, rtx, rtx);
static inline rtx gen_array32di_vis                 (rtx, rtx, rtx);
static inline rtx
gen_array32di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
static inline rtx gen_bmaskdi_vis                   (rtx, rtx, rtx);
static inline rtx
gen_bmaskdi_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_bmasksi_vis                   (rtx, rtx, rtx);
extern rtx        gen_bshufflev1di_vis              (rtx, rtx, rtx);
extern rtx        gen_bshufflev2si_vis              (rtx, rtx, rtx);
extern rtx        gen_bshufflev4hi_vis              (rtx, rtx, rtx);
extern rtx        gen_bshufflev8qi_vis              (rtx, rtx, rtx);
extern rtx        gen_edge8nsi_vis                  (rtx, rtx, rtx);
static inline rtx gen_edge8ndi_vis                  (rtx, rtx, rtx);
static inline rtx
gen_edge8ndi_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_edge8lnsi_vis                 (rtx, rtx, rtx);
static inline rtx gen_edge8lndi_vis                 (rtx, rtx, rtx);
static inline rtx
gen_edge8lndi_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_edge16nsi_vis                 (rtx, rtx, rtx);
static inline rtx gen_edge16ndi_vis                 (rtx, rtx, rtx);
static inline rtx
gen_edge16ndi_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_edge16lnsi_vis                (rtx, rtx, rtx);
static inline rtx gen_edge16lndi_vis                (rtx, rtx, rtx);
static inline rtx
gen_edge16lndi_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_edge32nsi_vis                 (rtx, rtx, rtx);
static inline rtx gen_edge32ndi_vis                 (rtx, rtx, rtx);
static inline rtx
gen_edge32ndi_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_edge32lnsi_vis                (rtx, rtx, rtx);
static inline rtx gen_edge32lndi_vis                (rtx, rtx, rtx);
static inline rtx
gen_edge32lndi_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_cmask8si_vis                  (rtx);
static inline rtx gen_cmask8di_vis                  (rtx);
static inline rtx
gen_cmask8di_vis(rtx ARG_UNUSED (a))
{
  return 0;
}
extern rtx        gen_cmask16si_vis                 (rtx);
static inline rtx gen_cmask16di_vis                 (rtx);
static inline rtx
gen_cmask16di_vis(rtx ARG_UNUSED (a))
{
  return 0;
}
extern rtx        gen_cmask32si_vis                 (rtx);
static inline rtx gen_cmask32di_vis                 (rtx);
static inline rtx
gen_cmask32di_vis(rtx ARG_UNUSED (a))
{
  return 0;
}
extern rtx        gen_fchksm16_vis                  (rtx, rtx, rtx);
extern rtx        gen_vashlv4hi3                    (rtx, rtx, rtx);
extern rtx        gen_vssashlv4hi3                  (rtx, rtx, rtx);
extern rtx        gen_vlshrv4hi3                    (rtx, rtx, rtx);
extern rtx        gen_vashrv4hi3                    (rtx, rtx, rtx);
extern rtx        gen_vashlv2si3                    (rtx, rtx, rtx);
extern rtx        gen_vssashlv2si3                  (rtx, rtx, rtx);
extern rtx        gen_vlshrv2si3                    (rtx, rtx, rtx);
extern rtx        gen_vashrv2si3                    (rtx, rtx, rtx);
extern rtx        gen_pdistnsi_vis                  (rtx, rtx, rtx);
static inline rtx gen_pdistndi_vis                  (rtx, rtx, rtx);
static inline rtx
gen_pdistndi_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_fmean16_vis                   (rtx, rtx, rtx);
extern rtx        gen_fpadd64_vis                   (rtx, rtx, rtx);
extern rtx        gen_fpsub64_vis                   (rtx, rtx, rtx);
extern rtx        gen_addv8qi3                      (rtx, rtx, rtx);
extern rtx        gen_subv8qi3                      (rtx, rtx, rtx);
extern rtx        gen_ssaddv4hi3                    (rtx, rtx, rtx);
extern rtx        gen_sssubv4hi3                    (rtx, rtx, rtx);
extern rtx        gen_ssaddv2si3                    (rtx, rtx, rtx);
extern rtx        gen_sssubv2si3                    (rtx, rtx, rtx);
extern rtx        gen_ssaddv2hi3                    (rtx, rtx, rtx);
extern rtx        gen_sssubv2hi3                    (rtx, rtx, rtx);
extern rtx        gen_ssaddv1si3                    (rtx, rtx, rtx);
extern rtx        gen_sssubv1si3                    (rtx, rtx, rtx);
extern rtx        gen_minv8qi3                      (rtx, rtx, rtx);
extern rtx        gen_maxv8qi3                      (rtx, rtx, rtx);
extern rtx        gen_minv4hi3                      (rtx, rtx, rtx);
extern rtx        gen_maxv4hi3                      (rtx, rtx, rtx);
extern rtx        gen_minv2si3                      (rtx, rtx, rtx);
extern rtx        gen_maxv2si3                      (rtx, rtx, rtx);
extern rtx        gen_minuv8qi3                     (rtx, rtx, rtx);
extern rtx        gen_maxuv8qi3                     (rtx, rtx, rtx);
extern rtx        gen_minuv4hi3                     (rtx, rtx, rtx);
extern rtx        gen_maxuv4hi3                     (rtx, rtx, rtx);
extern rtx        gen_minuv2si3                     (rtx, rtx, rtx);
extern rtx        gen_maxuv2si3                     (rtx, rtx, rtx);
extern rtx        gen_ssaddv8qi3                    (rtx, rtx, rtx);
extern rtx        gen_sssubv8qi3                    (rtx, rtx, rtx);
extern rtx        gen_usaddv4hi3                    (rtx, rtx, rtx);
extern rtx        gen_ussubv4hi3                    (rtx, rtx, rtx);
extern rtx        gen_usaddv8qi3                    (rtx, rtx, rtx);
extern rtx        gen_ussubv8qi3                    (rtx, rtx, rtx);
extern rtx        gen_fucmple8si_vis                (rtx, rtx, rtx);
extern rtx        gen_fucmpne8si_vis                (rtx, rtx, rtx);
extern rtx        gen_fucmpgt8si_vis                (rtx, rtx, rtx);
extern rtx        gen_fucmpeq8si_vis                (rtx, rtx, rtx);
static inline rtx gen_fucmple8di_vis                (rtx, rtx, rtx);
static inline rtx
gen_fucmple8di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
static inline rtx gen_fucmpne8di_vis                (rtx, rtx, rtx);
static inline rtx
gen_fucmpne8di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
static inline rtx gen_fucmpgt8di_vis                (rtx, rtx, rtx);
static inline rtx
gen_fucmpgt8di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
static inline rtx gen_fucmpeq8di_vis                (rtx, rtx, rtx);
static inline rtx
gen_fucmpeq8di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_fpcmpule16si_vis              (rtx, rtx, rtx);
extern rtx        gen_fpcmpune16si_vis              (rtx, rtx, rtx);
extern rtx        gen_fpcmpugt16si_vis              (rtx, rtx, rtx);
extern rtx        gen_fpcmpueq16si_vis              (rtx, rtx, rtx);
extern rtx        gen_fpcmpule32si_vis              (rtx, rtx, rtx);
extern rtx        gen_fpcmpune32si_vis              (rtx, rtx, rtx);
extern rtx        gen_fpcmpugt32si_vis              (rtx, rtx, rtx);
extern rtx        gen_fpcmpueq32si_vis              (rtx, rtx, rtx);
static inline rtx gen_fpcmpule16di_vis              (rtx, rtx, rtx);
static inline rtx
gen_fpcmpule16di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
static inline rtx gen_fpcmpune16di_vis              (rtx, rtx, rtx);
static inline rtx
gen_fpcmpune16di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
static inline rtx gen_fpcmpugt16di_vis              (rtx, rtx, rtx);
static inline rtx
gen_fpcmpugt16di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
static inline rtx gen_fpcmpueq16di_vis              (rtx, rtx, rtx);
static inline rtx
gen_fpcmpueq16di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
static inline rtx gen_fpcmpule32di_vis              (rtx, rtx, rtx);
static inline rtx
gen_fpcmpule32di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
static inline rtx gen_fpcmpune32di_vis              (rtx, rtx, rtx);
static inline rtx
gen_fpcmpune32di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
static inline rtx gen_fpcmpugt32di_vis              (rtx, rtx, rtx);
static inline rtx
gen_fpcmpugt32di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
static inline rtx gen_fpcmpueq32di_vis              (rtx, rtx, rtx);
static inline rtx
gen_fpcmpueq32di_vis(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c))
{
  return 0;
}
extern rtx        gen_fhaddsf_vis                   (rtx, rtx, rtx);
extern rtx        gen_fhadddf_vis                   (rtx, rtx, rtx);
extern rtx        gen_fhsubsf_vis                   (rtx, rtx, rtx);
extern rtx        gen_fhsubdf_vis                   (rtx, rtx, rtx);
extern rtx        gen_fnhaddsf_vis                  (rtx, rtx, rtx);
extern rtx        gen_fnhadddf_vis                  (rtx, rtx, rtx);
extern rtx        gen_atomic_loaddi_1               (rtx, rtx);
extern rtx        gen_atomic_storedi_1              (rtx, rtx);
extern rtx        gen_swapsi                        (rtx, rtx, rtx);
extern rtx        gen_ldstub                        (rtx, rtx);
extern rtx        gen_cstoresi4                     (rtx, rtx, rtx, rtx);
static inline rtx gen_cstoredi4                     (rtx, rtx, rtx, rtx);
static inline rtx
gen_cstoredi4(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c), rtx ARG_UNUSED (d))
{
  return 0;
}
extern rtx        gen_cstoresf4                     (rtx, rtx, rtx, rtx);
extern rtx        gen_cstoredf4                     (rtx, rtx, rtx, rtx);
extern rtx        gen_cstoretf4                     (rtx, rtx, rtx, rtx);
extern rtx        gen_cbranchcc4                    (rtx, rtx, rtx, rtx);
extern rtx        gen_cbranchsi4                    (rtx, rtx, rtx, rtx);
static inline rtx gen_cbranchdi4                    (rtx, rtx, rtx, rtx);
static inline rtx
gen_cbranchdi4(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c), rtx ARG_UNUSED (d))
{
  return 0;
}
extern rtx        gen_cbranchsf4                    (rtx, rtx, rtx, rtx);
extern rtx        gen_cbranchdf4                    (rtx, rtx, rtx, rtx);
extern rtx        gen_cbranchtf4                    (rtx, rtx, rtx, rtx);
extern rtx        gen_movqi                         (rtx, rtx);
extern rtx        gen_movhi                         (rtx, rtx);
extern rtx        gen_movsi                         (rtx, rtx);
extern rtx        gen_movsi_pic_label_ref           (rtx, rtx);
static inline rtx gen_vxworks_load_got              (void);
static inline rtx
gen_vxworks_load_got(void)
{
  return 0;
}
extern rtx        gen_movdi                         (rtx, rtx);
static inline rtx gen_movdi_pic_label_ref           (rtx, rtx);
static inline rtx
gen_movdi_pic_label_ref(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b))
{
  return 0;
}
extern rtx        gen_reload_indi                   (rtx, rtx, rtx);
extern rtx        gen_reload_outdi                  (rtx, rtx, rtx);
static inline rtx gen_movti                         (rtx, rtx);
static inline rtx
gen_movti(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b))
{
  return 0;
}
extern rtx        gen_movsf                         (rtx, rtx);
extern rtx        gen_movdf                         (rtx, rtx);
extern rtx        gen_movtf                         (rtx, rtx);
extern rtx        gen_movqicc                       (rtx, rtx, rtx, rtx);
extern rtx        gen_movhicc                       (rtx, rtx, rtx, rtx);
extern rtx        gen_movsicc                       (rtx, rtx, rtx, rtx);
static inline rtx gen_movdicc                       (rtx, rtx, rtx, rtx);
static inline rtx
gen_movdicc(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c), rtx ARG_UNUSED (d))
{
  return 0;
}
extern rtx        gen_movsfcc                       (rtx, rtx, rtx, rtx);
extern rtx        gen_movdfcc                       (rtx, rtx, rtx, rtx);
extern rtx        gen_movtfcc                       (rtx, rtx, rtx, rtx);
extern rtx        gen_zero_extendhisi2              (rtx, rtx);
extern rtx        gen_zero_extendqihi2              (rtx, rtx);
extern rtx        gen_zero_extendqisi2              (rtx, rtx);
static inline rtx gen_zero_extendqidi2              (rtx, rtx);
static inline rtx
gen_zero_extendqidi2(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b))
{
  return 0;
}
static inline rtx gen_zero_extendhidi2              (rtx, rtx);
static inline rtx
gen_zero_extendhidi2(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b))
{
  return 0;
}
extern rtx        gen_zero_extendsidi2              (rtx, rtx);
extern rtx        gen_extendhisi2                   (rtx, rtx);
extern rtx        gen_extendqihi2                   (rtx, rtx);
extern rtx        gen_extendqisi2                   (rtx, rtx);
static inline rtx gen_extendqidi2                   (rtx, rtx);
static inline rtx
gen_extendqidi2(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b))
{
  return 0;
}
static inline rtx gen_extendhidi2                   (rtx, rtx);
static inline rtx
gen_extendhidi2(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b))
{
  return 0;
}
static inline rtx gen_extendsidi2                   (rtx, rtx);
static inline rtx
gen_extendsidi2(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b))
{
  return 0;
}
extern rtx        gen_extendsftf2                   (rtx, rtx);
extern rtx        gen_extenddftf2                   (rtx, rtx);
extern rtx        gen_trunctfsf2                    (rtx, rtx);
extern rtx        gen_trunctfdf2                    (rtx, rtx);
extern rtx        gen_floatsitf2                    (rtx, rtx);
static inline rtx gen_floatunssitf2                 (rtx, rtx);
static inline rtx
gen_floatunssitf2(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b))
{
  return 0;
}
static inline rtx gen_floatunsdisf2                 (rtx, rtx);
static inline rtx
gen_floatunsdisf2(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b))
{
  return 0;
}
static inline rtx gen_floatunsdidf2                 (rtx, rtx);
static inline rtx
gen_floatunsdidf2(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b))
{
  return 0;
}
extern rtx        gen_floatditf2                    (rtx, rtx);
static inline rtx gen_floatunsditf2                 (rtx, rtx);
static inline rtx
gen_floatunsditf2(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b))
{
  return 0;
}
extern rtx        gen_fix_trunctfsi2                (rtx, rtx);
static inline rtx gen_fixuns_trunctfsi2             (rtx, rtx);
static inline rtx
gen_fixuns_trunctfsi2(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b))
{
  return 0;
}
static inline rtx gen_fixuns_truncsfdi2             (rtx, rtx);
static inline rtx
gen_fixuns_truncsfdi2(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b))
{
  return 0;
}
static inline rtx gen_fixuns_truncdfdi2             (rtx, rtx);
static inline rtx
gen_fixuns_truncdfdi2(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b))
{
  return 0;
}
extern rtx        gen_fix_trunctfdi2                (rtx, rtx);
static inline rtx gen_fixuns_trunctfdi2             (rtx, rtx);
static inline rtx
gen_fixuns_trunctfdi2(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b))
{
  return 0;
}
extern rtx        gen_adddi3                        (rtx, rtx, rtx);
extern rtx        gen_uaddvdi4                      (rtx, rtx, rtx, rtx);
extern rtx        gen_addvdi4                       (rtx, rtx, rtx, rtx);
extern rtx        gen_uaddvsi4                      (rtx, rtx, rtx, rtx);
extern rtx        gen_addvsi4                       (rtx, rtx, rtx, rtx);
extern rtx        gen_subdi3                        (rtx, rtx, rtx);
extern rtx        gen_usubvdi4                      (rtx, rtx, rtx, rtx);
extern rtx        gen_subvdi4                       (rtx, rtx, rtx, rtx);
extern rtx        gen_usubvsi4                      (rtx, rtx, rtx, rtx);
extern rtx        gen_subvsi4                       (rtx, rtx, rtx, rtx);
extern rtx        gen_muldi3                        (rtx, rtx, rtx);
extern rtx        gen_mulsidi3                      (rtx, rtx, rtx);
extern rtx        gen_smulsi3_highpart              (rtx, rtx, rtx);
extern rtx        gen_umulsidi3                     (rtx, rtx, rtx);
extern rtx        gen_umulsi3_highpart              (rtx, rtx, rtx);
extern rtx        gen_umulxhi_vis                   (rtx, rtx, rtx);
extern rtx        gen_xmulx_vis                     (rtx, rtx, rtx);
extern rtx        gen_xmulxhi_vis                   (rtx, rtx, rtx);
extern rtx        gen_divsi3                        (rtx, rtx, rtx);
extern rtx        gen_udivsi3                       (rtx, rtx, rtx);
extern rtx        gen_negdi2                        (rtx, rtx);
extern rtx        gen_unegvdi3                      (rtx, rtx, rtx);
extern rtx        gen_negvdi3                       (rtx, rtx, rtx);
extern rtx        gen_unegvsi3                      (rtx, rtx, rtx);
extern rtx        gen_negvsi3                       (rtx, rtx, rtx);
extern rtx        gen_addtf3                        (rtx, rtx, rtx);
extern rtx        gen_subtf3                        (rtx, rtx, rtx);
extern rtx        gen_multf3                        (rtx, rtx, rtx);
extern rtx        gen_divtf3                        (rtx, rtx, rtx);
extern rtx        gen_divdf3                        (rtx, rtx, rtx);
extern rtx        gen_negtf2                        (rtx, rtx);
extern rtx        gen_negdf2                        (rtx, rtx);
extern rtx        gen_abstf2                        (rtx, rtx);
extern rtx        gen_absdf2                        (rtx, rtx);
extern rtx        gen_sqrttf2                       (rtx, rtx);
extern rtx        gen_sqrtdf2                       (rtx, rtx);
extern rtx        gen_ashldi3                       (rtx, rtx, rtx);
extern rtx        gen_ashrdi3                       (rtx, rtx, rtx);
extern rtx        gen_lshrdi3                       (rtx, rtx, rtx);
extern rtx        gen_jump                          (rtx);
extern rtx        gen_tablejump                     (rtx, rtx);
extern rtx        gen_call                          (rtx, rtx, rtx, rtx);
extern rtx        gen_call_value                    (rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_untyped_call                  (rtx, rtx, rtx);
extern rtx        gen_sibcall                       (rtx);
extern rtx        gen_sibcall_value                 (rtx, rtx);
extern rtx        gen_prologue                      (void);
extern rtx        gen_epilogue                      (void);
extern rtx        gen_sibcall_epilogue              (void);
extern rtx        gen_eh_return                     (rtx);
extern rtx        gen_return                        (void);
extern rtx        gen_frame_blockage                (void);
extern rtx        gen_probe_stack                   (rtx);
extern rtx        gen_untyped_return                (rtx, rtx);
extern rtx        gen_indirect_jump                 (rtx);
extern rtx        gen_save_stack_nonlocal           (rtx, rtx);
extern rtx        gen_restore_stack_nonlocal        (rtx, rtx);
extern rtx        gen_nonlocal_goto                 (rtx, rtx, rtx, rtx);
extern rtx        gen_builtin_setjmp_receiver       (rtx);
extern rtx        gen_popcountdi2                   (rtx, rtx);
extern rtx        gen_popcountsi2                   (rtx, rtx);
extern rtx        gen_clzdi2                        (rtx, rtx);
extern rtx        gen_clzsi2                        (rtx, rtx);
extern rtx        gen_prefetch                      (rtx, rtx, rtx);
extern rtx        gen_ctrapsi4                      (rtx, rtx, rtx, rtx);
static inline rtx gen_ctrapdi4                      (rtx, rtx, rtx, rtx);
static inline rtx
gen_ctrapdi4(rtx ARG_UNUSED (a), rtx ARG_UNUSED (b), rtx ARG_UNUSED (c), rtx ARG_UNUSED (d))
{
  return 0;
}
extern rtx        gen_stack_protect_set             (rtx, rtx);
extern rtx        gen_stack_protect_test            (rtx, rtx, rtx);
extern rtx        gen_movv1si                       (rtx, rtx);
extern rtx        gen_movv2hi                       (rtx, rtx);
extern rtx        gen_movv4qi                       (rtx, rtx);
extern rtx        gen_movv1di                       (rtx, rtx);
extern rtx        gen_movv2si                       (rtx, rtx);
extern rtx        gen_movv4hi                       (rtx, rtx);
extern rtx        gen_movv8qi                       (rtx, rtx);
extern rtx        gen_vec_initv1si                  (rtx, rtx);
extern rtx        gen_vec_initv2hi                  (rtx, rtx);
extern rtx        gen_vec_initv4qi                  (rtx, rtx);
extern rtx        gen_vec_initv1di                  (rtx, rtx);
extern rtx        gen_vec_initv2si                  (rtx, rtx);
extern rtx        gen_vec_initv4hi                  (rtx, rtx);
extern rtx        gen_vec_initv8qi                  (rtx, rtx);
extern rtx        gen_wrgsr_vis                     (rtx);
extern rtx        gen_rdgsr_vis                     (rtx);
extern rtx        gen_vcondv4hiv4hi                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv2siv2si                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv8qiv8qi                (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vec_perm_constv8qi            (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_permv1di                  (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_permv2si                  (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_permv4hi                  (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_permv8qi                  (rtx, rtx, rtx, rtx);
extern rtx        gen_mem_thread_fence              (rtx);
extern rtx        gen_membar                        (rtx);
extern rtx        gen_atomic_loadqi                 (rtx, rtx, rtx);
extern rtx        gen_atomic_loadhi                 (rtx, rtx, rtx);
extern rtx        gen_atomic_loadsi                 (rtx, rtx, rtx);
extern rtx        gen_atomic_loaddi                 (rtx, rtx, rtx);
extern rtx        gen_atomic_storeqi                (rtx, rtx, rtx);
extern rtx        gen_atomic_storehi                (rtx, rtx, rtx);
extern rtx        gen_atomic_storesi                (rtx, rtx, rtx);
extern rtx        gen_atomic_storedi                (rtx, rtx, rtx);
extern rtx        gen_atomic_compare_and_swapqi     (rtx, rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_compare_and_swaphi     (rtx, rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_compare_and_swapsi     (rtx, rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_compare_and_swapdi     (rtx, rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_compare_and_swapsi_1   (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_compare_and_swapdi_1   (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_exchangesi             (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_test_and_set           (rtx, rtx, rtx);

#endif /* GCC_INSN_FLAGS_H */
