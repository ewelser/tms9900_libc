  def strchr
  even

################################################################################
#                                  strchr
###############################################################################
# Find the first occurrance of a character in a string
# 
# Inputs: R1 - Search string
#         R2 - Character to match
#
# Returns: R1 - Pointer to matching character
################################################################################
strchr:
  # Search for matching value
  swpb r2
scan_top:
  movb *r1+, r0  # Check for NULL, update pointer
  jeq  not_found
  cb   r2, r0
  jne  scan_top

  # Match found, return it
  dec r1 
  b    *r11

not_found:
  clr r1
  b   *r11

  .size strchr, .-strchr
