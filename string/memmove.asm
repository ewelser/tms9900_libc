  def memmove
  even

################################################################################
#                              memmove
################################################################################
# Copy possibly overlapping memory blocks
#
# Inputs: R1 - Destination address
#         R2 - Source address
#         R3 - Copy count
#
# Returns: R1 - Original destination address
################################################################################
memmove:
  # Copy value to preserve return value
  mov  r1, r0

  # See if we can use memcpy instead
  c    r0, r2
  jle  goto_memcpy
  a    r3, r0
  c    r0, r2
  jle  goto_memcpy

  # We can't use memcpy due to overlapping bounds
  # Copy block back-to-front to avoid corrupting source data
  a    r3, r2
  jmp  move_bottom
move_top:
  movb *r2, *r0    # Copy a byte
move_bottom:
  dec  r2          # Decrement source pointer
  dec  r0          # Decrement destination pointer
  c    r1, r0      # Did we reach the start of the block?
  jle  move_top    # If not, keep copying
  b    *r11

goto_memcpy:
  b    @memcpy

  .size memmove, .-memmove
