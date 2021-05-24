# savebooks.c
Saves a list of 100 books  in a .dat file (in binary format).
If the file already exists, the program shows you its current contents and then enables you to add to the file.
===============================================================================================================
1)The "a+b" format for append + binary format for (fread&fwrite).
2)Rewind() takes file pointer to start.
3)The variable filecount keeps track of how many structures were read.
4) The expression "count - filecount" yields the number of new book titles to be added, and the
call to fwrite() writes that number of structure-sized blocks to the file.
5)The expression "&library[filecount]" is the address of the first new structure in the array, so copying begins
from that point.


