  def strcspn
  even

################################################################################
#                                  strcspn
################################################################################
# Find the length of the check string consisting entirely of
# non-matching characters
#
# Inputs: R1 - String to check
#         R2 - Characters to not match
#
# Returns: R1 - Size of non-matching length
################################################################################
strcspn:
  mov  r1, r0
  seto r1         # Initialize match length to -1

  # Outer loop, iterate over check string
check_top:
  inc  r1         # Increment match length
  movb *r0+, r3   # Get next check character
  jeq  check_end  # Was this the end of the check string?

  # Inner loop, iterate over match string
  mov r2, r4      # Begin at start of match string
match_top:
  movb *r4+, r5   # Get next match character
  jeq check_top   # Get next check character if not in match string
  cb  r5, r3      # Compare check and match characters
  jne match_top   # No match? Try next match character

check_end:
  b   *r11

  .size strcspn, .-strcspn

