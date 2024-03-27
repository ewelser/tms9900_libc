int toupper(int c)
{
  if((unsigned int)(c - 'a') <= ('z' - 'a'))
  {
    c -= ('a' - 'A');
  }
  return c;
}
