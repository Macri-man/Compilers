program main( input, output );
	var a, b, c: integer;
	var x,y,z : real;
	function gcd( a,b : integer ) : integer;
		var r: integer;
        begin
            if a < b then 
                gcd := gcd( b, a )
            else if b = 0 then
                gcd := a
            else
                begin
                    r := a mod b;
                    gcd := gcd(b, r)
                end
        end;
    function gcdtwo( a,b : real ) : real;
		var r: real;
		var t: integer;
        begin
        	t := gcd ( 0 , 0 );
            if a < b then 
                gcdtwo := gcdtwo( b , a )
            else if b = 0 then
                gcdtwo := a
            else
                begin
                    r := (a mod b);
                    gcdtwo := gcdtwo(b, r)
                end
        end;
    begin
    	a := 5;
    	b := 10;
        read( a );
        c := gcd ( a , b );
        x := gcdtwo( y , z );
        writeln(c)
    end.