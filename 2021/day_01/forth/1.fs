include input.txt

variable data 2000 cells allot
: move_to_array 2001 1 do data 2000 i - cells + ! loop ;
: print_array 2000 0 do data i cells + ? loop ;
move_to_array

variable counter
0 counter !
: increase 1 counter +! ;
: ?bigger < if increase then ;

: calculate 
    0 counter !
    2000 0 do
    data i cells + @
    data i 1 + cells + @ 
    ?bigger
    loop
    counter ?
;

variable prev
data 0 cells + @
data 1 cells + @
data 2 cells + @
+ + prev !
variable curr
: window_slide 
    0 counter !
    1999 1 do 
        data i cells + @ 
        data i 1 +  cells + @ 
        data i 2 + cells + @ 
        + + curr ! 
        prev @ curr @
        ?bigger
        curr @ prev !
    loop
    counter ?
;
     
calculate
window_slide
