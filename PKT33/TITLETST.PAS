program titletst;

{$A-,B-,D+,E-,F+,I+,L+,N-,O-,R+,S+,V+}

{ Set stack, minheap and maxheap memory allocations }
{$M 32000,0,640000}
uses drivers,fonts,graph,opmouse,opcrt,wins,everobj;

{$I title2.inc}
{$I title.inc}

begin
  clrscr;
  initwins;
  title;
end.
