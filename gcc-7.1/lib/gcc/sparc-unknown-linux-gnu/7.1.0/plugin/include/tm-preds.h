/* Generated automatically by the program 'build/genpreds'
   from the machine description file '../../gcc-7.1.0/gcc/config/sparc/sparc.md'.  */

#ifndef GCC_TM_PREDS_H
#define GCC_TM_PREDS_H

#ifdef HAVE_MACHINE_MODES
extern int general_operand (rtx, machine_mode);
extern int address_operand (rtx, machine_mode);
extern int register_operand (rtx, machine_mode);
extern int pmode_register_operand (rtx, machine_mode);
extern int scratch_operand (rtx, machine_mode);
extern int immediate_operand (rtx, machine_mode);
extern int const_int_operand (rtx, machine_mode);
extern int const_scalar_int_operand (rtx, machine_mode);
extern int const_double_operand (rtx, machine_mode);
extern int nonimmediate_operand (rtx, machine_mode);
extern int nonmemory_operand (rtx, machine_mode);
extern int push_operand (rtx, machine_mode);
extern int pop_operand (rtx, machine_mode);
extern int memory_operand (rtx, machine_mode);
extern int indirect_operand (rtx, machine_mode);
extern int ordered_comparison_operator (rtx, machine_mode);
extern int comparison_operator (rtx, machine_mode);
extern int const_zero_operand (rtx, machine_mode);
extern int const_all_ones_operand (rtx, machine_mode);
extern int const_4096_operand (rtx, machine_mode);
extern int small_int_operand (rtx, machine_mode);
extern int uns_small_int_operand (rtx, machine_mode);
extern int const_high_operand (rtx, machine_mode);
extern int const_compl_high_operand (rtx, machine_mode);
extern int fp_const_high_losum_operand (rtx, machine_mode);
extern int const_double_or_vector_operand (rtx, machine_mode);
extern int zero_or_v7_operand (rtx, machine_mode);
extern int symbolic_operand (rtx, machine_mode);
extern int tgd_symbolic_operand (rtx, machine_mode);
extern int tld_symbolic_operand (rtx, machine_mode);
extern int tie_symbolic_operand (rtx, machine_mode);
extern int tle_symbolic_operand (rtx, machine_mode);
extern int medium_pic_operand (rtx, machine_mode);
extern int label_ref_operand (rtx, machine_mode);
extern int data_segment_operand (rtx, machine_mode);
extern int text_segment_operand (rtx, machine_mode);
extern int register_or_zero_operand (rtx, machine_mode);
extern int register_or_v9_zero_operand (rtx, machine_mode);
extern int register_or_zero_or_all_ones_operand (rtx, machine_mode);
extern int fp_register_operand (rtx, machine_mode);
extern int cstore_result_operand (rtx, machine_mode);
extern int fcc_register_operand (rtx, machine_mode);
extern int fcc0_register_operand (rtx, machine_mode);
extern int icc_register_operand (rtx, machine_mode);
extern int icc_or_fcc_register_operand (rtx, machine_mode);
extern int arith_operand (rtx, machine_mode);
extern int arith_double_operand (rtx, machine_mode);
extern int arith_add_operand (rtx, machine_mode);
extern int arith_double_add_operand (rtx, machine_mode);
extern int arith10_operand (rtx, machine_mode);
extern int arith11_operand (rtx, machine_mode);
extern int uns_arith_operand (rtx, machine_mode);
extern int arith5_operand (rtx, machine_mode);
extern int compare_operand (rtx, machine_mode);
extern int input_operand (rtx, machine_mode);
extern int call_address_operand (rtx, machine_mode);
extern int call_operand (rtx, machine_mode);
extern int mem_noofs_operand (rtx, machine_mode);
extern int nz_comparison_operator (rtx, machine_mode);
extern int c_comparison_operator (rtx, machine_mode);
extern int v_comparison_operator (rtx, machine_mode);
extern int icc_comparison_operator (rtx, machine_mode);
extern int fcc_comparison_operator (rtx, machine_mode);
extern int icc_or_fcc_comparison_operator (rtx, machine_mode);
extern int v9_comparison_operator (rtx, machine_mode);
extern int v9_register_comparison_operator (rtx, machine_mode);
extern int cc_arith_operator (rtx, machine_mode);
extern int cc_arith_not_operator (rtx, machine_mode);
#endif /* HAVE_MACHINE_MODES */

