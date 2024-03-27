  def strcpy
  even

################################################################################
#                                  strcpy
################################################################################
# Compare two strings. Return a value which reflects the comparison
#
# Inputs: R1 - Destination string
#         R2 - Source string
#
# Returns: R1 - Pointer to destination string
################################################################################
strcpy:
  mov  r1, r0
copy_top:
  movb *r2+, *r0+      # Is this NULL?
  jne  copy_top
  b    *r11

  .size strcpy, .-strcpy

