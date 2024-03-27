  def strstr
  even

################################################################################
#                                  strstr
################################################################################
# Find a string contained within another string
#
# Inputs: R1 - Haystack
#         R2 - Needle
#
# Returns: R1 - Start of "needle" in "haystack", NULL if not found
################################################################################
strstr:
  movb *r2+, r3
  jeq  match_end     # Match empty needle with all of haystack

  # Outer loop, iterate over check string
haystack_top:
  movb *r1+, r4
  jeq  no_match
  cb   r3, r4
  jne  haystack_top

  mov  r1, r4
  mov  r2, r5
needle_top:
  movb *r5+, r6
  jeq  match
  cb   r6, *r4+  
  jeq  needle_top
  jmp  haystack_top

match:
  dec  r1
  b    *r11

no_match:
  clr  r1
match_end:
  b    *r11

  .size strstr, .-strstr

