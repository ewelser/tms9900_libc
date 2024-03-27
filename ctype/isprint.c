int isprint(int c)
{
  return((unsigned int)(c - ' ') <= ('~' - ' '));
}
