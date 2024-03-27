  def memchr
  even

################################################################################
#                                  memchr
################################################################################
# Return a pointer to the first occurrance of VALUE in the first SIZE bytes
#
# Inputs: R1 - Buffer address
#         R2 - Value C to search for
#         R3 - Size of buffer to search
#
# Returns: R1 - Pointer to found value, NULL if not found
################################################################################
memchr:
  neg  r3
  jeq  search_failed  # If size == 0, give up now
  swpb r2
search_top:
  cb   r2, *r1        # Is this a match?
  jeq  search_end     # If so, return the pointer
  inc  r1             # Update pointer for next check
  inc  r3             # Decrement search count
  jlt  search_top     # Still searching? Get to it
search_failed:
  clr  r1             # No match found, return NULL
search_end:
  b    *r11

  .size memchr, .-memchr

