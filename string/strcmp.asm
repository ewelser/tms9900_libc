  def strcmp
  even

################################################################################
#                                  strcmp
################################################################################
# Compare two strings. Return a value which reflects the comparison
#
# Inputs: R1 - First buffer address
#         R2 - Second buffer to compare
#
# Returns: R1 - Returns an integer less than, equal to, or greater than zero
#               if the first n bytes of s1 is found, respectively, to be less
#               than, to match, or be greater than the first n bytes of s2
################################################################################
strcmp:
  mov  r1, r0
  clr  r1
compare_top:
  cb   *r2+, *r0      # Is this a match?
  jlt  compare_less
  jgt  compare_more
  movb *r0+, r3       # Is this NULL?
  jne  compare_top
  b    *r11
compare_less:
  dect r1
compare_more:
  inc  r1
  b    *r11

  .size strcmp, .-strcmp

