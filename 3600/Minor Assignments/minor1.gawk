Samuel Njogo
snn0070

NR>1 { 
	if ( $1 >= 0 ) 
	{
           printf "%5s\t%5s\n", $1, $1 % 360
        }
       
	else 
	{
           printf "%5s\t%5s\n", $1 , 360 - (($1 * -1) % 360)
        }
}
