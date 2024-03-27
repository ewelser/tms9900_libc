int tolower(int c)
{
  if((unsigned int)(c - 'A') <= ('Z' - 'A'))
  {
    c += ('a' - 'A');
  }
  return c;
}
