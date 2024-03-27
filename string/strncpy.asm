  def strncpy
  even

################################################################################
#                                  strncpy
################################################################################
# Copy no more than the first N characters of a string
#
# Inputs: R1 - Destination string
#         R2 - Source string
#         R3 - Maximum number of characters to copy
#
# Returns: R1 - Pointer to destination string
################################################################################
strncpy:
  mov  r1, r0

  # Check for zero length
  mov  r3, r3
  jeq  copy_end

  # Copy loop
copy_top:
  movb *r2+, *r0+      # Is this NULL?
  jeq  copy_exit
  dec  r3
  jne  copy_top

  # Append NULL if needed
copy_end:
  movb r3, *r0
copy_exit:
  b    *r11

  .size strncpy, .-strncpy

