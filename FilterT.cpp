#include <stdio.h>
#include <string.h>

class BloomFilter
{
  public:
      int filter_len;
      long filter;
      
      BloomFilter(int f_len)
      {
        filter_len = f_len;   // filter size - m
        filter = 0;           // filter
      }
      int hash1(char* str1)
      {
        int number = 17;
        int iteration = 0;
        for(int i=0; i < strlen(str1); i++)
        {         
          int code = str1[i];
          iteration = (iteration * number + code) % filter_len;
          if (iteration < 0)
            iteration *= -1;
        }
        int mask = 1 << iteration;
        return mask;
      }

      int hash2(char* str1)
      {
        int number = 223;
        int iteration = 0;
        for(int i=0; i < strlen(str1); i++)
        {         
          int code = str1[i];
          iteration = (iteration * number + code) % filter_len;
          if (iteration < 0)
            iteration *= -1;
        }
        int mask = 1 << iteration;
        return mask;
      }

      void add(char* str1)
      {
        filter |= hash1(str1);
        filter |= hash2(str1);
      }

      bool is_value(char* str1)
      {
        int mask = 0;
        mask |= hash1(str1);     
        mask |= hash2(str1);
        if ( (filter & mask) == mask )
          return true;
        return false;
      }
};

/*
int main()
{  
  int test = 0;
  BloomFilter* Filter = new BloomFilter(32);
  char string[21] = "01234567890123456789";
  char* _str = new char[11];
  int str_len = 10;
  
  for (int i = 0; i < 10; i++)
  {
    for (int j = i; j < i+10; j++) 
    {
      *(_str++) = string[j];
    }
    *_str = '\0';
    _str -= 10;
    Filter->add(_str);
  }

  int mistake = 0;
  for (int i = 0; i < 10; i++)
  {
    for (int j = i; j < i+10; j++) 
    {
      *(_str++) = string[j];
    }
    *_str = '\0';
    _str -= 10;
    if (!Filter->is_value(_str))
      mistake ++;
  }
  if (Filter->is_value("ìèðó ìèð")) test++;
  if (Filter->is_value("8901567234")) mistake++;
  if (Filter->is_value("0231589674")) mistake++;
  test += mistake;
  return test;
}
*/


