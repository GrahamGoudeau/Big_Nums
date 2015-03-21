Big_Nums
========

Author: Graham Goudeau
----------------------

Interface for a big_num implementation.  Big_nums support arbitrary precision
addition and subtraction, limited only by machine resources. Numbers can have
a length of at most 2^(max value of size_t) - 1, which is implementation 
dependent.  If a big_num has length greater than this, the behavior is
undefined.

If the user desires big_nums in bases other than 10, the const BASE variable
at the top of the big_num.c file can be changed to values 2 <= x <= 10.

When an addition or subtraction is performed on a big_num, the implementation
recalculates how much storage is actually required by the numeric digits, and
trims off any unnecessary storage.  Because of this, a big_num always takes up
as little storage as possible.

(Storage for a given big_num involves: n*sizeof(char) + sizeof(bool) bytes,
where n is the number of digits in the big_num plus a small amount of leading 
zeroes.)

Any big_num that a user requests must later by freed by the user with the 
included free_big_num() function.  

Also included is a function that fills the role of a for loop that is compatible
with big_nums, as well as functions that are equivalent to <= and ==.
