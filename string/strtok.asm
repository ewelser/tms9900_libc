  dseg

  # This stores a pointer to the last tokenized string
last_string
  data 0

  pseg

  def strtok
  even

################################################################################
#                                 strtok
################################################################################
# Decompose a string into a series of tokens
#
# Inputs: R1 - String to tokenize, NULL if we are to tokenize the last string
#         R2 - Token delimiter
#
# Returns: R1 - Pointer to first token, NULL if none found
################################################################################
strtok:
  # We'll take advantage of special knowledge of the functions we will call
  # Only R1, R3, R4, R5, R11 will be affected
  # The rest of the registers we can use as if they were non-volatile

  mov  r11, r7          # Save return pointer
  li   r6, last_string  # Save in a register for later
  mov  r1, r12          # Save string start and see if it's NULL
  jne  scan_top

  # Start string is NULL, tokenize the last string we used
  mov  *r6, r1   # Retrieve pointer for last string
  mov  r1, r12
  jeq  scan_end  # That was NULL too, nothing to do here

scan_top:
  # Skip leading delimiters
  bl   @strspn
  a    r12, r1    # Point to start of token
  mov  r1, r12    # Save for later
  
  # Find end of the token
  bl   @strcspn
  mov  r1, r3     # Is this a zero length token?
  jeq  last_token # R1 will equal zero, which will be the NULL return

  # Found a token, return it
  mov  r12, r4    # Save start of token
  a    r1, r12    # Point to end of token
  mov  r4, r1     # Prepare start of token for return
  movb *r12, r3   # Is this a NULL?
  jeq  last_token

  # Token found in the middle of the string
  sb *r12, *r12+  # Terminate token, point to start of next delimiter
  mov r12, r3     # Prepare for common exit

last_token:
  # Remember start of next delimiter
  mov  r3, *r6    
scan_end:
  b    *r7        # Return

  .size strtok, .-strtok

