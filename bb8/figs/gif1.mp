% outputformat := "png";
outputtemplate := "%j-%02c.%o";

nf := 24;
dr := 360 / nf;

def frame(expr j) =
    draw_main(n, t);
enddef;

for j:=1 upto nf:
    beginfig(j);
        th0 := th0 + dr;
        frame(j);
    endfig;
endfor;
