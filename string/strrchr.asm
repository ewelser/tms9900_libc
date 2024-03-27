  def strrchr
  even

################################################################################
#                                  strrchr
###############################################################################
# Find the last occurrance of a character in a string
# 
# Inputs: R1 - Search string
#         R2 - Character to match
#
# Returns: R1 - Pointer to matching character, NULL if not found
################################################################################
strrchr:
  # Search for matching value
  swpb r2
  mov  r1, r3
  clr  r1
scan_top:
  movb *r3+, r0  # Check for NULL, update pointer
  jeq  scan_done
  cb   r2, r0
  jne  scan_top  
  # Match found, remember it
  mov  r3, r1
  dec  r1
  jmp  scan_top

scan_done:
  b   *r11

  .size strrchr, .-strrchr

