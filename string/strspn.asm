  def strspn
  even

################################################################################
#                                  strspn
################################################################################
# Find the length of the check string consisting entirely of match characters
#
# Inputs: R1 - String to check
#         R2 - Characters to match
#
# Returns: R1 - Size of matching length
################################################################################
strspn:
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
  jeq check_end   # Jump if check character not in match string
  cb  r5, r3      # Compare check and match characters
  jne match_top   # No match? Try next match character
  jeq check_top   # Match? Get next check character

check_end:
  b   *r11

  .size strspn, .-strspn

