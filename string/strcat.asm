  def strcat
  even

################################################################################
#                                  strcat
###############################################################################
# Append one string to another
# 
# Inputs: R1 - Destination string
#         R2 - Source string
#
# Returns: R1 - Size of string buffer
################################################################################
strcat:
  mov  r1, r0    # Save buffer pointer
  clr  r3        # Set comparison value

  # Find end of destination string
scan_top:
  cb   r3, *r0+  # Check for NULL, update pointer
  jne  scan_top
  dec  r0        # Overwrite NULL

  # Copy source string
copy_top:
  movb *r2+, *r0+  # Copy byte, check for NULL, update pointer
  jne  copy_top
  b    *r11

  .size strcat, .-strcat
