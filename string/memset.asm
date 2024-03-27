  def memset
  even

################################################################################
#                              memset
################################################################################
# Initialize a block of memory with a set value
#
# Inputs: R1 - Destination address
#         R2 - Value
#         R3 - Set count
#
# Returns: R1 - Original destination address
################################################################################
memset:
  # Copy value to preserve return value
  neg   r3
  jeq   copy_end
  mov   r1, r0
  swpb  r2
copy_top:
  movb  r2, *r0+
copy_bottom:
  inc   r3
  jlt   copy_top
copy_end:
  b     *r11

  .size memset, .-memset
