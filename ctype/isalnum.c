int isalnum(int c)
{
  return((unsigned int)(c - '0') <= ('9' - '0') ||
         (unsigned int)((c | 0x20) - 'a') <= ('z' - 'a'));
}

