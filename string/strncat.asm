  def strncat
  even

################################################################################
#                                  strncat
###############################################################################
# Append one string to another, but copy no more than N characters
# 
# Inputs: R1 - Destination string
#         R2 - Source string
#         R3 - Max characters to copy
#
# Returns: R1 - Size of string buffer
################################################################################
strncat:
  # Exit now if we are to copy no characters
  mov  r3, r3
  jeq  copy_end

  mov  r1, r0    # Save buffer pointer
  clr  r4        # Set comparison value

  # Find end of destination string
scan_top:
  cb   r4, *r0+  # Check for NULL, update pointer
  jne  scan_top
  dec  r0        # Overwrite NULL

  # Copy source string
copy_top:
  movb *r2+, *r0+  # Copy byte, check for NULL, update pointer
  jeq  copy_end
  dec  r3          # Decrement copy count
  jne  copy_top
  movb r4, *r0     # Copy NULL
copy_end:
  b    *r11

  .size strncat, .-strncat
