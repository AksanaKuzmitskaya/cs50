bool search(int needle, int haystack[], int size)
{
    int lo = 0;
    int hi = size;
    int mid = (hi + lo) / 2;
    
    while (hi > lo)
    {
        if (haystack[mid] == needle)
        {
         return true
        }
        else if (haystack[mid] > needle)
        {
            hi = mid - 1; 
        }
        else
        {
            lo = mid + 1;
        }
    }
    
    return false
} 
