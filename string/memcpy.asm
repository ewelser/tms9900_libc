  def memcpy
  even

################################################################################
#                              memcpy
################################################################################
# Copy non-overlapping memory blocks
#
# Inputs: R1 - Destination address
#         R2 - Source address
#         R3 - Copy count
#
# Returns: R1 - Original destination address
################################################################################
memcpy:
  # Copy value to preserve return value
  mov  r1, r0
  neg  r3
  jeq  copy_end
copy_top:
  movb *r2+, *r0+
copy_bottom:
  inc  r3
  jlt  copy_top
copy_end:
  b    *r11

  .size memcpy, .-memcpy
