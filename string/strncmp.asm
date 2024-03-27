  def strncmp
  even

################################################################################
#                                  strncmp
################################################################################
# Compare two strings. Return a value which reflects the comparison
#
# Inputs: R1 - First buffer address
#         R2 - Second buffer to compare
#         R3 - Number of bytes to compare
#
# Returns: R1 - Returns an integer less than, equal to, or greater than zero
#               if the first n bytes of s1 is found, respectively, to be less
#               than, to match, or be greater than the first n bytes of s2
################################################################################
strncmp:
  mov   r1, r0
  clr   r1
  neg   r3
  jeq   compare_match  # If size == 0, give up now
compare_top:
  cb    *r2+, *r0      # Is this a match?
  jlt   compare_less
  jgt   compare_more
  movb  *r0+, r4       # Is this NULL?
  jeq   compare_match
  inc   r3             # Decrement search count
  jlt   compare_top    # Still searching? Get to it
compare_match:
  b     *r11
compare_less:
  dect r1
compare_more:
  inc  r1
  b     *r11

  .size strncmp, .-strncmp

