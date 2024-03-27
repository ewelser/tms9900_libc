  def strlen
  even

################################################################################
#                                  strlen
###############################################################################
# Find size of a null-terminated string buffer
# 
# Inputs: R1 - String buffer
#
# Returns: R1 - Size of string buffer
################################################################################
strlen:
  mov r1, r0    # Save buffer pointer
  clr r2        # Set comparison value
len_top:
  cb  r2, *r1+  # Check for NULL, update pointer
  jne len_top
  s   r0, r1    # Find byte count
  dec r1        # Count is off by one, correct it
  b   *r11       # Return length

  .size strlen, .-strlen
