  def strpbrk
  even

################################################################################
#                                  strpbrk
################################################################################
# Find the position of the first check character to appear in match string
#
# Inputs: R1 - String to check
#         R2 - Characters to not match
#
# Returns: R1 - Pointer to first matching character, or NULL if none found
################################################################################
strpbrk:
  mov  r1, r0
  clr  r1

  # Outer loop, iterate over check string
check_top:
  movb *r0+, r3   # Get next check character
  jeq  no_match   # Was this the end of the check string?

  # Inner loop, iterate over match string
  mov r2, r4      # Begin at start of match string
match_top:
  movb *r4+, r5   # Get next match character
  jeq check_top   # Get next check character if not in match string
  cb  r5, r3      # Compare check and match characters
  jne match_top   # No match? Try next match character
  
  # Match found, return pointer to it
  mov r0, r1
  dec r1
no_match:
  b   *r11

  .size strpbrk, .-strpbrk

