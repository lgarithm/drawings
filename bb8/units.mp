u := 1cm;

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

hr := RR * sind(25);
Hr := sqrt(1 + (hr/RR)*(hr/RR)) * RR;

n := 4;
Th := 360 / n;
th0 := 0;
