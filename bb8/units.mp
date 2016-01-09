u := 1cm;

n := 4;
th0 := 360 / n;
RR = 8u;
Rth = 30;
R := RR * sind(Rth);
rth = 22;  % asin (0.75 / 2)
r := RR * sind(rth);
rrth := 13; % asin (0.45 / 2)
rr := RR * sind(rrth);
dd := 0.2u;
t := 9;
tt := 9;
ts := 5;

hr := r;
Hr := sqrt(1 + (hr/RR)*(hr/RR)) * RR;
