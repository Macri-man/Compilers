program main(output,input);
    var a,g: integer;
    var x,y: real;
    var c: array [1..3] of integer;
    function foo(x:integer): integer;
    begin 
        foo := a
    end;
    procedure boo(x:integer);
    begin
        c[1] := a;
        g := foo(a)
    end;    
    function bar(x:integer): integer;
    begin 
        bar := a;
        boo(a);
        bar := foo(1.4)
    end;
begin
    g := bar(a);
    boo(1);
    a := foo(c[a])
end.