#define CONSTRAINT_NUM_DEFINED_P 1
enum constraint_num
{
  CONSTRAINT__UNKNOWN = 0,
  CONSTRAINT_r,
  CONSTRAINT_b,
  CONSTRAINT_c,
  CONSTRAINT_d,
  CONSTRAINT_e,
  CONSTRAINT_f,
  CONSTRAINT_h,
  CONSTRAINT_I,
  CONSTRAINT_J,
  CONSTRAINT_K,
  CONSTRAINT_L,
  CONSTRAINT_M,
  CONSTRAINT_N,
  CONSTRAINT_O,
  CONSTRAINT_P,
  CONSTRAINT_m,
  CONSTRAINT_o,
  CONSTRAINT_W,
  CONSTRAINT_w,
  CONSTRAINT_T,
  CONSTRAINT_p,
  CONSTRAINT_G,
  CONSTRAINT_C,
  CONSTRAINT_A,
  CONSTRAINT_H,
  CONSTRAINT_D,
  CONSTRAINT_Q,
  CONSTRAINT_R,
  CONSTRAINT_S,
  CONSTRAINT_Y,
  CONSTRAINT_Z,
  CONSTRAINT_U,
  CONSTRAINT_V,
  CONSTRAINT__l,
  CONSTRAINT__g,
  CONSTRAINT_i,
  CONSTRAINT_s,
  CONSTRAINT_n,
  CONSTRAINT_E,
  CONSTRAINT_F,
  CONSTRAINT_X,
  CONSTRAINT__LIMIT
};

extern enum constraint_num lookup_constraint_1 (const char *);
extern const unsigned char lookup_constraint_array[];

/* Return the constraint at the beginning of P, or CONSTRAINT__UNKNOWN if it
   isn't recognized.  */

static inline enum constraint_num
lookup_constraint (const char *p)
{
  unsigned int index = lookup_constraint_array[(unsigned char) *p];
  return (index == UCHAR_MAX
          ? lookup_constraint_1 (p)
          : (enum constraint_num) index);
}

extern bool (*constraint_satisfied_p_array[]) (rtx);

/* Return true if X satisfies constraint C.  */

static inline bool
constraint_satisfied_p (rtx x, enum constraint_num c)
{
  int i = (int) c - (int) CONSTRAINT_I;
  return i >= 0 && constraint_satisfied_p_array[i] (x);
}

static inline bool
insn_extra_register_constraint (enum constraint_num c)
{
  return c >= CONSTRAINT_r && c <= CONSTRAINT_h;
}

static inline bool
insn_extra_memory_constraint (enum constraint_num c)
{
  return c >= CONSTRAINT_m && c <= CONSTRAINT_w;
}

static inline bool
insn_extra_special_memory_constraint (enum constraint_num c)
{
  return c >= CONSTRAINT_T && c <= CONSTRAINT_T;
}

static inline bool
insn_extra_address_constraint (enum constraint_num c)
{
  return c >= CONSTRAINT_p && c <= CONSTRAINT_p;
}

static inline void
insn_extra_constraint_allows_reg_mem (enum constraint_num c,
				      bool *allows_reg, bool *allows_mem)
{
  if (c >= CONSTRAINT_G && c <= CONSTRAINT_Z)
    return;
  if (c >= CONSTRAINT_U && c <= CONSTRAINT_U)
    {
      *allows_reg = true;
      return;
    }
  if (c >= CONSTRAINT_V && c <= CONSTRAINT__g)
    {
      *allows_mem = true;
      return;
    }
  (void) c;
  *allows_reg = true;
  *allows_mem = true;
}

#define CONSTRAINT_LEN(c_,s_) 1

extern enum reg_class reg_class_for_constraint_1 (enum constraint_num);

static inline enum reg_class
reg_class_for_constraint (enum constraint_num c)
{
  if (insn_extra_register_constraint (c))
    return reg_class_for_constraint_1 (c);
  return NO_REGS;
}

extern bool insn_const_int_ok_for_constraint (HOST_WIDE_INT, enum constraint_num);
#define CONST_OK_FOR_CONSTRAINT_P(v_,c_,s_) \
    insn_const_int_ok_for_constraint (v_, lookup_constraint (s_))

enum constraint_type
{
  CT_REGISTER,
  CT_CONST_INT,
  CT_MEMORY,
  CT_SPECIAL_MEMORY,
  CT_ADDRESS,
  CT_FIXED_FORM
};

static inline enum constraint_type
get_constraint_type (enum constraint_num c)
{
  if (c >= CONSTRAINT_T)
    {
      if (c >= CONSTRAINT_G)
        return CT_FIXED_FORM;
      if (c >= CONSTRAINT_p)
        return CT_ADDRESS;
      return CT_SPECIAL_MEMORY;
    }
  if (c >= CONSTRAINT_m)
    return CT_MEMORY;
  if (c >= CONSTRAINT_I)
    return CT_CONST_INT;
  return CT_REGISTER;
}
#endif /* tm-preds.h */
